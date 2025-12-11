#include "eeprom.h"
#include "defines.h"
#include "i2c.h" // Nhớ trỏ đúng Component

// Địa chỉ I2C của EEPROM (Đã define trong defines.h là 0xA0)
// Nếu chưa có thì thêm #define EEPROM_ADDR 0xA0 vào defines.h

void EEPROM_Write(uint16_t address, uint8_t *data, uint16_t len) {
    // Ghi từng byte hoặc ghi theo Page (nhưng để an toàn cho newbie, ta ghi từng gói nhỏ)
    // Gọi hàm Wrapper I2C
    MCU_I2C_Mem_Write(EEPROM_ADDR, address, data, len);

    // BẮT BUỘC: EEPROM cần khoảng 5ms để hoàn tất quy trình ghi vật lý
    HAL_Delay(5);
}

void EEPROM_Read(uint16_t address, uint8_t *data, uint16_t len) {
    MCU_I2C_Mem_Read(EEPROM_ADDR, address, data, len);
}

void EEPROM_Format(void) {
    // Xóa 100 byte đầu tiên (ví dụ)
    uint8_t zero = 0;
    for(int i=0; i<100; i++) {
        EEPROM_Write(i, &zero, 1);
    }
}
