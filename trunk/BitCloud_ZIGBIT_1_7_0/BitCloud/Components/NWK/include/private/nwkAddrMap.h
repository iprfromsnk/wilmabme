/**************************************************************************//**
  \file  nwkAddrMap.h

  \brief Interface of the address map.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    18/05/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined  _NWK_ADDR_MAP_H
#define  _NWK_ADDR_MAP_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include  <nwk.h>
#include  <nwkAddrConflict.h>

/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Internal states of the address map. */
typedef  enum  _NwkAddressMapState_t
{
  NWK_ADDRESS_MAP_IDLE_STATE  = 0xA1,
  NWK_ADDRESS_MAP_SEND_CONFLICT_STATE = 0x67
}  NwkAddressMapState_t;

/* Type of size of the address map. */
typedef  uint8_t NwkSizeOfAddressMap_t;

/* Type of index of the address map. */
typedef  NwkSizeOfAddressMap_t  NwkAddressMapIndex_t;

/* Type of entry of the address map. */
typedef  struct  _NwkAddressMapEntry_t
{
  /* The entry is busy (1) or not (0). */
  uint8_t  busy  :1;
  /* Conflict of short addresses is detected (1) or not (0). */
  uint8_t  conflict  :1;
  uint8_t  reserved  :6;
  /* A network address (16-bit). */
  ShortAddr_t  shortAddr;
  /* IEEE address (64-bit). */
  ExtAddr_t  extAddr;
}  NwkAddressMapEntry_t;

/* Type of the address map. */
typedef  struct  _NwkAddressMap_t
{
  /* Internal state of the address map. */
  NwkAddressMapState_t  state;
  /* Size of the address map. */
  NwkSizeOfAddressMap_t  size;
  /* Current position for a new entry. */
  NwkAddressMapIndex_t  currentPosition;
  /* Array of address map entries. */
  NwkAddressMapEntry_t  *table;
#if defined(_ROUTER_) || defined(_COORDINATOR_)
  NwkAddrConflictReq_t  addrConflict;
#endif
}  NwkAddressMap_t;

/******************************************************************************
                           Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the address map.
 ******************************************************************************/
void nwkResetAddressMap(void);
 
#endif  /* _NWK_ADDR_MAP_H */
/* eof nwkAddrMap.h */

