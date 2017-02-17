/*******************************************************************************
* File Name: Signal_4_A.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Signal_4_A_H) /* Pins Signal_4_A_H */
#define CY_PINS_Signal_4_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Signal_4_A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Signal_4_A_Write(uint8 value) ;
void    Signal_4_A_SetDriveMode(uint8 mode) ;
uint8   Signal_4_A_ReadDataReg(void) ;
uint8   Signal_4_A_Read(void) ;
uint8   Signal_4_A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Signal_4_A_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define Signal_4_A_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define Signal_4_A_DM_RES_UP          PIN_DM_RES_UP
#define Signal_4_A_DM_RES_DWN         PIN_DM_RES_DWN
#define Signal_4_A_DM_OD_LO           PIN_DM_OD_LO
#define Signal_4_A_DM_OD_HI           PIN_DM_OD_HI
#define Signal_4_A_DM_STRONG          PIN_DM_STRONG
#define Signal_4_A_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define Signal_4_A_MASK               Signal_4_A__MASK
#define Signal_4_A_SHIFT              Signal_4_A__SHIFT
#define Signal_4_A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Signal_4_A_PS                     (* (reg8 *) Signal_4_A__PS)
/* Data Register */
#define Signal_4_A_DR                     (* (reg8 *) Signal_4_A__DR)
/* Port Number */
#define Signal_4_A_PRT_NUM                (* (reg8 *) Signal_4_A__PRT) 
/* Connect to Analog Globals */                                                  
#define Signal_4_A_AG                     (* (reg8 *) Signal_4_A__AG)                       
/* Analog MUX bux enable */
#define Signal_4_A_AMUX                   (* (reg8 *) Signal_4_A__AMUX) 
/* Bidirectional Enable */                                                        
#define Signal_4_A_BIE                    (* (reg8 *) Signal_4_A__BIE)
/* Bit-mask for Aliased Register Access */
#define Signal_4_A_BIT_MASK               (* (reg8 *) Signal_4_A__BIT_MASK)
/* Bypass Enable */
#define Signal_4_A_BYP                    (* (reg8 *) Signal_4_A__BYP)
/* Port wide control signals */                                                   
#define Signal_4_A_CTL                    (* (reg8 *) Signal_4_A__CTL)
/* Drive Modes */
#define Signal_4_A_DM0                    (* (reg8 *) Signal_4_A__DM0) 
#define Signal_4_A_DM1                    (* (reg8 *) Signal_4_A__DM1)
#define Signal_4_A_DM2                    (* (reg8 *) Signal_4_A__DM2) 
/* Input Buffer Disable Override */
#define Signal_4_A_INP_DIS                (* (reg8 *) Signal_4_A__INP_DIS)
/* LCD Common or Segment Drive */
#define Signal_4_A_LCD_COM_SEG            (* (reg8 *) Signal_4_A__LCD_COM_SEG)
/* Enable Segment LCD */
#define Signal_4_A_LCD_EN                 (* (reg8 *) Signal_4_A__LCD_EN)
/* Slew Rate Control */
#define Signal_4_A_SLW                    (* (reg8 *) Signal_4_A__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Signal_4_A_PRTDSI__CAPS_SEL       (* (reg8 *) Signal_4_A__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Signal_4_A_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Signal_4_A__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Signal_4_A_PRTDSI__OE_SEL0        (* (reg8 *) Signal_4_A__PRTDSI__OE_SEL0) 
#define Signal_4_A_PRTDSI__OE_SEL1        (* (reg8 *) Signal_4_A__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Signal_4_A_PRTDSI__OUT_SEL0       (* (reg8 *) Signal_4_A__PRTDSI__OUT_SEL0) 
#define Signal_4_A_PRTDSI__OUT_SEL1       (* (reg8 *) Signal_4_A__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Signal_4_A_PRTDSI__SYNC_OUT       (* (reg8 *) Signal_4_A__PRTDSI__SYNC_OUT) 


#if defined(Signal_4_A__INTSTAT)  /* Interrupt Registers */

    #define Signal_4_A_INTSTAT                (* (reg8 *) Signal_4_A__INTSTAT)
    #define Signal_4_A_SNAP                   (* (reg8 *) Signal_4_A__SNAP)

#endif /* Interrupt Registers */

#endif /* End Pins Signal_4_A_H */


/* [] END OF FILE */
