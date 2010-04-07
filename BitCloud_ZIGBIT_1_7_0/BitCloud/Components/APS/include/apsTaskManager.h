/*************************************************************************//**
  \file apsTaskManager.h

  \brief APS Task Manager header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    06/06/07 A. Potashov - Created
*****************************************************************************/


#ifndef _APSTASKMANAGER_H
#define _APSTASKMANAGER_H


/******************************************************************************
                   Includes section
******************************************************************************/
#include <apsComponentId.h>


/******************************************************************************
                   Define(s) section
******************************************************************************/
//Task descriptors table size
#define APS_TASK_TABLE_SIZE         (APS_MAX_COMPONENT_ID + 1)

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                   Constants section
******************************************************************************/

/******************************************************************************
                   External variables section
******************************************************************************/


/******************************************************************************
                   Prototypes section
******************************************************************************/

/*****************************************************************************
  Task Manager API
*****************************************************************************/

/*****************************************************************************
  Peforms APS sublayer processing
  Parameters: None
  Returns: None
*****************************************************************************/
void APS_TaskHandler(void);


/*****************************************************************************
  Perfoms request processor to specified APS task (appropriate component)
  Parameters: taskId - task ID
  Returns: None
*****************************************************************************/
void apsPostTask(ApsComponentId_t taskId);


/*****************************************************************************
  Perfoms reset of Task Manager as a whole
  Parameters: None
  Returns: None
*****************************************************************************/
void apsResetTaskManager(void);


/*****************************************************************************
  Perfoms initializing of Task Manager after switching from APS_STOP_STATE to
  APS_START_STATE
  Parameters: None
  Returns: None
*****************************************************************************/
void apsStartAfterStopTaskManager(void);
//============================================================================


/******************************************************************************
                   Inline static functions section
******************************************************************************/

#endif  //#ifndef _APSTASKMANAGER_H

//eof taskManager.h
