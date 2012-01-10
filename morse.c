/*
 * morse.c
 *
 * Created: 2012-01-10 17:03:13
 *  Author: pn264889
 */ 

#include "morse.h"

#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

char morseTable[MORSE_TABLE_SIZE][8];

static void setMorseTable(uint8_t index, const char *morseCode) {
	
	uint8_t end = 0;
	for (uint8_t i = 0; i < MORSE_CODE_SIZE; i++) {
		
		if (!end && morseCode[i] == 0)
		    end = 1;
			
		if (end)
		    morseTable[index][i] = 0;
	    else
	        morseTable[index][i] = morseCode[i];
	}   
}

void morseInit() {
		
	for (uint8_t i = 0; i < MORSE_TABLE_SIZE; i++)
	    setMorseTable(i, "");
		
    setMorseTable('A', ".-");
    setMorseTable('U', "..-");
    setMorseTable('B', "-...");
    setMorseTable('V', "...-");
    setMorseTable('C', "-.-.");
    setMorseTable('W', ".--");
    setMorseTable('D', "-..");
    setMorseTable('X', "-..-");
    setMorseTable('E', ".");
    setMorseTable('Y', "-.--");
    setMorseTable('Z', "--..");
    setMorseTable('F', "..-.");
    setMorseTable('G', "--.");
    setMorseTable('0', "-----");
    setMorseTable('H', "....");
    setMorseTable('1', ".----");
    setMorseTable('I', "..");
    setMorseTable('2', "..---");
    setMorseTable('J', ".---");
    setMorseTable('3', "...--");
    setMorseTable('4', "....-");
    setMorseTable('K', "-.-");
    setMorseTable('5', ".....");
    setMorseTable('L', ".-..");
    setMorseTable('6', "-....");
    setMorseTable('M', "--");
    setMorseTable('7', "--...");
    setMorseTable('N', "-.");
    setMorseTable('8', "---..");
    setMorseTable('O', "---");
    setMorseTable('9', "----.");
    setMorseTable('P', ".--.");
    setMorseTable('.', ".-.-.-");
    setMorseTable('Q', "--.-");
    setMorseTable(',', "--..--");
    setMorseTable('R', ".-.");
    setMorseTable('?', "..--..");
    setMorseTable('S', "...");
    setMorseTable('-', "-....-");
    setMorseTable('T', "-");
    setMorseTable('`', ".----.");
    setMorseTable(':', "---...");
    setMorseTable('U', "..-");
    setMorseTable('"', ".-..-.");
    setMorseTable('V', "...-");
    setMorseTable('/', "-..-.");
    setMorseTable('W', ".--");
    setMorseTable('@', ".--.-.");
    setMorseTable('X', "-..-");
    setMorseTable('Y', "-.--");
    setMorseTable('Z', "--..");		
};