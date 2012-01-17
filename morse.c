/*
 * morse.c
 *
 * Created: 2012-01-10 17:03:13
 *  Author: pn264889
 */ 

#include <stdlib.h>
#include "morse.h"
#include "config.h"

const uint16_t _ditRepeat = REPEAT_TIME * MORSE_DIT;
const uint16_t _dahRepeat = REPEAT_TIME * MORSE_DAH;
const uint16_t _bitSpaceRepeat = REPEAT_TIME * MORSE_BIT_SPACE;
const uint16_t _charSpaceRepeat = REPEAT_TIME * MORSE_CHAR_SPACE;
const uint16_t _wordSpaceRepeat = REPEAT_TIME * MORSE_WORD_SPACE;

uint8_t _minIndex = 255; //probably after morseInit it will be "
uint8_t _maxIndex = 0; //probably after morseInit it will be `

char morseTable[MORSE_TABLE_SIZE][MORSE_CODE_SIZE];

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
	if (index > _maxIndex)
	    _maxIndex = index;
	if (index < _minIndex)
	    _minIndex = index;
}

void morseInit() {
		
	for (uint8_t i = 0; i < MORSE_TABLE_SIZE; i++)
	    setMorseTable(i, 0);
		
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

 const char* getMorseString(uint8_t c) {
	return morseTable[c];
};

uint8_t getMorseChar(const char *morseString) {
	for (uint8_t i = _minIndex; i <= _maxIndex; i++) {
		
		const char *str = getMorseString(i);
		if (str && (strcmp(str, morseString) == 0))
		    return i;
	}  	
	return '~';
}