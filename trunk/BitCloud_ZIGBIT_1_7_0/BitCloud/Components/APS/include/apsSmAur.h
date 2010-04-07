/*************************************************************************//**
  \file apsSmAur.h

  \brief APSME-AUTHENTICATE.request feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMAUR_H
#define _APSSMAUR_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>
#include <apsMemoryManager.h>

extern bool apsAurNwkDataInd(NWK_DataInd_t *ind);
extern void apsResetSmAur(void);
extern void apsSmAurProcess(void);
extern void sendAuc(ApsBuffer_t *sspReq, APS_AuthenticateStatus_t status);
extern void apsSmAurTimeoutHandler(ApsBuffer_t *sspReq);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif  //#ifndef _APSSMKEREQ_H

//eof apsSmAur.h

