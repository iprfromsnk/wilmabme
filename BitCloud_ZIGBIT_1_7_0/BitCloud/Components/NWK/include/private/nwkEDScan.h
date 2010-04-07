/**************************************************************************//**
  \file nwkEDScan.h

  \brief EDScan header file.
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    14/06/07 S. Vladykin - Created.
    10/12/08 M. Gekk     - Reduction of the used RAM.
    15/03/09 M. Gekk     - Refactoring
 *****************************************************************************/
#if !defined _NWK_EDSCAN_H
#define _NWK_EDSCAN_H

/*****************************************************************************
                              Includes section
 *****************************************************************************/
#include <nwk.h>
#include <nwkMem.h>

/*****************************************************************************
                              Types section
 *****************************************************************************/
/* Internal states of NLME-ED-SCAN component */
typedef enum _NwkEDScanState_t
{
  NWK_EDSCAN_IDLE_STATE     = 0x13,
  NWK_EDSCAN_BEGIN_STATE    = 0xE7,
  NWK_EDSCAN_MAC_SCAN_STATE = 0xE8,
  NWK_EDSCAN_CONFIRM_STATE  = 0xE9
} NwkEDScanState_t;

/* Internal parameters of NLME-ED-SCAN */
typedef struct _NwkEDScan_t
{
  NwkEDScanState_t        state; /* finite-state machine */
  QueueDescriptor_t       queue; /* Queue of requests from upper layer */
  NwkState_t              savedStateMachine; 
} NwkEDScan_t;

/*****************************************************************************
                             Prototypes section
 *****************************************************************************/
/*************************************************************************//**
  \brief Reset NLME-ED-SCAN component
 *****************************************************************************/
void nwkResetEDScan(void);

/*************************************************************************//**
  \brief Main task handler of NLME-ED-SCAN
 *****************************************************************************/
void nwkEDScanTaskHandler(void);

#endif   /* _NWK_EDSCAN_H */
/* eof nwkEDScan.h */
