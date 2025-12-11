#ifndef DEV_LCD_H_
#define DEV_LCD_H_

#include "main.h"

// Hàm khởi tạo LCD (gọi 1 lần đầu chương trình)
void LCD_Init(void);

// Hàm xóa màn hình
void LCD_Clear(void);

// Hàm đặt con trỏ viết chữ (col: cột 0-15, row: hàng 0-1)
void LCD_SetCursor(uint8_t col, uint8_t row);

// Hàm viết 1 chuỗi ký tự
void LCD_WriteString(char *str);

#endif /* DEV_LCD_H_ */
