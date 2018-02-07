// ADC driver for analyzes of death zone
// input-output unit
// file: adc.h

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_rcc.h"

#include <math.h>

#define PIN1    GPIO_Pin_0
#define PIN2    GPIO_Pin_1

void InitADC1(void);
float ConvertADCvalueToVoltageFloat(uint16_t ADC_value);
uint16_t GetValueFromADC1(void);
uint16_t GetValueFromADC2(void);
