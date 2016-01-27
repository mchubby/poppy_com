#include "i2c_slave.h"
#include "crc.h"
#include <Wire.h>

// Global variables
extern context_t ctx;
static unsigned char *data_to_send;
static unsigned char msg_size = 0;

/*
 * idle transmit function is called when we are ready to receive or send a new message.
 */
void transmition() {
    /*
     * At this point we should have something ready to send.
     */
    if (msg_size) {
        /*
         *This case is dedicated to protocol messages
         */
        msg_size--;
         Wire.write(*data_to_send++);
    } else {
        ctx.tx_cb(&ctx.msg);
        for (unsigned char data_count=0; data_count<ctx.msg.size; data_count++)
            Wire.write(ctx.msg.data[data_count]);
    }
}

void reception(int size) {
    unsigned char data_count;
    //catch register
    ctx.msg.reg = Wire.read();
    switch (ctx.msg.reg) {
        case GET_ID:
            // Reply with ID
            msg_size = 1;
            data_to_send = &ctx.id;
        break;
        case WRITE_ID:
            // Get and save a new given ID
            ctx.id = Wire.read();
        break;
        case GET_MODULE_TYPE:
            // Reply with module_type number
            msg_size = 1;
            data_to_send = &ctx.type;
        break;
        case GET_STATUS:
            // Reply with a status register
            msg_size = 1;
            data_to_send = (unsigned char*)&ctx.status;
            // TODO(NR) ca devrais reset le status...
        break;
        case GET_FIRM_REVISION:
            // Reply with the actual firmware revision number
            // TODO(NR)
        break;
        default:
    // catch data size
            ctx.msg.size = Wire.read();
    // catch data table
            for (data_count=0; data_count<ctx.msg.size; data_count++)
                ctx.msg.data[data_count] = Wire.read();
    // catch CRC
            if (Wire.read() == crc(&ctx.msg.data[0], ctx.msg.size))
                msg_complete();
            else
                ctx.status.rx_error = true;
        break;
    }
}

void msg_complete() {
    switch (ctx.msg.reg) {
        case WRITE_ID:
            // Get and save a new given ID
            Wire.begin(ctx.id);
        break;
        case GET_ID:
        case GET_MODULE_TYPE:
        case GET_STATUS:
        case GET_FIRM_REVISION:
            // ERROR
            ctx.status.rx_error = true;
        break;
        default:
            ctx.rx_cb(&ctx.msg);
        break;
    }
}
