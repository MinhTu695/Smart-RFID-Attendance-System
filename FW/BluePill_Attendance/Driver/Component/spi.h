#ifndef MCU_SPI_H_
#define MCU_SPI_H_

#include "main.h"

// Hàm gửi 1 byte và nhận về 1 byte (Full Duplex)
uint8_t MCU_SPI_Transfer(uint8_t data);

#endif
