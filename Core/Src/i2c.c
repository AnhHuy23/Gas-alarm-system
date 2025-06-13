#include "i2c.h"
#include "timer.h"

void I2C1_Init(void) {
	RCC->AHB1ENR |= 1 << 1;				// GPIOB
    RCC->APB1ENR |= 1 << 21;			// I2C1

    // AF
    GPIOB->MODER &= ~(3 << (SCL * 2));
    GPIOB->MODER |= 2 << (SCL * 2);		// PB6: SCL
    GPIOB->OTYPER |= 1 << SCL;			// Open-drain
    GPIOB->AFR[0] |= 4 << (SCL * 4);	// AF4: I2C mode
    GPIOB->MODER &= ~(3 << (SDA * 2));
    GPIOB->MODER |= 2 << (SDA * 2);		// PB7: SDA
    GPIOB->OTYPER |= 1 << SDA;			// Open-drain
    GPIOB->OSPEEDR |= (3 << (6 * 2)) | (3 << (7 * 2));
    GPIOB->AFR[0] |= 4 << (SDA * 4);	// AF4: I2C mode

    I2C1->CR2 = 16;     				// APB1 at 16 MHz
    I2C1->CCR = 80;     				// 100kHz
    I2C1->TRISE = 17;
    I2C1->CR1 |= 1 << 0;
}

void I2C1_Write(uint8_t data) {
    while (!(I2C1->SR1 & I2C_SR1_TXE));
    I2C1->DR = data;
    while (!(I2C1->SR1 & I2C_SR1_BTF));
}

void LCD_Send_Byte(uint8_t data, uint8_t rs) {
    uint8_t upper = data & 0xF0;
    uint8_t lower = (data << 4) & 0xF0;
    uint8_t data_arr[4] = {
        upper | 0x0C | rs,
        upper | 0x08 | rs,
        lower | 0x0C | rs,
        lower | 0x08 | rs
    };

    I2C1->CR1 |= I2C_CR1_START;
    while (!(I2C1->SR1 & I2C_SR1_SB));
    I2C1->DR = SLAVE_ADDR_LCD;
    while (!(I2C1->SR1 & I2C_SR1_ADDR));
    (void)I2C1->SR2;

    for (int i = 0; i < 4; i++) {
        I2C1_Write(data_arr[i]);
    }

    I2C1->CR1 |= I2C_CR1_STOP;
    delay_ms(1);
}
