/********************************************************************************//**
  \file sspDbg.h
  
  \brief 
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
**********************************************************************************/
#ifndef _SSPDBGH
#define _SSPDBGH

#include <dbg.h>

typedef enum
{
  SSPSFPHANDLERC_SSPENCRYPTFRAMEREQHANDLER_00 = 0x7800,
  SSPMANAGER_TASKHANDLER_00                   = 0x7801,
  SSPMANAGER_TASKHANDLER_01                   = 0x7802,
  SSPCCM_SSPAESCONF_00                        = 0x7803,
  SSPSFPHANDLERC_CCMCONFIRM_00                = 0x7804,
  SSPHASHHANDLERC_BCBHASHCONF_00              = 0x7805,
  SSPSFPHANDLERC_SSPKEYEDHASHMACCONFIRM_00    = 0x7806,
  SSPSKKEHANDLERC_HASHCONFIRM_00              = 0x7807,
  SSPMANAGER_SENDREQTOHANDLER_00              = 0x7808,
  SSPHASHHANDLERC_SSPBCBHASH_0                = 0x7809,
} SspDbgCodeId_t;
#endif // _SSPDBGH
