/*******************************************************************************
* File Name: DMA_SOC.h  
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

#if !defined(CY_CONTROL_REG_DMA_SOC_H) /* CY_CONTROL_REG_DMA_SOC_H */
#define CY_CONTROL_REG_DMA_SOC_H

#include "cytypes.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 controlState;

} DMA_SOC_BACKUP_STRUCT;


/***************************************
*         Function Prototypes 
***************************************/

void    DMA_SOC_Write(uint8 control) ;
uint8   DMA_SOC_Read(void) ;

void DMA_SOC_SaveConfig(void) ;
void DMA_SOC_RestoreConfig(void) ;
void DMA_SOC_Sleep(void) ; 
void DMA_SOC_Wakeup(void) ;


/***************************************
*            Registers        
***************************************/

/* Control Register */
#define DMA_SOC_Control        (* (reg8 *) DMA_SOC_Sync_ctrl_reg__CONTROL_REG )
#define DMA_SOC_Control_PTR    (  (reg8 *) DMA_SOC_Sync_ctrl_reg__CONTROL_REG )

#endif /* End CY_CONTROL_REG_DMA_SOC_H */


/* [] END OF FILE */
