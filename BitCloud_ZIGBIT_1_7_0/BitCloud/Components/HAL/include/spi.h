/****************************************************************************//**
  \file spi.h

  \brief The header file describes the USART SPI mode (for avr) and SPI1 bus (for arm).

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    29/05/08 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _SPI_H
#define _SPI_H

/******************************************************************************
                   Includes section
******************************************************************************/
#if defined(AT91SAM7X256)
  #include <halMemSpi.h>
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) || defined(ATMEGA128RFA1)
  #include <halSpi.h>
#endif

/******************************************************************************
                   Types section
******************************************************************************/
/** \brief Spi descriptor */
typedef struct
{
  /** \brief tty - SPI_CHANNEL_n to be used. "n" range depends on the platform.
  Take a look into halSpi.h platform specific file fore more details. */
  uint16_t tty;
  /** \brief SpiClockMode_t clockMode - spi clock mode (set by user). Must be chosen from: \n
    SPI_CLOCK_MODE0 \n
    SPI_CLOCK_MODE1 \n
    SPI_CLOCK_MODE2 \n
    SPI_CLOCK_MODE3 \n */
  SpiClockMode_t clockMode;
#if defined(AT91SAM7X256)
  /** \brief parameters are valid only for arm: */
  /** \brief symbol size (bits) (set by user). Must be set: \n
    SPI_8BITS_SYMBOL  \n
    SPI_9BITS_SYMBOL  \n
    SPI_10BITS_SYMBOL \n
    SPI_11BITS_SYMBOL \n
    SPI_12BITS_SYMBOL \n
    SPI_13BITS_SYMBOL \n
    SPI_14BITS_SYMBOL \n
    SPI_15BITS_SYMBOL \n
    SPI_16BITS_SYMBOL \n */
  SpiSymbolSize_t symbolSize;
  /** \brief Must be use macros HAL_SPI_PACK_PARAMETER(freq_value, valid_delay_value, cons_delay_value). \n
  Where is: \n
    freq_value        - spi frequency (Hz) \n
    valid_delay_value - delay between setting CS and clock start (sec) \n
    cons_delay_value  - delay between consecutive transfers (sec) \n */
  uint32_t pack_parameter;
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) || defined(ATMEGA128RFA1)
  /** \brief parameters are valid only for avr:*/
  /** \brief spi data order (set by user). Must be chosen from: \n
    SPI_DATA_MSB_FIRST \n
    SPI_DATA_LSB_FIRST \n */
  SpiDataOrder_t dataOrder;
  /** \brief spi clock rate (set by user). Must be chosen from: \n
    SPI_CLOCK_RATE_62  \n
    SPI_CLOCK_RATE_125 \n
    SPI_CLOCK_RATE_250 \n
    SPI_CLOCK_RATE_500 \n  */
  SpiBaudRate_t  baudRate;
  /** \brief HAL USART service field - contatins variables for HAL USART module
    internal needs */
  HAL_UsartDescriptor_t spiDescriptor;
#endif
  /** \brief address of the function to notify the application when a transmission was completed. \n
             When the synchronous method is used, callback must be NULL. \n */
  void (*callback)(void);
} HAL_SpiDescriptor_t;

/**************************************************************************//**
\brief Opens USART in MSPI mode(for avr) or opens SPI1(for arm).
\param[in]
  descriptor - pointer to spi descriptor
\return
   -1 - there are no free resources. \n
    0 - SPI channel is ready.
******************************************************************************/
int HAL_OpenSpi(HAL_SpiDescriptor_t *descriptor);

/**************************************************************************//**
\brief Releases the channel and pins.
\param[in]
  descriptor - pointer to spi descriptor
\return
  -1 - channel was not opened. \n
   0 - success.
******************************************************************************/
int HAL_CloseSpi(HAL_SpiDescriptor_t *descriptor);

/**************************************************************************//**
\brief Writes a number of bytes to the SPI.\n
 Callback function will be used to notify when the activity is finished. \n
\param[in]
  descriptor - pointer to HAL_SpiDescriptor_t structure
\param[in]
  buffer -  pointer to the application data buffer
\param[in]
  length -  number of bytes to transfer
\return
  -1 - spi module was not opened, or there is unsent data, or the pointer to
   data or the length are NULL; \n
   0 - success; \n
   Number of written bytes - success (synchronous mode).
******************************************************************************/
int HAL_WriteSpi(HAL_SpiDescriptor_t *descriptor, uint8_t *buffer, uint16_t length);

/**************************************************************************//**
\brief Writes a number of bytes to the SPI.\n
 Callback function will be used to notify when the activity is finished.\n
 The read data is placed to the buffer.
\param[in]
  descriptor - pointer to HAL_SpiDescriptor_t structure
\param[in]
  buffer -  pointer to the application data buffer
\param[in]
  length -  number of bytes to transfer
\return
  -1 - spi module was not opened, or there is unsent data, or the pointer to
   data or the length are NULL; \n
   0 - success; \n
   Number of written bytes - success (synchronous mode).
******************************************************************************/
int HAL_ReadSpi(HAL_SpiDescriptor_t *descriptor, uint8_t *buffer, uint16_t length);

#endif /* _SPI_H */
// eof spi.h
