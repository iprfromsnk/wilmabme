/**************************************************************************//**
  \file nwkRouteRequest.h

  \brief Route record command types and functions.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    28/09/07 V. Panov - Created.
    10/12/08 M. Gekk - Memory optimization.
******************************************************************************/
#ifndef _NWK_ROUTE_RECORD_H
#define _NWK_ROUTE_RECORD_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <nwk.h>
#include <nwkFrame.h>


/******************************************************************************
                   Types section
******************************************************************************/
BEGIN_PACK
typedef struct PACK _NwkRouteRecordFrame_t
{
  uint8_t                 relayCount;
  ShortAddr_t             relayList[1];
} NwkRouteRecordFrame_t;
END_PACK

typedef struct _NwkRouteRecordItem_t
{
  ShortAddr_t path[NWKC_ROUTE_RECORD_ITEM_SIZE];
  uint8_t     pathSize;
  bool        active;
} NwkRouteRecordItem_t;

typedef struct _NwkRouteRecordTable_t
{
  NwkRouteRecordItem_t table[NWKC_ROUTE_RECORD_TABLE_SIZE];
  uint8_t index;
} NwkRouteRecordTable_t;

typedef struct _NwkRouteRecord_t
{
  NwkRouteRecordTable_t table;
} NwkRouteRecord_t;


/******************************************************************************
  prototypes
******************************************************************************/
#if defined(_NWK_MANY_TO_ONE_) && (defined(_ROUTER_)||defined(_COORDINATOR_))
/******************************************************************************
  \brief Action when command received.
  \param payload - cmd payload.
  \param header  - nwk header.
  \param parse   - parsed header fields.
  \return 'true' if continue processing of command packet otherwise 'false'.
******************************************************************************/
bool nwkRouteRecordFrameInd(const uint8_t *const payload, 
  const NwkFrameHeader_t *const header, const NwkParseHeader_t *const parse);

void nwkRouteRecordConfirm(void);
void nwkRouteRecordRequest(ShortAddr_t dstAddr, NWK_DstAddrMode_t dstAddrMode);

NwkRouteRecordItem_t* nwkRouteRecordFindByDest(ShortAddr_t addr);

#else
#define nwkRouteRecordFrameInd  NULL
#endif /* _NWK_MANY_TO_ONE_ and (_ROUTER_ or_COORDINATOR_) */
#endif
/* eof nwkRouteRecord.h */
