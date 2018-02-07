// i2c driver for analyzes of death zone
// input-output unit
// file: timer.h

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"

#define I2C_SPEED   400000

void InitI2C1(void);
void I2C1_single_write(uint8_t HW_address, uint8_t addr, uint8_t data);
uint8_t I2C1_single_read(uint8_t HW_address, uint8_t addr);

void I2C1_StartTransmission(uint8_t transmissionDirection,  uint8_t slaveAddress);
void I2C_WriteData(uint8_t data);
uint8_t I2C_ReadData(void);
void I2C1_StopTransmission(void);
