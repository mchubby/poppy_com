#include "src/i2c_master.h"
#include HAL

// I2C Master mode

// Global variables
extern context_t ctx;

unsigned char set_extern_id(unsigned char addr, unsigned char newid) {
    if (i2cAddr(addr, TX)) {
        i2c_transmit(STOP);
        return 1;
    }
    if (i2cWrite(WRITE_ID)) {
        i2c_transmit(STOP);
        return 1;
    }
    if (i2cWrite(newid)) {
        i2c_transmit(STOP);
        return 1;
    }
    i2cWrite(crc(&newid, 1));
    i2c_transmit(STOP);
    return 0;
}

unsigned char get_extern_module_type(unsigned char addr,
                                     unsigned char *module_type) {
    if (i2cAddr(addr, TX)) {
        i2c_transmit(STOP);
        return 1;
    }
    if (i2cWrite(GET_MODULE_TYPE)) {
        i2c_transmit(STOP);
        return 1;
    }
    if (i2cAddr(addr, RX)) {
        i2c_transmit(STOP);
        return 1;
    }
    if (i2cRead(FALSE, module_type)) {
        i2c_transmit(STOP);
        return 1;
    }
    i2c_transmit(STOP);
    return 0;
}


 // // Reply with ID
 //    SET_ID,
 //    ping(unsigned char addr);
 //    // Reply with module_type number
 //    GET_MODULE_TYPE,
 //    // Reply with a status register
 //    GET_STATUS,
 //    // Reply with the actual firmware revision number
 //    GET_FIRM_REVISION,
