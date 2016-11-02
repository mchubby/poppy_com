#include "UART.h"
#include "crc.h"
#include "HardwareSerial.h"
#include "Arduino.h"


void serialEvent()
{
    static unsigned char count = 0;
    static unsigned char keep = 0;
    static unsigned char size = 0;
    static bool toggle = false;
    static int serial_time = millis();
    if( millis() - serial_time > 3 ) {
        count = 0;
        keep = 0;
    }
    serial_time = millis();
	while (Serial.available()) {
        // get the new byte:
        unsigned char data = (char)Serial.read();
        if (!count && data == ctx.id) { // ID check
            keep = 1;        }
        if (count == 1 && keep) { // Catch register
            ctx.msg.reg = data;
        }
        if (count == 2) {// Catch size
            if (keep) {
                ctx.msg.size = data;
            }
            size = data;
        }
        if (count > 2) {// Catch data
            if (keep) {
                ctx.msg.data[count-3] = data;
            }
            if (count > size+2) {// Catch crc
                if (keep) {
                    if (data == crc(&ctx.msg.data[0], ctx.msg.size)) {
                        ctx.rx_cb(&ctx.msg);
                    }
                    else
                        ctx.status.rx_error = true;
                }
                count = 0;
                keep = 0;
                return;
            }
        }
        count++;
	}
}
