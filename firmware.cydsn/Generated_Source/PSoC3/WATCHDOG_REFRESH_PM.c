/*******************************************************************************
* File Name: WATCHDOG_REFRESH_PM.c
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

#include "WATCHDOG_REFRESH.h"

/* Check for removal by optimization */
#if !defined(WATCHDOG_REFRESH_Sync_ctrl_reg__REMOVED)

static WATCHDOG_REFRESH_BACKUP_STRUCT  WATCHDOG_REFRESH_backup = {0u};

    
/*******************************************************************************
* Function Name: WATCHDOG_REFRESH_SaveConfig
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
void WATCHDOG_REFRESH_SaveConfig(void) 
{
    WATCHDOG_REFRESH_backup.controlState = WATCHDOG_REFRESH_Control;
}


/*******************************************************************************
* Function Name: WATCHDOG_REFRESH_RestoreConfig
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
void WATCHDOG_REFRESH_RestoreConfig(void) 
{
     WATCHDOG_REFRESH_Control = WATCHDOG_REFRESH_backup.controlState;
}


/*******************************************************************************
* Function Name: WATCHDOG_REFRESH_Sleep
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
void WATCHDOG_REFRESH_Sleep(void) 
{
    WATCHDOG_REFRESH_SaveConfig();
}


/*******************************************************************************
* Function Name: WATCHDOG_REFRESH_Wakeup
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
void WATCHDOG_REFRESH_Wakeup(void)  
{
    WATCHDOG_REFRESH_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
