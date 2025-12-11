/* File: BSP/bsp_wifi.c */
#include "bsp_wifi.h"
#include "esp8266.h"   // <--- THÊM DÒNG NÀY (Để nó hiểu ESP_Init, ESP_Check_Alive là gì)
#include "mid_rfid.h"

void bsp_wifi_init(void) {
    ESP_Init();
}

uint8_t bsp_wifi_is_connected(void) {
    // Nó báo lỗi ở đây là do ông chưa dán code vào esp8266.c đấy!
    return ESP_Check_Alive();
}

void bsp_wifi_send(uint8_t* cardID) {
    MID_WiFi_Submit_Attendance(cardID);
}
