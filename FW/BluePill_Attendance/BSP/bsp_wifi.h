#ifndef BSP_WIFI_H_
#define BSP_WIFI_H_
#include "main.h"
#include "esp8266.h"

void bsp_wifi_init(void);
uint8_t bsp_wifi_is_connected(void); // Hàm check kết nối
void bsp_wifi_send(uint8_t* cardID);

#endif
