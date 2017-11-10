// ----------------------------------------------------------------------------
// BSD 3-Clause License

// Copyright (c) 2016, qbrobotics
// Copyright (c) 2017, Centro "E.Piaggio"
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// POSSIBILITY OF SUCH DAMAGE.
// ----------------------------------------------------------------------------

/**
* \file         globals.h
*
* \brief        Global definitions and macros are set in this file.
* \date         October 01, 2017
* \author       _Centro "E.Piaggio"_
* \copyright    (C) 2012-2016 qbrobotics. All rights reserved.
* \copyright    (C) 2017 Centro "E.Piaggio". All rights reserved.
*/

#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

//=================================================================     includes
#include <device.h>
#include "stdlib.h"
#include "math.h"
#include "commands.h"

//==============================================================================
//                                                                        DEVICE
//==============================================================================

#define VERSION         "TWO MOTORS HAND v6.1.0"

#define NUM_OF_MOTORS           2
#define NUM_OF_SENSORS          4
#define NUM_OF_EMGS             2
#define NUM_OF_ANALOG_INPUTS    7
#define NUM_OF_PARAMS           24

//==============================================================================
//                                                                       CONTROL
//==============================================================================

#define PWM_MAX_VALUE   100         // PWM is from 0 to 100, this value is used
                                    // to limit this value
#define PWM_DEAD        0           // deadband value, is directly added to the
                                    // value of PWM always limited to 100

//==============================================================================
//                                                               SYNCHRONIZATION
//==============================================================================

// Main frequency 1000 Hz

#define CALIBRATION_DIV         100     // 10 Hz

#define DIV_INIT_VALUE          1

//==============================================================================
//                                                                           DMA
//==============================================================================
    
#define DMA_BYTES_PER_BURST 2
#define DMA_REQUEST_PER_BURST 1
#define DMA_SRC_BASE (CYDEV_PERIPH_BASE)
#define DMA_DST_BASE (CYDEV_SRAM_BASE)
    
//==============================================================================
//                                                                     INTERRUPT
//==============================================================================
#define    WAIT_START   0
#define    WAIT_ID      1
#define    WAIT_LENGTH  2
#define    RECEIVE      3
#define    UNLOAD       4
    
//==============================================================================
//                                                                         OTHER
//==============================================================================

#define FALSE           0
#define TRUE            1

#define DEFAULT_EEPROM_DISPLACEMENT 8   // in pages
    
#define MAX_WATCHDOG_TIMER 250          // num * 2 [cs]

#define PWM_MAX_VALUE           100     /*!< Maximum value of the PWM signal.*/

#define ANTI_WINDUP             1000    /*!< Anti windup saturation.*/ 
#define DEFAULT_CURRENT_LIMIT   1000    /*!< Default Current limit, 0 stands for unlimited.*/

#define CURRENT_HYSTERESIS      10      /*!< milliAmperes of hysteresis for current control.*/

#define EMG_SAMPLE_TO_DISCARD   500     /*!< Number of sample to discard before calibration.*/
#define SAMPLES_FOR_MEAN        100     /*!< Number of samples used to mean current values.*/

#define SAMPLES_FOR_EMG_MEAN    1000    /*!< Number of samples used to mean emg values.*/

#define SAMPLES_FOR_JOYSTICK_MEAN   200
#define JOYSTICK_SAMPLE_TO_DISCARD  100
    
#define CALIB_DECIMATION        1
#define NUM_OF_CLOSURES         5

#define POS_INTEGRAL_SAT_LIMIT  50000000    /*!< Anti windup on position control.*/
#define CURR_INTEGRAL_SAT_LIMIT 100000      /*!< Anti windup on current control.*/

#define MIN_CURR_SAT_LIMIT      30

#define LOOKUP_DIM              6           /*!< Dimension of the current lookup table.*/


//==============================================================================
//                                                        structures definitions
//==============================================================================

//=========================================================     motor references

struct st_ref {

    int32 pos[NUM_OF_MOTORS];       // motor reference position
    uint8 onoff;                    // enable flags

};

//=============================================================     measurements

struct st_meas {

    int16 vel[NUM_OF_SENSORS];      // sensor velocity <Check. Probably data corrupted>
    int32 curr[NUM_OF_MOTORS];      // motor currents
    int32 pos[NUM_OF_SENSORS];      // sensor position
    int16 rot[NUM_OF_SENSORS];      // sensor rotations
    int32 emg[NUM_OF_EMGS];         // emg values
    int16 joystick[NUM_OF_MOTORS];  // Joystick measurements

};

//==============================================================     data packet

struct st_data {

    uint8   buffer[128];                    // CMD/DATA/CHECKSUM
    int16   length;                         // length
    int16   ind;                            // index
    uint8   ready;                          // Flag

};

//==============================================     hand calibration parameters
/** \brief Hand calibration structure
 *
**/ 
struct st_calib {
    uint8   enabled;                /*!< Calibration enabling flag.*/
    uint8   direction;              /*!< Direction of motor winding.*/
    int16   speed;                  /*!< Speed of hand opening/closing.*/
    int16   repetitions;            /*!< Number of cycles of hand closing/opening.*/
};

//============================================     settings stored on the memory

struct st_mem {

    uint8   flag;                       // Device has been configured               1
    uint8   id;                         // device ID                                1

    int32   k_p;                        // Proportional constant                    4
    int32   k_i;                        // Derivative constant                      4
    int32   k_d;                        // Integrative constant                     4

    int32   k_p_c;                      // Proportional constant current            4
    int32   k_i_c;                      // Derivative constant current              4
    int32   k_d_c;                      // Integrative constant current             4       26

    int32   k_p_dl;                     // Proportional double loop constant        4
    int32   k_i_dl;                     // Derivative double loop constant          4
    int32   k_d_dl;                     // Integrative double loop constant         4

    int32   k_p_c_dl;                   // Prop. double loop current constant       4
    int32   k_i_c_dl;                   // Derivative double loop current constant  4
    int32   k_d_c_dl;                   // Integrative double loop current constant 4       24

    int16   current_limit;              // Limit for absorbed current               2

    uint8   activ;                      // Activation upon startup                  1
    uint8   input_mode;                 // Input mode                               1       
    uint8   control_mode;               // Control mode                             1

    uint8   res[NUM_OF_SENSORS];        // Angle resolution                         1 (4)
    int32   m_off[NUM_OF_SENSORS];      // Measurement offset                       4 (16)
    float   m_mult[NUM_OF_SENSORS];     // Measurement multiplier                   4 (16)  41
    uint8   pos_lim_flag;               // Position limit active/inactive           1
    int32   pos_lim_inf[NUM_OF_MOTORS]; // Inferior position limit for motors       4 (8)
    int32   pos_lim_sup[NUM_OF_MOTORS]; // Superior position limit for motors       4 (8)

    uint8   baud_rate;                  // Baud Rate Setted                         1
    uint8   watchdog_period;            // Watchdog period setted, 255 = disable    1
    int32   max_step_neg;               // Maximum velocity for negative inputs     4
    int32   max_step_pos;               // Maximum velocity for positive inputs     4 

    uint16  emg_threshold[NUM_OF_EMGS]; // Minimum value for activation             4       31

    uint8   emg_calibration_flag;       // Enable emg calibration on startup        1
    uint32  emg_max_value[NUM_OF_EMGS]; // Maximum value for EMG                    8

    uint8   emg_speed;                  // Maximum closure speed when using emg     1

    uint8   double_encoder_on_off;      // Double encoder ON/OFF                    1

    int8    motor_handle_ratio;         // Discrete multiplier for handle           1
    
    float   curr_lookup[6];             // Current lookup table                     6

    uint8   activate_pwm_rescaling;     // PWM rescaling for 12V motors             1
    uint16  closure_speed;              // Hand closure speed                       2 
    int16   joystick_threshold;         // Joystick threshold                       2
    uint16  joystick_gains[2];          // Joystick measurements gains              4       27      
                                                                                    //TOT   149 bytes
};



//=================================================     calibration status

enum calibration_status {

    STOP        = 0,
    START       = 1,
    CONTINUE_1  = 2,
    CONTINUE_2  = 3,
    PAUSE_1     = 4,
    PAUSE_2     = 5

};

//=================================================     emg status
typedef enum {

    NORMAL        = 0,              /*!< Normal execution */
    RESET         = 1,              /*!< Reset analog measurements */
    DISCARD       = 2,              /*!< Discard first samples to obtain a correct value */
    SUM_AND_MEAN  = 3,              /*!< Sum and mean a definite value of samples*/
    WAIT          = 4               /*!< The second emg waits until the first emg has a valid value */

} emg_status, joystick_status;      /*!< EMG and joystick status enumeration */

//====================================      external global variables declaration


extern struct st_ref    g_ref, g_refNew, g_refOld;  // motor variables
extern struct st_meas   g_meas, g_measOld;          // measurements
extern struct st_data   g_rx;                       // income data
extern struct st_mem    g_mem, c_mem;               // memory
extern struct st_calib  calib;


extern uint32 timer_value;
extern uint32 timer_value0;

// Device Data

extern int32 dev_tension;                         // Power supply tension
extern uint8 dev_pwm_limit;

extern uint8 calibration_flag;

// Bit Flag

extern CYBIT reset_last_value_flag;
extern CYBIT tension_valid;                         // tension validation bit
extern CYBIT interrupt_flag;                        // interrupt flag enabler
extern CYBIT watchdog_flag;                         // watchdog flag enabler

// DMA Buffer

extern int16 ADC_buf[3];

// PWM Sign Value
extern int8 pwm_sign[NUM_OF_MOTORS];

// -----------------------------------------------------------------------------

#endif

//[] END OF FILE