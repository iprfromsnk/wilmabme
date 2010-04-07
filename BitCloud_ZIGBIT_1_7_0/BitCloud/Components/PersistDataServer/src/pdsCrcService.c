/***************************************************************************//**
  \file pdsCrcService.c

  \brief Persistence Data Server implementation
  
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
  History:
    22/01/08 A. Khromykh - Created
*****************************************************************************/
/******************************************************************************
                   Includes section
******************************************************************************/
#include <pdsMemAbstract.h>
#include <pdsCrcService.h>
#include <pdsAuxService.h>
#include <taskManager.h>

/*******************************************************************************
It is waiting when memory will be accessible for transaction
Parameters:
  none
Returns:
  none
*******************************************************************************/
void pdsWaitMemoryFree(void)
{
  while(IS_MEMORY_BUSY())
  {
    SYS_ForceRunTask();
  }
}

/*******************************************************************************
check crc system area.
Parameters:
  poinetr to crc structure property.
Returns:
  none.
*******************************************************************************/
void pdsCheckCrc(PDS_ServiceCrc_t *crcStation)
{
  uint8_t tdata = 0;
  MEMORY_DESCRIPTOR pdsEepromParams;

  if (NULL == crcStation)
    return;

  crcStation->crc = 0;
  pdsEepromParams.address = SYSTEM_BASE_EEPROM_ADDRESS;
  pdsEepromParams.length = 1;
  while (pdsEepromParams.address < pdsDataSize)
  {
    pdsEepromParams.data = &tdata;

    pdsWaitMemoryFree();

    if (EEPROM_ERROR == READ_MEMORY(&pdsEepromParams, NULL))
    {
      crcStation->eepromState = PDS_EEPROM_ERROR;
      return;
    }

    pdsWaitMemoryFree();

  	crcStation->crc += tdata;
  	pdsEepromParams.address++;
  }
  crcStation->eepromState = PDS_SUCCESS;
}

/*******************************************************************************
read crc from eeprom.
Parameters:
  poinetr to crc structure property.
Returns:
  none
*******************************************************************************/
void pdsReadCrc(PDS_ServiceCrc_t *crcStation)
{
  MEMORY_DESCRIPTOR eepromParams;

  if (NULL == crcStation)
    return;

  eepromParams.address = pdsDataSize;
  eepromParams.length = 1;
  while (eepromParams.address < USER_BASE_EEPROM_ADDRESS)
  {
  	eepromParams.data = &(crcStation->crc);

  	pdsWaitMemoryFree();

  	if (EEPROM_ERROR == READ_MEMORY(&eepromParams, NULL))
  	{
  	  crcStation->eepromState = PDS_EEPROM_ERROR;
  	  return;
  	}

  	pdsWaitMemoryFree();

    if (0xFF != crcStation->crc)
    {
      crcStation->position = eepromParams.address;
      crcStation->eepromState = PDS_SUCCESS;
      return;
    }
    eepromParams.address++;
  }
  crcStation->position = pdsDataSize;
  crcStation->eepromState = PDS_SUCCESS;
}

/*******************************************************************************
write crc to eeprom. (crc area 10 byte. next byte write. previous byte delete (write 0xFF)).
crc arae is ring buffer.
Parameters:
  none.
Returns:
  operation result.
*******************************************************************************/
PDS_DataServerState_t pdsWriteCrc(void)
{
  PDS_ServiceCrc_t crcRead, crcCheck;
  MEMORY_DESCRIPTOR eepromParams;
  uint8_t datadelete = 0xFF;

  pdsReadCrc(&crcRead);
  if (PDS_EEPROM_ERROR == crcRead.eepromState)
    return PDS_EEPROM_ERROR;

  pdsCheckCrc(&crcCheck);
  if (PDS_EEPROM_ERROR == crcCheck.eepromState)
    return PDS_EEPROM_ERROR;

  if (0 == (uint8_t)(crcCheck.crc + crcRead.crc))
    return PDS_SUCCESS;

  crcCheck.crc = 0 - crcCheck.crc;
  eepromParams.address = crcRead.position;
  eepromParams.data = &datadelete;
  eepromParams.length = 1;

  pdsWaitMemoryFree();

  if (EEPROM_ERROR == WRITE_MEMORY(&eepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;

  pdsWaitMemoryFree();

  if (++eepromParams.address >= USER_BASE_EEPROM_ADDRESS)
    eepromParams.address = pdsDataSize;
  eepromParams.data = &(crcCheck.crc);

  pdsWaitMemoryFree();

  if (EEPROM_ERROR == WRITE_MEMORY(&eepromParams, pdsDummy))
    return PDS_EEPROM_ERROR;

  pdsWaitMemoryFree();

  return PDS_SUCCESS;
}

#ifdef __DBG_PDS__
  uint8_t  eepromCopy[0x400u];

  void pdsDbgReadAllEeprom(void)
  {
    MEMORY_DESCRIPTOR tempEepromParams;

    tempEepromParams.address = 0;
    tempEepromParams.data = eepromCopy;
    tempEepromParams.length = 0x400u;

    pdsWaitMemoryFree();

    if (EEPROM_ERROR == READ_MEMORY(&tempEepromParams, NULL))
      return;

    pdsWaitMemoryFree();
  }
#endif
// eof pdsDataServer.c
