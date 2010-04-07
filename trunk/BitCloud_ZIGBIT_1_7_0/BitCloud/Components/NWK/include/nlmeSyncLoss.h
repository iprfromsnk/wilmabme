/**************************************************************************//**
  \file  nlmeSyncLoss.h

  \brief NLME-SYNC-LOSS interface
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    12/04/2009  Max Gekk - Created.
 ******************************************************************************/
#if !defined _NLME_SYNC_LOSS_H
#define _NLME_SYNC_LOSS_H
/******************************************************************************
                                Includes section
 ******************************************************************************/
#include <types.h>

/******************************************************************************
                               Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief  NLME-SYNC-LOSS indication primitive's prototype.
  \return none.
******************************************************************************/
extern void NWK_SyncLossInd(void);

#endif  /* _NLME_SYNC_LOSS_H */
/* eof nlmeSyncLoss.h */
