/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the MPLAB(c) Code Configurator device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for MPLAB(c) Code Configurator interrupts.
    Generation Information : 
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  dsPIC33EP256MC502
        Version           :  1.02
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


/**
    Section: Includes
*/
#include <xc.h>
#include "pin_manager.h"
#include "../axes.h"

/**
    void PIN_MANAGER_Initialize(void)
*/
void PIN_MANAGER_Initialize(void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0800;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001D;
    TRISB = 0x07FF;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x0002;
    ANSELB = 0x0000;

    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPINR18bits.U1RXR = 0x002A;   //RB10->UART1:U1RX;
    RPINR8bits.IC3R = 0x0020;   //RB0->IC3:IC3;
    RPINR8bits.IC4R = 0x0021;   //RB1->IC4:IC4;
    RPOR4bits.RP43R = 0x0001;   //RB11->UART1:U1TX;
    RPINR7bits.IC1R = 0x0026;   //RB6->IC1:IC1;
    RPINR7bits.IC2R = 0x0027;   //RB7->IC2:IC2;

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS

    /****************************************************************************
     * Interrupt On Change for group CNENA - any
     ***************************************************************************/
    CNENAbits.CNIEA0 = 1; // Pin : RA0 
    CNENAbits.CNIEA2 = 1; // Pin : RA2
	CNENAbits.CNIEA3 = 1; // Pin : RA3
    CNENAbits.CNIEA4 = 1; // Pin : RA4

    /****************************************************************************
     * Interrupt On Change for group CNENB - any
     ***************************************************************************/
	CNENBbits.CNIEB5 = 1; // Pin : RB5

    IEC1bits.CNIE = 1; // Enable CNI interrupt 
}

bool hala; 

/* Interrupt service routine for the CNI interrupt. */
void __attribute__ (( interrupt, no_auto_psv )) _CNInterrupt ( void )
{
    if(IFS1bits.CNIF == 1)
    {
        // Clear the flag
        IFS1bits.CNIF = 0;
    }
    
    if (I_EmerStop_GetValue()) {
        EmergencyOn = true;
        PDC1 = 0;
        PDC2 = 0;
        return;
    }
    
    if (I_MCup_GetValue()) { // If the UP Button is Pressed
        PDC1 = AltitudeMoveSpeed;       // Turn ON PWM1 for 500 ms
        IOCON1bits.SWAP = 0; // Make it forward-biased (High PWM ON)
    } else if (I_MCdown_GetValue()) { // If the DOWN Button is Pressed
        PDC1 = AltitudeMoveSpeed;       // Turn ON PWM1 for 500 ms
        IOCON1bits.SWAP = 1; // Make it reverse-biased (Low PWM ON)
    } else {
        PDC1 = AltitudeUniformSpeed;          // Turn OFF PWM
    }
    
    if (I_MCright_GetValue()) { // If the RIGHT Button is Pressed
        PDC2 = AzimuthMoveSpeed;       // Turn ON PWM2 based on move value in axes.h
        IOCON2bits.SWAP = 0; // Make it forward-biased (High PWM ON)
    } else if (I_MCleft_GetValue()) { // If the LEFT Button is Pressed
        PDC2 = AzimuthMoveSpeed;       // Turn ON PWM2 based on move value in axes.h
        IOCON2bits.SWAP = 1; // Make it reverse-biased (Low PWM ON)
    } else {
        IOCON2bits.SWAP = 0;
        PDC2 = AzimuthUniformSpeed;          // Move Azimuth at Uniform Speed
    }
    
}
