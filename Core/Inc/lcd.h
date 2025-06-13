#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx.h"

#define SAFE_LEVEL 		300
#define ALERT_LEVEL 	700
#define DANGER_LEVEL 	1000

void LCD_Send_Cmd(uint8_t cmd);
void LCD_Send_Data(uint8_t data);
void LCD_Init(void);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Send_String(char *str);
void LCD_Update_State(uint16_t gas_ppm);

#endif
