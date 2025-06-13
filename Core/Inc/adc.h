#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"

#define VREF 	3.3f
#define RL 		1.0f
#define R0 		1.9f
#define A 		-0.48f
#define B 		1.33f

void ADC1_Init(void);
uint16_t ADC1_Read(void);
uint16_t MQ2_Read_PPM(void);

#endif
