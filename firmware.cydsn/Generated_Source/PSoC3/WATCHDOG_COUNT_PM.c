/*******************************************************************************
* File Name: WATCHDOG_COUNT_PM.c
* Version 1.0
*
* Description:
*  This file provides Low power mode APIs for Count7 component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "WATCHDOG_COUNT.h"


WATCHDOG_COUNT_BACKUP_STRUCT WATCHDOG_COUNT_backup;


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_SaveConfig
********************************************************************************
*
* Summary:
*  This function saves the component configuration and non-retention registers.
*  This function is called by the Count7_Sleep() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  WATCHDOG_COUNT_backup - used to save component configuration and non-
*  retention registers before enter sleep mode.
*
*******************************************************************************/
void WATCHDOG_COUNT_SaveConfig(void) 
{
    WATCHDOG_COUNT_backup.count = WATCHDOG_COUNT_COUNT_REG;
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for low power mode
*  operation. The Count7_Sleep() API saves the current component state using
*  Count7_SaveConfig() and disables the counter.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_COUNT_Sleep(void) 
{
    if(0u != (WATCHDOG_COUNT_AUX_CONTROL_REG & WATCHDOG_COUNT_COUNTER_START))
    {
        WATCHDOG_COUNT_backup.enableState = 1u;
        WATCHDOG_COUNT_Stop();
    }
    else
    {
        WATCHDOG_COUNT_backup.enableState = 0u;
    }

    WATCHDOG_COUNT_SaveConfig();
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_RestoreConfig
********************************************************************************
*
* Summary:
*  This function restores the component configuration and non-retention
*  registers. This function is called by the Count7_Wakeup() function.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  WATCHDOG_COUNT_backup - used to save component configuration and
*  non-retention registers before exit sleep mode.
*
*******************************************************************************/
void WATCHDOG_COUNT_RestoreConfig(void) 
{
    WATCHDOG_COUNT_COUNT_REG = WATCHDOG_COUNT_backup.count;
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNT_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when
*  Count7_Sleep() was called. The Count7_Wakeup() function calls the
*  Count7_RestoreConfig() function to restore the configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_COUNT_Wakeup(void) 
{
    WATCHDOG_COUNT_RestoreConfig();

    /* Restore enable state */
    if (WATCHDOG_COUNT_backup.enableState != 0u)
    {
        WATCHDOG_COUNT_Enable();
    }
}


/* [] END OF FILE */
