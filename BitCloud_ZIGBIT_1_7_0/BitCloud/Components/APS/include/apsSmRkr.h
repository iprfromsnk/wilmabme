/*************************************************************************//**
  \file apsSmRkr.h

  \brief APSME-REQUEST-KEY.request feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRKR_H
#define _APSSMRKR_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
#include <apsMemoryManager.h>

extern void apsSmRkrProcess(void);
extern void apsSmRkrSspConf(ApsBuffer_t *buffer, uint8_t status);
extern void apsResetSmRkr(void);

#endif  //#ifdef _HIGH_SECURITY_
#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMRKR_H

//eof apsSmRkr.h

