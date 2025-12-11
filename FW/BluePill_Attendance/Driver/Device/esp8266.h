#ifndef DEV_ESP8266_H_
#define DEV_ESP8266_H_

#include "main.h"

void ESP_Init(void);
void ESP_SendCommand(char *cmd);
void ESP_Send_Data_To_Server(char *cardID);
uint8_t ESP_Check_Alive(void);
#endif
