/*
 * keyboard.c
 *
 * Created: 2011-11-15 17:41:50
 *  Author: pn264889
 */ 
/*
#include "keyboard.h"

#include <avr/delay.h>
#include "commons.h"

void initKeypad()
{
    KEYBOARD_DDR = 0xF0; //rows as inputs, columns as outputs
    KEYBOARD_PORT = 0x0F; //rows with resistors, columns 0    
}

int8_t readKeypad()
{
    initKeypad();
    
    int8_t key = -58;
    if (!CHECK(KEYBOARD_PIN, R0))
        key += 41;
    if (!CHECK(KEYBOARD_PIN, R1))
        key += 45;        
    if (!CHECK(KEYBOARD_PIN, R2))
        key += 49;
    if (!CHECK(KEYBOARD_PIN, R3))
        key += 53;
        
    KEYBOARD_DDR = 0x0F; //rows as outputs, columns as inputs
    KEYBOARD_PORT = 0xF0; //rows 0, columns with resistors
        
    _delay_loop_1(16);
    
    if (!CHECK(KEYBOARD_PIN, C0))
        key += 17;
    if (!CHECK(KEYBOARD_PIN, C1))
        key += 18;        
    if (!CHECK(KEYBOARD_PIN, C2))
        key += 19;
    if (!CHECK(KEYBOARD_PIN, C3))
        key += 20;    
        
    initKeypad();
    return key;   
}    */