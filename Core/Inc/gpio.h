#ifndef __GPIO_H
#define __GPIO_H

#define STOP_BUTTON 	0
#define RESET_BUTTON 	1
#define RELAY 			4
#define BUZZER 			5
#define RED_LED 		10
#define YELLOW_LED 		11
#define BLUE_LED 		12
#define GREEN_LED 		15

#include "stm32f4xx.h"

void GPIO_Init(void);
void Turn_On_GPIO(uint16_t pin);
void Turn_Off_GPIO(uint16_t pin);
void System_Shutdown(void);
void System_Safe(void);
void System_Alert(void);
void System_Danger(void);
void System_Critical(uint16_t gas_ppm);

extern volatile uint32_t speed;

#endif
