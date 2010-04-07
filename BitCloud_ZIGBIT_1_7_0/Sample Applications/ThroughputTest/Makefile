#==============================================================================
#  The file builds the application.
#  \author
#    Atmel Corporation: http://www.atmel.com \n
#    Support email: avr@atmel.com
#
#  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
#  Licensed under Atmel's Limited License Agreement (BitCloudTM).
#==============================================================================

#==============================================================================
# Include configuration file
#==============================================================================
include Configuration
include $(COMPONENTS_PATH)/../lib/MakerulesSelector
#MAKERULES = $(abspath $(COMPONENTS_PATH)/../lib/$(LIB_MAKERULES)) # use this line once bug is fixed
# workaround GNU make 3.81 bug on windows platform
realpath_ = $(join \
            $(filter %:,$(subst :,: ,$1)),\
            $(realpath $(filter-out %:,$(subst :,: ,$1)))) 
MAKERULES = $(call realpath_, $(COMPONENTS_PATH)/../lib/$(LIB_MAKERULES))
include $(MAKERULES)
include $(BSP_PATH)/BoardConfig

#==============================================================================
# Application parameters 
#==============================================================================
APP_PARAMS = \
  APP_USE_APS_ACK \
  APP_USART_CHANNEL \
  TIMER_DELAY_PERIOD \
  TIMER_TRACK_PERIOD

CFLAGS += -DAPP_DEV_TYPE_$(APP_DEVICE_TYPE)
CFLAGS += -D$(APP_INTERFACE)

#==============================================================================
# Stack parameters being set to Config Server
#==============================================================================
CS_PARAMS = \
  CS_MAX_NETWORK_DEPTH \
  CS_NEIB_TABLE_SIZE \
  CS_MAX_CHILDREN_AMOUNT \
  CS_MAX_CHILDREN_ROUTER_AMOUNT \
  CS_CHANNEL_MASK \
  CS_CHANNEL_PAGE \
  CS_EXT_PANID


ifeq ($(SECURITY_MODE), STANDARD_SECURITY_MODE)
CS_PARAMS += \
  CS_NETWORK_KEY \
  CS_ZDO_SECURITY_STATUS \
  CS_APS_SECURITY_TIMEOUT_PERIOD \
  CS_APS_TRUST_CENTER_ADDRESS
endif

# Hardware depended stack parameters being set to Config Server
ifeq (, $(findstring $(BOARD), BOARD_MESHBEAN BOARD_RAVEN BOARD_USB_DONGLE))
  CS_PARAMS += CS_UID
endif

# Test network dependent parameters being set to Config Server
ifeq ($(TEST_NETWORK), 1)
  CFLAGS += -DTEST_NETWORK
endif

#==============================================================================
# Generate FLAGS based on stack parameters ans application parameters
#==============================================================================
CFLAGS_CS  = $(foreach PARAM, $(CS_PARAMS) $(APP_PARAMS), -D$(PARAM)=$(value $(PARAM)))

# CFLAGS extending with configuration server parameters.
CFLAGS += $(CFLAGS_CS)

#==============================================================================
# Output debug port for ARM platforms only 
#==============================================================================
ifeq ($(HAL), AT91SAM7X256)
  ifeq ($(DEBUG), ON)
    CFLAGS += -D_DBG_
  endif
endif

#==============================================================================
# Compiler specific flags
#==============================================================================
ifeq ($(DEBUG), ON)
  ifeq ($(COMPILER_TYPE), GCC)
    CFLAGS_DBG += -g
  endif
  ifeq ($(COMPILER_TYPE), IAR)
    CFLAGS_DBG += --debug
  endif
  # Compiler flags extending with "debug info" compiler flag.
  CFLAGS += $(CFLAGS_DBG)
endif

#==============================================================================
# Include paths flags
#==============================================================================
INCLUDEDIRS =                            \
	-I$(APP_PATH)/include            \
	-I$(SE_PATH)/include             \
	-I$(APS_PATH)/include            \
	-I$(NWK_PATH)/include            \
	-I$(ZDO_PATH)/include            \
	-I$(MAC_PHY_PATH)/include        \
	-I$(HAL_PATH)/include            \
	-I$(HAL_HWD_COMMON_PATH)/include \
	-I$(BSP_PATH)/include            \
	-I$(CS_PATH)/include             \
	-I$(PDS_PATH)/include            \
	-I$(TC_PATH)/include             \
	-I$(SSP_PATH)/include            \
	-I$(DRIVERS_PATH)/include

#==============================================================================
# Libraries paths
#==============================================================================
ifeq ($(COMPILER_TYPE), GCC)
  LIBDIRS  = -L$(COMPONENTS_PATH)/../lib
  LIBDIRS += -L$(BSP_PATH)/lib
  LIBDIRS += -L$(CS_PATH)/lib
  LIBDIRS += -L$(PDS_PATH)/lib
  ifeq ($(APP_INTERFACE), APP_USE_VCP)
    LIBDIRS += -L$(DRIVERS_PATH)/lib
  endif

  LIBS = -l$(STACK_LIB) 
  ifeq ($(APP_INTERFACE), APP_USE_VCP)
    LIBS += -l$(VCP_LIB) 
  endif
  LIBS += -l$(CS_LIB) 
  LIBS += -l$(PDS_LIB) 
  LIBS += -l$(BSP_LIB) 
  LIBS += -l$(HAL_LIB)
  LIBS += -l$(STACK_LIB)
endif
ifeq ($(COMPILER_TYPE), IAR)
  LIBS =  $(COMPONENTS_PATH)/../lib/lib$(HAL_LIB).a
  LIBS += $(COMPONENTS_PATH)/../lib/lib$(STACK_LIB).a
  LIBS += $(CS_PATH)/lib/lib$(CS_LIB).a
  LIBS += $(PDS_PATH)/lib/lib$(PDS_LIB).a
  LIBS += $(BSP_PATH)/lib/lib$(BSP_LIB).a
  ifeq ($(APP_INTERFACE), APP_USE_VCP)
    LIBS += $(DRIVERS_PATH)/lib/lib$(VCP_LIB).a
  endif
endif

#==============================================================================
# Linking
#==============================================================================
ifeq ($(COMPILER_TYPE), GCC)
  # It's easier to use indirect ld call via gcc instead of direct ld call.
  LD = $(CC)
  LINKER_FLAGS = -Xlinker -Map=$(APP_PATH)/list/$(PROJNAME).map -Wl,--gc-sections
  ifeq ($(HAL), ATMEGA1281)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(APP_PATH)/linkerScr/atmega1281.ld
  endif
  ifeq ($(HAL), ATMEGA2561)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(APP_PATH)/linkerScr/atmega2561.ld
  endif
  ifeq ($(HAL), AT91SAM7X256)
    LDSCRIPT = atmel-rom
    LINKER_FLAGS += $(filter -mthumb%,$(CFLAGS))
    LINKER_FLAGS += $(filter -mcpu%,$(CFLAGS))
    LINKER_FLAGS += -nostartfiles
    LINKER_FLAGS += -Xlinker -T$(APP_PATH)/linkerScr/$(LDSCRIPT).ld
  endif
  ifeq ($(HAL), AT90USB1287)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(APP_PATH)/linkerScr/at90usb1287.ld
  endif
  ifeq ($(HAL), ATMEGA1284)
    LINKER_FLAGS += $(filter -mmcu%,$(CFLAGS))
    LINKER_FLAGS += -Wl,--script=$(APP_PATH)/linkerScr/atmega1284p.ld
  endif

  ifeq ($(DEBUG), ON)
    LINKER_FLAGS += -g
  endif
endif
ifeq ($(COMPILER_TYPE), IAR)
  ifeq ($(HAL), AT91SAM7X256)
    LDSCRIPT = at91SAM7X256_FLASH
    LINKER_FLAGS  = --redirect _Printf=_PrintfTiny 
    LINKER_FLAGS += --redirect _Scanf=_ScanfSmall
    LINKER_FLAGS += --semihosting 
    LINKER_FLAGS += --entry __iar_program_start
    LINKER_FLAGS += --map $(APP_PATH)/list/$(PROJNAME).map
    LINKER_FLAGS += --config $(APP_PATH)/linkerScr/$(LDSCRIPT).icf
  endif
  ifeq ($(HAL), ATMEGA1281)
    LINKER_FLAGS  = -Fdebug-intel-ext 
    LINKER_FLAGS += -l $(APP_PATH)/list/$(PROJNAME).html 
    LINKER_FLAGS += -xmsh #Generate linker list file
    LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm1281bitcloud.xcl 
    LINKER_FLAGS += -H1895 
    LINKER_FLAGS += -h"(CODE)0-(_..X_INTVEC_SIZE-1)"
    LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90 
    LINKER_FLAGS += -e_PrintfSmall=_Printf
    LINKER_FLAGS += -S
  endif
  ifeq ($(HAL), ATMEGA2561)
    LINKER_FLAGS  = -Fdebug-intel-ext 
    LINKER_FLAGS += -l $(APP_PATH)/list/$(PROJNAME).html 
    LINKER_FLAGS += -xmsh #Generate linker list file
    LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm2561bitcloud.xcl 
    LINKER_FLAGS += -H1895 
    LINKER_FLAGS += -h"(CODE)0-(_..X_INTVEC_SIZE-1)"
    LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90 
    LINKER_FLAGS += -e_PrintfSmall=_Printf
    LINKER_FLAGS += -S
  endif
  ifeq ($(HAL), ATMEGA1284)
    LINKER_FLAGS  = -Fdebug-intel-ext 
    LINKER_FLAGS += -l $(APP_PATH)/list/$(PROJNAME).html 
    LINKER_FLAGS += -xmsh #Generate linker list file
    LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgm1284bitcloud.xcl 
    LINKER_FLAGS += -H1895 
    LINKER_FLAGS += -h"(CODE)0-(_..X_INTVEC_SIZE-1)"
    LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90 
    LINKER_FLAGS += -e_PrintfSmall=_Printf
    LINKER_FLAGS += -S
  endif
  ifeq ($(HAL), AT90USB1287)
    LINKER_FLAGS  = -Fdebug-intel-ext 
    LINKER_FLAGS += -l $(APP_PATH)/list/$(PROJNAME).html 
    LINKER_FLAGS += -xmsh #Generate linker list file
    LINKER_FLAGS += -f $(APP_PATH)/linkerScr/cfgusb1287bitcloud.xcl 
    LINKER_FLAGS += -H1895 
    LINKER_FLAGS += -h"(CODE)0-(_..X_INTVEC_SIZE-1)"
    LINKER_FLAGS += -s __bitcloud_start $(IAR_PATH)/LIB/DLIB/dlAVR-3s-ec_mul-n.r90 
    LINKER_FLAGS += -e_PrintfSmall=_Printf
    LINKER_FLAGS += -S
  endif      
endif

PLATFORM_SPECIFIC_OBJECTS_WITH_PATH = $(addprefix $(COMPONENTS_PATH)/../lib/, $(PLATFORM_SPECIFIC_OBJECTS))

#==============================================================================
# Export all variables needed by sub-make processes
#==============================================================================
export MAKERULES BOARD CFLAGS_CS CFLAGS_DBG

#==============================================================================
# Objects
#==============================================================================
SRCS = $(wildcard $(APP_PATH)/src/*.c)
OBJS += $(addprefix $(APP_PATH)/objs/, $(notdir $(SRCS:.c=.o)))

#==============================================================================
# Targets
#==============================================================================
.PHONY: all clean size cs pds bsp vcp obj_label

all: $(PROJNAME).elf $(PROJNAME).srec $(PROJNAME).hex $(PROJNAME).bin size


$(PROJNAME).elf: cs pds bsp vcp obj_label $(OBJS) $(PLATFORM_SPECIFIC_OBJECTS_WITH_PATH)
	@echo 
	@echo -----------------Linking---------------------------
	$(LD) $(LIBDIRS) $(LINKER_FLAGS) $(OBJS) $(PLATFORM_SPECIFIC_OBJECTS_WITH_PATH) $(LIBS) -o $@

pds:
	make all -C $(PDS_PATH)

bsp:
	make all -C $(BSP_PATH)

cs:
	make all -C $(CS_PATH)

vcp:
ifeq ($(APP_INTERFACE), APP_USE_VCP)
	make all -C $(DRIVERS_PATH)/VCP
endif # APP_USE_VCP

obj_label:
	@echo 
	@echo -------Application objects creation---------------

objs/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) $< -o $@

%.srec: $(PROJNAME).elf
	$(OBJCOPY) -O srec --srec-len 128 $^ $@

%.hex:  $(PROJNAME).elf
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

%.bin:  $(PROJNAME).elf
	$(OBJCOPY) -O binary --strip-debug --strip-unneeded -R .eeprom $^ $@

size: $(PROJNAME).elf
	@echo 
	@$(SIZE) -td $(PROJNAME).elf

clean:
	@echo 
	@echo -------Application cleaning------------------------
	-rm -rf $(OBJS) $(APP_PATH)/list/*.* $(PROJNAME).elf $(PROJNAME).hex $(PROJNAME).srec $(PROJNAME).bin
	make clean -C $(PDS_PATH)
	make clean -C $(CS_PATH)
	make clean -C $(BSP_PATH)
ifeq ($(APP_INTERFACE), APP_USE_VCP)
	make clean -C $(DRIVERS_PATH)/VCP
endif # APP_USE_VCP

ifeq ($(HAL), ATMEGA1281)
flash:
	jtagiceii -d ATmega1281 -f 0x1F62 -e -pf -if $(PROJNAME).hex
endif

# eof Makefile
