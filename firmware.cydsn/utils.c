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
* \file         utils.h
*
* \brief        Definition of utility functions.
* \date         Dic. 1, 2015
* \author       qbrobotics
* \copyright    (C) 2012-2016 qbrobotics. All rights reserved.
* \copyright    (C) 2017 Centro "E.Piaggio". All rights reserved.
*/

#include <utils.h>
#include <math.h>

//==============================================================================
//                                                               CURRENT FILTERS
//==============================================================================

int32 filter_i1(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - ALPHA) + (new_value << 6) * (ALPHA)) >> 10;

    old_value = aux;

    return (aux >> 6);
}

int32 filter_i2(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - ALPHA) + (new_value << 6) * (ALPHA)) >> 10;

    old_value = aux;

    return (aux >> 6);
}

//==============================================================================
//                                                              VELOCITY FILTERS
//==============================================================================

int32 filter_vel_1(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - GAMMA) + (new_value << 6) * (GAMMA)) / 1024;

    old_value = aux;

    return (aux >> 6);
}

int32 filter_vel_2(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - GAMMA) + (new_value << 6) * (GAMMA)) / 1024;

    old_value = aux;

    return (aux >> 6);
}

int32 filter_vel_3(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - GAMMA) + (new_value << 6) * (GAMMA)) / 1024;

    old_value = aux;

    return (aux >> 6);
}

//==============================================================================
//                                                                   Emg Filters
//==============================================================================

int32 filter_ch1(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - BETA) + new_value * (BETA)) / 1024;

    old_value = aux;

    return aux;
}

int32 filter_ch2(int32 new_value) {

    static int32 old_value, aux;

    aux = (old_value * (1024 - BETA) + new_value * (BETA)) / 1024;

    old_value = aux;

    return aux;
}


//==============================================================================
//                                                                CHECK ENC DATA
//==============================================================================

// Returns 1 if the encoder data is correct, 0 otherwise

CYBIT check_enc_data(const uint32 *value) {

    const uint8* CYIDATA p = (const uint8*)value;
    uint8 CYDATA a = *p;

    a = a ^ *(++p);
    a = a ^ *(++p);
    a = a ^ *(++p);
    a = (a & 0x0F) ^ (a>>4);

    return (0x9669 >> a) & 0x01;
    //0x9669 is a bit vector representing the !(bitwise XOR) of 4bits
}

//==============================================================================
//                                                                     CALIBRATE
//==============================================================================

void calibration(void) {
    static uint8 direction;                 //0 closing, 1 opening
    static uint16 closure_counter;          //Range [0 - 2^16]


    // closing
    if (direction == 0) {
        g_ref.pos[0] += (calib.speed << g_mem.res[0]);
        if ((g_ref.pos[0]) > g_mem.pos_lim_sup[0]) {
            direction = 1;
        }
    } else { //opening
        g_ref.pos[0] -= (calib.speed << g_mem.res[0]);
        if (SIGN(g_ref.pos[0]) != 1) {
            direction = 0;
            closure_counter++;
            if (closure_counter == calib.repetitions) {
                closure_counter = 0;
                calib.enabled = FALSE;
            }
        }
    }
}

//==============================================================================
//                                                                        MODULE
//==============================================================================

uint32 my_mod(int32 val, int32 divisor) {

    if (val >= 0) {
        return (int32)(val % divisor);
    } else {
        return (int32)(divisor - (-val % divisor));
    }
}

//==============================================================================
//                                                      DOUBLE ENCODER CALC TURN
//==============================================================================

// Use this matlab function to calculate I1 and I2
//
// function [inv_a, inv_b] = mod_mul_inv(a, b)
//     a = int32(a);
//     b = int32(b);
//     if b == 0
//         inv_a = 1;
//         inv_b = 0;
//         return
//     else
//         q = idivide(a,b,'floor');
//         r = mod(a,b);
//         [s, t] = mod_mul_inv(b, r);
//     end
//     inv_a = t;
//     inv_b = s - q * t;
// return

// Number of teeth of the two wheels
#define N1 15           ///< Teeth of the first encoder wheel (previous 28)
#define N2 14           ///< Teeth of the second encoder wheel (previous 27)

#define I1 1            ///< First wheel invariant value
#define I2 (-1)         ///< Second wheel invariant value

// Number of ticks per turn
#define M 65536          ///< Number of encoder ticks per turn


int calc_turns_fcn(const int32 pos1, const int32 pos2) {
    
    int32 x = (my_mod( - N2*pos2 - N1*pos1, M*N2) + M/2) / M;

    int32 aux = my_mod(x*I1, N2);
    
    return (my_mod(aux + N2/2, N2) - N2/2);
}


//==============================================================================
//                                                             CHECKSUM FUNCTION
//==============================================================================

// Performs a XOR byte by byte on the entire vector

uint8 LCRChecksum(uint8 *data_array, const uint8 data_length) {
    
    uint8 CYDATA i;
    uint8 CYDATA checksum = 0x00;
    
    for(i = 0; i < data_length; ++i)
       checksum ^= data_array[i];
  
    return checksum;
}

/* [] END OF FILE */