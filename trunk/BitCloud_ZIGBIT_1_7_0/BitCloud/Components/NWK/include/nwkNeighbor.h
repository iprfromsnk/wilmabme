/**************************************************************************//**
 \file nwkNeighbor.h

 \brief Neighbor table interface.

 \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/04/2009  Max Gekk - Created
******************************************************************************/
/* The neighbor table of a device shall contain information on every device 
 * within transmission range. ZigBee Spec r17, 3.6.1.5, page 366. */
#if !defined _NWK_NEIGHBOR_H
#define _NWK_NEIGHBOR_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <types.h>
#include <appFramework.h>
#include <appTimer.h>
#include <mac.h>

/******************************************************************************
                   Types section
 ******************************************************************************/
/* The relationship between the neighbor and the current device */
typedef enum
{
  RELATIONSHIP_PARENT                = 0x00,  /* neighbor is the parent */
  RELATIONSHIP_CHILD                 = 0x01,  /* neighbor is a child */
  RELATIONSHIP_SIBLING               = 0x02,  /* neighbor is a sibling */
  RELATIONSHIP_NONE_OF_ABOVE         = 0x03,  /* none of the above */
  RELATIONSHIP_PREVIOUS_CHILD        = 0x04,  /* previous child */
  RELATIONSHIP_UNAUTHENTICATED_CHILD = 0x05,  /* unauthenticated child */
  RELATIONSHIP_EMPTY,
} Relationship_t;

/* The neighbor table item. */
typedef struct
{
  Relationship_t  relationship;
  /* The type of neighbor device. */
  DeviceType_t  deviceType;
  /* IEEE 802.15.4-2006 7.3.1.2 Capability Information field. */
  MAC_CapabilityInf_t  capability; 
  /* The logical channel on which the network is operating. */  
  uint8_t  logicalChannel;
  /* The 16-bit network address of the neighboring device. */
  ShortAddr_t  networkAddr;
  PanId_t  panId;       
  /* 64-bit IEEE address that is unique to every device. */
  ExtAddr_t  extAddr;
  /* The 64-bit unique identifier of the network to which the device belongs.*/
  ExtPanId_t  extPanId;
  /* The tree depth of the neighbor device. */
  uint8_t  depth;
  /* The value identifying a snapshot of the network settings with which this
   * node is operating with.*/
  uint8_t  updateId;
  /* Indicates if neighbor's receiver is enabled during idle periods. */
  bool  rxOnWhenIdle  :1;     
  /* An indication of whether the device is accepting joining requests. */
  bool  permitJoining :1;
  /* An indication of whether the device has been ruled out as a potential parent. */
  bool  potentialParent  :1;
  bool  useNetworkKey  :1;
  unsigned  reserved1  :4;
} NwkNeighbor_t;

/* Mutable fields of a entry in the neighbor table. */
typedef struct _MutableNeib_t
{
  /* The time of life of a neighbor entry. */
  uint16_t  lifeTime;
  /* The estimated link quality for RF transmissions from this device. */
  uint8_t  lqi;
  int8_t  rssi;
  /* The cost of an outgoing link as measured by the neighbor. */
  unsigned  outgoingCost  :3;
  /* The cost of an incoming link as measured by this device. */
  unsigned  incomingCost  :3;
  unsigned  reserved2  :2;
} NwkMutablePartOfNeighbor_t;

/* Type of size of the neighbor table. */
typedef uint8_t NwkSizeOfNeighborTable_t;

/* Type of the neighbor table. */
typedef struct
{
 /* The array of a neighbor entry. */
  NwkNeighbor_t  *table;
  /* The array of a mutable neighbor entry. */
  NwkMutablePartOfNeighbor_t  *mutableTable;
  /* Maximum neighbors in the neighbor table. */
  NwkSizeOfNeighborTable_t  tableSize;
  /* Timer for internal use. */
  HAL_AppTimer_t ageTimer;
} NwkNeighborTable_t;

/* For backward compatibility */
typedef NwkNeighbor_t  Neib_t;
typedef NwkMutablePartOfNeighbor_t  MutableNeib_t;
typedef NwkNeighborTable_t  NeibTable_t;

/******************************************************************************
                   Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Access function to the neighbor table.
  \return pointer to the neighbor table
 ******************************************************************************/
NeibTable_t*  NWK_GetNeighborTable(void);

/**************************************************************************//**
  \brief Searching a neighbor entry by extended address. 
  \return NULL if no records found, or entry with extAddr otherwise
 ******************************************************************************/
NwkNeighbor_t* NWK_FindNeighborByExtAddr(const ExtAddr_t extAddr);

/**************************************************************************//**
  \brief Searching a neighbor entry by short addr. 
  \return NULL if no records found, or entry with shortAddr otherwise
 ******************************************************************************/
NwkNeighbor_t* NWK_FindNeighborByShortAddr(const ShortAddr_t shortAddr);

/**************************************************************************//**
  \brief Removing child from the neighbor table.
  \param child - pointer to the child in the neighbor table.
  \return none
 ******************************************************************************/
void NWK_RemoveNeighbor(NwkNeighbor_t *const neighbor);

/**************************************************************************//**
  \brief Link quality indication for given neighbor.
  \param neib - pointer to a entry of neighbor in the neighbor table.
  \return LQI of received frames from a neighbor
 ******************************************************************************/
uint8_t  NWK_GetNeighborsLqi(Neib_t const *const neib);

/**************************************************************************//**
  \brief RSSI  for given neighbor.
  \param neib - pointer to a entry of neighbor in the neighbor table.
  \return RSSI of received frames from a neighbor
 ******************************************************************************/
int8_t  NWK_GetNeighborsRssi(Neib_t const *const neib);

#endif /* _NWK_NEIGHBOR_H */
/* eof nwkNeighbor.h */

