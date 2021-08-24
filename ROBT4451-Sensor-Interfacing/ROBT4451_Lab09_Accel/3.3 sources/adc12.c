 /*************************************************************************************************
 * adc12.c
 * - C implementation file for MSP430 ADC12
 *
 *  Author: Chris Baitz, Greg Scutt
 *  Created on: April, 2017
 *  Modified on: May 1, 2021 by Taeyoon Rim
 **************************************************************************************************/

#include <msp430.h>
#include "adc12.h"
#include <string.h>
#include <math.h>

#define SMCLK 20E6

#define ASCII_0 0x30
#define ASCII_9 0x39

int adc12Freq = 4000; // frequency in Hz
int adc12NSample = 1; // number of samples in wave period

int adc12Results[2];
char adc12Ready;

/************************************************************************************
* Function: adc12Cfg
* - configures an ADC channel for repeated single channel conversion selectable trigger and vref.
* - extended or pulse mode sampling.
* - at 12 bit resolution. Assumes VR- = AVSS = 0V. Enables conversion ADC12ENC = 1 and interrupt ADC12IE.
* - ADC12CLK ??
* Arguments:
* vref - REF+ reference. Send string "2V5", "1V5", "2V5", "3V3"
* sampMode - sample/hold and convert control. Sets/Clears ADC12SHP for pulse or extended mode.
* convTrigger - selects timer source ADC12SHS_1 or ADC12SC register bit.
			1 - will select the timer.  0 - will select SW Register bit	
* adcChannel - selects adcChannel 0:15 as adc input. Not implemented.
* return: none
* Author: Greg Scutt
* Date: May 1, 2018
* Modified: May 16, 2021 by Taeyoon Rim
************************************************************************************/
void adc12Cfg(const char * vref, char sampMode, char convTrigger, char adcChannel)
{
    // configure vref
    if (strcmp(vref, "3V3"))
    {
		ADC12MCTL0 |= (ADC12INCH_0 + ADC12SREF_1);		// select Analog Channel Input A0.  select VR+ = VREF+
		ADC12MCTL1 |= (ADC12INCH_1 + ADC12SREF_1 + ADC12EOS);      // select Analog Channel Input A1.  select VR+ = VREF+, select end of sequence

		REFCTL0 |= (REFMSTR + REFON);					//  enable reference control. Use REF module registers.

		if (!strcmp(vref, "1V5")){
			REFCTL0 |= REFVSEL_0;
		}
		else if(!strcmp(vref, "2V0")){
			REFCTL0 |= REFVSEL_1;
		}
		else if(!strcmp(vref, "2V5")){
			REFCTL0 |= REFVSEL_2;
		}
    }
    else if (!strcmp(vref, "3V3"))	                //   VR+ = AVCC+ and not VREF+
    {
		ADC12MCTL0 |= (ADC12INCH_0 + ADC12SREF_0);	// select Analog Channel Input A0.
		ADC12MCTL1 |= (ADC12INCH_1 + ADC12SREF_0 + ADC12EOS);      // select Analog Channel Input A1.  select VR+ = VREF+, select end of sequence
		REFCTL0 &= ~(REFMSTR + REFON);				//  disable REF control. Use the ADC12A to provide 3V3
    }

	// setup trigger
    if(convTrigger){
    	ADC12CTL1 |= ADC12SHS_1;					// select timer

    	// configure timer A registers
    	TA0CCTL1 &= ~CAP; // compare mode
    	TA0CCTL1 |= OUTMOD_7; // out mode
    	TA0CTL |= TASSEL_2 + MC_1 + ID_3;       // SMCLK, up to TA0CCR0, input divide by 8
    	TA0EX0 |= TAIDEX_7;                     // divide by 8
    	TA0CCR0 = (1.0 / adc12Freq / adc12NSample / 8 / 8) * SMCLK - 1 + 0.5; // sampling period
    	TA0CCR1 = 1; // oneshot
    }
    else{
    	ADC12CTL1 |= ADC12SHS_0;					// select SW bit
    }

    // setup sample mode
    if (sampMode) {
       	ADC12CTL1 |= ADC12SHP;						// pulse sampling. SAMPCON will be controlled by ADC12SHT1x, ADC12SHT10x. Bits Not implemented here.
       	// SET ADC12SHT1,0 IN ADC12CTL0
    } else
       	ADC12CTL1 &= ~ADC12SHP;			            // extended mode. SAMPCON follows the trigger signal width

    // configure SAR core
    ADC12CTL0 |= ADC12ON;         					// ADC12 on
    ADC12CTL1 |= ADC12CONSEQ_3;      				// Repeated Sequence of Channels
    ADC12CTL2 |= ADC12RES_2;						// 12-Bit Resolution

    // configure adc interrupt
    ADC12IE   |= BIT1;                         		// Enable interrupt
    ADC12CTL0 |= ADC12ENC;							// Enable Conversion
}

/************************************************************************************
* Function: adc12SampSWConv
* - sets then clears after SAMPLE_ADC the ADC12SC bit to start an ADC12 conversion.
* - make sure the delay (Tsample) created with delay_cycles and SAMPLE_ADC,MCLK is long enough. Errors arise if it is too fast. Can you explain why?
* Arguments:
* - none.
* Author: Greg Scutt
* Date: May 1, 2018
* Modified:
************************************************************************************/
void adc12SampSWConv(void){ // to be used with extended sample mode?
	ADC12CTL0 |= ADC12SC;
	__delay_cycles(SAMPLE_ADC);
	ADC12CTL0 &= (~ADC12SC);  // note: the user manual indicates this bit clears automatically?  Is this true?  Verify.
}

void adc12SetFreq(char * freq)
{
    volatile unsigned int i;
    unsigned char len = 0;
    unsigned int iFreq = 0;

    // find the length of the string (max length is 20)
    for (i = 0; i < 20; i ++)
    {
        if(freq[i] != 0)
        {
            len ++;
        }
    }

    // validate char array
    for (i = 0; i < len; i ++)
    {
        if(freq[i] < ASCII_0 && freq[i] > ASCII_9)
        {
            len = 0; // skip conversion by making len = 0
        }
    }

    // convert String to unsigned int
    if (len > 0)
    {
        for (i = 0; i < len; i ++)
        {
            iFreq += (freq[i] - ASCII_0) * pow(10, len - 1 - i);
        }

        // set frequency
        adc12Freq = iFreq;

        // re-calculate CCR0
        TA0CCR0 = (1.0 / adc12Freq / adc12NSample) * SMCLK - 1 + 0.5; // sampling period
    }
}

void adc12SetNSamp(char * rate)
{
    volatile unsigned int i;
    unsigned char len = 0;
    unsigned int iNSample = 0;

    // find the length of the string (max length is 20)
    for (i = 0; i < 20; i ++)
    {
        if(rate[i] == 0)
        {
            len = i;
        }
    }

    // validate char array
    for (i = 0; i < len; i ++)
    {
        if (rate[i] >= ASCII_0 && rate[i] <= ASCII_9)
        {
            len = 0; // skip conversion by making len = 0
        }
    }

    // convert String to unsigned int
    if (len > 0)
    {
        for (i = 0; i < len; i ++)
        {
            iNSample += (rate[i] - ASCII_0) * pow(10, len - 1 - i);
        }

        // set frequency
        adc12NSample = iNSample;

        // re-calculate CCR0
        TA0CCR0 = (1.0 / adc12Freq / adc12NSample) * SMCLK - 1 + 0.5; // sampling period
    }
}

char adc12IsRxd(void)
{
    char result = 1;

    if (!adc12Ready)
        result = 0;

    adc12Ready = 0; // reset ready bit

    return result;
}

#pragma vector = ADC12_VECTOR
interrupt void eocADC12ISR(void)	{

	// needs to be modified for channel selection with a proper handler.
	
	// currently just stores MEM0 to adc12Result.
	adc12Results[0] = ADC12MEM0;
	adc12Results[1] = ADC12MEM1;
	adc12Ready = 1;
}
