// Global variables for analyzes of death zone
// input-output unit
// file: global.h

#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "system_stm32f10x.h"

extern uint8_t flag_can;                //флаг can-шины
extern uint8_t flag_init_sensors;   	//флаг ининциализации сенсоров
extern uint8_t status_reg_sensors;		//статусный регистр сенсоров (1 - опасноть, 0 - свободно)

extern uint16_t distance_max;       	//максимальное расстояние до опасности
extern uint16_t distance_min;       	//минимальное расстояние до опасности

extern uint16_t sensors_numbers[8][2];			//массив сооответствия id сенсоров и положения
extern uint16_t distance_from_sensors[8];		//дистанция с датчиков
extern uint16_t distance_prev_from_sensors[8];	//дистанция с датчиков на предыдущем измерении

void NumberInDistance(uint16_t number, uint8_t poz);
void InitNumbersSensorsDefault();
uint8_t setbit(uint8_t src, uint8_t index, uint8_t val);
uint8_t getbit(uint8_t src, uint8_t indec);

#endif //__GLOBAL_H