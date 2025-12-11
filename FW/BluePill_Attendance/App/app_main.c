/* File: App/app_main.c */
#include "app_main.h"

// --- 1. INCLUDE THỦ CÔNG TỪNG FILE BSP ---
// (Vì ông không dùng board.h nên phải liệt kê hết ra đây)
#include "bsp_led.h"
#include "bsp_button.h"
#include "bsp_lcd.h"
#include "bsp_rfid.h"
#include "bsp_wifi.h"
#include "bsp_eeprom.h"

// --- 2. INCLUDE CÁC THƯ VIỆN KHÁC ---
#include "mid_rfid.h"   // Middleware xử lý logic thẻ
#include <stdio.h>      // Dùng thư viện chuẩn để xử lý chuỗi (sprintf)

// --- CẤU HÌNH ---
#define MAX_CARDS 5
uint8_t danh_sach_the[MAX_CARDS][5];

typedef enum {
    MODE_CHECK_IN = 0,
    MODE_REGISTER_USER
} SystemMode;

SystemMode currentMode = MODE_CHECK_IN;

// --- HÀM HIỂN THỊ (Dùng BSP LCD) ---
void App_Show_Screen(void) {
    bsp_lcd_clear();
    bsp_lcd_write(0, 0, "MD: CHAM CONG");

    if (currentMode == MODE_CHECK_IN) {
        bsp_lcd_write(1, 0, "Moi quet the...");
    } else {
        bsp_lcd_write(0, 0, "MD: DANG KY THE");
        bsp_lcd_write(1, 0, "Quet the moi...");
    }
}

// --- HÀM KHỞI TẠO (Gọi từng hàm Init của BSP) ---
void App_Init(void) {
    // 1. Khởi tạo từng món phần cứng
    bsp_led_init();     // Khởi tạo đèn/còi
    bsp_button_init();  // Khởi tạo nút nhấn
    bsp_lcd_init();     // Khởi tạo màn hình
    bsp_rfid_init();    // Khởi tạo đầu đọc thẻ

    // 2. Kiểm tra và Khởi tạo WiFi
    bsp_lcd_clear();
    bsp_lcd_write(0, 0, "Check WiFi...");

    if (bsp_wifi_is_connected()) {
        bsp_wifi_init(); // Nếu cắm dây thì mới init
        bsp_lcd_write(1, 0, "WiFi OK!");
    } else {
        bsp_lcd_write(1, 0, "Mode: Offline");
    }
    HAL_Delay(1000);

    // 3. Load dữ liệu từ EEPROM
    bsp_lcd_clear();
    bsp_lcd_write(0, 0, "Loading Data...");
    for(int i = 0; i < MAX_CARDS; i++) {
        bsp_eeprom_read(i * 4, danh_sach_the[i], 4);
    }

    bsp_lcd_write(1, 0, "System Ready!");
    HAL_Delay(1000);
    App_Show_Screen();
}

// --- VÒNG LẶP CHÍNH (Dùng hàm BSP thay cho HAL) ---
void App_Loop(void) {
    uint8_t currentCardID[5];
    char buff[20];

    // 1. XỬ LÝ NÚT MODE
    if (bsp_button_get_state(BTN_MODE_ID) == BUTTON_PRESSED) {
        bsp_beep(1); // Kêu bíp 1 cái
        currentMode = !currentMode;
        App_Show_Screen();
        // Chờ nhả nút
        while(bsp_button_get_state(BTN_MODE_ID) == BUTTON_PRESSED);
    }

    // 2. XỬ LÝ NÚT RESET
    if (bsp_button_get_state(BTN_RESET_ID) == BUTTON_PRESSED) {
        bsp_lcd_clear();
        bsp_lcd_write(0, 0, "DANG XOA ALL...");
        bsp_beep(3); // Kêu bíp 3 cái cảnh báo

        uint8_t zero[4] = {0, 0, 0, 0};
        for(int i = 0; i < MAX_CARDS; i++) {
            bsp_eeprom_write(i * 4, zero, 4);
            for(int j = 0; j < 5; j++) danh_sach_the[i][j] = 0;
        }

        bsp_lcd_write(1, 0, "DA XOA XONG!");
        HAL_Delay(1000);
        currentMode = MODE_REGISTER_USER;
        App_Show_Screen();
    }

    // 3. XỬ LÝ RFID
    if (bsp_rfid_check(currentCardID)) { // Trả về 1 nếu có thẻ
        bsp_beep(1);

        if (currentMode == MODE_REGISTER_USER) {
            // --- LOGIC ĐĂNG KÝ ---
            int slot = -1;

            // Check trùng
            for(int i = 0; i < MAX_CARDS; i++) {
                if(MID_RFID_Compare(currentCardID, danh_sach_the[i])) {
                     bsp_lcd_clear();
                     bsp_lcd_write(0, 0, "THE DA TON TAI!");
                     HAL_Delay(1000);
                     App_Show_Screen();
                     return;
                }
            }
            // Tìm chỗ trống
            for(int i = 0; i < MAX_CARDS; i++) {
                if(danh_sach_the[i][0] == 0) { slot = i; break; }
            }

            if(slot != -1) {
                bsp_eeprom_write(slot * 4, currentCardID, 4);
                MID_RFID_Copy(danh_sach_the[slot], currentCardID);

                bsp_lcd_clear();
                bsp_lcd_write(0, 0, "DA LUU OK!");

                sprintf(buff, "%02X%02X%02X%02X",
                        currentCardID[0], currentCardID[1], currentCardID[2], currentCardID[3]);
                bsp_lcd_write(1, 0, buff);

                HAL_Delay(2000);
                currentMode = MODE_CHECK_IN;
                App_Show_Screen();
            } else {
                bsp_lcd_clear();
                bsp_lcd_write(0, 0, "FULL BO NHO!");
                bsp_beep(3);
                HAL_Delay(2000);
                App_Show_Screen();
            }

        } else {
            // --- LOGIC CHẤM CÔNG ---
            bsp_lcd_clear();
            int hasData = 0;
            for(int i = 0; i < MAX_CARDS; i++) if(danh_sach_the[i][0] != 0) hasData=1;

            if(!hasData) {
                bsp_lcd_write(0, 0, "CHUA CO DATA!");
                bsp_lcd_write(1, 0, "Vui long DK");
                bsp_beep(2);
            } else {
                int found = 0;
                for(int i = 0; i < MAX_CARDS; i++) {
                    if(danh_sach_the[i][0] != 0 && MID_RFID_Compare(currentCardID, danh_sach_the[i])) {
                        found = 1; break;
                    }
                }
                if(found) {
                    bsp_lcd_write(0, 0, "HOP LE (OK)");
                    bsp_beep(2);
                    bsp_lcd_write(1, 0, "Dang gui...");

                    // Gửi qua WiFi
                    bsp_wifi_send(currentCardID);

                    bsp_lcd_write(1, 0, "Gui Xong!");
                } else {
                    bsp_lcd_write(0, 0, "SAI THE!");
                    bsp_lcd_write(1, 0, "Access Denied");
                    bsp_beep(1);
                }
            }
            HAL_Delay(1500);
            App_Show_Screen();
        }
    }
}
