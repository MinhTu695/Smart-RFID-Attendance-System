/* Copy vào App/app_main.c */
#include "app_main.h"
#include "button.h"
#include "defines.h"
#include "gpio.h" // Để dùng hàm Toggle

void App_Init(void) {
    // Không cần Init gì đặc biệt ngoài GPIO (đã làm trong CubeMX)
}

void App_Loop(void) {
    // Test nút PA0
    if (Button_IsPressed(BTN_MODE_PORT, BTN_MODE_PIN)) {
        // Nếu nhấn nút -> Đèn PC13 sáng/tắt
        MCU_GPIO_Toggle(GPIOC, GPIO_PIN_13);

        // Chống lặp một chút để dễ nhìn
        HAL_Delay(200);
    }
}
