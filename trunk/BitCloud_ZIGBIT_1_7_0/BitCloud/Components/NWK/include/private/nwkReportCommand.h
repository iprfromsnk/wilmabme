/**************************************************************************//**
  \file nwkReportCommand.h

  \brief Report command header file.
   
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    10/12/08 M. Gekk  - Reduction of usage of the RAM at separate compiling
    05/06/09 M. Gekk  - Refactoring
 ******************************************************************************/
#if !defined _NWK_REPORT_COMMAND_H
#define  _NWK_REPORT_COMMAND_H

/******************************************************************************
                             Includes section
 ******************************************************************************/
#include  <types.h>
#include  <mac.h> 
#include  <nwkFrame.h> 
#include  <nwkCommands.h>

/******************************************************************************
                            Definitions section
 ******************************************************************************/
/* Maximum size of a list of 16-bit PAN identifiers that are operating in the 
 * neighborhood of the reporting device.*/
#define NWK_MAX_REPORT_PANID  16
/* Types of report information command. */
#define NWK_REPORT_TYPE_PANID_CONFLICT  0
/* Minimum size of the report command payload without report information field. */
#define  NWK_SIZE_OF_MIN_REPORT_CMD_PAYLOD  10

/******************************************************************************
                               Types section
 ******************************************************************************/
/* Internal states of the report command component */
typedef  enum _NwkReportCommandState_t
{
  /* State after reset */
  NWK_REPORT_IDLE_STATE = 0x27,
  /* States of preparing and sending a report command. */
  NWK_REPORT_FIRST_STATE = 0x51,
  NWK_REPORT_SCAN_STATE = NWK_REPORT_FIRST_STATE,
  NWK_REPORT_PREPARE_MAC_DATA_STATE = 0x52,
  NWK_REPORT_PREPARE_MAC_REQ_STATE = 0x53,
  NWK_REPORT_SEND_STATE = 0x54,
  NWK_REPORT_LAST_STATE
}  NwkReportCommandState_t;

/* Internal variables of the report command component. */
typedef  struct _NwkReportCommand_t 
{
  /* finite-state machine */
  NwkReportCommandState_t  state;
  union
  {
    /* MLME-SCAN request primitive's parameters */
    MAC_ScanReq_t  macScan;
    union 
    {
      /* Parameters of send command request. */
      NwkCommandReq_t  commandReq; 
      /* Size of NPDU of the report command. */
      uint8_t  sizeOfReportCommand;
    };
  };
}  NwkReportCommand_t;

/* Payload of network report command. ZigBee spec r17, Figure 3.24. */
BEGIN_PACK
typedef  struct PACK _NwkReportCommandPayload_t
{
  /* Id of report command. ZigBee spec r17, Table 3.40. */
  uint8_t  commandId;
  /* Command Options Field. ZigBee spec r17, Figure 3.25. */
  /* The report information count sub-field contains an integer indicating 
   * the number of records contained within the Report Information field.*/
  uint8_t  infoCount    :5;
  /* The report command identifier sub-field contains an integer indicating 
   * the type of report information command. ZigBee spec r17, 3.4.9.3.1.2, page 334. */
  uint8_t  reportCmdId  :3;
  /* The EPID field shall contain the 64-bit EPID that identifies the network 
   * that the reporting device is a member of. ZigBee spec r17, 3.4.9.3.2, page 334. */
  uint64_t  extPanId;
  /* The report information field provides the information being reported, the format
   * of this field depends upon the value of the Report Command Identifier sub-field. */
  union 
  {
    uint8_t  reportInfo[NWK_MAX_REPORT_PANID * sizeof(PanId_t)];
    PanId_t  panId[NWK_MAX_REPORT_PANID];
  };
}  NwkReportCommandPayload_t;
END_PACK

/******************************************************************************
                            Prototypes section
 ******************************************************************************/
#if defined(_RESOLVE_PANID_CONFLICT_)
/**************************************************************************//**
  \brief Function detects the potential conflict of addresses.
  \param beaconNotify - MLME-BEACON_NOTIFY indication parameters' 
    structure pointer.
 ******************************************************************************/
void  nwkDetectPanIdConflict(const MAC_BeaconNotifyInd_t *const beaconNotify);

/**************************************************************************//**
  \brief Reset the report command component.
 ******************************************************************************/
void  nwkResetReportCommand(void);

/**************************************************************************//**
  \brief Searching other network and fill MAC pan descriptors in configServer.
  \param macScan - MLME-SCAN.request parameters.
  \param MAC_ScanConf - MLME-SCAN confirm callback function.
 ******************************************************************************/
void nwkSearchOtherNetworks(MAC_ScanReq_t *const macScan, 
  void (*MAC_ScanConf)(MAC_ScanConf_t *));

#else
/* Interface of the report command is disabled. */
#define  nwkDetectPanIdConflict(beaconNotify)
#define  nwkResetReportCommand  NULL
#define  nwkSearchOtherNetworks(macScan, MAC_ScanConf) 
#endif

#endif  /* _NWK_REPORT_COMMAND_H */
/* eof nwkReportCommand.h */
