#include "global.h"

uint8_t flag_can = 0;
uint8_t flag_danger_sens1 = 0;
uint8_t flag_danger_sens2 = 0;
uint8_t flag_danger_sens3 = 0;
uint8_t flag_danger_sens4 = 0;
uint8_t flag_init_sensors = 0;

uint16_t distance_sens1 = 10000; //дециметры
uint16_t distance_sens2 = 10000;
uint16_t distance_sens3 = 10000;
uint16_t distance_sens4 = 10000;
uint16_t distance_max = 350; //дециметры
uint16_t distance_min = 1;

uint8_t NumberInDistance(uint16_t number)
{
    if( (number <= distance_max) && (number >= distance_min))
        return 1;
    else
        return 0;
}