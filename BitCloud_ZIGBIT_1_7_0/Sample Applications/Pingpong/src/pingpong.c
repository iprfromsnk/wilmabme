/**************************************************************************//**
  \file pingpong.c

  \brief Ping-pong sample application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#include <configServer.h>    // Config Server header
#include <taskManager.h>
#include <appFramework.h>    // Main stack types
#include <appTimer.h>        // Application timer header
#include <apsMacros.h>
#include <pingpong.h>        // Own application header
#include <usart.h>
#include <uid.h>
#include <aps.h>             // Main APS header
#include <zdo.h>             // Main ZDO header

/***********************************************************************************
  Local variables
***********************************************************************************/
static DeviceType_t appDeviceType = DEVICE_TYPE_COORDINATOR;   // Device type (Router/Coordinator/End device)
static uint8_t dataPayload; // Payload
static uint8_t appPayload[APP_PAYLOAD_SIZE + APS_AFFIX_LENGTH]; // Buffer for application payload
bool fwPacketFlag = false;  // Flag indicating that device is currently forwarding a packet

static AppState_t appState = APP_INITING_STATE; // Current application state
static ZDO_StartNetworkReq_t networkParams; // Request params for ZDO_StartNetworkReq

#ifdef TEST_NETWORK
static HAL_UsartDescriptor_t appUsartDescriptor; // USART descriptor (required by stack)
#endif // TEST_NETWORK

// Endpoint parameters
static SimpleDescriptor_t simpleDescriptor = {PINGPONG_ENDPOINT, PINGPONG_PROFILE, 1, 1, 0, 0 , NULL, 0, NULL};
#if APP_USE_BINDING
static ClusterId_t clustersTable[] = {0};
static ClusterId_t currentCluster;
static APS_BindReq_t apsReq;
static bool matchesFound = false;
static ZDO_ZdpReq_t zdpReq;
static ShortAddr_t discoveredDevice = BROADCAST_SHORT_ADDRESS;
static bool deferredPacket = false; //flag to indicate deffered packets
#else
static ShortAddr_t srcAddr;          // Own network address
static ShortAddr_t dstAddr;          // Destination network address
#endif

static APS_RegisterEndpointReq_t endpointParams;

static HAL_AppTimer_t flashTimer; // Timer indicating starting network
static HAL_AppTimer_t delayFwTimer;         // Timer period of waiting before forwarding packet to next node

static APS_DataReq_t dataReq;        // Request for APS_DataReq primitive

/***********************************************************************************
  Local functions
***********************************************************************************/

static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo); // Network start/join confirmation
static void APS_DataInd(APS_DataInd_t *indData); // Data reception handler
static void APS_DataConf(APS_DataConf_t *confInfo);  // Data transmission confirmation handler
static void buttonReleased(uint8_t buttonNumber); // Button release event handler
static void prepareMsgParams(void); // Configures general data message parameters

#ifdef TEST_NETWORK
// USART related functions (only required for test network)
static void usartInit(void);
static void usartSendHeartbeat(void);
static void usartWriteConf(void);
#endif // TEST_NETWORK
#if APP_USE_BINDING
static void findDevices(ClusterId_t cluster);
static void doIEEEAddrReq(ShortAddr_t);
#endif

/********************************************************************
  Description: Flash timer fired. Toggle LED for blink
  Parameters: none.
  Returns: nothing.
********************************************************************/
static void flashTimerFired(void)
{
  static uint8_t ledState = 1;
  ledState ^= 1;

  switch(appState)
  {
    case APP_NETWORK_STARTING_STATE:
      if(ledState)
        appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_OFF);
      else
        appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_2);
      appToggleLed(NETWORK_LED);
      break;

    case APP_DEVICE_FINDING_STATE:
      appToggleLed(BIND_LED);
      break;

    default:
      break;
  }
}

/********************************************************************
  Description: Set and start timer for LED blinking
  Parameters: none.
  Returns: nothing.
********************************************************************/
static void startFlashTimer(void)
{
  HAL_StopAppTimer(&flashTimer);
  flashTimer.interval = TIMER_STARTING_NETWORK;
  flashTimer.mode     = TIMER_REPEAT_MODE;
  flashTimer.callback = flashTimerFired;
  HAL_StartAppTimer(&flashTimer);
}

/********************************************************************
  Description: Packet forwarding delay has expired. Forward packet and turn indicating LED off

  Parameters: none.

  Returns: nothing.
********************************************************************/
void delayFwTimerFired(void)
{
  appOnLed(DATA_LED);
  appSendLcdCmd(LCD_CMD_SYMB_TRX_OFF);
  appSendLcdCmd(LCD_CMD_SYMB_TRX_TX);
  APS_DataReq(&dataReq);
}

/********************************************************************
  Description: Application task handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void APL_TaskHandler(void)
{
  switch (appState)
  {
    // Node is in initial state
    case APP_INITING_STATE:
    {
      endpointParams.simpleDescriptor = &simpleDescriptor;

      // Read switches and assign own network address
      uint8_t dswitch;
      dswitch = appReadSliders() & SLIDERS_MASK;

#if !APP_USE_BINDING
      srcAddr = dswitch & ADDRESS_SLIDERS_MASK;

      // If 3rd switch is on then destination address is 0 (coordinator)
      if (dswitch & SLIDER_3_MASK)
        dstAddr = 0;
      else
        dstAddr = srcAddr + 1;

      CS_WriteParameter(CS_NWK_ADDR_ID, &srcAddr); // Assign own NWK address

      bool useStatAddr = true;
      CS_WriteParameter(CS_NWK_UNIQUE_ADDR_ID, &useStatAddr);
#else
	// Endpoint chain configuration
      {
        currentCluster = START_CLUSTER + (dswitch & ADDRESS_SLIDERS_MASK);
        // If 3rd switch is on then destination cluster is 0
        clustersTable[0] = (dswitch & SLIDER_3_MASK) ? START_CLUSTER: (currentCluster + 1);
        endpointParams.simpleDescriptor->AppInClustersList = clustersTable;
        endpointParams.simpleDescriptor->AppInClustersCount = 1;
      }
#endif

      // Set device type: logical address equal to 0 is coordinator, otherwise router
      appDeviceType = (dswitch & ADDRESS_SLIDERS_MASK) ? DEVICE_TYPE_ROUTER : DEVICE_TYPE_COORDINATOR;
      CS_WriteParameter(CS_DEVICE_TYPE_ID, &appDeviceType);

#ifdef TEST_NETWORK
      if (DEVICE_TYPE_COORDINATOR == appDeviceType)
        usartInit();
#endif // TEST_NETWORK

#ifdef _SECURITY_
      if (DEVICE_TYPE_COORDINATOR == appDeviceType)
      {
        ExtAddr_t addr;
        CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &addr);
        CS_WriteParameter(CS_UID_ID, &addr);
      }
#endif //_SECURITY_

    { // Set transceiver to be always on (no sleeping)
        bool rxOnWhenIdleFlag = true;
        CS_WriteParameter(CS_RX_ON_WHEN_IDLE_ID, &rxOnWhenIdleFlag);
      }

      appOpenLeds();
      appOpenLcd();

      endpointParams.APS_DataInd = APS_DataInd;   // Register handler for incoming data packets
      appState = APP_AWAITING_NETWORK_START_STATE; // Switch to awaiting network start state
      SYS_PostTask (APL_TASK_ID);
      break;
    }

    // Node is waiting network start/join request
    case APP_AWAITING_NETWORK_START_STATE:
      appOpenButtons(NULL, buttonReleased); // Set handlers for button events

#ifndef _BUTTONS_ // Button press simulating.
      buttonReleased(NETWORK_BUTTON);
#endif // _BUTTONS_
      break;

    // Node is starting/joining network
    case APP_NETWORK_STARTING_STATE:
      {
        // Set network request parameters
        networkParams.ZDO_StartNetworkConf = ZDO_StartNetworkConf; // Handler for network start confirmation
        ZDO_StartNetworkReq(&networkParams); // Start/join network
      }
      break;

      // Data sending after indication
    case APP_NETWORK_DATA_SENDING_STATE:
      // No packet is being currently forwarded by the device
      if (fwPacketFlag == false)
      {
        // Set payload value
        appPayload[APS_ASDU_OFFSET] = dataPayload;
        dataReq.asdu = (uint8_t *) &appPayload[APS_ASDU_OFFSET];
        // Start delay packet transmission timer
        delayFwTimer.interval = TIMER_FW_DELAY;
        delayFwTimer.mode     = TIMER_ONE_SHOT_MODE;
        delayFwTimer.callback = delayFwTimerFired;

        HAL_StartAppTimer(&delayFwTimer);
        appState = APP_WAITING_CONFIRM_STATE; // Switch application state
        fwPacketFlag = true; // Mark node as currently forwarding a packet
      }
      else
      {
        SYS_PostTask(APL_TASK_ID);
      }
      break;

      // Waiting confirm
    case APP_WAITING_CONFIRM_STATE:
      break;

    // Node is in network
    case APP_IN_NETWORK_STATE:
#ifndef _BUTTONS_
  #if APP_FINAL_DEVICE
        buttonReleased(DATA_TX_BUTTON); // Button released event simulating.
  #endif // APP_FINAL_DEVICE == 1
#endif // _BUTTONS_
#if APP_USE_BINDING
      if (deferredPacket)  // does we have deferred packets?
      {
        deferredPacket = false;
        appState = APP_NETWORK_DATA_SENDING_STATE; // Switch application state
        SYS_PostTask(APL_TASK_ID);
      }
      break;
#endif //APP_USE_BINDING
    // Node is out of network
    case APP_NO_NETWORK_STATE:
      break;

#if APP_USE_BINDING
    case APP_DEVICE_FINDING_STATE:
      // find defices which are able to bind to me
      findDevices(currentCluster);
      break;
#endif

    default:
      break;
  }
}

/********************************************************************
  Description: ZDO_StartNetwork primitive confirmation was received.

  Parameters: confirmInfo - confirmation information

  Returns: nothing.
********************************************************************/
void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t *confirmInfo)
{
  // Network start/join was successful
  if (ZDO_SUCCESS_STATUS == confirmInfo->status)
  {
    HAL_StopAppTimer(&flashTimer); // Stop network led blinking
    appOnLed(NETWORK_LED); // Indicate successfull network start/join
    appSendLcdCmd(LCD_CMD_SYMB_ANTENNA_LEVEL_2);

    APS_RegisterEndpointReq(&endpointParams); // Register endpoint
    prepareMsgParams(); // Set basic data message parameters

#if APP_USE_BINDING
    appState = APP_DEVICE_FINDING_STATE;
#else
    appState = APP_IN_NETWORK_STATE; // Switch application state
#endif
  }

  SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description: Button release handler

  Parameters: buttonNumber - number of button being released

  Returns: nothing.
********************************************************************/
static void buttonReleased(uint8_t buttonNumber)
{
  // Start/join network request
  if ((APP_AWAITING_NETWORK_START_STATE == appState) && (NETWORK_BUTTON == buttonNumber))
  {
    startFlashTimer();
    appState = APP_NETWORK_STARTING_STATE; // Switch application state
    SYS_PostTask(APL_TASK_ID);
  }

  // Initialize data packet transmission
  else if ((DATA_TX_BUTTON == buttonNumber) &&
           (APP_IN_NETWORK_STATE == appState) &&
           (false == fwPacketFlag))
  {
    uint8_t data = 0; // Initial payload value
    fwPacketFlag = true; // Transmitting packet, disable packet forwarding

    appPayload[APS_ASDU_OFFSET] = data;
    dataReq.asdu = (uint8_t *) &appPayload[APS_ASDU_OFFSET];

    // Configure and start delay packet forwarding timer
    delayFwTimer.interval = TIMER_FW_DELAY;
    delayFwTimer.mode     = TIMER_ONE_SHOT_MODE;
    delayFwTimer.callback = delayFwTimerFired;
    HAL_StartAppTimer(&delayFwTimer);

    appState = APP_WAITING_CONFIRM_STATE; // Switch application state
  }
}

/********************************************************************
  Description: Confirmation of message received.
  Turn off data forwarding indication LED

  Parameters: confData - confirmation information

  Returns: nothing.
********************************************************************/
static void APS_DataConf(APS_DataConf_t *confData)
{
  // TODO: add status checking
  confData = confData;         // Unused parameter, warning prevention
  fwPacketFlag = false;      // Enable packet forwarding

  if (APS_SUCCESS_STATUS != confData->status)
  {
    appState = APP_NETWORK_DATA_SENDING_STATE;
    SYS_PostTask(APL_TASK_ID);
  }
  else
  {
    appOffLed(DATA_LED);    // Transmission completed, turn off indication
    appSendLcdCmd(LCD_CMD_SYMB_TRX_OFF);

    if (APP_WAITING_CONFIRM_STATE == appState)
      appState = APP_IN_NETWORK_STATE; // Switch application state
  }
}

/********************************************************************
  Description: Handler of aps data indication

  Parameters: indData - structure of incoming msg

  Returns: nothing.
********************************************************************/
void APS_DataInd(APS_DataInd_t *indData)
{
#if APP_USE_BINDING
  AppState_t oldState = appState;
  //if binding still not obtained
  if (APP_IN_NETWORK_STATE != appState)
  {
    deferredPacket = true; //defer paket until binding will be established
  }
#endif

  // Update payload value
  dataPayload = *(indData->asdu);

  if (DEVICE_TYPE_ROUTER == appDeviceType)
  {
    dataPayload += 1;
    appState = APP_NETWORK_DATA_SENDING_STATE;
  }
  else
  {
    dataPayload = 0;
#ifdef TEST_NETWORK
    appState = APP_SENDING_HEARTBEAT;
    usartSendHeartbeat();
#else
    appState = APP_NETWORK_DATA_SENDING_STATE;
#endif // TEST_NETWORK
  }

#if APP_USE_BINDING
  //if binding still not obtained
  if (deferredPacket)
  {
    appState = oldState; //do not change application state
  }
#endif

  SYS_PostTask(APL_TASK_ID);
}

/********************************************************************
  Description: Prepare common data request parameters

  Parameters: none.

  Returns: nothing.
********************************************************************/
void prepareMsgParams(void)
{
#if APP_USE_BINDING
  dataReq.dstAddrMode             = APS_NO_ADDRESS; // Use binding in place direct addressing
  dataReq.txOptions.acknowledgedTransmission = 0;//APP_USE_APS_ACK; // Whether ACKs on application level are used
  dataReq.clusterId               = currentCluster;
#else
  dataReq.dstAddrMode             = APS_SHORT_ADDRESS; // Use short (NWK) addressing
  dataReq.dstAddress.shortAddress = dstAddr;       // Destination NWK address
  dataReq.txOptions.acknowledgedTransmission = 1;//APP_USE_APS_ACK; // Whether ACKs on application level are used
  dataReq.clusterId               = 1;
#endif
  dataReq.dstEndpoint             = PINGPONG_ENDPOINT;       // Destination endpoint
  dataReq.profileId               = endpointParams.simpleDescriptor->AppProfileId;
  dataReq.srcEndpoint             = PINGPONG_ENDPOINT;
  dataReq.asduLength              = APP_PAYLOAD_SIZE;
  dataReq.radius                  = 0;
  dataReq.APS_DataConf            = APS_DataConf;  // Confirm callback function
}

/********************************************************************
  Description: update network status event handler

  Parameters: nwkParams - new network parameters

  Returns: nothing.
********************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  // Network is lost/left
  if (ZDO_NETWORK_LOST_STATUS == nwkParams->status)
  {
    startFlashTimer();
    appState = APP_NETWORK_STARTING_STATE;    // Switch application state

    SYS_PostTask(APL_TASK_ID);
  }
}

/********************************************************************
  Description: dummy wakeup event handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void ZDO_WakeUpInd(void)
{
}

/********************************************************************
  Description: dummy sleep event handler

  Parameters: none.

  Returns: nothing.
********************************************************************/
void ZDO_SleepInd(void)
{
}

#ifdef TEST_NETWORK
/********************************************************************
  Description: Init USART, register USART callbacks.

  Parameters: none.

  Returns: nothing.
********************************************************************/
static void usartInit(void)
{
  appUsartDescriptor.tty             = APP_USART_CHANNEL;
  appUsartDescriptor.mode            = USART_MODE_ASYNC;
  appUsartDescriptor.baudrate        = USART_BAUDRATE_38400;
  appUsartDescriptor.dataLength      = USART_DATA8;
  appUsartDescriptor.parity          = USART_PARITY_NONE;
  appUsartDescriptor.stopbits        = USART_STOPBIT_1;
  appUsartDescriptor.rxBuffer        = NULL;
  appUsartDescriptor.rxBufferLength  = 0;
  appUsartDescriptor.txBuffer        = NULL;
  appUsartDescriptor.txBufferLength  = 0;
  appUsartDescriptor.rxCallback      = NULL;
  appUsartDescriptor.txCallback      = usartWriteConf;
  appUsartDescriptor.flowControl     = USART_FLOW_CONTROL_NONE;

  HAL_OpenUsart(&appUsartDescriptor);
}

/********************************************************************
  Description: Send Heartbeat Signal To Usart

  Parameters: none

  Returns: nothing.
********************************************************************/
static void usartSendHeartbeat(void)
{
  static uint8_t heartbeat = '#';

  HAL_WriteUsart(&appUsartDescriptor, &heartbeat, 1);
}

/********************************************************************
  Description: Writing confirmation has been received.

  Parameters: none.

  Returns: nothing.
********************************************************************/
static void usartWriteConf(void)
{
  appState = APP_NETWORK_DATA_SENDING_STATE;
}
#endif // TEST_NETWORK

#if APP_USE_BINDING

static void zdpIeeeAddrResp(ZDO_ZdpResp_t *resp)
{
  ZDO_IeeeAddrResp_t *ieeeAddrResp = (ZDO_IeeeAddrResp_t *) &resp->respPayload.ieeeAddrResp;
  if (ZDO_SUCCESS_STATUS == resp->respPayload.status)
  {
    CS_ReadParameter(CS_UID_ID, &apsReq.srcAddr);
    apsReq.srcEndpoint = PINGPONG_ENDPOINT;
    apsReq.clusterId = currentCluster;
    apsReq.dstAddrMode = APS_EXT_ADDRESS;
    apsReq.dstAddr.extAddress = ieeeAddrResp->ieeeAddrRemote;
    apsReq.dstEndpoint = PINGPONG_ENDPOINT;
    APS_BindReq(&apsReq);
    if (APS_SUCCESS_STATUS == apsReq.confirm.status)
    {
      HAL_StopAppTimer(&flashTimer);
      appOnLed(BIND_LED); // Indicate successfull bind
      appState = APP_IN_NETWORK_STATE;
    }
    else
    {
      appState = APP_DEVICE_FINDING_STATE; //perform device finding again
    }
    SYS_PostTask(APL_TASK_ID);
  }
  else
  {
    doIEEEAddrReq(discoveredDevice); //perform IEEE request again
  }
}

void doIEEEAddrReq(ShortAddr_t nwkAddr)
{
  ZDO_IeeeAddrReq_t *ieeeAddrReq = &zdpReq.req.reqPayload.ieeeAddrReq;

  zdpReq.ZDO_ZdpResp = zdpIeeeAddrResp;
  zdpReq.reqCluster = IEEE_ADDR_CLID;

  ieeeAddrReq->nwkAddrOfInterest = nwkAddr;
  ieeeAddrReq->reqType = SINGLE_RESPONSE_REQUESTTYPE;
  ieeeAddrReq->startIndex = 0;

  ZDO_ZdpReq(&zdpReq);
}

static void zdpMatchDescResp(ZDO_ZdpResp_t *resp)
{
  ZDO_MatchDescResp_t *matchResp = &resp->respPayload.matchDescResp;

  if (ZDO_CMD_COMPLETED_STATUS == resp->respPayload.status)
  {
    if (matchesFound)
    {
      doIEEEAddrReq(discoveredDevice);
    }
    else
    {
      appState = APP_DEVICE_FINDING_STATE;
      SYS_PostTask(APL_TASK_ID);
    }
  }
  else if (ZDO_SUCCESS_STATUS != resp->respPayload.status)
  {
    appState = APP_DEVICE_FINDING_STATE;
    SYS_PostTask(APL_TASK_ID);
  }
  else
  {
    discoveredDevice = matchResp->nwkAddrOfInterest;
    matchesFound = true;
  }
}

static void findDevices(ClusterId_t cluster)
{
  startFlashTimer();

  // search device related vars
  ZDO_MatchDescReq_t *matchDescReq = &zdpReq.req.reqPayload.matchDescReq;

  matchesFound = false;

  zdpReq.ZDO_ZdpResp = zdpMatchDescResp;
  zdpReq.reqCluster = MATCH_DESCRIPTOR_CLID;

  matchDescReq->nwkAddrOfInterest = BROADCAST_SHORT_ADDRESS;
  matchDescReq->profileId = PINGPONG_PROFILE;

  matchDescReq->numInClusters = 1;
  matchDescReq->inClusterList[0] = cluster;
  ZDO_ZdpReq(&zdpReq);
}

#endif //_BINDING_

//eof pingpong.c
