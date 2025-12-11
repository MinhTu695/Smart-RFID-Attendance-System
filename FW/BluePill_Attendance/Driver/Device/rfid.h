#ifndef DEV_RFID_H_
#define DEV_RFID_H_

#include "main.h"

// Trạng thái trả về
#define MI_OK       0
#define MI_NOTAGERR 1
#define MI_ERR      2

// Hàm khởi tạo
void MFRC522_Init(void);

// Hàm kiểm tra thẻ (trả về MI_OK nếu có thẻ)
// cardID: Mảng 5 byte để lưu UID của thẻ đọc được
uint8_t MFRC522_Check(uint8_t *cardID);

#endif
