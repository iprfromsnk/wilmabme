/**************************************************************************//**
 \file nwkAttributes.h

 \brief Interface of network attributes.

 \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    01/05/2009  Max Gekk - Created
 ******************************************************************************/
#if !defined _NWK_ATTRIBUTES_H
#define _NWK_ATTRIBUTES_H
/******************************************************************************
                               Includes section
 ******************************************************************************/
#include  <types.h>
#include  <mac.h>
#include  <nwkCommon.h>

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief This function return a short address that is allocated by parent.
  \return short address of this node or NWK_NO_SHORT_ADDR
 ******************************************************************************/
ShortAddr_t  NWK_GetShortAddr(void);

/**************************************************************************//**
  \brief Setting new short address of this device.
  \param shortAddr - new short (16-bit) address.
  \return NWK_SUCCESS_STATUS - if this request is valid 
     otherwise NWK_NOT_PERMITTED_STATUS.
 ******************************************************************************/
NWK_Status_t NWK_SetShortAddr(const ShortAddr_t shortAddr);

/**************************************************************************//**
  \brief This function return a short address of parent.
  \return short address of parent device or NWK_NO_SHORT_ADDR
 ******************************************************************************/
ShortAddr_t  NWK_GetParentShortAddr(void);

/**************************************************************************//**
  \brief This function return a short panid of network.
  \return short panid or 0xFFFF
 ******************************************************************************/
PanId_t  NWK_GetPanId(void);

/**************************************************************************//**
  \brief This function return a extended panid of network.
  \return extended panid or 0
 ******************************************************************************/
ExtPanId_t  NWK_GetExtPanId();

/**************************************************************************//**
  \brief MAC capability information.
 ******************************************************************************/
MAC_CapabilityInf_t  NWK_GetCapabilityInformation(void);

/**************************************************************************//**
  \brief Current RF channel
 ******************************************************************************/
uint8_t  NWK_GetLogicalChannel(void);

/**************************************************************************//**
  \brief Setting a new RF channel
 ******************************************************************************/
void  NWK_SetLogicalChannel(const uint8_t channel);

/**************************************************************************//**
  \brief Counter of data packet transmission
 ******************************************************************************/
uint16_t  NWK_GetTransmitCounter(void);

/**************************************************************************//**
  \brief Failure counter of data packet transmission
 ******************************************************************************/
uint16_t  NWK_GetTransmitFailureCounter(void);

/**************************************************************************//**
  \brief To set in a zero all counters
 ******************************************************************************/
void  NWK_ResetTransmitCounters(void);

/**************************************************************************//**
  \brief Maximum delivery time of broadcasting transmission on a network
 ******************************************************************************/
uint8_t  NWK_GetBroadcastDeliveryTime(void);

/**************************************************************************//**
  \brief Set a short address of a network manager.
 ******************************************************************************/
void  NWK_SetManagerAddr(const ShortAddr_t  shortAddr);

/**************************************************************************//**
  \brief Set a id of network snapshot.
 ******************************************************************************/
void  NWK_SetUpdateId(const uint8_t updateId);

#endif /* _NWK_ATTRIBUTES_H */
/* eof nwkAttributes.h */

