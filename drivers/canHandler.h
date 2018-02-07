// can handler for analyzes of death zone
// input-output unit
// file: canHandler.h

#include "stm32f10x_can.h"
#include "stm32f10x.h"

#include "can.h"
#include "adc.h"
#include "videoswitch.h"
#include "global.h"

#define VERSION_PO_MAJOR    0
#define VERSION_PO_MINOR    4
#define VERSION_PO_MICRO    0

#define CAN_ID_GLB  0x18FF0000
#define CAN_ID_CMD  0x0CEA0000
#define CAN_ID_ACK  0x10E80000
#define CAN_ID_REQ  0x18EA0000

#define CAN_IOU_ADRESS      0x90 //input-output unit
#define CAN_DCU_ADRESS      0x91 //display and control unit
#define CAN_SENSOR_ADRESS   0x92 //sensor

#define ADC1_VALUE          0x01
#define ADC2_VALUE          0x02
#define ADC1_VALUE_CONV     0x03
#define ADC2_VALUE_CONV     0x04
#define VERSION_PO          0x05
#define FROM_SENSORS        0x06


//commands
#define CAMERA_SWITCH       0x01
#define SWITCH1_MUTE        0x02
#define SWITCH2_MUTE        0x03
#define SWITCH1_STANDBY     0x04
#define SWITCH2_STANDBY     0x05
#define ENABLE_CAMERAS      0x06
#define DISABLE_CAMERAS     0x07
#define GET_VERSION_PO		0x08
#define GET_ADC1_VALUE		0x09
#define GET_ADC2_VALUE		0x10
#define GET_ADC1_CONV		0x11
#define GET_ADC2_CONV		0x12

uint8_t CommandProcessing(CanRxMsg *rxMessage);
void CanSendMess(uint8_t name_mess);
void CanSendAck(uint16_t unit_adress, uint8_t name_command, uint8_t rezult);
void CanSpamer(void);
void DistanceProcessing(uint8_t *data);
