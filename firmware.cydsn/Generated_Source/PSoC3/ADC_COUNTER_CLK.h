/*******************************************************************************
* File Name: ADC_COUNTER_CLK.h
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

#if !defined(CY_CLOCK_ADC_COUNTER_CLK_H)
#define CY_CLOCK_ADC_COUNTER_CLK_H

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

void ADC_COUNTER_CLK_Start(void) ;
void ADC_COUNTER_CLK_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void ADC_COUNTER_CLK_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void ADC_COUNTER_CLK_StandbyPower(uint8 state) ;
void ADC_COUNTER_CLK_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 ADC_COUNTER_CLK_GetDividerRegister(void) ;
void ADC_COUNTER_CLK_SetModeRegister(uint8 modeBitMask) ;
void ADC_COUNTER_CLK_ClearModeRegister(uint8 modeBitMask) ;
uint8 ADC_COUNTER_CLK_GetModeRegister(void) ;
void ADC_COUNTER_CLK_SetSourceRegister(uint8 clkSource) ;
uint8 ADC_COUNTER_CLK_GetSourceRegister(void) ;
#if defined(ADC_COUNTER_CLK__CFG3)
void ADC_COUNTER_CLK_SetPhaseRegister(uint8 clkPhase) ;
uint8 ADC_COUNTER_CLK_GetPhaseRegister(void) ;
#endif /* defined(ADC_COUNTER_CLK__CFG3) */

#define ADC_COUNTER_CLK_Enable()                       ADC_COUNTER_CLK_Start()
#define ADC_COUNTER_CLK_Disable()                      ADC_COUNTER_CLK_Stop()
#define ADC_COUNTER_CLK_SetDivider(clkDivider)         ADC_COUNTER_CLK_SetDividerRegister(clkDivider, 1u)
#define ADC_COUNTER_CLK_SetDividerValue(clkDivider)    ADC_COUNTER_CLK_SetDividerRegister((clkDivider) - 1u, 1u)
#define ADC_COUNTER_CLK_SetMode(clkMode)               ADC_COUNTER_CLK_SetModeRegister(clkMode)
#define ADC_COUNTER_CLK_SetSource(clkSource)           ADC_COUNTER_CLK_SetSourceRegister(clkSource)
#if defined(ADC_COUNTER_CLK__CFG3)
#define ADC_COUNTER_CLK_SetPhase(clkPhase)             ADC_COUNTER_CLK_SetPhaseRegister(clkPhase)
#define ADC_COUNTER_CLK_SetPhaseValue(clkPhase)        ADC_COUNTER_CLK_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(ADC_COUNTER_CLK__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define ADC_COUNTER_CLK_CLKEN              (* (reg8 *) ADC_COUNTER_CLK__PM_ACT_CFG)
#define ADC_COUNTER_CLK_CLKEN_PTR          ((reg8 *) ADC_COUNTER_CLK__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define ADC_COUNTER_CLK_CLKSTBY            (* (reg8 *) ADC_COUNTER_CLK__PM_STBY_CFG)
#define ADC_COUNTER_CLK_CLKSTBY_PTR        ((reg8 *) ADC_COUNTER_CLK__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define ADC_COUNTER_CLK_DIV_LSB            (* (reg8 *) ADC_COUNTER_CLK__CFG0)
#define ADC_COUNTER_CLK_DIV_LSB_PTR        ((reg8 *) ADC_COUNTER_CLK__CFG0)
#define ADC_COUNTER_CLK_DIV_PTR            ((reg16 *) ADC_COUNTER_CLK__CFG0)

/* Clock MSB divider configuration register. */
#define ADC_COUNTER_CLK_DIV_MSB            (* (reg8 *) ADC_COUNTER_CLK__CFG1)
#define ADC_COUNTER_CLK_DIV_MSB_PTR        ((reg8 *) ADC_COUNTER_CLK__CFG1)

/* Mode and source configuration register */
#define ADC_COUNTER_CLK_MOD_SRC            (* (reg8 *) ADC_COUNTER_CLK__CFG2)
#define ADC_COUNTER_CLK_MOD_SRC_PTR        ((reg8 *) ADC_COUNTER_CLK__CFG2)

#if defined(ADC_COUNTER_CLK__CFG3)
/* Analog clock phase configuration register */
#define ADC_COUNTER_CLK_PHASE              (* (reg8 *) ADC_COUNTER_CLK__CFG3)
#define ADC_COUNTER_CLK_PHASE_PTR          ((reg8 *) ADC_COUNTER_CLK__CFG3)
#endif /* defined(ADC_COUNTER_CLK__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define ADC_COUNTER_CLK_CLKEN_MASK         ADC_COUNTER_CLK__PM_ACT_MSK
#define ADC_COUNTER_CLK_CLKSTBY_MASK       ADC_COUNTER_CLK__PM_STBY_MSK

/* CFG2 field masks */
#define ADC_COUNTER_CLK_SRC_SEL_MSK        ADC_COUNTER_CLK__CFG2_SRC_SEL_MASK
#define ADC_COUNTER_CLK_MODE_MASK          (~(ADC_COUNTER_CLK_SRC_SEL_MSK))

#if defined(ADC_COUNTER_CLK__CFG3)
/* CFG3 phase mask */
#define ADC_COUNTER_CLK_PHASE_MASK         ADC_COUNTER_CLK__CFG3_PHASE_DLY_MASK
#endif /* defined(ADC_COUNTER_CLK__CFG3) */

#endif /* CY_CLOCK_ADC_COUNTER_CLK_H */


/* [] END OF FILE */
