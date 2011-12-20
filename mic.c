/*
 * mic.c
 *
 * Created: 2011-12-06 17:37:03
 *  Author: kodie
 */
#include "mic.h"

#include "commons.h"

void micInit(void)
{
	// V_ref = 2,56V
	ADMUX = 0xC0 | MIC_PA_NUMBER;
	// Starts ADC, starts conversion, no interrupts,
	
	ADCSRA = 1<<ADEN | 0<<ADSC | 1<<ADATE | 0<<ADIF | 1<<ADIE |
	         1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0;
	
	// wyzwalaj konwersje przez przepelnienie licznika 0
	SFIOR &= 0x80;
}

uint16_t micRead(void)
{
	while (!CHECK(ADCSRA, ADIF)) ;
	
	uint8_t l = ADCL;
	uint8_t h = ADCH;
	
	SBI(ADCSRA, ADIF);
	
	return ((uint16_t)h << 8) | l;
}
