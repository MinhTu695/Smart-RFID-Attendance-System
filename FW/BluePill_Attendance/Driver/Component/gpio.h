/* File: Driver/Component/gpio.h */
#ifndef GPIO_H_
#define GPIO_H_

#include "main.h" // <--- QUAN TRỌNG NHẤT: Phải có dòng này mới hiểu GPIO_TypeDef

// Khai báo hàm
void MCU_GPIO_Write(GPIO_TypeDef* Port, uint16_t Pin, uint8_t State);
uint8_t MCU_GPIO_Read(GPIO_TypeDef* Port, uint16_t Pin);
void MCU_GPIO_Toggle(GPIO_TypeDef* Port, uint16_t Pin);

#endif /* GPIO_H_ */
