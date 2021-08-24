/*************************************************************************************************
 * adc12.h
 * - C interface file for MSP430 ADC_12
 *
 *  Author: Greg Scutt
 *  Created on: May 1, 2018
 **************************************************************************************************/

#ifndef ADC12_H_
#define ADC12_H_

extern int adc12Result; // public global variable declarations

#define SAMPLE_ADC 1000   // delay between ADC12SC H-->L

void adc12Cfg(const char * vref, char sampMode, char convTrigger, char adcChannel);
void adc12SampSWConv(void);


#endif /* ADC12_H_ */
