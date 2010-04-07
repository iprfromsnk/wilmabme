/***************************************************************************//**
  \file apsDbg.h

  \brief APS Debug Module header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    09/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSDBG_H
#define _APSDBG_H

/******************************************************************************
                   Includes section
******************************************************************************/

/******************************************************************************
                   Define(s) section
******************************************************************************/

/******************************************************************************
                   Types section
******************************************************************************/

/******************************************************************************
                   Constants section
******************************************************************************/
typedef enum
{
  /***********************************
    APS section. Range 0x4000 - 0x4FFF
  ************************************/

  //APS Data Manager Id (0x4000 - 0x40ff)
  APSDATAMANAGER_NWKDATACONFPROCESS_0         = 0x4000,
  APS_DM_UNKNOWN_BUFFER_TYPE_0                = 0x4001,
  APS_DM_MEMORY_FAULT_0                       = 0x4002,
  APS_DUPLICATE_REJECTION_TIMEOUT_OVERFLOW    = 0x4003,

  //APS Security Manager Id (0x4100 - 0x41ff)
  APS_SM_OWN_EXTADDR_ERROR                    = 0x4100,
  APS_SM_UNKNOWN_COMPONENT_ID                 = 0x4101,
  DBG_SM_MEMORY_FAULT_1,
  APS_SM_COMMAND_DATA_REQ_MEMORY_FAULT_1      = 0x4106,
  APS_SM_COMMAND_DATA_REQ_MEMORY_FAULT_2      = 0x4107,
  DBG_APS_SM_GET_PARENT_EXT_ADDR_FAULT,

  //APS Security Manager Key Establish Router (0x4200 - 0x42ff)
  DBG_APS_SM_KERO_INVALID_STATE_1             = 0x4200,
  DBG_APS_SM_KERO_INVALID_STATE_2             = 0x4201,
  DBG_APS_SM_KERO_INVALID_STATE_3             = 0x4202,
  DBG_APS_SM_KERO_MEMORY_FAULT_1              = 0x4203,
  DBG_APS_SM_KERO_MEMORY_FAULT_2              = 0x4204,


  DBG_APS_SM_KEREQ_INVALID_REQUEST            = 0x4205,
  DBG_APS_SM_KEREQ_INVALID_STATE_1            = 0x4206,
  DBG_APS_SM_KEREQ_INVALID_STATE_2            = 0x4207,
  DBG_APS_SM_KEREQ_MEMORY_FAULT_1             = 0x4208,
  DBG_APS_SM_KEREQ_MEMORY_FAULT_2             = 0x4209,

  DBG_APS_SM_KERESP_INVALID_STATE_1           = 0x420a,
  DBG_APS_SM_KERESP_INVALID_STATE_2           = 0x420b,
  DBG_APS_SM_KERESP_MEMORY_FAULT_1            = 0x420c,
  DBG_APS_SM_KERESP_MEMORY_FAULT_2            = 0x420d,
  DBG_APS_SM_KERESP_MEMORY_FAULT_3            = 0x420e,
  DBG_APS_SM_KERESP_MEMORY_FAULT_4            = 0x420f,
  DBG_APS_SM_KERESP_MEMORY_FAULT_5            = 0x4210,
  DBG_APS_SM_KERESP_MEMORY_FAULT_6            = 0x4211,
  DBG_APS_SM_KERESP_MEMORY_FAULT_7            = 0x4212,
  DBG_APS_SM_KERESP_MEMORY_FAULT_8            = 0x4213,

  DBG_APS_SM_TKR_INVALID_REQUEST              = 0x4214,
  DBG_APS_SM_TKR_INVALID_STATE_1              = 0x4215,
  DBG_APS_SM_TKR_INVALID_STATE_2              = 0x4216,
  DBG_APS_SM_TKR_MEMORY_FAULT_1               = 0x4217,
  DBG_APS_SM_TKR_MEMORY_FAULT_2               = 0x4218,

  DBG_APS_SM_UDR_INVALID_REQUEST              = 0x4219,
  DBG_APS_SM_UDR_INVALID_STATE_1              = 0x421a,
  DBG_APS_SM_UDR_INVALID_STATE_2              = 0x421b,

  DBG_APS_SM_TRANSACTION_MEMORY_FAULT_1       = 0x421c,

  //DBG_APS_SM_ENCRYPTION_MEMORY_FAULT_1        = 0x421d,
  //DBG_APS_SM_ENCRYPTION_MEMORY_FAULT_2        = 0x421e,

  //DBG_APS_SM_DECRYPTION_MEMORY_FAULT_1        = 0x421f,

  //DBG_SM_INVALID_SSP_SKKE_CONF                = 0x4220,

  /* APS_SM_SSPE */
  DBG_APS_SM_SSPE_INVALID_BUFFER_TYPE         = 0x4221,

  //DBG_APS_SM_EKREQ_MEMORY_FAULT_1             = 0x4222,
  //DBG_APS_SM_EKREQ_MEMORY_FAULT_1             = 0x4223,
  DBG_APS_SM_EKREQ_INVALID_IND                = 0x4224,

  DBG_APS_SM_EKRESP_INVALID_RESP              = 0x4225,
  DBG_APS_SM_EKRESP_INVALID_NWK_CONF          = 0x4226,
  DBG_APS_SM_EKRESP_INVALID_STATE_1           = 0x4227,
  DBG_APS_SM_EKRESP_INVALID_STATE_2           = 0x4228,

  DBG_APS_SM_AUI_INVALID_REQ                  = 0x4229,

  //APS_DM_UNKNOWN_BUFFER_TYPE_0                = 0x422a,
  //APS_DM_MEMORY_FAULT_0                       = 0x422b,

  // NULL Pointer asserts 0x4300 - 0x43ff
  DBG_APS_NULL_POINTER_0  = 0x4300, // apsDataManager.c apsMakeApsDataConf() 
  DBG_APS_NULL_POINTER_1  = 0x4301, // apsDataManager.c apsNwkDataConfProcess()
  DBG_APS_NULL_POINTER_2  = 0x4302, // apsControlManager.c apsSendStopConf()
  DBG_APS_NULL_POINTER_3  = 0x4303, // apsControlManager.c apsNwkResetConf()
  DBG_APS_NULL_POINTER_4  = 0x4304, // apsControlManager.c APS_StartReq()
  DBG_APS_NULL_POINTER_5  = 0x4305, // apsControlManager.c apsSendStopConf()
  DBG_APS_NULL_POINTER_6  = 0x4306, // apsDataManager.c apsMakeNwkDataResp()
  DBG_APS_NULL_POINTER_7  = 0x4307, // apsSmRdi.c sendRdc()
  DBG_APS_NULL_POINTER_8  = 0x4308, // apsSmSkr.c sendSkc()
  DBG_APS_NULL_POINTER_9  = 0x4309, // apsSmTkr.c sendTkc()
  DBG_APS_NULL_POINTER_10 = 0x430a, // apsSmUdr.c sendUdc()
} ApsDbgCodeId_t;

typedef enum
{
  LOG_APS_APS_DATA_REQ,
  LOG_APS_NWK_DATA_REQ
} ApsLogCodeId_t;

/******************************************************************************
                   External variables section
******************************************************************************/

/******************************************************************************
                   Prototypes section
******************************************************************************/

/******************************************************************************
                   Inline static functions section
******************************************************************************/


#endif  //#ifndef _APSDBG_H

//eof apsDbg.h
