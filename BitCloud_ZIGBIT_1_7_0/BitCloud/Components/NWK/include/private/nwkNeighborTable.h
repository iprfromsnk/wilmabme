/**************************************************************************//**
  \file  nwkNeighborTable.h

  \brief Interface of the neighbor table..

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    12/05/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_NEIGHBOR_TABLE_H
#define  _NWK_NEIGHBOR_TABLE_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <nwk.h>
#include <nwkMem.h>

/******************************************************************************
                               Define(s) section
 ******************************************************************************/
#define  IS_EMPTY(ntEntry)  (RELATIONSHIP_EMPTY == ntEntry->relationship)
#define  IS_AUTHENTICATED_CHILD(ntEntry) (RELATIONSHIP_CHILD == ntEntry->relationship)
#define  IS_UNAUTHENTICATED_CHILD(ntEntry)  (RELATIONSHIP_UNAUTHENTICATED_CHILD == ntEntry->relationship)
#define  IS_END_DEVICE(ntEntry)  (DEVICE_TYPE_END_DEVICE  == ntEntry->deviceType)
#define  IS_CHILD(ntEntry)  (IS_AUTHENTICATED_CHILD(ntEntry) || IS_UNAUTHENTICATED_CHILD(ntEntry))
#define  IS_PARENT(ntEntry)  (RELATIONSHIP_PARENT == ntEntry->relationship)
#define  IS_RX_ON_WHEN_IDLE(ntEntry) (ntEntry->rxOnWhenIdle)
#define  FREE_NEIGHBOR(neighbor)  neighbor->relationship = RELATIONSHIP_EMPTY
/* Getting mutable part of neighbor entry */
#define  MUTABLE_PART(neighbor)  nwkMutablePart(nwkMemNeighborTable(), neighbor)
/* Minimum value of a cost metric */
#define  NWK_MIN_LINK_COST  1
/* Maximum value of a cost metric */
#define  NWK_MAX_LINK_COST  7

/******************************************************************************
                 Inline static functions prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief First entry of the neighbor table.
 ******************************************************************************/
INLINE NwkNeighbor_t*  nwkNtBegin(void)
{
  return nwkMemNeighborTable()->table;
}

/**************************************************************************//**
  \brief Function return a pointer to memory area after last entry of the
    neighbor table.
 ******************************************************************************/
INLINE NwkNeighbor_t*  nwkNtEnd(void)
{
  return nwkMemNeighborTable()->table + nwkMemNeighborTable()->tableSize;
}

/**************************************************************************//**
  \brief Function return a total size of the neighbor table.
 ******************************************************************************/
INLINE NwkSizeOfNeighborTable_t nwkNtSize(void)
{
  return nwkMemNeighborTable()->tableSize;
}

/**************************************************************************//**
  \brief Getting the mutable part of given neighbor entry.
 ******************************************************************************/
INLINE NwkMutablePartOfNeighbor_t* nwkMutablePart(NwkNeighborTable_t const *const neighborTable,
  NwkNeighbor_t  const *const neighbor)
{
  return neighborTable->mutableTable + (neighbor - neighborTable->table);
}

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the neighbor table.
  \param powerFailure - restore the neighbor table from configServer or not
 ******************************************************************************/
void nwkResetNeighborTable(bool powerFailure);

/**************************************************************************//**
  \brief Clear all entries in the neighbor table.
  \param removeParent - remove parent's entry
 ******************************************************************************/
void  nwkClearNeighborTable(const bool removeParent);

/**************************************************************************//**
  \brief Start the age timer of the neighbor table.
 ******************************************************************************/
void  nwkStartAgeTimerOfNeighborTable(void);

/**************************************************************************//**
  \brief Search of the following child after given with a flag rxOnWhenIdle in false.
  \param neighbor - the neighbour with which search should begin.
  \param exceptShortAddr - the address of the child which should be passed.
 ******************************************************************************/
NwkNeighbor_t* nwkFindRxOffWhenIdleChild(NwkNeighbor_t* neighbor,
    const ShortAddr_t exceptShortAddr);

/**************************************************************************//**
  \brief Free a entry in the neighbor table.
  \param neighbor - pointer to a neighbor.
 ******************************************************************************/
void nwkFreeNeighbor(NwkNeighbor_t *const neighbor);

/**************************************************************************//**
  \brief Update of time of a life of the neighbour.
  \param neighbor - pointer to a neighbor.
 ******************************************************************************/
void nwkSetLifeTimeOfNeighbor(NwkNeighbor_t *const neighbor);

/**************************************************************************//**
  \brief Checking of that the given device is destination node for the
    short address.
  \param shortAddress - unicast or multicast short address.
  \param group - if 'true' then shortAddress is a multicast address.
  \return 'true' if this node is destination else 'false'.
 ******************************************************************************/
bool nwkIsRouteDestination(const ShortAddr_t shortAddr, const bool group);

/**************************************************************************//**
  \brief Calculate an incoming cost by LQI.
  \param lqi - link quality indicator.
 ******************************************************************************/
uint8_t nwkCostFromLqi(const uint8_t lqi);

/**************************************************************************//**
  \brief Recalculation LQI and costs for the set neighbor.
  \param neighbor - pointer to a neighbor
  \param linkQuality - the link quality indicator of a received packet.
  \param rssi - received signal strength indication.
 ******************************************************************************/
void nwkUpdateLqiAndCostOfNeighbor(NwkNeighbor_t *const neighbor,
  const uint8_t linkQuality, const int8_t rssi);

/**************************************************************************//**
  \brief Recalculation LQI and costs for a neighbor with given short address.
  \param addr -  short address of a neighbor.
  \param linkQuality - the link quality indicator of a received packet.
  \param rssi - received signal strength indication.
 ******************************************************************************/
void nwkUpdateLqiAndLifeTime(const ShortAddr_t addr, const uint8_t linkQuality,
  const int8_t rssi);

/**************************************************************************//**
  \brief Calculation of quantity of children and updating of capacity bits.
 ******************************************************************************/
void  nwkUpdateCapacityBitsInBeacon(void);

/**************************************************************************//**
  \brief Updating capacity bits in beacon by end devices and routers count.
 ******************************************************************************/
void nwkUpdateCapacityBits(uint8_t endDeviceCount, uint8_t routerCount);

#endif  /* _NWK_NEIGHBOR_TABLE_H */
/* eof nwkNeighborTable.h */
