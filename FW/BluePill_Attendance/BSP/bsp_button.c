#include "bsp_button.h"

void bsp_button_init(void) { } // CubeMX init

uint8_t bsp_button_get_state(uint8_t btn_id) {
    GPIO_PinState state = GPIO_PIN_SET;
    if(btn_id == BTN_MODE_ID) {
        state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0); // PA0
    } else if (btn_id == BTN_RESET_ID) {
        state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1); // PA1
    }

    if(state == GPIO_PIN_RESET) return BUTTON_PRESSED;
    return BUTTON_RELEASED;
}
