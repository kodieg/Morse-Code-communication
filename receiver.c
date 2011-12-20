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
#include "lcd.h"
#include "mic.h"
#include "counter.h"

#define EMA_RATE 3

volatile uint16_t avgVal=0;


ISR(TIMER0_OVF_vect) {
}	

ISR(ADC_vect) {

   const uint16_t micVal = micRead();

	if (avgVal < micVal)
	    avgVal = micVal;
	else
		avgVal -= avgVal >> EMA_RATE;
}


int main(void)
{
	lcdInit();
	micInit();
	counterInit();
	
    LD_DDR = 0xFF;
	
    uint8_t counter = 48;
	
	lcdString("Hello world!\0");

	while(1)
	{		
		lcdClear();
        lcdInt(avgVal);
		_delay_ms(50);
    }
}




