/*
 * klawiatura.c
 *
 * Created: 2011-11-15 16:44:01
 *  Author: pn264889
 */

#include "config.h"

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

#include "commons.h"
//#include "keyboard.h"
#include "lcd.h"
#include "mic.h"
/*
ISR(INT0_vect) {

    //volatile uint16_t t;
    //for (t = 0; t < 2000; ++t);

    _delay_loop_2(2000);

    int8_t key = readKeypad();

    LD_PORT = ~key;
}
int main_keypad(void)
{
    LD_DDR = 0xFF;
    initKeypad();

    // Przerwanie INT0 bedzie zglaszane przy zboczu opadajacym
    uint8_t tmp = MCUCR;
    CBI(tmp, ISC00);
    SBI(tmp, ISC01);
    MCUCR = tmp;

    // Wlaczenie przerwania INT0
    SBI(GICR, INT0);
    // Wyzerowanie znacznikow przerwan
    SBI(GIFR, INTF0);
    // Waaczenie przerwan (ustawienie globalnego znacznikaprzerwan)
    sei();

    while(1) {
        //_delay_ms(500);
    }

}
*/
int main(void)
{
    LD_DDR = 0xFF;

	lcdInit();
	micInit();
	
    uint8_t counter = 48;

	lcdString("Hello world!\0");
	_delay_ms(20);

    uint16_t maxVal=0;
	uint16_t minVal=0xFFFF;
	
	for(uint16_t i = 0; 1; ++i)
	{
		const uint16_t micVal = micRead();
		if (micVal > maxVal)
			maxVal = micVal;
		if (micVal < minVal)
			minVal = micVal;
					
		if (i % 2048 == 0) 
		{
			lcdClear();
			//lcdInt(micRead());
			//_delay_ms(10);
			lcdInt(minVal);
			lcdString(" | ");
			lcdInt(maxVal);
			maxVal = 0;
			minVal = 0xFFFF;
		}		
    }

}

