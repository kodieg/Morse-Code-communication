/*
 * commons.h
 *
 * Created: 2011-11-15 16:54:13
 *  Author: pn264889
 */ 


#ifndef COMMONS_H_
#define COMMONS_H_

//swap bytes
#define BSWAP_16(x)   ((((x) & 0xFF00) >> 8) | (((x) & 0x00FF) << 8))

//swap half bytes
#define SWAP(x)   (x) = ((((x) & 0xF0) >> 4) | (((x) & 0x0F) << 4))

#define SBI(port, bit) port |= 1 << bit
#define CBI(port, bit) port &= ~(1 << bit)

//check if bit is set in pin
#define CHECK(pin, bit) (pin & (1 << bit))

//on DDRX
#define INPUT(port, bit) CBI(port, bit)
//on DDRX
#define OUTPUT(port, bit) SBI(port, bit)

//on PORTX
#define CLEAR_RESISTOR(port, bit) CBI(port, bit)
//on PORTX
#define SET_RESISTOR(port, bit) SBI(port, bit)


#endif /* COMMONS_H_ */