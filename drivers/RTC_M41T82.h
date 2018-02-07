////////////////////////////////////////////////////////////////////////////////
//
// File: /MyDrivers/RTC_M41T82.h
// Description:
// Author(s): SaverHar as an engineer "SKB WEST"
// Copyright(s):
// Version:
// Creation date: 12-October-2017
//
////////////////////////////////////////////////////////////////////////////////

#ifndef M41T82_h
#define M41T82_h

#include "stm32f10x.h"
#include "stm32f10x_i2c.h"

#define M41T82_ADDR_R	0xD1
#define M41T82_ADDR_W	0xD0

#define REG_MSEC	0x00
#define REG_SEC	        0x01
#define REG_MIN		0x02
#define REG_HOUR	0x03
#define REG_DOW		0x04
#define REG_DATE	0x05
#define REG_MON		0x06
#define REG_YEAR	0x07
#define REG_DIG_CALIBR	0x08
#define REG_WDT	        0x09
#define REG_AL1_HOUR    0x0C
#define REG_FLAGS	0x0f
#define REG_TIMER_VAL	0x10
#define REG_TIMER_CON	0x11
#define REG_AN_CALIBR	0x12
#define REG_SQW 	0x13

#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define TIMER_STOP      0x80
#define TIMER_START     0x7F

#define TIMER_ENABLE    0x80
#define TIMER_DISAABLE  0x7F

#define SQW_RATE_4K	0x00
#define SQW_RATE_64	0x01
#define SQW_RATE_1	0x02
#define SQW_RATE_60s	0x03

#define HT_BIT_SET      0x40
#define HT_BIT_RESET    0xAF

void RTC_M41T82_Init();
uint8_t RTC_M41T82_GetSecond();
uint8_t RTC_M41T82_GetCurrentTime(uint8_t* pBuffer);//, uint32_t readBytes);
uint8_t RTC_M41T82_GetCurrentDate(uint8_t* pBuffer);
uint8_t RTC_M41T82_SetCurrentTime(uint8_t* pBuffer);
uint8_t RTC_M41T82_SetCurrentDate(uint8_t* pBuffer);
uint8_t BCDToDecimal(uint8_t number);
uint8_t DecimalToBCD(uint8_t number);

#endif