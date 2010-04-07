/**************************************************************************//**
  \file nwkManager.h

  \brief Interface of the network manager.
   
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    08/06/2009 Max Gekk - Created
 ******************************************************************************/
#if !defined  _NWK_MANAGER_H
#define  _NWK_MANAGER_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include  <mac.h>
#include  <nwkCommands.h>

/******************************************************************************
                                Types section
 ******************************************************************************/
/* Internal states of the report command component */
typedef  enum _NwkManagerState_t
{
  NWK_MANAGER_IDLE_STATE = 0xFB,
  NWK_MANAGER_FIRST_STATE = 0x83,
  NWK_MANAGER_MAC_SCAN_STATE = NWK_MANAGER_FIRST_STATE,
  NWK_MANAGER_PREPARE_MAC_DATA_STATE = 0x84,
  NWK_MANAGER_PREPARE_MAC_REQ_STATE = 0x85,
  NWK_MANAGER_SEND_UPDATE_CMD_STATE = 0x86,
  NWK_MANAGER_SET_PAN_ID_STATE = 0x87,
  NWK_MANAGER_LAST_STATE
}  NwkManagerState_t;

/* Internal variables of the network manager component. */
typedef  struct  _NwkManager_t
{
  /* finite-state machine */
  NwkManagerState_t  state;
  PanId_t  newPanId;
  union
  {
    /* MLME-SCAN request primitive's parameters */
    MAC_ScanReq_t  macScan;
    /* Parameters of send command request. For sending the update command frame.*/
    NwkCommandReq_t  commandReq; 
  };
}  NwkManager_t;

/******************************************************************************
                                Prototypes section
 ******************************************************************************/
#if defined(_RESOLVE_PANID_CONFLICT_) && defined(_NETWORK_MANAGER_)
/**************************************************************************//**
  \brief Processing a conflict of panId by the network manager.
 ******************************************************************************/
void nwkDetectPanIdConflictByNwkManager(void);

/**************************************************************************//**
  \brief Reset the report command component.
 ******************************************************************************/
void  nwkResetNetworkManager(void);

/**************************************************************************//**
  \brief Action when a report command is received.
  \param payload - pointer to NPDU of NWK report command.
  \param header  - nwk header.
  \param parse   - parsed header fields.
  \return 'true' - continue command processing otherwise 'false'.
******************************************************************************/
bool  nwkReportFrameInd(const uint8_t *const payload, const NwkFrameHeader_t *const header, 
    const NwkParseHeader_t *const parse);

#else
/* Interface of the network manager is disabled. */
#define  nwkDetectPanIdConflictByNwkManager()
#define  nwkResetNetworkManager NULL
#define  nwkReportFrameInd  NULL
#endif
#endif  /* _NWK_MANAGER_H */
/* eof nwkManager.h */
