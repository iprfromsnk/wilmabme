/**************************************************************************//**
  \file nwkConcentrator.h

  \brief Interface of network concentrator.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    14/09/09 Max Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_CONCENTRATOR_H
#define _NWK_CONCENTRATOR_H

/******************************************************************************
                               Includes section
 ******************************************************************************/
#include <appTimer.h>
#include <nlmeRouteDiscovery.h>
 
/******************************************************************************
                                 Types section
 ******************************************************************************/
/* Internal states of the network concentrator. */
typedef  enum  _NwkConcentratorState_t
{
  NWK_CONCENTRATOR_IDLE_STATE = 0x89,
  NWK_CONCENTRATOR_START_TIMER_STATE = 0x8A,
  NWK_CONCENTRATOR_ROUTE_DISCOVERY_STATE = 0x8B
}  NwkConcentratorState_t;

/* State and parameters of the network concentrator. */
typedef  struct  _NwkConcentrator_t
{
  NwkConcentratorState_t  state;
  union
  {
    HAL_AppTimer_t  timer;
    NWK_RouteDiscoveryReq_t  routeDiscovery;
  };
}  NwkConcentrator_t;

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
#if defined(NWK_IS_CONCENTRATOR) && (0 < NWK_CONCENTRATOR_DISCOVERY_TIME)
/**************************************************************************//**
  \brief Start the network concentrator: Periodic sending of route discovery commands. 
 ******************************************************************************/
void nwkStartConcentrator(void);

/**************************************************************************//**
  \brief Stop the network concentrator. 
  Stop timer and doesn't send route  discovery commands.
 ******************************************************************************/
void nwkStopConcentrator(void);

/**************************************************************************//**
  \brief Reset the network concentrator.
 ******************************************************************************/
void nwkResetConcentrator(void);

#else
#define nwkStartConcentrator()  (void)0
#define nwkStopConcentrator()  (void)0
#define nwkResetConcentrator  NULL
#endif /* NWK_IS_CONCENTRATOR and 0 < NWK_CONCENTRATOR_DISCOVERY_TIME */
#endif /* _NWK_CONCENTRATOR_H */
/* eof nwkConcentrator.h */
