////////////////////////////////////////////////////////////////////////////////
//
// File: /MyDrivers/RTC_M41T82.c
// Description:
// Author(s): SaverHar as an engineer "SKB WEST"
// Copyright(s):
// Version:
// Creation date: 12-Oktober-2017
//
////////////////////////////////////////////////////////////////////////////////

#include "stm32f10x_i2c.h"
#include "RTC_M41T82.h"
#include "i2c.h"

void RTC_M41T82_Init()
{
  //Инициализация интерфейса I2C
  InitI2C1();
  //Сброс флага остановки сохранённого времени
  I2C1_single_write(M41T82_ADDR_W, REG_AL1_HOUR, HT_BIT_RESET);
//  I2C_single_write(M41T82_ADDR_W, REG_TIMER_CON, (TIMER_ENABLE | SQW_RATE_1));
//  I2C_single_write(M41T82_ADDR_W, REG_SEC, (second | TIMER_STOP));
//  I2C_single_write(M41T82_ADDR_W, REG_SEC, (second | TIMER_START));
}

uint8_t RTC_M41T82_GetCurrentTime(uint8_t* pBuffer)
{
  uint8_t msec, sec, min, hour;

  //Чтение данных из регистров RTC в фрмате BCD
  msec = I2C1_single_read(M41T82_ADDR_R, REG_MSEC);
  sec = I2C1_single_read(M41T82_ADDR_R, REG_SEC);
  min = I2C1_single_read(M41T82_ADDR_R, REG_MIN);
  hour = I2C1_single_read(M41T82_ADDR_R, REG_HOUR);
      
//  *pBuffer++ = msec;
//  *pBuffer++ = sec;
//  *pBuffer++ = min;
//  *pBuffer++ = hour;
//  *pBuffer++ = dow;
//  *pBuffer++ = date;
//  *pBuffer++ = month;
//  *pBuffer = year;
  
  //Запись данны хв буфер после преобразования в десятичный вид
  *pBuffer++ = BCDToDecimal(msec);
  *pBuffer++ = BCDToDecimal(sec);
  *pBuffer++ = BCDToDecimal(min);
  *pBuffer++ = BCDToDecimal(hour);
  
  return 0;
}

uint8_t RTC_M41T82_GetCurrentDate(uint8_t* pBuffer)
{
  uint8_t dow, date, month, year;

  //Чтение данных из регистров RTC в фрмате BCD
  dow = I2C1_single_read(M41T82_ADDR_R, REG_DOW);
  date = I2C1_single_read(M41T82_ADDR_R, REG_DATE);
  month = I2C1_single_read(M41T82_ADDR_R, REG_MON);
  year = I2C1_single_read(M41T82_ADDR_R, REG_YEAR);
    
//  *pBuffer++ = msec;
//  *pBuffer++ = sec;
//  *pBuffer++ = min;
//  *pBuffer++ = hour;
//  *pBuffer++ = dow;
//  *pBuffer++ = date;
//  *pBuffer++ = month;
//  *pBuffer = year;
  
  //Запись данны хв буфер после преобразования в десятичный вид
  *pBuffer++ = BCDToDecimal(dow);
  *pBuffer++ = BCDToDecimal(date);
  *pBuffer++ = BCDToDecimal(month);
  *pBuffer = BCDToDecimal(year);
  
  return 0;
}

//Не правильно считывает данные по порядку
/*uint8_t RTC_M41T82_GetCurrentTime(uint8_t* pBuffer, uint32_t readBytes)
{
  uint32_t i;
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, M41T82_ADDR_W, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_SendData(I2C1, REG_MSEC);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, M41T82_ADDR_R, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_AcknowledgeConfig(I2C1, DISABLE);
  
  for(i=0; i<readBytes; i++)
  {
//    I2C_GenerateSTART(I2C1, ENABLE);
//    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
//    I2C_Send7bitAddress(I2C1, M41T82_ADDR_R, I2C_Direction_Receiver);
//    while(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED));
    *pBuffer = I2C_ReceiveData(I2C1);
    pBuffer++;
  }

  I2C_AcknowledgeConfig(I2C1, ENABLE);
  I2C_GenerateSTOP(I2C1, ENABLE);
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  return 0;
}*/

uint8_t RTC_M41T82_SetCurrentTime(uint8_t* pBuffer)
{
  uint32_t i;
  
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, M41T82_ADDR_W, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_SendData(I2C1, REG_MSEC);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  for(i=0; i<4; i++)
  {
//    I2C_SendData(I2C1, *pBuffer);
    I2C_SendData(I2C1, DecimalToBCD(*pBuffer));
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    pBuffer++;
  }
  
  I2C_GenerateSTOP(I2C1, ENABLE);
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  return 0;
}

uint8_t RTC_M41T82_SetCurrentDate(uint8_t* pBuffer)
{
  uint32_t i;
  
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  I2C_GenerateSTART(I2C1, ENABLE);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
  I2C_Send7bitAddress(I2C1, M41T82_ADDR_W, I2C_Direction_Transmitter);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  I2C_SendData(I2C1, REG_DOW);
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  for(i=0; i<4; i++)
  {
//    I2C_SendData(I2C1, *pBuffer);
    I2C_SendData(I2C1, DecimalToBCD(*pBuffer));
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    pBuffer++;
  }
  
  I2C_GenerateSTOP(I2C1, ENABLE);
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  return 0;
}


uint8_t BCDToDecimal(uint8_t number)
{
  return ((number & 0xF0) >> 4) * 10 + (number & 0x0F);
}

uint8_t DecimalToBCD(uint8_t number)
{
  return ((number / 16) << 4) | (number % 16);
}