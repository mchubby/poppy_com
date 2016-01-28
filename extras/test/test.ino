#include "poppy_com.h"
#include "i2c_master.h"
#include <Wire.h> // Ne devrais pas apparaitre!!!

#define FIRST_ADDR 0x02
#define SECOND_ADDR 0x03

// #define FIRST
#define REF_VAL 170

/**
 * \enum msg_dir_t
 * \brief Module specific register enumerator.
 *
 * This structure is used to list all the specific module register.
 */
typedef enum {
    LED_REGISTER
}module_register_t;
#ifdef FIRST
    char client_addr = SECOND_ADDR;
#else
    char client_addr = FIRST_ADDR;
#endif


void rx_cb(msg_t *msg) {
    digitalWrite(13, msg->data[0]);
}

void tx_cb(msg_t *msg) {
    msg->data[0] = REF_VAL;
}

void setup() {
    poppy_com_init(tx_cb, rx_cb);
    bitSet(TWAR, TWGCE); // ugly hack to enable General call (thanks to arduino)
    delay(100);
    set_extern_id(0x00, client_addr);
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    msg_t msg;
    msg.reg = LED_REGISTER;
    msg.size = 1;
    delay(500);

    // Write "led on"
    msg.data[0] = HIGH;
    poppy_com_write(client_addr, &msg);
    delay(500);

    // Write "led off" and read result
    msg.data[0] = LOW;
    poppy_com_read(client_addr, &msg, 1);
    if (msg.data[0] == REF_VAL)
        Serial.print("Ok");
    else
        Serial.print("Ko!");
}
