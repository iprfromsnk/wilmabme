/**************************************************************************//**
  \file Peer2Peer.h
  
  \brief Peer-2-peer sample application header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:     
******************************************************************************/

#ifndef _PEER2PEER_H
#define _PEER2PEER_H

#if TEST_NETWORK
  #undef _SLIDERS_
  #undef _BUTTONS_
#endif // TEST_NETWORK

/******************************************************************************
                    Includes section
******************************************************************************/
#ifdef _SLIDERS_
  #include "sliders.h"
#endif // _SLIDERS_

#ifdef _LEDS_
  #include "leds.h"
#endif // _LEDS_

#ifdef _BUTTONS_
  #include "buttons.h"
#endif // _BUTTONS_

/******************************************************************************
                    Define(s) section
******************************************************************************/
#ifndef APP_USART_CHANNEL
  #define APP_USART_CHANNEL               USART_CHANNEL_1
#endif

#define APP_MAX_NWK_ADDR                  7    // Only 8 nodes are supported by application

#ifndef APP_JOINING_INDICATION_PERIOD
  #define APP_JOINING_INDICATION_PERIOD   500L // Period of blinking during starting network
#endif

// Temporary data received via network buffer size
// Note that temporary Buffer size should not exceed 255 bytes size because
// of USART HAL API limitations. HAL_WriteUsart function can get 
// only 255 bytes buffer length for transmission. 
#ifndef APP_TMP_DATA_BUFFER_SIZE   
  #define APP_TMP_DATA_BUFFER_SIZE        256
#endif

// USART Tx buffer size
#ifndef APP_USART_TX_BUFFER_SIZE   
  #define APP_USART_TX_BUFFER_SIZE        APP_TMP_DATA_BUFFER_SIZE
#endif

#define APP_ENDPOINT                      1    // Endpoint will be useed
#define APP_PROFILE_ID                    1    // Profile Id will be used
#define APP_CLUSTER_ID                    1    // Cluster Id will be used  

#define APP_STOP_TRANSMISSION_DELAY       20

#if defined APP_FRAGMENTATION

#define  APP_SIZE_OF_OUTPUT_DATA          100
#define  APP_MAX_DATA_SIZE                (APP_SIZE_OF_OUTPUT_DATA - 1)
#define  APP_WAIT_OUTPUT_DATA_DELAY       60
#define  APP_FRAGMENTATION_PERMITTED      1
#define  APP_USART_RX_BUFFER_SIZE         (APP_MAX_DATA_SIZE + APP_SIZE_OF_OUTPUT_DATA)

#else /* APP_FRAGMENTATION is not defined */

#define  APP_SIZE_OF_OUTPUT_DATA          64
#define  APP_MAX_DATA_SIZE                (APS_MAX_ASDU_SIZE - 1)
#define  APP_WAIT_OUTPUT_DATA_DELAY       0
#define  APP_FRAGMENTATION_PERMITTED      0
#define  APP_USART_RX_BUFFER_SIZE         100

#endif /* APP_FRAGMENTATION */

// Common application state definition
typedef enum
{
  APP_INITIAL_STATE,                           // Initial state
  APP_NETWORK_JOINING_STATE,                   // Attempting join network state
  APP_NETWORK_JOINED_STATE,                    // Successfull joined state (networking)
  APP_ERROR_STATE                              // Error state (runtime error occured)
} AppState_t;

// Network data transmission state
typedef enum
{
  APP_DATA_TRANSMISSION_READY_STATE,            // APS Data Request was not sent yet
  APP_DATA_TRANSMISSION_BUSY_STATE,             // APS Data Request was sent (confirm waiting)
  APP_DATA_TRANSMISSION_WAIT_STATE,             // Waiting a data block from USART
  APP_DATA_TRANSMISSION_CONF_STATE,             // Confirmation of APS data sending
  APP_DATA_TRANSMISSION_STOP_STATE              // Delay state for fall of transmission speed
} AppDataTransmissionState_t;

// Application network messsage descriptor
BEGIN_PACK
typedef struct
{
  uint8_t messageId;                           // message ID
  uint8_t data[APP_MAX_DATA_SIZE];         // actual data
} PACK AppMessage_t;
END_PACK

// Application network messsage buffer descriptor
BEGIN_PACK
typedef struct
{
  uint8_t header[APS_ASDU_OFFSET];                    // Auxiliary header (required by stack)
  AppMessage_t message;                               // Application message
  uint8_t footer[APS_AFFIX_LENGTH - APS_ASDU_OFFSET]; // Auxiliary footer (required by stack)
} PACK AppMessageBuffer_t;
END_PACK


// Leds aliases definition hardware platfor supported if
#ifdef _LEDS_
  #define APP_NETWORK_STATUS_LED            LED_GREEN   // Network status LED
  #define APP_RECEIVING_STATUS_LED          LED_YELLOW  // Data receiving status LED
  #define APP_SENDING_STATUS_LED            LED_RED     // Data transmission status LED
#endif // _LEDS_

#ifdef _LEDS_
  #define appOpenLeds() BSP_OpenLeds()
  #define appCloseLeds() BSP_CloseLeds()
  #define appOnLed(id) BSP_OnLed(id)
  #define appOffLed(id) BSP_OffLed(id)
  #define appToggleLed(id) BSP_ToggleLed(id)
#else
  #define appOpenLeds()
  #define appCloseLeds()
  #define appOnLed(id)
  #define appOffLed(id)
  #define appToggleLed(id)
#endif // _LEDS_

#ifdef _BUTTONS_
  #define appOpenButtons(pressed, released) BSP_OpenButtons(pressed, released)
  #define appCloseButtons() BSP_CloseButtons()
  #define appReadButtonsState() BSP_ReadButtonsState()
#else
#define appOpenButtons(pressed, released){(void)released;}
  #define appCloseButtons()
  #define appReadButtonsState() 0
  #define BSP_KEY0 0
#endif // _BUTTONS_

#endif // ifndef _PEER2PEER_H

// eof peer2peer.h
