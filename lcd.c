/*
 * lcd.c
 *
 * Created: 2011-11-29 17:01:14
 *  Author: pn264889
 */ 

#include "lcd.h"

#include <avr/delay.h>

#include "commons.h"

void lcdSend4Bits(uint8_t data)
{    
    SBI(LCD_E_PORT, LCD_OE);
    
    SBI(LCD_DATA_PORT, LCD_D4);
    SBI(LCD_DATA_PORT, LCD_D5);  
    SBI(LCD_DATA_PORT, LCD_D6);
    SBI(LCD_DATA_PORT, LCD_D7);
    
    if (!CHECK(data, 4))
        CBI(LCD_DATA_PORT, LCD_D4);
    if (!CHECK(data, 5))
        CBI(LCD_DATA_PORT, LCD_D5);
    if (!CHECK(data, 6))
        CBI(LCD_DATA_PORT, LCD_D6);
    if (!CHECK(data, 7))
        CBI(LCD_DATA_PORT, LCD_D7);
    
    _delay_loop_1(1); // 3+ cycles
    
    CBI(LCD_E_PORT, LCD_OE);
}

void lcdSend4BitsMode(uint8_t data)
{
    lcdSend4Bits(data);
    SWAP(data);
    lcdSend4Bits(data);
    
    _delay_us(40);
}

void lcdInit()
{
    // based on http://www.mimuw.edu.pl/~marpe/mikrokontrolery/w5_klawisze_lcd.pdf 
    // slide no. 26
    
    // set input/output direction
    SBI(LCD_DATA_DDR, LCD_D4);
    SBI(LCD_DATA_DDR, LCD_D5);
    SBI(LCD_DATA_DDR, LCD_D6);
    SBI(LCD_DATA_DDR, LCD_D7);      
    SBI(LCD_E_DDR, LCD_OE);   
    SBI(LCD_RS_DDR, LCD_RS);
    
    CBI(LCD_RS_PORT, LCD_RS);
    CBI(LCD_E_PORT, LCD_OE);
    
    _delay_ms(40);
    
    SBI(LCD_E_PORT, LCD_OE);
    SBI(LCD_DATA_PORT, LCD_D4);
    SBI(LCD_DATA_PORT, LCD_D5);
    CBI(LCD_DATA_PORT, LCD_D6);
    CBI(LCD_DATA_PORT, LCD_D7);
    
    _delay_loop_1(1); // 3+ cycles

    CBI(LCD_E_PORT, LCD_OE);
    
    _delay_ms(4.1);
    
    SBI(LCD_E_PORT, LCD_OE);
    
    _delay_loop_1(1); // 3+ cycles
    
    CBI(LCD_E_PORT, LCD_OE);
    
    _delay_us(100);
    
    SBI(LCD_E_PORT, LCD_OE);
    
    _delay_loop_1(1); // 3+ cycles
    
    CBI(LCD_E_PORT, LCD_OE);
    
    _delay_us(100);

    SBI(LCD_E_PORT, LCD_OE);
    CBI(LCD_DATA_PORT, LCD_D4);
    
    _delay_loop_1(1); // 3+ cycles
    
    CBI(LCD_E_PORT, LCD_OE); 
    
    _delay_us(100);
        
    lcdInstr(0x28); //0b00101000
    
    lcdInstr(0x06); //0b00000110
    
    lcdInstr(0x0f); //0b00001111

    lcdInstr(0x01); //0b00000001
    
    _delay_ms(2);    
}    
 
//move cursor to pos position (7 bit)
void lcdGoTo(uint8_t pos)
{
    lcdInstr(pos | (1<<7));
}

void lcdClear(void)
{
	lcdInstr(0x01); //0b00000001	
	_delay_ms(3);
}	    
    
//send 8bit data to the LCD using R16 as argument
void lcdData(uint8_t data)
{
    SBI(LCD_RS_PORT, LCD_RS);
    lcdSend4BitsMode(data);
}

void lcdString(char* str)
{
	while (*str != 0) 
	{
		lcdData(*str);
		++str;
	}	
}

void lcdInt(int16_t i)
{
	if (i < 0) 
	{
		lcdString("-");
		i = -i;
	}
	lcdUint(i);
}

void lcdUint(uint16_t i)
{
	int8_t log2 = 0;
	int16_t tmp = i;
	
	while (tmp > 15)
	{
		tmp >>= 4;
		log2 += 4;	
	}
	
	while (log2 >= 0)
	{
		int16_t div = i >> log2;
		lcdData(div + (div > 9 ? 'A'- 10: '0'));
		i -= div << log2;
		log2 -= 4;
	}	
}


void lcdInstr(uint8_t instr)
{
    CBI(LCD_RS_PORT, LCD_RS);
    lcdSend4BitsMode(instr);
}