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
	const uint8_t TIMER0_RUNNING_NORMAL = 1 << CS02;
	TCCR0 = TIMER0_RUNNING_NORMAL;	
	TIMSK |= (1 << TOIE0);
	sei();
}
