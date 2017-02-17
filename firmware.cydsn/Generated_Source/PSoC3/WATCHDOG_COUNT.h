/*******************************************************************************
* File Name: WATCHDOG_COUNT.h
* Version 1.0
*
* Description:
*  This header file contains registers and constants associated with the
*  Count7 component.
*
* Note:
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_COUNT7_WATCHDOG_COUNT_H)
#define CY_COUNT7_WATCHDOG_COUNT_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
* Function Prototypes
***************************************/
void  WATCHDOG_COUNT_Init(void) ;
void  WATCHDOG_COUNT_Enable(void) ;
void  WATCHDOG_COUNT_Start(void) ;
void  WATCHDOG_COUNT_Stop(void) ;
void  WATCHDOG_COUNT_WriteCounter(uint8 count) ;
uint8 WATCHDOG_COUNT_ReadCounter(void) ;
void  WATCHDOG_COUNT_WritePeriod(uint8 period) ;
uint8 WATCHDOG_COUNT_ReadPeriod(void) ;
void  WATCHDOG_COUNT_SaveConfig(void) ;
void  WATCHDOG_COUNT_RestoreConfig(void) ;
void  WATCHDOG_COUNT_Sleep(void) ;
void  WATCHDOG_COUNT_Wakeup(void) ;


/***************************************
*     Data Struct Definitions
***************************************/
/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;
    uint8 count;
} WATCHDOG_COUNT_BACKUP_STRUCT;


/***************************************
*           Global Variables
***************************************/
extern WATCHDOG_COUNT_BACKUP_STRUCT WATCHDOG_COUNT_backup;
extern uint8 WATCHDOG_COUNT_initVar;


/***************************************
* Initial Parameter
***************************************/
#define WATCHDOG_COUNT_INITIAL_PERIOD               (3u)


/***************************************
* Registers
***************************************/
#define WATCHDOG_COUNT_COUNT_REG                    (*(reg8 *) WATCHDOG_COUNT_Counter7__COUNT_REG)
#define WATCHDOG_COUNT_COUNT_PTR                    ( (reg8 *) WATCHDOG_COUNT_Counter7__COUNT_REG)
#define WATCHDOG_COUNT_PERIOD_REG                   (*(reg8 *) WATCHDOG_COUNT_Counter7__PERIOD_REG)
#define WATCHDOG_COUNT_PERIOD_PTR                   ( (reg8 *) WATCHDOG_COUNT_Counter7__PERIOD_REG)
#define WATCHDOG_COUNT_AUX_CONTROL_REG              (*(reg8 *) WATCHDOG_COUNT_Counter7__CONTROL_AUX_CTL_REG)
#define WATCHDOG_COUNT_AUX_CONTROL_PTR              ( (reg8 *) WATCHDOG_COUNT_Counter7__CONTROL_AUX_CTL_REG)


/***************************************
* Register Constants
***************************************/
#define WATCHDOG_COUNT_COUNTER_START                (0x20u)

/* This constant is used to mask the TC bit (bit#7) in the Count register */
#define WATCHDOG_COUNT_COUNT_7BIT_MASK              (0x7Fu)


#endif /* CY_COUNT7_WATCHDOG_COUNT_H */


/* [] END OF FILE */
