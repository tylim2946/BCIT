/*
 * waveformGenerator.c
 *
 *  Created on: Apr 12, 2021
 *  Last modified: Apr 19, 2021
 *      Author: a01160214
 */

#include <msp430.h>
#include "mcp4921Dac.h"
#include <math.h>

#define SMCLK 20.0E6
#define MAX_N_SAMPLE 100
#define PI 3.14159265359

unsigned int k = 0;
unsigned int out = 0;

void triangularWaveAllDac()
{
    unsigned int i;

    while(1)
    {
        for(i = 0; i < 4096; i ++)
        {
            dacSetBin(i);
        }

        for(i = 4096; i > 0; i --)
        {
            dacSetBin(i);
        }
    }
}

void triangularWaveDac(double amp, double freq, int nSamples)
{
    double x[MAX_N_SAMPLE];
    unsigned int i;

    if ((amp >= 0 && amp <= 2.5) /*&& (&& 1/freq <= SMCLK)*/) // amplitude between 0 to 2.5 V
    {
        // pre-calculate x(k)
        for(i = 0; i < nSamples / 2; i ++)
        {
            x[i] = 2.0 * i / nSamples;
        }

        for(i = nSamples / 2; i < nSamples; i ++)
        {
            x[i] = 2.0 * (nSamples - i) / nSamples;
        }

        // set up Ts timer
        triWave(freq, nSamples);

        // draw waveform
        while(1)
        {
            if (out)
            {
                k %= nSamples;
                dacSet(amp * x[k]);
                out = 0;
            }
        }
    }
}

void triWave(double freq, int nSamples)
{
    // configure timer A registers
    TA0CTL |= TASSEL_2 + MC_1 + ID_0;                           // SMCLK, up to CCR0, input divide by 1
    TA0EX0 |= TAIDEX_0;                                         // divide by 1
    TA0CCR0 = SMCLK / (freq * nSamples) - 1 + 0.5;  // sampling frequency

    // configure interrupts
    TA0CTL |= TAIE;     // enable interrupt
    TA0CTL &= ~TAIFG;   // clear interrupt flag
}

void sinusoidWaveDac(double amp, double freq, int nSamples)
{
    double x[MAX_N_SAMPLE];
    unsigned int i;

    if ((amp >= 0 && amp <= 2.5) /*&& (&& 1/freq <= SMCLK)*/) // amplitude between 0 to 2.5 V
    {
        // pre-calculate x(k)
        for(i = 0; i < nSamples; i ++)
        {
            x[i] = 0.5 * sin(2 * PI * i / nSamples);
        }

        // set up Ts timer
        triWave(freq, nSamples);

        // draw waveform
        while(1)
        {
            if (out)
            {
                k %= nSamples;
                dacSet(amp * x[k] + V_FSV / 2);
                out = 0;
            }
        }
    }
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA0_ISR(void)
{
    switch(__even_in_range(TA0IV, 0x0E))
    {
    case 0x0E: // TA0CTL TAIFG (interrupted at every Ts)
        k ++;
        out = 1;
        break;
    }
}
