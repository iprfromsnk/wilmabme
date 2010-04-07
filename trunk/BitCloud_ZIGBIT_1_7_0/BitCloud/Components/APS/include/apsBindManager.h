/*************************************************************************//**
  \file apsBindManager.h

  \brief APS BINDING feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    11/03/08 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSBINDMANAGER_H
#define _APSBINDMANAGER_H
#ifdef _BINDING_

#include <aps.h>

#define APS_INVALID_BINDING_TABLE_ENTRY_INDEX   0xff

BEGIN_PACK

typedef struct PACK
{
  APS_AddrMode_t addrMode;
  struct PACK
  {
    union PACK
    {
#ifdef _APS_MULTICAST_
      GroupAddr_t groupAddress; //!< 16-bit group (multicast) address
#endif
      ExtAddr_t   extAddress;   //!< 64-bit extended IEEE address
    };
  } addr;
  Endpoint_t endpoint;
} ApsBindingTableDestinationEntry_t;

typedef struct PACK
{
  ExtAddr_t addr;
  Endpoint_t endpoint;
  uint16_t clusterId;
} ApsBindingTableSourceEntry_t;

typedef struct PACK
{
  ApsBindingTableSourceEntry_t        src;
  ApsBindingTableDestinationEntry_t   dst[0];
} ApsBindingTableEntry_t;

typedef struct PACK
{
  ApsBindingTableEntry_t *entry;
  uint8_t index;
} ApsBindingDescriptor_t;
END_PACK

extern void apsResetBindManager(bool powerFailure);
extern ApsBindingTableEntry_t *apsFindBindSrcEntry(ApsBindingTableSourceEntry_t *src);
extern uint8_t apsGetNextBindDestEntryIndex(ApsBindingTableEntry_t *entry, uint8_t index);

#endif //#ifdef _BINDING_
#endif //#ifndef _APSBINDMANAGER_H
//eof apsBindManager.h
