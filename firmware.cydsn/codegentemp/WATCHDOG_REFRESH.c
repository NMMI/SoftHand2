/*******************************************************************************
* File Name: WATCHDOG_REFRESH.c  
* Version 1.80
*
* Description:
*  This file contains API to enable firmware control of a Control Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WATCHDOG_REFRESH.h"

/* Check for removal by optimization */
#if !defined(WATCHDOG_REFRESH_Sync_ctrl_reg__REMOVED)

    
/*******************************************************************************
* Function Name: WATCHDOG_REFRESH_Write
********************************************************************************
*
* Summary:
*  Write a byte to the Control Register.
*
* Parameters:
*  control:  The value to be assigned to the Control Register.
*
* Return:
*  None.
*
*******************************************************************************/
void WATCHDOG_REFRESH_Write(uint8 control) 
{
    WATCHDOG_REFRESH_Control = control;
}


/*******************************************************************************
* Function Name: WATCHDOG_REFRESH_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Control Register.
*
* Parameters:
*  None.
*
* Return:
*  Returns the current value in the Control Register.
*
*******************************************************************************/
uint8 WATCHDOG_REFRESH_Read(void) 
{
    return WATCHDOG_REFRESH_Control;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
