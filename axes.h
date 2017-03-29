/* 
 * File:   axes.h
 * Author: Thabet Marwa
 * Comments: This file allows the user to keep track of the axes and their current states.
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __AXES_H__
#define	__AXES_H__

#include <xc.h> // include processor files - each processor file is guarded.  
#include <string.h> // include spring to allow serial communication processing

// The AzimuthMoveSpeed has the default wait time when a button is pressed
#define AzimuthMoveSpeed 0.8 * PTPER
// The AzimuthUniformSpeed is the desired speed to keep track of a moving object
#define AzimuthUniformSpeed (4 * PTPER) / 100

// The AzimuthMoveSpeed has the default wait time when a button is pressed
#define AltitudeMoveSpeed (5 * PTPER) / 10
// The AltitudeUniformSpeed is the desired speed to keep track of a moving object
#define AltitudeUniformSpeed 0


struct Encoder {
    unsigned int mCurrentLocation;
    unsigned int mDesired;
    bool mPinA;
    bool mPinB;  
};

void Initialize_Azimuth();
void SerialInterface();
char ASCIItoNum(char key);
extern struct Encoder azimuthEnc;
extern struct Encoder altitudeEnc;
extern bool EmergencyOn;

#endif	/* __AXES_H__ */

