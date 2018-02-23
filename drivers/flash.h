// flash driver for analyzes of death zone
// input-output unit
// file: flash.h

#ifndef __FLASH_H
#define __FLASH_H

#include "stm32f10x.h"
#include "stm32f10x_flash.h"

#include "global.h"

#define ADDRESS 0x08020000

//extern uint16_t sensor_number;

void InitSensorNumberFromFlash();
void WriteNumberSensorAndPosition();
void EraseNumbersSensors();

uint32_t Read_Flash32(uint32_t Data_adr);
uint16_t Read_Flash16(uint32_t Data_adr);
uint8_t Read_Flash8(uint16_t Data_adr);

#endif // __FLASH_H