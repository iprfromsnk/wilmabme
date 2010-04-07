/**************************************************************************//**
  \file  nwkDiscovery.h

  \brief Discovery header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 S. Vladykin - Created.
    10/12/08 M. Gekk     - Reduction of the used RAM.
    06/04/09 M. Gekk     - Refactoring
 ******************************************************************************/
#if !defined _NWK_DISCOVERY_H
#define _NWK_DISCOVERY_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include  <queue.h>
#include  <nwk.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Internal states of NLME-NETWORK-DISCOVERY component */
typedef enum _NwkDiscoveryState_t
{
  NWK_DISCOVERY_IDLE_STATE  = 0xD6,
  NWK_DISCOVERY_BEGIN_STATE = 0x70,
  NWK_DISCOVERY_MAC_SCAN_STATE = 0x71,
  NWK_DISCOVERY_CONFIRM_STATE = 0x72
} NwkDiscoveryState_t;

/* Internal parameters of NLME-NETWORK-DISCOVERY */
typedef struct _NwkDiscovery_t
{
  NwkDiscoveryState_t  state;  /* finite-state machine */
  QueueDescriptor_t  queue;  /* Queue of requests from upper layer */
} NwkDiscovery_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Main task handler of NLME-NETWORK-DISCOVERY component
 ******************************************************************************/
void nwkDiscoveryTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-NETWORK-DISCOVERY component
 ******************************************************************************/
void nwkResetDiscovery(void);

#endif  /* _NWK_DISCOVERY_H */
/* eof nwkDiscovery.h */
