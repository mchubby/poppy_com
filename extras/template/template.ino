#include "poppy_com.h"


/**
 * \enum msg_dir_t
 * \brief Module specific register enumerator.
 *
 * This structure is used to list all the specific module register.
 */
typedef enum {
    REGISTER_1,
    REGISTER_2
}module_register_t;

void rx_cb(msg_t *msg) {
    /*
     * Add your RX code here.
     */
}

void tx_cb(msg_t *msg) {
    /*
     * Add your TX code here.
     */
}

void setup() {
  // put your setup code here, to run once:

  poppy_com_init(tx_cb, rx_cb);

}

void loop() {
  // put your main code here, to run repeatedly:

}
