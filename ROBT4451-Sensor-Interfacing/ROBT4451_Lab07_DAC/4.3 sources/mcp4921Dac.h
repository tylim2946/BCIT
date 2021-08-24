/*
 * mcp4921Dac.h
 *
 *  Created on: Apr 9, 2017
 *      Author: Greg Scutt
 */

#ifndef MCP4921DAC_H_
#define MCP4921DAC_H_

#define CS 	 BIT0							// active LOW CS
#define LDAC BIT2							// active LOW LDAC
#define LDAC_B_ASSERT   P4OUT &= ~LDAC;		// active LOW LDAC_B assertion
#define LDAC_B_DEASSERT P4OUT |=  LDAC;
#define CS_B_ASSERT   P4OUT &= ~CS;			// active LOW CS_B assertion
#define CS_B_DEASSERT P4OUT |=  CS;
#define DAC_CFG_WR BITF						// BIT 15 of DAC word. 0 -> write to DAC register, 1-> ignore command
#define DAC_CFG_BUF BITE					// BIT 14 of DAC word. 0 -> unbuffered Vref, 1-> buffered Vref
#define DAC_CFG_GA BITD						// BIT 13 of DAC word. 0 -> 2XVout, 1-> 1XVout
#define DAC_CFG_SHDN BITC					// BIT 12 of DAC word. 0 -> shutdown device, 1-> Vout is active
#define DAC_FS 4096							// Full scale code 2^12.

extern unsigned char rxFlag;
void dacWriteWord(unsigned int , unsigned int);
void dacSet(double voltage);

#endif /* MCP4921DAC_H_ */
