/*************************************************************************************************
 * main.c
 * - main source file for Activity 3.5 - Signal Sampling and Reconstruction
 *
 *  Author: Taeyoon Rim
 *  Created on: Apr 26, 2021
 *  Modified on: May 1, 2021
 **************************************************************************************************/

#include <msp430.h>
#include <adc12.h>
#include <usciA1Uart.h>
#include <incSensor.h>
#include <usciB1Spi.h>
#include <nok5110LCD.h>
#include <ucsControl.h>
#include "stdio.h"
#include "math.h"

#define dcoFreq 20                          //MHz.
#define PI 3.14159265359

int main(void)
{
    unsigned char oscFail = 1;

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    /*********Set clock frequency*********************************************/
    //unsigned char testPass = 1;
    ucsSelSource(1,1,1,1);
    oscFail = ucsDcoFreqSet (dcoFreq, 2, 1);            //set sclk to dcoFreq
    if (oscFail)
        return 1;
    /***End***Set clock frequency*********************************************/

    // initialize modules
    adc12Cfg(REF_2V5, MODE_PULSESAMPLE, TRIG_TIMER, 0);
    usciA1UartInit();
    usciB1SpiInit(MST, 16, MODE_DEFAULT, !LOOPBACK);
    nokLcdInit();

    // enable global interrupt
    __enable_interrupt();

    char str1[BUFF_SIZE];
    char str2[BUFF_SIZE];

    double ang;
    double angAve;

    double angRad, cosAng, sinAng;
    int x1, x2, y1, y2, i;

    const double mag = 20;

    while(1)
    {
        if (adc12IsRxd())
        {
            usciA1UartTxString("\r\n");
            sprintf(str1, "\r\nAng: %0.4f degrees", dout2Ang(adc12Results));
            sprintf(str2, "\r\nAng Ave: %0.4f degrees", incAveResult);
            usciA1UartTxString(str1);
            usciA1UartTxString(str2);

            // draw line
            nokLcdClear();

            // deg to rad conversion
            angRad = incAveResult * PI / 180;
            cosAng = cos(angRad);
            sinAng = sin(angRad);

            // calculate the points
            for (i = 0; i < mag; i ++)
            {
                x1 = -i * cosAng + 42;
                x2 = i * cosAng + 42;
                y1 = i * sinAng + 24;
                y2 = -i * sinAng + 24;

                nokLcdSetPixel(x1, y1);
                nokLcdSetPixel(x2, y2);
            }
        }
    }

    __disable_interrupt(); // disable global interrupts
    return 0;
}
