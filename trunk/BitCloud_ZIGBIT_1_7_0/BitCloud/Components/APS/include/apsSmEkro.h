/*************************************************************************//**
  \file apsSmEkro.h

  \brief SKKE Protocol Routing feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMEKRO_H
#define _APSSMEKRO_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>

extern void apsSmEkroProcess(void);
extern bool apsSmEkroNwkDataInd(NWK_DataInd_t *ind);
extern void apsResetSmEkro(void);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMEKRO_H

//eof apsSmEkro.h

