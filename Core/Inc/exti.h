#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f4xx.h"

void EXTI_Init(void);

extern volatile uint8_t paused_flag;
extern volatile uint8_t reset_flag;

#endif
