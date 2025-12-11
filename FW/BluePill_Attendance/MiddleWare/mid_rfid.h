#ifndef MID_RFID_MANAGER_H_
#define MID_RFID_MANAGER_H_

#include <stdint.h>

// Hàm so sánh 2 UID (Logic thuần túy, không đụng phần cứng)
// Trả về 1 nếu trùng, 0 nếu khác
uint8_t MID_RFID_Compare(uint8_t *uid1, uint8_t *uid2);

// Hàm biến đổi mảng UID thành chuỗi String để in LCD hoặc gửi WiFi
// Input: uid (mảng số), Output: strBuffer (chuỗi ký tự)
void MID_RFID_FormatString(uint8_t *uid, char *strBuffer);

// [MỚI] Copy nội dung thẻ nguồn (src) sang thẻ đích (dest)
void MID_RFID_Copy(uint8_t *dest, uint8_t *src);

// [MỚI] Xóa trắng dữ liệu thẻ (về 0)
void MID_RFID_Clear(uint8_t *uid);
// Thêm dòng này vào cuối file (trước #endif)
void MID_WiFi_Submit_Attendance(uint8_t *uid);
#endif
