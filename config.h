/*
 * config.h
 *
 * Created: 2011-11-15 18:00:42
 *  Author: pn264889
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

//1 sec ~ 61*64
#define REPEAT_TIME (61*2)

#define F_CPU 8000000UL /* 8 MHz */

// Mic 
#define MIC_PA_NUMBER 7 // PA7

// Mode select
#define SWITCH_DDR DDRC
#define SWITCH_PORT PORTC
#define SWITCH_PIN PINC

#define BEEP_MODE 0
#define SETUP_MODE 5
#define DETECT_MAX_MODE 6
#define RESET_MAX_MODE 7

/*
#define KEYBOARD_DDR DDRA
#define KEYBOARD_PORT PORTA
#define KEYBOARD_PIN PINA

#define R0 PD0
#define R1 PA1
#define R2 PA2
#define R3 PA3

#define C0 PA4
#define C1 PA5
#define C2 PA6
#define C3 PA7
*/
#define LD_DDR DDRB
#define LD_PORT PORTB

#define LD0 PB0
#define LD1 PB1
#define LD2 PB2
#define LD3 PB3
#define LD4 PB4
#define LD5 PB5
#define LD6 PB6
#define LD7 PB7

//LCD

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

#endif /* CONFIG_H_ */
