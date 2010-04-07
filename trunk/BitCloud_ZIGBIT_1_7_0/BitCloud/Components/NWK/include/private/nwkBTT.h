/**************************************************************************//**
  \file nwkBTT.h

  \brief Broadcast transaction table.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    01/09/07 V. Panov - Created.
    17/11/08 M. Gekk - Correct clearing of record in BTT. In case of overflow 
                       of the table function nwkCheckBTT returns an error.
                       BTT moved in ConfigServer.
    29/04/09 M. Gekk - Refactoring                   
******************************************************************************/
#if !defined _NWK_BTT_H
#define _NWK_BTT_H

/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <mac.h>
#include <nwkAge.h>

/******************************************************************************
                                  Types section
 ******************************************************************************/
/* Broadcast transaction record */
typedef struct _NwkBTR_t
{
  /* The 16-bit network address of the broadcast initiator. */
  ShortAddr_t  shortAddr;
  /* The NWK layer sequence number of the initiator?s broadcast. */
  uint8_t      sequenceNumber;
  /* Age of BTR */
  NwkAgeItem_t age;
} NwkBTR_t;

/* Broadcast transaction table */
typedef struct _NwkBTT_t
{
  /* Pointer to an array of BTR */
  NwkBTR_t      *table;
  /* Size of BTT */
  uint8_t       tableSize;
  /* Age of BTT */
  NwkAgeTable_t age;
} NwkBTT_t;

/* Status of nwkCheckBTT */
typedef enum _NwkCheckBTTStatus_t
{
  NWK_BTR_DOES_NOT_EXIST  = 0x00,
  NWK_BTR_EXISTS,
  NWK_BTT_IS_FULL
} NwkCheckBTTStatus_t;

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reseting of the broadcast transaction table.
 ******************************************************************************/
void nwkResetBTT(void);

/**************************************************************************//**
  \brief Check entry for addr and sequence number.
  \param shortAddr - source address of broadcast packet
  \param sequenceNumber - a sequence number of broadcast packet
 ******************************************************************************/
NwkCheckBTTStatus_t  nwkCheckBTT(const ShortAddr_t shortAddr, const uint8_t sequenceNumber);

/**************************************************************************//**
  \brief Updating age of BTT. This function should be called periodically.
 ******************************************************************************/
void nwkUpdateAgeBTT(void);

#endif /* _NWK_BTT_H */
/* eof nwkBTT.h */
