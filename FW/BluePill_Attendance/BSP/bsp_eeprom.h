#ifndef BSP_EEPROM_H_
#define BSP_EEPROM_H_
#include "main.h"
#include "eeprom.h"

void bsp_eeprom_write(uint16_t addr, uint8_t* data, uint16_t len);
void bsp_eeprom_read(uint16_t addr, uint8_t* data, uint16_t len);

#endif
