/**************************************************************************//**
  \file Peer2Peer.c 
  
  \brief Peer-2-peer sample application.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
******************************************************************************/

/******************************************************************************
                    Includes section
******************************************************************************/
#include <types.h>
#include <configServer.h>
#include <appTimer.h>
#include <zdo.h>
#include <peer2peer.h>
#include <serialInterface.h>

/******************************************************************************
                    Define(s) section
******************************************************************************/

/******************************************************************************
                    Variables section
******************************************************************************/
// Network related variables
static uint16_t nwkAddr;                        // Own NWK address
static AppMessageBuffer_t appMessageBuffer;     // Application message buffer
static uint8_t messageIdTx = 0;                 // Application transmitted message ID
static uint8_t messageIdRx = 0;                 // Application received message ID
static bool messageIdRxValid = false;           // Application received message ID valid flag
static uint8_t actualDataLength = 0;            // Actual data length to be transmitted via network   

// Temporary data received via network buffer
static uint8_t tmpDataBuffer[APP_TMP_DATA_BUFFER_SIZE];
static uint8_t tmpDataBufferActualLength = 0;   

// USART related variables
static HAL_UsartDescriptor_t appUsartDescriptor;          // USART descriptor (required by stack)
static bool usartTxBusyFlag = false;                     // USART transmission transaction status
static uint8_t usartTxBuffer[APP_USART_TX_BUFFER_SIZE];   // USART Tx buffer
static uint8_t usartRxBuffer[APP_USART_RX_BUFFER_SIZE];   // USART Rx buffer

static AppState_t appState = APP_INITIAL_STATE;  // application state
//application data transmission feature state
static AppDataTransmissionState_t appDataTransmissionState = APP_DATA_TRANSMISSION_READY_STATE;
static ZDO_StartNetworkReq_t networkParams; // request params for ZDO_StartNetworkReq
static APS_DataReq_t apsDataReq;

// endpoint parameters
static SimpleDescriptor_t simpleDescriptor = { APP_ENDPOINT, APP_PROFILE_ID, 1, 1, 0, 0 , NULL, 0, NULL };
static APS_RegisterEndpointReq_t endpointParams;

// Timer indicating starting network during network joining.
// Also used as delay timer between APS_DataConf and APS_DataReq.
static HAL_AppTimer_t delayTimer;

/***********************************************************************************
                    Static functions declarations section
***********************************************************************************/
static void APS_DataIndication(APS_DataInd_t* dataInd);
static void APS_DataConf(APS_DataConf_t* confInfo);
static void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t* confirmInfo);
static void initNetwork(void);
static void startNetwork(void);
static void networkSendData(bool newTransmission);
static void startBlinkTimer(void);
static void initSerialInterface(void);
static void sendDataToUsart(uint8_t*, uint8_t);
static void startingNetworkTimerFired(void);
static void delayTimerFired(void);
static void usartBytesReceived(uint16_t readBytesLen);
static void usartWriteConf(void);
static void buttonReleased(uint8_t buttons);

/***********************************************************************************
                    Implementation section
***********************************************************************************/
/**************************************************************************//**
  \brief Application task handler.
  
  \param  none.
  \return none.
******************************************************************************/
void APL_TaskHandler(void)
{
  switch (appState)
  { 
    case APP_INITIAL_STATE:                 // Node has initial state
      initSerialInterface();                // Open USART
      appOpenButtons(NULL, buttonReleased); // Open buttons
      appOpenLeds();                        // Enable LEDs   
      initNetwork();
      SYS_PostTask(APL_TASK_ID);            // Execute next step
      break;

    case APP_NETWORK_JOINING_STATE:
      startBlinkTimer();
      startNetwork();
      break;

    case APP_NETWORK_JOINED_STATE:
    default:
      break;
  }
}

/**************************************************************************//**
  \brief Intializes network parameters.
  
  \param  none.
  \return none.
******************************************************************************/
static void initNetwork(void)
{
  DeviceType_t  deviceType  = DEVICE_TYPE_ROUTER;
#ifndef _SLIDERS_
  // NWK preconfigured address reading for Config Server
  CS_ReadParameter(CS_NWK_ADDR_ID, &nwkAddr);
#else  //#ifndef _SLIDERS_
  // NWK address reading from sliders 
  nwkAddr = BSP_ReadSliders();
  // Set the NWK address value to Config Server
  CS_WriteParameter(CS_NWK_ADDR_ID, &nwkAddr);
#endif //#ifndef _SLIDERS_

  //NWK address value check
  if (APP_MAX_NWK_ADDR < nwkAddr)
  {
    appState = APP_ERROR_STATE;
  }
  else
  {
    // Node role detection. If nwkAddr == 0 then node is coordinator. 
    // In othe case the node role is router.
    if (0 == nwkAddr)   
    {
#ifdef _SECURITY_
      //Set coordinator uid equal to trust center address
      ExtAddr_t extAddr;
      CS_ReadParameter(CS_APS_TRUST_CENTER_ADDRESS_ID, &extAddr);
      CS_WriteParameter(CS_UID_ID, &extAddr);
#endif //_SECURITY_

      deviceType = DEVICE_TYPE_COORDINATOR;
    }
    // Set the deviceType value to Config Server
    CS_WriteParameter(CS_DEVICE_TYPE_ID, &deviceType);

    // Application state changing
    appState = APP_NETWORK_JOINING_STATE;
  }
}

/**************************************************************************//**
  \brief ZDO_StartNetwork primitive confirmation callback.
  
  \param  confirmInfo - confirmation parametrs.  
  \return none.
******************************************************************************/
void ZDO_StartNetworkConf(ZDO_StartNetworkConf_t* confirmInfo)
{
  HAL_StopAppTimer(&delayTimer); // Stop the blink timer

  if (confirmInfo->status == ZDO_SUCCESS_STATUS)
  {
    appState = APP_NETWORK_JOINED_STATE;
    actualDataLength = 0;
    messageIdRxValid = false;

    appOnLed(APP_NETWORK_STATUS_LED);

    // Setup timer to be used as delay timer between APS_DataConf and APS_DataReq.

    // Set application endpoint properties
    endpointParams.simpleDescriptor = &simpleDescriptor;
    endpointParams.APS_DataInd = APS_DataIndication;
    // Register endpoint
    APS_RegisterEndpointReq(&endpointParams);
  }
  else
  {
    SYS_PostTask(APL_TASK_ID);
  }
}

/**************************************************************************//**
  \brief Starts network.
  
  \param  none.
  \return none.
******************************************************************************/
static void startNetwork(void)
{
  networkParams.ZDO_StartNetworkConf = ZDO_StartNetworkConf;
  // start network
  ZDO_StartNetworkReq(&networkParams);   
}

/**************************************************************************//**
  \brief Starts Blink Timer based on HAL_AppTimer_t.
  
  \param  none.
  \return none.
******************************************************************************/
static void startBlinkTimer(void)
{
  delayTimer.interval = APP_JOINING_INDICATION_PERIOD;
  delayTimer.mode     = TIMER_REPEAT_MODE;
  delayTimer.callback = startingNetworkTimerFired;
  HAL_StartAppTimer(&delayTimer);
}

/**************************************************************************//**
  \brief Blink timer callback function.
  
  \param none.
  \return none.
******************************************************************************/
static void startingNetworkTimerFired(void)
{
  appToggleLed(APP_NETWORK_STATUS_LED);
}

/**************************************************************************//**
  \brief Update network status event handler.
  
  \param  nwkParams - new network parameters.
  \return none.
******************************************************************************/
void ZDO_MgmtNwkUpdateNotf(ZDO_MgmtNwkUpdateNotf_t *nwkParams)
{
  switch (nwkParams->status)
  {
    case ZDO_NETWORK_STARTED_STATUS:
      break;

    case ZDO_NETWORK_LOST_STATUS:
//    case ZDO_REJOIN_STARTED_STATUS:
      {
        APS_UnregisterEndpointReq_t unregEndpoint;  
        if (APP_NETWORK_JOINED_STATE == appState)
        {
          unregEndpoint.endpoint = endpointParams.simpleDescriptor->endpoint;
          APS_UnregisterEndpointReq(&unregEndpoint);    
        }
        appOffLed(APP_NETWORK_STATUS_LED);
  
        // try to rejoin the network
        appState = APP_NETWORK_JOINING_STATE;
        SYS_PostTask(APL_TASK_ID);
        break;  
      }        

    case ZDO_NWK_UPDATE_STATUS:
      break;

    default:
      break;
  }
}

/**************************************************************************//**
  \brief Wakeup event handler (dummy).
  
  \param  none.
  \return none.
******************************************************************************/
void ZDO_WakeUpInd(void)
{
}

/**************************************************************************//**
  \brief Sleep event handler (dummy).
  
  \param  none.
  \return none.
******************************************************************************/
void ZDO_SleepInd(void)
{
}

/**************************************************************************//**
  \brief Sends data to the network.
  
  \param newTransmission - new data transmission or retransmission

  \return none.
******************************************************************************/
static void networkSendData(bool newTransmission)
{
  if (APP_DATA_TRANSMISSION_READY_STATE == appDataTransmissionState)
  {
    appDataTransmissionState = APP_DATA_TRANSMISSION_BUSY_STATE;
    // indicate we're sending
    appOnLed(APP_SENDING_STATUS_LED);

    if (newTransmission)
    {
      // The new applicatiom message will be sent
      // messageId value 
      appMessageBuffer.message.messageId = messageIdTx++;
      // APS Data Request preparing
      apsDataReq.dstAddrMode = APS_SHORT_ADDRESS;               // Short addressing mode 
      // Destination address
      apsDataReq.dstAddress.shortAddress = (nwkAddr & 0xfffe) | ((~nwkAddr) & 0x01);
      apsDataReq.profileId = simpleDescriptor.AppProfileId;     // Profile ID
      apsDataReq.dstEndpoint = simpleDescriptor.endpoint;       // Desctination endpoint
      apsDataReq.clusterId = APP_CLUSTER_ID;                    // Desctination cluster ID
      apsDataReq.srcEndpoint = simpleDescriptor.endpoint;       // Source endpoint
      apsDataReq.asdu = (uint8_t*) &appMessageBuffer.message;   // application message pointer
      // actual application message length
      apsDataReq.asduLength = actualDataLength + sizeof(appMessageBuffer.message.messageId);
      apsDataReq.txOptions.acknowledgedTransmission = 1;        // Acknowledged transmission enabled
      apsDataReq.txOptions.fragmentationPermitted = APP_FRAGMENTATION_PERMITTED;
      apsDataReq.radius = 0;                                    // Default radius
      apsDataReq.APS_DataConf = APS_DataConf;                   // Confirm handler
    }

    // send data request
    APS_DataReq(&apsDataReq);
  }
}

/**************************************************************************//**
  \brief Handler of aps data sent confirmation.
  
  \param  confInfo - confirmation info
  \return none.
******************************************************************************/
void APS_DataConf(APS_DataConf_t* confInfo)
{
  appOffLed(APP_SENDING_STATUS_LED);

  if (APS_SUCCESS_STATUS != confInfo->status)
  {
    /* Data not delivered, resend. */
    appDataTransmissionState = APP_DATA_TRANSMISSION_READY_STATE;
    networkSendData(false); /* Current application message retransmission */
    return;
  }
  actualDataLength = 0;
#if 0 < APP_STOP_TRANSMISSION_DELAY
  appDataTransmissionState = APP_DATA_TRANSMISSION_STOP_STATE;
  
  delayTimer.interval = APP_STOP_TRANSMISSION_DELAY;
  delayTimer.mode     = TIMER_ONE_SHOT_MODE;
  delayTimer.callback = delayTimerFired;
  HAL_StartAppTimer(&delayTimer);
#else
  appDataTransmissionState = APP_DATA_TRANSMISSION_CONF_STATE;
  usartBytesReceived(0);
#endif
}

/**************************************************************************//**
  \brief Delay timer callback function.
  
  \param  none.
  \return none.
******************************************************************************/
static void delayTimerFired(void)
{
  if (APP_DATA_TRANSMISSION_STOP_STATE == appDataTransmissionState)
    appDataTransmissionState = APP_DATA_TRANSMISSION_CONF_STATE;    
  else
    appDataTransmissionState = APP_DATA_TRANSMISSION_READY_STATE;
  usartBytesReceived(0);
}
                
/**************************************************************************//**
  \brief APS data indication handler.
  
  \param  indData - received data.
  \return none.
******************************************************************************/
void APS_DataIndication(APS_DataInd_t* indData)
{
  AppMessage_t *appMessage = (AppMessage_t *) indData->asdu;

  // Data received indication
  appOnLed(APP_RECEIVING_STATUS_LED);

  if ((false == messageIdRxValid) ||
      (messageIdRx != appMessage->messageId))
  {
    messageIdRxValid = true;
    messageIdRx = appMessage->messageId;
    // write received data to USART
    sendDataToUsart(appMessage->data, indData->asduLength - 1);
  }
  appOffLed(APP_RECEIVING_STATUS_LED);
}

/**************************************************************************//**
  \brief Initializes USART or VCP (depends on user's settings).
  
  \param  none.
  \return none.
******************************************************************************/
static void initSerialInterface(void)
{
  usartTxBusyFlag = false;
  
  appUsartDescriptor.tty             = USART_CHANNEL;
  appUsartDescriptor.mode            = USART_MODE_ASYNC;
  appUsartDescriptor.baudrate        = USART_BAUDRATE_38400;
  appUsartDescriptor.dataLength      = USART_DATA8;
  appUsartDescriptor.parity          = USART_PARITY_NONE;
  appUsartDescriptor.stopbits        = USART_STOPBIT_1;
  appUsartDescriptor.rxBuffer        = usartRxBuffer;
  appUsartDescriptor.rxBufferLength  = sizeof(usartRxBuffer);
  appUsartDescriptor.txBuffer        = NULL; // use callback mode
  appUsartDescriptor.txBufferLength  = 0;
  appUsartDescriptor.rxCallback      = usartBytesReceived;
  appUsartDescriptor.txCallback      = usartWriteConf;
  appUsartDescriptor.flowControl     = USART_FLOW_CONTROL_HARDWARE;
  OPEN_USART(&appUsartDescriptor);
}

/**************************************************************************//**
  \brief Sends data to Usart.
  
  \param  data   - pointer to the frame to be sent via USART.
          length - length of the frame (bytes).
  \return none.
******************************************************************************/
static void sendDataToUsart(uint8_t* data, uint8_t length)
{
  if (APP_TMP_DATA_BUFFER_SIZE > tmpDataBufferActualLength + length)
  {
    memcpy(&tmpDataBuffer[tmpDataBufferActualLength], data, length);
    tmpDataBufferActualLength += length;
    // If there are no space in tmp Buffer for future messages receive
  }
   
  if (false == usartTxBusyFlag)
  {
    usartWriteConf();
  }
  
  // If there are no space in tmp Buffer for future messages receive
  if (APP_TMP_DATA_BUFFER_SIZE < tmpDataBufferActualLength + APP_MAX_DATA_SIZE)	
  {
    APS_StopEndpointIndication(APP_ENDPOINT); // Disable APS Data Indications
  }
}

/**************************************************************************//**
  \brief Writing confirmation has been received. New message can be sent.
  
  \param none.
  \return none.
******************************************************************************/
static void usartWriteConf(void)
{
  int bytesWritten;

  if (0 < tmpDataBufferActualLength)  // data waiting to be written to USART
  {
    memcpy(usartTxBuffer, tmpDataBuffer, tmpDataBufferActualLength);
    bytesWritten = WRITE_USART(&appUsartDescriptor, usartTxBuffer, tmpDataBufferActualLength);
    if (0 < bytesWritten)
    {
      tmpDataBufferActualLength -= bytesWritten;
      usartTxBusyFlag = true;
    }
  }
  else
  {
    usartTxBusyFlag = false;
    APS_ResumeEndpointIndication(APP_ENDPOINT); // Enable APS Data Indications
  }
}

/**************************************************************************//**
  \brief New USART bytes are received - HAL USART callback function.
  
  \param  bytesToRead - received bytes amount.
  \return none.
******************************************************************************/
static void usartBytesReceived(uint16_t bytesToRead)
{
  if (APP_NETWORK_JOINED_STATE != appState)
    return;
  if ((APP_DATA_TRANSMISSION_BUSY_STATE == appDataTransmissionState)
    || (APP_DATA_TRANSMISSION_STOP_STATE == appDataTransmissionState))
    return;

  if (actualDataLength < APP_MAX_DATA_SIZE)
  {
    actualDataLength += (uint8_t) READ_USART(&appUsartDescriptor, 
      appMessageBuffer.message.data + actualDataLength, 
      APP_MAX_DATA_SIZE - actualDataLength);
  }

#if 0 < APP_WAIT_OUTPUT_DATA_DELAY
  if (actualDataLength < APP_SIZE_OF_OUTPUT_DATA)
  {
    if (APP_DATA_TRANSMISSION_CONF_STATE == appDataTransmissionState)
    {
      appDataTransmissionState = APP_DATA_TRANSMISSION_WAIT_STATE;
      delayTimer.interval = APP_WAIT_OUTPUT_DATA_DELAY;
      delayTimer.mode     = TIMER_ONE_SHOT_MODE;
      delayTimer.callback = delayTimerFired;
      HAL_StartAppTimer(&delayTimer);      
      return;
    }
    if (APP_DATA_TRANSMISSION_WAIT_STATE == appDataTransmissionState)
      return;
  }
  else if (APP_DATA_TRANSMISSION_WAIT_STATE == appDataTransmissionState)
    HAL_StopAppTimer(&delayTimer);
#endif

  if (0 < actualDataLength)
  {
    appDataTransmissionState = APP_DATA_TRANSMISSION_READY_STATE;
    networkSendData(true);
  }
  (void)bytesToRead;    
}

/**************************************************************************//**
  \brief Button released event handler.
  
  \param  aButton - released button number
  \return none.
******************************************************************************/
static void buttonReleased(uint8_t aButton)
{
  switch (aButton)
  {
    case BSP_KEY0:  // SW1 pressed
      if ((APP_NETWORK_JOINED_STATE == appState) &&
          (APP_DATA_TRANSMISSION_READY_STATE == appDataTransmissionState))
      {
        // Fill the buffer with some data and send it
        memset(&appMessageBuffer.message.data, 0xdd, APP_MAX_DATA_SIZE);
        actualDataLength = APP_MAX_DATA_SIZE;
        networkSendData(true);
        break;
      }
      
    default:
      break;
  }
}

// eof peer2Peer.c
