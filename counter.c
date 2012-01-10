/*
 * counter.c
 *
 * Created: 2011-12-20 17:33:03
 *  Author: kodie
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void counterInit(void) 
{
	const uint8_t TIMER0_RUNNING_CTC = 1<<WGM01 | 1 << CS01;
	TCCR0 = TIMER0_RUNNING_CTC;
	OCR0 = 118;
	TIMSK |= (1 << OCIE0) | (1 << TOIE0);
	sei();
}
