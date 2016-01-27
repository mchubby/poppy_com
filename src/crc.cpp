#include "crc.h"

unsigned char crc(unsigned char* data, unsigned char size) {
    unsigned char x;
    unsigned int crc = 0xFFFF;

    while (size--) {
        x = crc >> 8 ^ *data++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((unsigned int)(x << 12))
                         ^ ((unsigned int)(x <<5))
                         ^ ((unsigned int)x);
    }
    return (unsigned char)crc;
}
