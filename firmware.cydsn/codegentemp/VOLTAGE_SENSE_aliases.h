/*******************************************************************************
* File Name: VOLTAGE_SENSE.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_VOLTAGE_SENSE_ALIASES_H) /* Pins VOLTAGE_SENSE_ALIASES_H */
#define CY_PINS_VOLTAGE_SENSE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define VOLTAGE_SENSE_0			(VOLTAGE_SENSE__0__PC)
#define VOLTAGE_SENSE_0_INTR	((uint16)((uint16)0x0001u << VOLTAGE_SENSE__0__SHIFT))

#define VOLTAGE_SENSE_INTR_ALL	 ((uint16)(VOLTAGE_SENSE_0_INTR))

#endif /* End Pins VOLTAGE_SENSE_ALIASES_H */


/* [] END OF FILE */
