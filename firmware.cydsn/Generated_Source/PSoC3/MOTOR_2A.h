/*******************************************************************************
* File Name: MOTOR_2A.h  
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

#if !defined(CY_PINS_MOTOR_2A_H) /* Pins MOTOR_2A_H */
#define CY_PINS_MOTOR_2A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "MOTOR_2A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    MOTOR_2A_Write(uint8 value) ;
void    MOTOR_2A_SetDriveMode(uint8 mode) ;
uint8   MOTOR_2A_ReadDataReg(void) ;
uint8   MOTOR_2A_Read(void) ;
void    MOTOR_2A_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   MOTOR_2A_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the MOTOR_2A_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define MOTOR_2A_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define MOTOR_2A_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define MOTOR_2A_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define MOTOR_2A_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define MOTOR_2A_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define MOTOR_2A_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define MOTOR_2A_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define MOTOR_2A_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define MOTOR_2A_MASK               MOTOR_2A__MASK
#define MOTOR_2A_SHIFT              MOTOR_2A__SHIFT
#define MOTOR_2A_WIDTH              1u

/* Interrupt constants */
#if defined(MOTOR_2A__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MOTOR_2A_SetInterruptMode() function.
     *  @{
     */
        #define MOTOR_2A_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define MOTOR_2A_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define MOTOR_2A_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define MOTOR_2A_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define MOTOR_2A_INTR_MASK      (0x01u)
#endif /* (MOTOR_2A__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define MOTOR_2A_PS                     (* (reg8 *) MOTOR_2A__PS)
/* Data Register */
#define MOTOR_2A_DR                     (* (reg8 *) MOTOR_2A__DR)
/* Port Number */
#define MOTOR_2A_PRT_NUM                (* (reg8 *) MOTOR_2A__PRT) 
/* Connect to Analog Globals */                                                  
#define MOTOR_2A_AG                     (* (reg8 *) MOTOR_2A__AG)                       
/* Analog MUX bux enable */
#define MOTOR_2A_AMUX                   (* (reg8 *) MOTOR_2A__AMUX) 
/* Bidirectional Enable */                                                        
#define MOTOR_2A_BIE                    (* (reg8 *) MOTOR_2A__BIE)
/* Bit-mask for Aliased Register Access */
#define MOTOR_2A_BIT_MASK               (* (reg8 *) MOTOR_2A__BIT_MASK)
/* Bypass Enable */
#define MOTOR_2A_BYP                    (* (reg8 *) MOTOR_2A__BYP)
/* Port wide control signals */                                                   
#define MOTOR_2A_CTL                    (* (reg8 *) MOTOR_2A__CTL)
/* Drive Modes */
#define MOTOR_2A_DM0                    (* (reg8 *) MOTOR_2A__DM0) 
#define MOTOR_2A_DM1                    (* (reg8 *) MOTOR_2A__DM1)
#define MOTOR_2A_DM2                    (* (reg8 *) MOTOR_2A__DM2) 
/* Input Buffer Disable Override */
#define MOTOR_2A_INP_DIS                (* (reg8 *) MOTOR_2A__INP_DIS)
/* LCD Common or Segment Drive */
#define MOTOR_2A_LCD_COM_SEG            (* (reg8 *) MOTOR_2A__LCD_COM_SEG)
/* Enable Segment LCD */
#define MOTOR_2A_LCD_EN                 (* (reg8 *) MOTOR_2A__LCD_EN)
/* Slew Rate Control */
#define MOTOR_2A_SLW                    (* (reg8 *) MOTOR_2A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define MOTOR_2A_PRTDSI__CAPS_SEL       (* (reg8 *) MOTOR_2A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define MOTOR_2A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) MOTOR_2A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define MOTOR_2A_PRTDSI__OE_SEL0        (* (reg8 *) MOTOR_2A__PRTDSI__OE_SEL0) 
#define MOTOR_2A_PRTDSI__OE_SEL1        (* (reg8 *) MOTOR_2A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define MOTOR_2A_PRTDSI__OUT_SEL0       (* (reg8 *) MOTOR_2A__PRTDSI__OUT_SEL0) 
#define MOTOR_2A_PRTDSI__OUT_SEL1       (* (reg8 *) MOTOR_2A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define MOTOR_2A_PRTDSI__SYNC_OUT       (* (reg8 *) MOTOR_2A__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(MOTOR_2A__SIO_CFG)
    #define MOTOR_2A_SIO_HYST_EN        (* (reg8 *) MOTOR_2A__SIO_HYST_EN)
    #define MOTOR_2A_SIO_REG_HIFREQ     (* (reg8 *) MOTOR_2A__SIO_REG_HIFREQ)
    #define MOTOR_2A_SIO_CFG            (* (reg8 *) MOTOR_2A__SIO_CFG)
    #define MOTOR_2A_SIO_DIFF           (* (reg8 *) MOTOR_2A__SIO_DIFF)
#endif /* (MOTOR_2A__SIO_CFG) */

/* Interrupt Registers */
#if defined(MOTOR_2A__INTSTAT)
    #define MOTOR_2A_INTSTAT             (* (reg8 *) MOTOR_2A__INTSTAT)
    #define MOTOR_2A_SNAP                (* (reg8 *) MOTOR_2A__SNAP)
    
	#define MOTOR_2A_0_INTTYPE_REG 		(* (reg8 *) MOTOR_2A__0__INTTYPE)
#endif /* (MOTOR_2A__INTSTAT) */

#endif /* End Pins MOTOR_2A_H */


/* [] END OF FILE */
