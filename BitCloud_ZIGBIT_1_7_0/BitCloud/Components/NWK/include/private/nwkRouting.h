/**************************************************************************//**
  \file  nwkRouting.h

  \brief Routing header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 V. Panov - Created.
    06/09/08 M. Gekk  - Modified to support parallel processing.
    08/09/09 M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_ROUTING_H
#define _NWK_ROUTING_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <types.h>

/******************************************************************************
                              Definitions section
 ******************************************************************************/
#define  NWK_ROUTE_MULTICAST         (1U << 0)
#define  NWK_ROUTE_MULTICAST_MEMBER  (1U << 1)
#define  NWK_ROUTE_INDIRECT          (1U << 2)
#define  NWK_ROUTE_RECORD_REQUIRED   (1U << 3)

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Getting MAC short address of next hop by destination network address.
  \param dstAddr - destination network address.
  \param flags - routing flags. Incoming flag - NWK_ROUTE_MULTICAST, 
    NWK_ROUTE_MULTICAST_MEMBER; outgoing flags - NWK_ROUTE_INDIRECT, NWK_ROUTE_RECORD_REQUIRED.
  \return MAC short address of next hop or  MAC_NO_SHORT_ADDR.
 ******************************************************************************/
ShortAddr_t  nwkGetNextHop(const ShortAddr_t  dstAddr, uint8_t  *const flags);

#endif /* _NWK_ROUTING_H */
/* eof nwkRouting.h */
