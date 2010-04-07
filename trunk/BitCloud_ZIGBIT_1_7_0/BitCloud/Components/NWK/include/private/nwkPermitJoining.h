/*************************************************************************//**
  \file  nwkPermitJoining.h

  \brief NWK permit joining header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    27/06/07 V. Panov - Created.
    10/12/08 M. Gekk  - Reduction of usage of the RAM at separate compiling
 *****************************************************************************/
#if !defined _NWK_PERMIT_JOINING_H
#define _NWK_PERMIT_JOINING_H

/*****************************************************************************
                             Includes section
 *****************************************************************************/
#include <types.h>
#include <nwk.h>
#include <queue.h>
#include <nwkConfig.h>

/*****************************************************************************
                               Types section
 *****************************************************************************/
/* Internal states of NLME-PERMIT_JOINING component */
typedef enum _NwkPermitJoiningStates_t
{
  NWK_PERMIT_JOINING_IDLE_STATE   = 0x48,
  NWK_PERMIT_JOINING_WAIT_TIMER_FIRED_STATE = 0x4A,
  NWK_PERMIT_JOINING_BEGIN_STATE  = 0x5D,
  NWK_PERMIT_JOINING_CONFIRM_STATE  = 0x5E,
  NWK_PERMIT_JOINING_TIMER_FIRED_STATE  = 0x5F,
  NWK_PERMIT_JOINING_SET_ASSOC_PERMIT_STATE = 0x60
} NwkPermitJoiningState_t;

/* Internal parameters of NLME-PERMIT-JOINING component. */
typedef struct _NwkPermitJoining_t
{
  NwkPermitJoiningState_t  state;
  QueueDescriptor_t  queue;
  MAC_SetReq_t  macReq;
  NWK_PermitJoiningReq_t  *req;
#if defined(NWK_PJ_TIMER_SUPPORT)
  HAL_AppTimer_t  timer;
#endif  
} NwkPermitJoining_t;

/*****************************************************************************
                         Inline functions section
 *****************************************************************************/
#if defined(_ROUTER_) || defined(_COORDINATOR_)
/*************************************************************************//**
  \brief  Task handler of the NLME-PERMIT-JOINING component.
 *****************************************************************************/
void nwkPermitJoiningTaskHandler(void);

/*************************************************************************//**
  \brief  Reset the NLME-PERMIT-JOINING component.
 *****************************************************************************/
void nwkResetPermitJoining(void);

#else
#define nwkPermitJoiningTaskHandler NULL
#define nwkResetPermitJoining NULL
#endif /* _ROUTER_ or _COORDINATOR_ */
#endif /* _NWK_PERMIT_JOINING_H */
/* eof nwkPermitJoining.h */
