#include "bsp_rfid.h"
#include "rfid.h"
#include "mid_rfid.h"
void bsp_rfid_init(void) {
    MFRC522_Init();
}
uint8_t bsp_rfid_check(uint8_t* cardID) {
    if(MFRC522_Check(cardID) == MI_OK) return 1;
    return 0;
}
