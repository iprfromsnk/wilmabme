/************************************************************************//**
  \file zdoTaskManager.h

  \brief The header file describes the constants, types and internal interface
  of ZDO task manager

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
******************************************************************************/

#ifndef ZDOTASKMANAGER_H_
#define ZDOTASKMANAGER_H_

#include <inttypes.h>
#include <types.h>

typedef uint16_t ZDO_TaskMask_t;

typedef enum
{
  ZDO_STATEMACHINE_TASK_ID,
  ZDO_SECURITYMANAGER_TASK_ID,
  ZDO_ZDP_FRAME_PROCESSOR_TASK_ID,
  ZDO_ZDP_MANAGER_TASK_ID,
  ZDO_NETWORKMANAGER_TASK_ID,
  ZDO_DISCOVERYMANAGER_TASK_ID,
  ZDO_NODEMANAGER_TASK_ID,
  ZDO_BINDMANAGER_TASK_ID,
  ZDO_NUMBER_TASKHANDLERS // Not a real task
} ZDO_TaskID_t;

typedef struct
{
  void (*f)();
} ZdoTaskHandler_t;

extern void zdoStateMachineHandler(void);
extern void zdoSecurityManagerHandler(void);
extern void zdoZdpManagerHandler(void);
extern void zdoZdpFrameProcessorHandler(void);
extern void zdoPostTask(ZDO_TaskID_t);

#endif /*ZDOTASKMANAGER_H_*/
