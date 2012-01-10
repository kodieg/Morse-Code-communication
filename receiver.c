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

#include "commons.h"
#include "lcd.h"
#include "mic.h"
#include "counter.h"

#define EMA_RATE 6
#define EMA_THRESHOLD_OFFSET 10;
uint16_t EmaThreshold = 0x1FF;

//1 sec ~ 0x70
#define REPEAT_1SEC 0x70;

const uint16_t ShortRepeat = REPEAT_1SEC;
const uint16_t LongRepeat = 2*REPEAT_1SEC;
volatile uint16_t RepeatCount = 0; 

uint8_t WorkMode = 0;

volatile uint16_t AvgVal=0;
uint16_t PreviousAvgVal=0;

volatile uint8_t ReceivedValue = 0;
volatile uint8_t ReceivedCounter = 0;

ISR(TIMER0_OVF_vect) {
}	

ISR(ADC_vect) {

   const uint16_t micVal = micRead();
   PreviousAvgVal = AvgVal;

	if (AvgVal < micVal)
	    AvgVal = micVal;
	else {
		uint16_t diffVal = (AvgVal >> EMA_RATE);
		
		// if AvgVal >> EMA_RATE would be underflow
		if (diffVal == 0) {
			// asserting that never diffVal > AvgVal
		    diffVal = AvgVal > EMA_RATE ? EMA_RATE : AvgVal;
		}			
	
		// avg_n+1 = (avg_n*(E-1))/E + mic/E
		// avg_n+1 = avg_n - avg_n/E + mic/E
		AvgVal = AvgVal - diffVal + (micVal >> EMA_RATE);
	}		
	
	if (CHECK(WorkMode, DETECT_MAX_MODE) && AvgVal > EmaThreshold)
	    EmaThreshold = AvgVal + EMA_THRESHOLD_OFFSET;
		
	if (CHECK(WorkMode, RESET_MAX_MODE))
	    EmaThreshold = 0;
	
	// DEBUG led output
	if (AvgVal > EmaThreshold)
	    LD_DDR = 0x00;
	else
	    LD_DDR = 0xFF;
		
    if (CHECK(WorkMode, RECEIVE_MODE)) {
	    if (AvgVal > EmaThreshold)
		    ++RepeatCount;	
	    else if (PreviousAvgVal > EmaThreshold) {
	        // Previously we were over the threshold, now we are under
		    // so we have finished receiving a bit
			
			if (RepeatCount >= LongRepeat) {
			    ReceivedValue = 1;
				++ReceivedCounter;
			}				
		    else if (RepeatCount >= ShortRepeat) {
			    ReceivedValue = 0;
				++ReceivedCounter;
			}				
			
			RepeatCount = 0;
	    }				
    }		
}

int main(void)
{
	lcdInit();
	micInit();
	counterInit();
	
    LD_DDR = 0xFF;
	SWITCH_DDR = 0x00;
	SWITCH_PORT = 0xFF;
	
    uint8_t localReceivedCounter = 0;
	
	lcdString("Hello world!\0");

	while(1)
	{
		WorkMode = ~SWITCH_PIN;
		
		if (!CHECK(WorkMode, RECEIVE_MODE))
		{
            lcdClear();
  
	        if (WorkMode == 0)
		        lcdInt(AvgVal);
	        else
                lcdInt(EmaThreshold);
		}
		else {
			// if there is something to read, receive it
		    if (localReceivedCounter < ReceivedCounter)	{
				lcdData('#');				
			    lcdUint(ReceivedValue);
				++localReceivedCounter;
		    }
			// if there is something more to read, that means
			// we probably lost some bit!
			if (localReceivedCounter < ReceivedCounter) 
			    lcdData('X');
		}			

		_delay_ms(50);
    }
}

