/* 
 * File:   axes.c
 * Author: Thabet Marwa
 * Comments: This file allows the user to keep track of the axes and their current states.
 */


#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "axes.h"

struct Encoder azimuthEnc;
struct Encoder altitudeEnc;

bool EmergencyOn;

void Initialize_Azimuth() {
    azimuthEnc.mCurrentLocation = 0;
    altitudeEnc.mCurrentLocation = 0;
    EmergencyOn = false;
    PDC1 = AltitudeUniformSpeed;          // Turn OFF PWM
    IOCON2bits.SWAP = 0;
    PDC2 = AzimuthUniformSpeed;          // Move Azimuth at Uniform Speed
}

