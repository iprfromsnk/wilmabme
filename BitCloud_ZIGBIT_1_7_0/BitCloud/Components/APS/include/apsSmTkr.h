/*************************************************************************//**
  \file apsSmTkr.h

  \brief APSME-TRANSPORT-KEY.request feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMTKR_H
#define _APSSMTKR_H

#ifdef _SECURITY_
#include <apsMemoryManager.h>

extern void apsSmTkrProcess(void);
extern void apsSmTkrSspConf(ApsBuffer_t *buffer, uint8_t status);
extern void apsResetTkr(void);
extern ShortAddr_t *apsFindNextNeibRxOffWhenIdleShortAddr(ShortAddr_t *shortAddr);
extern ExtAddr_t *apsFindNextNeibRxOffWhenIdleExtAddr(ExtAddr_t *extAddr);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMTKR_H

//eof apsSmTkr.h

