/**********************************************************************//**
  \file USARTManager.c

  \brief

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    13/06/07 I. Kalganova - Modified
**************************************************************************/
#ifdef _COORDINATOR_

#include <types.h>
#include <usart.h>
#include <WSNDemoApp.h>
#include <WSNVisualizer.h>
#include <serialInterface.h>

typedef struct
{
  uint8_t payload[MAX_RAW_APP_MESSAGE_SIZE];
  uint8_t size;
} UsartMessage_t;


static struct
{
  UsartMessage_t usartMessageQueue[MAX_USART_MESSAGE_QUEUE_COUNT];
  bool isFreeUsart;
  uint8_t head,tail,size;
} wsn2usart;

static void readByteEvent(uint16_t readBytesLen);
static void writeConfirm(void);
static void sendNextMessage(void);
static HAL_UsartDescriptor_t usartDescriptor;
#if 0 != USART_RX_BUFFER_LENGTH
  static uint8_t rxBuffer[USART_RX_BUFFER_LENGTH];
#else
  static uint8_t *rxBuffer = NULL;
#endif

/***********************************************************************************
  Init USART, register USART callbacks.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
void appStartUsartManager(void)
{
  usartDescriptor.tty            = USART_CHANNEL;
  usartDescriptor.mode           = USART_MODE_ASYNC;
  usartDescriptor.flowControl    = USART_FLOW_CONTROL_NONE;
  usartDescriptor.baudrate       = USART_BAUDRATE_38400;
  usartDescriptor.dataLength     = USART_DATA8;
  usartDescriptor.parity         = USART_PARITY_NONE;
  usartDescriptor.stopbits       = USART_STOPBIT_1;
  usartDescriptor.rxBuffer       = rxBuffer;
  usartDescriptor.rxBufferLength = USART_RX_BUFFER_LENGTH;
  usartDescriptor.txBuffer       = NULL;
  usartDescriptor.txBufferLength = 0;
  usartDescriptor.rxCallback     = readByteEvent;
  usartDescriptor.txCallback     = writeConfirm;

  OPEN_USART(&usartDescriptor);

  memset(&wsn2usart, 0, sizeof(wsn2usart));
  wsn2usart.isFreeUsart = true;
}

void appStopUsartManager(void)
{
  CLOSE_USART(&usartDescriptor);
}

/***********************************************************************************
  New USART bytes were received.

  Parameters:
    readBytesLen - count of received bytes

  Return:
    none

 ***********************************************************************************/
static void readByteEvent(uint16_t readBytesLen)
{
  readBytesLen = readBytesLen;
}

/***********************************************************************************
  Send next message from queue.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
static void sendNextMessage(void)
{
  if (wsn2usart.size)
  {
    WRITE_USART(&usartDescriptor,
      wsn2usart.usartMessageQueue[wsn2usart.head].payload,
      wsn2usart.usartMessageQueue[wsn2usart.head].size
    );
  }
}

/***********************************************************************************
  Writing confirmation has been received. New message can be sent.

  Parameters:
    none

  Return:
    none

 ***********************************************************************************/
static void writeConfirm(void)
{
  if (wsn2usart.size)
  {
    wsn2usart.size--;
    if (++wsn2usart.head >= MAX_USART_MESSAGE_QUEUE_COUNT)
      wsn2usart.head -= MAX_USART_MESSAGE_QUEUE_COUNT;
  }
  wsn2usart.isFreeUsart = true;
  //send next message
  sendNextMessage();
}

/***********************************************************************************
  New message being sent into USART has to be put into queue.

  Parameters:
    newMessage - new message fields.

  Return:
    none

 ***********************************************************************************/
void appSendMessageToUsart(AppMessage_t *newMessage)
{
  UsartMessage_t *msg;
  uint8_t *p, *q, summ, i;
  q = (uint8_t *)newMessage;
  summ = 0;

  if (wsn2usart.size < MAX_USART_MESSAGE_QUEUE_COUNT)
  {
    wsn2usart.size++;
    msg = &wsn2usart.usartMessageQueue[wsn2usart.tail];
    if (++wsn2usart.tail >= MAX_USART_MESSAGE_QUEUE_COUNT)
      wsn2usart.tail -= MAX_USART_MESSAGE_QUEUE_COUNT;

    p = msg->payload;
    *p++ = 0x10;
    *p++ = 0x02;
    for (i = 0; i < sizeof(AppMessage_t); i++)
    {
      if (*q == 0x10)
      {
        *p++ = 0x10;
        summ += 0x10;
      }
      summ += *q;
      *p++ = *q++;
    }
    *p++ = 0x10;
    *p++ = 0x03;
    summ += 0x10 + 0x02 + 0x10 + 0x03;
    *p++ = summ;

    msg->size = p - msg->payload;
  }

  //check sending state
  if (true == wsn2usart.isFreeUsart)
  {
    sendNextMessage();
  }
}

#endif
//eof UARTManager.c
