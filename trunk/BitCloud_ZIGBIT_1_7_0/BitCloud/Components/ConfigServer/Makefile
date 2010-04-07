COMPONENTS_PATH = ..
include $(MAKERULES)
 
# Compiler flags extending with Confiuration server parameters.
CFLAGS += $(CFLAGS_CS)

# Compiler flags extending with "debug info" compiler flag.
CFLAGS += $(CFLAGS_DBG)

##### PATHS FLAGS OF INCLUDES #########
CFLAGS += -I./include
CFLAGS += -I$(SE_PATH)/include
CFLAGS += -I$(ZDO_PATH)/include
CFLAGS += -I$(NWK_PATH)/include
CFLAGS += -I$(NWK_PATH)/include/private
CFLAGS += -I$(APS_PATH)/include
CFLAGS += -I$(MAC_PHY_PATH)/include
CFLAGS += -I$(HAL_PATH)/include
CFLAGS += -I$(HAL_HWD_COMMON_PATH)/include
CFLAGS += -I$(SSP_PATH)/include
CFLAGS += -I$(PDS_PATH)/include
CFLAGS += -I$(TC_PATH)/include

###### LIB #########
BUILDDIR =.
LIBDIR = $(BUILDDIR)/lib
LISTDIR = $(BUILDDIR)/list
LDFLAGS = -L$(LIBDIR)
LIB = $(LIBDIR)/lib$(CS_LIB).a

###### TARGETS ################
all: component_label LIB_CONFIG_SERVER
component_label:
	@echo 
	@echo ----------------------------------------------------
	@echo Config Server library creation.
	@echo ----------------------------------------------------

################
LIB_CONFIG_SERVER:
	$(CC) $(CFLAGS) $(BUILDDIR)/src/configServer.c -o $(BUILDDIR)/objs/configServer.o
	$(AR) $(AR_KEYS) $(LIB) $(BUILDDIR)/objs/configServer.o
	$(SIZE) -td $(LIB)
################

clean:
	@echo 
	@echo ----------------------------------------------------
	@echo Config Server component cleaning.
	@echo ----------------------------------------------------
	rm -f $(PROG) $(BUILDDIR)/objs/configServer.o $(LIB) $(LISTDIR)/*.*
