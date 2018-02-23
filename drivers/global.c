#include "global.h"

uint8_t flag_can = 0;
uint8_t status_reg_sensors = 0x00;
uint16_t distance_max = 350; //сантиметры
uint16_t distance_min = 1;
uint16_t sensors_numbers[8][2];
uint16_t distance_from_sensors[8];
uint16_t distance_prev_from_sensors[8];

void NumberInDistance(uint16_t number, uint8_t poz)
{
    if((number <= distance_max) && (number >= distance_min))
    {
		status_reg_sensors |= (1<<poz - 1);
	}
    else
        status_reg_sensors &=~(1<<poz - 1);
}

void InitNumbersSensorsDefault()
{
	sensors_numbers[0][0] = 0x00;
	sensors_numbers[1][0] = 0x00;
	sensors_numbers[2][0] = 0x00;
	sensors_numbers[3][0] = 0x00;
	sensors_numbers[4][0] = 0x00;
	sensors_numbers[5][0] = 0x00;
	sensors_numbers[6][0] = 0x00;
	sensors_numbers[7][0] = 0x00;
	sensors_numbers[0][1] = 0x00;
	sensors_numbers[1][1] = 0x00;
	sensors_numbers[2][1] = 0x00;
	sensors_numbers[3][1] = 0x00;
	sensors_numbers[4][1] = 0x00;
	sensors_numbers[5][1] = 0x00;
	sensors_numbers[6][1] = 0x00;
	sensors_numbers[7][1] = 0x00;
}

uint8_t setbit(uint8_t src, uint8_t index, uint8_t val)
{
	if(val == 1)
		src |= (1<<index);
	else
		src &=~(1<<index);
	return src;
}

uint8_t getbit(uint8_t src, uint8_t index)
{
	return src&=(1<<index);
}