/***************************************************************************//**
  \file pdsCrcService.h

  \brief The header file describes the interface of crc counting  

  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/

#ifndef _PDSCRCSERVICE_H
#define _PDSCRCSERVICE_H

/******************************************************************************
                   Includes section
******************************************************************************/
#include <pdsDataServer.h>
#include <pdsAuxService.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/*******************************************************************************
check crc system area.
Parameters:
  poinetr to crc structure property.
Returns:
  none.
*******************************************************************************/
void pdsCheckCrc(PDS_ServiceCrc_t *crcStation);
	
/*******************************************************************************
read crc from eeprom.
Parameters:
  poinetr to crc structure property.
Returns:
  none
*******************************************************************************/
void pdsReadCrc(PDS_ServiceCrc_t *crcStation);

/*******************************************************************************
write crc to eeprom. (crc area 10 byte. next byte write. previous byte delete (write 0xFF)).
crc arae is ring buffer.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t pdsWriteCrc(void);

/*******************************************************************************
It is waiting when memory will be accessible for transaction
Parameters:
  none
Returns:
  none
*******************************************************************************/
void pdsWaitMemoryFree(void);

/*******************************************************************************
Dummy function for callback. 
*******************************************************************************/
void pdsDummy(void);

#ifdef __DBG_PDS__
  void pdsDbgReadAllEeprom(void);
#endif

#endif /*_PDSCRCSERVICE_H*/
