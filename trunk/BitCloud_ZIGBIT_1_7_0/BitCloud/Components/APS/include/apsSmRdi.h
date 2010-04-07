/*************************************************************************//**
  \file apsSmRdi.h

  \brief APSME-REMOVE-DEVICE.indication feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRDI_H
#define _APSSMRDI_H

#ifdef _SECURITY_

#include <apsMemoryManager.h>
#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmRdiNwkDataInd(ApsBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmRdiUnsecuredNwkDataInd(NWK_DataInd_t *ind);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMRDI_H

//eof apsSmRdi.h

