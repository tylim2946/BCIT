/*************************************************************************************************
 * adc12.h
 * - C interface file for MSP430 ADC_12
 *
 *  Author: Greg Scutt
 *  Created on: May 1, 2018
 *  Modified on: May 1, 2021 by Taeyoon Rim
 **************************************************************************************************/

#ifndef ADC12_H_
#define ADC12_H_

extern int adc12Results[2]; // public global variable declarations

#define SAMPLE_ADC 1000   // delay between ADC12SC H-->L

#define V_R 3.3
#define CONV_D2V (V_R / 4095)

void adc12Cfg(const char * vref, char sampMode, char convTrigger, char adcChannel);
// vref
#define REF_1V5 "1V5"
#define REF_2V0 "2V0"
#define REF_2V5 "2V5"
#define REF_3V3 "3V3"
// sampMode
#define MODE_EXTENDED 0
#define MODE_PULSESAMPLE 1
// convTrigger
#define TRIG_SW 0
#define TRIG_TIMER 1

void adc12SampSWConv(void);
void adc12SetFreq(char * freq);
void adc12SetNSamp(char * rate);
char adc12IsRxd(void);

#endif /* ADC12_H_ */
// 12-bit ADC conversion takes 13 ADC12CLK cycles (28.2.5)