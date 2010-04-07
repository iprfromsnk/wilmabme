/************************************************************************//**
  \file zdoPowerManager.h
  
  \brief The header file describes the constants, types and internal interface
  of ZDO power manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef _ZDOPOWERMANAGER_H
#define _ZDOPOWERMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/

#include <sleepTimer.h>
#include <nwk.h>
#include <zdo.h>
/******************************************************************************
                   Types section
******************************************************************************/

typedef enum SleepState_t_
{
  ZDO_IDLE_SLEEP_STATE,
  ZDO_SLEEPING_SLEEP_STATE
} SleepState_t;

typedef enum SyncState_t_
{
  ZDO_STOPPED_SYNC_STATE,
  ZDO_RUNNING_SYNC_STATE,
  ZDO_WAIT_SYNC_CONF_STATE,
} SyncState_t;

/*
 * Power manager variables
 * */
typedef struct
{
  SleepState_t        sleepState;
  SyncState_t         syncState;
  uint8_t             syncFailCounter;
  ZDO_SleepReq_t      *sleepReq;
  ZDO_WakeUpReq_t     *wakeUpReq;
  HAL_AppTimer_t      syncTimer;
  HAL_SleepTimer_t    sleepTimerHandler;
  NWK_SyncReq_t       zdoSyncReqParams; //indirect message request parameters
} ZdoPowerManager_t;

void zdoPowerManagerInit(void);
void zdoStartSyncReq(void);
void zdoStopSyncReq(void);

#endif /*ZDOPOWERMANAGER_H_*/
