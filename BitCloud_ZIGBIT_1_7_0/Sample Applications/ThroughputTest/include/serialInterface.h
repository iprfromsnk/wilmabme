/*****************************************************************************//**
  \file serialInterface.h

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
******************************************************************************/
#ifndef _SERIALINTERFACE_H
#define _SERIALINTERFACE_H

#include <usart.h>
#ifdef APP_USE_VCP
  #include <vcpVirtualUsart.h>
#endif // APP_USE_VCP

#ifdef APP_USE_NONE
  INLINE int OPEN_USART(HAL_UsartDescriptor_t *descriptor)\
  {\
    (void)descriptor;\
    return 0;\
  }
  INLINE int CLOSE_USART(HAL_UsartDescriptor_t *descriptor)\
  {\
    (void)descriptor;\
    return 0;\
  }
  INLINE int WRITE_USART(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint16_t length)\
  {\
    (void)descriptor;\
    (void)buffer;\
    return length;\
  }
  INLINE int READ_USART(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint16_t length)\
  {\
    (void)descriptor;\
    (void)buffer;\
    (void)length;\
    return 0;\
  }
  #define USART_CHANNEL         0
  #define USART_RX_BUFFER_LENGTH 0
#endif // APP_USE_USART

#ifdef APP_USE_USART
  #define OPEN_USART            HAL_OpenUsart
  #define CLOSE_USART           HAL_CloseUsart
  #define WRITE_USART           HAL_WriteUsart
  #define READ_USART            HAL_ReadUsart
  #define USART_CHANNEL         APP_USART_CHANNEL
  #define USART_RX_BUFFER_LENGTH 0
#endif // APP_USE_USART

#ifdef APP_USE_VCP
  #define OPEN_USART            VCP_OpenUsart
  #define CLOSE_USART           VCP_CloseUsart
  #define WRITE_USART           VCP_WriteUsart
  #define READ_USART            VCP_ReadUsart
  #define USART_CHANNEL         USART_CHANNEL_VCP
  #define USART_RX_BUFFER_LENGTH 64
#endif // APP_USE_VCP

#ifndef USART_CHANNEL
  #error USART interface is not defined.
#endif // OPEN_USART

#endif // _SERIALINTERFACE_H

// eof serialInterface.h
