#include "gpio.h"
#include "timer.h"

volatile uint32_t speed = 0;

void GPIO_Init(void) {
	RCC->AHB1ENR |= 1 << 0;						// GPIOA

	// Input
	GPIOA->MODER &= ~(3 << (STOP_BUTTON * 2));	// PA0: stop button
	GPIOA->MODER &= ~(3 << (RESET_BUTTON * 2));	// PA1: reset button

	// Output
	GPIOA->MODER &= ~(3 << (RELAY * 2));
	GPIOA->MODER |= 1 << (RELAY * 2);			// PA4: relay
	GPIOA->MODER &= ~(3 << (BUZZER * 2));
	GPIOA->MODER |= 1 << (BUZZER * 2);			// PA5: buzzer
	GPIOA->MODER &= ~(3 << (RED_LED * 2));
	GPIOA->MODER |= 1 << (RED_LED * 2);			// PA10: red led
	GPIOA->MODER &= ~(3 << (YELLOW_LED * 2));
	GPIOA->MODER |= 1 << (YELLOW_LED * 2);		// PA11: yellow led
	GPIOA->MODER &= ~(3 << (BLUE_LED  * 2));
	GPIOA->MODER |= 1 << (BLUE_LED  * 2);		// PA12: blue led
	GPIOA->MODER &= ~(3 << (GREEN_LED  * 2));
	GPIOA->MODER |= 1 << (GREEN_LED  * 2);		// PA15: green led
}

void Turn_On_GPIO(uint16_t pin) {
    GPIOA->BSRR = (1 << pin);
}

void Turn_Off_GPIO(uint16_t pin) {
    GPIOA->BSRR = (1 << (pin + 16));
}

void Turn_Off_Relay(void) {
    GPIOA->BSRR = (1 << (RELAY + 16));
}

void Turn_On_Relay(void) {
    GPIOA->BSRR = (1 << RELAY);
}

void System_Shutdown(void) {
	Turn_Off_GPIO(RED_LED); 	Turn_Off_GPIO(YELLOW_LED);
	Turn_Off_GPIO(BLUE_LED); 	Turn_Off_Relay();
	Turn_On_GPIO(GREEN_LED);
	Turn_Off_GPIO(BUZZER);
}

void System_Safe(void) {
	Turn_Off_GPIO(GREEN_LED);
	Turn_Off_GPIO(YELLOW_LED); 	Turn_Off_GPIO(RED_LED);
	Turn_Off_GPIO(BUZZER);		Turn_Off_Relay();
	Turn_On_GPIO(BLUE_LED);
}

void System_Alert(void) {
	Turn_Off_GPIO(GREEN_LED);
	Turn_Off_GPIO(BLUE_LED); 	Turn_Off_GPIO(RED_LED);
	Turn_Off_GPIO(BUZZER);		Turn_Off_Relay();
	Turn_On_GPIO(YELLOW_LED);
}

void System_Danger(void) {
	Turn_Off_GPIO(GREEN_LED);
	Turn_Off_GPIO(YELLOW_LED); 	Turn_Off_GPIO(BLUE_LED);
	Turn_Off_GPIO(BUZZER); 		Turn_On_Relay();
	Turn_On_GPIO(RED_LED); 		delay_ms(500);
	Turn_Off_GPIO(RED_LED); 	delay_ms(500);
}

void System_Critical(uint16_t gas_ppm) {
	Turn_Off_GPIO(GREEN_LED);
	Turn_Off_GPIO(YELLOW_LED); 	Turn_Off_GPIO(BLUE_LED);
	Turn_On_GPIO(BUZZER); 		Turn_On_Relay();
	speed = (4000 - gas_ppm) * (250 - 50)/(4000 - 1000) + 50;
	Turn_On_GPIO(RED_LED); 		delay_ms(speed);
	Turn_Off_GPIO(RED_LED); 	delay_ms(speed);
}
