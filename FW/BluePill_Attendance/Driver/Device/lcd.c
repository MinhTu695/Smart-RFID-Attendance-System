/* File: Driver/Device/lcd.c */
#include "lcd.h"
#include "defines.h" // Đảm bảo ông đã Add Path cho thư mục Common
#include "gpio.h"    // Đảm bảo ông đã Add Path cho thư mục Driver/Component

// --- CÁC HÀM NỘI BỘ (Private) ---

// Hàm gửi 4 bit dữ liệu ra chân (Đã sửa về dùng MCU_GPIO_Write cho đồng bộ)
static void LCD_Send4Bit(uint8_t Data) {
    // Data là giá trị từ 0-15 (4 bit)
    // Lấy bit 0 đẩy ra D4, bit 1 ra D5...
    MCU_GPIO_Write(LCD_D4_PORT, LCD_D4_PIN, (Data >> 0) & 0x01);
    MCU_GPIO_Write(LCD_D5_PORT, LCD_D5_PIN, (Data >> 1) & 0x01);
    MCU_GPIO_Write(LCD_D6_PORT, LCD_D6_PIN, (Data >> 2) & 0x01);
    MCU_GPIO_Write(LCD_D7_PORT, LCD_D7_PIN, (Data >> 3) & 0x01);
}

// Hàm tạo xung Enable (Giữ nguyên delay ông đã chỉnh)
static void LCD_Enable(void) {
    MCU_GPIO_Write(LCD_EN_PORT, LCD_EN_PIN, 1); // Lên cao
    HAL_Delay(2); // Chờ LCD ăn lệnh
    MCU_GPIO_Write(LCD_EN_PORT, LCD_EN_PIN, 0); // Xuống thấp
    HAL_Delay(2); // Chờ xử lý xong
}

// Hàm gửi đầy đủ 1 byte (chia làm 2 lần gửi 4 bit)
static void LCD_Send(uint8_t val, uint8_t type) {
    // 0 = Lệnh, 1 = Dữ liệu
    MCU_GPIO_Write(LCD_RS_PORT, LCD_RS_PIN, type);

    // Gửi 4 bit cao (High Nibble)
    LCD_Send4Bit(val >> 4);
    LCD_Enable();

    // Gửi 4 bit thấp (Low Nibble)
    LCD_Send4Bit(val & 0x0F);
    LCD_Enable();
}

// --- CÁC HÀM PUBLIC ---

void LCD_Init(void) {
    // 1. Chờ nguồn ổn định sau khi bật điện
    HAL_Delay(50);

    // 2. Reset mềm về chế độ 4-bit (QUAN TRỌNG: Gửi thủ công)
    MCU_GPIO_Write(LCD_RS_PORT, LCD_RS_PIN, 0); // Chế độ lệnh
    MCU_GPIO_Write(LCD_EN_PORT, LCD_EN_PIN, 0);

    // Lần 1: Gửi 0x03
    LCD_Send4Bit(0x03); LCD_Enable();
    HAL_Delay(5); // Chờ > 4.1ms

    // Lần 2: Gửi 0x03
    LCD_Send4Bit(0x03); LCD_Enable();
    HAL_Delay(1); // Chờ > 100us

    // Lần 3: Gửi 0x03
    LCD_Send4Bit(0x03); LCD_Enable();
    HAL_Delay(1);

    // Lần 4: Gửi 0x02 (Chuyển sang 4-bit mode)
    LCD_Send4Bit(0x02); LCD_Enable();
    HAL_Delay(1);

    // --- Từ đây về sau LCD đã hiểu 4-bit, dùng hàm LCD_Send bình thường ---

    // Cấu hình: 4-bit, 2 dòng, font 5x8
    LCD_Send(0x28, 0);
    HAL_Delay(1);

    // Tắt hiển thị để cấu hình tiếp
    LCD_Send(0x08, 0);
    HAL_Delay(1);

    // Xóa màn hình
    LCD_Send(0x01, 0);
    HAL_Delay(2); // Lệnh xóa màn hình cần delay lâu

    // Chế độ nhập: Tự động tăng con trỏ
    LCD_Send(0x06, 0);

    // Bật hiển thị, tắt con trỏ nhấp nháy
    LCD_Send(0x0C, 0);
}

void LCD_Clear(void) {
    LCD_Send(0x01, 0);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t col, uint8_t row) {
    uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_Send(address, 0);
}

void LCD_WriteString(char *str) {
    while (*str) {
        LCD_Send(*str++, 1);
    }
}
