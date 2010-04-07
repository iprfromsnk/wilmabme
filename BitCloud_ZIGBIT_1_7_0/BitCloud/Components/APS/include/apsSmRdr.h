/*************************************************************************//**
  \file apsSmRdr.h

  \brief APSME-REMOVE-DEVICE.request feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRDR_H
#define _APSSMRDR_H

#ifdef _SECURITY_
#include <apsMemoryManager.h>

extern void apsSmRdrProcess(void);
extern void apsSmRdrSspConf(ApsBuffer_t *buffer, uint8_t status);
extern void apsResetSmRdr(void);

#endif  //#ifdef _SECURITY_

#endif  //#ifndef _APSSMUDR_H

//eof apsSmRdr.h

