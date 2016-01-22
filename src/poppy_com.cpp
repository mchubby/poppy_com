/*
 * poppyNetwork.c
 *
 * Created: 16/02/2015 11:53:28
 *  Author: nico
 *  Abstract: basics functionalities of the Poppy communication protocol
 */
#include "poppy_com.h"
#include "i2c_master.h"
#include "i2c_slave.h"
#include "context.h"
#include "crc.h"
#include <Wire.h>

#include <Arduino.h>

context_t ctx;

void poppy_com_ChangeHardwareMode(hardwareMode_t newMode) {
    ctx.hardMode = newMode;
}

// Startup and network configuration
void poppy_com_init(MSG_CB tx_cb,
                    MSG_CB rx_cb) {

    // Initialization for UART mode
    Serial.begin(1000000);  // 1M clock
    Serial.setTimeout(1);   // 1ms timeout

    // Save context
    // User side slave TX callback
    ctx.tx_cb = tx_cb;
    // User side slave RX callback
    ctx.rx_cb = rx_cb;

    // Module id
    ctx.id = DEFAULTID;
    // Module type
    ctx.type = MODULETYPE;
    // Module communication type
    ctx.hardMode = DEFAULTHARDWAREMODE;

    // Status
    ctx.status = ((status_t) {false, false, false, false});

    Wire.begin(DEFAULTID);
    // Wire.setclock(SCLFREQ); // No setclock function on my lib version...
    Wire.onReceive(reception);
    Wire.onRequest(transmition);
}

void poppy_com_read(unsigned char addr, msg_t *msg,
                    unsigned char reply_size) {
    if(ctx.hardMode == I2C) {
        unsigned char i = 0;
        // Write to address
        Wire.beginTransmission(addr);
        // Register
        Wire.write(msg->reg + PROTOCOL_REGISTER_NB);
        // Size
        Wire.write(msg->size);
        // Data
        for (i = 0; i < msg->size; i++)
            Wire.write(msg->data[i]);
        // CRC
        Wire.write(crc(&msg->data[0], msg->size));

        // Read to address
        Wire.requestFrom(addr, reply_size);
        msg->size = reply_size;
        // Save data
        for (i = 0; i < msg->size; i++)
            msg->data[i] = Wire.read();
        // Stop
        Wire.endTransmission();
	}
	 else   // UART mode
    {
        // Send request trame
        Serial.write((addr<<1)|0x01);           // Adress byte construct like in I2C protocol
        Serial.write(msg->reg);
        Serial.write(msg->size);
        Serial.write(msg->data,msg->size);

        // Receive answer
        Serial.write((addr<<1)|0x00);
        msg->size = Serial.readBytes(msg->data,reply_size);
    }
}

void poppy_com_write(unsigned char addr, msg_t *msg) {
    if(ctx.hardMode == I2C)
    {
        // Write to address
        Wire.beginTransmission(addr);
        // Register
        Wire.write(msg->reg + PROTOCOL_REGISTER_NB);
        // Size
        Wire.write(msg->size);
        // Data
        for (unsigned char i = 0; i < msg->size; i++)
            Wire.write(msg->data[i]);
        // CRC
        Wire.write(crc(&msg->data[0], msg->size));
        // Stop
        Wire.endTransmission();
    }
    else
    {
        // Send write trame
        Serial.write((addr<<1)|0x01);           // Adress byte construct like in I2C protocol
        Serial.write(msg->reg);
        Serial.write(msg->size);
        Serial.write(msg->data,msg->size);
        Serial.write(crc(msg->data,msg->size));
     }
 }
