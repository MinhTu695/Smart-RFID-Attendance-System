#include "bsp_lcd.h"

void bsp_lcd_init(void) {
    LCD_Init();
}
void bsp_lcd_clear(void) {
    LCD_Clear();
}
void bsp_lcd_write(uint8_t row, uint8_t col, char* str) {
    LCD_SetCursor(col, row); // Lưu ý thư viện gốc là (col, row)
    LCD_WriteString(str);
}
