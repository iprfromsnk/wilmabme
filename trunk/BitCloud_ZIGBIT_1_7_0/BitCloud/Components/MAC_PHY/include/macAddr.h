/**************************************************************************//**
  \file macAddr.h
  
  \brief MAC addressing types and constants.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).
  
  \internal
    History:     
      18/06/07 ALuzhetsky - Created.
******************************************************************************/

#ifndef _MACADDR_H
#define _MACADDR_H


/******************************************************************************
                        Includes section.
******************************************************************************/
#include <types.h>

/******************************************************************************
                        Define(s) section.
******************************************************************************/
#define MAC_BROADCAST_PANID       0xFFFF ///< Broadcast PANID.
#define MAC_BROADCAST_SHORT_ADDR  0xFFFF ///< Broadcast short address, no association.
#define MAC_NO_SHORT_ADDR         0xFFFE ///< After association no short address.

/******************************************************************************
                        Types section.
******************************************************************************/
typedef uint16_t PanId_t;     ///< PAN identifier type declaration. 
typedef uint16_t ShortAddr_t; ///< Short address type declaration.
typedef uint64_t ExtAddr_t;   ///< Extended address type declaration.

/// Union of possible MAC address types.
typedef union
{
  ShortAddr_t sh;
  ExtAddr_t   ext;
} MAC_Addr_t;

/******************************************************************************
                        Definitions section.
******************************************************************************/
//! MAC address mode types (IEEE 802.15.4-2006 Table 80).
 typedef enum
{
  MAC_NO_ADDR_MODE    = 0x00,
  MAC_RSRV_ADDR_MODE  = 0x01,
  MAC_SHORT_ADDR_MODE = 0x02,
  MAC_EXT_ADDR_MODE   = 0x03
} MAC_AddrMode_t;

#endif //_MACADDR_H

// eof macAddr.h
