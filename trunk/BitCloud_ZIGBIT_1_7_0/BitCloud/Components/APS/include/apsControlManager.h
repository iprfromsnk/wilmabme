/***************************************************************************//**
  \file apsControlManager.h

  \brief APS Control Manager header file
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal          
  History:
    06.06.07 A. Potashov - Created.
*****************************************************************************/


#ifndef _APSCONTROLMANAGER_H
#define _APSCONTROLMANAGER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <apsComponentId.h>

/******************************************************************************
                   Define(s) section
******************************************************************************/

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
  Search the registered endpoint descriptor 
  Parameters: endpoint - endpoint 
  Returns: Valid endpoint descriptor pointer if one finded
           NULL - at other case
*****************************************************************************/
APS_RegisterEndpointReq_t *apsFindRegisteredEnpoint(uint8_t endpoint);


/*****************************************************************************
  APS Control Manager endpoint descriptors direct access function
  Parameters: previousEndpointDescriptor - previous endpoint descriptor pointer. 
              It is must be non NULL sequential access required if. And it is 
              must be NULL the first descriptor as registered endpoints queue
              head element access required if.
  Returns:  Valid endpoint descriptor pointer descriptor found if.
            NULL - other case. 
*****************************************************************************/
APS_RegisterEndpointReq_t *apsGetEndpointDescriptor(APS_RegisterEndpointReq_t *previousEndpointDescriptor);


/*****************************************************************************
  APS Control Manager process function
  Parameters: None
  Returns: None
*****************************************************************************/
void apsControlManagerProcess(void);


/*****************************************************************************
  Return system time value at stop if start request does not occur yet.
  Return system time interval from stop in other case.
  Parameters: None
  Returns: None
*****************************************************************************/
uint32_t apsGetSystemTimeOnStopEvent(void);

/*****************************************************************************
  Check stop procedure complete (all APS components are stopped) and peform
  APS_StopConf if it is true
  Parameters: apsComponentId - APS Component Id of a component wich stopped 
  already
  Returns: None
*****************************************************************************/
void apsCompleteStop(ApsComponentId_t apsComponentId);

/******************************************************************************
                   Inline static functions section 
******************************************************************************/


#endif  //#ifndef _APSCONTROLMANAGER_H

//eof apsControlManager.h
