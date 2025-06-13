#include "timer.h"

void TIM2_Init(void) {
    RCC->APB1ENR |= (1 << 0);  			// TIM2

    TIM2->PSC = 16000 - 1;				// 16MHz/16000 = 1kHz
    TIM2->CR1 = 0;             			// Reset TIM2
    TIM2->EGR |= (1 << 0);     			// UG: cập nhật ngay giá trị PSC mới
}

void delay_ms(uint32_t ms) {
    TIM2->ARR = ms;           			// Thời gian delay (ms)
    TIM2->CNT = 0;            			// Reset bộ đếm
    TIM2->SR &= ~(1 << 0);    			// Xóa cờ UIF
    TIM2->CR1 |= (1 << 0);    			// Bật TIM2

    while ((TIM2->SR & (1 << 0)) == 0); // Chờ đến khi UIF = 1 (tràn)
    TIM2->SR &= ~(1 << 0);    			// Xóa cờ UIF khi delay xong
    TIM2->CR1 &= ~(1 << 0);   			// Tắt timer
}
