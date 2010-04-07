/**************************************************************************//**
  \file nwkRouteRequest.h

  \brief Route request command types and functions.
 
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    17/09/07 V. Panov - Created.
    10/12/08 M. Gekk  - Optimization of NWK memory.
 ******************************************************************************/
#ifndef _NWK_ROUTE_REQUEST_H
#define _NWK_ROUTE_REQUEST_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>

/******************************************************************************
                               Types section
******************************************************************************/
#define CONST_COST 7

typedef enum _NwkRouteRequestManyToOneFlag_t {
  RR_NOT_MANY_TO_ONE                     = 0,
  RR_MANY_TO_ONE_SENDER_WITH_RRTABLE     = 1,
  RR_MANY_TO_ONE_SENDER_WITHOUT_RRTABLE  = 2,
} NwkRouteRequestManyToOneFlag_t;

BEGIN_PACK
typedef struct PACK _NwkRouteRequestOptions_t
{
  uint8_t reserved1  : 3;
  uint8_t manyToOne  : 2;
  uint8_t dstExt     : 1;
  uint8_t multicast  : 1;
  uint8_t reserved2  : 1;
} NwkRouteRequestOptions_t;

typedef struct PACK _NwkRouteRequestFrame_t
{
  union PACK 
  {
    NwkRouteRequestOptions_t   cmdOptions;
    uint8_t                    cmdOptionsByte;
  };
  uint8_t                    identifier;
  ShortAddr_t                dstAddr;
  uint8_t                    pathCost;
  ExtAddr_t                  dstExt;
} NwkRouteRequestFrame_t;
END_PACK

/******************************************************************************
  prototypes
******************************************************************************/
#if defined(_ROUTER_)||defined(_COORDINATOR_)
/******************************************************************************
//preparing nwk payload for route request
//route table items to process stored in global pointers
******************************************************************************/
void cmdRouteReqPrepareMacData(uint8_t *data);

/******************************************************************************
preparing mac request for route request frame
******************************************************************************/
void cmdRouteReqPrepareMacReq(MAC_DataReq_t *req);

/******************************************************************************
route request sent ready to 
******************************************************************************/
void cmdRouteReqConfirm(NWK_Status_t status);

/******************************************************************************
  \brief Action when command received.
  \brief payload - cmd payload.
  \brief header  - nwk header.
  \brief parse   - parsed header fields.
******************************************************************************/
bool nwkRouteReqFrameInd(const uint8_t *const payload, 
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

#else
#define nwkRouteReqFrameInd  NULL
#endif /* _ROUTER_ or_COORDINATOR_ */
#endif
/* eof nwkRouteRequest.h */
