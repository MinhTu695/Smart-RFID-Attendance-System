#include "rfid.h"
#include "defines.h"
#include "spi.h"
#include "gpio.h" // Để điều khiển chân CS và RST

// --- CÁC THANH GHI CỦA RC522 (MFRC522 Registers) ---
#define MFRC522_REG_COMMAND     0x01
#define MFRC522_REG_COMM_IEN    0x02
#define MFRC522_REG_DIV_IEN     0x03
#define MFRC522_REG_COMM_IRQ    0x04
#define MFRC522_REG_DIV_IRQ     0x05
#define MFRC522_REG_ERROR       0x06
#define MFRC522_REG_STATUS1     0x07
#define MFRC522_REG_STATUS2     0x08
#define MFRC522_REG_FIFO_DATA   0x09
#define MFRC522_REG_FIFO_LEVEL  0x0A
#define MFRC522_REG_CONTROL     0x0C
#define MFRC522_REG_BIT_FRAMING 0x0D
#define MFRC522_REG_MODE        0x11
#define MFRC522_REG_TX_CONTROL  0x14
#define MFRC522_REG_TX_AUTO     0x15
#define MFRC522_REG_T_MODE      0x2A
#define MFRC522_REG_T_PRESCALER 0x2B
#define MFRC522_REG_T_RELOAD_H  0x2C
#define MFRC522_REG_T_RELOAD_L  0x2D

#define PCD_IDLE              0x00
#define PCD_AUTHENT           0x0E
#define PCD_RECEIVE           0x08
#define PCD_TRANSMIT          0x04
#define PCD_TRANSCEIVE        0x0C
#define PCD_RESETPHASE        0x0F
#define PCD_CALCCRC           0x03

#define PICC_REQIDL           0x26
#define PICC_ANTICOLL         0x93
#define MAX_LEN               16
// --- HÀM CẤP THẤP (Low Level) ---

static void Write_Reg(uint8_t addr, uint8_t val) {
    MCU_GPIO_Write(RFID_CS_PORT, RFID_CS_PIN, 0); // Chọn chip (CS Low)
    MCU_SPI_Transfer((addr << 1) & 0x7E); // Gửi địa chỉ
    MCU_SPI_Transfer(val);                // Gửi dữ liệu
    MCU_GPIO_Write(RFID_CS_PORT, RFID_CS_PIN, 1); // Bỏ chọn (CS High)
}

static uint8_t Read_Reg(uint8_t addr) {
    uint8_t val;
    MCU_GPIO_Write(RFID_CS_PORT, RFID_CS_PIN, 0);
    MCU_SPI_Transfer(((addr << 1) & 0x7E) | 0x80); // Bit đọc
    val = MCU_SPI_Transfer(0x00);
    MCU_GPIO_Write(RFID_CS_PORT, RFID_CS_PIN, 1);
    return val;
}

static void SetBitMask(uint8_t reg, uint8_t mask) {
    Write_Reg(reg, Read_Reg(reg) | mask);
}

static void ClearBitMask(uint8_t reg, uint8_t mask) {
    Write_Reg(reg, Read_Reg(reg) & (~mask));
}

static void AntennaOn(void) {
    uint8_t temp = Read_Reg(MFRC522_REG_TX_CONTROL);
    if (!(temp & 0x03)) SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}

static void MFRC522_Reset(void) {
    Write_Reg(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}

// Hàm giao tiếp chính với thẻ
static uint8_t MFRC522_ToCard(uint8_t command, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint16_t *backLen) {
    uint8_t status = MI_ERR;
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t lastBits;
    uint8_t n;
    uint16_t i;

    switch (command) {
        case PCD_AUTHENT:    irqEn = 0x12; waitIRq = 0x10; break;
        case PCD_TRANSCEIVE: irqEn = 0x77; waitIRq = 0x30; break;
        default: break;
    }

    Write_Reg(MFRC522_REG_COMM_IEN, irqEn | 0x80);
    ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
    SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);
    Write_Reg(MFRC522_REG_COMMAND, PCD_IDLE);

    for (i = 0; i < sendLen; i++) Write_Reg(MFRC522_REG_FIFO_DATA, sendData[i]);

    Write_Reg(MFRC522_REG_COMMAND, command);
    if (command == PCD_TRANSCEIVE) SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);

    i = 2000;
    do {
        n = Read_Reg(MFRC522_REG_COMM_IRQ);
        i--;
    } while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

    ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);

    if (i != 0) {
        if (!(Read_Reg(MFRC522_REG_ERROR) & 0x1B)) {
            status = MI_OK;
            if (n & irqEn & 0x01) status = MI_NOTAGERR;
            if (command == PCD_TRANSCEIVE) {
                n = Read_Reg(MFRC522_REG_FIFO_LEVEL);
                lastBits = Read_Reg(MFRC522_REG_CONTROL) & 0x07;
                if (lastBits) *backLen = (n - 1) * 8 + lastBits;
                else *backLen = n * 8;
                if (n == 0) n = 1;
                if (n > 16) n = 16;
                for (i = 0; i < n; i++) backData[i] = Read_Reg(MFRC522_REG_FIFO_DATA);
            }
        } else status = MI_ERR;
    }
    return status;
}

static uint8_t MFRC522_Request(uint8_t reqMode, uint8_t *TagType) {
    uint8_t status;
    uint16_t backBits;
    Write_Reg(MFRC522_REG_BIT_FRAMING, 0x07);
    TagType[0] = reqMode;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
    if ((status != MI_OK) || (backBits != 0x10)) status = MI_ERR;
    return status;
}

static uint8_t MFRC522_Anticoll(uint8_t *serNum) {
    uint8_t status;
    uint8_t i;
    uint8_t serNumCheck = 0;
    uint16_t unLen;

    Write_Reg(MFRC522_REG_BIT_FRAMING, 0x00);
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK) {
        for (i = 0; i < 4; i++) serNumCheck ^= serNum[i];
        if (serNumCheck != serNum[4]) status = MI_ERR;
    }
    return status;
}

// --- HÀM PUBLIC ---

void MFRC522_Init(void) {
    // 1. Reset cứng module
    MCU_GPIO_Write(RFID_RST_PORT, RFID_RST_PIN, 1);
    HAL_Delay(10);
    MCU_GPIO_Write(RFID_RST_PORT, RFID_RST_PIN, 0);
    HAL_Delay(10);
    MCU_GPIO_Write(RFID_RST_PORT, RFID_RST_PIN, 1);
    HAL_Delay(10);

    // 2. Khởi tạo chip
    MFRC522_Reset();
    Write_Reg(MFRC522_REG_T_MODE, 0x8D);
    Write_Reg(MFRC522_REG_T_PRESCALER, 0x3E);
    Write_Reg(MFRC522_REG_T_RELOAD_L, 30);
    Write_Reg(MFRC522_REG_T_RELOAD_H, 0);
    Write_Reg(MFRC522_REG_TX_AUTO, 0x40);
    Write_Reg(MFRC522_REG_MODE, 0x3D);
    AntennaOn();
}

uint8_t MFRC522_Check(uint8_t *cardID) {
    uint8_t status;
    uint8_t str[MAX_LEN]; // MAX_LEN định nghĩa mặc định trong HAL thường là 16

    // 1. Tìm thẻ (Request)
    status = MFRC522_Request(PICC_REQIDL, str);
    if (status != MI_OK) return MI_ERR;

    // 2. Chống va chạm và lấy UID (Anticoll)
    status = MFRC522_Anticoll(cardID);
    if (status == MI_OK) return MI_OK;

    return MI_ERR;
}
