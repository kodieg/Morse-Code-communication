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
#include "morse.h"

#define EMA_RATE 4
#define EMA_THRESHOLD_OFFSET 10;
uint16_t EmaThreshold = 0x1FF;

enum ReceiverState {
	Idle,
	Reading,
	CoolingDown,
	OverFlow
};

volatile enum ReceiverState _state = Idle;


volatile uint16_t _highRepeatCount = 0; 
volatile uint16_t _lowRepeatCount = 0; 

uint8_t WorkMode = 0;

volatile uint16_t _avgVal=0;
uint16_t _previousAvgVal=0;

#define IN_BUFFER_SIZE 16

uint8_t _bufferStart = 0;
uint8_t _bufferEnd = 0;
uint8_t _bufferWriteBit = 0; // next bit read position is _inputBuffer[_bufferEnd][_bufferWriteBit]
char _inputBuffer[IN_BUFFER_SIZE][MORSE_CODE_SIZE];

ISR(TIMER0_COMP_vect) {
}

ISR(ADC_vect) {

   const uint16_t micVal = micRead();
   _previousAvgVal = _avgVal;

	if (_avgVal < micVal)
	    _avgVal = micVal;
	else {
		uint16_t diffVal = (_avgVal >> EMA_RATE);
		
		// if AvgVal >> EMA_RATE would be underflow
		if (diffVal == 0) {
			// asserting that never diffVal > AvgVal
		    diffVal = _avgVal > EMA_RATE ? EMA_RATE : _avgVal;
		}			
	
		// avg_n+1 = (avg_n*(E-1))/E + mic/E
		// avg_n+1 = avg_n - avg_n/E + mic/E
		_avgVal = _avgVal - diffVal + (micVal >> EMA_RATE);
	}		
	
	if (CHECK(WorkMode, DETECT_MAX_MODE) && _avgVal > EmaThreshold)
	    EmaThreshold = _avgVal + EMA_THRESHOLD_OFFSET;
		
	if (CHECK(WorkMode, RESET_MAX_MODE)) {
		_state = Idle;
		_bufferStart = _bufferEnd = 0;
	    EmaThreshold = 0;
	}		
	
	// DEBUG led output
	if (_avgVal > EmaThreshold)
	    LD_DDR = 0x00;
	else
	    LD_DDR = 0xFF;
		
    if (!CHECK(WorkMode, SETUP_MODE)) {
		
		if (_state == OverFlow)
		    return;
		
	    if (_avgVal > EmaThreshold) {
		    ++_highRepeatCount;	
			_lowRepeatCount = 0;
		}			
	    else if (_previousAvgVal > EmaThreshold) {
	        // Previously we were over the threshold, now we are under
		    // so we have finished receiving a bit
			
			int8_t receivedBit = -1;
			
			if (_highRepeatCount >= _dahRepeat) {
			    receivedBit = 1;
			}				
		    else if (_highRepeatCount >= _ditRepeat) {
			    receivedBit = 0;
			}				
			
			if (receivedBit >= 0) {
			    _inputBuffer[_bufferEnd][_bufferWriteBit++] = receivedBit ? '-' : '.';
			
			    _state = Reading;
			}				
			
			_highRepeatCount = 0;
			_lowRepeatCount = 0;
	    }
		else if (_state == Reading) {
			++_lowRepeatCount;
			
			if (_lowRepeatCount >= _charSpaceRepeat) {
				
				_inputBuffer[_bufferEnd][_bufferWriteBit] = 0;
				
				_bufferEnd = (_bufferEnd + 1) % IN_BUFFER_SIZE;
				_bufferWriteBit = 0;
				
				if (_bufferEnd == _bufferStart)
				    _state = OverFlow;
					
			    _lowRepeatCount = 0;
				_state = CoolingDown;
			}
		}
		else if (_state == CoolingDown) {
			++_lowRepeatCount;
			
			if (_lowRepeatCount >= _messageSpaceRepeat) {
				_inputBuffer[_bufferEnd][0] = 0;
				_bufferEnd = (_bufferEnd + 1) % IN_BUFFER_SIZE;
				_bufferWriteBit = 0;
				_state = Idle;
			}
		}					
    }		
}

int main(void)
{
	morseInit();
	lcdInit();
	micInit();
	counterInit();
	
    LD_DDR = 0xFF;
	SWITCH_DDR = 0x00;
	SWITCH_PORT = 0xFF;
	
	lcdString("Hello world!\0");

	while(1)
	{
		WorkMode = ~SWITCH_PIN;
		
		if (CHECK(WorkMode, SETUP_MODE))
		{
            lcdClear();
  
	        if (WorkMode == 0)
		        lcdInt(_avgVal);
	        else
                lcdInt(EmaThreshold);
		    lcdData('X');
		}
		else {
			if (_state == OverFlow) {
				lcdData('X');
			}				
			// if there is something to read, receive it
		    else if (_bufferStart != _bufferEnd)	{
				//lcdData('#');
				
				//lcdString(_inputBuffer[_bufferStart]);
				const char *message = _inputBuffer[_bufferStart];
				
				if (message[0] != 0)
				    lcdData(getMorseChar(message));
				else
				    lcdClear();
				
				_bufferStart = (_bufferStart + 1) % IN_BUFFER_SIZE;
		    }
		}			

		_delay_ms(50);
    }
}

