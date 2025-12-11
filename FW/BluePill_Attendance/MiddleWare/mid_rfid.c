/* File: MiddleWare/mid_rfid_manager.c */
#include "mid_rfid.h"
#include <stdio.h>
#include <string.h>
#include "esp8266.h" // Thư viện chứa hàm ESP_Send_Data_To_Server

// Hàm so sánh
uint8_t MID_RFID_Compare(uint8_t *uid1, uint8_t *uid2) {
    for (int i = 0; i < 4; i++) {
        if (uid1[i] != uid2[i]) {
            return 0; // Khác nhau
        }
    }
    return 1; // Giống nhau
}

// Hàm format chuỗi cho LCD (Có chữ ID:)
void MID_RFID_FormatString(uint8_t *uid, char *strBuffer) {
    sprintf(strBuffer, "ID:%02X%02X%02X%02X",
            uid[0], uid[1], uid[2], uid[3]);
}

// Hàm Copy thẻ
void MID_RFID_Copy(uint8_t *dest, uint8_t *src) {
    memcpy(dest, src, 4);
}

// Hàm Xóa thẻ
void MID_RFID_Clear(uint8_t *uid) {
    memset(uid, 0, 4);
}

// Hàm Gửi dữ liệu qua WiFi
void MID_WiFi_Submit_Attendance(uint8_t *uid) {
    char strUID_Web[20]; // Buffer chuỗi gửi đi

    // Format chỉ lấy số Hex (Ví dụ: "A1B2C3D4") để gửi Web cho gọn
    sprintf(strUID_Web, "%02X%02X%02X%02X",
            uid[0], uid[1], uid[2], uid[3]);

    // Gọi Driver ESP bắn lên PushingBox
    ESP_Send_Data_To_Server(strUID_Web);
}
