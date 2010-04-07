/**************************************************************************//**
  \file nwkTaskManager.h

  \brief Header file of NWK task manager.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/06/07 V. Panov - Created.
    21/08/08 Max Gekk - More fair planning of tasks.
    12/06/09 Max Gekk - Refactoring
******************************************************************************/
#if !defined _NWK_TASK_MANAGER_H
#define  _NWK_TASK_MANAGER_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include <types.h>

/******************************************************************************
                            Definitions section
 ******************************************************************************/
/* List of NWK task handlers */
#define NWK_TASKS_LIST                    \
{                                         \
  {nwkResetTaskHandler},                  \
  {nwkSyncTaskHandler},                   \
  {nwkAddrConflictTaskHandler},           \
  {nwkDataReqTaskHandler},                \
  {nwkRouteDiscoveryTaskHandler},         \
  {nwkRouteDiscoveryTableTaskHandler},    \
  {nwkStartRouterTaskHandler},            \
  {nwkPermitJoiningTaskHandler},          \
  {nwkDiscoveryTaskHandler},              \
  {nwkFormationTaskHandler},              \
  {nwkJoinReqTaskHandler},                \
  {nwkJoinIndTaskHandler},                \
  {nwkLeaveTaskHandler},                  \
  {nwkEDScanTaskHandler},                 \
  {nwkDataConfTaskHandler}                \
}

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Identifiers of NWK task handlers. */
typedef enum  _NwkTaksID_t
{
  NWK_TASK_RESET,
  NWK_TASK_SYNC,
  NWK_TASK_ADDR_CONFLICT,
  NWK_TASK_DATA_REQ,
  NWK_TASK_ROUTE_DISCOVERY,
  NWK_TASK_ROUTE_DISCOVERY_TABLE,
  NWK_TASK_START_ROUTER,
  NWK_TASK_PERMIT_JOINING,
  NWK_TASK_DISCOVERY_REQ,
  NWK_TASK_FORMATION_REQ,
  NWK_TASK_JOIN_REQ,
  NWK_TASK_JOIN_IND,
  NWK_TASK_LEAVE,
  NWK_TASK_EDSCAN,
  NWK_TASK_DATA_CONF,
  NWK_TASKS_SIZE
}  NwkTaskID_t;

/* Bit array of NWK task. If bit is '1' the task is posted. */
typedef uint16_t NwkTaskBitMask_t;

typedef struct _NwkTaskManager_t
{
  NwkTaskBitMask_t taskBitMask;
} NwkTaskManager_t;

/******************************************************************************
                            Prototypes section
 ******************************************************************************/
/******************************************************************************
  \brief post NWK task.
  \param taskID - identifier of NWK task.
 ******************************************************************************/
void nwkPostTask(NwkTaskID_t taskID);

/******************************************************************************
  \brief Reset the task manager.
 ******************************************************************************/
void nwkResetTaskManager(void);

#endif /* _NWK_TASK_MANAGER_H */
/* eof nwkTaskManager.h */
