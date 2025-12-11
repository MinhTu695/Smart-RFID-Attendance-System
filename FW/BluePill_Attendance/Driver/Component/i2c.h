#ifndef MCU_I2C_H_
#define MCU_I2C_H_

#include "main.h"

// Hàm ghi vào vùng nhớ của thiết bị I2C
// DevAddress: Địa chỉ thiết bị (ví dụ 0xA0)
// MemAddress: Địa chỉ ô nhớ bên trong EEPROM
// pData: Con trỏ dữ liệu cần ghi
// Size: Số lượng byte cần ghi
void MCU_I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);

// Hàm đọc từ vùng nhớ
void MCU_I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size);

#endif
