/*******************************************************************************
* File Name: WATCHDOG_COUNTER.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "WATCHDOG_COUNTER.h"

uint8 WATCHDOG_COUNTER_initVar = 0u;


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void WATCHDOG_COUNTER_Init(void) 
{
        #if (!WATCHDOG_COUNTER_UsingFixedFunction && !WATCHDOG_COUNTER_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!WATCHDOG_COUNTER_UsingFixedFunction && !WATCHDOG_COUNTER_ControlRegRemoved) */
        
        #if(!WATCHDOG_COUNTER_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 WATCHDOG_COUNTER_interruptState;
        #endif /* (!WATCHDOG_COUNTER_UsingFixedFunction) */
        
        #if (WATCHDOG_COUNTER_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            WATCHDOG_COUNTER_CONTROL &= WATCHDOG_COUNTER_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                WATCHDOG_COUNTER_CONTROL2 &= ((uint8)(~WATCHDOG_COUNTER_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                WATCHDOG_COUNTER_CONTROL3 &= ((uint8)(~WATCHDOG_COUNTER_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (WATCHDOG_COUNTER_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                WATCHDOG_COUNTER_CONTROL |= WATCHDOG_COUNTER_ONESHOT;
            #endif /* (WATCHDOG_COUNTER_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            WATCHDOG_COUNTER_CONTROL2 |= WATCHDOG_COUNTER_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            WATCHDOG_COUNTER_RT1 &= ((uint8)(~WATCHDOG_COUNTER_RT1_MASK));
            WATCHDOG_COUNTER_RT1 |= WATCHDOG_COUNTER_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            WATCHDOG_COUNTER_RT1 &= ((uint8)(~WATCHDOG_COUNTER_SYNCDSI_MASK));
            WATCHDOG_COUNTER_RT1 |= WATCHDOG_COUNTER_SYNCDSI_EN;

        #else
            #if(!WATCHDOG_COUNTER_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = WATCHDOG_COUNTER_CONTROL & ((uint8)(~WATCHDOG_COUNTER_CTRL_CMPMODE_MASK));
            WATCHDOG_COUNTER_CONTROL = ctrl | WATCHDOG_COUNTER_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = WATCHDOG_COUNTER_CONTROL & ((uint8)(~WATCHDOG_COUNTER_CTRL_CAPMODE_MASK));
            
            #if( 0 != WATCHDOG_COUNTER_CAPTURE_MODE_CONF)
                WATCHDOG_COUNTER_CONTROL = ctrl | WATCHDOG_COUNTER_DEFAULT_CAPTURE_MODE;
            #else
                WATCHDOG_COUNTER_CONTROL = ctrl;
            #endif /* 0 != WATCHDOG_COUNTER_CAPTURE_MODE */ 
            
            #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved) */
        #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!WATCHDOG_COUNTER_UsingFixedFunction)
            WATCHDOG_COUNTER_ClearFIFO();
        #endif /* (!WATCHDOG_COUNTER_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        WATCHDOG_COUNTER_WritePeriod(WATCHDOG_COUNTER_INIT_PERIOD_VALUE);
        #if (!(WATCHDOG_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
            WATCHDOG_COUNTER_WriteCounter(WATCHDOG_COUNTER_INIT_COUNTER_VALUE);
        #endif /* (!(WATCHDOG_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */
        WATCHDOG_COUNTER_SetInterruptMode(WATCHDOG_COUNTER_INIT_INTERRUPTS_MASK);
        
        #if (!WATCHDOG_COUNTER_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)WATCHDOG_COUNTER_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            WATCHDOG_COUNTER_WriteCompare(WATCHDOG_COUNTER_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            WATCHDOG_COUNTER_interruptState = CyEnterCriticalSection();
            
            WATCHDOG_COUNTER_STATUS_AUX_CTRL |= WATCHDOG_COUNTER_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(WATCHDOG_COUNTER_interruptState);
            
        #endif /* (!WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void WATCHDOG_COUNTER_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (WATCHDOG_COUNTER_UsingFixedFunction)
        WATCHDOG_COUNTER_GLOBAL_ENABLE |= WATCHDOG_COUNTER_BLOCK_EN_MASK;
        WATCHDOG_COUNTER_GLOBAL_STBY_ENABLE |= WATCHDOG_COUNTER_BLOCK_STBY_EN_MASK;
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!WATCHDOG_COUNTER_ControlRegRemoved || WATCHDOG_COUNTER_UsingFixedFunction)
        WATCHDOG_COUNTER_CONTROL |= WATCHDOG_COUNTER_CTRL_ENABLE;                
    #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved || WATCHDOG_COUNTER_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  WATCHDOG_COUNTER_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void WATCHDOG_COUNTER_Start(void) 
{
    if(WATCHDOG_COUNTER_initVar == 0u)
    {
        WATCHDOG_COUNTER_Init();
        
        WATCHDOG_COUNTER_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    WATCHDOG_COUNTER_Enable();        
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void WATCHDOG_COUNTER_Stop(void) 
{
    /* Disable Counter */
    #if(!WATCHDOG_COUNTER_ControlRegRemoved || WATCHDOG_COUNTER_UsingFixedFunction)
        WATCHDOG_COUNTER_CONTROL &= ((uint8)(~WATCHDOG_COUNTER_CTRL_ENABLE));        
    #endif /* (!WATCHDOG_COUNTER_ControlRegRemoved || WATCHDOG_COUNTER_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (WATCHDOG_COUNTER_UsingFixedFunction)
        WATCHDOG_COUNTER_GLOBAL_ENABLE &= ((uint8)(~WATCHDOG_COUNTER_BLOCK_EN_MASK));
        WATCHDOG_COUNTER_GLOBAL_STBY_ENABLE &= ((uint8)(~WATCHDOG_COUNTER_BLOCK_STBY_EN_MASK));
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void WATCHDOG_COUNTER_SetInterruptMode(uint8 interruptsMask) 
{
    WATCHDOG_COUNTER_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   WATCHDOG_COUNTER_ReadStatusRegister(void) 
{
    return WATCHDOG_COUNTER_STATUS;
}


#if(!WATCHDOG_COUNTER_ControlRegRemoved)
/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   WATCHDOG_COUNTER_ReadControlRegister(void) 
{
    return WATCHDOG_COUNTER_CONTROL;
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    WATCHDOG_COUNTER_WriteControlRegister(uint8 control) 
{
    WATCHDOG_COUNTER_CONTROL = control;
}

#endif  /* (!WATCHDOG_COUNTER_ControlRegRemoved) */


#if (!(WATCHDOG_COUNTER_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void WATCHDOG_COUNTER_WriteCounter(uint8 counter) \
                                   
{
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (WATCHDOG_COUNTER_GLOBAL_ENABLE & WATCHDOG_COUNTER_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        WATCHDOG_COUNTER_GLOBAL_ENABLE |= WATCHDOG_COUNTER_BLOCK_EN_MASK;
        CY_SET_REG16(WATCHDOG_COUNTER_COUNTER_LSB_PTR, (uint16)counter);
        WATCHDOG_COUNTER_GLOBAL_ENABLE &= ((uint8)(~WATCHDOG_COUNTER_BLOCK_EN_MASK));
    #else
        CY_SET_REG8(WATCHDOG_COUNTER_COUNTER_LSB_PTR, counter);
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}
#endif /* (!(WATCHDOG_COUNTER_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) The present value of the counter.
*
*******************************************************************************/
uint8 WATCHDOG_COUNTER_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
		(void)CY_GET_REG16(WATCHDOG_COUNTER_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(WATCHDOG_COUNTER_COUNTER_LSB_PTR_8BIT);
	#endif/* (WATCHDOG_COUNTER_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(WATCHDOG_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(WATCHDOG_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) Present Capture value.
*
*******************************************************************************/
uint8 WATCHDOG_COUNTER_ReadCapture(void) 
{
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(WATCHDOG_COUNTER_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG8(WATCHDOG_COUNTER_STATICCOUNT_LSB_PTR));
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint8) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void WATCHDOG_COUNTER_WritePeriod(uint8 period) 
{
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
        CY_SET_REG16(WATCHDOG_COUNTER_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG8(WATCHDOG_COUNTER_PERIOD_LSB_PTR, period);
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint8) Present period value.
*
*******************************************************************************/
uint8 WATCHDOG_COUNTER_ReadPeriod(void) 
{
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
        return ((uint8)CY_GET_REG16(WATCHDOG_COUNTER_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG8(WATCHDOG_COUNTER_PERIOD_LSB_PTR));
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}


#if (!WATCHDOG_COUNTER_UsingFixedFunction)
/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void WATCHDOG_COUNTER_WriteCompare(uint8 compare) \
                                   
{
    #if(WATCHDOG_COUNTER_UsingFixedFunction)
        CY_SET_REG16(WATCHDOG_COUNTER_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG8(WATCHDOG_COUNTER_COMPARE_LSB_PTR, compare);
    #endif /* (WATCHDOG_COUNTER_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint8) Present compare value.
*
*******************************************************************************/
uint8 WATCHDOG_COUNTER_ReadCompare(void) 
{
    return (CY_GET_REG8(WATCHDOG_COUNTER_COMPARE_LSB_PTR));
}


#if (WATCHDOG_COUNTER_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void WATCHDOG_COUNTER_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    WATCHDOG_COUNTER_CONTROL &= ((uint8)(~WATCHDOG_COUNTER_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    WATCHDOG_COUNTER_CONTROL |= compareMode;
}
#endif  /* (WATCHDOG_COUNTER_COMPARE_MODE_SOFTWARE) */


#if (WATCHDOG_COUNTER_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void WATCHDOG_COUNTER_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    WATCHDOG_COUNTER_CONTROL &= ((uint8)(~WATCHDOG_COUNTER_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    WATCHDOG_COUNTER_CONTROL |= ((uint8)((uint8)captureMode << WATCHDOG_COUNTER_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (WATCHDOG_COUNTER_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: WATCHDOG_COUNTER_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void WATCHDOG_COUNTER_ClearFIFO(void) 
{

    while(0u != (WATCHDOG_COUNTER_ReadStatusRegister() & WATCHDOG_COUNTER_STATUS_FIFONEMP))
    {
        (void)WATCHDOG_COUNTER_ReadCapture();
    }

}
#endif  /* (!WATCHDOG_COUNTER_UsingFixedFunction) */


/* [] END OF FILE */

