#TODO faire une entête avec licence et tout

# make all = Make software and program
# make clean = Clean out built project files.
# make program = Download the hex file to the device, using avrdude.  Please
#                customize the avrdude settings below first!
# make docs = compile with doxygen the code documentation

#-------------------------------------------------------------------------------
# Tools
#-------------------------------------------------------------------------------

# Set DEBUG variable for once if not coming from command line
ifndef DEBUG
DEBUG = 0
endif

# Tool suffix when cross-compiling
CROSS_COMPILE ?=

# Compilation tools
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
SIZE = $(CROSS_COMPILE)size
GDB = $(CROSS_COMPILE)gdb
NM = $(CROSS_COMPILE)nm

ROOT_PATH = ../..
HAL_PATH = $(ROOT_PATH)/hal/$(HAL_NAME)
DOC_PATH = $(ROOT_PATH)/../extra/Docs

ifeq ($(CROSS_COMPILE),arm-none-eabi-)
	# change this value if openocd isn't in the user/system PATH
	OPENOCD = openocd
	RESOURCES_OPENOCD_UPLOAD = $(HAL_PATH)/openocd_scripts/variant_upload.cfg
	RESOURCES_OPENOCD_START = $(HAL_PATH)/openocd_scripts/variant_debug_start.cfg
	RESOURCES_GDB = $(HAL_PATH)/debug_scripts/variant.gdb
	# RESOURCES_LINKER = $(HAL_PATH)/linker_scripts/gcc/variant_without_bootloader.ld
	RESOURCES_LINKER = $(HAL_PATH)/ASF/sam/utils/linker_scripts/samg/samg55j19/gcc/flash.ld

	INCLUDES += -I$(ROOT_PATH)/tools/CMSIS_API/Include
	INCLUDES += -I$(ROOT_PATH)/tools/CMSIS_Devices/ATMEL
endif

# Doxygen configuration file name
DOXYFILE = $(ROOT_PATH)/../extra/.Doxyfile

OBJ_PATH = $(HAL_PATH)/obj
OUTPUT_NAME = lib$(HAL_NAME)
OUTPUT_FILE_PATH = $(HAL_PATH)/$(OUTPUT_NAME).a

#|---------------------------------------------------------------------------------------|
#| Source files                                                                          |
#|---------------------------------------------------------------------------------------|
include ../sources.mk

#|---------------------------------------------------------------------------------------|
#| Extract file names and path                                                           |
#|---------------------------------------------------------------------------------------|
PROJ_ASRCS   = $(filter %.s,$(foreach file,$(SOURCES),$(file)))
PROJ_ASRCS  += $(filter %.S,$(foreach file,$(SOURCES),$(file)))
PROJ_CSRCS   = $(filter %.c,$(foreach file,$(SOURCES),$(file)))
PROJ_CPPSRCS = $(filter %.cpp,$(foreach file,$(SOURCES),$(file)))

#|---------------------------------------------------------------------------------------|
#| Set important path variables                                                          |
#|---------------------------------------------------------------------------------------|
VPATH    = $(foreach path,$(sort $(foreach file,$(SOURCES),$(dir $(file)))),$(path) :)
INC_PATH = $(INCLUDES)
LIB_PATH = -L$(dir $(RESOURCES_LINKER))

#|---------------------------------------------------------------------------------------|
#| Options for compiler binaries                                                         |
#|---------------------------------------------------------------------------------------|

COMMON_FLAGS = -g -O$(OPT) -funsigned-char -fpack-struct -fshort-enums
COMMON_FLAGS += -Wall -Wstrict-prototypes -Wa,-adhlns=$(<:.c=.lst) -D$(MCU)
COMMON_FLAGS += -DMAINCLOCK=$(MAINCLOCK) -DBOARD=$(BOARD) -Dscanf=iscanf
COMMON_FLAGS += -DARM_MATH_CM4=true -Dprintf=iprintf -DDONT_USE_CMSIS_INIT
COMMON_FLAGS += -Wall -Wchar-subscripts -Wcomment
COMMON_FLAGS += -Wmain -Wparentheses 
# COMMON_FLAGS += -Werror-implicit-function-declaration
COMMON_FLAGS += -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused
COMMON_FLAGS += -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef
COMMON_FLAGS += -Wshadow -Wpointer-arith -Wwrite-strings
COMMON_FLAGS += -Wsign-compare -Waggregate-return -Wmissing-declarations
COMMON_FLAGS += -Wmissing-format-attribute -Wno-deprecated-declarations
COMMON_FLAGS += -Wpacked -Wredundant-decls -Wlong-long
COMMON_FLAGS += -Wunreachable-code -Wcast-align
COMMON_FLAGS += -fdiagnostics-color=always $(INCLUDES)

ifeq ($(DEBUG),0)
COMMON_FLAGS += -Os -DDEBUG
else
COMMON_FLAGS += -ggdb3 -O0
COMMON_FLAGS += -Wformat=2
endif

ifeq ($(CROSS_COMPILE),avr-)
	COMMON_FLAGS += -mmcu=$(MCU)
	ASFLAGS = -mmcu=$(MCU)
endif
ifeq ($(CROSS_COMPILE),arm-none-eabi-)
	COMMON_FLAGS += -mthumb -mcpu=$(DEVICE_CORE) -mfpu=fpv4-sp-d16
	COMMON_FLAGS += --param max-inline-insns-single=500 -ffunction-sections -fdata-sections
	COMMON_FLAGS += -DDONT_USE_CMSIS_INIT
	# COMMON_FLAGS += -Wa,-adhlns="$(subst .o,.lst,$@)"
	COMMON_FLAGS += --param max-inline-insns-single=500
endif

CFLAGS += $(COMMON_FLAGS) -std=gnu99 -Wimplicit-int -Wbad-function-cast -Wmissing-prototypes -Wnested-externs

CPPFLAGS = $(COMMON_FLAGS) -std=gnu++11 -fno-rtti -fno-exceptions

# AFLAGS += -Wa,-adhlns=$(<:.S=.lst),-gstabs -I. -x assembler-with-cpp

# LDFLAGS = -Wl,-Map=$(HAL_NAME).map,--cref

#|---------------------------------------------------------------------------------------|
#| Define targets                                         Board                               |
#|---------------------------------------------------------------------------------------|
#AOBJS += $(patsubst %.S,%.o,$(PROJ_ASRCS))
AOBJS = $(patsubst %.s,%.o,$(addprefix $(OBJ_PATH)/, $(notdir $(PROJ_ASRCS))))
COBJS = $(patsubst %.c,%.o,$(addprefix $(OBJ_PATH)/, $(notdir $(PROJ_CSRCS))))
CPPOBJS = $(patsubst %.cpp,%.o,$(addprefix $(OBJ_PATH)/, $(notdir $(PROJ_CPPSRCS))))

.PHONY: all clean print_info packaging

all: $(OUTPUT_FILE_PATH)

print_info:
	@echo DEFAULT_GOAL ---------------------------------------------------------------------------------
	@echo $(.DEFAULT_GOAL)
	@echo VPATH ---------------------------------------------------------------------------------
	@echo $(VPATH)
	@echo SOURCES -------------------------------------------------------------------------------
	@echo $(SOURCES)
#	@echo PROJ_ASRCS ----------------------------------------------------------------------------
#	@echo $(PROJ_ASRCS)
#	@echo AOBJS ---------------------------------------------------------------------------------
#	@echo $(AOBJS)
	@echo PROJ_CSRCS ----------------------------------------------------------------------------
	@echo $(PROJ_CSRCS)
	@echo COBJS ---------------------------------------------------------------------------------
	@echo $(COBJS)
	@echo PROJ_CPPSRCS --------------------------------------------------------------------------
	@echo $(PROJ_CPPSRCS)
	@echo CPPOBJS -------------------------------------------------------------------------------
	@echo $(CPPOBJS)
	@echo ---------------------------------------------------------------------------------------
	@echo $(CURDIR)
	@echo $(OUTPUT_FILE_PATH)
	@echo ---------------------------------------------------------------------------------------

$(OUTPUT_FILE_PATH): $(OBJ_PATH) ../rules.mk ../sources.mk $(HAL_PATH)/Makefile $(AOBJS) $(COBJS) $(CPPOBJS)
	$(AR) -rv $(OUTPUT_FILE_PATH) $(AOBJS)
	$(AR) -rv $(OUTPUT_FILE_PATH) $(COBJS)
	$(AR) -rv $(OUTPUT_FILE_PATH) $(CPPOBJS)
	$(NM) $(OUTPUT_FILE_PATH) > $(HAL_PATH)/$(OUTPUT_NAME)_symbols.txt

#|---------------------------------------------------------------------------------------|
#| Compile or assemble                                                                   |
#|---------------------------------------------------------------------------------------|
$(AOBJS): $(OBJ_PATH)/%.o: %.s
	@echo +++ Assembling [$(notdir $<)]
	@$(AS) $(AFLAGS) $< -o $@

$(AOBJS): $(OBJ_PATH)/%.o: %.S
	@echo +++ Assembling [$(notdir $<)]
	@$(AS) $(AFLAGS) $< -o $@

$(COBJS): $(OBJ_PATH)/%.o: %.c
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CFLAGS) -c $< -o $@

$(CPPOBJS): $(OBJ_PATH)/%.o: %.cpp
	@echo +++ Compiling [$(notdir $<)]
	@$(CC) $(CPPFLAGS) -c $< -o $@

#|---------------------------------------------------------------------------------------|
#| Output folder                                                                         |
#|---------------------------------------------------------------------------------------|
$(OBJ_PATH):
	@echo +++ Creation of [$@]
	@-mkdir $(OBJ_PATH)

#|---------------------------------------------------------------------------------------|
#| Cleanup                                                                               |
#|---------------------------------------------------------------------------------------|
clean:
	-rm -f $(OBJ_PATH)/* $(OBJ_PATH)/*.*
	-rmdir $(OBJ_PATH)
	-rm -f $(OUTPUT_FILE_PATH)
	-rm -f $(HAL_PATH)/$(OUTPUT_NAME)_symbols.txt
	-rm -rf $(DOC_PATH)

#|---------------------------------------------------------------------------------------|
#| Dependencies                                                                          |
#|---------------------------------------------------------------------------------------|
$(OBJ_PATH)/%.d: %.s $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(AFLAGS) -MM -c $< -MT $(basename $@).o -o $@

$(OBJ_PATH)/%.d: %.S $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(AFLAGS) -MM -c $< -MT $(basename $@).o -o $@

$(OBJ_PATH)/%.d: %.c $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(CFLAGS) -MM -c $< -MT $(basename $@).o -o $@

$(OBJ_PATH)/%.d: %.cpp $(OBJ_PATH)
	@echo +++ Dependencies of [$(notdir $<)]
	@$(CC) $(CPPFLAGS) -MM -c $< -MT $(basename $@).o -o $@

#|---------------------------------------------------------------------------------------|
#| Include dependencies, if existing                                                     |
#| Little trick to avoid dependencies build for some rules when useless                  |
#| CAUTION: this won't work as expected with 'make clean all'                            |
#|---------------------------------------------------------------------------------------|
DEP_EXCLUDE_RULES := clean print_info
ifeq (,$(findstring $(MAKECMDGOALS), $(DEP_EXCLUDE_RULES)))
-include $(AOBJS:%.o=%.d)
-include $(COBJS:%.o=%.d)
-include $(CPPOBJS:%.o=%.d)
endif


#|---------------------------------------------------------------------------------------|
#| Module packaging for Arduino IDE Board Manager                                        |
#|---------------------------------------------------------------------------------------|
packaging: $(OUTPUT_FILE_PATH)

docs:
	( cat $(DOXYFILE) ; echo "OUTPUT_DIRECTORY = $(DOC_PATH)" ; echo "INPUT = $(DOC_SOURCES)" ) | doxygen -
#	doxygen $(DOXYFILE)

%.d:
