/**************************************************************************//**
  \file nwkStartRouter.h

  \brief Start router header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    27/06/07 V. Panov - Created.
    10/12/08 M. Gekk  - Reduction of usage of the RAM at separate compiling.
    19/03/09 N. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_START_ROUTER_H
#define _NWK_START_ROUTER_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Internal states of NLME-START-ROUTER component */
typedef enum _NwkStartRouterState_t
{
  NWK_START_ROUTER_IDLE_STATE = 0x9A,
  NWK_START_ROUTER_FIRST_STATE = 0x45,
  NWK_START_ROUTER_BEGIN_STATE  = NWK_START_ROUTER_FIRST_STATE,
  NWK_START_ROUTER_MAC_REQ_STATE  = 0x46,
  NWK_START_ROUTER_CONFIRM_STATE  = 0x47,
  NWK_START_ROUTER_LAST_STATE
} NwkStartRouterState_t;

/* Internal parameters of NLME-START-ROUTER */
typedef struct _NwkStartRouter_t
{
  NwkStartRouterState_t state; /* finite-state machine */
  QueueDescriptor_t queue; /* Queue of requests from upper layer */
  bool  coordRealignment;
} NwkStartRouter_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
#if defined _ROUTER_
/**************************************************************************//**
  \brief Is network configuration realignment allowed or not?
 ******************************************************************************/
bool nwkRealignmentIsAllowed(void);

/**************************************************************************//**
  \brief Main task handler of NLME-START-ROUTER component
 ******************************************************************************/
void nwkStartRouterTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-START-ROUTER component.
 ******************************************************************************/
void nwkResetStartRouter(void);

#else
#define nwkStartRouterTaskHandler  NULL
#define nwkResetStartRouter  NULL
#endif  /* _ROUTER_ */
#endif  /* _NWKSTARTROUTER_H */
/* eof nwkStartRouter.h */
