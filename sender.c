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
#include <string.h>

#include "commons.h"
//#include "keyboard.h"
#include "lcd.h"
#include "mic.h"
#include "counter.h"
#include "morse.h"
//INT0_vect
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

const uint16_t DITS_SCALER = 61;

volatile uint8_t turn_sound_off = 0;
volatile uint8_t sound_is_on = 0;
volatile uint16_t sound_counter = 0;
volatile uint16_t silence_counter = 0;

volatile char buffer[256];
volatile uint8_t start = 0;
volatile uint8_t end = 0;
volatile uint8_t letter_pos = 0;

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
		//sound_off();
		if (start != end) {
			char letter = buffer[start];
			const char* morseCode = getMorseString(letter);
			if (morseCode) {
				uint8_t len = strlen(morseCode);
				if (letter_pos >= len) {
					start++;
					letter_pos = 0;
					silence_counter = _charSpaceRepeat; // between letters
				} else {
					const char code = morseCode[letter_pos];
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
		sound_on();
		--sound_counter;
	} else if (silence_counter > 0) {
		 sound_off();
		--silence_counter;
	}
}

void sound_on() {
	if (sound_is_on == 0) {
		sound_is_on = 1;
		TCCR0 = (1 << WGM01 | 1 << COM00 | 1 << CS01);	
		SBI(LD_DDR, 0);
	}		
}

void sound_off() {
	if (sound_is_on) {
		sound_is_on = 0;
		turn_sound_off = 1;
		CBI(LD_DDR, 0);
		//TCCR0 = (1 << WGM01 | 1 << CS01);
	}	
}

ISR(USART_RXC_vect) {
	uint8_t b = UDR;
	buffer[end] = b;
	++end;
	// lcdInt(b);
}

ISR(USART_TXC_vect) {}
ISR(USART_UDRE_vect) {}

int WorkMode = 0;

int main(void)
{
    LD_DDR = 0xFF;
	SWITCH_DDR = 0x00;
	SWITCH_PORT = 0xFF;
		
	UCSRA = 0x40;
	UCSRB = 0x98;
	UCSRC = 0x86;
	UBRRH = 0x00;
	UBRRL = 0x33;

	morseInit();
	lcdInit();
	counterInit();
			
	const uint8_t MIN_TRESHOLD = 127;
	uint8_t previous = 128;
	uint8_t counter = 0;
	volatile uint16_t timer = 1001;

	
	strcpy(buffer, "KODIE SOS");
	end = strlen(buffer);
	
	while(1)
	{}
	{
			
			
		WorkMode = ~SWITCH_PIN;
		if (timer > 100) {
		  // cli();
		  lcdClear();
		  lcdString(buffer);
		  lcdString(" ");
		  lcdInt(start);
		  lcdString(" ");
		  lcdInt(sound_counter);
		  lcdString(" ");
		  lcdInt(silence_counter);
		  // sei();
		  timer = 0;	
		}		
		timer++;
		
		if (previous != CHECK(WorkMode, BEEP_MODE)) {
			counter = 0;
			previous = CHECK(WorkMode, BEEP_MODE);
		} else {
			counter++;			
		}			
		
		if (counter > MIN_TRESHOLD) {
			counter = MIN_TRESHOLD;
			if (previous == 1 && !sound_is_on) {
			  sound_on();
			  //lcdInt(0);
			} else if (previous == 0 && sound_is_on) {
			  sound_off();
			  //lcdInt(1);
			}			
		}
		
		_delay_us(100);
		//lcdInt(TCCR0);
		//_delay_ms(100);
	}
/*
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
*/
}



