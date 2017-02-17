/*******************************************************************************
* File Name: INIT_SOC_PM.c
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

#include "INIT_SOC.h"

/* Check for removal by optimization */
#if !defined(INIT_SOC_Sync_ctrl_reg__REMOVED)

static INIT_SOC_BACKUP_STRUCT  INIT_SOC_backup = {0u};

    
/*******************************************************************************
* Function Name: INIT_SOC_SaveConfig
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
void INIT_SOC_SaveConfig(void) 
{
    INIT_SOC_backup.controlState = INIT_SOC_Control;
}


/*******************************************************************************
* Function Name: INIT_SOC_RestoreConfig
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
void INIT_SOC_RestoreConfig(void) 
{
     INIT_SOC_Control = INIT_SOC_backup.controlState;
}


/*******************************************************************************
* Function Name: INIT_SOC_Sleep
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
void INIT_SOC_Sleep(void) 
{
    INIT_SOC_SaveConfig();
}


/*******************************************************************************
* Function Name: INIT_SOC_Wakeup
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
void INIT_SOC_Wakeup(void)  
{
    INIT_SOC_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
