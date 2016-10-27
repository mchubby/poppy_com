/*
 * poppyNetwork.c
 *
 * Created: 16/02/2015 11:53:28
 *  Author: nico
 *  Abstract: basics functionalities of the Poppy communication protocol
 */
#include "poppy_com.h"
#include "context.h"
#include "crc.h"

#include "HardwareSerial.h"
#include "UART.h"

context_t ctx;

// Startup and network configuration
void poppy_com_init(MSG_CB tx_cb,
                    MSG_CB rx_cb,
                    unsigned char id,
                    unsigned char type) {

    // Initialization for UART mode
    Serial.begin(1000000);  // 1M clock
    Serial.setTimeout(1);   // 1ms timeout

    // Save context
    // User side slave TX callback
    ctx.tx_cb = tx_cb;
    // User side slave RX callback
    ctx.rx_cb = rx_cb;

    // Module id
    ctx.id = id;
    // Module type
    ctx.type = type;

    // Status
    ctx.status = ((status_t) {false, false, false, false});

}

void poppy_com_write(unsigned char addr, msg_t *msg) {
    // Send write trame
    Serial.write(addr);           // Adress byte construct like in I2C protocol
    Serial.write(msg->reg);
    Serial.write(msg->size);
    Serial.write(msg->data,msg->size);
    Serial.write(crc(msg->data,msg->size));
 }
