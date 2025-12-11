#ifndef BSP_LED_H_
#define BSP_LED_H_
#include "main.h"

// Định nghĩa phần cứng (LED PC13)
#define LED_PIN  GPIO_PIN_13
#define LED_PORT GPIOC

void bsp_led_init(void);
void bsp_led_on(void);
void bsp_led_off(void);
void bsp_led_toggle(void);
void bsp_led_blink(int times); // Hàm kêu bíp/chớp đèn
void bsp_beep(int times);
#endif
