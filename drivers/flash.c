// flash driver for analyzes of death zone
// input-output unit
// file: flash.c

#include "flash.h"

//uint16_t sensor_number = 0;

void InitSensorNumberFromFlash()
{
	sensors_numbers[0][0] = Read_Flash16(ADDRESS + 2*0);
	sensors_numbers[1][0] = Read_Flash16(ADDRESS + 2*1);
	sensors_numbers[2][0] = Read_Flash16(ADDRESS + 2*2);
	sensors_numbers[3][0] = Read_Flash16(ADDRESS + 2*3);
	sensors_numbers[4][0] = Read_Flash16(ADDRESS + 2*4);
	sensors_numbers[5][0] = Read_Flash16(ADDRESS + 2*5);
	sensors_numbers[6][0] = Read_Flash16(ADDRESS + 2*6);
	sensors_numbers[7][0] = Read_Flash16(ADDRESS + 2*7);
	sensors_numbers[0][1] = Read_Flash16(ADDRESS + 2*8);
	sensors_numbers[1][1] = Read_Flash16(ADDRESS + 2*9);
	sensors_numbers[2][1] = Read_Flash16(ADDRESS + 2*10);
	sensors_numbers[3][1] = Read_Flash16(ADDRESS + 2*11);
	sensors_numbers[4][1] = Read_Flash16(ADDRESS + 2*12);
	sensors_numbers[5][1] = Read_Flash16(ADDRESS + 2*13);
	sensors_numbers[6][1] = Read_Flash16(ADDRESS + 2*14);
	sensors_numbers[7][1] = Read_Flash16(ADDRESS + 2*15);
}

void WriteNumberSensorAndPosition()
{
    FLASH_Unlock();

	FLASH_ErasePage(ADDRESS);
	FLASH_ProgramHalfWord(ADDRESS + 2*0, sensors_numbers[0][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*1, sensors_numbers[1][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*2, sensors_numbers[2][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*3, sensors_numbers[3][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*4, sensors_numbers[4][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*5, sensors_numbers[5][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*6, sensors_numbers[6][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*7, sensors_numbers[7][0]);
	FLASH_ProgramHalfWord(ADDRESS + 2*8, sensors_numbers[0][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*9, sensors_numbers[1][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*10, sensors_numbers[2][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*11, sensors_numbers[3][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*12, sensors_numbers[4][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*13, sensors_numbers[5][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*14, sensors_numbers[6][1]);
	FLASH_ProgramHalfWord(ADDRESS + 2*15, sensors_numbers[7][1]);
	
	FLASH_Lock();
}

void EraseNumbersSensors()
{
	FLASH_Unlock();

	FLASH_ErasePage(ADDRESS);
	FLASH_Lock();
}

uint32_t Read_Flash32(uint32_t Data_adr)
{
	return *(uint32_t *) Data_adr;
}

uint16_t Read_Flash16(uint32_t Data_adr)
{
	return *(uint16_t *) Data_adr;
}

uint8_t Read_Flash8(uint16_t Data_adr)
{
	return *(uint8_t *) Data_adr;
}