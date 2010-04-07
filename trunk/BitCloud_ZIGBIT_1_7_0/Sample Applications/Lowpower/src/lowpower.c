/**************************************************************************//**
  \file lowpower.c

  \brief Low-Power application implementation.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#include "lowpower.h"
#include "boardabstraction.h"

/***********************************************************************************
  Global variables - APS layer variables
***********************************************************************************/
APS_DataReq_t apsDataReq; // APS Data Request primitive (for application message sending)
AppMessageBuffer_t appMessageBuffer; // Application message buffer

/***********************************************************************************
  Local variables
***********************************************************************************/
static AppState_t appState = APP_STATE_INITIAL;                       // Current application state

// BitCloud stack primitives
static APS_RegisterEndpointReq_t apsRegisterEndpointReq;       // APS Register Endpoint Request primitive (APS endpoint descriptor)
static ZDO_StartNetworkReq_t  zdoStartNetworkReq;              // Request parameters for network start

// Endpoint simple descriptor (ZDO endpoint descriptor)
static SimpleDescriptor_t simpleDescriptor =
{
  .endpoint = APP_ENDPOINT,
  .AppProfileId = APP_PROFILE_ID,
  .AppDeviceId = 1,
  .AppDeviceVersion = 1,
};

// Pointer to device type specific functions.
// Can be either coordinator or end device.
static AppClientOps_t *ops = NULL;

/***********************************************************************************
  Local functions declaration
***********************************************************************************/
static void buttonCallback(AppButton_t button);
static void APS_DataInd(APS_DataInd_t* ind);
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confInfo);

/***********************************************************************************
  Local functions implementation
***********************************************************************************/
/********************************************************************
  Description:  Change application state, inform devie specific code
  if needed
  Parameters:   newState - state to set
  Returns:      none
********************************************************************/
static void setAppState(AppState_t newState)
{
  appState = newState;
  SYS_PostTask(APL_TASK_ID);
  if (APP_STATE_NETWORK_JOINING == newState || APP_STATE_NETWORK_JOINED == newState)
  {
    if (ops && ops->networkStateChanged)
      ops->networkStateChanged(newState);
  }
}

/********************************************************************
  Description:  application and stack parameters init
  Parameters:   none
  Returns:      none
********************************************************************/
static void initApp(void)
{
  ShortAddr_t nwkAddr;

#ifdef _BUTTONS_
  setAppState(APP_STATE_START_WAIT);
#else
  setAppState(APP_STATE_NETWORK_JOINING);
#endif

  // Open periphery and read NWK address as dipswitch's state.
  boardAbstractionOpen();
  nwkAddr = boardAbstractionReadSliders();

  if (0 == nwkAddr)
  {
#ifdef _COORDINATOR_
#ifdef _SECURITY_
    ExtAddr_t addr;
    CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &addr);
    CS_WriteParameter(CS_UID_ID, &addr);
#endif //_SECURITY_
    ops = appGetCoordinatorOps();
#else
    return; // This device can not be coordinator
#endif // _COORDINATOR_
  }
  else
  {
#ifdef _ENDDEVICE_
    ops = appGetEndDeviceOps();
#else
    return; // This device can not be end device
#endif // _ENDDEVICE_
  }

  // Set common options to config server
  CS_WriteParameter(CS_NWK_ADDR_ID, &nwkAddr);

  //init common
  apsDataReq.dstEndpoint             = APP_ENDPOINT;                          // Destination endpoint
  apsDataReq.profileId               = APP_PROFILE_ID;                        // Profile ID
  apsDataReq.clusterId               = APP_CLUSTER_ID;                        // Destination cluster ID
  apsDataReq.srcEndpoint             = APP_ENDPOINT;                          // Source endpoint
  apsDataReq.txOptions.acknowledgedTransmission = 1;                          // Acknowledged transmission enabled
  apsDataReq.radius                  = 0;                                     // Default radius
  apsDataReq.asduLength              = sizeof (appMessageBuffer.msg);         // ASDU size
  apsDataReq.asdu                    = (uint8_t*) &appMessageBuffer.msg;      // ASDU pointer as an application message
  apsDataReq.dstAddrMode             = APS_SHORT_ADDRESS;                     // Short addressing mode

  // Set device type specific options
  if (ops && ops->init)
    ops->init();

  boardAbstractionRegisterKeyCallback(buttonCallback);

  SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description: Button released handler
  Parameters: button - number of button was released
              (Button0 as BSP_KEY0 - Join network, other keys routed to device specific layer)
  Returns:    none
********************************************************************/
static void buttonCallback(AppButton_t button)
{
  switch (button)
  {
    case APP_BUTTON_0:                              // Network start button
      if (APP_STATE_START_WAIT == appState)     // If application waits for this event
        setAppState(APP_STATE_NETWORK_JOINING);
      break;

    default:
      if (ops && ops->buttonHandler)
        ops->buttonHandler(button);
      break;
  }
}

/********************************************************************
  Description: start network
  Parameters: none.
  Returns:    none
********************************************************************/
static void startNetwork(void)
{
  boardAbstractionShowIndication(APP_INDICATION_NETWORK_SEARCH);
  zdoStartNetworkReq.ZDO_StartNetworkConf = ZDO_StartNetworkConf; // Network started confirm handler
  ZDO_StartNetworkReq(&zdoStartNetworkReq); // start network
}

/********************************************************************
  Description: ZDO_StartNetwork primitive confirmation was received.
  Parameters: confirmInfo - confirmation information
  Returns:    none
********************************************************************/
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confInfo)
{
  // Joined network successfully
  if (ZDO_SUCCESS_STATUS == confInfo->status)     // Network was started successfully
  {
    setAppState(APP_STATE_NETWORK_JOINED);

    boardAbstractionShowIndication(APP_INDICATION_NETWORK_STARTED);

    // Set application endpoint properties and register endpoint
    apsRegisterEndpointReq.simpleDescriptor = &simpleDescriptor;
    apsRegisterEndpointReq.APS_DataInd = APS_DataInd;
    APS_RegisterEndpointReq(&apsRegisterEndpointReq);
  }

  SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description:  Application endpoint indication handler
  Parameters:   ind - APS Data Indication primitive
  Returns:      none
********************************************************************/
static void APS_DataInd(APS_DataInd_t* ind)
{
  boardAbstractionShowIndication(APP_INDICATION_DATA_RECEIVED);
  if (ops && ops->dataInd)
    ops->dataInd(ind);
}

/***********************************************************************************
  Global functions
***********************************************************************************/

/********************************************************************
  Description: Network update notification
  Parameters: ZDO_MgmtNwkUpdateNotf_t *nwkParams - update notification
  Returns: nothing.
********************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  ZDO_StartNetworkConf_t conf;

  if (ZDO_NETWORK_STARTED_STATUS == nwkParams->status)
  {
    conf.status = ZDO_SUCCESS_STATUS;
    ZDO_StartNetworkConf(&conf);
  }
  else if (ZDO_NETWORK_LEFT_STATUS == nwkParams->status)
  {
    setAppState(APP_STATE_NETWORK_JOINING);
  }
}

/********************************************************************
  Description: Application task handler
  Parameters: none.
  Returns:    none
********************************************************************/
void APL_TaskHandler(void)
{
  switch (appState)
  {
    // node is in initial state
    case APP_STATE_INITIAL:                 // Initial (after RESET) state
      initApp();                            // Init application
      break;

    case APP_STATE_START_WAIT:              //Do nothing, waiting for 'start network' key press
      break;

    case APP_STATE_NETWORK_JOINING:         // Network is in the joining stage
      startNetwork();                       // Start/joing network
      break;

    case APP_STATE_NETWORK_JOINED:          // Network was successfully started
      if (ops && ops->taskHandler)                  // Route events to device specific layers
        ops->taskHandler();
      break;
  }
}

// eof lowpower.c
