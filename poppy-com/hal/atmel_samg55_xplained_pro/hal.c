#include "hal.h"
#include "asf.h"
#include "stdio_serial.h"
#include "conf_board.h"
#include "conf_clock.h"
#include "uart.h"
#include "time.h"
#include "button.h"
#include "rs485.h"

#include "log.h"
#define LOG_TAG        "Main"
#define LOG_LEVEL     LOG_LEVEL_INFO



#ifdef __cplusplus
extern "C" {
#endif


// Global variables
context_t ctx;

/**
 * \fn void hal_init(void)
 * \brief hardware configuration (clock, communication, DMA...)
 */
void hal_init(void) {
    sysclk_init();
    board_init();

    uart_stdio_init(CONSOLE_UART, 115200);

    TEST_LOG_INFO(){
        printf("\n\r\tFirmware Poppy-com built on %s at %s\n\r", __DATE__, __TIME__ );
    }

    if (SysTick_Config(sysclk_get_cpu_hz() / 1000)) {
        LOG_ERROR("systic config failed");
        while (1);
    }

    rs485_init();
}

/**
 * \fn unsigned char hal_transmit(unsigned char* data)
 * \brief write a data byte
 *
 * \param data *data bytes to send
 * \param size size of data to send in byte
 *
 * \return error
 */
unsigned char hal_transmit(unsigned char* data, unsigned short size) {
    if /*hardware ready*/ {
        // Put data into a DMA => serial interface or do it with a for
       for (unsigned short i = 0; i < size; i++)
       {
            rs485_set_dir(RS485_BOTH);
            delay_ms(1); // TODO wait for event when it's done writing
            rs485_write(data++);
            delay_ms(1); // TODO wait for event when it's done writing
       }
    } else {
        ctx.status.master_write = TRUE;
        return 1;
    }
    return 0;
}

/**
 * \fn void id_update(unsigned short id)
 * \brief update the slave address
 *
 * \param id new address
 *
 */
void id_update(unsigned short id) {
    ctx.id = id;
    /*address register*/ = (ctx.id << 1);
    // Write your ID on EEprom
}


/**
 * \fn void alias_update(unsigned char id[16])
 * \brief update the slave address
 *
 * \param alias new address
 *
 */
// void alias_update(unsigned char alias[16]) {
//     for (unsigned char i=0; i < 16; i++)
//         ctx.alias[i] = alias[i];
//     // Write your alias on EEprom
// }
