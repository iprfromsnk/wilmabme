/**************************************************************************//**
  \file  nwkFormation.h

  \brief Formation header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 S. Vladykin - Created.
    19/12/08 M. Gekk - Numbers are added to enum of state.
    24/03/09 M. Gekk - Refactoring 
 ******************************************************************************/
#if !defined _NWK_FORMATION_H
#define _NWK_FORMATION_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwk.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Internal states of NLME-NETWORK-FORMATION component */
typedef enum _NwkFormationState_t
{
  NWK_FORMATION_IDLE_STATE  = 0xB7,
  NWK_FORMATION_BEGIN_STATE = 0x54,
  NWK_FORMATION_MAC_REALIGNMENT_STATE = 0x55,
  NWK_FORMATION_MAC_ACTIVE_SCAN_STATE = 0x56,
  NWK_FORMATION_MAC_ED_SCAN_STATE = 0x57,
  NWK_FORMATION_CONFIRM_STATE = 0x58,
  NWK_FORMATION_SET_SHORT_ADDR_STATE  = 0x59,
  NWK_FORMATION_SET_BEACON_PAYLOAD_LEN_STATE  = 0x5A,
  NWK_FORMATION_SET_BEACON_PAYLOAD_STATE  = 0x5B,
  NWK_FORMATION_SET_RX_ON_WHEN_IDLE_STATE = 0x5C,
  NWK_FORMATION_MAC_START_STATE = 0x5D,
  NWK_FORMATION_RX_ENABLE_STATE = 0x5E
} NwkFormationState_t;

/* Internal parameters of NLME-NETWORK-FORMATION component. */
typedef struct _NwkFormation_t
{
  NwkFormationState_t state;  /* finite-state machine */
  QueueDescriptor_t   queue;  /* Queue of requests from upper layer */
  bool  coordRealignment;
} NwkFormation_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined(_COORDINATOR_)
/**************************************************************************//**
  \brief Main task handler of NLME-NETWORK-FORMATION component
 ******************************************************************************/
void nwkFormationTaskHandler(void);

/**************************************************************************//**
  \brief Reset NLME-NETWORK-FORMATION component
 ******************************************************************************/
void nwkResetFormation(void);

#else
#define nwkFormationTaskHandler  NULL
#define nwkResetFormation NULL
#endif   /* _COORDINATOR_ */
#endif   /* _NWK_FORMATION_H */
/* eof nwkFormation.h */
