/*******************************************************************************
* File Name: SHIFTREG_ENC_4_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SHIFTREG_ENC_4.h"

static SHIFTREG_ENC_4_BACKUP_STRUCT SHIFTREG_ENC_4_backup =
{
    SHIFTREG_ENC_4_DISABLED,

    ((uint32) SHIFTREG_ENC_4_DEFAULT_A0),
    ((uint32) SHIFTREG_ENC_4_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) SHIFTREG_ENC_4_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: SHIFTREG_ENC_4_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SHIFTREG_ENC_4_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    SHIFTREG_ENC_4_backup.saveSrA0Reg   = CY_GET_REG24(SHIFTREG_ENC_4_SHIFT_REG_LSB_PTR);
    SHIFTREG_ENC_4_backup.saveSrA1Reg   = CY_GET_REG24(SHIFTREG_ENC_4_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        SHIFTREG_ENC_4_backup.saveSrIntMask = SHIFTREG_ENC_4_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: SHIFTREG_ENC_4_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SHIFTREG_ENC_4_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG24(SHIFTREG_ENC_4_SHIFT_REG_LSB_PTR, SHIFTREG_ENC_4_backup.saveSrA0Reg);
    CY_SET_REG24(SHIFTREG_ENC_4_SHIFT_REG_VALUE_LSB_PTR, SHIFTREG_ENC_4_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        SHIFTREG_ENC_4_SR_STATUS_MASK = ((uint8) SHIFTREG_ENC_4_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: SHIFTREG_ENC_4_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void SHIFTREG_ENC_4_Sleep(void) 
{
    SHIFTREG_ENC_4_backup.enableState = ((uint8) SHIFTREG_ENC_4_IS_ENABLED);

    SHIFTREG_ENC_4_Stop();
    SHIFTREG_ENC_4_SaveConfig();
}


/*******************************************************************************
* Function Name: SHIFTREG_ENC_4_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void SHIFTREG_ENC_4_Wakeup(void) 
{
    SHIFTREG_ENC_4_RestoreConfig();

    if(0u != SHIFTREG_ENC_4_backup.enableState)
    {
        SHIFTREG_ENC_4_Enable();
    }
}


/* [] END OF FILE */
