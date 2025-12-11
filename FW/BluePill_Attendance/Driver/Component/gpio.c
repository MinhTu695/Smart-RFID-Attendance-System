/* File: Driver/Component/gpio.c */
#include "main.h"
#include "gpio.h"

// Hàm Ghi
void MCU_GPIO_Write(GPIO_TypeDef* Port, uint16_t Pin, uint8_t State) {
    if (State == 0) HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_RESET);
    else            HAL_GPIO_WritePin(Port, Pin, GPIO_PIN_SET);
}

// Hàm Đọc
uint8_t MCU_GPIO_Read(GPIO_TypeDef* Port, uint16_t Pin) {
    return (uint8_t)HAL_GPIO_ReadPin(Port, Pin);
}

// Hàm Đảo
void MCU_GPIO_Toggle(GPIO_TypeDef* Port, uint16_t Pin) {
    HAL_GPIO_TogglePin(Port, Pin);
}
