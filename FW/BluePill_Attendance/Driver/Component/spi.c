#include "spi.h"

// Lấy biến hspi1 từ main.c sang (do CubeMX tự tạo)
extern SPI_HandleTypeDef hspi1;

uint8_t MCU_SPI_Transfer(uint8_t data) {
    uint8_t rx_data = 0;
    // Gửi data đi và nhận rx_data về, chờ tối đa 100ms
    HAL_SPI_TransmitReceive(&hspi1, &data, &rx_data, 1, 100);
    return rx_data;
}
