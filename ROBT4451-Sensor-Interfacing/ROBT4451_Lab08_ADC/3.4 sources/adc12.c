 /*************************************************************************************************
 * adc12.c
 * - C implementation file for MSP430 ADC12
 *
 *  Author: Greg Scutt
 *  Created on: May 1,2018
 *  Modified on: May 1, 2021 by Taeyoon Rim
 **************************************************************************************************/

#include <msp430.h>
#include "adc12.h"
#include <string.h>

#define SMCLK 1.048E6

#define WAVE_FREQ 100 // sinusoid wave frequency in Hz
#define NSAMPLE 100 // number of samples in wave period

const int constCCR0 = (1.0 / WAVE_FREQ / NSAMPLE) * SMCLK - 1 + 0.5;

int adc12Result;
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
* Modified: May 1, 2021 by Taeyoon Rim
************************************************************************************/
void adc12Cfg(const char * vref, char sampMode, char convTrigger, char adcChannel)
{
    // configure vref
    if (strcmp(vref, "3V3"))
    {
		ADC12MCTL0 |= (ADC12INCH_0 + ADC12SREF_1);		// select Analog Channel Input A0.  select VR+ = VREF+
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
		REFCTL0 &= ~(REFMSTR + REFON);				//  disable REF control. Use the ADC12A to provide 3V3
    }

	// setup trigger
    if(convTrigger){
    	ADC12CTL1 |= ADC12SHS_1;					// select timer

    	// configure timer A registers
    	TA0CCTL1 &= ~CAP; // compare mode
    	TA0CCTL1 |= OUTMOD_7; // out mode
    	TA0CTL |= TASSEL_2 + MC_1 + ID_0;       // SMCLK, up to TA0CCR0, input divide by 1
    	TA0EX0 |= TAIDEX_0;                     // divide by 1
    	TA0CCR0 = constCCR0; // sampling period
    	TA0CCR1 = 1; // oneshot
    }
    else{
    	ADC12CTL1 |= ADC12SHS_0;					// select SW bit
    }

    // setup sample mode
    if (sampMode) {
       	ADC12CTL1 |= ADC12SHP;						// pulse sampling sampling. SAMPCON will be controlled by ADC12SHT1x, ADC12SHT10x. Bits Not implemented here.
       	// SET ADC12SHT1,0 IN ADC12CTL0
    } else
       	ADC12CTL1 &= ~ADC12SHP;			            // extended mode. SAMPCON follows the trigger signal width

    // configure SAR core
    ADC12CTL0 |= ADC12ON;         					// ADC12 on
    ADC12CTL1 |= ADC12CONSEQ_2;      				// Repeated Single Channel
    ADC12CTL2 |= ADC12RES_2;						// 12-Bit Resolution

    // configure adc interrupt
    ADC12IE   |= BIT0;                         		// Enable interrupt
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

#pragma vector = ADC12_VECTOR
interrupt void eocADC12ISR(void)	{

	// needs to be modified for channel selection with a proper handler.
	
	// currently just stores MEM0 to adc12Result.
	adc12Result = ADC12MEM0;
	adc12Ready = 1;

}
