# WinAVR Sample makefile written by Eric B. Weddington, Jörg Wunsch, et al.
# Modified (bringing often-changed options to the top) by Elliot Williams

# make all = Make software and program
# make clean = Clean out built project files.
# make program = Download the hex file to the device, using avrdude.  Please
#                customize the avrdude settings below first!
# make docs = compile with doxygen the code documentation

# Doxygen configuration file name
DOXYFILE = .Doxyfile

VPATH = extras/test/

# Microcontroller Type
MCU = stub

# Target file name (without extension).
TARGET = test

# Programming hardware: type avrdude -c ?
# to get a full listing.
# AVRDUDE_PROGRAMMER = dapa
# AVRDUDE_PROGRAMMER = usbtiny
AVRDUDE_PROGRAMMER = dragon_isp
# AVRDUDE_PROGRAMMER = dt006

AVRDUDE_PORT = usb # not really needed for usb
#AVRDUDE_PORT = /dev/parport0           # linux
# AVRDUDE_PORT = lpt1              # windows

############# Don't need to change below here for most purposes  (Elliot)

# Optimization level, can be [0, 1, 2, 3, s]. 0 turns off optimization.
# (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

# Output format. (can be srec, ihex, binary)
FORMAT = ihex

# List C source files here. (C dependencies are automatically generated.)
SRC = $(TARGET).c

# If there is more than one source file, append them above, or modify and
# uncomment the following:
# poppy_com source files
SRC += \
src/i2c_master.c \
src/i2c_slave.c \
src/poppyNetwork.c \
extras/hal/$(MCU)/hal.c
# Application source files
SRC += \
extras/test/src/test_mngmnt.c

# You can also wrap lines by appending a backslash to the end of the line:
#SRC += baz.c \
#xyzzy.c



# List Assembler source files here.
# Make them always end in a capital .S.  Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC =


# List any extra directories to look for include files here.
#     Each directory must be seperated by a space.
EXTRAINCDIRS = \
src/ \
extras/hal/$(MCU)/ \
extras/test/ \
extras/test/inc \
extras/test/src



# Optional compiler flags.
#  -g:        generate debugging information (for GDB, or for COFF conversion)
#  -O*:       optimization level
#  -f...:     tuning, see gcc manual and avr-libc documentation
#  -Wall...:  warning level
#  -Wa,...:   tell GCC to pass this to the assembler.
#    -ahlms:  create assembler listing
CFLAGS = -O$(OPT) \
-DMCU=$(MCU) \
-Wall \
-coverage \
$(patsubst %,-I%,$(EXTRAINCDIRS))


# Set a "language standard" compiler flag.
#   Unremark just one line below to set the language standard to use.
#   gnu99 = C99 + GNU extensions. See GCC manual for more information.
#CFLAGS += -std=c89
#CFLAGS += -std=gnu89
#CFLAGS += -std=c99
CFLAGS += -std=gnu99



# Optional assembler flags.
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -ahlms:    create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
ASFLAGS = -Wa,-gstabs



# Optional linker flags.
#  -Wl,...:   tell GCC to pass this to linker.
#  -Map:      create map file
#  --cref:    add cross reference to  map file
LDFLAGS =



# Additional libraries

# Minimalistic printf version
#LDFLAGS += -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires -lm below)
#LDFLAGS += -Wl,-u,vfprintf -lprintf_flt

# -lm = math library
# LDFLAGS += -lm


# Programming support using avrdude. Settings and variables.


AVRDUDE_WRITE_FLASH = -U flash:w:$(TARGET).hex
#AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(TARGET).eep

AVRDUDE_FLAGS = -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)

# Uncomment the following if you want avrdude's erase cycle counter.
# Note that this counter needs to be initialized first using -Yn,
# see avrdude manual.
#AVRDUDE_ERASE += -y

# Uncomment the following if you do /not/ wish a verification to be
# performed after programming the device.
#AVRDUDE_FLAGS += -V

# Increase verbosity level.  Please use this when submitting bug
# reports about avrdude. See <http://savannah.nongnu.org/projects/avrdude>
# to submit bug reports.
#AVRDUDE_FLAGS += -v -v

#Run while cable attached or don't
AVRDUDE_FLAGS += -E reset #keep chip disabled while cable attached
#AVRDUDE_FLAGS += -E noreset

# AVRDUDE_WRITE_FLASH += -U lfuse:w:0xFF:m #run with 8 Mhz ext Crystal Osc +65ms

#AVRDUDE_WRITE_FLASH += -U lfuse:w:0x04:m #run with 8 Mhz clock

#AVRDUDE_WRITE_FLASH += -U lfuse:w:0x21:m #run with 1 Mhz clock #default clock mode

#AVRDUDE_WRITE_FLASH += -U lfuse:w:0x01:m #run with 1 Mhz clock no start up time

# ---------------------------------------------------------------------------

# Define directories, if needed.
# DIRAVR = c:/winavr
# DIRAVRBIN = $(DIRAVR)/bin
# DIRAVRUTILS = $(DIRAVR)/utils/bin
# DIRINC = .
# DIRLIB = $(DIRAVR)/avr/lib


# Define programs and commands.
SHELL = sh

CC = gcc

OBJCOPY = objcopy
OBJDUMP = objdump
SIZE = size


# Programming support using avrdude.
AVRDUDE = avrdude


REMOVE = rm -f
COPY = cp

HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET).hex
ELFSIZE = $(SIZE) -A $(TARGET).elf



# Define Messages
# English
MSG_ERRORS_NONE = "\033[33;32mErrors: none\033[33;0m"
MSG_BEGIN = "\033[33;33m-------- begin --------\033[33;0m"
MSG_END = "\033[33;33m--------  end  --------\033[33;0m"
MSG_SIZE_BEFORE = "\033[33;34mSize before:"
MSG_SIZE_AFTER = "\033[33;35mSize after:"
MSG_COFF = "\033[33;36mConverting to AVR COFF:\033[33;0m"
MSG_EXTENDED_COFF = "\033[33;36mConverting to AVR Extended COFF:\033[33;0m"
MSG_FLASH = "\033[33;36mCreating load file for Flash:\033[33;0m"
MSG_EEPROM = "\033[33;36mCreating load file for EEPROM:\033[33;0m"
MSG_EXTENDED_LISTING = "\033[33;36mCreating Extended Listing:\033[33;0m"
MSG_SYMBOL_TABLE = "\033[33;36mCreating Symbol Table:\033[33;0m"
MSG_LINKING = "\033[33;36mLinking:\033[33;0m"
MSG_COMPILING = "\033[33;36mCompiling:\033[33;0m"
MSG_ASSEMBLING = "\033[33;36mAssembling:\033[33;0m"
MSG_CLEANING = "\033[33;36mCleaning project:\033[33;0m"




# Define all object files.
OBJ = $(SRC:.c=.o) $(ASRC:.S=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -I. $(CFLAGS)
ALL_ASFLAGS = -I. -x assembler-with-cpp $(ASFLAGS)



# Default target: make program!
all: begin gccversion $(TARGET).eep \
	 finished end
#   $(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)

# Eye candy.
# AVR Studio 3.x does not check make's exit code but relies on
# the following magic strings to be generated by the compile job.
begin:
	@echo
	@echo $(MSG_BEGIN)

finished:
	@echo $(MSG_ERRORS_NONE)

end:
	@echo $(MSG_END)
	@echo

# Display size of file.
sizebefore:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(ELFSIZE); echo; fi

sizeafter:
	@if [ -f $(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(ELFSIZE); echo; fi



# Display compiler version information.
gccversion :
	@$(CC) --version




# Convert ELF to COFF for use in debugging / simulating in
# AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
	--change-section-address .data-0x800000 \
	--change-section-address .bss-0x800000 \
	--change-section-address .noinit-0x800000 \
	--change-section-address .eeprom-0x810000


coff: $(TARGET).elf
	@echo
	@echo $(MSG_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-avr $< $(TARGET).cof


extcoff: $(TARGET).elf
	@echo
	@echo $(MSG_EXTENDED_COFF) $(TARGET).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(TARGET).cof




# Program the device.
program: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM)




# Create final output files (.hex, .eep) from ELF output file.

%.eep: %.elf
	@echo

# Link: create ELF output file from object files.
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(OBJ)
%.elf: $(OBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(OBJ) --output $@ $(LDFLAGS)


# Compile: create object files from C source files.
%.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(ALL_CFLAGS) $< -o $@


# Compile: create assembler files from C source files.
%.s : %.c
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
%.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@






# Target: clean project.
clean: begin clean_list finished end

clean_list :
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).eep
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).cof
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).obj
	$(REMOVE) $(TARGET).a90
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lnk
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(OBJ)
	$(REMOVE) $(LST)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) $(SRC:.c=.d)
	$(REMOVE) $(SRC:.c=.gc*)
	$(REMOVE) *~
	# $(REMOVE) ../test.*

# Automatically generate C source code dependencies.
# (Code originally taken from the GNU make user manual and modified
# (See README.txt Credits).)
#
# Note that this will work with sh (bash) and sed that is shipped with WinAVR
# (see the SHELL variable defined above).
# This may not work with other shells or other seds.
#
%.d: %.c
	set -e; $(CC) -MM $(ALL_CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@


# Remove the '-' if you want to see the dependency files generated.
-include $(SRC:.c=.d)



# Listing of phony targets.
.PHONY : all begin finish end sizebefore sizeafter gccversion coff extcoff \
	clean clean_list program

docs:
	doxygen $(DOXYFILE)
