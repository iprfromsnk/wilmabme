/*************************************************************************//**
  \file apsGroupManager.h

  \brief APS Group Manager header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    24/07/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSGROUPMANAGER_H
#define _APSGROUPMANAGER_H
#ifdef _APS_MULTICAST_
/******************************************************************************
                   Includes section
******************************************************************************/
#include <aps.h>
#include <types.h>
#include <appFramework.h>
#include <macAddr.h>

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

/*============================================================================
  APS Group Manager API
============================================================================*/

/*****************************************************************************
  Make a reset of APS Group Manager
  Parameters: powerFailure - is powerFailure feature activated
  Returns:    None
*****************************************************************************/
extern void apsResetGroupManager(bool powerFailure);

/*****************************************************************************
  APS Group Manager Process function
  Parameters: None
  Returns: None
*****************************************************************************/
extern void apsGroupManagerProcess(void);


/*****************************************************************************
  Get a member of group specified.
  Parameters: groupDescriptor - group descriptor as APS Group Table entry
              memberIndex - index of group member (endpoint)

  Returns: valid endpoint pointer - member exist if
           NULL - invalid parameter
*****************************************************************************/
extern Endpoint_t *apsGetGroupMember(APS_GroupTableEntry_t *groupDescriptor, uint8_t memberIndex);

/*****************************************************************************
  Make a search a member of group specified.
  Parameters: groupDescriptor - group descriptor as APS Group Table entry
              endpoint - endpoint as group member.

  Returns: if not APS_ZDO_ENDPOINT endpoinrt specified:
              actual member (endpoint) index - member found
              0xff - member not found

           if APS_ZDO_ENDPOINT endpoinrt specified:
              actual group members amount
*****************************************************************************/
extern uint8_t APS_FindGroupMember(APS_GroupTableEntry_t *groupDescriptor, Endpoint_t endpoint);

/******************************************************************************
                   Inline static functions section
******************************************************************************/

#endif  //#ifdef _APS_MULTICAST_
#endif  //#ifndef _APSGROUPMANAGER_H

//eof apsGroupManager.h
