#ifndef BSP_BUTTON_H_
#define BSP_BUTTON_H_
#include "main.h"

#define BTN_MODE_ID   0
#define BTN_RESET_ID  1

#define BUTTON_PRESSED  1
#define BUTTON_RELEASED 0

void bsp_button_init(void);
uint8_t bsp_button_get_state(uint8_t btn_id);

#endif
