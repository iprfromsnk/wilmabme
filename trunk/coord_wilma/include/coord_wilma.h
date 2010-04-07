/**************************************************************************//**
  \file coord_wilma.h
  
  \brief WILMA project coordinator

  \author
    Görög, Balázs

  \internal
    History:
	21 febr 2010 created     
******************************************************************************/
#ifndef _COORD_WILMA_H
#define _COORD_WILMA_H



/******************************************************************************
                    Defines section
******************************************************************************/




typedef enum         // Type specifing application state
{
  APP_INITING_STATE,
  APP_NETWORK_STARTING_STATE,
  APP_IN_NETWORK_STATE,
} AppState_t;

#endif // _COORD_WILMA_H

// eof coord_wilma.h
