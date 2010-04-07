/**************************************************************************//**
  \file serilaInterface.h

  \brief Peer-2-peer sample application: header file contains serial interface
         definitions.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _SERIALINTERFACE_H
#define _SERIALINTERFACE_H

#include <usart.h>
#ifdef APP_USE_VCP
  #include <vcpVirtualUsart.h>
#endif // APP_USE_VCP

#ifdef APP_USE_USART
  #define OPEN_USART            HAL_OpenUsart
  #define CLOSE_USART           HAL_CloseUsart
  #define WRITE_USART           HAL_WriteUsart
  #define READ_USART            HAL_ReadUsart
  #define USART_CHANNEL         APP_USART_CHANNEL
#endif // APP_USE_UART

#ifdef APP_USE_VCP
  #define OPEN_USART            VCP_OpenUsart
  #define CLOSE_USART           VCP_CloseUsart
  #define WRITE_USART           VCP_WriteUsart
  #define READ_USART            VCP_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_VCP
#endif // APP_USE_VCP

#ifndef OPEN_USART
  #error USART interface is not defined.
#endif // OPEN_UART

#endif // _SERIALINTERFACE_H

// eof serialInterface.h
