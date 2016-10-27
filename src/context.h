#ifndef CONTEXT_H_
#define CONTEXT_H_

#include "config.h"
#include "poppy_com.h"

typedef struct {
  unsigned char rx_error : 1;
  unsigned char master_write : 1;
  unsigned char master_read : 1;
  unsigned char unexpected_state : 1;
  unsigned char warning : 1;
} status_t;

/*
 * All applicativ side message should have a structure like :
 * ADDR - REGISTER - SIZE - DATA[512] - CHECKSUM
 */
typedef enum {
    GET_ID,              /*!< Reply with ID. */
    WRITE_ID,            /*!< Get and save a new given ID. */
    GET_MODULE_TYPE,     /*!< Reply with module_type number. */
    GET_STATUS,          /*!< Reply with a status register. */
    GET_FIRM_REVISION,   /*!< Reply with the actual firmware revision number. */
    GET_COM_REVISION,    /*!< Reply with the actual communication protocole version (1 default). */
    PROTOCOL_REGISTER_NB /*!< This is the minim  l register value available for applicative side. */
}register_t;

typedef struct {
    // Callback pointers
        MSG_CB tx_cb;        /*!< User side slave TX callback. */
        MSG_CB rx_cb;        /*!< User side slave RX callback. */

    // Module infomations
        unsigned char id;   /*!< Module ID. */
        unsigned char type; /*!< Module type. */

    // Variables
        status_t status;          /*!< Status. */
        msg_t msg;                /*!< Message. */
    }context_t;

extern context_t ctx;

#endif /* CONTEXT_H_ */
