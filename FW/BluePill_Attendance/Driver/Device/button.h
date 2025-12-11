
#ifndef GPIO_H_
#define GPIO_H_

#include "main.h"

void MCU_GPIO_Write(GPIO_TypeDef* Port, uint16_t Pin, uint8_t State);
// Phải có dòng dưới này:
uint8_t MCU_GPIO_Read(GPIO_TypeDef* Port, uint16_t Pin);
void MCU_GPIO_Toggle(GPIO_TypeDef* Port, uint16_t Pin);

#endif
