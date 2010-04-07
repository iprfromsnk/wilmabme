/**************************************************************************//**
  \file  halTaslManager.h

  \brief Declarations of enums and functions of HAL task manager.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    10/12/07 A. Khromykh - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

#ifndef _HALTASKHANDLER_H
#define _HALTASKHANDLER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <taskManager.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/
#if defined(AT91SAM7X256)
/*! \brief task ID for hal task manager.  HAL_FIRST_X are free ID. */
enum
{
  HAL_USB_ENDPOINTS               = 1ul << 0,
  HAL_USB_SUSPEND                 = 1ul << 1,
  HAL_USB_RESUME                  = 1ul << 2,
  HAL_USB_BUS_RESET               = 1ul << 3,
  HAL_FIRST_4                     = 1ul << 4,
  HAL_FIRST_5                     = 1ul << 5,
  HAL_FIRST_6                     = 1ul << 6,
  HAL_FIRST_7                     = 1ul << 7,
  HAL_FIRST_8                     = 1ul << 8,
  HAL_FIRST_9                     = 1ul << 9,
  HAL_FIRST_10                    = 1ul << 10,
  HAL_FIRST_11                    = 1ul << 11,
  HAL_FIRST_12                    = 1ul << 12,
  HAL_FIRST_13                    = 1ul << 13,
  HAL_FIRST_14                    = 1ul << 14,
  HAL_FIRST_15                    = 1ul << 15,
  HAL_FIRST_16                    = 1ul << 16,
  HAL_FIRST_17                    = 1ul << 17,
  HAL_FIRST_18                    = 1ul << 18,
  HAL_FIRST_19                    = 1ul << 19,
  HAL_FIRST_20                    = 1ul << 20,
  HAL_FIRST_21                    = 1ul << 21,
  HAL_USART0_ERR                  = 1ul << 22,  /** uart0 received error is occurred*/
  HAL_USART0_RX                   = 1ul << 23,  /** uart0 byte is received */
  HAL_USART0_UDRE                 = 1ul << 24,  /** uart0 shift register is empty */
  HAL_USART0_TX                   = 1ul << 25,  /** uart0 byte is moved to shift register */
  HAL_FIRST_23                    = 1ul << 26,
  HAL_ADC                         = 1ul << 27,  /** adc measurement is ready */
  HAL_FIRST_24                    = 1ul << 28,
  HAL_FIRST_25                    = 1ul << 29,
  HAL_FIRST_26                    = 1ul << 30,
  HAL_FIRST_27                    = 1ul << 31
};

/*! \brief task ID for hal task manager.  HAL_SECOND_X are free ID. */
enum
{
  HAL_SECOND_1                    = 1ul << 0,
  HAL_USART1_ERR                  = 1ul << 1,  /** uart1 received error is occurred*/
  HAL_USART1_RX                   = 1ul << 2,  /** uart1 byte is received */
  HAL_USART1_UDRE                 = 1ul << 3,  /** uart1 shift register is empty */
  HAL_USART1_TX                   = 1ul << 4,  /** uart1 byte is moved to shift register */
  HAL_TWI                         = 1ul << 5,  /** twi bus interrupt is happened */
  HAL_SECOND_3                    = 1ul << 6,
  HAL_TIMER4_COMPA                = 1ul << 7,  /** timer interrupt is happened */
  HAL_SECOND_4                    = 1ul << 8,
  HAL_SECOND_5                    = 1ul << 9,
  HAL_SECOND_6                    = 1ul << 10,
  HAL_SECOND_7                    = 1ul << 11,
  HAL_SECOND_8                    = 1ul << 12,
  HAL_SECOND_9                    = 1ul << 13,
  HAL_SECOND_10                   = 1ul << 14,
  HAL_SECOND_11                   = 1ul << 15,
  HAL_USART0_TXBUFE               = 1ul << 16, /** uart0 dma buffer is empty */
  HAL_USART0_RXBUFF               = 1ul << 17, /** uart0 dma buffer is full */
  HAL_USART0_TIMEOUT              = 1ul << 18, /** uart0 dma timeout is happened */
  HAL_USART1_TXBUFE               = 1ul << 19, /** uart1 dma buffer is empty */
  HAL_USART1_RXBUFF               = 1ul << 20, /** uart1 dma buffer is full */
  HAL_USART1_TIMEOUT              = 1ul << 21, /** uart1 dma timeout is happened */
  HAL_SPI0_TXBUFE                 = 1ul << 22,  /** spi0 dma buffer is empty */
  HAL_SPI0_RXBUFF                 = 1ul << 23,  /** spi0 dma buffer is full */
  HAL_SPI1_TXBUFE                 = 1ul << 24,  /** spi1 dma buffer is empty */
  HAL_SPI1_RXBUFF                 = 1ul << 25,  /** spi1 dma buffer is full */
  HAL_SECOND_12                   = 1ul << 26,
  HAL_SECOND_13                   = 1ul << 27,
  HAL_SECOND_14                   = 1ul << 28,
  HAL_SECOND_15                   = 1ul << 29,
  HAL_SECOND_16                   = 1ul << 30,
  HAL_SECOND_17                   = 1ul << 31
};

#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) \
   || defined(ATXMEGA128A1) || defined(ATXMEGA256A3) || defined(ATMEGA128RFA1)
/**************************************************************************//**
  \brief halTaskFlags0 flags definitions.
******************************************************************************/
enum
{
  HAL_ASYNC_TIMER     = (uint8_t)1 << 0,
  HAL_SYNC_SLEEP_TIME = (uint8_t)1 << 1,
  HAL_EMPTY_TASK_0_2  = (uint8_t)1 << 2,
  HAL_EMPTY_TASK_0_3  = (uint8_t)1 << 3,
  HAL_EMPTY_TASK_0_4  = (uint8_t)1 << 4,
  HAL_EMPTY_TASK_0_5  = (uint8_t)1 << 5,
  HAL_EMPTY_TASK_0_6  = (uint8_t)1 << 6,
  HAL_EMPTY_TASK_0_7  = (uint8_t)1 << 7
};

/**************************************************************************//**
  \brief halTaskFlags1 flags definitions.
******************************************************************************/
enum
{
  HAL_EMPTY_TASK_1_0 = (uint8_t)1 << 0,
  HAL_EMPTY_TASK_1_1 = (uint8_t)1 << 1,
  HAL_EMPTY_TASK_1_2 = (uint8_t)1 << 2,
  HAL_EMPTY_TASK_1_3 = (uint8_t)1 << 3,
  HAL_EMPTY_TASK_1_4 = (uint8_t)1 << 4,
  HAL_EMPTY_TASK_1_5 = (uint8_t)1 << 5,
  HAL_EMPTY_TASK_1_6 = (uint8_t)1 << 6,
  HAL_EMPTY_TASK_1_7 = (uint8_t)1 << 7
};

/**************************************************************************//**
  \brief halTaskFlags2 flags definitions.
******************************************************************************/
enum
{
  HAL_EMPTY_TASK_2_0 = (uint8_t)1 << 0,
  HAL_EMPTY_TASK_2_1 = (uint8_t)1 << 1,
  HAL_EMPTY_TASK_2_2 = (uint8_t)1 << 2,
  HAL_EMPTY_TASK_2_3 = (uint8_t)1 << 3,
  HAL_EMPTY_TASK_2_4 = (uint8_t)1 << 4,
  HAL_EMPTY_TASK_2_5 = (uint8_t)1 << 5,
  HAL_EMPTY_TASK_2_6 = (uint8_t)1 << 6,
  HAL_TASK_USART     = (uint8_t)1 << 7
};

/**************************************************************************//**
  \brief halTaskFlags3 flags definitions.
******************************************************************************/
enum
{
  HAL_SM_ENCRYPT_REQ = (uint8_t)1 << 0,
  HAL_EMPTY_TASK_3_1 = (uint8_t)1 << 1,
  HAL_EMPTY_TASK_3_2 = (uint8_t)1 << 2,
  HAL_ADC            = (uint8_t)1 << 3,
  HAL_EE_READY       = (uint8_t)1 << 4,
  HAL_USB_ENDPOINTS  = (uint8_t)1 << 5,
  HAL_USB_SUSPEND    = (uint8_t)1 << 6,
  HAL_USB_RESUME     = (uint8_t)1 << 7
};

/**************************************************************************//**
  \brief halTaskFlags4 flags definitions.
******************************************************************************/
enum
{
  HAL_USB_BUS_RESET  = (uint8_t)1 << 0,
  HAL_EMPTY_TASK_4_1 = (uint8_t)1 << 1,
  HAL_WAKEUP         = (uint8_t)1 << 2,
  HAL_EMPTY_TASK_4_3 = (uint8_t)1 << 3,
  HAL_EMPTY_TASK_4_4 = (uint8_t)1 << 4,
  HAL_TWI            = (uint8_t)1 << 5,
  HAL_EMPTY_TASK_4_6 = (uint8_t)1 << 6,
  HAL_TIMER4_COMPA   = (uint8_t)1 << 7
};

/**************************************************************************//**
  \brief halTaskFlags5 flags definitions.
******************************************************************************/
enum
{
  HAL_EMPTY_TASK_5_0 = (uint8_t)1 << 0,
  HAL_EMPTY_TASK_5_1 = (uint8_t)1 << 1,
  HAL_EMPTY_TASK_5_2 = (uint8_t)1 << 2,
  HAL_EMPTY_TASK_5_3 = (uint8_t)1 << 3,
  HAL_EMPTY_TASK_5_4 = (uint8_t)1 << 4,
  HAL_EMPTY_TASK_5_5 = (uint8_t)1 << 5,
  HAL_EMPTY_TASK_5_6 = (uint8_t)1 << 6,
  HAL_SLEEP          = (uint8_t)1 << 7
};

#endif //defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284)...

/******************************************************************************
                   External variables section
******************************************************************************/
#if defined(AT91SAM7X256)
extern volatile uint32_t halTaskFlags0 ;
extern volatile uint32_t halTaskFlags1;
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) \
   || defined(ATXMEGA128A1) || defined(ATXMEGA256A3) || defined(ATMEGA128RFA1)
extern volatile uint8_t halTaskFlags0;
extern volatile uint8_t halTaskFlags1;
extern volatile uint8_t halTaskFlags2;
extern volatile uint8_t halTaskFlags3;
extern volatile uint8_t halTaskFlags4;
extern volatile uint8_t halTaskFlags5;
#endif //  defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284)...

/******************************************************************************
                   Inline static functions section
******************************************************************************/
#if defined(AT91SAM7X256)
/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 0
******************************************************************************/
INLINE void halPostTask0(uint32_t flag)
{
  halTaskFlags0 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 1
******************************************************************************/
INLINE void halPostTask1(uint32_t flag)
{
  halTaskFlags1 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}
#elif defined(ATMEGA1281) || defined(ATMEGA2561) || defined(ATMEGA1284) || defined(AT90USB1287) \
   || defined(ATXMEGA128A1) || defined(ATXMEGA256A3) || defined(ATMEGA128RFA1)
/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 0
******************************************************************************/
INLINE void halPostTask0(uint8_t flag)
{
  halTaskFlags0 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 1
******************************************************************************/
INLINE void halPostTask1(uint8_t flag)
{
  halTaskFlags1 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 2
******************************************************************************/
INLINE void halPostTask2(uint8_t flag)
{
  halTaskFlags2 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 3
******************************************************************************/
INLINE void halPostTask3(uint8_t flag)
{
  halTaskFlags3 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 4
******************************************************************************/
INLINE void halPostTask4(uint8_t flag)
{
  halTaskFlags4 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

/**************************************************************************//**
\brief Set task for task manager.

\param[in]
  flag task for task mask 5
******************************************************************************/
INLINE void halPostTask5(uint8_t flag)
{
  halTaskFlags5 |= flag;
  SYS_PostTask(HAL_TASK_ID);
}

#endif

#endif  /*_HALTASKHANDLER_H*/

// eof halTaskManager.h
