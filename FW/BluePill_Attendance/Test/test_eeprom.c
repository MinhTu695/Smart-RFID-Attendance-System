/* Copy vào App/app_main.c */
#include "app_main.h"
#include "lcd.h"
#include "eeprom.h"
#include <stdio.h>

void App_Init(void) {
    LCD_Init();
    LCD_SetCursor(0, 0);
    LCD_WriteString("EEPROM TEST...");
    HAL_Delay(1000);

    // 1. Dữ liệu mẫu để test (Ví dụ: AA BB CC DD)
    uint8_t testDataWrite[4] = {0xAA, 0xBB, 0xCC, 0xDD};

    // 2. Ghi vào địa chỉ 0
    EEPROM_Write(0, testDataWrite, 4);

    LCD_SetCursor(0, 1);
    LCD_WriteString("Writing... Done");
    HAL_Delay(1000);

    // 3. Đọc lại từ địa chỉ 0
    uint8_t testDataRead[4];
    EEPROM_Read(0, testDataRead, 4);

    // 4. Hiển thị kết quả đọc được
    LCD_Clear();
    LCD_SetCursor(0, 0);
    LCD_WriteString("Read Result:");

    char strBuf[16];
    sprintf(strBuf, "%02X %02X %02X %02X",
            testDataRead[0], testDataRead[1], testDataRead[2], testDataRead[3]);

    LCD_SetCursor(0, 1);
    LCD_WriteString(strBuf);

    // Nếu màn hình hiện: AA BB CC DD là thành công!
}

void App_Loop(void) {
    // Không làm gì cả
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_Delay(500);
}
