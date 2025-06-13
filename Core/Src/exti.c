#include "exti.h"

volatile uint8_t paused_flag = 0;
volatile uint8_t reset_flag = 0;

void EXTI_Init(void) {
	RCC->APB2ENR |= 1 << 14;

	SYSCFG->EXTICR[0] &= ~(0xF << (0 * 4)); // EXTI0 = PA0
	SYSCFG->EXTICR[0] &= ~(0xF << (1 * 4));	// EXTI1 = PA1

	EXTI->IMR  |= (1 << 0) | (1 << 1);   	// Unmask EXTI0 và EXTI1
	EXTI->FTSR |= (1 << 0) | (1 << 1);   	// Sườn xuống

	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI0_IRQHandler(void) {
	if(EXTI->PR & (1 << 0)) {
		paused_flag = 1;
		EXTI->PR |= (1 << 0);
	}
}

void EXTI1_IRQHandler(void) {
	if(EXTI->PR & (1 << 1)) {
		reset_flag = 1;
		EXTI->PR |= (1 << 1);
	}
}
