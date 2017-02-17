/*******************************************************************************
* File Name: AMUX_1.h
* Version 1.80
*
*  Description:
*    This file contains the constants and function prototypes for the Analog
*    Multiplexer User Module AMux.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_AMUX_AMUX_1_H)
#define CY_AMUX_AMUX_1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cyfitter_cfg.h"


/***************************************
*        Function Prototypes
***************************************/

void AMUX_1_Start(void) ;
#define AMUX_1_Init() AMUX_1_Start()
void AMUX_1_FastSelect(uint8 channel) ;
/* The Stop, Select, Connect, Disconnect and DisconnectAll functions are declared elsewhere */
/* void AMUX_1_Stop(void); */
/* void AMUX_1_Select(uint8 channel); */
/* void AMUX_1_Connect(uint8 channel); */
/* void AMUX_1_Disconnect(uint8 channel); */
/* void AMUX_1_DisconnectAll(void) */


/***************************************
*         Parameter Constants
***************************************/

#define AMUX_1_CHANNELS  3u
#define AMUX_1_MUXTYPE   1
#define AMUX_1_ATMOSTONE 0

/***************************************
*             API Constants
***************************************/

#define AMUX_1_NULL_CHANNEL 0xFFu
#define AMUX_1_MUX_SINGLE   1
#define AMUX_1_MUX_DIFF     2


/***************************************
*        Conditional Functions
***************************************/

#if AMUX_1_MUXTYPE == AMUX_1_MUX_SINGLE
# if !AMUX_1_ATMOSTONE
#  define AMUX_1_Connect(channel) AMUX_1_Set(channel)
# endif
# define AMUX_1_Disconnect(channel) AMUX_1_Unset(channel)
#else
# if !AMUX_1_ATMOSTONE
void AMUX_1_Connect(uint8 channel) ;
# endif
void AMUX_1_Disconnect(uint8 channel) ;
#endif

#if AMUX_1_ATMOSTONE
# define AMUX_1_Stop() AMUX_1_DisconnectAll()
# define AMUX_1_Select(channel) AMUX_1_FastSelect(channel)
void AMUX_1_DisconnectAll(void) ;
#else
# define AMUX_1_Stop() AMUX_1_Start()
void AMUX_1_Select(uint8 channel) ;
# define AMUX_1_DisconnectAll() AMUX_1_Start()
#endif

#endif /* CY_AMUX_AMUX_1_H */


/* [] END OF FILE */
