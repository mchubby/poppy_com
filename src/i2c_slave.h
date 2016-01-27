#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

#include "context.h"

// Callbacks
void transmition(void);
void reception(int size);

void msg_complete(void);

#endif /* I2C_SLAVE_H_ */
