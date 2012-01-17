/*
 * klawiatura.c
 *
 * Created: 2011-11-15 16:44:01
 *  Author: kg262932
 */

#include "config.h"

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "commons.h"
#include "lcd.h"
#include "mic.h"
#include "counter.h"
#include "morse.h"

volatile uint8_t turn_sound_off = 0;
volatile uint8_t sound_is_on = 0;
volatile uint16_t sound_counter = 0;
volatile uint16_t silence_counter = 0;

volatile char buffer[256];
volatile uint8_t start = 0;
volatile uint8_t end = 0;
volatile uint8_t letter_pos = 0;

void soundOn() {
	if (sound_is_on == 0) {
		sound_is_on = 1;	
		TCCR0 = (1 << WGM01 | 1 << COM00 | 1 << CS01);	
		SBI(LD_DDR, 0);
	}		
}

void soundOff() {
	if (sound_is_on) {
		sound_is_on = 0;
		turn_sound_off = 1;
		CBI(LD_DDR, 0);
	}	
}


ISR(TIMER0_COMP_vect) {
	if (turn_sound_off && !(PINB & (1 << PB3))) {		
		TCCR0 = (1 << WGM01 | 1 << CS01);
		turn_sound_off = 0;
	}		
}

ISR(TIMER0_OVF_vect) {}
	
ISR(TIMER2_OVF_vect) {}

ISR(TIMER2_COMP_vect) {
	if (sound_counter == 0 && silence_counter == 0) {
		if (start != end) {
			char letter = buffer[start];
			if (letter == ' ') {
				silence_counter = _wordSpaceRepeat;
				start++;
				return;
			}
			const char* morse_code = getMorseString(letter);
			if (morse_code) {
				uint8_t len = strlen(morse_code);
				if (letter_pos >= len) {
					start++;
					letter_pos = 0;
					silence_counter = _charSpaceRepeat; // between letters
				} else {
					const char code = morse_code[letter_pos];
					if (code == '.') {
						sound_counter = _ditRepeat; // dit
					}				
					else {
						sound_counter = _dahRepeat; // dah
					}
					silence_counter = _bitSpaceRepeat; // between beeps
					letter_pos++;
				}
			} else {
				start++;
				silence_counter =_charSpaceRepeat;
			}			
		}
	}
	if (sound_counter > 0) {
		soundOn();
		--sound_counter;
	} else if (silence_counter > 0) {
		 soundOff();
		--silence_counter;
	}
}

ISR(USART_RXC_vect) {
	buffer[end++] = UDR;
}

ISR(USART_TXC_vect) {}
ISR(USART_UDRE_vect) {}

int main(void)
{
    LD_DDR = 0xFF;
	SWITCH_DDR = 0x00;
	SWITCH_PORT = 0xFF;

	UBRRH = 0x00;
	UBRRL = 0x33;		
	UCSRA = 0x40;
	UCSRB = 0x98;
	UCSRC = 0x86;

	morseInit();
	counterInit();
	
	strcpy(buffer, "WITAJ SWIECIE");
	end = strlen(buffer);
	
	while(1) {}
}



