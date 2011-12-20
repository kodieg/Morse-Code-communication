/*
 * keyboard.h
 *
 * Created: 2011-11-15 17:41:36
 *  Author: pn264889
 */ 

#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "config.h"

#include <avr/io.h>
#include <stdint.h>

/*
    requires following defines:

    #define KEYBOARD_DDR DDRA
    #define KEYBOARD_PORT PORTA
    #define KEYBOARD_PIN PINA

    #define R0 PA0
    #define R1 PA1
    #define R2 PA2
    #define R3 PA3

    #define C0 PA4
    #define C1 PA5
    #define C2 PA6
    #define C3 PA7
 */

/**
 * Returns key code scanned from 4x4 keyboard. 
 * Codes [0,16) - correct key number
 * Codes (-inf, -58) or [16, + inf) - multiple input
 * Code -58 - no input
 **/
//int8_t readKeypad(void);

//void initKeypad();


#endif /* KEYBOARD_H_ */