#ifndef BSP_LCD_H_
#define BSP_LCD_H_
#include "main.h"
#include "lcd.h" // Thư viện gốc của ông

void bsp_lcd_init(void);
void bsp_lcd_clear(void);
void bsp_lcd_write(uint8_t row, uint8_t col, char* str);

#endif
