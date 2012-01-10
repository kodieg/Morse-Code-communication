/*
 * counter.c
 *
 * Created: 2011-12-20 17:33:03
 *  Author: kodie
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "local_config.h"

void counterInit(void) 
{
#if APP == SENDER_APP 
	// Setup timer 2 in normal mode
	const uint8_t TIMER2_RUNNING_CTC = 1 << WGM21 | 1 << CS21;
    TCCR2 = TIMER2_RUNNING_CTC;
    TIMSK |= (1 << OCIE0);
	
	// Setup timer 0 in CTC mode (for C2 sound)
	const uint8_t TIMER0_RUNNING_CTC = 1<<WGM01 | 1 << CS01;
	TCCR0 = TIMER0_RUNNING_CTC;
	OCR0 = 118;
	TIMSK |= (1 << OCIE0);
#else 
	const uint8_t TIMER0_RUNNING_CTC = 1 << WGM01 | 1 << CS01;
	TCCR0 = TIMER0_RUNNING_CTC;
	OCR0 = 250;
	TIMSK |= (1 << OCIE0);
#endif
	sei();
}
