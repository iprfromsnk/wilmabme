#-------------------------------------------------------------------------------------
# Paths.
HAL_PATH = .

#-------------------------------------------------------------------------------------
# Includes.
include $(HAL_PATH)/Makerules

ifeq ($(HAL), ATMEGA1281)
  TARGET=AVR
endif

ifeq ($(HAL), ATMEGA2561)
  TARGET=AVR
endif

ifeq ($(HAL), ATMEGA1284)
  TARGET=AVR
endif

ifeq ($(HAL), AT90USB1287)
  TARGET=AVR
endif

ifeq ($(HAL), ATMEGA128RFA1)
  TARGET=AVR
endif

ifeq ($(HAL), ATXMEGA128A1)
  TARGET=XMEGA
endif

ifeq ($(HAL), ATXMEGA256A3)
  TARGET=XMEGA
endif

ifeq ($(HAL), AT91SAM7X256)
  TARGET=ARM
endif

ifeq ($(TARGET), AVR)
all:
	make all -C $(COMPONENTS_PATH)/HAL/avr

clean:  
	make clean -C $(COMPONENTS_PATH)/HAL/avr
endif

ifeq ($(TARGET), XMEGA)
all:
	make all -C $(COMPONENTS_PATH)/HAL/xmega

clean:  
	make clean -C $(COMPONENTS_PATH)/HAL/xmega
endif

ifeq ($(TARGET), ARM)
all:
	make all -C $(COMPONENTS_PATH)/HAL/arm7tdmi

clean:  
	make clean -C $(COMPONENTS_PATH)/HAL/arm7tdmi
endif
