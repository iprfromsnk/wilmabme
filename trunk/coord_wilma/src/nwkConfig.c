#include "nwkConfig.h"

#include <configServer.h>    // Config Server header
#include <appFramework.h>    // Main stack types

//*******************************************************
//				CHANGE HERE
//*******************************************************
#define END_DEVICE_ADDRESS 0x07

#define APP_COORD_UID 0xAAAAAAAAAAAAAAAALL
#define CS_CHANNEL_MASK (1l<<0x0f)

bool useStatAddr = true;

#ifdef COORDINATOR
	bool rxOnWhenIdleFlag = true;
#else
	bool rxOnWhenIdleFlag = true;
#endif


//*******************************************************
//				DO NOT CHANGE BELOW
//*******************************************************
#ifdef COORDINATOR 
	static ShortAddr_t srcAddr = 0x00;
	static DeviceType_t appDeviceType = DEVICE_TYPE_COORDINATOR; 			
#else				
	static ShortAddr_t srcAddr = END_DEVICE_ADDRESS;
	static DeviceType_t appDeviceType = DEVICE_TYPE_END_DEVICE;
#endif

static uint64_t extPanId = APP_COORD_UID;
static uint32_t chMask = CS_CHANNEL_MASK;

//*******************************************************
//				FUNCTIONS
//*******************************************************
void initNwkParams(void){
      
    CS_WriteParameter(CS_EXT_PANID_ID, &extPanId);  
    CS_WriteParameter(CS_CHANNEL_MASK_ID, &chMask);
    CS_WriteParameter(CS_NWK_ADDR_ID, &srcAddr);
	CS_WriteParameter(CS_DEVICE_TYPE_ID, &appDeviceType);
	
    CS_WriteParameter(CS_NWK_UNIQUE_ADDR_ID, &useStatAddr);

    CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdleFlag);


	  {
	  uint32_t sleepPer=6000000; //eleg nagy kell h legyen h ne kapcsoljon ki kozben
	  CS_WriteParameter(CS_END_DEVICE_SLEEP_PERIOD_ID, &sleepPer);
	  }

}
