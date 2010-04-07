/**************************************************************************//**
  \file  nwkJoinReq.h

  \brief Join request header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 S. Vladykin - Created.
    10/12/08 M. Gekk     - Optimization of NWK memory.
    09/02/09 M. Gekk     - Refactoring
******************************************************************************/
#if !defined _NWK_JOINREQ_H
#define _NWK_JOINREQ_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <types.h>
#include <mac.h>
#include <nwk.h>
#include <queue.h>
#include <appTimer.h>
#include <nwkFrame.h>

/******************************************************************************
                                  Types section
 ******************************************************************************/
/* Internal states of the join request component. */
typedef enum _NwkJoinReqState_t
{
   JOIN_REQ_IDLE_STATE = 0xDA,
   JOIN_REQ_FIRST_STATE = 0x21,                   
   JOIN_REQ_GET_ELEM_FROM_QUEUE = JOIN_REQ_FIRST_STATE,
   JOIN_REQ_CONFIRM_STATE = 0x22,
   JOIN_REQ_ASSOCIATION_WAIT_STATE = 0x23,
   JOIN_REQ_SET_BEACON_PAYLOAD_STATE = 0x24,
   JOIN_REQ_SET_BEACON_PAYLOAD_LEN_STATE = 0x25,
   JOIN_REQ_SET_RX_ON_WHEN_IDLE_STATE = 0x26,
   JOIN_REQ_RX_ENABLE_STATE = 0x27,
   JOIN_REQ_PKT_PREPARE_AND_SEND_STATE = 0x28,
   JOIN_REQ_SET_PANID_STATE = 0x29,
   JOIN_REQ_SET_CHANNEL_STATE = 0x2A,
   JOIN_REQ_GET_RESPONSE_WAIT_TIME_STATE = 0x2B,
   JOIN_REQ_WAIT_REJOIN_RESPONSE_DECRYPT  = 0x2C,
   JOIN_REQ_REJOIN_RESPONSE_WAITING_STATE = 0x2D,
   JOIN_REQ_SET_SHORT_ADDRESS_STATE = 0x2E,
   JOIN_REQ_SET_COORD_SHORT_ADDR_STATE = 0x2F,
   JOIN_REQ_SET_COORD_EXT_ADDR_STATE = 0x30,
   JOIN_REQ_SET_SHORT_ADDRESS_ONLY_STATE = 0x31,
   JOIN_REQ_NETWORK_DISCOVERY_STATE = 0x32,
   JOIN_REQ_SET_FIRST_SHORT_ADDRESS_STATE = 0x33,
   JOIN_REQ_LAST_STATE
} NwkJoinReqState_t;

/* Format of rejoin command payload. ZigBee spec r17, 3.4.6.3, page 329. */
/* The NWK frame payload contains a command identifier field and a capability
 * information field. The command frame identifier shall contain the value
 * indicating a rejoin request command frame. */
BEGIN_PACK
typedef struct PACK
{
  uint8_t              commandId;
  /* This one-octet field has the format of the capability information field 
   * in the association request command. ZigBee spec r17, 3.4.6.3.1, page 329. */
  MAC_CapabilityInf_t  capability;
} NwkRejoinReqCmd_t;
END_PACK

/* Internal parameters of the join request component. */
typedef struct _NwkJoinReq_t
{
  NwkJoinReqState_t  state;
  QueueDescriptor_t  queue;
  NWK_JoinReq_t  *req;
  NwkNeighbor_t  *currentCandidateRouter;
  uint8_t  attempNum;
  HAL_AppTimer_t  timer;
  MAC_PollReq_t  pollReq;
  NwkCommandReq_t  rejoinCmd;
  union
  {
    MAC_AssociateReq_t  assocReq;
    MAC_SetReq_t  setReq;
    MAC_GetReq_t  getReq;
    MAC_RxEnableReq_t  rxEnableReq;
    NWK_NetworkDiscoveryReq_t  discReq;
  };
}  NwkJoinReq_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) || defined(_ENDDEVICE_)
/**************************************************************************//**
  \brief Action when command received.
  \param payload - a payload of network join request command.
  \param header - nwk header.
  \param parse  - parsed header fields.
  \return 'true' if continue processing of command packet otherwise 'false'.
******************************************************************************/
bool nwkRejoinResponseFrameInd(const uint8_t *const payload, 
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/**************************************************************************//**
  \brief Reset the join request component
 ******************************************************************************/
void nwkResetJoinReq(void);

/**************************************************************************//**
  \brief Task handler of NWK join request component.
 ******************************************************************************/
void nwkJoinReqTaskHandler(void);

#else 
#define nwkRejoinResponseFrameInd  NULL
#define nwkResetJoinReq  NULL
#define nwkJoinReqTaskHandler  NULL
#endif /* _ROUTER_ or _ENDDEVICE_ */
#endif /* _NWK_JOINREQ_H */
/* eof nwkJoinReq.h */
