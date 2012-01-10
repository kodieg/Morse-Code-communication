/*
 * morse.h
 *
 * Created: 2012-01-10 17:02:54
 *  Author: pn264889
 */ 


#ifndef MORSE_H_
#define MORSE_H_

#define MORSE_TABLE_SIZE 128
#define MORSE_CODE_SIZE 8

extern char morseTable[MORSE_TABLE_SIZE][8];

void morseInit();

const char* getMorseString(char c) {
	morseTable[c];
};

#endif /* MORSE_H_ */