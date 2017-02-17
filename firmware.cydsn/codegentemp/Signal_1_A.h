/*******************************************************************************
* File Name: Signal_1_A.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Signal_1_A_H) /* Pins Signal_1_A_H */
#define CY_PINS_Signal_1_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Signal_1_A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Signal_1_A_Write(uint8 value) ;
void    Signal_1_A_SetDriveMode(uint8 mode) ;
uint8   Signal_1_A_ReadDataReg(void) ;
uint8   Signal_1_A_Read(void) ;
void    Signal_1_A_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   Signal_1_A_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Signal_1_A_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define Signal_1_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define Signal_1_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define Signal_1_A_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define Signal_1_A_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define Signal_1_A_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define Signal_1_A_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define Signal_1_A_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define Signal_1_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Signal_1_A_MASK               Signal_1_A__MASK
#define Signal_1_A_SHIFT              Signal_1_A__SHIFT
#define Signal_1_A_WIDTH              1u

/* Interrupt constants */
#if defined(Signal_1_A__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Signal_1_A_SetInterruptMode() function.
     *  @{
     */
        #define Signal_1_A_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define Signal_1_A_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define Signal_1_A_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define Signal_1_A_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define Signal_1_A_INTR_MASK      (0x01u)
#endif /* (Signal_1_A__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Signal_1_A_PS                     (* (reg8 *) Signal_1_A__PS)
/* Data Register */
#define Signal_1_A_DR                     (* (reg8 *) Signal_1_A__DR)
/* Port Number */
#define Signal_1_A_PRT_NUM                (* (reg8 *) Signal_1_A__PRT) 
/* Connect to Analog Globals */                                                  
#define Signal_1_A_AG                     (* (reg8 *) Signal_1_A__AG)                       
/* Analog MUX bux enable */
#define Signal_1_A_AMUX                   (* (reg8 *) Signal_1_A__AMUX) 
/* Bidirectional Enable */                                                        
#define Signal_1_A_BIE                    (* (reg8 *) Signal_1_A__BIE)
/* Bit-mask for Aliased Register Access */
#define Signal_1_A_BIT_MASK               (* (reg8 *) Signal_1_A__BIT_MASK)
/* Bypass Enable */
#define Signal_1_A_BYP                    (* (reg8 *) Signal_1_A__BYP)
/* Port wide control signals */                                                   
#define Signal_1_A_CTL                    (* (reg8 *) Signal_1_A__CTL)
/* Drive Modes */
#define Signal_1_A_DM0                    (* (reg8 *) Signal_1_A__DM0) 
#define Signal_1_A_DM1                    (* (reg8 *) Signal_1_A__DM1)
#define Signal_1_A_DM2                    (* (reg8 *) Signal_1_A__DM2) 
/* Input Buffer Disable Override */
#define Signal_1_A_INP_DIS                (* (reg8 *) Signal_1_A__INP_DIS)
/* LCD Common or Segment Drive */
#define Signal_1_A_LCD_COM_SEG            (* (reg8 *) Signal_1_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Signal_1_A_LCD_EN                 (* (reg8 *) Signal_1_A__LCD_EN)
/* Slew Rate Control */
#define Signal_1_A_SLW                    (* (reg8 *) Signal_1_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Signal_1_A_PRTDSI__CAPS_SEL       (* (reg8 *) Signal_1_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Signal_1_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Signal_1_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Signal_1_A_PRTDSI__OE_SEL0        (* (reg8 *) Signal_1_A__PRTDSI__OE_SEL0) 
#define Signal_1_A_PRTDSI__OE_SEL1        (* (reg8 *) Signal_1_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Signal_1_A_PRTDSI__OUT_SEL0       (* (reg8 *) Signal_1_A__PRTDSI__OUT_SEL0) 
#define Signal_1_A_PRTDSI__OUT_SEL1       (* (reg8 *) Signal_1_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Signal_1_A_PRTDSI__SYNC_OUT       (* (reg8 *) Signal_1_A__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Signal_1_A__SIO_CFG)
    #define Signal_1_A_SIO_HYST_EN        (* (reg8 *) Signal_1_A__SIO_HYST_EN)
    #define Signal_1_A_SIO_REG_HIFREQ     (* (reg8 *) Signal_1_A__SIO_REG_HIFREQ)
    #define Signal_1_A_SIO_CFG            (* (reg8 *) Signal_1_A__SIO_CFG)
    #define Signal_1_A_SIO_DIFF           (* (reg8 *) Signal_1_A__SIO_DIFF)
#endif /* (Signal_1_A__SIO_CFG) */

/* Interrupt Registers */
#if defined(Signal_1_A__INTSTAT)
    #define Signal_1_A_INTSTAT             (* (reg8 *) Signal_1_A__INTSTAT)
    #define Signal_1_A_SNAP                (* (reg8 *) Signal_1_A__SNAP)
    
	#define Signal_1_A_0_INTTYPE_REG 		(* (reg8 *) Signal_1_A__0__INTTYPE)
#endif /* (Signal_1_A__INTSTAT) */

#endif /* End Pins Signal_1_A_H */


/* [] END OF FILE */
