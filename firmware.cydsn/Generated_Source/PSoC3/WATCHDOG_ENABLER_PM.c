/*******************************************************************************
* File Name: WATCHDOG_ENABLER_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WATCHDOG_ENABLER.h"

/* Check for removal by optimization */
#if !defined(WATCHDOG_ENABLER_Sync_ctrl_reg__REMOVED)

static WATCHDOG_ENABLER_BACKUP_STRUCT  WATCHDOG_ENABLER_backup = {0u};

    
/*******************************************************************************
* Function Name: WATCHDOG_ENABLER_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_ENABLER_SaveConfig(void) 
{
    WATCHDOG_ENABLER_backup.controlState = WATCHDOG_ENABLER_Control;
}


/*******************************************************************************
* Function Name: WATCHDOG_ENABLER_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void WATCHDOG_ENABLER_RestoreConfig(void) 
{
     WATCHDOG_ENABLER_Control = WATCHDOG_ENABLER_backup.controlState;
}


/*******************************************************************************
* Function Name: WATCHDOG_ENABLER_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_ENABLER_Sleep(void) 
{
    WATCHDOG_ENABLER_SaveConfig();
}


/*******************************************************************************
* Function Name: WATCHDOG_ENABLER_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void WATCHDOG_ENABLER_Wakeup(void)  
{
    WATCHDOG_ENABLER_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
