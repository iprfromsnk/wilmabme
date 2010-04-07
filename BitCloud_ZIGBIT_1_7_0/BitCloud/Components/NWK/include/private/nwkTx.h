/**************************************************************************//**
  \file nwkTx.h

  \brief Data request header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/06/07 V. Panov - Created.
    10/12/08 M. Gekk  - Reduction of the used RAM.
 ******************************************************************************/
#ifndef _NWK_TX_H
#define _NWK_TX_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <nwk.h>
#include <appTimer.h>
#include <nwkRouting.h>
#include <nwkSystem.h>
#include <nwkStatusReq.h>
#ifdef _SECURITY_
#include <sspSfp.h>
#endif

/******************************************************************************
                                 Types section
 ******************************************************************************/
typedef enum _NwkDataReqState_t
{
  DATA_REQ_OBJ_FREE_STATE             = 0x00,
  DATA_REQ_OBJ_REQUEST_STATE          = 0x01,
  DATA_REQ_OBJ_ROUTING_DONE_STATE     = 0x02,
  DATA_REQ_OBJ_MACREQUEST_STATE       = 0x03,
  DATA_REQ_OBJ_MACREQUEST_REPEAT_STATE  = 0x04,
  DATA_REQ_OBJ_CONFIRMING_STATE       = 0x05,
  DATA_REQ_OBJ_DELAY_STATE            = 0x06,
  DATA_REQ_OBJ_USE_SOURCE_ROUTING     = 0x07,

  DATA_REQ_OBJ_RESERVED_STATE         = 0x08,
  DATA_REQ_OBJ_ROUTING_WAIT_STATE     = 0x09,
  DATA_REQ_OBJ_ENCRIPTING_STATE       = 0x0A,
  DATA_REQ_OBJ_WAIT_STATE             = 0x0B,
  DATA_REQ_OBJ_DECRIPTING_STATE       = 0x0C,
  DATA_REQ_OBJ_WAIT_TIMER_STATE       = 0x0D,
} NwkDataReqState_t;


typedef enum _NwkDataConfState_t
{
  NWK_DATA_CONF_FIRST_STATE = 0x01,
  NWK_DATA_CONF_IDLE_STATE = NWK_DATA_CONF_FIRST_STATE,
  NWK_DATA_CONF_PROCESS_STATE = 0x02,
  NWK_DATA_CONF_LAST_STATE    
}  NwkDataConfState_t;

typedef struct _NwkOutputPacket_t
{
  struct
  {
    void  *next;
  } service;
  NwkCommandReq_t  *commandReq;
  uint8_t  *data;
  uint8_t  length;
} NwkOutputPacket_t;


typedef struct _NwkDataReqObj_t
{
  NwkDataReqState_t state     :8;
  bool              fromNhle  :1;
  bool              transit   :1;
  bool              command   :1;
  bool              broadcast :1;
  bool              sourceRouted        :1;
  bool              decryptRequired     :1;
  Neib_t*           edToRebroadcast;
  uint8_t           retryCounter;
  MAC_DataReq_t     macDataReq;
  union {
    NWK_DataReq_t   *nwkDataReq;
    NwkOutputPacket_t *outPkt;
  };
  union 
  {
    NWK_RouteDiscoveryReq_t  routeDiscovery;
#if defined _SECURITY_
    SSP_EncryptFrameReq_t encryptReq;
    SSP_DecryptFrameReq_t decryptReq;
#endif /* _SECURITY_ */
  };
} NwkDataReqObj_t;

typedef struct _NwkDataReq_t
{
  QueueDescriptor_t queue, 
                    transitQueue,
                    commandQueue;
  NwkDataReqObj_t   *objects;
  uint8_t           objectsSize;
  uint8_t           maxRetryCounter;
  bool              statusReqActive :1;
  bool              timerActive     :1;
  unsigned          reserved        :6;
  HAL_AppTimer_t    delayTimer;
#if defined(_ROUTER_) || defined(_COORDINATOR_)
  NwkStatusReq_t  statusReq;
#endif
  
} NwkDataReq_t;

typedef struct _NwkDataConf_t
{
  NwkDataConfState_t  state;
  QueueDescriptor_t  queue;
}  NwkDataConf_t;

/******************************************************************************
                              Prototypes section
******************************************************************************/
void nwkTxReq(NWK_DataReq_t *const nwkDataReq);

void nwkTxTransitReq(NwkOutputPacket_t *outPkt);

void nwkTxCommandReq(NwkOutputPacket_t *outPkt);

void nwkTxCommandConf(NwkOutputPacket_t *const outPkt, const NWK_Status_t status);

void nwkResetDataReq(void);

void nwkDataReqTaskHandler(void);

void nwkDataReqFlushConfirms(void);

#endif
// eof dataRequest.h

