/*******************************************************************************
* File Name: Signal_3_B.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "Signal_3_B.h"


/*******************************************************************************
* Function Name: Signal_3_B_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void Signal_3_B_Write(uint8 value) 
{
    uint8 staticBits = (Signal_3_B_DR & (uint8)(~Signal_3_B_MASK));
    Signal_3_B_DR = staticBits | ((uint8)(value << Signal_3_B_SHIFT) & Signal_3_B_MASK);
}


/*******************************************************************************
* Function Name: Signal_3_B_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Signal_3_B_DM_STRONG     Strong Drive 
*  Signal_3_B_DM_OD_HI      Open Drain, Drives High 
*  Signal_3_B_DM_OD_LO      Open Drain, Drives Low 
*  Signal_3_B_DM_RES_UP     Resistive Pull Up 
*  Signal_3_B_DM_RES_DWN    Resistive Pull Down 
*  Signal_3_B_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Signal_3_B_DM_DIG_HIZ    High Impedance Digital 
*  Signal_3_B_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Signal_3_B_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(Signal_3_B_0, mode);
}


/*******************************************************************************
* Function Name: Signal_3_B_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro Signal_3_B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Signal_3_B_Read(void) 
{
    return (Signal_3_B_PS & Signal_3_B_MASK) >> Signal_3_B_SHIFT;
}


/*******************************************************************************
* Function Name: Signal_3_B_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 Signal_3_B_ReadDataReg(void) 
{
    return (Signal_3_B_DR & Signal_3_B_MASK) >> Signal_3_B_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Signal_3_B_INTSTAT) 

    /*******************************************************************************
    * Function Name: Signal_3_B_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 Signal_3_B_ClearInterrupt(void) 
    {
        return (Signal_3_B_INTSTAT & Signal_3_B_MASK) >> Signal_3_B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
