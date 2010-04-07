/**************************************************************************//**
  \file thrTestRouter.c
  
  \brief Troughput test application - router functionality.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
******************************************************************************/

#include "throughputTest.h"
#include <stdio.h>

// Set APP_PAYLOAD_SIZE to maximum possible if not specified before
#ifndef APP_PAYLOAD_SIZE
#define APP_PAYLOAD_SIZE APS_MAX_ASDU_SIZE
#endif

static APS_DataReq_t  msgParams; // Request parameters for APS_DataReq primitive

uint8_t appPayload[APP_PAYLOAD_SIZE + APS_AFFIX_LENGTH]; // Buffer for APS_DataReq primitive

static void APS_DataConfRouter(APS_DataConf_t *confInfo); // Indication for data confirm on router

static HAL_AppTimer_t trackPeriodTimer; // Timer for counting TIMER_TRACK_PERIOD
static uint32_t successPackets = 0;   // Amount of successfully sent packets
static uint32_t totalPackets = 0;   // Total amount of sent packets

/***********************************************************************************
  Description: handler of trackPeriodTimer fire.
  
  Parameters: none.
  
  Returns: nothing.
***********************************************************************************/
static void trackPeriodTimerFired(void)
{
  static uint8_t msgFirstPart[] = "000 of ";
  static uint8_t msgSecondPart[] = "000 successfully sent\r\n";

  printUint32(msgFirstPart, successPackets, 3);
  printUint32(msgSecondPart, totalPackets, 3);

  appWriteDataToUart(msgFirstPart, sizeof(msgFirstPart)-1);
  appWriteDataToUart(msgSecondPart, sizeof(msgSecondPart)-1);

  // Reset counters
  successPackets = 0;
  totalPackets = 0;
}


/********************************************************************
  Description: Process router or end device functionality.
               The function should be called only one time 
               after starting network.
  
  Parameters: none.

  Returns: nothing.
********************************************************************/
void appRouterTaskHandler(void)
{
  int i;
  
  // Fill application data buffer
  for (i = 0; i < APP_PAYLOAD_SIZE; i++)
  {
    appPayload[APS_ASDU_OFFSET + i] = 0xDD;
  }

  // Configure and start track period timer
  trackPeriodTimer.interval = TIMER_TRACK_PERIOD;
  trackPeriodTimer.mode     = TIMER_REPEAT_MODE;
  trackPeriodTimer.callback = trackPeriodTimerFired;
  HAL_StartAppTimer(&trackPeriodTimer);

  // Set data request parameters
  msgParams.dstAddrMode             = APS_SHORT_ADDRESS; // Short (NWK) addressing is used
  msgParams.dstAddress.shortAddress = 0;  // Coordinator NWK address is always 0
  msgParams.dstEndpoint             = END_POINT; // Destination application end point
  msgParams.profileId               = endpointParams.simpleDescriptor->AppProfileId; // Application Profile ID
  msgParams.clusterId               = 1; // Message Cluster ID (same for all messages)
  msgParams.srcEndpoint             = END_POINT; // Source end point address
  msgParams.asduLength              = APP_PAYLOAD_SIZE; // ASDU length 
  msgParams.asdu                    = (uint8_t*) (&appPayload[APS_ASDU_OFFSET]); // Buffer to ASDU
  msgParams.txOptions.acknowledgedTransmission = APP_USE_APS_ACK; // Flag indicating to use acknowledgements on APS layer or not
  msgParams.radius                  = 0;
  msgParams.APS_DataConf            = APS_DataConfRouter; // Confirm callback

  APS_DataReq(&msgParams);  // Send data request
}

/********************************************************************
  Description: Confirm on message transmission
  
  Parameters: confInfo - confirmation information

  Returns: nothing.
********************************************************************/
static void APS_DataConfRouter(APS_DataConf_t *confInfo)
{ 
  totalPackets += 1;

  if (APS_SUCCESS_STATUS == confInfo->status)
  {
    appToggleLed(DATA_TX_LED); // Indicate if successfull
    successPackets += 1;
  }
  
  APS_DataReq(&msgParams); // Immediately transmit another message to utilize bandwidth
}

//eof thrTestRouter.c
