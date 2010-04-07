/*************************************************************************//**
  \file apsSmRki.h

  \brief APSME-REQUEST-KEY.indication feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMRKI_H
#define _APSSMRKI_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_
#include <apsMemoryManager.h>

#include <apsSecurityManager.h>
extern void apsSmRkiNwkDataInd(ApsBuffer_t *buffer);
extern bool apsSmRkiUnsecuredInd(NWK_DataInd_t *ind);
extern void apsSmRkiNwkDataInd(ApsBuffer_t *buffer);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY

#endif  //#ifndef _APSSMRDI_H

//eof apsSmRki.h

