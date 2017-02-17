/*******************************************************************************
* File Name: WATCHDOG_COUNT.c
* Version 1.0
*
* Description:
*  This file provides source code for the Count7 component's API.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "WATCHDOG_COUNT.h"
#include "CyLib.h"


uint8 WATCHDOG_COUNT_initVar = 0u;


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the parameter editor
*  settings.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*  It is not necessary to call Count7_Init() because the Count7_Start() API
*  calls this function and is the preferred method to begin component
*  operation.
*
*******************************************************************************/
void WATCHDOG_COUNT_Init(void) 
{
    /* Set the initial period value from parameter editor */
    WATCHDOG_COUNT_PERIOD_REG = WATCHDOG_COUNT_INITIAL_PERIOD;
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_Enable
********************************************************************************
*
* Summary:
*  Enables the software enable of the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Theory:
*  It is not necessary to call Count7_Enable() because the Count7_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.
*  This API performs modification of auxiliary control register which is a
*  shared resource so it is required to disable interrupts until the
*  modification will complete.
*
*******************************************************************************/
void WATCHDOG_COUNT_Enable(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    /* Set the counter start bit in auxiliary control. If routed enable
    * isn't used then this will immediately star the Count7 operation.
    */
    WATCHDOG_COUNT_AUX_CONTROL_REG |= WATCHDOG_COUNT_COUNTER_START;

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables
*  the counter. The first time the routine is executed, the period is set as
*  configured in the customizer. When called to restart the counter following a
*  Count7_Stop() call, the current period value is retained.
*
* Parameters:
*  None.
*
* Global Variables:
*  WATCHDOG_COUNT_initVar - global variable.
*
* Return:
*  None.
*
*******************************************************************************/
void WATCHDOG_COUNT_Start(void) 
{
    /* If not initialized then perform initialization */
    if(WATCHDOG_COUNT_initVar == 0u)
    {
        WATCHDOG_COUNT_Init();
        WATCHDOG_COUNT_initVar = 1u;
    }

    /* Enable Count7 */
    WATCHDOG_COUNT_Enable();
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_Stop
********************************************************************************
*
* Summary:
*  Disables the software enable of the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_COUNT_Stop(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    /* Clear the counter start bit in auxiliary control. */
    WATCHDOG_COUNT_AUX_CONTROL_REG &= (uint8) ~((uint8) WATCHDOG_COUNT_COUNTER_START);

    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_WriteCounter
********************************************************************************
*
* Summary:
*  This function writes the counter directly. The counter should be disabled
*  before calling this function.
*
* Parameters:
*  count - Value to be written to counter.
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_COUNT_WriteCounter(uint8 count) 
{
    WATCHDOG_COUNT_COUNT_REG = (count & WATCHDOG_COUNT_COUNT_7BIT_MASK);
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_ReadCounter
********************************************************************************
*
* Summary:
*  This function reads the counter value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
uint8 WATCHDOG_COUNT_ReadCounter(void) 
{
    return(WATCHDOG_COUNT_COUNT_REG & WATCHDOG_COUNT_COUNT_7BIT_MASK);
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_WritePeriod
********************************************************************************
*
* Summary:
*  This function writes the period register. The actual period is one greater
*  than the value in the period register since the counting sequence starts
*  with the period register and counts down to 0 inclusive. The period of the
*  counter output does not change until the counter is reloaded following the
*  terminal count value of 0 or due to a hardware load signal.
*
* Parameters:
*  period - Period value to be written.
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_COUNT_WritePeriod(uint8 period) 
{
    WATCHDOG_COUNT_PERIOD_REG = period;
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_ReadPeriod
********************************************************************************
*
* Summary:
*  This function reads the period register.
*
* Parameters:
*  None
*
* Return:
*  uint8 - Current period value.
*
*******************************************************************************/
uint8 WATCHDOG_COUNT_ReadPeriod(void) 
{
    return(WATCHDOG_COUNT_PERIOD_REG);
}


/* [] END OF FILE */
