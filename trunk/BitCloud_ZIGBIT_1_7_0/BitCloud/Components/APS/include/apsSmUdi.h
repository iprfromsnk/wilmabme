/*************************************************************************//**
  \file apsSmUdi.h

  \brief APSME-UPDATE-DEVICE.indication feature headder file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMUDI_H
#define _APSSMUDI_H

#ifdef _SECURITY_

#include <apsMemoryManager.h>
#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmUdiNwkDataInd(ApsBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmUdiUnsecuredInd(NWK_DataInd_t *ind);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMUDI_H

//eof apsSmUdi.h

