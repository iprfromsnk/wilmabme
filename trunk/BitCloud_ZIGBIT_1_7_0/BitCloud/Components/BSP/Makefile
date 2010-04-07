COMPONENTS_PATH = ..
include $(MAKERULES)
include ./BoardConfig

###### LIB ##########
ifeq ($(BOARD), BOARD_MESHBEAN)
  BUILDDIR = ./MESHBEAN
endif
ifeq ($(BOARD), BOARD_RAVEN)
  BUILDDIR = ./RAVEN
endif
ifeq ($(BOARD), BOARD_STK500)
  BUILDDIR = ./ATML_STK500
endif
ifeq ($(BOARD), BOARD_STK600)
  BUILDDIR = ./ATML_STK600
endif
ifeq ($(BOARD), BOARD_USB_DONGLE)
  BUILDDIR = ./ATML_USB_DONGLE
endif
ifeq ($(BOARD), BOARD_MESHBEAN_LAN)
  BUILDDIR = ./MESHBEAN_LAN
endif
ifeq ($(BOARD), BOARD_MESHBEAN_TURBO)
  BUILDDIR = ./MESHBEAN_TURBO
endif
ifeq ($(BOARD), BOARD_SAM7X_EK)
  BUILDDIR = ./ATML_SAM7X_EK
endif
ifeq ($(BOARD), BOARD_HON_IQL)
  BUILDDIR = ./HON_IQL
endif
ifeq ($(BOARD), BOARD_HON_ALERTON)
  BUILDDIR = ./HON_ALERTON
endif
ifeq ($(BOARD), BOARD_RCB128RFA1)
  BUILDDIR = ./RCB128RFA1
endif

# Compiler flags extending with "debug info" compiler flag.
CFLAGS += $(CFLAGS_DBG)

LIBDIR = ./lib
LISTDIR = ./list
LDFLAGS = -L$(LIBDIR)
PROG = BSP.elf
LIBS = $(LIBDIR)/lib$(BSP_LIB).a

##### PATHS FLAGS OF INCLUDES #########
CFLAGS += -I$(BUILDDIR)/include
CFLAGS += -I$(BUILDDIR)/../include
CFLAGS += -I$(HAL_PATH)/include  
CFLAGS += -I$(HAL_HWD_COMMON_PATH)/include
CFLAGS += -I$(SE_PATH)/include

BSPFLAGS=$(CFLAGS) 
ifeq ($(BOARD), BOARD_SAM7X_EK)
  BSPFLAGS=$(patsubst %$(ARM_MODE_THUMBS_CFLAGS),,$(CFLAGS)) $(ARM_MODE_ARM_CFLAGS)
  BSPFLAGS += -I$(FREE_RTOS_PATH)/
  BSPFLAGS += -I$(FREE_RTOS_PATH)/include
endif

ifeq ($(BOARD), BOARD_MESHBEAN)
modules =                       \
       bspTII                   \
       swTII					\
       bspTaskManager           

endif
ifeq ($(BOARD), BOARD_RAVEN)
modules =                       \
       lcd                      \
       bspTaskManager           \
       joystik
endif
ifeq ($(BOARD), BOARD_STK500)
modules =                       \
       leds                     \
       pwrCtrl                  \
       bspTaskManager           \
       buttons                  \
       battery                  \
       sliders                  \
       sensors
endif
ifeq ($(BOARD), BOARD_STK600)
modules =                       \
       leds                     \
       buttons                  \
       bspTaskManager
endif
ifeq ($(BOARD), BOARD_USB_DONGLE)
modules =                       \
       leds                     \
       bspTaskManager
endif
ifeq ($(BOARD), BOARD_MESHBEAN_LAN)
modules =                       \
       leds                     \
       buttons                  \
       bspTaskManager
endif
ifeq ($(BOARD), BOARD_MESHBEAN_TURBO)
modules =                       \
       leds                     \
       buttons                  \
       sliders                  \
       bspTaskManager
endif
ifeq ($(BOARD), BOARD_SAM7X_EK)
modules =                       \
       leds                     \
       joystick                 \
       bspTaskManager
endif
ifeq ($(BOARD), BOARD_HON_IQL)
modules =                       \
       leds                     \
       buttons                  \
       hexSwitch                \
       bspTaskManager           \
       rs485Controller
endif
ifeq ($(BOARD), BOARD_HON_ALERTON)
modules =                       \
       leds                     \
       buttons                  \
       hexSwitch                \
       bspTaskManager           \
       rs485Controller          \
       usbController
endif
ifeq ($(BOARD), BOARD_RCB128RFA1)
modules =                       \
       leds                     \
       bspTaskManager           \
       buttons
endif

objects = $(addsuffix .o,$(addprefix $(BUILDDIR)/objs/,$(modules)))
sources = $(addsuffix .c,$(addprefix $(BUILDDIR)/src/,$(modules)))

###### TARGETS ################
all: component_label LIB_BSP
component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo Board Support library creation.
	@echo ----------------------------------------------------

################
$(BUILDDIR)/objs/%.o: $(BUILDDIR)/src/%.c
	$(CC) $(BSPFLAGS) $^ -o $@

################
LIB_BSP : $(objects)
	$(AR) $(AR_KEYS) $(LIBDIR)/lib$(BSP_LIB).a $(objects)
	$(SIZE) -td $(LIBDIR)/lib$(BSP_LIB).a
################
clean:
	@echo 
	@echo ----------------------------------------------------
	@echo Board Support component cleaning.
	@echo ----------------------------------------------------
	rm -f $(objects) $(LIBS) $(LISTDIR)/*.*
