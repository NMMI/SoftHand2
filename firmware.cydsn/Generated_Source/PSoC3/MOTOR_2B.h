/*******************************************************************************
* File Name: MOTOR_2B.h  
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

#if !defined(CY_PINS_MOTOR_2B_H) /* Pins MOTOR_2B_H */
#define CY_PINS_MOTOR_2B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOTOR_2B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOTOR_2B_Write(uint8 value) ;
void    MOTOR_2B_SetDriveMode(uint8 mode) ;
uint8   MOTOR_2B_ReadDataReg(void) ;
uint8   MOTOR_2B_Read(void) ;
void    MOTOR_2B_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   MOTOR_2B_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOTOR_2B_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define MOTOR_2B_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define MOTOR_2B_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define MOTOR_2B_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define MOTOR_2B_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define MOTOR_2B_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define MOTOR_2B_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define MOTOR_2B_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define MOTOR_2B_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOTOR_2B_MASK               MOTOR_2B__MASK
#define MOTOR_2B_SHIFT              MOTOR_2B__SHIFT
#define MOTOR_2B_WIDTH              1u

/* Interrupt constants */
#if defined(MOTOR_2B__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOTOR_2B_SetInterruptMode() function.
     *  @{
     */
        #define MOTOR_2B_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define MOTOR_2B_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define MOTOR_2B_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define MOTOR_2B_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define MOTOR_2B_INTR_MASK      (0x01u)
#endif /* (MOTOR_2B__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOTOR_2B_PS                     (* (reg8 *) MOTOR_2B__PS)
/* Data Register */
#define MOTOR_2B_DR                     (* (reg8 *) MOTOR_2B__DR)
/* Port Number */
#define MOTOR_2B_PRT_NUM                (* (reg8 *) MOTOR_2B__PRT) 
/* Connect to Analog Globals */                                                  
#define MOTOR_2B_AG                     (* (reg8 *) MOTOR_2B__AG)                       
/* Analog MUX bux enable */
#define MOTOR_2B_AMUX                   (* (reg8 *) MOTOR_2B__AMUX) 
/* Bidirectional Enable */                                                        
#define MOTOR_2B_BIE                    (* (reg8 *) MOTOR_2B__BIE)
/* Bit-mask for Aliased Register Access */
#define MOTOR_2B_BIT_MASK               (* (reg8 *) MOTOR_2B__BIT_MASK)
/* Bypass Enable */
#define MOTOR_2B_BYP                    (* (reg8 *) MOTOR_2B__BYP)
/* Port wide control signals */                                                   
#define MOTOR_2B_CTL                    (* (reg8 *) MOTOR_2B__CTL)
/* Drive Modes */
#define MOTOR_2B_DM0                    (* (reg8 *) MOTOR_2B__DM0) 
#define MOTOR_2B_DM1                    (* (reg8 *) MOTOR_2B__DM1)
#define MOTOR_2B_DM2                    (* (reg8 *) MOTOR_2B__DM2) 
/* Input Buffer Disable Override */
#define MOTOR_2B_INP_DIS                (* (reg8 *) MOTOR_2B__INP_DIS)
/* LCD Common or Segment Drive */
#define MOTOR_2B_LCD_COM_SEG            (* (reg8 *) MOTOR_2B__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOTOR_2B_LCD_EN                 (* (reg8 *) MOTOR_2B__LCD_EN)
/* Slew Rate Control */
#define MOTOR_2B_SLW                    (* (reg8 *) MOTOR_2B__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOTOR_2B_PRTDSI__CAPS_SEL       (* (reg8 *) MOTOR_2B__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOTOR_2B_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOTOR_2B__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOTOR_2B_PRTDSI__OE_SEL0        (* (reg8 *) MOTOR_2B__PRTDSI__OE_SEL0) 
#define MOTOR_2B_PRTDSI__OE_SEL1        (* (reg8 *) MOTOR_2B__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOTOR_2B_PRTDSI__OUT_SEL0       (* (reg8 *) MOTOR_2B__PRTDSI__OUT_SEL0) 
#define MOTOR_2B_PRTDSI__OUT_SEL1       (* (reg8 *) MOTOR_2B__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOTOR_2B_PRTDSI__SYNC_OUT       (* (reg8 *) MOTOR_2B__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOTOR_2B__SIO_CFG)
    #define MOTOR_2B_SIO_HYST_EN        (* (reg8 *) MOTOR_2B__SIO_HYST_EN)
    #define MOTOR_2B_SIO_REG_HIFREQ     (* (reg8 *) MOTOR_2B__SIO_REG_HIFREQ)
    #define MOTOR_2B_SIO_CFG            (* (reg8 *) MOTOR_2B__SIO_CFG)
    #define MOTOR_2B_SIO_DIFF           (* (reg8 *) MOTOR_2B__SIO_DIFF)
#endif /* (MOTOR_2B__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOTOR_2B__INTSTAT)
    #define MOTOR_2B_INTSTAT             (* (reg8 *) MOTOR_2B__INTSTAT)
    #define MOTOR_2B_SNAP                (* (reg8 *) MOTOR_2B__SNAP)
    
	#define MOTOR_2B_0_INTTYPE_REG 		(* (reg8 *) MOTOR_2B__0__INTTYPE)
#endif /* (MOTOR_2B__INTSTAT) */

#endif /* End Pins MOTOR_2B_H */


/* [] END OF FILE */
