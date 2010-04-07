/**************************************************************************//**
  \file nwkAddrConflict.h

  \brief Interface of address conflict resolver.
   
  \author
    Atmel Corporation: http://www.atmel.com \n
    Support email: avr@atmel.com

  Copyright (c) 2008 , Atmel Corporation. All rights reserved.
  Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
   History:
    23/06/2009  Max Gekk - Created
 ******************************************************************************/
#if  !defined  _NWK_ADDR_CONFLICT_H
#define  _NWK_ADDR_CONFLICT_H

/******************************************************************************
                              Includes section
 ******************************************************************************/
#include  <nwk.h>
#include  <nwkStatusReq.h>

/******************************************************************************
                               Types section
 ******************************************************************************/
/*  Declaration of address conflict confirmation parameters. */
typedef  struct  _NwkAddrConflictConf_t
{
  /* Status of address conflict resolution. */
  NWK_Status_t  status;
}  NwkAddrConflictConf_t;

/* Type of request with address conflict information. */
typedef  struct  _NwkAddrConflictReq_t
{
  /* Service field - for internal needs. */
  struct
  {
    void  *next;
  }  service;
  /* Potentially conflict address. */
  ShortAddr_t  shortAddr;
  /* Only own or children's address conflict should be resolved. */
  bool onlyOwnConflict;
  /* Confirmation  of address conflict resolution.. */
  void (* nwkAddrConflictConf)(NwkAddrConflictConf_t  *conf);
  NwkAddrConflictConf_t  confirm;
}  NwkAddrConflictReq_t;

/* Internal states of the address conflict component. */
typedef  enum  _NwkAddrConflictState_t
{
  NWK_ADDR_CONFLICT_IDLE_STATE = 0xAA,
  NWK_ADDR_CONFLICT_FIRST_STATE = 0x43,
  NWK_ADDR_CONFLICT_BEGIN_STATE = NWK_ADDR_CONFLICT_FIRST_STATE,
  NWK_ADDR_CONFLICT_MAC_SET_STATE = 0x44,
  NWK_ADDR_CONFLICT_REJOIN_STATE = 0x45,
  NWK_ADDR_CONFLICT_SEND_STATUS_STATE = 0x46,
  NWK_ADDR_CONFLICT_CONFIRM_STATE = 0x47,
  NWK_ADDR_CONFLICT_LAST_STATE
}  NwkAddrConflictState_t;

/* Internal variables of the network manager component. */
typedef  struct  _NwkAddrConflict_t
{
  /* finite-state machine */
  NwkAddrConflictState_t  state;
  /* Queue of requests to resolve address conflict. */
  QueueDescriptor_t  queue;
  union
  {
    MAC_SetReq_t  macSet;
    NWK_JoinReq_t  rejoin;
    NwkStatusReq_t  nwkStatus;    
  };
}  NwkAddrConflict_t;

/******************************************************************************
                              Prototypes section
 ******************************************************************************/
/**************************************************************************//**
  \brief Request to resolve address conflict.
  \param req - address conflict information.
 ******************************************************************************/
void  nwkAddrConflictReq(NwkAddrConflictReq_t *const req);

/**************************************************************************//**
  \brief Reset address conflict component.
 ******************************************************************************/
void  nwkResetAddrConflict(void);

/**************************************************************************//**
  \brief Main task handler of address conflict component.
 ******************************************************************************/
void  nwkAddrConflictTaskHandler(void);

#endif  /* _NWK_ADDR_CONFLICT_H */
/* eof nwkAddrConflict.h */

