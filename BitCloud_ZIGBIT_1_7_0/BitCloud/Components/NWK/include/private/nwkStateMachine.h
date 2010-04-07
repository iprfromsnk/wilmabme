/**************************************************************************//**
  \file nwkStateMachine.h

  \brief State machine header file.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 V. Panov - Created.
    21/02/09 M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_STATE_MACHINE_H
#define _NWK_STATE_MACHINE_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <types.h>
#include <nwkCommon.h>
#include <nwkMem.h>

/******************************************************************************
                                  Types section
 ******************************************************************************/
typedef  enum  _NwkStateMachineModuleID_t
{
  NWK_MODULE_ID_DATA_REQ      = (1u << 0),
  NWK_MODULE_ID_SYNC          = (1u << 1),
  NWK_MODULE_ID_LINK_STATUS   = (1u << 2),
  NWK_MODULE_ID_JOIN_IND      = (1u << 3),
  NWK_MODULE_ID_NETWORK_COMMAND = (1u << 4),
  NWK_MODULE_ID_LEAVE         = (1u << 5),
  NWK_MODULE_ID_PANID_CONFLICT  = (1u << 6),
  NWK_MODULE_ID_DATA_IND      = (1u << 7),
  NWK_MODULE_ID_DISCOVERY     = (1u << 8),
  NWK_MODULE_ID_FORMATION     = (1u << 9),
  NWK_MODULE_ID_JOIN_REQ      = (1u << 10),
  NWK_MODULE_ID_COMMAND_REQ   = (1u << 11),
  NWK_MODULE_ID_COMMAND_IND   = (1u << 12),
  NWK_MODULE_ID_EDSCAN        = (1u << 13),
  NWK_MODULE_ID_START_ROUTER  = (1u << 14),
  NWK_MODULE_ID_ADDR_CONFLICT = (1u << 15)
} NwkStateMachineModuleID_t;

typedef NwkState_t NwkStateMachineEvent_t;

/* Module permitions */
#define NWK_EVENT_RESET_REQ \
  (NWK_MODULE_ID_DISCOVERY | NWK_MODULE_ID_FORMATION \
  | NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ | NWK_MODULE_ID_COMMAND_IND)
#define NWK_EVENT_FORMATION_SUCCESS (~NWK_MODULE_ID_FORMATION)
#define NWK_EVENT_JOIN_SUCCESS (~NWK_MODULE_ID_FORMATION)
#define NWK_EVENT_LEAVE_ALL_CHILDREN \
  (~NWK_MODULE_ID_JOIN_IND & ~NWK_MODULE_ID_FORMATION & ~NWK_MODULE_ID_START_ROUTER)
#define NWK_EVENT_LEAVE_SUCCESS (NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ)
#define NWK_EVENT_LEAVE_FAIL NWK_EVENT_JOIN_SUCCESS
#define NWK_EVENT_REJOIN_REQ \
  (NWK_MODULE_ID_JOIN_REQ | NWK_MODULE_ID_COMMAND_REQ \
  | NWK_MODULE_ID_COMMAND_IND | NWK_MODULE_ID_DISCOVERY)
#define NWK_EVENT_REJOIN_SUCCESS (~NWK_MODULE_ID_FORMATION)
#define NWK_EVENT_POWER_FAILURE_RESET (NWK_EVENT_FORMATION_SUCCESS | NWK_EVENT_JOIN_SUCCESS)
#define NWK_EVENT_EDSCAN 0 /* disable all nwk modules */

/******************************************************************************
                          Inline functions section
******************************************************************************/
/**************************************************************************//**
  \brief this function return true, if module with moduleID is allowed to work.
 ******************************************************************************/
INLINE bool nwkCheckStateMachine(NwkStateMachineModuleID_t moduleID)
{
  return (nwkMem.state & moduleID)? true: false;
}

/**************************************************************************//**
  \brief Modules that can switch state machine shall send events.
  \param event - id of event
 ******************************************************************************/
INLINE void nwkSwitchStateMachine(NwkStateMachineEvent_t event)
{
  nwkMem.state = event;
}

/**************************************************************************//**
  \brief This function return the current state of network layer.
  \return current state
 ******************************************************************************/
INLINE NwkState_t nwkGetStateMachine(void)
{
  return nwkMem.state;
}

/**************************************************************************//**
 \brief Set new the network layer state.
 \param state - new state.
 \return current state
 ******************************************************************************/
INLINE void nwkRestoreStateMachine(NwkState_t state)
{
  nwkMem.state = state;
}

#endif /* _NWK_STATE_MACHINE_H */
/* eof nwkStateMachine.h */
