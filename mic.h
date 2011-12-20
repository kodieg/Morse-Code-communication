/*
 * mic.h
 *
 * Created: 2011-12-06 17:35:43
 *  Author: kodie
 */ 


#ifndef MIC_H_
#define MIC_H_

// Requires definition of MIC_PA_NUMBER in range [0, 7]
#include "config.h"

#include <avr/io.h>
#include <stdint.h>

void micInit(void);

uint16_t micRead(void);

#endif /* MIC_H_ */