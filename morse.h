/*
 * morse.h
 *
 * Created: 2012-01-10 17:02:54
 *  Author: pn264889
 */ 

#ifndef MORSE_H_
#define MORSE_H_

#include <avr/io.h>

#define MORSE_TABLE_SIZE 128
#define MORSE_CODE_SIZE 8

//spacing are defined in dits (aka dots)
#define MORSE_DIT 1
#define MORSE_DAH 3
#define MORSE_BIT_SPACE 1
#define MORSE_CHAR_SPACE 3
#define MORSE_WORD_SPACE 7

extern const uint16_t _ditRepeat;
extern const uint16_t _dahRepeat;
extern const uint16_t _bitSpaceRepeat;
extern const uint16_t _charSpaceRepeat;
extern const uint16_t _wordSpaceRepeat;


extern char morseTable[MORSE_TABLE_SIZE][MORSE_CODE_SIZE];

void morseInit();

const char* getMorseString(uint8_t c);

#endif /* MORSE_H_ */