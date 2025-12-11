#ifndef DEV_EEPROM_H_
#define DEV_EEPROM_H_

#include "main.h"

// Hàm ghi 1 mảng dữ liệu vào EEPROM
// address: Vị trí bắt đầu ghi (0 - 32000)
void EEPROM_Write(uint16_t address, uint8_t *data, uint16_t len);

// Hàm đọc dữ liệu từ EEPROM
void EEPROM_Read(uint16_t address, uint8_t *data, uint16_t len);

// Hàm xóa trắng EEPROM (nếu cần reset)
void EEPROM_Format(void);

#endif
