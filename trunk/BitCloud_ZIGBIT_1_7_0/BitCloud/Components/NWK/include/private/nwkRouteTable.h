/**************************************************************************//**
  \file  nwkRouteTable.h

  \brief Route table header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    17/09/07 V. Panov - Created.
 ******************************************************************************/
#ifndef _NWKROUTETABLE_H
#define _NWKROUTETABLE_H

/******************************************************************************
                                 Includes section
 ******************************************************************************/
#include <nwk.h>
#include <nwkAge.h>
#include <nwkConfig.h>

/******************************************************************************
                                  Types section
******************************************************************************/
typedef enum _NwkRouteTableStatus
{
  RDISCOVERY_ACTIVE,
  RDISCOVERY_DISCOVERY_UNDERWAY,
  RDISCOVERY_FAILED,
  RDISCOVERY_INACTIVE,
  RDISCOVERY_VALIDATION_UNDERWAY,
} NwkRouteTableStatus;

typedef struct _NwkRouteDiscoveryItem_t
{
//standard fields
  uint8_t          routeRequestId;
  ShortAddr_t      srcAddr;
  ShortAddr_t      senderAddr;
  uint8_t          forwardCost;
  uint8_t          residualCost;
//internal fields
  bool             routeRequestRequired : 1;
  bool             routeReplyRequired   : 1;
  unsigned         reserved             : 6;
  uint8_t          routeItemIndex;
  uint8_t          radius;
  NwkAgeItem_t     age;
} NwkRouteDiscoveryItem_t;

typedef struct _NwkRouteItem_t
{
  unsigned        status              : 3;
  unsigned        noRouteCache        : 1;
  unsigned        manyToOne           : 2;
  unsigned        routeRecordRequired : 1;
  unsigned        groupIdFlag         : 1;
  ShortAddr_t     dstAddr;
  ShortAddr_t     nextHopAddr;
  uint8_t         failCounter;
  NwkAgeItem_t    age;
} NwkRouteItem_t;

typedef struct NwkRouteDiscoveryTable_t 
{
  NwkRouteDiscoveryItem_t *table;
  uint8_t                 size;
  NwkAgeTable_t           age;
} NwkRouteDiscoveryTable_t;

typedef struct NwkRouteTable_t 
{
  NwkRouteItem_t  *table;
  uint8_t         size;
  uint8_t         routeReqId;
  NwkAgeTable_t   age;
} NwkRouteTable_t;


/******************************************************************************
                        Prototypes section
******************************************************************************/

/******************************************************************************
  reset routine
******************************************************************************/
void resetRouteTables(void);

/******************************************************************************
  find next hop using routing tables
dstAddr,dstAddrMode - address of destination
return: next hop address if it is found, or NWK_NO_SHORT_ADDR otherwise
******************************************************************************/
ShortAddr_t nwkFindNextHopMesh(ShortAddr_t dstAddr, uint8_t dstAddrMode, bool *routeRec);

/******************************************************************************
  get unique route request ID for new request
******************************************************************************/
uint8_t nwkRouteRequestId(void);

/******************************************************************************
  find item having process nedded flags set to true
******************************************************************************/
void nwkFindRouteItemsByState(NwkRouteItem_t          **item,
                              NwkRouteDiscoveryItem_t **discoveryItem
                             );

/******************************************************************************
  find route table item by given destination address
dstAddr - destination address
return: pointer to route table item
******************************************************************************/
NwkRouteItem_t* nwkFindRouteItem(ShortAddr_t dstAddr, bool group);

/******************************************************************************
  find route discovery table item by given 
item - route table item,
routeRequestId - request id and
srcAddr - originator of route request
return: pointer to route discovery table item
******************************************************************************/
NwkRouteDiscoveryItem_t* nwkFindRouteDiscoveryItem(NwkRouteItem_t *item, 
  uint8_t routeRequestId, ShortAddr_t srcAddr);

/******************************************************************************
  find free route table item 
return: pointer to route table item
******************************************************************************/
NwkRouteItem_t* nwkFindFreeRouteItem(void);

/******************************************************************************
  find free route discovery table item 
return: pointer to route table item
******************************************************************************/
NwkRouteDiscoveryItem_t* nwkFindFreeRouteDiscoveryItem(void);

/******************************************************************************
  link items of route table and route discovery table
discoveryItem - route discovery table item
item - route table item
******************************************************************************/
void nwkRouteDiscoveryItemLink(NwkRouteDiscoveryItem_t *discoveryItem, NwkRouteItem_t *item);

/******************************************************************************
  called periodically to correct aging of tables
******************************************************************************/
void nwkUpdateAgeRouteDiscovery(void);

/******************************************************************************
  remove on transmit error
******************************************************************************/
void nwkRouteTableNextHopFail(ShortAddr_t nextHop);
void nwkRouteTableNextHopSuccess(ShortAddr_t nextHop);

/******************************************************************************
  calc link cost avoiding overload
******************************************************************************/
uint8_t nwkRouteTableLinkCost(ShortAddr_t orig, ShortAddr_t macSrc);

/******************************************************************************
******************************************************************************/
NwkRouteDiscoveryItem_t* nwkOldestRouteDiscoveryItem(void);

/******************************************************************************
******************************************************************************/
void nwkRouteTableRemoveNextHop(ShortAddr_t nextHop);

/******************************************************************************
******************************************************************************/
void nwkRouteTableRemoveDest(ShortAddr_t dst);
void nwkUpdateRouteTable(ShortAddr_t nextHop, ShortAddr_t dstAddr, bool group, bool hardUpdate);

#endif //_NWKROUTETABLE_H
//eof nwkRouteTable.h
