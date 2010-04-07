/**************************************************************************//**
\file  bspTaskManager.c

\brief Implemenattion of BSP task manager.

\author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

\internal
  History:
    29/05/07 E. Ivanov - Created
******************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <bspTaskManager.h>
#include <atomic.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief BSP TII handler.
******************************************************************************/
void bspTIIhandler(void);
void swTIIhandler(void);

/******************************************************************************
                   Global variables section
******************************************************************************/
uint8_t bspTaskFlags0 = 0;

/******************************************************************************
                   Implementations section
******************************************************************************/
/**************************************************************************//**
\brief BSP task handler.
******************************************************************************/
void BSP_TaskHandler(void)
{
	if(bspTaskFlags0 & BSP_TII)
	{
		bspTaskFlags0&=(~BSP_TII);
		bspTIIhandler();
	}
	if(bspTaskFlags0 & SW_TII)
	{
		bspTaskFlags0&=(~SW_TII);
		swTIIhandler();
	}

  if (bspTaskFlags0)
  {
    SYS_PostTask(BSP_TASK_ID);
  }
}
// eof bspTaskManager.c
