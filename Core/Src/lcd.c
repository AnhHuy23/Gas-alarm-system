#include "lcd.h"
#include "i2c.h"
#include "timer.h"

void LCD_Send_Cmd(uint8_t cmd) {
    LCD_Send_Byte(cmd, 0);
}

void LCD_Send_Data(uint8_t data) {
    LCD_Send_Byte(data, 1);
}

void LCD_Init(void) {
    delay_ms(50);
    LCD_Send_Cmd(0x33);
    LCD_Send_Cmd(0x32);
    LCD_Send_Cmd(0x28); // 4-bit, 2 line, 5x8 font
    LCD_Send_Cmd(0x0C); // Display ON
    LCD_Send_Cmd(0x06); // Entry mode
    LCD_Send_Cmd(0x01); // Clear display
    delay_ms(2);
}

void LCD_Set_Cursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? 0x80 + col : 0xC0 + col;
    LCD_Send_Cmd(addr);
}

void LCD_Send_String(char *str) {
    while (*str) LCD_Send_Data(*str++);
}

void LCD_Update_State(uint16_t gas_ppm) {
    LCD_Set_Cursor(1, 7);
    if (gas_ppm < SAFE_LEVEL) {
        LCD_Send_String("SAFE    ");
    } else if (gas_ppm < ALERT_LEVEL) {
        LCD_Send_String("ALERT   ");
    } else if (gas_ppm < DANGER_LEVEL) {
        LCD_Send_String("DANGER  ");
    } else {
        LCD_Send_String("CRITICAL");
    }
}

