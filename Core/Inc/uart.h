#ifndef __UART_H
#define __UART_H

#include "stm32f4xx.h"

void USART2_Init(void);
void USART2_SendChar(char c);
void USART2_SendString(const char *str);

#endif
