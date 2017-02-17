/*******************************************************************************
* File Name: WATCHDOG_ENABLER.h  
* Version 1.80
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CONTROL_REG_WATCHDOG_ENABLER_H) /* CY_CONTROL_REG_WATCHDOG_ENABLER_H */
#define CY_CONTROL_REG_WATCHDOG_ENABLER_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} WATCHDOG_ENABLER_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    WATCHDOG_ENABLER_Write(uint8 control) ;
uint8   WATCHDOG_ENABLER_Read(void) ;

void WATCHDOG_ENABLER_SaveConfig(void) ;
void WATCHDOG_ENABLER_RestoreConfig(void) ;
void WATCHDOG_ENABLER_Sleep(void) ; 
void WATCHDOG_ENABLER_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define WATCHDOG_ENABLER_Control        (* (reg8 *) WATCHDOG_ENABLER_Sync_ctrl_reg__CONTROL_REG )
#define WATCHDOG_ENABLER_Control_PTR    (  (reg8 *) WATCHDOG_ENABLER_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_WATCHDOG_ENABLER_H */


/* [] END OF FILE */
