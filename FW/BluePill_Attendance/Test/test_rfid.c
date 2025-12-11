/* Copy vào App/app_main.c */
#include "app_main.h"
#include "lcd.h"
#include "rfid.h"
#include <stdio.h>

void App_Init(void) {
    LCD_Init();
    MFRC522_Init();

    LCD_SetCursor(0, 0);
    LCD_WriteString("RFID TEST MODE");
}

void App_Loop(void) {
    uint8_t CardID[5];
    char strBuf[16];

    // Nếu có thẻ
    if (MFRC522_Check(CardID) == MI_OK) {
        LCD_Clear();
        LCD_SetCursor(0, 0);
        LCD_WriteString("FOUND TAG!");

        // In mã Hex của thẻ
        sprintf(strBuf, "ID: %02X%02X%02X%02X",
                CardID[0], CardID[1], CardID[2], CardID[3]);

        LCD_SetCursor(0, 1);
        LCD_WriteString(strBuf);

        // Nháy đèn báo hiệu
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(200);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);

        HAL_Delay(1000); // Dừng 1 giây rồi quét tiếp

        LCD_Clear();
        LCD_WriteString("Moi quet tiep...");
    }
}
