/**************************************************************************//**
  \file  nwkSyncLoss.h

  \brief SyncLoss header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    02/04/09 M. Gekk - Created.
 ******************************************************************************/
#ifndef _NWKSYNCLOSS_H
#define _NWKSYNCLOSS_H

/******************************************************************************
                                 Includes section
 ******************************************************************************/
#include <nwk.h> 
#include <nwkConfig.h> 

/******************************************************************************
                                   Types section
 ******************************************************************************/
/* Internal states of SyncLoss component */
typedef enum _NwkSyncLossState_t
{
  NWK_SYNC_LOSS_IDLE_STATE  = 0x00,
  NWK_REALIGNMENT_START_STATE = 0x01
} NwkSyncLossState_t;

/* Internal parameters of SyncLoss */
typedef struct _NwkSyncLoss_t
{
  NwkSyncLossState_t  state;
  NWK_StartRouterReq_t  startRouter;
} NwkSyncLoss_t;

/******************************************************************************
                                 Prototypes section
 ******************************************************************************/
#if defined(_ROUTER_) && defined(NWK_COORD_REALIGNMENT)
/******************************************************************************
  \brief Reset SyncLoss component.
 ******************************************************************************/
void nwkResetSyncLoss(void);

#else
#define nwkResetSyncLoss  NULL
#endif /* _ROUTER_ && NWK_COORD_REALIGNMENT */ 
#endif /* _NWKSYNCLOSS_H */ 

