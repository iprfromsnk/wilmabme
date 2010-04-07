/************************************************************************//**
  \file zdoDbg.h

  \brief The header file describes the ZDO debug codes of assert function

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
    27.07.09 A. Taradov - Refactoring
******************************************************************************/

#ifndef _ZDODBG_H
#define _ZDODBG_H

#include <dbg.h>

typedef enum ZdoDbgCode_t_
{
  ZDO_ASSERT_MESSAGE                      = 0x5000,
  ZDO_NULL_CONFIRM_MESSAGE                = 0x5001,
  ZDO_UNKNOWN_DEVICE_TYPE_MESSAGE         = 0x5002,
  ZDO_UNKNOWN_EVENT_MESSAGE               = 0x5003,
  ZDO_UNKNOWN_STATE_MESSAGE               = 0x5004,
  ZDO_UNEXPECTED_FAIL_CONFIRM_MESSAGE     = 0x5005,
  ZDO_UNKNOWN_NETWORK_START_TYPE_MESSAGE  = 0x5006,
  ZDO_STACK_RESET_FAIL_MESSAGE            = 0x5007,
  ZDO_UNKNOWN_ZDP_CLUSTER_MESSAGE         = 0x5008,
  ZDO_ILLEGAL_ADDRESS_MODE_MESSAGE        = 0x5009,
  ZDO_UNKNOWN_SECURITY_KEY_MESSAGE        = 0x500A,
  ZDO_UNEXPECTED_CALLBACK                 = 0x500B,
  ZDO_NULL_CALLBACK_WAKEUP_CONF           = 0x500C,
  ZDO_NULL_CALLBACK_SLEEP_CONF            = 0x500D,
  ZDO_NULL_CALLBACK_SET_TX_POWER_CONF_0   = 0x500E,
  ZDO_NULL_CALLBACK_SET_TX_POWER_CONF_1   = 0x500F,
  ZDO_NULL_CALLBACK_ENDTOENDAPPKEY_CONF   = 0x5010,
  ZDO_NULL_CALLBACK_STARTNETWORK_CONF     = 0x5011,
  ZDO_NULL_UID_MESSAGE                    = 0x5012,
  ZDO_ZDP_MANAGER_QUEUE_EMPTY             = 0x5013,
  ZDO_INVALID_ZDP_REQUEST_STATE           = 0x5014,

  ZDO_STATE_MACHINE_0                     = 0x5015,
  ZDO_STATE_MACHINE_1                     = 0x5016,
  ZDO_STATE_MACHINE_2                     = 0x5017,
  ZDO_STATE_MACHINE_3                     = 0x5018,
  ZDO_STATE_MACHINE_4                     = 0x5019,
  ZDO_STATE_MACHINE_5                     = 0x501a,
  ZDO_STATE_MACHINE_6                     = 0x501b,
  ZDO_STATE_MACHINE_7                     = 0x501c,
  ZDO_STATE_MACHINE_8                     = 0x501d,
  ZDO_STATE_MACHINE_9                     = 0x501e,
  ZDO_STATE_MACHINE_10                    = 0x501f,
  ZDO_STATE_MACHINE_11                    = 0x5020,
  ZDO_STATE_MACHINE_12                    = 0x5021,
  ZDO_STATE_MACHINE_13                    = 0x5022,
  ZDO_STATE_MACHINE_14                    = 0x5023,
  ZDO_STATE_MACHINE_15                    = 0x5024,
  ZDO_STATE_MACHINE_16                    = 0x5025,
  ZDO_STATE_MACHINE_17                    = 0x5026,
} ZdoDbgCode_t;

#endif /*ZDODBG_H_*/
