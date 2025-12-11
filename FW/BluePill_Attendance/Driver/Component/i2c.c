/* File: Driver/Component/i2c.c */

#include "main.h"   // <--- QUAN TRỌNG: Thêm dòng này lên đầu tiên!
#include "i2c.h"    // (Hoặc mcu_i2c.h tùy tên ông đặt)

// Sau khi include main.h thì mới khai báo biến này được
extern I2C_HandleTypeDef hi2c1;

void MCU_I2C_Mem_Write(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size) {
    // Với EEPROM 24C256, địa chỉ bộ nhớ là 16-bit (I2C_MEMADD_SIZE_16BIT)
    HAL_I2C_Mem_Write(&hi2c1, DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pData, Size, 1000);
}

void MCU_I2C_Mem_Read(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size) {
    HAL_I2C_Mem_Read(&hi2c1, DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pData, Size, 1000);
}
