/**************************************************************************//**
  \file  nwkAddress.h

  \brief Formation header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    12/05/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_ADDRESS_H
#define  _NWK_ADDRESS_H

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
 \brief Computing the size of the address sub-block.
 \param depth - current depth.  
 \return cskip block.
 ******************************************************************************/
uint16_t nwkCSkip(const uint8_t depth);

/**************************************************************************//**
 \brief Allocating a new short address
 \param router - 'true' if address is allocating for router, else 'false'.
 \param addrRequested - requested address
 \return allocated short address
******************************************************************************/
ShortAddr_t nwkAllocateShortAddr(const bool router, const ShortAddr_t addrRequested);

#endif  /* _NWK_ADDRESS_H */
/* eof nwkAddress.h */ 

