#include "i2c_master.h"
#include "crc.h"
#include <Wire.h>

// I2C Master mode

// Global variables
extern context_t ctx;

unsigned char set_extern_id(unsigned char addr, unsigned char newid) {
    Wire.beginTransmission(addr); // transmit to device #addr
    Wire.write(WRITE_ID);         // sends msg_type
    Wire.write(newid);            // sends data
    Wire.write(crc(&newid, 1));   // sends CRC
    Wire.endTransmission();       // stop transmitting
    return 0;
}

unsigned char get_extern_module_type(unsigned char addr,
                                     unsigned char *module_type) {
    Wire.beginTransmission(addr);     // transmit to device #addr
    Wire.write(GET_MODULE_TYPE);      // sends msg_type
    Wire.requestFrom((int)addr, 1);   // slave may send less than requested
    *module_type = Wire.read();       // receive a byte as character
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
