#include <msp430.h> 
#include <keypad.h>
#include <pwmTimerA0.h>
#include <vnh7070API.h>
#include <motionProfile.h>

struct KEYPAD_4X4 myKeypad;

/*
 * Bugs:
 * - Keypad does not detect the first keypress
 * - d.c. of pwm will reach 100% if moved from Stop to CW/CCW
 * -
 */

/*
 * Need to know:
 * - initial motor condition (direction, duty cycle, ...)
 */

#define SMCLK_CLK 1.048E6
#define HZ 500

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	keypadInit(&myKeypad);
	timerA0Init(1000);
	vnh7070Init();
	timerA1Init(); // motionProfile

	/*
	// 1 Hz
	TA0CTL |= TASSEL_2 + MC_1 + ID_3; //up mode, divide by 8
	TA0EX0 |= TAIDEX_1; // divide by 2
	TA0CCR0 = 1.0 / 8 * SMCLK_CLK - 1 + 0.5; // compute and set TACCR0 value
	TA0CCR1 = (1.0 + TA0CCR0) * 5 / 10; // compute and set TA0CCR1
    */

	/*
    // 2 Hz
    TA0CTL |= TASSEL_2 + MC_1 + ID_3; //up mode, divide by 8
    TA0EX0 |= TAIDEX_0; // divide by 1
    TA0CCR0 = 1.0 / 8 * SMCLK_CLK - 1 + 0.5; // compute and set TACCR0 value
    TA0CCR1 = (1.0 + TA0CCR0) * 5 / 10; // compute and set TA0CCR1
	*/

	TA0CTL |= TASSEL_2 + MC_1 + ID_3; //up mode, divide by 8
	TA0EX0 |= TAIDEX_1; // divide by 2
	TA0CCR0 = 1.0 / HZ / 16 * SMCLK_CLK - 1 + 0.5; // compute and set TACCR0 value
	TA0CCR1 = (1.0 + TA0CCR0) * 5 / 10; // compute and set TA0CCR1

	while(1)
	{
	    if (!getKeypress(&myKeypad))
	    {
	        decodeKeyCoord(&myKeypad);
	        onClick(&myKeypad);
	    }
	}

	return 0;
}

void onClick(KEYPAD_4X4 * keypad)
{
    switch(keypad->currentKey)
    {
    case 'F':
        dirReq = 1;
        break;
    case 'R':
        dirReq = -1;
        break;
    case '0':
        dirReq = 0;
        break;
    default:
        //drive();
        dCycleReq = keypad->currentKey;
    }
}
