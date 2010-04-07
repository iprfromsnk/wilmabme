/**************************************************************************//**
\file  usart.c

\brief USART implementation. Asynchronous mode.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/05/07 E. Ivanov - Created
    18/02/09 A. Luzhetsky - Corretced.
*******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <halDbg.h>
#include <usart.h>
#include <appTimer.h>
#include <halDiagnostic.h>
/******************************************************************************
                   Define(s) section
******************************************************************************/
#define HANDLERS_GET(A, I) memcpy_P(A, &halUsartHandlers[I], sizeof(HalUsartTask_t))
#define MIN_BUFFER_SIZE  8
#define BUFFER_RESERV    1
#define USART_HW_CONTROLLER_TIMER_PERIOD 10
#if defined(_USE_USART_ERROR_EVENT_)
  #define HAL_BM_FRAME_ERROR     (1 << 4)
  #define HAL_BM_DATA_OVERRUN    (1 << 3)
  #define HAL_BM_PARITY_ERROR    (1 << 2)
#endif

/******************************************************************************
                   Types definition section
******************************************************************************/
/**************************************************************************//**
  \brief HAL USART tasks bit mask.
******************************************************************************/
typedef volatile uint8_t HalUsartTaskBitMask_t;

/**************************************************************************//**
  \brief HAL USART task type declaration.
******************************************************************************/
typedef struct
{
  void (*task)(void);
} HalUsartTask_t;

/******************************************************************************
                   Global functions prototypes section
******************************************************************************/
int HAL_OpenUsart(HAL_UsartDescriptor_t *descriptor);
int HAL_CloseUsart(HAL_UsartDescriptor_t *descriptor);
int HAL_WriteUsart(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint16_t length);
int HAL_ReadUsart(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint16_t length);
int HAL_OnUsartCts(HAL_UsartDescriptor_t *descriptor);
int HAL_OffUsartCts(HAL_UsartDescriptor_t *descriptor);
int HAL_ReadUsartRts(HAL_UsartDescriptor_t *descriptor);
int HAL_ReadUsartDtr(HAL_UsartDescriptor_t *descriptor);
int HAL_IsTxEmpty(HAL_UsartDescriptor_t *descriptor);
void HAL_EnableDtrWakeUp(void (* callback)(void));
void HAL_DisableDtrWakeUp(void);
void halSigUsartHandler(void);
void halSetUsartConfig(HAL_UsartDescriptor_t *usartmode);
void halPostUsartTask(HalUsartTaskId_t taskId);
bool isChannelCorrect(uint16_t channel);
int8_t findDescriptor(HAL_UsartDescriptor_t* descriptor);
int8_t findChannel(uint16_t channel);
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  void hwControlPinsPollCallback(void);
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT


/******************************************************************************
                   Static function prototypes section
******************************************************************************/
#if defined(HAL_USE_USART_CHANNEL_0)
  static void halUsartTaskUsart0Dre(void);
  static void halUsartTaskUsart0Txc(void);
  static void halUsartTaskUsart0Rxc(void);
  #if defined(_USE_USART_ERROR_EVENT_)
    static void halUsartTaskUsart0Err(void);
  #endif
#endif

#if defined(HAL_USE_USART_CHANNEL_1)
  static void halUsartTaskUsart1Dre(void);
  static void halUsartTaskUsart1Txc(void);
  static void halUsartTaskUsart1Rxc(void);
  #if defined(_USE_USART_ERROR_EVENT_)
    static void halUsartTaskUsart1Err(void);
  #endif
#endif

static void halUsartHwController(uint8_t tty);
static void halSigUsartReceptionComplete(uint8_t tty);


/******************************************************************************
                   Static variables section
******************************************************************************/
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  static HAL_AppTimer_t halUsartAppTimer;
  static volatile uint8_t divider = 0;
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT
HAL_UsartDescriptor_t *halPointDescrip[NUM_USART_CHANNELS] =
{
  #if defined(HAL_USE_USART_CHANNEL_0)
    NULL,
  #endif
  #if defined(HAL_USE_USART_CHANNEL_1)
    NULL
  #endif
};
static volatile HalUsartTaskBitMask_t halUsartTaskBitMask = 0; // HAL USART tasks' bit mask.
static const HalUsartTask_t PROGMEM_DECLARE(halUsartHandlers[HAL_USART_TASKS_NUMBER]) =
{
  #if defined(HAL_USE_USART_CHANNEL_0)
    {halUsartTaskUsart0Dre},
    {halUsartTaskUsart0Txc},
    {halUsartTaskUsart0Rxc},
    #if defined(_USE_USART_ERROR_EVENT_)
      {halUsartTaskUsart0Err},
    #endif
  #endif

  #if defined(HAL_USE_USART_CHANNEL_1)
    {halUsartTaskUsart1Dre},
    {halUsartTaskUsart1Txc},
    {halUsartTaskUsart1Rxc},
    #if defined(_USE_USART_ERROR_EVENT_)
      {halUsartTaskUsart1Err},
    #endif
  #endif
}; // List Of possible HAL USART tasks.

/******************************************************************************
  DTR service
******************************************************************************/
volatile bool halEnableDtrWakeUp = false;
void (* dtrWakeUpCallback)(void) = NULL;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief  HAL USART task. Exact action depends on USART internal task.
******************************************************************************/
void halSigUsartHandler(void)
{
  HalUsartTask_t         handler;
  HalUsartTaskBitMask_t  mask = 1;
  HalUsartTaskId_t       index = 0;

  for ( ; index < HAL_USART_TASKS_NUMBER; index++, mask <<= 1)
  {
    if (halUsartTaskBitMask & mask)
    {
      ATOMIC_SECTION_ENTER
      halUsartTaskBitMask ^= mask;
      ATOMIC_SECTION_LEAVE
      HANDLERS_GET(&handler, index);
      (*handler.task)();
    }
  }
}

/**************************************************************************//**
\brief Posts specific USART task.

\param[in]
  taskId - unique identifier of the task to be posted.
******************************************************************************/
void halPostUsartTask(HalUsartTaskId_t taskId)
{
  halUsartTaskBitMask |= (HalUsartTaskBitMask_t)1 << taskId;
  halPostTask2(HAL_TASK_USART);
}

/**************************************************************************//**
\brief Puts the received byte to the cyclic buffer.

\param[in]
  tty - channel number.
\param[in]
  data - data to put.
******************************************************************************/
void halUsartRxBufferFiller(uint8_t tty, uint8_t data)
{
  uint16_t       old;
  int8_t         i;
  UsartControl_t *halUsartControl;

  i = findChannel(tty);
  if (-1 == i)
  {
    assert(false, USARTC_HALUSARTRXBUFFERFILLER_0);
    return; // Descriptor with "tty" channel is not found.
  }
  if (NULL == halPointDescrip[i])
  {// abnormal
    halDisableUsartRxcInterrupt(tty); // disable usart
    return;
  }

  if (halPointDescrip[i]->flowControl & USART_SPI_WRITE_MODE)
    return;

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  if (halPointDescrip[i]->flowControl & USART_SPI_READ_MODE)
  { // For spi mode.
    *(uint8_t*)(halPointDescrip[i]->rxBuffer) = data;
    halPointDescrip[i]->rxBuffer++;
    return;
  } // For spi mode.

  if (NULL != halPointDescrip[i]->rxBuffer)
  {
    old = halUsartControl->rxPointOfWrite;

    if (++halUsartControl->rxPointOfWrite == halPointDescrip[i]->rxBufferLength)
      halUsartControl->rxPointOfWrite = 0;

    if (halUsartControl->rxPointOfWrite == halUsartControl->rxPointOfRead)
    { // Buffer full.
      halUsartControl->rxPointOfWrite = old;
      return;
    } // Buffer full.

    halPointDescrip[i]->rxBuffer[old] = data;

#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
    if ((halPointDescrip[i]->flowControl & USART_FLOW_CONTROL_HARDWARE) && (HW_CONTROL_PINS_PORT_ASSIGNMENT == halPointDescrip[i]->tty))
    {
      uint16_t number = 0;

      if (halUsartControl->rxPointOfWrite > halUsartControl->rxPointOfRead)
        number = halUsartControl->rxPointOfWrite - halUsartControl->rxPointOfRead;
      else
        number = halPointDescrip[i]->rxBufferLength - (halUsartControl->rxPointOfRead - halUsartControl->rxPointOfWrite);

      if ((halPointDescrip[i]->rxBufferLength - number) < divider)
        GPIO_USART_CTS_set();// CTS_ON
    }
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT
  }
}

#if defined(_USE_USART_ERROR_EVENT_)
/**************************************************************************//**
\brief Save status register for analyzing of the error reason.

\param[in]
  tty - channel number.
\param[in]
  status - usart status register.
******************************************************************************/
void halUsartSaveErrorReason(uint8_t tty, uint8_t status)
{
  int8_t          i;
  UsartControl_t *halUsartControl;

  i = findChannel(tty);
  if (-1 == i)
  {
    assert(false, USARTC_HALUSARTSAVEERRORREASON);
    return; // Descriptor with "tty" channel is not found.
  }
  if (NULL == halPointDescrip[i])
  {// abnormal
    halDisableUsartRxcInterrupt(tty); // disable usart
    return;
  }

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  halUsartControl->errorReason = status;
}
#endif

/**************************************************************************//**
\brief Registers uasrt's event handlers. Performs configuration
of usart registers. Performs configuration of RTS, CTS and DTR pins.

\param[in]
  descriptor - pointer to HAL_UsartDescriptor_t structure

\return
  Returns positive usart descriptor on success or -1 in cases: \n
    - bad usart channel. \n
    - unsupported parameters. \n
    - the channel was already opened. \n
    - there are not enough resources. \n
******************************************************************************/
int HAL_OpenUsart(HAL_UsartDescriptor_t *descriptor)
{
  int8_t i; // Descriptor index

  if (0 == NUM_USART_CHANNELS)
    return -1; // User has not declared USART channels to be used.
  if (NULL == descriptor)
    return -1;
  if (false == isChannelCorrect(descriptor->tty))
    return -1;

#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  if ((descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE) && \
      (HW_CONTROL_PINS_PORT_ASSIGNMENT != descriptor->tty))
    return -1; // Hardware control cannot be used for this channel.
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

  if (-1 != findDescriptor(descriptor))
    return -1; // Channel is already opened.
  i = findDescriptor(NULL); // Find free descriptors array element.
  if (-1 == i)
    return -1; // There are no free descriptors.

  halPointDescrip[i] = descriptor;
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  if (HW_CONTROL_PINS_PORT_ASSIGNMENT == descriptor->tty)
  {
    if (descriptor->flowControl & USART_DTR_CONTROL)
      GPIO_USART_DTR_make_in();
    if (descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE)
    {
      GPIO_USART_CTS_make_out();
      GPIO_USART_RTS_make_in();
      if (NULL == descriptor->rxBuffer)
        GPIO_USART_CTS_set(); // CTS_ON
      else
      {
        if (descriptor->rxBufferLength >= MIN_BUFFER_SIZE)
          divider = descriptor->rxBufferLength >> BUFFER_RESERV;
        else
          divider = descriptor->rxBufferLength >> 2;
        GPIO_USART_CTS_clr(); // CTS_OFF
      }
    }
  }
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

  if (USART_MODE_SYNC == descriptor->mode)
  {
    if (USART_CLK_MODE_MASTER == descriptor->syncMode)
    {
      switch (descriptor->tty)
      {
#ifdef USART_CHANNEL_0
        case USART_CHANNEL_0:
          GPIO_USART0_EXTCLK_make_out();
          break;
#endif // USART_CHANNEL_0
#ifdef USART_CHANNEL_1
        case USART_CHANNEL_1:
          GPIO_USART1_EXTCLK_make_out();
          break;
#endif // USART_CHANNEL_1
        default:
          break;
      }
    }
    else
    {
      switch (descriptor->tty)
      {
#ifdef USART_CHANNEL_0
        case USART_CHANNEL_0:
          GPIO_USART0_EXTCLK_make_in();
          GPIO_USART0_EXTCLK_make_pullup();
          break;
#endif // USART_CHANNEL_0
#ifdef USART_CHANNEL_1
        case USART_CHANNEL_1:
          GPIO_USART1_EXTCLK_make_in();
          GPIO_USART1_EXTCLK_make_pullup();
          break;
#endif // USART_CHANNEL_1
        default:
        break;
      }
    }
  }

  descriptor->service.halUsartControl.txPointOfRead = 0;
  descriptor->service.halUsartControl.txPointOfWrite = 0;
  if (NULL == descriptor->rxBuffer)
    descriptor->rxBufferLength = 0;
  if (NULL == descriptor->txBuffer)
    descriptor->txBufferLength = 0;
  descriptor->service.halUsartControl.rxPointOfRead = 0;
  descriptor->service.halUsartControl.rxPointOfWrite = 0;
  descriptor->service.halUsartControl.usartShiftRegiaterEmpty = 1;

  halSetUsartConfig(descriptor);

  return descriptor->tty;
}

/**************************************************************************//**
\brief Frees the usart channel and pins, if hardware flow control was used.

\param[in]
  descriptor - the usart descriptor.
\return
   0 on success, \n
  -1 if bad descriptor.
******************************************************************************/
int HAL_CloseUsart(HAL_UsartDescriptor_t *descriptor)
{
  int8_t i;

  if (NULL == descriptor)
    return -1;
  if (false == isChannelCorrect(descriptor->tty))
    return -1;
  i = findDescriptor(descriptor);
  if (-1 == i)
    return -1; // descriptor is not found.

  halPointDescrip[i] = NULL;
  halCloseUsart(descriptor->tty);
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  if (descriptor->flowControl & USART_DTR_CONTROL)
  {
    GPIO_USART_DTR_make_in();
  }
  if (descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE)
  {
    GPIO_USART_CTS_make_in();
    GPIO_USART_RTS_make_in();
  }
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

  if (descriptor->syncMode & USART_CLK_MODE_MASTER)
  {
    switch (descriptor->tty)
    {
#ifdef USART_CHANNEL_0
      case USART_CHANNEL_0:
        GPIO_USART0_EXTCLK_make_in();
        break;
#endif // USART_CHANNEL_0
#ifdef USART_CHANNEL_1
      case USART_CHANNEL_1:
        GPIO_USART1_EXTCLK_make_in();
        break;
#endif // USART_CHANNEL_1
      default:
        break;
    }
  }

  return 0;
}

/**************************************************************************//**
\brief Controls RTS and DTR the pins and makes decision if the usart can transmit
 byte.

\param[in]
  tty - channel number.
******************************************************************************/
static void halUsartHwController(uint8_t tty)
{
  int8_t i;
  UsartControl_t *halUsartControl;

  i = findChannel(tty);
  if (-1 == i)
    return; // descriptor is not found.

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  if (HW_CONTROL_PINS_PORT_ASSIGNMENT == tty)
  {
    uint8_t hw1 = 0;
    uint8_t hw2 = 0;

    if (halPointDescrip[i]->flowControl & USART_DTR_CONTROL)
      hw1 = HAL_ReadUsartDtr(halPointDescrip[i]);

    if (halPointDescrip[i]->flowControl & USART_FLOW_CONTROL_HARDWARE)
      hw2 = HAL_ReadUsartRts(halPointDescrip[i]);

    if (hw1 || hw2)
    {
      halUsartAppTimer.interval = USART_HW_CONTROLLER_TIMER_PERIOD;
      halUsartAppTimer.mode = TIMER_ONE_SHOT_MODE;
      halUsartAppTimer.callback = hwControlPinsPollCallback;
      HAL_StartAppTimer(&halUsartAppTimer);
      return;
    }
  }
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

  if (halUsartControl->txPointOfWrite != halUsartControl->txPointOfRead)
  {
    halSendUsartByte(tty, halPointDescrip[i]->txBuffer[halUsartControl->txPointOfRead]);
    halUsartControl->txPointOfRead++;
    if (halUsartControl->txPointOfRead == halPointDescrip[i]->txBufferLength)
      halUsartControl->txPointOfRead = 0;
    halEnableUsartDremInterrupt(tty);
  }
  else
  {
    // data register empty interrupt was disabled
    halEnableUsartTxcInterrupt(tty);// TX Complete interrupt enable
  }
}

/**************************************************************************//**
\brief Writes a number of bytes to a usart channel.
txCallback function will be used to notify when the transmission is finished.
If hardware flow control is used for transmitting then RTS and DTR pins will
be tested during transmission.

\param[in]
  descriptor - pointer to HAL_UsartDescriptor_t structure;

\param[in]
  buffer - pointer to the application data buffer;

\param[in]
  length - number of bytes to transfer;

\return
  -1 - bad descriptor; \n
   Number of bytes placed to the buffer - success.
******************************************************************************/
int HAL_WriteUsart(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint16_t length)
{
  int8_t  i;
  uint16_t wasWrote = 0;
  bool    needStartTrmt = false;
  uint16_t old;
  UsartControl_t *halUsartControl;

  if (NULL == descriptor)
    return -1;
  if (false == isChannelCorrect(descriptor->tty))
    return -1;
  if (!buffer || !length)
    return -1;
  i = findDescriptor(descriptor);
  if (-1 == i)
    return -1; // Descriptor is not found.

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  if (0 == descriptor->txBufferLength)
  { // Callback mode
    if (halUsartControl->txPointOfWrite != halUsartControl->txPointOfRead)
      return -1; // there is unsent data
    halPointDescrip[i]->txBuffer = buffer;
    halUsartControl->txPointOfWrite = length;
    halUsartControl->txPointOfRead = 0;
    halEnableUsartDremInterrupt(descriptor->tty);
    return length;
  } // Callback mode.
  else
  { // Polling mode.
    ATOMIC_SECTION_ENTER
    BEGIN_MEASURE
    if (halUsartControl->txPointOfWrite == halUsartControl->txPointOfRead)
      needStartTrmt = true; // Buffer empty.

    while (wasWrote < length)
    {
      old = halUsartControl->txPointOfWrite;

      if (++halUsartControl->txPointOfWrite == halPointDescrip[i]->txBufferLength)
        halUsartControl->txPointOfWrite = 0;

      if (halUsartControl->txPointOfWrite == halUsartControl->txPointOfRead)
      { // Buffer full.
        halUsartControl->txPointOfWrite = old;
        break;
      } // Buffer full.

      halPointDescrip[i]->txBuffer[old] = buffer[wasWrote++];
    }

    if (needStartTrmt)
    {
      halUsartControl->usartShiftRegiaterEmpty = 0; // Buffer and shift register is full
      // Enable interrupt. Transaction will be launched in the callback.
      halEnableUsartDremInterrupt(halPointDescrip[i]->tty);
    }
    END_MEASURE(HALATOM_WRITE_USART_TIME_LIMIT)
    ATOMIC_SECTION_LEAVE

    return wasWrote;
  } // Polling mode
}

/*************************************************************************//**
\brief Reads length bytes from usart and places ones to buffer.

\param[in]
  descriptor - usart descriptor;
\param[out]
  buffer - pointer to a application buffer;
\param[in]
  length - the number of bytes which should be placed to buffer

\return
  -1 - bad descriptor, bad number to read or number of bytes that \n
  were placed to buffer.
*****************************************************************************/
int HAL_ReadUsart(HAL_UsartDescriptor_t *descriptor, uint8_t *buffer, uint16_t length)
{
  int8_t  i = 0;
  uint16_t wasRead = 0;
  UsartControl_t *halUsartControl;
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  uint16_t number;
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

  if (NULL == descriptor)
    return -1;
  if (false == isChannelCorrect(descriptor->tty))
    return -1;
  if (!buffer || !length)
    return -1;
  i = findDescriptor(descriptor);
  if (-1 == i)
    return -1; // descriptor is not found.

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  ATOMIC_SECTION_ENTER
  BEGIN_MEASURE
  while ((halUsartControl->rxPointOfRead != halUsartControl->rxPointOfWrite) && (wasRead < length))
  {
    buffer[wasRead] = halPointDescrip[i]->rxBuffer[halUsartControl->rxPointOfRead];
    if (++halUsartControl->rxPointOfRead == halPointDescrip[i]->rxBufferLength)
      halUsartControl->rxPointOfRead = 0;
    wasRead++;
  }

#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
  if ((HW_CONTROL_PINS_PORT_ASSIGNMENT == descriptor->tty) && (descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE))
  {
    if (halUsartControl->rxPointOfWrite != halUsartControl->rxPointOfRead)
    {
      if (halUsartControl->rxPointOfWrite > halUsartControl->rxPointOfRead)
        number = halUsartControl->rxPointOfWrite - halUsartControl->rxPointOfRead;
      else
        number = halPointDescrip[i]->rxBufferLength - (halUsartControl->rxPointOfRead - halUsartControl->rxPointOfWrite);

      if ((halPointDescrip[i]->rxBufferLength - number) >= divider)
        GPIO_USART_CTS_clr(); // CTS_OFF
    }
    else
      GPIO_USART_CTS_clr(); // CTS_OFF
  }
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT
  END_MEASURE(HALATOM_READ_USART_TIME_LIMIT)
  ATOMIC_SECTION_LEAVE

  return wasRead;
}

/**************************************************************************//**
\brief Forbids to the host data transmiting. Only HW_CONTROL_PINS_PORT_ASSIGNMENT
         port can be used for hardware flow control.

\param[in]
  descriptor - usart descriptor.

\return
  -1 - bad descriptor, bad usart, unsupported mode;
   0 - on success.
******************************************************************************/
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
int HAL_OnUsartCts(HAL_UsartDescriptor_t *descriptor)
{
  if (NULL == descriptor)
    return -1;

  if (HW_CONTROL_PINS_PORT_ASSIGNMENT != descriptor->tty)
    return -1;

  if (!(descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE))
    return -1;

  GPIO_USART_CTS_set();// CTS_ON

  return 0;
}
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

/**************************************************************************//**
\brief Allows to transfer a host data. Only HW_CONTROL_PINS_PORT_ASSIGNMENT
can be used for hardware flow control.

\param[in]
  descriptor - usart descriptor.

\return
  -1 - bad descriptor, bad usart, unsupported mode;
   0 - on success.
******************************************************************************/
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
int HAL_OffUsartCts(HAL_UsartDescriptor_t *descriptor)
{
  if (NULL == descriptor)
    return -1;

  if (HW_CONTROL_PINS_PORT_ASSIGNMENT != descriptor->tty)
    return -1;

  if (!(descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE))
    return -1;

  GPIO_USART_CTS_clr(); // CTS_OFF

  return 0;
}
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

/**************************************************************************//**
\brief Fills UsartHardwareControl_t variable by potential of RTS pin. Only
  HW_CONTROL_PINS_PORT_ASSIGNMENT can be used for hardware flow control.

\param[in]
  descriptor - usart descriptor.
\return
  -1 - bad descriptor, bad usart, unsupported mode;
   0 - on success.
******************************************************************************/
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
int HAL_ReadUsartRts(HAL_UsartDescriptor_t *descriptor)
{
  if (NULL == descriptor)
    return -1;

  if (HW_CONTROL_PINS_PORT_ASSIGNMENT != descriptor->tty)
    return -1;

  if (!(descriptor->flowControl & USART_FLOW_CONTROL_HARDWARE))
    return -1;

  return GPIO_USART_RTS_read();
}
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

/**************************************************************************//**
\brief Fills UsartHardwareControl_t variable by potential of DTR pin. Only
  HW_CONTROL_PINS_PORT_ASSIGNMENT can be used for hardware flow control.

\param[in]
  descriptor - usart descriptor.
\return
  -1 - bad descriptor, bad usart, unsupported mode;
   0 - on success.
******************************************************************************/
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
int HAL_ReadUsartDtr(HAL_UsartDescriptor_t *descriptor)
{
  if (NULL == descriptor)
    return -1;

  if (USART_CHANNEL_1 != descriptor->tty)
    return -1;

  if (!(descriptor->flowControl & USART_DTR_CONTROL))
    return -1;

  return GPIO_USART_DTR_read();
}
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

// Interrupt handlers
/**************************************************************************//**
\brief Hardware Control pins polling timer callback.
******************************************************************************/
#ifdef HW_CONTROL_PINS_PORT_ASSIGNMENT
void hwControlPinsPollCallback(void)
{
  halUsartHwController(HW_CONTROL_PINS_PORT_ASSIGNMENT);
}
#endif // HW_CONTROL_PINS_PORT_ASSIGNMENT

/**************************************************************************//**
\brief Transmission complete interrupt handler.

\param[in]
  tty - USART channel identifier.
******************************************************************************/
void halSigUsartTransmissionComplete(uint8_t tty)
{
  int8_t i;
  UsartControl_t *halUsartControl;

  i = findChannel(tty);
  if (-1 == i)
  {
    assert(false, USARTC_HALSIGUSARTTRANSMISSIONCOMPLETE_0);
    return; // Descriptor with "tty" channel is not found.
  }

  if (NULL == halPointDescrip[i])
    return; // Port closed.

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  if (halUsartControl->txPointOfWrite == halUsartControl->txPointOfRead)
    halUsartControl->usartShiftRegiaterEmpty = 1; // Buffer is empty, shift register is empty too.

  if (0 == halPointDescrip[i]->txBufferLength)
    halPointDescrip[i]->txBuffer = NULL; // nulling pointer for callback mode

  if (NULL != halPointDescrip[i]->txCallback)
    halPointDescrip[i]->txCallback();
}

/**************************************************************************//**
\brief Reception complete interrupt handler.

\param[in]
  tty - USART channel identifier.
******************************************************************************/
static void halSigUsartReceptionComplete(uint8_t tty)
{
  int8_t i;
  UsartControl_t *halUsartControl;
  uint16_t number;

  i = findChannel(tty);
  if (-1 == i)
  {
    assert(false, USARTC_HALSIGUSARTRECEPTIONCOMPLETE_0);
    return; // Descriptor with "tty" channel is not found.
  }
  if (NULL == halPointDescrip[i])
    return; // Port closed.

  if (halPointDescrip[i]->flowControl & (USART_SPI_READ_MODE | USART_SPI_WRITE_MODE))
    return; // for spi mode

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  if (halUsartControl->rxPointOfWrite != halUsartControl->rxPointOfRead)
  {
    ATOMIC_SECTION_ENTER
    BEGIN_MEASURE
    if (halUsartControl->rxPointOfWrite > halUsartControl->rxPointOfRead)
      number = halUsartControl->rxPointOfWrite - halUsartControl->rxPointOfRead;
    else
      number = halPointDescrip[i]->rxBufferLength - (halUsartControl->rxPointOfRead - halUsartControl->rxPointOfWrite);
    END_MEASURE(HALATOM_USART_RX_COMPLETE_TIME_LIMIT)
    ATOMIC_SECTION_LEAVE
    if (NULL != halPointDescrip[i]->rxCallback)
      halPointDescrip[i]->rxCallback(number);
  }
}

#if defined(_USE_USART_ERROR_EVENT_)
/**************************************************************************//**
\brief Error occurred action handler.

\param[in]
  tty - USART channel identifier.
******************************************************************************/
static void halSigUsartErrorOccurred(uint8_t tty)
{
  int8_t i;
  UsartControl_t *halUsartControl;
  UsartErrorReason_t errReason = FRAME_ERROR;

  i = findChannel(tty);
  if (-1 == i)
  {
    assert(false, USARTC_HALSIGUSARTERROROCCURED_0);
    return; // Descriptor with "tty" channel is not found.
  }
  if (NULL == halPointDescrip[i])
    return; // Port closed.

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  if (halUsartControl->errorReason & HAL_BM_FRAME_ERROR)
    errReason = FRAME_ERROR;
  else if (halUsartControl->errorReason & HAL_BM_DATA_OVERRUN)
    errReason = DATA_OVERRUN;
  else if (halUsartControl->errorReason & HAL_BM_PARITY_ERROR)
    errReason = PARITY_ERROR;
  else
  {
    assert(false, USARTC_HALUNKNOWNERRORREASON_0);
  }

  if (NULL != halPointDescrip[i]->errCallback)
    halPointDescrip[i]->errCallback(errReason);
}
#endif

/**************************************************************************//**
\brief Enables DTR wake up.

\param[in] callback - callback method pointer.
******************************************************************************/
void HAL_EnableDtrWakeUp(void (* callback)(void))
{
  dtrWakeUpCallback = callback;
  halEnableDtrWakeUp = true;
}

/**************************************************************************//**
\brief Disables DTR wake up.
******************************************************************************/
void HAL_DisableDtrWakeUp(void)
{
  halEnableDtrWakeUp = false;
}

/**************************************************************************//**
\brief Checks the status of tx buffer.

\param[in]
  descriptor - pointer to HAL_UsartDescriptor_t structure;

\return
  -1 - bad descriptor, no tx buffer; \n
   1 - tx buffer is empty; \n
   0 - tx buffer is not empty;
******************************************************************************/
int HAL_IsTxEmpty(HAL_UsartDescriptor_t *descriptor)
{
  int8_t i;
  UsartControl_t *halUsartControl;

  if (NULL == descriptor)
    return -1;
  if (false == isChannelCorrect(descriptor->tty))
    return -1;
  i = findDescriptor(descriptor);
  if (-1 == i)
    return -1; // descriptor is not found.

  halUsartControl = &halPointDescrip[i]->service.halUsartControl;
  if (halUsartControl->txPointOfWrite == halUsartControl->txPointOfRead)
    return halUsartControl->usartShiftRegiaterEmpty;
  return 0;
}

/**************************************************************************//**
\brief Checks the channel number.

\param[in]
  channel - channel to be verified.

\return
  true if channel is possible, \n
  false otherwise.
******************************************************************************/
bool isChannelCorrect(uint16_t channel)
{
  switch (channel)
  {
#ifdef USART_CHANNEL_0
    case USART_CHANNEL_0:
#endif // USART_CHANNEL_0
#ifdef USART_CHANNEL_1
    case USART_CHANNEL_1:
#endif // USART_CHANNEL_0
#if defined(USART_CHANNEL_0) || defined(USART_CHANNEL_1)
      return true;
#endif
    default:
      return false;
  }
}

/**************************************************************************//**
\brief Looks for HAL USART descriptor which is equal to descriptor.

\param[in]
  descriptor - USART descriptor to be found.

\return
  array element index if descriptor is found, \n
  -1 otherwise.
******************************************************************************/
int8_t findDescriptor(HAL_UsartDescriptor_t* descriptor)
{
  int8_t i;

  for (i = 0; i < NUM_USART_CHANNELS; i++)
    if (halPointDescrip[i] == descriptor)
      return i;
  return -1;
}

/**************************************************************************//**
\brief Looks for HAL USART descriptor with particular channel.

\param[in]
  channel - channel to be found.

\return
  array element index if channel is found, \n
  -1 otherwise.
******************************************************************************/
int8_t findChannel(uint16_t channel)
{
  int8_t i;

  for (i = 0; i < NUM_USART_CHANNELS; i++)
    if ((NULL != halPointDescrip[i]) && (halPointDescrip[i]->tty == channel))
      return i;
  return -1;
}

#if defined(HAL_USE_USART_CHANNEL_0)
/**************************************************************************//**
\brief Wrapper for data empty handler for usart channel 0
******************************************************************************/
static void halUsartTaskUsart0Dre(void)
{
  halUsartHwController(USART_CHANNEL_0);
}

/**************************************************************************//**
\brief Wrapper for transmit complete handler for usart channel 0
******************************************************************************/
static void halUsartTaskUsart0Txc(void)
{
  halSigUsartTransmissionComplete(USART_CHANNEL_0);
}

/**************************************************************************//**
\brief Wrapper for receive complete handler for usart channel 0
******************************************************************************/
static void halUsartTaskUsart0Rxc(void)
{
  halSigUsartReceptionComplete(USART_CHANNEL_0);
}

#if defined(_USE_USART_ERROR_EVENT_)
/**************************************************************************//**
\brief Wrapper for error occurred handler for usart channel 0
******************************************************************************/
static void halUsartTaskUsart0Err(void)
{
  halSigUsartErrorOccurred(USART_CHANNEL_0);
}
#endif // defined(_USE_USART_ERROR_EVENT_)
#endif // defined(HAL_USE_USART_CHANNEL_0)

#if defined(HAL_USE_USART_CHANNEL_1)
/**************************************************************************//**
\brief Wrapper for data empty handler for usart channel 1
******************************************************************************/
static void halUsartTaskUsart1Dre(void)
{
  halUsartHwController(USART_CHANNEL_1);
}

/**************************************************************************//**
\brief Wrapper for transmit complete handler for usart channel 1
******************************************************************************/
static void halUsartTaskUsart1Txc(void)
{
  halSigUsartTransmissionComplete(USART_CHANNEL_1);
}

/**************************************************************************//**
\brief Wrapper for receive complete handler for usart channel 0
******************************************************************************/
static void halUsartTaskUsart1Rxc(void)
{
  halSigUsartReceptionComplete(USART_CHANNEL_1);
}

#if defined(_USE_USART_ERROR_EVENT_)
/**************************************************************************//**
\brief Wrapper for error occurred handler for usart channel 1
******************************************************************************/
static void halUsartTaskUsart1Err(void)
{
  halSigUsartErrorOccurred(USART_CHANNEL_1);
}
#endif // defined(_USE_USART_ERROR_EVENT_)
#endif // defined(HAL_USE_USART_CHANNEL_1)
//eof usart.c
