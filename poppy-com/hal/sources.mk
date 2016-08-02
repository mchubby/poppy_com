LIB_SRC_PATH = $(ROOT_PATH)/src
LIB_INC_PATH = $(ROOT_PATH)/inc

SRC_DISCARDED=

SRC_SYS =                                                           \
(ROOT_PATH)/tools/CMSIS_Devices/ATMEL/samg55/source/system_samg55.c \
(ROOT_PATH)/tools/CMSIS_Devices/ATMEL/samg55/source/as_gcc/startup_samg55.c
INCLUDES += -I$(ROOT_PATH)/tools/CMSIS_Devices/ATMEL/samg55/include

SRC_LIB += \
$(LIB_SRC_PATH)/sys_msg.c   			\
$(LIB_SRC_PATH)/reception.c    			\
$(LIB_SRC_PATH)/target.c    			\
$(LIB_SRC_PATH)/poppyNetwork.c
INCLUDES += -I$(LIB_INC_PATH) -I$(LIB_SRC_PATH) -I$(ROOT_PATH)

SRC_HAL += \
$(HAL_PATH)/hal.c
INCLUDES += -I$(HAL_PATH)

SOURCES=$(SRC_LIB) $(SRC_HAL) $(SRC_SYS)

DOC_SOURCES=$(ROOT_PATH)/../ $(ROOT_PATH)/../extra/doc $(SOURCES)
