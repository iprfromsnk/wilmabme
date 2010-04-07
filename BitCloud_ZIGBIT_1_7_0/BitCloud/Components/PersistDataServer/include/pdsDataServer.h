/***************************************************************************//**
  \file pdsDataServer.h

  \brief The header file describes the Persistence Data Server interface

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    28/09/07 A. Khromykh - Created
*****************************************************************************/

#ifndef _PERSISTDATASERVER_H
#define _PERSISTDATASERVER_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <configServer.h>

/******************************************************************************
                   Types section
******************************************************************************/
//! PDS state result after a command call
typedef enum
{
  PDS_SUCCESS,                    //!< - Command completed successfully
  PDS_EEPROM_ERROR,               //!< - EEPROM error occured
  PDS_CRC_ERROR,                  //!< - Wrong CRC
  PDS_INVALID_REQUEST,	          //!< - Some parameters are wrong
  PDS_EEPROM_BUSY                 //!< - EEPROM is busy
} PDS_DataServerState_t;

//! \cond internal
/***************************************************************************//**
\brief Reads all parameters from EEPROM to Config Server memory.

Reads all parameters from EEPROM to Config Server memory and also checks CRC of 
EEPROM stack parameters. In case of wrong CRC ConfigServer should reset EEPROM stack
parameters to default values.

\return - PDS state as a result of initiation.
*******************************************************************************/
PDS_DataServerState_t PDS_Init(void);
//! \endcond

/*****************************************************************************//**
\brief Writes default values of parameters to EEPROM

\return - PDS state as a result of setting parameters to default state
*******************************************************************************/
PDS_DataServerState_t PDS_SetToDefault(void);

/***************************************************************************//**
\brief Must be called only from ::APL_TaskHandler() function.\n
Function forces writing data from config server to eeprom. After return from function
all Config Server data are stored into EEPROM.
*******************************************************************************/
void PDS_FlushData(void);

/*****************************************************************************//**
\brief Must be called only from ::APL_TaskHandler() function.\n
Reads data from user area of EEPROM.

\param[in] offset - data offset
\param[in] data - pointer to user data area
\param[in] length - data length
\param[in] callback - callback method. If callback is NULL, then data will be read syncronous.

\return - PDS state as a result of data reading operation
*******************************************************************************/
PDS_DataServerState_t PDS_ReadUserData(uint16_t offset, uint8_t *data, uint16_t length, void (*callback)(void));

/****************************************************************************//**
\brief Must be called only from ::APL_TaskHandler() function.\n
Writes data to user area of EEPROM.

\param[in] offset - data offset
\param[in] data - pointer to user data area
\param[in] length - data length
\param[in] callback - callback method. If callback is NULL, then data will be write syncronous.  

\return - PDS state as a result of data writing operation
*******************************************************************************/
PDS_DataServerState_t PDS_WriteUserData(uint16_t offset, uint8_t *data, uint16_t length, void (*callback)(void));

#endif  //#ifndef _PERSISTDATASERVER_H

