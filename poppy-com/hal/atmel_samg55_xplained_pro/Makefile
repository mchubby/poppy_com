#TODO faire une entête avec licence et tout

SHELL := /bin/sh

.SUFFIXES: .d .o .c .h .cpp .hpp .s .S

include mcu.mk

BASE_PATH = ../../hal/$(HAL_NAME)

# ASF includes
ASF_PATH = $(BASE_PATH)/ASF \
$(BASE_PATH)/ASF/common                                           \
$(BASE_PATH)/ASF/common/boards                                    \
$(BASE_PATH)/ASF/common/services                                  \
$(BASE_PATH)/ASF/common/services/clock                            \
$(BASE_PATH)/ASF/common/services/clock/samg                       \
$(BASE_PATH)/ASF/common/services/ioport                           \
$(BASE_PATH)/ASF/common/services/ioport/sam                       \
$(BASE_PATH)/ASF/common/services/serial                           \
$(BASE_PATH)/ASF/common/services/serial/sam_uart                  \
$(BASE_PATH)/ASF/common/services/sleepmgr                         \
$(BASE_PATH)/ASF/common/services/sleepmgr/sam                     \
$(BASE_PATH)/ASF/common/utils                                     \
$(BASE_PATH)/ASF/common/utils/interrupt                           \
$(BASE_PATH)/ASF/common/utils/stdio                               \
$(BASE_PATH)/ASF/common/utils/stdio/stdio_serial                  \
$(BASE_PATH)/ASF/sam                                              \
$(BASE_PATH)/ASF/sam/boards                                       \
$(BASE_PATH)/ASF/sam/boards/samg55_xplained_pro                   \
$(BASE_PATH)/ASF/sam/drivers                                      \
$(BASE_PATH)/ASF/sam/drivers/efc                                  \
$(BASE_PATH)/ASF/sam/drivers/flexcom                              \
$(BASE_PATH)/ASF/sam/drivers/pio                                  \
$(BASE_PATH)/ASF/sam/drivers/pmc                                  \
$(BASE_PATH)/ASF/sam/drivers/supc                                 \
$(BASE_PATH)/ASF/sam/drivers/tc                                   \
$(BASE_PATH)/ASF/sam/drivers/usart                                \
$(BASE_PATH)/ASF/sam/utils                                        \
$(BASE_PATH)/ASF/sam/utils/cmsis                                  \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg                             \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55                      \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/include              \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/include/component    \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/include/instance     \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/include/pio          \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/source               \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/source/templates     \
$(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/source/templates/gcc \
$(BASE_PATH)/ASF/sam/utils/fpu                                    \
$(BASE_PATH)/ASF/sam/utils/header_files                           \
$(BASE_PATH)/ASF/sam/utils/linker_scripts                         \
$(BASE_PATH)/ASF/sam/utils/linker_scripts/samg                    \
$(BASE_PATH)/ASF/sam/utils/linker_scripts/samg/samg55j19          \
$(BASE_PATH)/ASF/sam/utils/linker_scripts/samg/samg55j19/gcc      \
$(BASE_PATH)/ASF/sam/utils/make                                   \
$(BASE_PATH)/ASF/sam/utils/preprocessor                           \
$(BASE_PATH)/ASF/sam/utils/syscalls                               \
$(BASE_PATH)/ASF/sam/utils/syscalls/gcc                           \
$(BASE_PATH)/ASF/thirdparty                                       \
$(BASE_PATH)/ASF/thirdparty/CMSIS                                 \
$(BASE_PATH)/ASF/thirdparty/CMSIS/Include                         \
$(BASE_PATH)/ASF/thirdparty/CMSIS/Lib                             \
$(BASE_PATH)/ASF/thirdparty/CMSIS/Lib/GCC

INCLUDES = $(ASF_PATH:%=-I%)

ASF_SRC = \
$(BASE_PATH)/ASF/common/services/clock/samg/sysclk.c                               \
$(BASE_PATH)/ASF/common/services/serial/usart_serial.c                             \
$(BASE_PATH)/ASF/common/services/sleepmgr/sam/sleepmgr.c                           \
$(BASE_PATH)/ASF/common/utils/interrupt/interrupt_sam_nvic.c                       \
$(BASE_PATH)/ASF/common/utils/stdio/read.c                                         \
$(BASE_PATH)/ASF/common/utils/stdio/write.c                                        \
$(BASE_PATH)/ASF/sam/boards/samg55_xplained_pro/board_init.c                       \
$(BASE_PATH)/ASF/sam/drivers/efc/efc.c                                             \
$(BASE_PATH)/ASF/sam/drivers/flexcom/flexcom.c                                     \
$(BASE_PATH)/ASF/sam/drivers/pio/pio.c                                             \
$(BASE_PATH)/ASF/sam/drivers/pio/pio_handler.c                                     \
$(BASE_PATH)/ASF/sam/drivers/pmc/pmc.c                                             \
$(BASE_PATH)/ASF/sam/drivers/pmc/sleep.c                                           \
$(BASE_PATH)/ASF/sam/drivers/supc/supc.c                                           \
$(BASE_PATH)/ASF/sam/drivers/tc/tc.c                                               \
$(BASE_PATH)/ASF/sam/drivers/usart/usart.c                                         \

# $(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/source/templates/gcc/startup_samg55.c \
# $(BASE_PATH)/ASF/sam/utils/cmsis/samg/samg55/source/templates/system_samg55.c      \

# HAL sources includes
LIBS_PATH = $(BASE_PATH)/libs
BUTTON_PATH = $(LIBS_PATH)/button
INTERFACES_PATH = $(LIBS_PATH)/interfaces
LED_PATH = $(LIBS_PATH)/led
SERIAL_PATH = $(LIBS_PATH)/serial
SYSTEM_PATH = $(LIBS_PATH)/system
CONFIG_PATH = $(BASE_PATH)/config

SRC_HAL =                            \
$(BASE_PATH)/libs/button/button.c    \
$(BASE_PATH)/libs/interfaces/ptp.c   \
$(BASE_PATH)/libs/interfaces/rs485.c \
$(BASE_PATH)/libs/led/led.c          \
$(BASE_PATH)/libs/serial/uart.c      \
$(BASE_PATH)/libs/system/debug.c     \
$(BASE_PATH)/libs/system/system.c    \
$(BASE_PATH)/libs/system/time.c      \
$(ASF_SRC)

INCLUDES +=          \
-I$(LIBS_PATH)       \
-I$(BUTTON_PATH)     \
-I$(INTERFACES_PATH) \
-I$(LED_PATH)        \
-I$(SERIAL_PATH)     \
-I$(SYSTEM_PATH)     \
-I$(CONFIG_PATH)

include ../rules.mk
