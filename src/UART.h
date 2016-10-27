#ifndef UART_H_
#define UART_H_

#include "context.h"

extern volatile unsigned char communicationState;

void serialEvent();

#endif //UART_H_
