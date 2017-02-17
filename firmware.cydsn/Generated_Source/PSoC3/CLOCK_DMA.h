/*******************************************************************************
* File Name: CLOCK_DMA.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_CLOCK_DMA_H)
#define CY_CLOCK_CLOCK_DMA_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void CLOCK_DMA_Start(void) ;
void CLOCK_DMA_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void CLOCK_DMA_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void CLOCK_DMA_StandbyPower(uint8 state) ;
void CLOCK_DMA_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 CLOCK_DMA_GetDividerRegister(void) ;
void CLOCK_DMA_SetModeRegister(uint8 modeBitMask) ;
void CLOCK_DMA_ClearModeRegister(uint8 modeBitMask) ;
uint8 CLOCK_DMA_GetModeRegister(void) ;
void CLOCK_DMA_SetSourceRegister(uint8 clkSource) ;
uint8 CLOCK_DMA_GetSourceRegister(void) ;
#if defined(CLOCK_DMA__CFG3)
void CLOCK_DMA_SetPhaseRegister(uint8 clkPhase) ;
uint8 CLOCK_DMA_GetPhaseRegister(void) ;
#endif /* defined(CLOCK_DMA__CFG3) */

#define CLOCK_DMA_Enable()                       CLOCK_DMA_Start()
#define CLOCK_DMA_Disable()                      CLOCK_DMA_Stop()
#define CLOCK_DMA_SetDivider(clkDivider)         CLOCK_DMA_SetDividerRegister(clkDivider, 1u)
#define CLOCK_DMA_SetDividerValue(clkDivider)    CLOCK_DMA_SetDividerRegister((clkDivider) - 1u, 1u)
#define CLOCK_DMA_SetMode(clkMode)               CLOCK_DMA_SetModeRegister(clkMode)
#define CLOCK_DMA_SetSource(clkSource)           CLOCK_DMA_SetSourceRegister(clkSource)
#if defined(CLOCK_DMA__CFG3)
#define CLOCK_DMA_SetPhase(clkPhase)             CLOCK_DMA_SetPhaseRegister(clkPhase)
#define CLOCK_DMA_SetPhaseValue(clkPhase)        CLOCK_DMA_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(CLOCK_DMA__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define CLOCK_DMA_CLKEN              (* (reg8 *) CLOCK_DMA__PM_ACT_CFG)
#define CLOCK_DMA_CLKEN_PTR          ((reg8 *) CLOCK_DMA__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define CLOCK_DMA_CLKSTBY            (* (reg8 *) CLOCK_DMA__PM_STBY_CFG)
#define CLOCK_DMA_CLKSTBY_PTR        ((reg8 *) CLOCK_DMA__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define CLOCK_DMA_DIV_LSB            (* (reg8 *) CLOCK_DMA__CFG0)
#define CLOCK_DMA_DIV_LSB_PTR        ((reg8 *) CLOCK_DMA__CFG0)
#define CLOCK_DMA_DIV_PTR            ((reg16 *) CLOCK_DMA__CFG0)

/* Clock MSB divider configuration register. */
#define CLOCK_DMA_DIV_MSB            (* (reg8 *) CLOCK_DMA__CFG1)
#define CLOCK_DMA_DIV_MSB_PTR        ((reg8 *) CLOCK_DMA__CFG1)

/* Mode and source configuration register */
#define CLOCK_DMA_MOD_SRC            (* (reg8 *) CLOCK_DMA__CFG2)
#define CLOCK_DMA_MOD_SRC_PTR        ((reg8 *) CLOCK_DMA__CFG2)

#if defined(CLOCK_DMA__CFG3)
/* Analog clock phase configuration register */
#define CLOCK_DMA_PHASE              (* (reg8 *) CLOCK_DMA__CFG3)
#define CLOCK_DMA_PHASE_PTR          ((reg8 *) CLOCK_DMA__CFG3)
#endif /* defined(CLOCK_DMA__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define CLOCK_DMA_CLKEN_MASK         CLOCK_DMA__PM_ACT_MSK
#define CLOCK_DMA_CLKSTBY_MASK       CLOCK_DMA__PM_STBY_MSK

/* CFG2 field masks */
#define CLOCK_DMA_SRC_SEL_MSK        CLOCK_DMA__CFG2_SRC_SEL_MASK
#define CLOCK_DMA_MODE_MASK          (~(CLOCK_DMA_SRC_SEL_MSK))

#if defined(CLOCK_DMA__CFG3)
/* CFG3 phase mask */
#define CLOCK_DMA_PHASE_MASK         CLOCK_DMA__CFG3_PHASE_DLY_MASK
#endif /* defined(CLOCK_DMA__CFG3) */

#endif /* CY_CLOCK_CLOCK_DMA_H */


/* [] END OF FILE */
