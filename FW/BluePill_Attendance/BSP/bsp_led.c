/* File: BSP/bsp_led.c */
#include "bsp_led.h"

void bsp_led_init(void) {
    // CubeMX đã init PC13 rồi
}

void bsp_led_on(void) {
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // LED sáng (Active Low)
}

void bsp_led_off(void) {
    HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);   // LED tắt
}

void bsp_led_toggle(void) {
    HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}

// Hàm này thay thế cho còi: Nháy đèn n lần
void bsp_led_blink(int times) {
    for(int i=0; i<times; i++) {
        bsp_led_on();
        HAL_Delay(100);  // Sáng 100ms
        bsp_led_off();
        HAL_Delay(100);  // Tắt 100ms
    }
}
// Hàm giả lập còi (gọi nháy đèn)
void bsp_beep(int times) {
    bsp_led_blink(times);
}
