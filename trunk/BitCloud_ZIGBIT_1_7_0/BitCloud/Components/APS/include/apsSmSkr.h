/*************************************************************************//**
  \file apsSmSkr.h

  \brief APSME-SWITCH-KEY.request feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMSKR_H
#define _APSSMSKR_H

#ifdef _SECURITY_
#include <apsMemoryManager.h>

extern void apsSmSkrProcess(void);
extern void apsSmSkrSspConf(ApsBuffer_t *buffer, uint8_t status);
extern void apsResetSmSkr(void);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMSKR_H

//eof apsSmSkr.h

