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
* \file         interruptions.c
*
* \brief        Interruption functions are in this file.
* \date         October 01, 2017
* \author       _Centro "E.Piaggio"_
* \copyright    (C) 2012-2016 qbrobotics. All rights reserved.
* \copyright    (C) 2017 Centro "E.Piaggio". All rights reserved.
*/


//=================================================================     includes
#include <interruptions.h>
#include <command_processing.h>

#include "globals.h"
#include "utils.h"

//===================================================================     global


// PWM vaules needed to obtain 12 Volts given a certain input tension
// Numbers are sperimentally calculated //[index] (milliampere)
CYCODE uint8 pwm_preload_values[29] = {100,    //0 (11500)
                                        83,
                                        78,
                                        76,
                                        74,
                                        72,    //5 (14000)
                                        70,
                                        68,
                                        67,
                                        65,
                                        64,    //10 (16500)
                                        63,
                                        62,
                                        61,
                                        60,
                                        59,    //15 (19000)
                                        58,
                                        57,
                                        56,
                                        56,
                                        55,    //20 (21500)
                                        54,
                                        54,
                                        53,
                                        52,
                                        52,    //25 (24000)
                                        52,
                                        51,
                                        51};   //28 (25500)


//==============================================================================
//                                                            WATCHDOG INTERRUPT
//==============================================================================

CY_ISR(ISR_WATCHDOG_Handler){

    // Set WDT flag
    
    watchdog_flag = TRUE;

}

//==============================================================================
//                                                            RS485 RX INTERRUPT
//==============================================================================

CY_ISR(ISR_RS485_RX_ExInterrupt) {

    // Set RS485 flag
    
    interrupt_flag = TRUE;
     
}

//==============================================================================
//                                                             INTERRUPT MANAGER
//==============================================================================
// Manage interrupt from RS485 
//==============================================================================
// Processing RS-485 data frame:
//
// - WAIT_START:    Waits for beginning characters;
// - WAIT_ID:       Waits for ID;
// - WAIT_LENGTH:   Data length;
// - RECEIVE:       Receive all bytes;
// - UNLOAD:        Wait for another device end of transmission;
//
//==============================================================================

void interrupt_manager(){

    //===========================================     local variables definition

    static uint8 CYDATA state = WAIT_START;                      // state
    
    //------------------------------------------------- local data packet
    static uint8 CYDATA data_packet_index;
    static uint8 CYDATA data_packet_length;
    static uint8 data_packet_buffer[128];                     
    static uint8 CYDATA rx_queue[3];                    // last 2 bytes received
    //-------------------------------------------------

    uint8 CYDATA    rx_data;                            // RS485 UART rx data
    CYBIT           rx_data_type;                       // my id?
    uint8 CYDATA    package_count = 0;                     

    //======================================================     receive routine
    
    // Get data until buffer is not empty 
    
    while(UART_RS485_GetRxBufferSize() && (package_count < 6)){  
        // 6 stima di numero massimo di pacchetti che riesco a leggere senza bloccare l'esecuzione del firmware
        
        // Get next char
        rx_data = UART_RS485_GetChar();
        
        switch (state) {
            //-----     wait for frame start     -------------------------------
            case WAIT_START:
            
                rx_queue[0] = rx_queue[1];
                rx_queue[1] = rx_queue[2];
                rx_queue[2] = rx_data;
                
                // Check for header configuration package
                if ((rx_queue[1] == 58) && (rx_queue[2] == 58)) {
                    rx_queue[0] = 0;
                    rx_queue[1] = 0;
                    rx_queue[2] = 0;
                    state       = WAIT_ID;                    
                }else
                    if ((rx_queue[0] == 63) &&      //ASCII - ?
                        (rx_queue[1] == 13) &&      //ASCII - CR
                        (rx_queue[2] == 10))        //ASCII - LF)
                        infoGet(INFO_ALL);
                break;

            //-----     wait for id     ----------------------------------------
            case  WAIT_ID:

                // packet is for my ID or is broadcast
                if (rx_data == c_mem.id || rx_data == 0)
                    rx_data_type = FALSE;
                else                //packet is for others
                    rx_data_type = TRUE;
                
                data_packet_length = 0;
                state = WAIT_LENGTH;
                break;

            //-----     wait for length     ------------------------------------
            case  WAIT_LENGTH:

 
                data_packet_length = rx_data;
                // check validity of pack length
                if (data_packet_length <= 1) {
                    data_packet_length = 0;
                    state = WAIT_START;
                } else if (data_packet_length > 128) {
                    data_packet_length = 0;
                    state = WAIT_START;
                } else {
                    data_packet_index = 0;
                    
                    if(rx_data_type == FALSE)
                        state = RECEIVE;          // packet for me or broadcast
                    else
                        state = UNLOAD;           // packet for others
                }
                break;

            //-----     receiving     -------------------------------------------
            case RECEIVE:

                data_packet_buffer[data_packet_index] = rx_data;
                data_packet_index++;
                
                // check end of transmission
                if (data_packet_index >= data_packet_length) {
                    // verify if frame ID corresponded to the device ID
                    if (rx_data_type == FALSE) {
                        // copying data from buffer to global packet
                        memcpy(g_rx.buffer, data_packet_buffer, data_packet_length);
                        g_rx.length = data_packet_length;
                        g_rx.ready  = 1;
                        commProcess();
                    }
                    
                    data_packet_index  = 0;
                    data_packet_length = 0;
                    state              = WAIT_START;
                    package_count++;
                
                }
                break;

            //-----     other device is receving     ---------------------------
            case UNLOAD:
                if (!(--data_packet_length)) {
                    data_packet_index  = 0;
                    data_packet_length = 0;
                    RS485_CTS_Write(1);
                    RS485_CTS_Write(0);
                    state              = WAIT_START;
                    package_count++;
                }
                break;
        }
    }
}

//==============================================================================
//                                                            FUNCTION SCHEDULER
//==============================================================================
// Call all the function with the right frequency
//==============================================================================
// Base frequency 1000 Hz
//==============================================================================

void function_scheduler(void) {
 
    static uint16 counter_calibration = DIV_INIT_VALUE;
    
    // Start ADC Conversion, SOC = 1

    timer_value0 = (uint32)MY_TIMER_ReadCounter();
    
    ADC_SOC_Write(0x01); 
    
    // Check Interrupt 

    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
  
    //---------------------------------- Get Encoders

    encoder_reading(0); 
    
    // Check Interrupt     
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }   
    
    encoder_reading(1);
    
    // Check Interrupt 
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
    
    encoder_reading(2);
    
    // Check Interrupt 
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }

    encoder_reading(3);
    
    // Check Interrupt 
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
    
    //---------------------------------- Control Motors
    
    motor_control(0);

    // Check Interrupt 

    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
    
    motor_control(1);
    
    // Check Interrupt 
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }

    //---------------------------------- Read conversion buffer - LOCK function

    analog_read_end();

    //---------------------------------- Calibration 

    // Divider 100, freq = 10 Hz
    if (!(calibration_flag == STOP)) {
        if (counter_calibration == CALIBRATION_DIV) {
            calibration();
            counter_calibration = 0;
        }
        counter_calibration++;
    }
    // Check Interrupt 
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
   
    //---------------------------------- Update States
    
    // Load k-1 state
    memcpy( &g_measOld, &g_meas, sizeof(g_meas) );
    memcpy( &g_refOld, &g_ref, sizeof(g_ref) );

    // Load k+1 state
    memcpy( &g_ref, &g_refNew, sizeof(g_ref) );

    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }

    //CyDelayUs(100);

    timer_value = (uint32)MY_TIMER_ReadCounter();
    MY_TIMER_WriteCounter(5000000);

}


//==============================================================================
//                                                                MOTORS CONTROL
//==============================================================================

void motor_control(const uint8 idx) {
    
    uint8 CYDATA index = idx;
 
    int32 CYDATA curr_ref;

    int32 CYDATA pwm_input = 0;
    
    int32 CYDATA pos_error;
    int32 CYDATA curr_error;
    int32 CYDATA handle_value;

    int32 CYDATA err_emg_1, err_emg_2;
    int32 CYDATA err_joy_1, err_joy_2;
    int32 CYDATA pos_diff, pos_sum;
    
    int32 CYDATA k_p = c_mem.k_p;  
    int32 CYDATA k_i = c_mem.k_i; 
    int32 CYDATA k_d = c_mem.k_d; 

    int32 /*CYDATA*/ k_p_c = c_mem.k_p_c;  
    int32 /*CYDATA*/ k_i_c = c_mem.k_i_c; 
    int32 /*CYDATA*/ k_d_c = c_mem.k_d_c;   

    int32 /*CYDATA*/ k_p_dl = c_mem.k_p_dl;  
    int32 /*CYDATA*/ k_i_dl = c_mem.k_i_dl; 
    int32 /*CYDATA*/ k_d_dl = c_mem.k_d_dl; 

    int32 /*CYDATA*/ k_p_c_dl = c_mem.k_p_c_dl;  
    int32 /*CYDATA*/ k_i_c_dl = c_mem.k_i_c_dl; 
    int32 /*CYDATA*/ k_d_c_dl = c_mem.k_d_c_dl;  

    // Static Variables
    
    static CYBIT dirM0, dirM1;
    
    static int32 pos_error_sum[NUM_OF_MOTORS];
    static int32 curr_error_sum[NUM_OF_MOTORS];
    static int32 prev_curr_err[NUM_OF_MOTORS];
    static int32 prev_pos_err[NUM_OF_MOTORS];

    static uint8 current_emg = 0;   // 0 NONE
                                    // 1 EMG 1
                                    // 2 EMG 2
                                    // wait for both to get down

    err_emg_1 = g_meas.emg[0] - c_mem.emg_threshold[0];
    err_emg_2 = g_meas.emg[1] - c_mem.emg_threshold[1];

    // check index value
    if (index >= NUM_OF_MOTORS)
        return;
    // --------------- USE THIRD ENCODER AS INPUT FOR BOTH MOTORS --------------
    switch(c_mem.input_mode) {

        case INPUT_MODE_ENCODER3:
/*
            // Calculate handle value based on position of handle in the
            // sensor chain and multiplication factor between handle and motor position
            if (c_mem.double_encoder_on_off) 
                handle_value = g_meas.pos[2] * c_mem.motor_handle_ratio;
            else
                handle_value = g_meas.pos[1] * c_mem.motor_handle_ratio;
            

            // Read handle and use it as reference for the motor
            if (((handle_value - g_ref.pos[0]) > c_mem.max_step_pos) && (c_mem.max_step_pos != 0))
                g_ref.pos[0] += c_mem.max_step_pos;
            else {
                if (((handle_value - g_ref.pos[0]) < c_mem.max_step_neg) && (c_mem.max_step_neg != 0))
                    g_ref.pos[0] += c_mem.max_step_neg;
                else
                g_ref.pos[0] = handle_value;
            }
*/
        break;

        case INPUT_MODE_EMG_PROPORTIONAL:
/*            if (err_emg_1 > 0)
                g_ref.pos[0] = (err_emg_1 * g_mem.pos_lim_sup[0]) / (1024 - c_mem.emg_threshold[0]);
            else
                g_ref.pos[0] = 0;
*/
        break;

        case INPUT_MODE_EMG_INTEGRAL:
/*            if (err_emg_1 > 0)
                g_ref.pos[0] += (err_emg_1 * g_mem.emg_speed << 1) / (1024 - c_mem.emg_threshold[0]);

            if (err_emg_2 > 0) 
                g_ref.pos[0] -= (err_emg_2 * g_mem.emg_speed << 1) / (1024 - c_mem.emg_threshold[1]);
*/            
        break;

        case INPUT_MODE_EMG_FCFS:
/*            switch (current_emg) {
                case 0:
                    // Look for the first EMG passing the threshold
                    if (err_emg_1 > 0) {
                        current_emg = 1;
                        break;
                    }
                    if (err_emg_2 > 0) {
                        current_emg = 2;
                        break;
                    }
                    break;

                case 1:
                    // EMG 1 is first
                    if (err_emg_1 < 0) {
                        current_emg = 0;
                        break;
                    }
                    g_ref.pos[0] += (err_emg_1 * g_mem.emg_speed * 2) / (1024 - c_mem.emg_threshold[0]);
                    break;

                case 2:
                    // EMG 2 is first
                    if (err_emg_2 < 0) {
                        current_emg = 0;
                        break;
                    }
                    g_ref.pos[0] -= (err_emg_2 * g_mem.emg_speed * 2) / (1024 - c_mem.emg_threshold[1]);
                    break;

                default:
                    break;
            }
*/
        break;

        case INPUT_MODE_EMG_FCFS_ADV:
/*            switch (current_emg) {
                // Look for the first EMG passing the threshold
                case 0:
                    if (err_emg_1 > 0) {
                        current_emg = 1;
                        break;
                    }
                    if (err_emg_2 > 0) {
                        current_emg = 2;
                        break;
                    }
                    break;

                // EMG 1 is first
                case 1:
                    // If both signals are under threshold go back to status 0
                    if ((err_emg_1 < 0) && (err_emg_2 < 0)) {
                        current_emg = 0;
                        break;
                    }
                    // but if the current signal come back over threshold, continue using it
                    if (err_emg_1 > 0) 
                        g_ref.pos[0] += (err_emg_1 * g_mem.emg_speed << 2) / (1024 - c_mem.emg_threshold[0]);
                    
                    break;

                // EMG 2 is first
                case 2:
                    // If both signals are under threshold go back to status 0
                    if ((err_emg_1 < 0) && (err_emg_2 < 0)) {
                        current_emg = 0;
                        break;
                    }
                    // but if the current signal come back over threshold, continue using it
                    if (err_emg_2 > 0) {
                        g_ref.pos[0] -= (err_emg_2 * c_mem.emg_speed << 2) / (1024 - c_mem.emg_threshold[1]);
                    }
                    break;

                default:
                    break;
            }
*/
        break;
        
        case INPUT_MODE_JOYSTICK:

            err_joy_1 = 0;
            err_joy_2 = 0;
            if(!(g_meas.joystick[0] > 900)) {
                err_joy_1 = g_meas.joystick[0] - g_mem.joystick_threshold;

                //if (err_joy_1 > 0) {   
                if(g_meas.joystick[0] > g_mem.joystick_threshold) {     //both motors wind the wire around the pulley
                    g_refNew.pos[0] += ((int32) err_joy_1 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);
                    g_refNew.pos[1] += ((int32) err_joy_1 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);

                    /*temp = ((g_ref.pos[0] + g_ref.pos[1]) / 2) - c_mem.pos_lim_sup[0];
                    if(temp > 0) {
                        g_ref.pos[0] -= temp;
                        g_ref.pos[1] -= temp;
                    }*/
                }
                else {
                    err_joy_1 = g_meas.joystick[0] + g_mem.joystick_threshold;
                    //if (err_joy_1 < 0) {
                    if(g_meas.joystick[0] < -g_mem.joystick_threshold) {  //both motors unroll the wire around the pulley
                        g_refNew.pos[0] += ((int32) err_joy_1 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);
                        g_refNew.pos[1] += ((int32) err_joy_1 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);

                        /*temp = ((g_ref.pos[0] + g_ref.pos[1]) / 2);
                        if(temp < 0) {
                            g_ref.pos[0] -= temp;
                            g_ref.pos[1] -= temp;
                        }*/
                    }
                }

                err_joy_2 = g_meas.joystick[1] - g_mem.joystick_threshold;
                //if(err_joy_2 > 0) {
                if(g_meas.joystick[1] > g_mem.joystick_threshold) {    //The wire is winded around the first pulley and unwinded from the second one
                    g_refNew.pos[0] += ((int32) err_joy_2 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);
                    g_refNew.pos[1] -= ((int32) err_joy_2 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);
                
                    /*temp = g_ref.pos[1] - c_mem.pos_lim_inf[1]; 
                    if(temp < 0) {
                        g_ref.pos[0] += temp;
                        g_ref.pos[1] -= temp;
                    }*/
                }
                else {
                    err_joy_2 = g_meas.joystick[1] + g_mem.joystick_threshold;
                    //if(err_joy_2 < 0) {
                    if(g_meas.joystick[1] < -g_mem.joystick_threshold) {  //The wire is unwinded from the first pulley and winded on the second one
                        g_refNew.pos[0] += ((int32) err_joy_2 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);
                        g_refNew.pos[1] -= ((int32) err_joy_2 * g_mem.closure_speed) / (1024 - g_mem.joystick_threshold);

                        /*temp = g_ref.pos[0] - c_mem.pos_lim_inf[0]; 
                        if(temp < 0) {
                            g_ref.pos[0] -= temp;
                            g_ref.pos[1] += temp;
                        }*/
                    }
                }
            }

            else {  //The button is pressed and the hand is opened firstly making the position difference
                    //equal to zero, then the position sum is gradually set to zero 
                pos_diff = (g_meas.pos[0] - g_meas.pos[1]) >> c_mem.res[0];
                pos_sum = (g_meas.pos[0] + g_meas.pos[1]) >> c_mem.res[0];

                if(abs(pos_diff) > 500) {
                    if(SIGN(pos_diff) == 1) {
                        g_refNew.pos[1] += g_mem.closure_speed;
                        g_refNew.pos[0] -= g_mem.closure_speed / 2;
                    }
                    else {
                        g_refNew.pos[0] += g_mem.closure_speed;
                        g_refNew.pos[1] -= g_mem.closure_speed / 2;
                    }
                    /*temp = ((g_ref.pos[0] + g_ref.pos[1]) / 2) - c_mem.pos_lim_sup[0];
                    if(temp > 0) {
                        g_ref.pos[0] -= temp;
                        g_ref.pos[1] -= temp;
                    }*/
                }
                else {
                    if(pos_sum > 0) {
                        g_refNew.pos[0] -= g_mem.closure_speed * 2;
                        g_refNew.pos[1] -= g_mem.closure_speed * 2;
                        if(g_refNew.pos[0] < 0)
                            g_refNew.pos[0] = 0;
                        if(g_refNew.pos[1] < 0);
                            g_refNew.pos[1] = 0;
                    }
                }
            }
        
        break;

        default:
            break;
    }

    switch(c_mem.control_mode) {
        case CONTROL_ANGLE:
        
            pos_error = g_ref.pos[index] - g_meas.pos[index << 1];
           
            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }
            
            // error sum for integral
            pos_error_sum[index] += pos_error;

            //anti wind-up
            if (pos_error_sum[index] > ANTI_WINDUP)
                pos_error_sum[index] = ANTI_WINDUP;
            else {
                if (pos_error_sum[index] < -ANTI_WINDUP)
                    pos_error_sum[index] = -ANTI_WINDUP;
            }
              
            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }
            // pwm_input init
            pwm_input = 0;
            // Proportional
            if (k_p != 0) 
                pwm_input = (int32)(k_p * pos_error) >> 16;
                      
            // Integral
            if (k_i != 0) 
                pwm_input += (int32)(k_i * pos_error_sum[index]) >> 16;
            
            // Derivative
            if (k_d != 0)
                pwm_input += (int32)(k_d * (pos_error - prev_pos_err[index])) >> 16;
         
            prev_pos_err[index] = pos_error;
                
            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }
            

            if (index == 0){
                if (pwm_input >= 0)
                    dirM0 = 1;
                    //direction |= 0x01;
                else
                    dirM0 = 0;
                    //direction &= 0xFE;
            }
            else { // index == 1
                if (pwm_input >= 0)
                    dirM1 = 1;
                   // direction |= 0x02;
                else
                    dirM1 = 0;
                    //direction &= 0xFD;
            }
            
        break;

        case CURR_AND_POS_CONTROL:

            pos_error = g_ref.pos[index] - g_meas.pos[index << 1];

            pos_error_sum[index] += pos_error;

            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }

            // error_sum saturation
            if (pos_error_sum[index] > POS_INTEGRAL_SAT_LIMIT)
                pos_error_sum[index] = POS_INTEGRAL_SAT_LIMIT;
            else {
                if (pos_error_sum[index] < -POS_INTEGRAL_SAT_LIMIT)
                    pos_error_sum[index] = -POS_INTEGRAL_SAT_LIMIT;
            }
            // ------ position PID control -----

            curr_ref = 0;

            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }

            // Proportional
            if (k_p_dl != 0)
                curr_ref += (int32)(k_p_dl * pos_error) >> 16;

            // Integral
            if (k_i_dl != 0)
                curr_ref += (int32)(k_i_dl * pos_error_sum[index]) >> 16;
            
            // Derivative
            if (k_d_dl != 0)
                curr_ref += (int32)(k_d_dl * (pos_error - prev_pos_err[index])) >> 16;

            prev_pos_err[index] = pos_error;
                        
            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }

            // saturate max current
            if (curr_ref > c_mem.current_limit)
                curr_ref = c_mem.current_limit;
            else {
                if (curr_ref < -c_mem.current_limit)
                    curr_ref = -c_mem.current_limit;
            }

            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }

            // current error and error sum
            curr_error = curr_ref - g_meas.curr[index];
            curr_error_sum[index] += curr_error;

            if (curr_error_sum[index] > CURR_INTEGRAL_SAT_LIMIT)
                curr_error_sum[index] = CURR_INTEGRAL_SAT_LIMIT;
            else{
                if (curr_error_sum[index] < -CURR_INTEGRAL_SAT_LIMIT)
                    curr_error_sum[index] = -CURR_INTEGRAL_SAT_LIMIT;
            }

            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }

            // ----- current PID control -----

            pwm_input = 0;

            // Proportional
            if (k_p_c_dl != 0)
                pwm_input += (int32)(k_p_c_dl * curr_error) >> 16;
            
            // Integral
            if (k_i_c_dl != 0)
                pwm_input += (int32)(k_i_c_dl * curr_error_sum[index]) >> 16;
            
            // Derivative
            if (k_d_c_dl != 0)
                pwm_input += (int32)(k_d_c_dl * (curr_error - prev_curr_err[index])) >> 16;

            prev_curr_err[index] = curr_error;

            if (interrupt_flag){
                interrupt_flag = FALSE;
                interrupt_manager();
            }

            if (index == 0){
                if (pwm_input >= 0)
                    dirM0 = 1;
                    //direction |= 0x01;
                else
                    dirM0 = 0;
                    //direction &= 0xFE;
            }
            else { // index == 1
                if (pwm_input >= 0)
                    dirM1 = 1;
                   // direction |= 0x02;
                else
                    dirM1 = 0;
                    //direction &= 0xFD;
            }

        break;

        case CONTROL_CURRENT:
            if(g_ref.onoff && tension_valid) {
                // Current ref from pos ref
                curr_ref = g_ref.pos[index] >> g_mem.res[index];

                // saturate max current
                if (curr_ref > c_mem.current_limit)
                    curr_ref = c_mem.current_limit;
                else {
                    if(curr_ref < -c_mem.current_limit)
                       curr_ref = -c_mem.current_limit;
                }
                // Current error
                curr_error = curr_ref - g_meas.curr[index];

                // Error sum for integral
                curr_error_sum[index] += curr_error;

                //anti wind-up
                if (curr_error_sum[index] > CURR_INTEGRAL_SAT_LIMIT)
                    curr_error_sum[index] = CURR_INTEGRAL_SAT_LIMIT;
                else {
                    if (curr_error_sum[index] < -CURR_INTEGRAL_SAT_LIMIT)
                        curr_error_sum[index] = -CURR_INTEGRAL_SAT_LIMIT;
                }

                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

                // pwm_input init
                pwm_input = 0;

                // Proportional
                if (k_p_c != 0)
                    pwm_input += (int32)(k_p * curr_error) >> 16;

                // Integral
                if (k_i_c != 0)
                    pwm_input += (int32)(k_i_c * (curr_error_sum[index] >> 6)) >> 10;
                
                // Derivative
                if (k_d_c != 0)
                    pwm_input += (int32)(k_d_c * (curr_error - prev_curr_err[index])) >> 16;

                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

                // Update measure
                prev_curr_err[index] = curr_error;
                
                if (index == 0) {
                    if (pwm_input >= 0)
                        dirM0 = 1;
                        //direction |= 0x01;
                    else
                        dirM0 = 0;
                        //direction &= 0xFE;
                }
                else { // index == 1
                    if (pwm_input >= 0)
                        dirM1 = 1;
                       // direction |= 0x02;
                    else
                        dirM1 = 0;
                        //direction &= 0xFD;
                }

                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
            }

        break;

        case CONTROL_PWM:
            // Direct PWM value
            pwm_input = g_ref.pos[index] >> g_mem.res[index];

            if (index == 0) {
                if (pwm_input >= 0)
                    dirM0 = 1;
                    //direction |= 0x01;
                else
                    dirM0 = 0;
                    //direction &= 0xFE;
            }
            else { // index == 1
                if (pwm_input >= 0)
                    dirM1 = 1;
                   // direction |= 0x02;
                else
                    dirM1 = 0;
                    //direction &= 0xFD;
            }

        break;

        default:
            break;
    }
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
        
    // abs(pwm_input) must be lower or equal to PWM_MAX_VALUE
    if(pwm_input >  PWM_MAX_VALUE) 
        pwm_input =  PWM_MAX_VALUE;
    if(pwm_input < -PWM_MAX_VALUE) 
        pwm_input = -PWM_MAX_VALUE;
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }   

    // remap pwm_input on pwm_limit based on input tension to have maximum 8 volts
    if (c_mem.control_mode != CONTROL_PWM)
        pwm_input = (((pwm_input << 10) / PWM_MAX_VALUE) * dev_pwm_limit) >> 10;

    // drive direction and pwm duty cycle
        
    if (dirM0){
        if (dirM1)
            MOTOR_DIR_Write(0x03);
        else
            MOTOR_DIR_Write(0x01);
    }
    else{
        if (dirM1)
            MOTOR_DIR_Write(0x02);
        else
            MOTOR_DIR_Write(0x00);
    }

    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
    
    if (index == 0) {
        pwm_sign[0] = SIGN(pwm_input);
        PWM_MOTORS_WriteCompare1(abs(pwm_input));
    }
    else { // index == 1
        pwm_sign[1] = SIGN(pwm_input);
        PWM_MOTORS_WriteCompare2(abs(pwm_input));
    }
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
}

//==============================================================================
//                                                           ANALOG MEASUREMENTS
//==============================================================================

void analog_read_end() {
       
    /* =========================================================================
    /   Ideal formulation to calculate tension and current
    /
    /   tension = ((read_value_mV - offset) * 101) / gain -> [mV]
    /   current = ((read_value_mV - offset) * 375) / (gain * resistor) -> [mA]
    /
    /   Definition:
    /   read_value_mV = counts_read / 0.819 -> conversion from counts to mV
    /   offset = 2000 -> hardware amplifier bias in mV
    /   gain = 8.086 -> amplifier gain
    /   resistor = 18 -> resistor of voltage divider in KOhm 
    /
    /   Real formulation: tradeoff in good performance and accurancy, ADC_buf[] 
    /   and offset unit of measurment is counts, instead dev_tension and
    /   g_meas.curr[] are converted in properly unit.
    /  =========================================================================
    */

    int16 CYDATA i_aux;

    static emg_status CYDATA emg_1_status = RESET; 
    static emg_status CYDATA emg_2_status = RESET; 

    static joystick_status CYDATA UD_status = RESET;
    static joystick_status CYDATA LR_status = RESET;                                          
    
    static uint16 emg_counter_1 = 0;
    static uint16 emg_counter_2 = 0;

    static uint16 UD_counter = 0;
    static uint16 LR_counter = 0;
    
    static int32 UD_mean_value;
    static int32 LR_mean_value;
    
    // Wait for conversion end
    while(!ADC_STATUS_Read()){
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
    }
    
    // Convert tension read
    dev_tension = ((int32)(ADC_buf[0] - 1638) * 1952) >> 7;
    
    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }

    // Until there is no valid input tension repeat this measurement
    
    if (dev_tension > 0){
        
        // Set PWM depends on tension
        pwm_limit_search();
        
        // Check Interrupt 
    
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }

        // Filter and Set currents
        g_meas.curr[0] = filter_i1((int16) pwm_sign[0] * (((int32)(ADC_buf[1] - 1638) * 25771) >> 13));
        
        // Check Interrupt 
    
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
        g_meas.curr[1] = filter_i2((int16) pwm_sign[1] * (((int32)(ADC_buf[2] - 1638) * 25771) >> 13));
        
        // Check Interrupt 
    
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
        // if calibration is not needed go to "normal execution"
        if (!g_mem.emg_calibration_flag){
            emg_1_status = 0; // normal execution
            emg_2_status = 0; // normal execution
        }

        // EMG 1 calibration state machine
        
        // Calibration state machine
        switch(emg_1_status) {
            case NORMAL: // normal execution
                i_aux = filter_ch1(ADC_buf[3]);
                i_aux = (i_aux << 10) / g_mem.emg_max_value[0];
    
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
                //Saturation
                if (i_aux < 0)
                    i_aux = 0;
                else 
                    if (i_aux > 1024) 
                        i_aux = 1024;
                
                g_meas.emg[0] = i_aux;
    
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
                
                break;

            case RESET: // reset variables
                emg_counter_1 = 0;
                g_mem.emg_max_value[0] = 0;
                emg_1_status = DISCARD; // goto next status
                
                break;

            case DISCARD: // discard first EMG_SAMPLE_TO_DISCARD samples
                emg_counter_1++;
                if (emg_counter_1 == EMG_SAMPLE_TO_DISCARD) {
                    emg_counter_1 = 0;          // reset counter
                    LED_REG_Write(0x01);        // turn on LED
                        
                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }
                    
                    emg_1_status = SUM_AND_MEAN;           // sum and mean status
                }
                break;

            case SUM_AND_MEAN: // sum first SAMPLES_FOR_EMG_MEAN samples
                // NOTE max(value)*SAMPLES_FOR_EMG_MEAN must fit in 32bit
                emg_counter_1++;
                g_mem.emg_max_value[0] += filter_ch1(ADC_buf[3]);
                
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
                
                if (emg_counter_1 == SAMPLES_FOR_EMG_MEAN) {
                    g_mem.emg_max_value[0] = g_mem.emg_max_value[0] / SAMPLES_FOR_EMG_MEAN; // calc mean
    
                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }                    
                    
                    LED_REG_Write(0x00);        // led OFF
                    emg_counter_1 = 0;          // reset counter

                    emg_1_status = NORMAL;           // goto normal execution
                }
                break;

            default:
                break;
        }
    
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
        // EMG 2 calibration state machine
        switch(emg_2_status) {
            case NORMAL: // normal execution
                i_aux = filter_ch2(ADC_buf[4]);
                i_aux = (i_aux << 10) / g_mem.emg_max_value[1];
    
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
                
                if (i_aux < 0) 
                    i_aux = 0;
                else 
                    if (i_aux > 1024)
                        i_aux = 1024;
                
                g_meas.emg[1] = i_aux;

                break;

            case RESET: // reset variables
                emg_counter_2 = 0;
                g_mem.emg_max_value[1] = 0;
    
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
                
                emg_2_status = WAIT; // wait for EMG 1 calibration
                break;

            case DISCARD: // discard first EMG_SAMPLE_TO_DISCARD samples
                emg_counter_2++;
                if (emg_counter_2 == EMG_SAMPLE_TO_DISCARD) {
                    emg_counter_2 = 0;          // reset counter
                    LED_REG_Write(0x01);        // turn on LED
    
                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }
                    
                    emg_2_status = SUM_AND_MEAN;           // sum and mean status
                }
                break;

            case SUM_AND_MEAN: // sum first SAMPLES_FOR_EMG_MEAN samples
                // NOTE max(value)*SAMPLES_FOR_EMG_MEAN must fit in 32bit
                emg_counter_2++;
                g_mem.emg_max_value[1] += filter_ch2(ADC_buf[4]);
    
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }
                
                if (emg_counter_2 == SAMPLES_FOR_EMG_MEAN) {
                    g_mem.emg_max_value[1] = g_mem.emg_max_value[1] / SAMPLES_FOR_EMG_MEAN; // calc mean
                    LED_REG_Write(0x00);        // led OFF
                    emg_counter_2 = 0;          // reset counter
                
                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }
                    
                    // if EMG control mode active, activate motors accordingly with startup value
                    if ((c_mem.input_mode == INPUT_MODE_EMG_PROPORTIONAL) ||
                        (c_mem.input_mode == INPUT_MODE_EMG_INTEGRAL) ||
                        (c_mem.input_mode == INPUT_MODE_EMG_FCFS) ||
                        (c_mem.input_mode == INPUT_MODE_EMG_FCFS_ADV)) {
                        if (c_mem.control_mode == CONTROL_ANGLE) {
                            g_ref.pos[0] = g_meas.pos[0];
                            g_ref.pos[1] = g_meas.pos[1];
                        }
                        g_ref.onoff = c_mem.activ;
                        MOTOR_ON_OFF_Write(g_ref.onoff);
                    }
                    emg_2_status = NORMAL;           // goto normal execution
                }
                break;

            case WAIT: // wait for EMG calibration to be done
                if (emg_1_status == NORMAL)
                    emg_2_status = DISCARD;           // goto discard sample
                break;

            default:
                break;
        }
            
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
    
        switch (UD_status) {
            case NORMAL:
                i_aux = ADC_buf[5];
                // Remap the analog reading from -1024 to 1024.  
                i_aux = (int32) (((float) (i_aux - UD_mean_value) / UD_mean_value) * g_mem.joystick_gains[1]); 
                
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

                //Saturation
                if (i_aux < -1024) 
                    i_aux = -1024;
                if (i_aux > 1024)
                    i_aux = 1024;

                g_meas.joystick[1] = (int16) i_aux;

                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

            break;

            case RESET: // reset variables
                UD_counter = 0;
                UD_mean_value = 0;
                UD_status = WAIT; // go to waiting status

            break;

            case DISCARD: // discard first EMG_SAMPLE_TO_DISCARD samples
                UD_counter++;
                if (UD_counter == JOYSTICK_SAMPLE_TO_DISCARD) {
                    UD_counter = 0;                     // reset counter

                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }

                    UD_status = SUM_AND_MEAN;           // sum and mean status
                }

            break;

            case SUM_AND_MEAN: // sum first SAMPLES_FOR_EMG_MEAN samples
                // NOTE max(value)*SAMPLES_FOR_EMG_MEAN must fit in 32bit
                UD_counter++;
                UD_mean_value += ADC_buf[5];

                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

                if (UD_counter == SAMPLES_FOR_JOYSTICK_MEAN) {
                    UD_mean_value = UD_mean_value / SAMPLES_FOR_JOYSTICK_MEAN; // calc mean

                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }

                    UD_counter = 0;          // reset counter
                    UD_status = NORMAL;           // goto normal execution
                }
            break;

            case WAIT: // wait for both EMG calibrations to be done
                if (emg_1_status == NORMAL && emg_2_status == NORMAL)
                    UD_status = DISCARD;           // goto discard sample
            break;
        }

        switch (LR_status) {
            case NORMAL:
                i_aux = ADC_buf[6];

                i_aux = (int32) (((float) (i_aux - LR_mean_value) / LR_mean_value) * g_mem.joystick_gains[0]); 
                
                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

                //Saturation
                if (i_aux < -1024)
                    i_aux = -1024;
                if (i_aux > 1024)
                    i_aux = 1024;

                if (interrupt_flag){
                    interrupt_flag = FALSE;
                    interrupt_manager();
                }

                g_meas.joystick[0] = (int16) i_aux;

            break;

            case RESET: // reset variables
                LR_counter = 0;
                LR_mean_value = 0;
                LR_status = WAIT; // goes waiting for all conversions to be done
            break;

            case DISCARD: // discard first EMG_SAMPLE_TO_DISCARD samples8
                LR_counter++;
                if (LR_counter == JOYSTICK_SAMPLE_TO_DISCARD) {
                    LR_counter = 0;                     // reset counter

                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }

                    LR_status = SUM_AND_MEAN;           // sum and mean status
                }
            break;

            case SUM_AND_MEAN: // sum first SAMPLES_FOR_EMG_MEAN samples
                // NOTE max(value)*SAMPLES_FOR_EMG_MEAN must fit in 32bit
                LR_counter++;
                LR_mean_value += ADC_buf[6];
                if (LR_counter == SAMPLES_FOR_JOYSTICK_MEAN) {
                    LR_mean_value = LR_mean_value / SAMPLES_FOR_JOYSTICK_MEAN; // calc mean
                    
                    if (interrupt_flag){
                        interrupt_flag = FALSE;
                        interrupt_manager();
                    }

                    LR_counter = 0;               // reset counter
                    LR_status = NORMAL;           // goto normal execution
                }
            break;

            case WAIT:
                if(emg_1_status == NORMAL && emg_2_status == NORMAL && UD_status == NORMAL)
                    LR_status = DISCARD;
            break;
        }

        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
    }

    else {
        emg_1_status = RESET; 
        emg_2_status = RESET;
        UD_status = RESET;
        LR_status = RESET;

        tension_valid = FALSE;
            
        if (interrupt_flag){
            interrupt_flag = FALSE;
            interrupt_manager();
        }
        
        if (c_mem.emg_calibration_flag) {
            if ((c_mem.input_mode == INPUT_MODE_EMG_PROPORTIONAL) ||
                (c_mem.input_mode == INPUT_MODE_EMG_INTEGRAL) ||
                (c_mem.input_mode == INPUT_MODE_EMG_FCFS) ||
                (c_mem.input_mode == INPUT_MODE_EMG_FCFS_ADV)) {
                g_ref.onoff = 0x00;
                MOTOR_ON_OFF_Write(g_ref.onoff);
            }
        }

        // Reset current
        g_meas.curr[0] = 0;
        g_meas.curr[1] = 0;

        // Reset emg
        g_meas.emg[0] = 0;
        g_meas.emg[1] = 0;

        //Reset Joystick
        g_meas.joystick[0] = 0;
        g_meas.joystick[1] = 0;
    }

    if (interrupt_flag){
        interrupt_flag = FALSE;
        interrupt_manager();
    }
}

//==============================================================================
//                                                               ENCODER READING
//==============================================================================

void encoder_reading(const uint8 idx)
{
    uint8 CYDATA index = idx;
    
    uint8 CYDATA jj;
    
    uint32 data_encoder;
    int32 value_encoder;
    int32 aux;
    uint8 sensor_index;
    int8 rot[2] = {0,0};

    static int32 last_value_encoder[NUM_OF_SENSORS];
    static uint8 error[NUM_OF_SENSORS];
    static CYBIT only_first_time = TRUE;
    static CYDATA uint8 one_time_execute = 0;
    static CYBIT pos_reconstruct = FALSE;

    // static int32 l_value[NUM_OF_SENSORS];   //last value for vel
    // static int32 ll_value[NUM_OF_SENSORS];  //last last value for vel
    // static int32 lll_value[NUM_OF_SENSORS];  //last last last value for vel

    if (index >= NUM_OF_SENSORS)
        return;
    
    if (reset_last_value_flag) {
        for (jj = NUM_OF_SENSORS; jj--;) {
            last_value_encoder[jj] = 0;
        }
        reset_last_value_flag = 0;
    }

    //======================================================     reading sensors
    if (index == 0)
            data_encoder = (SHIFTREG_ENC_1_ReadData() >> 1) & 0x3FFFF;
    else {
        if (index == 1)
            data_encoder = (SHIFTREG_ENC_2_ReadData() >> 1) & 0x3FFFF;
        else {
            if (index == 2)
                data_encoder = (SHIFTREG_ENC_3_ReadData() >> 1) & 0x3FFFF;
            else // index == 3
                data_encoder = (SHIFTREG_ENC_4_ReadData() >> 1) & 0x3FFFF;
        }
    }    

    if (check_enc_data(&data_encoder)) {

        value_encoder = (int16) (-(32768 - (data_encoder & 0x3FFC0) >> 2) + g_mem.m_off[index]);  

        // Initialize last_value_encoder
        if (only_first_time) {
            last_value_encoder[index] = value_encoder;
            
            if (index == 3)
                only_first_time = 0;
        }

        // Take care of rotations
        aux = value_encoder - last_value_encoder[index];

        // ====================== 1 TURN ======================
        // -32768                    0                    32767 -32768                   0                     32767
        // |-------------------------|-------------------------|-------------------------|-------------------------|
        //              |                         |      |           |      |                         |
        //           -16384                     16383    |           |   -16384                     16383
        //                                               |           |
        //                                           24575           -24576
        //                                               |___________|
        //                                                   49152

        // if we are in the right interval, take care of rotation
        // and update the variable only if the difference between
        // one measure and another is less than 1/4 of turn

        // Considering we are sampling at 1kHz, this means that our shaft needs
        // to go slower than 1/4 turn every ms -> 1 turn every 4ms
        // equal to 250 turn/s -> 15000 RPM

        if (aux > 49152)
            g_meas.rot[index]--;
        else{ 
            if (aux < -49152)
                g_meas.rot[index]++;
            else{
                if (abs(aux) > 16384) { // if two measure are too far
                    error[index]++;
                    if (error[index] < 10)
                        // Discard
                        return;
                }
            }
        }
        
        error[index] = 0;
        
        last_value_encoder[index] = value_encoder;

        value_encoder += (int32)g_meas.rot[index] << 16;

        if (c_mem.m_mult[index] != 1.0)
            value_encoder *= c_mem.m_mult[index];
      
        g_meas.pos[index] = value_encoder;
    }
    
    if (pos_reconstruct == FALSE) {
        if (one_time_execute < 34) {
            one_time_execute++;
        } else {
            // If necessary activate motors
            g_ref.pos[0] = g_meas.pos[0];
            g_ref.pos[1] = g_meas.pos[2];
            MOTOR_ON_OFF_Write(g_ref.onoff);

            // Double encoder translation
            sensor_index = (index >> 1);           // [0-1]->0, [2-3]->1
            if (c_mem.double_encoder_on_off) 
                g_meas.rot[(sensor_index >> 1) << 1] = calc_turns_fcn(g_meas.pos[sensor_index << 1], g_meas.pos[(sensor_index << 1) + 1]);

            g_meas.pos[(sensor_index >> 1) << 1] += (int32) g_meas.rot[(sensor_index >> 1) << 1] << 16;
            
            g_refNew.pos[(sensor_index >> 1) << 1] = g_meas.pos[(sensor_index >> 1) << 1];

            pos_reconstruct = TRUE;
        }
    }

    // // velocity calculation
    // switch(i) {
    //     case 0: {
    //         g_meas.vel[i] = (int16)filter_vel_1((3*value_encoder + l_value[i] - ll_value[i] - 3*lll_value[i]) / 10);
    //         break;
    //     }
    //     case 1: {
    //         g_meas.vel[i] = (int16)filter_vel_2((3*value_encoder + l_value[i] - ll_value[i] - 3*lll_value[i]) / 10);
    //         break;
    //     }
    //     case 2: {
    //         g_meas.vel[i] = (int16)filter_vel_3((3*value_encoder + l_value[i] - ll_value[i] - 3*lll_value[i]) / 10);
    //         break;
    //     }
    // }

    // // update old values
    // lll_value[i] = ll_value[i];
    // ll_value[i] = l_value[i];
    // l_value[i] = value_encoder;
}

//==============================================================================
//                                                              PWM_LIMIT_SEARCH
//==============================================================================

void pwm_limit_search() {
    
    dev_pwm_limit = 100;
    /*uint8 CYDATA index;

    if (dev_tension > 25500)    // Max value 
        dev_pwm_limit = 0;
    else{ 
        if (dev_tension < 11500) // Min value
            dev_pwm_limit = 100;
        else {                  
            index = (uint8)((dev_tension - 11500) >> 9);
            dev_pwm_limit = pwm_preload_values[index];
        }
    }*/
}


/* [] END OF FILE */
