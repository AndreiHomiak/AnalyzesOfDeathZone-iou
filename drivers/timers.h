// Timers configurations for analyzes of death zone
// input-output unit
// file: timer.h

#ifndef __TIMERS_H
#define __TIMERS_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "canHandler.h"
#include "global.h"

void InitTimers(void);

void InitTimer6(void);
void InitTimer7(void);

#endif // __TIMERS_H