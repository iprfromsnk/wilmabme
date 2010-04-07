/**************************************************************************//**
  \file  nwkRouteDiscovery.h

  \brief Network route discovery header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    05/09/07 V. Panov - Created.
    06/09/08 M. Gekk  - Modified to support parallel processing
 ******************************************************************************/
#if !defined _NWK_ROUTE_DISCOVERY_H
#define _NWK_ROUTE_DISCOVERY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>
#include <nwkRouteTable.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Internal states of the route discovery component. */
typedef enum _NwkRouteDiscoveryStates_t
{
  ROUTE_DISCOVERY_IDLE_STATE,
  ROUTE_DISCOVERY_REQUEST_STATE,
  ROUTE_DISCOVERY_CONFIRM_STATE,
} NwkRouteDiscoveryState_t;

typedef struct _NwkRouteDiscoveryObj_t
{
  NwkRouteDiscoveryState_t state;
  NWK_RouteDiscoveryReq_t  *req;
  uint32_t  timeout;
}   NwkRouteDiscoveryObj_t;

typedef struct _NwkRouteDiscovery_t
{
  unsigned  processTableInProgress  :1;
  unsigned  timerIsSet              :1;
  unsigned  reserved                :6;
  QueueDescriptor_t  queue;
  NwkCommandReq_t  commandReq;
  NwkRouteItem_t  *routeItem;
  NwkRouteDiscoveryItem_t  *routeDiscoveryItem;
  uint8_t  frameLength;
  uint8_t  objectsSize;
  NwkRouteDiscoveryObj_t  *objects;
  HAL_AppTimer_t  rreqTimeoutTimer;
} NwkRouteDiscovery_t;

/******************************************************************************
                           Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) || defined(_COORDINATOR_)
/**************************************************************************//**
  \brief Task handler of the route discovery component.
 ******************************************************************************/
void nwkRouteDiscoveryTaskHandler(void);

/**************************************************************************//**
  \brief Route discovery table task handler .
 ******************************************************************************/
void nwkRouteDiscoveryTableTaskHandler(void);

/******************************************************************************
  \brief Reset the route discovery component.
 ******************************************************************************/
void nwkResetRouteDiscovery(void);

/******************************************************************************
  \brief This function is called when route reply command for the given 
    node is received
******************************************************************************/
void nwkRouteReplyForThisNode(ShortAddr_t from);

#else
#define  nwkRouteDiscoveryTaskHandler  NULL
#define  nwkRouteDiscoveryTableTaskHandler  NULL
#define  nwkResetRouteDiscovery  NULL
#endif /* _ROUTER_ or _COORDINATOR_ */
#endif /* _NWK_ROUTE_DISCOVERY_H */
/* eof nwkRouteDiscovery.h */
