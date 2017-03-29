/* 
 * File:   axes.c
 * Author: Thabet Marwa
 * Comments: This file allows the user to keep track of the axes and their current states.
 */


#include <xc.h>
#include "mcc_generated_files/mcc.h"
#include "axes.h"
#include "../stdio.h"

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

// This function does the Serial interfacing to get basic 
void SerialInterface() {
    
        const int ContainerSize = 100;
        int i;
        char c, buffer[ContainerSize];
        c = UART1_Read();
        switch (c) {
            case 'P': case 'p': // Ping character
                UART1_Write('P');
                break;
            case 'E': case 'e': // Another ping character
                UART1_Write('E');
                break;
            case 'Z': case 'z': // Configure the desired azimuth location
                // Get the desired azimuth location
                for (i = 0; i < 4; i++) {
                    c = UART1_Read();
                    buffer[i] = c;
                }
                int azimuthDesired;
                memcpy(&azimuthDesired, buffer, 4);
                azimuthEnc.mDesired = azimuthDesired;
                break;
            case 'A': case 'a': // Configure the desired altitude location
                // Get the desired altitude location
                for (i = 0; i < 4; i++) {
                    c = UART1_Read();
                    buffer[i] = c;
                }
                int altitudeDesired;
                memcpy(&altitudeDesired, buffer, 4);
                altitudeEnc.mDesired = altitudeDesired;
                break;    
            case 'G': case 'g': // Get the current location
                printf("Azimuth: %d, Altitude: %d", azimuthEnc.mCurrentLocation,
                        altitudeEnc.mCurrentLocation);
                break;
        }    
}

char ASCIItoNum(char key) {
    //TODO Implement fnc
    return 0;
}
