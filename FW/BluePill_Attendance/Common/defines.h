/* File: Common/defines.h */
#ifndef COMMON_DEFINES_H_
#define COMMON_DEFINES_H_

#include "main.h"

// =============================================================
// 1. PIN MAPPING CHO LCD (Giao tiếp 4-bit)
// =============================================================
#define LCD_RS_PORT     GPIOB
#define LCD_RS_PIN      GPIO_PIN_1

#define LCD_EN_PORT     GPIOB
#define LCD_EN_PIN      GPIO_PIN_10

#define LCD_D4_PORT     GPIOB
#define LCD_D4_PIN      GPIO_PIN_12

#define LCD_D5_PORT     GPIOB
#define LCD_D5_PIN      GPIO_PIN_13

#define LCD_D6_PORT     GPIOB
#define LCD_D6_PIN      GPIO_PIN_14

#define LCD_D7_PORT     GPIOB
#define LCD_D7_PIN      GPIO_PIN_15

// =============================================================
// 2. PIN MAPPING CHO RFID RC522 (SPI1)
// =============================================================
#define RFID_CS_PORT    GPIOA
#define RFID_CS_PIN     GPIO_PIN_4

#define RFID_RST_PORT   GPIOB
#define RFID_RST_PIN    GPIO_PIN_0

// =============================================================
// 3. PIN MAPPING CHO NÚT NHẤN (Active LOW)
// =============================================================
#define BTN_MODE_PORT   GPIOA
#define BTN_MODE_PIN    GPIO_PIN_0

#define BTN_RESET_PORT  GPIOA
#define BTN_RESET_PIN   GPIO_PIN_1

// =============================================================
// 4. CẤU HÌNH EEPROM
// =============================================================
#define EEPROM_ADDR     0xA0

// =============================================================
// 5. CẤU HÌNH WIFI & SERVER (ESP8266) --> THÊM MỚI Ở ĐÂY
// =============================================================
// Thay đổi thông tin mạng nhà ông tại đây
#define WIFI_SSID       "Nha Tro 174"
#define WIFI_PASS       "12356789"

// Cấu hình Server (Test)
#define SERVER_IP       "api.pushingbox.com"
#define SERVER_PORT     80
// MÃ DEVICE ID (Lấy từ trang PushingBox)
// Ví dụ: v0123456789ABCDE (Thay cái mã thật của ông vào đây)
#define PUSHINGBOX_DEVID  "v4F51F3506D86010"
#endif /* COMMON_DEFINES_H_ */
