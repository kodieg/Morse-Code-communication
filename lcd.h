/*
 * lcd.h
 *
 * Created: 2011-11-29 16:55:19
 *  Author: pn264889

    rquires following defines 
    #define LCD_DATA_PORT PORTD // port danych
    #define LCD_E_PORT PORTD    // port linii wyzwalajacej E
    #define LCD_RS_PORT PORTD   // port linii LCD_RS
    #define LCD_DATA_DDR DDRD   // rejestr kierunku danych
    #define LCD_E_DDR DDRD      // rejestr kierunku linii E
    #define LCD_RS_DDR DDRD     // rejestr kierunku linii LCD_RS
    #define LCD_OE PD1          // numer bitu linii OE
    #define LCD_RS PD0          // numer bitu linii RS
    #define LCD_D4 PD2          // numer bitu linii D4
    #define LCD_D5 PD3          // numer bitu linii D5
    #define LCD_D6 PD4          // numer bitu linii D6
    #define LCD_D7 PD5          // numer bitu linii D7
*/


#ifndef LCD_H_
#define LCD_H_

#include "config.h"

#include <avr/io.h>
#include <stdint.h>

void lcdInit();

//move cursor to pos position (7 bit)
void lcdGoTo(uint8_t pos);
    
//send 8bit data to the LCD using R16 as argument
void lcdData(uint8_t data);

// print string on lcd
void lcdString(char* str);

// clear lcd
void lcdClear();

void lcdInstr(uint8_t instr);
    
#endif /* LCD_H_ */