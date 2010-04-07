###############################################################################
# Makefile for the project stim_wilma
###############################################################################

## General Flags
PROJECT = stim_wilma
MCU = atmega324p
TARGET = stim_wilma.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99   -DF_CPU=8000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=stim_wilma.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = accmtr.o ea_spi.o ia_spi.o main.o stim2_0.o tii.o signal.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) stim_wilma.hex stim_wilma.eep stim_wilma.lss size

## Compile
accmtr.o: ../accmtr.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ea_spi.o: ../ea_spi.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ia_spi.o: ../ia_spi.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

stim2_0.o: ../stim2_0.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

tii.o: ../tii.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

signal.o: ../signal.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) stim_wilma.elf dep/* stim_wilma.hex stim_wilma.eep stim_wilma.lss stim_wilma.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

