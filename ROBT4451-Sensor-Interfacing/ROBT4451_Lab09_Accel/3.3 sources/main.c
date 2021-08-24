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
#include <ucsControl.h>
#include <quadEncDec.h>
#include <vnh7070API.h>
#include <pwmTimerA1.h>
#include "stdio.h"
#include "math.h"

#define dcoFreq 20                          //MHz.

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
    quadEncDecInit();
    vnh7070Init();
    timerA1Init(20000);

    // enable global interrupt
    __enable_interrupt();

    char str[30];

    #define Kp 16
    #define Ki 8

    double error;
    double accError = 0;

    double piAmp;

    while(1)
    {
        if (adc12IsRxd())
        {
            // calculate encoder angular displacement
            double angDisp = (posCount % REV_COUNT) * (2*PI / REV_COUNT);
            if (angDisp > PI)
            {
                angDisp -= 2*PI;
            }

            // calculate accelerometer angle and its average
            dout2Ang(adc12Results);
            double incAve = incAveResult * PI / 180;

            // calculate error
            error = incAve - angDisp;
            accError += error * 0.00025;

            // multiply errors by each gain value
            piAmp = Kp * error + Ki * accError;

            // set direction
            if (piAmp > 0)
            {
                vnh7070CW(0);
            }
            else
            {
                vnh7070CCW(0);
            }

            // set voltage
            if (piAmp > Vin)
            {
                piAmp = Vin;
            }
            TA1CCR1 = (1.0 + TA1CCR0) * piAmp / Vin + 0.5; // compute and set TA1CCR1

            // display pidAmp through UART
            sprintf(str, "\r\nerr [rad]: %.4f", error);
            usciA1UartTxString(str);
        }
    }

    __disable_interrupt(); // disable global interrupts
    return 0;
}
