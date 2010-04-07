/**************************************************************************//**
  \file nwkGroup.h

  \brief The group addressing interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    01/07/07 S. Vladykin - Created
    13/06/09 M. Gekk     - Refactoring
 ******************************************************************************/
#if !defined _NWK_GROUP_H
#define _NWK_GROUP_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include  <mac.h>

/******************************************************************************
                         Inline functions section
 ******************************************************************************/
/**************************************************************************//**
  \brief Check of an accessory to group.

  \param[in] groupAddr - a group address.
  \return 'true' if groupAddr is own group address or 'false' otherwise.

 *****************************************************************************/
extern bool APS_IsOwnGroup(uint16_t groupAddr);

/******************************************************************************
  \brief Gate to APS group container
 ******************************************************************************/
INLINE bool nwkIsGroupMember(ShortAddr_t addr)
{
#ifdef _APS_MULTICAST_
  return APS_IsOwnGroup(addr);
#else
  (void)addr;
  return false;
#endif
}

#endif /* _NWK_GROUP_H */
/* eof nwkGroup.h */
