/*******************************************************************************
* File Name: WATCHDOG_COUNTER_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WATCHDOG_COUNTER.h"

static WATCHDOG_COUNTER_backupStruct WATCHDOG_COUNTER_backup;


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  WATCHDOG_COUNTER_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void WATCHDOG_COUNTER_SaveConfig(void) 
{
    #if (!WATCHDOG_COUNTER_UsingFixedFunction)

        WATCHDOG_COUNTER_backup.CounterUdb = WATCHDOG_COUNTER_ReadCounter();

        #if(!WATCHDOG_COUNTER_ControlRegRemoved)
            WATCHDOG_COUNTER_backup.CounterControlRegister = WATCHDOG_COUNTER_ReadControlRegister();
        #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved) */

    #endif /* (!WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  WATCHDOG_COUNTER_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void WATCHDOG_COUNTER_RestoreConfig(void) 
{      
    #if (!WATCHDOG_COUNTER_UsingFixedFunction)

       WATCHDOG_COUNTER_WriteCounter(WATCHDOG_COUNTER_backup.CounterUdb);

        #if(!WATCHDOG_COUNTER_ControlRegRemoved)
            WATCHDOG_COUNTER_WriteControlRegister(WATCHDOG_COUNTER_backup.CounterControlRegister);
        #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved) */

    #endif /* (!WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  WATCHDOG_COUNTER_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void WATCHDOG_COUNTER_Sleep(void) 
{
    #if(!WATCHDOG_COUNTER_ControlRegRemoved)
        /* Save Counter's enable state */
        if(WATCHDOG_COUNTER_CTRL_ENABLE == (WATCHDOG_COUNTER_CONTROL & WATCHDOG_COUNTER_CTRL_ENABLE))
        {
            /* Counter is enabled */
            WATCHDOG_COUNTER_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            WATCHDOG_COUNTER_backup.CounterEnableState = 0u;
        }
    #else
        WATCHDOG_COUNTER_backup.CounterEnableState = 1u;
        if(WATCHDOG_COUNTER_backup.CounterEnableState != 0u)
        {
            WATCHDOG_COUNTER_backup.CounterEnableState = 0u;
        }
    #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved) */
    
    WATCHDOG_COUNTER_Stop();
    WATCHDOG_COUNTER_SaveConfig();
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  WATCHDOG_COUNTER_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void WATCHDOG_COUNTER_Wakeup(void) 
{
    WATCHDOG_COUNTER_RestoreConfig();
    #if(!WATCHDOG_COUNTER_ControlRegRemoved)
        if(WATCHDOG_COUNTER_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            WATCHDOG_COUNTER_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved) */
    
}


/* [] END OF FILE */
