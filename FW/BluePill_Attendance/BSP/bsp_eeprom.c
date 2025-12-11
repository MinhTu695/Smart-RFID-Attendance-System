#include "bsp_eeprom.h"

void bsp_eeprom_write(uint16_t addr, uint8_t* data, uint16_t len) {
    EEPROM_Write(addr, data, len);
}
void bsp_eeprom_read(uint16_t addr, uint8_t* data, uint16_t len) {
    EEPROM_Read(addr, data, len);
}
