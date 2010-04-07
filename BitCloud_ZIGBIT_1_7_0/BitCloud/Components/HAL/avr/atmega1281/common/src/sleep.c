/**************************************************************************//**
  \file  sleep.c

  \brief The module to make power off mode.

  \author
      Atmel Corporation: http://www.atmel.com \n
      Support email: avr@atmel.com

    Copyright (c) 2008 , Atmel Corporation. All rights reserved.
    Licensed under Atmel's Limited License Agreement (BitCloudTM).

  \internal
    History:
      29/06/07 E. Ivanov - Created
 ******************************************************************************/
/******************************************************************************
 *   WARNING: CHANGING THIS FILE MAY AFFECT CORE FUNCTIONALITY OF THE STACK.  *
 *   EXPERT USERS SHOULD PROCEED WITH CAUTION.                                *
 ******************************************************************************/

/******************************************************************************
                   Includes section
******************************************************************************/
#include <sleepTimer.h>
#include <halSleepTimerClock.h>
#include <halRfPio.h>
#include <sleep.h>
#include <halIrq.h>
#include <halDbg.h>
#include <halAppClock.h>

/******************************************************************************
                   Prototypes section
******************************************************************************/
/**************************************************************************//**
\brief Performs calibration of the main clock generator.
******************************************************************************/
void halStartingCalibrate(void);

/**************************************************************************//**
\brief Wait for when radio will be waked up.
******************************************************************************/
void halWaitRadio(void);

#if defined(_RF_TX_RX_INDICATOR_)
/**************************************************************************//**
\brief  Turn on pin 1 (DIG3) and pin 2 (DIG4) to indicate the transmit state of
the radio transceiver.
******************************************************************************/
void phyRxTxSwitcherOn(void);

/**************************************************************************//**
\brief  Turn off pin 1 (DIG3) and pin 2 (DIG4) to indicate the transmit state of
the radio transceiver.
******************************************************************************/
void phyRxTxSwitcherOff(void);
#endif

/******************************************************************************
                   External global variables section
******************************************************************************/
extern volatile bool halEnableDtrWakeUp;
extern volatile HAL_SleepTimer_t *halSleepTimerPointer;

/******************************************************************************
                   Global variables section
******************************************************************************/
volatile WakeupStation_t halWakeupFlag = ACTIVE_MODE;
static uint32_t halTimeStartOfSleep = 0ul;

/******************************************************************************
                   Implementations section
******************************************************************************/
/******************************************************************************
  Lets the network stack to control TRSLEEP pin.
******************************************************************************/
void halPowerOn(void)
{ // will let the application the control of TRSLEEP pin
  if (SLEEP_MODE != halWakeupFlag)
    return;
  halWakeupFlag = ACTIVE_MODE;

  if (INTERNAL_RC == halGetClockSource())
  {
    GPIO_RF_SLP_TR_clr();
  }
  else
  {
    GPIO_RF_SLP_TR_make_in();
    TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0)); // no compare
    while (ASSR & HAL_ASSR_FLAGS);
  }
  GPIO_RF_SLP_TR_make_out();

  #ifdef _HAL_USE_AMPLIFIER_
    // set one on pin. Enable power amplifier.
    GPIO_POW_AMPLF_SLP_set();
  #endif

  halPostTask4(HAL_WAKEUP);
}

/******************************************************************************
Shutdowns system.
  NOTES:
  the application should be sure the poweroff will not be
  interrupted after the execution of the sleep().
******************************************************************************/
void halPowerOff(void)
{
  if (SLEEP_MODE != halWakeupFlag)
    return;  // it is a too late to sleep.

  // stop application timer clock
  halStopAppClock(); // will be shutdown
  if (0ul == halTimeStartOfSleep)
  { // start of sleep procedure
    // save time of stopping of the application timer
    halTimeStartOfSleep = halGetTimeOfSleepTimer();
  }

  #ifdef _HAL_USE_AMPLIFIER_
    // set zero on pin. Disable power amplifier.
    GPIO_POW_AMPLF_SLP_clr();
  #endif

  #if defined(_RF_TX_RX_INDICATOR_)
    // disable front end driver if that is supported
    phyRxTxSwitcherOff();
  #endif

  if (halEnableDtrWakeUp)
  { /* enable DTR (irq 4) wake up */
    halEnableIrqInterrupt(IRQ_4);
  } /* enable DTR (irq 4) wake up */

  // wait for end of eeprom writing
  while (EECR & (1 << EEPE));

  if (INTERNAL_RC == halGetClockSource())
  {
    GPIO_RF_SLP_TR_set();
    GPIO_RF_SLP_TR_make_out();

    if (NULL != halSleepTimerPointer)
    { // sleep timer is started
      SMCR = (1 << SM1) | (1 << SM0) | (1 << SE); // power-save
      __SLEEP;
      SMCR = 0;
    }
    else
    {
      halStopSleepTimerClock();
      SMCR = (1 << SM1) | (1 << SE); // power-down
      __SLEEP;
      SMCR = 0;
      halStartSleepTimerClock();
      halStartingCalibrate();
    }
  }
  else
  {
    uint8_t timsk4 = TIMSK4;
    uint8_t twcr = TWCR;
    uint8_t adcsra =  ADCSRA;
    TIMSK4 = 0;
    TWCR = 0;
    ADCSRA = 0;
    GPIO_RF_SLP_TR_make_out();
    SMCR = (1 << SM1) | (1 << SM0) | (1 << SE); // power-save
    __SLEEP;
    SMCR = 0;
    TIMSK4 = timsk4;
    TWCR = twcr;
    ADCSRA = adcsra;
  }

  // wait for time about 1 TOSC1 cycle for correct re-entering from power save mode to power save mode
  // wait for time about 1 TOSC1 cycle for correct reading TCNT2 after wake up to
  OCR2B = SOME_VALUE_FOR_SYNCHRONIZATION;
  while (ASSR & HAL_ASSR_FLAGS);
}

/******************************************************************************
  Prepares system for power-save, power-down.
  Power-down the mode is possible only when internal RC is used
  Parametres:
  none.
  Returns:
  -1 there is no possibility to power-down system.
******************************************************************************/
int HAL_Sleep(void)
{
  if (INTERNAL_RC != halGetClockSource())
  {
    if (NULL == halSleepTimerPointer)
    { // sleep timer isn't started
      return -1;
    }
    GPIO_RF_SLP_TR_make_in();

    while (ASSR & HAL_ASSR_FLAGS);
    if (!(TIMSK2 & (1 << OCIE2A)))
    { // compare interrupt is disabled
      OCR2A = 0xFF;
      while (ASSR & HAL_ASSR_FLAGS);
    }

    TCCR2A |= ((1 << COM2A1) | (1 << COM2A0)); // set OC2A on compare
    while (ASSR & HAL_ASSR_FLAGS);
    TCCR2B |= (1 << FOC2A); // force output to set OC2A
    while (ASSR & HAL_ASSR_FLAGS);
    TCCR2A &= ~((1 << COM2A1) | (1 << COM2A0)); // no compare
    while (ASSR & HAL_ASSR_FLAGS);
    TCCR2A |= (1 << COM2A1); // clear OC2A on compare
    while (ASSR & HAL_ASSR_FLAGS);
  }

  halWakeupFlag = SLEEP_MODE;  // the reset of sign of entry to the sleep mode.
  while (ASSR & HAL_ASSR_FLAGS);
  halPostTask5(HAL_SLEEP);
  return 0;
}

/******************************************************************************
 Handler for task manager. It is executed when system has waked up.
******************************************************************************/
void halWakeupHandler(void)
{
  uint32_t timeEndOfSleep;

  // save time of stopping of the application timer
  timeEndOfSleep = halGetTimeOfSleepTimer();

  timeEndOfSleep -= halTimeStartOfSleep;  // time of sleep
  halTimeStartOfSleep = 0ul;
  // adjust application timer interval
  halAdjustSleepInterval(timeEndOfSleep);
  // start application timer clock
  halStartAppClock();
  // Wait for when radio will be waked up.
  halWaitRadio();
  #if defined(_RF_TX_RX_INDICATOR_)
    // enable front end driver if that is supported
    phyRxTxSwitcherOn();
  #endif
}

// eof sleep.c
