/**************************************************************************//**
  \file nwkExtra.h
  
  \brief Extra public interface of the NWK layer.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).
  
  \internal
  History:     
    13/04/2009 Max Gekk - Created.
******************************************************************************/
#if !defined _NWK_EXTRA_H
#define _NWK_EXTRA_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <appFramework.h>

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief  NWK_Init shall be called only by APS and only once at startup
  \return none.
 ******************************************************************************/
void NWK_Init(void);

/**************************************************************************//**
  \brief Main network task handler.
  \return none
 ******************************************************************************/
void NWK_TaskHandler(void);

/**************************************************************************//**
  \brief  The stack don't sleep if this function return 'true'
  \return 'true' if the network layer if active otherwise 'false'.
 ******************************************************************************/
bool NWK_IsActiveTransaction(void);

/**************************************************************************//**
  \brief This function return the 16-bit network address of the next hop on 
     the way to the destination. 
  \return the network address of the next hop.
 ******************************************************************************/
ShortAddr_t NWK_GetNextHop(ShortAddr_t dstAddr);

/**************************************************************************//**
  \brief Set new network address in NIB and MIB
  \param newAddr - new network address
  \return none
 ******************************************************************************/
void NWK_SetNetworkAddress(const ShortAddr_t newAddr);

#endif /* _NWK_EXTRA_H */
/* eof nwkExtra.h */

