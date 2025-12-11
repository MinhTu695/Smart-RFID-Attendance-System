/* File: BSP/bsp_rfid.h */
#ifndef BSP_RFID_H_
#define BSP_RFID_H_
#include <stdint.h>  // Nhớ cái này để không lỗi uint8_t
#include "main.h"

// THÊM 2 DÒNG NÀY VÀO:
void bsp_rfid_init(void);
uint8_t bsp_rfid_check(uint8_t* cardID);

#endif
