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

#define VERSION_PO_MAJOR    0
#define VERSION_PO_MINOR    4
#define VERSION_PO_MICRO    0

int main()
{
    InitCan1();
    InitADC1();
    InitI2C1();
    initFRAM();
    sFLASH_Init();
    RTC_M41T82_Init();
    InitVideoSwitch();
    InitTimer6();
    
    uint8_t data[] = {1, 200, 0};
    
    while(1)
    {
 //       CanSendMess(VERSION_PO);
        
        CanRxMsg msg;
        msg.ExtId = 0x0CEA9091;
        msg.Data[0] = 0;
        msg.Data[1] = 2;
        msg.Data[2] = 0xFF;
        msg.Data[3] = 0xFF;
        msg.Data[4] = 0xFF;
        msg.Data[5] = 0xFF;
        msg.Data[6] = 0xFF;
        msg.Data[7] = 0xFF;
 //       CommandProcessing(&msg);
        
        //DistanceProcessing(&data[0]);
        
        CanSpamer();
        
    }
  return 0;
}