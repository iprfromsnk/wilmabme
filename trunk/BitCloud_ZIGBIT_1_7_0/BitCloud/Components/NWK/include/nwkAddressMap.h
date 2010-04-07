/**************************************************************************//**
  \file nwkAddressMap.h
  
  \brief The access interface to the address map..
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).
  
  \internal
  History:     
    13/04/2009 Max Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_ADDRESS_MAP_H
#define _NWK_ADDRESS_MAP_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <types.h>
#include <appFramework.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Add a short and extended addresses in the address map.
  \param shortAddr - a short address.
  \param extAddr - an extended address.
******************************************************************************/
void  NWK_AddToAddressMap(const ShortAddr_t shortAddr, const ExtAddr_t extAddr);

/**************************************************************************//**
  \brief Searching a extended address by the short address
  \param shortAddr - a short address
  \return pointer to the extended address in the address map.
 ******************************************************************************/
const ExtAddr_t*  NWK_GetExtByShortAddress(const ShortAddr_t shortAddr);

/**************************************************************************//**
  \brief Searching a short adress by the extended address.
  \param extAddr - pointer to the extended address.
  \return pointer to the short address in the address map.
 ******************************************************************************/
const ShortAddr_t*  NWK_GetShortByExtAddress(const ExtAddr_t *const extAddr);

/**************************************************************************//**
  \brief Remove the entry with given short address from the address map.
  \param shortAddr - a short address.
 ******************************************************************************/
void  NWK_RemoveFromAddressMap(const ShortAddr_t shortAddr);

#endif /* _NWK_ADDRESS_MAP_H */
/* eof nwkAddressMap.h */

