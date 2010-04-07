#ifndef _MESSAGES_H_
#define _MESSAGES_H_

//***********************************************************************************************
//include section
//***********************************************************************************************
#include <appFramework.h>    // endpoint descriptor types
#include <aps.h>             // Main APS header

#include "nwkConfig.h"		//kell az application header is, abban van definiálva az endpoint


//***********************************************************************************************
//define section
//***********************************************************************************************
#define MAX_MSG_LTH 48


//***********************************************************************************************
//function header section
//***********************************************************************************************

//initialization functions
void registerEndpoints(void);
void initMessages(void (*dataCallback)(APS_DataInd_t *), void (*commandCallback)(APS_DataInd_t *));
//send message/command - both may contain 0-s -> message length is a parameter
void sendMessage_wZ(uint8_t *message, uint8_t lth, ShortAddr_t destAddr);
void sendCommand_wZ(uint8_t *message, uint8_t lth, ShortAddr_t destAddr);

//internal confirmation function
void APS_DataConf(APS_DataConf_t *confInfo);  // Data transmission confirmation handler
//internal data indication functions
void APS_DataInd(APS_DataInd_t *indData);
void APS_CommandInd(APS_DataInd_t *indData); // Command reception handler

#endif //_MESSAGES_H_
