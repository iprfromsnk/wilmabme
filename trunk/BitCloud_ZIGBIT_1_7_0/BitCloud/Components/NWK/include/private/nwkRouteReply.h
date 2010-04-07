/**************************************************************************//**
  \file nwkRouteReply.h

  \brief Route reply command types and functions.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    17/09/07 V. Panov - Created.
 ******************************************************************************/
#ifndef _NWK_ROUTE_REPLY_H
#define _NWK_ROUTE_REPLY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
BEGIN_PACK
typedef struct PACK _NwkRouteReplyOptions_t
{
  uint8_t reserved1     : 4;
  uint8_t originatorExt : 1;
  uint8_t responderExt  : 1;
  uint8_t multicast     : 1;
  uint8_t reserved2     : 1;
} NwkRouteReplyOptions_t;

typedef struct PACK _NwkRouteReplyFrame_t
{
  union PACK
  {
    NwkRouteReplyOptions_t  cmdOptions;
    uint8_t                 cmdOptionsByte;
  };
  uint8_t                   identifier;
  ShortAddr_t               originatorAddr;
  ShortAddr_t               responderAddr;
  uint8_t                   pathCost;
  ExtAddr_t                 originatorExt;
  ExtAddr_t                 responderExt;
} NwkRouteReplyFrame_t;
END_PACK

/******************************************************************************
  prototypes
******************************************************************************/
#if defined(_ROUTER_)||defined(_COORDINATOR_)
/******************************************************************************
  \brief Action when command received.
  \param payload - cmd payload.
  \param header  - nwk header.
  \param parse   - parsed header fields.
******************************************************************************/
bool nwkRouteReplyFrameInd(const uint8_t *const payload, 
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

/******************************************************************************
callback, fill nwk payload of route reply cmd
******************************************************************************/
void cmdRouteReplyPrepareMacData(uint8_t *data);

/******************************************************************************
callback, fill mac request for route reply cmd
******************************************************************************/
void cmdRouteReplyPrepareMacReq(MAC_DataReq_t *req);

/******************************************************************************
callback, route reply sent, ready to send another command
******************************************************************************/
void cmdRouteReplyConfirm(NWK_Status_t status);

#else
#define  nwkRouteReplyFrameInd  NULL
#endif /* _ROUTER_ or _COORDINATOR_ */
#endif /* _NWK_ROUTE_REPLY_H */
/* eof nwkRouteReply.h */
