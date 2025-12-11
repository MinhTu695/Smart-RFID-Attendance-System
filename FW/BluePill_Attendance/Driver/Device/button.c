/* File: Driver/Device/button.c */
#include "button.h"
#include "gpio.h" // Gọi component GPIO để đọc chân

// Hàm kiểm tra nút nhấn (Có chống rung)
uint8_t Button_IsPressed(GPIO_TypeDef* Port, uint16_t Pin) {
    // 1. Kiểm tra lần đầu (Nút nhấn tích cực mức thấp 0)
    if (MCU_GPIO_Read(Port, Pin) == 0) {
        // 2. Chờ 20ms để chống rung (Debounce)
        HAL_Delay(20);

        // 3. Kiểm tra lại lần nữa cho chắc
        if (MCU_GPIO_Read(Port, Pin) == 0) {
            // 4. Chờ người dùng thả tay ra (tránh bị lặp lệnh liên tục)
            while(MCU_GPIO_Read(Port, Pin) == 0);

            return 1; // Xác nhận ĐÃ NHẤN
        }
    }
    return 0; // Chưa nhấn
}
