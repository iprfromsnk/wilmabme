/**************************************************************************//**
  \file nwkAge.h

  \brief Functions of operation with the age field in tables

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/06/07 S. Vladykin - Created.
    13/06/09 M. Gekk - Comments are added.
 ******************************************************************************/
#if  !defined _NWK_AGE_H
#define _NWK_AGE_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include <nwk.h>
#include <appTimer.h>

/******************************************************************************
                            Definitions section
 ******************************************************************************/
#define NWK_AGE_PERMANENT 0xFF

/******************************************************************************
                              Types section
 ******************************************************************************/
typedef struct _NwkAgeItem_t
{
  union 
  {
    uint8_t   timeStamp;
    struct
    {
      uint8_t notUsed  : 7;
      uint8_t veryOld  : 1;
    };
  };
} NwkAgeItem_t;

typedef struct _NwkAgeTable_t
{
  uint16_t      timeStamp;
  NwkAgeItem_t  *ageItemStart;
  uint8_t       ageItemSize;
  uint8_t       size;
} NwkAgeTable_t;

typedef struct _NwkAge_t
{
  HAL_AppTimer_t ageTimer;
} NwkAge_t;

/******************************************************************************
                           Prototypes section  
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the age component.
 ******************************************************************************/
void nwkResetAge(void);

/**************************************************************************//**
  \brief Init aging for any table.
  \param table - table that needs aging (usually field of table)
  \param item1 - NwkAgeItem_t of first array element 
  \param item2 - NwkAgeItem_t of second array element, used to calc size 
    of structure containing NwkAgeItem_t, even if alignment is used.
  \param tableSize - size of array.
 ******************************************************************************/
void nwkInitAge(NwkAgeTable_t *const table, NwkAgeItem_t *const item1, 
  const NwkAgeItem_t *const item2, const uint8_t tableSize);

/**************************************************************************//**
  \brief Function shall be called often than (max(timeStamp) / 2) time units
    maxTimeToLive shall be lower than (max(timeStamp) / 2)
  \param table - table to process.
  \param time - system time in preferred units.
 ******************************************************************************/
void nwkUpdateAge(NwkAgeTable_t *const table, const uint16_t time);

/**************************************************************************//**
  \brief Find most unused item
  \param table - table to process
  \return oldest item.
 ******************************************************************************/
NwkAgeItem_t* nwkFindOldestAge(const NwkAgeTable_t *const table);

/**************************************************************************//**
  \brief Mark item of table as new, reset its time to live counter.
  \param table - table to process
  \param item - item of this table
  \param time - system time in preferred units
 ******************************************************************************/
void nwkResetItemAge(NwkAgeTable_t *const table, NwkAgeItem_t *const item, 
  const uint16_t time);

/**************************************************************************//**
  \biref Get item age
  \param table - table to process
  \param item - item of this table
  \param time - system time in preferred units
  \return an age of item
 ******************************************************************************/
uint8_t nwkGetItemAge(const NwkAgeTable_t *const table, const NwkAgeItem_t *const item, 
  const uint16_t time);

#endif  /* _NWK_AGE_H */
/* eof nwkAge.h */
