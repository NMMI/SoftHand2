/*******************************************************************************
* File Name: VOLTAGE_SENSE.h  
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

#if !defined(CY_PINS_VOLTAGE_SENSE_H) /* Pins VOLTAGE_SENSE_H */
#define CY_PINS_VOLTAGE_SENSE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "VOLTAGE_SENSE_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    VOLTAGE_SENSE_Write(uint8 value) ;
void    VOLTAGE_SENSE_SetDriveMode(uint8 mode) ;
uint8   VOLTAGE_SENSE_ReadDataReg(void) ;
uint8   VOLTAGE_SENSE_Read(void) ;
void    VOLTAGE_SENSE_SetInterruptMode(uint16 position, uint16 mode) ;
uint8   VOLTAGE_SENSE_ClearInterrupt(void) ;
/** @} general */

/***************************************
*           API Constants        
***************************************/

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the VOLTAGE_SENSE_SetDriveMode() function.
     *  @{
     */
        /* Drive Modes */
        #define VOLTAGE_SENSE_DM_ALG_HIZ         PIN_DM_ALG_HIZ   /**< \brief High Impedance Analog   */
        #define VOLTAGE_SENSE_DM_DIG_HIZ         PIN_DM_DIG_HIZ   /**< \brief High Impedance Digital  */
        #define VOLTAGE_SENSE_DM_RES_UP          PIN_DM_RES_UP    /**< \brief Resistive Pull Up       */
        #define VOLTAGE_SENSE_DM_RES_DWN         PIN_DM_RES_DWN   /**< \brief Resistive Pull Down     */
        #define VOLTAGE_SENSE_DM_OD_LO           PIN_DM_OD_LO     /**< \brief Open Drain, Drives Low  */
        #define VOLTAGE_SENSE_DM_OD_HI           PIN_DM_OD_HI     /**< \brief Open Drain, Drives High */
        #define VOLTAGE_SENSE_DM_STRONG          PIN_DM_STRONG    /**< \brief Strong Drive            */
        #define VOLTAGE_SENSE_DM_RES_UPDWN       PIN_DM_RES_UPDWN /**< \brief Resistive Pull Up/Down  */
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define VOLTAGE_SENSE_MASK               VOLTAGE_SENSE__MASK
#define VOLTAGE_SENSE_SHIFT              VOLTAGE_SENSE__SHIFT
#define VOLTAGE_SENSE_WIDTH              1u

/* Interrupt constants */
#if defined(VOLTAGE_SENSE__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VOLTAGE_SENSE_SetInterruptMode() function.
     *  @{
     */
        #define VOLTAGE_SENSE_INTR_NONE      (uint16)(0x0000u)   /**< \brief Disabled             */
        #define VOLTAGE_SENSE_INTR_RISING    (uint16)(0x0001u)   /**< \brief Rising edge trigger  */
        #define VOLTAGE_SENSE_INTR_FALLING   (uint16)(0x0002u)   /**< \brief Falling edge trigger */
        #define VOLTAGE_SENSE_INTR_BOTH      (uint16)(0x0003u)   /**< \brief Both edge trigger    */
        /** @} intrMode */
/** @} group_constants */

    #define VOLTAGE_SENSE_INTR_MASK      (0x01u)
#endif /* (VOLTAGE_SENSE__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define VOLTAGE_SENSE_PS                     (* (reg8 *) VOLTAGE_SENSE__PS)
/* Data Register */
#define VOLTAGE_SENSE_DR                     (* (reg8 *) VOLTAGE_SENSE__DR)
/* Port Number */
#define VOLTAGE_SENSE_PRT_NUM                (* (reg8 *) VOLTAGE_SENSE__PRT) 
/* Connect to Analog Globals */                                                  
#define VOLTAGE_SENSE_AG                     (* (reg8 *) VOLTAGE_SENSE__AG)                       
/* Analog MUX bux enable */
#define VOLTAGE_SENSE_AMUX                   (* (reg8 *) VOLTAGE_SENSE__AMUX) 
/* Bidirectional Enable */                                                        
#define VOLTAGE_SENSE_BIE                    (* (reg8 *) VOLTAGE_SENSE__BIE)
/* Bit-mask for Aliased Register Access */
#define VOLTAGE_SENSE_BIT_MASK               (* (reg8 *) VOLTAGE_SENSE__BIT_MASK)
/* Bypass Enable */
#define VOLTAGE_SENSE_BYP                    (* (reg8 *) VOLTAGE_SENSE__BYP)
/* Port wide control signals */                                                   
#define VOLTAGE_SENSE_CTL                    (* (reg8 *) VOLTAGE_SENSE__CTL)
/* Drive Modes */
#define VOLTAGE_SENSE_DM0                    (* (reg8 *) VOLTAGE_SENSE__DM0) 
#define VOLTAGE_SENSE_DM1                    (* (reg8 *) VOLTAGE_SENSE__DM1)
#define VOLTAGE_SENSE_DM2                    (* (reg8 *) VOLTAGE_SENSE__DM2) 
/* Input Buffer Disable Override */
#define VOLTAGE_SENSE_INP_DIS                (* (reg8 *) VOLTAGE_SENSE__INP_DIS)
/* LCD Common or Segment Drive */
#define VOLTAGE_SENSE_LCD_COM_SEG            (* (reg8 *) VOLTAGE_SENSE__LCD_COM_SEG)
/* Enable Segment LCD */
#define VOLTAGE_SENSE_LCD_EN                 (* (reg8 *) VOLTAGE_SENSE__LCD_EN)
/* Slew Rate Control */
#define VOLTAGE_SENSE_SLW                    (* (reg8 *) VOLTAGE_SENSE__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define VOLTAGE_SENSE_PRTDSI__CAPS_SEL       (* (reg8 *) VOLTAGE_SENSE__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define VOLTAGE_SENSE_PRTDSI__DBL_SYNC_IN    (* (reg8 *) VOLTAGE_SENSE__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define VOLTAGE_SENSE_PRTDSI__OE_SEL0        (* (reg8 *) VOLTAGE_SENSE__PRTDSI__OE_SEL0) 
#define VOLTAGE_SENSE_PRTDSI__OE_SEL1        (* (reg8 *) VOLTAGE_SENSE__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define VOLTAGE_SENSE_PRTDSI__OUT_SEL0       (* (reg8 *) VOLTAGE_SENSE__PRTDSI__OUT_SEL0) 
#define VOLTAGE_SENSE_PRTDSI__OUT_SEL1       (* (reg8 *) VOLTAGE_SENSE__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define VOLTAGE_SENSE_PRTDSI__SYNC_OUT       (* (reg8 *) VOLTAGE_SENSE__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(VOLTAGE_SENSE__SIO_CFG)
    #define VOLTAGE_SENSE_SIO_HYST_EN        (* (reg8 *) VOLTAGE_SENSE__SIO_HYST_EN)
    #define VOLTAGE_SENSE_SIO_REG_HIFREQ     (* (reg8 *) VOLTAGE_SENSE__SIO_REG_HIFREQ)
    #define VOLTAGE_SENSE_SIO_CFG            (* (reg8 *) VOLTAGE_SENSE__SIO_CFG)
    #define VOLTAGE_SENSE_SIO_DIFF           (* (reg8 *) VOLTAGE_SENSE__SIO_DIFF)
#endif /* (VOLTAGE_SENSE__SIO_CFG) */

/* Interrupt Registers */
#if defined(VOLTAGE_SENSE__INTSTAT)
    #define VOLTAGE_SENSE_INTSTAT             (* (reg8 *) VOLTAGE_SENSE__INTSTAT)
    #define VOLTAGE_SENSE_SNAP                (* (reg8 *) VOLTAGE_SENSE__SNAP)
    
	#define VOLTAGE_SENSE_0_INTTYPE_REG 		(* (reg8 *) VOLTAGE_SENSE__0__INTTYPE)
#endif /* (VOLTAGE_SENSE__INTSTAT) */

#endif /* End Pins VOLTAGE_SENSE_H */


/* [] END OF FILE */
