// 26.12.2017
// Analyzes od death zone
// input-output unit
// Andrei Komiak

#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "system_stm32f10x.h"

#include "global.h"
#include "can.h"
#include "adc.h"
#include "i2c.h"
#include "fm24w256.h"
#include "s25fl127s.h"
#include "RTC_M41T82.h"
#include "videoswitch.h"
#include "canHandler.h"
#include "timers.h"
#include "flash.h"

#define VERSION_PO_MAJOR    0
#define VERSION_PO_MINOR    4
#define VERSION_PO_MICRO    0

int main()
{
    //InitTestFlashForSensor();
	//EraseNumbersSensors();
    InitSensorNumberFromFlash();
    InitCan1();
    InitADC1();
    InitI2C1();
    initFRAM();
    sFLASH_Init();
    RTC_M41T82_Init();
    InitVideoSwitch();
    InitTimer6();

    while(1)
    {       
       // CanSpamer();
    }
    return 0;
}