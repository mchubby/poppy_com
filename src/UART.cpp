#include "UART.h"


msg_t slaveMsg;
volatile unsigned char communicationState = 0x00;
unsigned char receiveAdress;
unsigned char expectedMessageSize;

void serialEvent()
{
	if(communicationState == 0x01) return;	//master receiver mode (not yet implemented)
	else if(communicationState == 0x00)		//enter in slave receiver mode
		communicationState == 0x02;

	switch(communicationState)
	{
		case 0x02:  // Store adress byte
			receiveAdress = Serial.read();
			if((receiveAdress&0x01) == 0x00) // master ask for request
			{
				if((receiveAdress>>1) == ctx.id && ctx.tx_cb)
				{
					(ctx.tx_cb)(&slaveMsg);
					Serial.write(slaveMsg.data,slaveMsg.size);
					Serial.flush();
				}
				communicationState = 0x00;
			}
			else communicationState++;
			break;

		case 0x03:	// Store register byte
			slaveMsg.reg = Serial.read();
			switch(slaveMsg.reg)
			{
                case GET_ID:
                    Serial.write(ctx.id);
					communicationState = 0x00;
					break;
				case WRITE_ID:
                    slaveMsg.size = 1;
					communicationState = 0x05;
					break;
                case GET_MODULE_TYPE:
                    Serial.write(ctx.type);
					communicationState = 0x00;
					break;
                case GET_STATUS:
                    //Serial.write((uint8_t*)ctx.status,5);
					communicationState = 0x00;
					break;
                default:
                    communicationState++;
					break;
            }
			break;

		case 0x04:	// Store message size
			slaveMsg.size = 0;
			expectedMessageSize = Serial.read();
			if(expectedMessageSize) communicationState++;
			else if(ctx.rx_cb)
			{
				slaveMsg.size = 0;
				(ctx.rx_cb)(RX,&slaveMsg);
				communicationState = 0x00;
			}
			else communicationState = 0x00;
			break;

		case 0x05:	// Store message
			if(slaveMsg.reg == WRITE_ID)
			{
				ctx.id = Serial.read();
				communicationState = 0x00;
			}
			else if(expectedMessageSize)
			{
				expectedMessageSize--;
				slaveMsg.data[slaveMsg.size] = Serial.read();
				if(expectedMessageSize) slaveMsg.size++;
				else
				{
					//controle crc
				}
			}
			break;
	}
}



