/**************************************************************************//**
  \file nwkCommands.h

  \brief NWK commands header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    20/06/07 V. Panov - Created.
    28/04/09 M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_COMMANDS_H
#define _NWK_COMMANDS_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <mac.h>
#include <queue.h>
#include <nwkFrame.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Type of request to send command packet. */
typedef struct _NwkCommandReq_t
{
  /* Service field - for internal needs. */
  struct 
  { 
    void  *next; 
  } service;
  bool  noRoute : 1;
  uint8_t  retryCounter : 7;
  uint8_t  baseJitter;
  uint8_t  randomJitterMask;
  void  (*prepareMacData)(uint8_t *data);
  void  (*prepareMacReq)(MAC_DataReq_t *req);
  void  (*confirm)(NWK_Status_t status);
}  NwkCommandReq_t;

/* Internal variables of the commands component. */
typedef struct _NwkCommands_t
{
  QueueDescriptor_t   queue;  /* Queue of requests from NWK components. */
} NwkCommands_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Request to perform outgoing command (outgoing frame allocated in data buffer)
  \param req - command request's parameters
 ******************************************************************************/
void  nwkCommandReq(NwkCommandReq_t *const req);

/**************************************************************************//**
 \brief Action when any command received
 \param payload - cmd payload (with ID)
 \param header  - nwk header
 \param parse   - parsed header fields
 \return 'true' if continue command processing otherwise 'false'.
******************************************************************************/
bool nwkCommandInd(const uint8_t *const payload, const NwkFrameHeader_t *const header, 
  const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Reset the commands component.
 ******************************************************************************/
void  nwkResetCommands(void);

#endif /* _NWK_COMMANDS_H */
/* eof nwkCommands.h */

