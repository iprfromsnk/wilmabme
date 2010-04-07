/*************************************************************************//**
  \file apsSmTki.h

  \brief APSME-TRANSPORT-KEY.indication feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMTKI_H
#define _APSSMTKI_H

#ifdef _SECURITY_

#include <apsMemoryManager.h>
#include <apsSecurityManager.h>

#ifdef _HIGH_SECURITY_
extern void apsSmTkiNwkDataInd(ApsBuffer_t *buffer);
#endif //#ifdef _HIGH_SECURITY_

extern bool apsSmTkiUnsecuredInd(NWK_DataInd_t *ind);
extern void apsSmTkiProcess(void);

#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMTKI_H

//eof apsSmTki.h

