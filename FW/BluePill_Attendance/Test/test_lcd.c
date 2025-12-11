/* Copy vào App/app_main.c */
#include "app_main.h"
#include "lcd.h"

void App_Init(void) {
    LCD_Init();

    // Test in dòng 1
    LCD_SetCursor(0, 0);
    LCD_WriteString("TEST LCD 16x2");

    // Test in dòng 2
    LCD_SetCursor(0, 1);
    LCD_WriteString("Hello World!");

    HAL_Delay(2000);
}

void App_Loop(void) {
    // Test hiệu ứng nhấp nháy chữ
    LCD_Clear();
    HAL_Delay(500);

    LCD_SetCursor(0, 0);
    LCD_WriteString("BLINK TEST");
    HAL_Delay(1000);
}
