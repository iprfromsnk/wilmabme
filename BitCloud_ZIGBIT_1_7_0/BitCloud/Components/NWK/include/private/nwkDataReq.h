/**************************************************************************//**
  \file nwkDataReq.h

  \brief Interface of the data request component.

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    29/08/09 M. Gekk - Created.
 ******************************************************************************/
#if !defined _NWK_DATA_REQ_H
#define _NWK_DATA_REQ_H

/******************************************************************************
                             Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Reset the data request component.
 ******************************************************************************/
void  nwkResetDataConf(void);

/**************************************************************************//**
  \brief Main task handler of the data request component.
 ******************************************************************************/
void  nwkDataConfTaskHandler(void);

#endif /* _NWK_DATA_REQ_H */
/* eof nwkDataReq.h */
