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

#define EMA_RATE 8

volatile uint16_t avgVal=0;


ISR(TIMER0_OVF_vect) {
}	

ISR(ADC_vect) {

   const uint16_t micVal = micRead();

	if (avgVal < micVal)
	    avgVal = micVal;
	else {
		uint16_t diffVal = (avgVal >> EMA_RATE);
		
		// if avgVal >> EMA_RATE would be underflow
		if (diffVal == 0) {
			// asserting that never diffVal > avgVal
		    diffVal = avgVal > EMA_RATE ? EMA_RATE : avgVal;
		}			
	
		// avg_n+1 = (avg_n*(E-1))/E + mic/E
		// avg_n+1 = avg_n - avg_n/E + mic/E
		avgVal = avgVal - diffVal + (micVal >> EMA_RATE);
	}		
	
	if (avgVal > EMA_RATE)
	    LD_DDR = 0x00;
	else
	    LD_DDR = 0xFF;
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






