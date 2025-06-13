#ifndef __I2C_H
#define __I2C_H

#define SLAVE_ADDR_LCD 	0x27 << 1
#define SCL				6
#define SDA				7

#include "stm32f4xx.h"

void I2C1_Init(void);
void I2C1_Write(uint8_t data);
void LCD_Send_Byte(uint8_t data, uint8_t rs);

#endif
