/* File: Driver/Device/esp8266.c */
#include "esp8266.h"
#include <stdio.h>
#include <string.h>
#include "stm32f1xx_hal.h"
#include "defines.h" // Chứa WIFI_SSID, WIFI_PASS, SERVER info

// --- CẤU HÌNH UART ---
// Đảm bảo huart2 đúng với chân cắm trên mạch (PA2/PA3)
extern UART_HandleTypeDef huart2;

// 1. HÀM GỬI LỆNH AT
void ESP_Send_AT(char *cmd) {
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, strlen(cmd), 1000);
}

// 2. HÀM KHỞI TẠO WIFI
void ESP_Init(void) {
    char cmd_buffer[100];

    // Reset module
    ESP_Send_AT("AT+RST\r\n");
    HAL_Delay(2000);

    // Chế độ Station
    ESP_Send_AT("AT+CWMODE=1\r\n");
    HAL_Delay(1000);

    // Kết nối WiFi
    sprintf(cmd_buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", WIFI_SSID, WIFI_PASS);
    ESP_Send_AT(cmd_buffer);

    // Đợi kết nối (5s)
    HAL_Delay(5000);
}

// 3. HÀM GỬI DỮ LIỆU PUSHINGBOX
void ESP_Send_Data_To_Server(char *uid_str) {
    char cmd_buffer[128];
    char http_request[256];

    // -- BƯỚC 1: Kết nối TCP --
    sprintf(cmd_buffer, "AT+CIPSTART=\"TCP\",\"%s\",%d\r\n", SERVER_IP, SERVER_PORT);
    ESP_Send_AT(cmd_buffer);
    HAL_Delay(2000);

    // -- BƯỚC 2: Chuẩn bị nội dung GET --
    sprintf(http_request,
            "GET /pushingbox?devid=%s&uid=%s HTTP/1.1\r\n"  // <--- Đã sửa idthe thành uid
            "Host: %s\r\n"
            "Connection: close\r\n\r\n",
            PUSHINGBOX_DEVID, uid_str, SERVER_IP);

    // -- BƯỚC 3: Báo độ dài --
    int len = strlen(http_request);
    sprintf(cmd_buffer, "AT+CIPSEND=%d\r\n", len);
    ESP_Send_AT(cmd_buffer);
    HAL_Delay(500);

    // -- BƯỚC 4: Bắn gói tin --
    ESP_Send_AT(http_request);
}
extern UART_HandleTypeDef huart2;

uint8_t ESP_Check_Alive(void) {
    char rx_buffer[20] = {0}; // Tăng buffer lên chút để chứa đủ chữ OK
    char cmd[] = "AT\r\n";

    // 1. Xóa sạch bộ nhớ đệm UART (để tránh đọc lại rác cũ)
    __HAL_UART_FLUSH_DRREGISTER(&huart2);

    // 2. Gửi lệnh AT
    HAL_UART_Transmit(&huart2, (uint8_t*)cmd, 4, 100);

    // 3. Chờ phản hồi (Đọc tối đa 10 ký tự hoặc chờ 500ms)
    // ESP trả về thường là: "\r\nOK\r\n"
    HAL_UART_Receive(&huart2, (uint8_t*)rx_buffer, 10, 500);

    // 4. KIỂM TRA NỘI DUNG (Quan trọng nhất)
    // Chỉ khi nào trong chuỗi nhận về có chữ "OK" thì mới tính là sống
    if (strstr(rx_buffer, "OK") != NULL) {
        return 1; // Sống thật (Real)
    }

    return 0; // Chết hoặc chỉ là nhiễu (Fake)
}
