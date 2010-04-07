/***************************************************************************//**
  \file apsSmAui.h

  \brief APSME-AUTHENTICATE.indication feature header file

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal         
  History:
    07/11/07 A. Potashov - Created.
*****************************************************************************/

#ifndef _APSSMAUI_H
#define _APSSMAUI_H

#ifdef _SECURITY_
#ifdef _HIGH_SECURITY_

#include <aps.h>
#include <apsMemoryManager.h>

extern void apsSmAuiReqHandler(APS_AuthenticateReq_t *req);
extern bool apsAuiNwkDataInd(NWK_DataInd_t *ind);
extern void apsSmAuiProcess(void);
extern void apsResetSmAui(void);
extern void apsSmAuiTimeoutHandler(ApsBuffer_t *sspReq);

#endif //#ifdef _HIGH_SECURITY_
#endif //#ifdef _SECURITY_

#endif //#ifndef _APSSMAUI_H

//eof apsSmAui.h

