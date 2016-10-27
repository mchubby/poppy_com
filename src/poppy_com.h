/**
 * \file poppyNetwork.h
 * \brief Poppy communication main include file.
 * \author Nicolas Rabault
 * \version 0.1
 * \date 22 Avril 2015
 *
 * Include this file to use the poppy communication protocole.
 *
 */

#ifndef poppy_com_H_
#define poppy_com_H_

/**
 * \enum msg_dir_t
 * \brief Message direction enum.
 *
 * This structure is used to get the message direction but it seems to be useles
 * because we have defferent interrupt for each msg_dir case.
 */
typedef enum {
    TX,   /*!< Slave transmiter mode. */
    RX,   /*!< Slave receiver mode. */
    RXGC, /*!< Slave receiver g�n�ral call mode. */
    END   /*!< Slave receiver stop. */
}msg_dir_t;

/**
 * \struct msg_t
 * \brief Message structure.
 *
 * This structure is used to receive or send messages between modules in slave
 * and master mode.
 * please refer to ?? documentation
 */
typedef struct {
    unsigned char reg;        /*!< Message register. */
    unsigned char size;       /*!< Message size. */
    unsigned char data[512];  /*!< Data (512 bytes max). */
}msg_t;

typedef void (*MSG_CB) (msg_t *msg);

/**
 * \fn void poppy_com_init(TX_CB tx_cb, RX_CB rx_cb, RX_CB rxgc_cb)
 * \brief Initialisation of the Poppy communication lib.
 *
 * \param tx_cb function pointer into the tx callback.
 * \param rx_cb function pointer into the rx callback.
 * \param rxgc_cb function pointer into the rx general call callback.
 *
 */
void poppy_com_init(MSG_CB tx_cb,
                    MSG_CB rx_cb,
                    unsigned char id,
                    unsigned char type);
/**
 * \fn unsigned char poppy_com_write(unsigned char addr, msg_t *msg)
 * \brief Master mode write function.
 *
 * \param addr Address of the slave.
 * \param msg Message to send to the slave.
 */
void poppy_com_write(unsigned char addr, msg_t *msg);

#endif /* poppy_com_H_ */
