#include <msp430.h> 
#include <usciB1Spi.h>
#include <nok5110LCD.h>

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	usciB1SpiInit(MST, 16, MODE_DEFAULT, !LOOPBACK);
	nokLcdInit();

	nokLcdDrawScrnLine(0, H);
	nokLcdClear();
	nokLcdDrawScrnLine(0, V);
	nokLcdClear();

	return 0;
}
