/************************************************************************//**
  \file zdoBindingManager.h

  \brief The header file describes the constants and types of
  binding component of ZDO

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      03/06/09 A.Potashov - created
******************************************************************************/

#ifndef ZDOBINDINGMANAGER_H_
#define ZDOBINDINGMANAGER_H_

#ifdef _COORDINATOR_

#ifndef ZDO_DEVICE_BIND_REQ_TIMEOUT
#define ZDO_DEVICE_BIND_REQ_TIMEOUT       2000L
#endif

#endif  //#ifdef _COORDINATOR_


void zdoBindManagerRequestCreate(void);
void zdoBindManagerInd(void);

#endif /*ZDOBINDINGMANAGER_H_*/
