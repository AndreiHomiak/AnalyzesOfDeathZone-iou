#include "canHandler.h"

uint8_t CommandProcessing(CanRxMsg *rxMessage)
{  
    uint32_t viewMsg = rxMessage->ExtId & 0xFFFF0000;
    uint8_t DA, SA, rezult = 0xFE;
    DA = (rxMessage->ExtId & 0x0000FF00) >> 8;
    SA =  rxMessage->ExtId & 0x000000FF;
    
    if(DA == CAN_IOU_ADRESS)
    {
        switch(viewMsg)
        {
            case CAN_ID_CMD:
                
                    switch (rxMessage->Data[0])
                    {
                        case CAMERA_SWITCH:
                            ChoiceVideoChannel(rxMessage->Data[1], rxMessage->Data[2]);
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, CAMERA_SWITCH, rezult);
                        break;
                            
                        case SWITCH1_MUTE:
                            VideoSwitch_1_Mute();
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, SWITCH1_MUTE, rezult);
                        break;
                            
                        case SWITCH2_MUTE:
                            VideoSwitch_2_Mute();
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, SWITCH2_MUTE, rezult);
                        break;
                        
                        case SWITCH1_STANDBY:
                            VideoSwitch_1_Standby();
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, SWITCH1_STANDBY, rezult);
                        break;
                            
                        case SWITCH2_STANDBY:
                            VideoSwitch_2_Standby();
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, SWITCH2_STANDBY, rezult);
                        break;
                            
                        case ENABLE_CAMERAS:
                            EnableCameras();
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, ENABLE_CAMERAS, rezult);                        
                        break;
                            
                        case DISABLE_CAMERAS:
                            DisableCameras();
                            rezult = 0x00;
                            CanSendAck(CAN_DCU_ADRESS, DISABLE_CAMERAS, rezult);
                        break;
                    }    
            break;
            
            
            case CAN_ID_GLB:
                    
                    switch(SA)
                    {
                        case CAN_DCU_ADRESS:
                            break;
                            
                        case CAN_SENSOR_ADRESS:
                            DistanceProcessing(&rxMessage->Data[0]);//!!!!!!!!!!!!
                            break;
                    }
            break;
        }
    }
    return 0; 
}

void CanSendMess(uint8_t name_mess)
{
    uint8_t fSend = 1;
    uint16_t buf;
    float buff;
    CanTxMsg TxMessage;
    
    TxMessage.ExtId = CAN_ID_GLB | ((uint16_t)name_mess<<8) | CAN_IOU_ADRESS;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_Id_Extended;
    TxMessage.DLC = 8;
    TxMessage.Data[0] = 0xFF;
    TxMessage.Data[1] = 0xFF;
    TxMessage.Data[2] = 0xFF;
    TxMessage.Data[3] = 0xFF;
    TxMessage.Data[4] = 0xFF;
    TxMessage.Data[5] = 0xFF;
    TxMessage.Data[6] = 0xFF;
    TxMessage.Data[7] = 0xFF;
    
    switch(name_mess)
    {
        case ADC1_VALUE:
                buf = GetValueFromADC1();
                *(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) buf;
            break;
            
        case ADC2_VALUE:
                buf = GetValueFromADC2();
                *(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) buf;
            break;
            
        case ADC1_VALUE_CONV:
                buf = GetValueFromADC1();
                buff = ConvertADCvalueToVoltageFloat(buf);
                buf = (uint16_t) roundf(buff * 1000);
                *(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) buf;
            break;
            
        case ADC2_VALUE_CONV:
                buf = GetValueFromADC2();
                buff = ConvertADCvalueToVoltageFloat(buf);
                buf = (uint16_t) roundf(buff * 1000);
                *(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) buf;
            break;
            
        case VERSION_PO:
                TxMessage.Data[0] = VERSION_PO_MICRO;
                TxMessage.Data[1] = VERSION_PO_MINOR;
                TxMessage.Data[2] = VERSION_PO_MAJOR;
            break;
            
        default:
            fSend = 0;
            break;
    }
    
    if(fSend)
        CAN_Transmit(CAN1, &TxMessage);
}

void CanSendAck(uint16_t unit_adress, uint8_t name_command, uint8_t rezult)
{
    CanTxMsg answerMsg;
    
    answerMsg.StdId = 0x00;
    answerMsg.ExtId = CAN_ID_ACK | ((uint8_t)unit_adress<<8) | CAN_IOU_ADRESS;
    answerMsg.IDE = CAN_Id_Extended;
    answerMsg.RTR = CAN_RTR_DATA;
    answerMsg.DLC = 8;
    answerMsg.Data[0] = name_command;
    answerMsg.Data[1] = rezult;
    answerMsg.Data[2] = 0xFF;
    answerMsg.Data[3] = 0xFF;
    answerMsg.Data[4] = 0xFF;
    answerMsg.Data[5] = 0xFF;
    answerMsg.Data[6] = 0xFF;
    answerMsg.Data[7] = 0xFF;
    
    CAN_Transmit(CAN1, &answerMsg);
}

void CanSpamer(void)
{
    static uint8_t index = 0;
    
    if(flag_can && flag_init_sensors==0)
    {
        flag_can = 0;
        
        switch(index)
        {
            case 0:
                CanSendMess(ADC1_VALUE);
                index++;
                break;
                
            case 1:
                CanSendMess(ADC2_VALUE);
                index++;
                break;
                
            case 2:
                CanSendMess(ADC1_VALUE_CONV);
                index++;
                break;
                
            case 3:
                CanSendMess(ADC2_VALUE_CONV);
                index++;
                break;
                
            case 4:
                CanSendMess(VERSION_PO);
                index = 0;
                break;
            
            default:
                break;
        }
    }
}

void DistanceProcessing(uint8_t *data)
{
    CanTxMsg TxMessage;
    TxMessage.StdId = 0x00;
    TxMessage.ExtId = CAN_ID_GLB | ((uint16_t)FROM_SENSORS<<8) | CAN_IOU_ADRESS;
    TxMessage.IDE = CAN_Id_Extended;				
	TxMessage.RTR = CAN_RTR_DATA;					
	TxMessage.DLC = 8;
    TxMessage.Data[0] = 0xFF;
    TxMessage.Data[1] = 0xFF;
    TxMessage.Data[2] = 0xFF;
    TxMessage.Data[3] = 0xFF;
    TxMessage.Data[4] = 0xFF;
    TxMessage.Data[5] = 0xFF;
    TxMessage.Data[6] = 0xFF;
    TxMessage.Data[7] = 0xFF;
    
    
    switch(data[0])
    {
        case 0x01:
            distance_sens1 = *(uint16_t *)(&data[1]); //Проверить!!!!!!!!!!
            break;
            
        case 0x02:
            distance_sens2 = *(uint16_t *)(&data[1]);
            break;
        
        case 0x03:
            distance_sens3 = *(uint16_t *)(&data[1]);
            break;
            
        case 0x04:
            distance_sens4 = *(uint16_t *)(&data[1]);
            break;
        default:
            break;
    }
    
    flag_danger_sens1 = NumberInDistance(distance_sens1);
    flag_danger_sens2 = NumberInDistance(distance_sens2);
    flag_danger_sens3 = NumberInDistance(distance_sens3);
    flag_danger_sens4 = NumberInDistance(distance_sens4);
    
    if( flag_danger_sens1==0 && flag_danger_sens2==0 && 
        flag_danger_sens3==0 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x00;
    }
    else if(flag_danger_sens1==0 && flag_danger_sens2==0 && 
            flag_danger_sens3==0 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x01;
    }
    else if(flag_danger_sens1==0 && flag_danger_sens2==0 && 
            flag_danger_sens3==1 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x02;
    }  
    else if(flag_danger_sens1==0 && flag_danger_sens2==0 && 
            flag_danger_sens3==1 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x03;
    }
    else if(flag_danger_sens1==0 && flag_danger_sens2==1 && 
            flag_danger_sens3==0 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x04;
    } 
    else if(flag_danger_sens1==0 && flag_danger_sens2==1 && 
            flag_danger_sens3==0 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x05;
    }
    else if(flag_danger_sens1==0 && flag_danger_sens2==1 && 
            flag_danger_sens3==1 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x06;
    }
    else if(flag_danger_sens1==0 && flag_danger_sens2==1 && 
            flag_danger_sens3==1 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x07;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==0 && 
            flag_danger_sens3==0 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x08;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==0 && 
            flag_danger_sens3==0 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x09;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==0 && 
            flag_danger_sens3==1 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x0A;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==0 && 
            flag_danger_sens3==1 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x0B;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==1 && 
            flag_danger_sens3==0 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x0C;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==1 && 
            flag_danger_sens3==0 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x0D;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==1 && 
            flag_danger_sens3==1 && flag_danger_sens4==0)
    {
        TxMessage.Data[0] = 0x0E;
    } 
    else if(flag_danger_sens1==1 && flag_danger_sens2==1 && 
            flag_danger_sens3==1 && flag_danger_sens4==1)
    {
        TxMessage.Data[0] = 0x0F;
    } 
    
    CAN_Transmit(CAN1, &TxMessage);
}
