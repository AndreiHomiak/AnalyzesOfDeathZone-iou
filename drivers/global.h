// Global variables for analyzes of death zone
// input-output unit
// file: global.h

#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "system_stm32f10x.h"

extern uint8_t flag_can;                //флаг can-шины
extern uint8_t flag_danger_sens1;      //флаг опасности сенсора 1
extern uint8_t flag_danger_sens2;
extern uint8_t flag_danger_sens3;
extern uint8_t flag_danger_sens4;
extern uint8_t flag_init_sensors;   //флаг ининциализации сенсоров

extern uint16_t distance_sens1;     //расстояние с датчика 1
extern uint16_t distance_sens2;     //расстояние с датчика 2
extern uint16_t distance_sens3;     //расстояние с датчика 3
extern uint16_t distance_sens4;     //расстояние с датчика 4
extern uint16_t distance_max;       //максимальное расстояние до опасности
extern uint16_t distance_min;       //минимальное расстояние до опасности

uint8_t NumberInDistance(uint16_t number);

#endif //__GLOBAL_H