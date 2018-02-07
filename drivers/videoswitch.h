// VideoSwitch driver for analyzes of death zone
// input-output unit
// file: videoswitch.h

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define CTLA1   GPIO_Pin_3
#define CTLB1   GPIO_Pin_2
#define CTLC1   GPIO_Pin_1
#define CTLD1   GPIO_Pin_0

#define CTLA2   GPIO_Pin_8
#define CTLB2   GPIO_Pin_9
#define CTLC2   GPIO_Pin_10
#define CTLD2   GPIO_Pin_11

#define POWER_CAMERA_PIN        GPIO_Pin_4
#define SWPOWER_CAMERA_PIN      GPIO_Pin_0
#define DG_CAMERA_PIN           GPIO_Pin_1

#define CAMERA_NORMAL       0x01
#define CAMERA_NOT_NORMAL   0x02

#define OUT_CAMERA_1    0x01
#define OUT_CAMERA_2    0x02
#define OUT_CAMERA_3    0x03
#define OUT_CAMERA_4    0x04
#define OUT_CAMERA_5    0x05
#define OUT_CAMERA_6    0x06
#define OUT_CAMERA_7    0x07
#define OUT_CAMERA_8    0x08
#define OUT_CAMERA_9    0x09
#define OUT_CAMERA_10   0x10
#define OUT_CAMERA_11   0x11
#define OUT_CAMERA_12   0x12
#define OUT_CAMERA_13   0x13
#define OUT_CAMERA_14   0x14
#define OUT_CAMERA_15   0x15
#define OUT_CAMERA_16   0x16

void InitVideoSwitch(void);
uint8_t ChoiceVideoChannel(uint8_t VideoSwitch_1, uint8_t VideoSwitch_2);
void VideoSwitch_1_Mute(void);
void VideoSwitch_2_Mute(void);
void VideoSwitch_1_Standby(void);
void VideoSwitch_2_Standby(void);
void EnableCameras(void);
void DisableCameras(void);
uint8_t GetStateVideoAdapter(void);
uint8_t CameraDiagnostic(void);
