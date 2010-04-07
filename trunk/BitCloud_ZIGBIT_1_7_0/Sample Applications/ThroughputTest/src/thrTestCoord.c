/**************************************************************************//**
  \file throughputTest.c
  
  \brief Calculates received data and prints it to UART.

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

static HAL_AppTimer_t trackPeriodTimer; // Timer for counting TIMER_TRACK_PERIOD
static uint32_t rcvdBitsAmount = 0;   // Amount of bits received during TIMER_TRACK_PERIOD

/***********************************************************************************
  Description: handler of trackPeriodTimer fire.
  
  Parameters: none.
  
  Returns: nothing.
***********************************************************************************/
static void trackPeriodTimerFired(void)
{
  static uint8_t msgBuf[] = "000 kbps\r\n"; // Buffer UART message
  
  appToggleLed(TIMER_LED); // Indicate end of track period

  printUint32(msgBuf, rcvdBitsAmount / 1000, 3);

  appWriteDataToUart(msgBuf, sizeof(msgBuf)-1);
  rcvdBitsAmount = 0; // Reset bites amount
}

/***********************************************************************************
  Description: process coordinator functionality. The function should be called
               only one time after starting network.
  
  Parameters: none.
  
  Returns: nothing.
***********************************************************************************/
void appCoordTaskHandler(void)
{
  // Configure and start track period timer
  trackPeriodTimer.interval = TIMER_TRACK_PERIOD;
  trackPeriodTimer.mode     = TIMER_REPEAT_MODE;
  trackPeriodTimer.callback = trackPeriodTimerFired;
  HAL_StartAppTimer(&trackPeriodTimer);
}

/***********************************************************************************
  Description: handler of aps data indication.
  
  Parameters: indData - received frame
  
  Returns: nothing.
***********************************************************************************/
void APS_DataIndCoord(APS_DataInd_t *indData)
{
  appToggleLed(DATA_RX_LED); // Indicate data reception
  rcvdBitsAmount += 8 * (indData->asduLength); // Increase received bits amount
}

// eof thrTestCoord.c 
