/*******************************************************************************
* File Name: AMUX_1.c
* Version 1.80
*
*  Description:
*    This file contains all functions required for the analog multiplexer
*    AMux User Module.
*
*   Note:
*
*******************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "AMUX_1.h"

static uint8 AMUX_1_lastChannel = AMUX_1_NULL_CHANNEL;


/*******************************************************************************
* Function Name: AMUX_1_Start
********************************************************************************
* Summary:
*  Disconnect all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMUX_1_Start(void) 
{
    uint8 chan;

    for(chan = 0u; chan < AMUX_1_CHANNELS ; chan++)
    {
#if (AMUX_1_MUXTYPE == AMUX_1_MUX_SINGLE)
        AMUX_1_Unset(chan);
#else
        AMUX_1_CYAMUXSIDE_A_Unset(chan);
        AMUX_1_CYAMUXSIDE_B_Unset(chan);
#endif
    }

    AMUX_1_lastChannel = AMUX_1_NULL_CHANNEL;
}


#if (!AMUX_1_ATMOSTONE)
/*******************************************************************************
* Function Name: AMUX_1_Select
********************************************************************************
* Summary:
*  This functions first disconnects all channels then connects the given
*  channel.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMUX_1_Select(uint8 channel) 
{
    AMUX_1_DisconnectAll();        /* Disconnect all previous connections */
    AMUX_1_Connect(channel);       /* Make the given selection */
    AMUX_1_lastChannel = channel;  /* Update last channel */
}
#endif


/*******************************************************************************
* Function Name: AMUX_1_FastSelect
********************************************************************************
* Summary:
*  This function first disconnects the last connection made with FastSelect or
*  Select, then connects the given channel. The FastSelect function is similar
*  to the Select function, except it is faster since it only disconnects the
*  last channel selected rather than all channels.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMUX_1_FastSelect(uint8 channel) 
{
    /* Disconnect the last valid channel */
    if( AMUX_1_lastChannel != AMUX_1_NULL_CHANNEL)
    {
        AMUX_1_Disconnect(AMUX_1_lastChannel);
    }

    /* Make the new channel connection */
#if (AMUX_1_MUXTYPE == AMUX_1_MUX_SINGLE)
    AMUX_1_Set(channel);
#else
    AMUX_1_CYAMUXSIDE_A_Set(channel);
    AMUX_1_CYAMUXSIDE_B_Set(channel);
#endif


    AMUX_1_lastChannel = channel;   /* Update last channel */
}


#if (AMUX_1_MUXTYPE == AMUX_1_MUX_DIFF)
#if (!AMUX_1_ATMOSTONE)
/*******************************************************************************
* Function Name: AMUX_1_Connect
********************************************************************************
* Summary:
*  This function connects the given channel without affecting other connections.
*
* Parameters:
*  channel:  The channel to connect to the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMUX_1_Connect(uint8 channel) 
{
    AMUX_1_CYAMUXSIDE_A_Set(channel);
    AMUX_1_CYAMUXSIDE_B_Set(channel);
}
#endif

/*******************************************************************************
* Function Name: AMUX_1_Disconnect
********************************************************************************
* Summary:
*  This function disconnects the given channel from the common or output
*  terminal without affecting other connections.
*
* Parameters:
*  channel:  The channel to disconnect from the common terminal.
*
* Return:
*  void
*
*******************************************************************************/
void AMUX_1_Disconnect(uint8 channel) 
{
    AMUX_1_CYAMUXSIDE_A_Unset(channel);
    AMUX_1_CYAMUXSIDE_B_Unset(channel);
}
#endif

#if (AMUX_1_ATMOSTONE)
/*******************************************************************************
* Function Name: AMUX_1_DisconnectAll
********************************************************************************
* Summary:
*  This function disconnects all channels.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
void AMUX_1_DisconnectAll(void) 
{
    if(AMUX_1_lastChannel != AMUX_1_NULL_CHANNEL) 
    {
        AMUX_1_Disconnect(AMUX_1_lastChannel);
        AMUX_1_lastChannel = AMUX_1_NULL_CHANNEL;
    }
}
#endif

/* [] END OF FILE */
