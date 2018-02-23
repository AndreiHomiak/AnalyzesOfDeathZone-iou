#include "canHandler.h"

uint8_t CommandProcessing(CanRxMsg *rxMessage)
{  
    uint32_t viewMsg = rxMessage->ExtId & 0xFFFF0000;
    uint8_t DA, SA, IDS, rezult = 0xFE;
    DA = (rxMessage->ExtId & 0x0000FF00) >> 8;
    SA =  rxMessage->ExtId & 0x000000FF;
    IDS = DA;
    uint8_t num_sens, poz;
    
	switch(viewMsg)
	{
		case CAN_ID_CMD:
			
			if(DA == CAN_IOU_ADRESS)
			{
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
						
					case GET_DISTANCE:
						num_sens = rxMessage->Data[1];
						switch(num_sens)
						{
							case 0x01: CanSendMess(DISTANCE_1); break;
							case 0x02: CanSendMess(DISTANCE_2); break;
							case 0x03: CanSendMess(DISTANCE_3); break;
							case 0x04: CanSendMess(DISTANCE_4); break;
							case 0x05: CanSendMess(DISTANCE_5); break;
							case 0x06: CanSendMess(DISTANCE_6); break;
							case 0x07: CanSendMess(DISTANCE_7); break;
							case 0x08: CanSendMess(DISTANCE_8); break;
							default: 
								rezult = 0x01;
								CanSendAck(CAN_DCU_ADRESS, GET_DISTANCE, rezult);
							break;
						}
					break;
				}
			}
		break;
            
            
		case CAN_ID_GLB:
				
				switch(SA)
				{
					case CAN_DCU_ADRESS:
					break;
						
					case CAN_SENSOR_ADRESS:
						poz = ProcessingSensorID(rxMessage->Data);
						if(poz == 0xFF)
						DistanceProcessing(poz, rxMessage->Data);
					break;
				}
		break;       
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
		
		case STATUS_REG:
			TxMessage.Data[0] = status_reg_sensors;
		break;
		
		case DISTANCE_1:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[0];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[0];
		break;
		
		case DISTANCE_2:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[1];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[1];		
		break;
		
		case DISTANCE_3:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[2];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[2];
		break;
		
		case DISTANCE_4:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[3];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[3];
		break;
		
		case DISTANCE_5:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[4];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[4];
		break;
		
		case DISTANCE_6:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[5];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[5];
		break;
		
		case DISTANCE_7:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[6];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[6];
		break;
		
		case DISTANCE_8:
			*(uint16_t *)(&TxMessage.Data[0]) = (uint16_t) distance_from_sensors[7];
			*(uint16_t *)(&TxMessage.Data[2]) = (uint16_t) distance_prev_from_sensors[7];
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

void DistanceProcessing(uint8_t poz, uint8_t *data)
{
	//вытягивание чисел
	uint16_t distance_cur = *(uint16_t *)(&data[2]);
    
    if((poz != 0x00) || (poz != 0xFF))
	{
		if(poz == sensors_numbers[0][1])
		{
			distance_prev_from_sensors[0] = distance_from_sensors[0];
			distance_from_sensors[0] = distance_cur;
			NumberInDistance(distance_from_sensors[0], poz);
		}
		else if(poz == sensors_numbers[1][1])
		{
			distance_prev_from_sensors[1] = distance_from_sensors[1];
			distance_from_sensors[1] = distance_cur;
			NumberInDistance(distance_from_sensors[1], poz);
		}
		else if(poz == sensors_numbers[2][1])
		{
			distance_prev_from_sensors[2] = distance_from_sensors[2];
			distance_from_sensors[2] = distance_cur;
			NumberInDistance(distance_from_sensors[2], poz);
		}
		else if(poz == sensors_numbers[3][1])
		{
			distance_prev_from_sensors[3] = distance_from_sensors[3];
			distance_from_sensors[3] = distance_cur;
			NumberInDistance(distance_from_sensors[3], poz);
		}
		else if(poz == sensors_numbers[4][1])
		{
			distance_prev_from_sensors[4] = distance_from_sensors[4];
			distance_from_sensors[4] = distance_cur;
			NumberInDistance(distance_from_sensors[4], poz);
		}
		else if(poz == sensors_numbers[5][1])
		{
			distance_prev_from_sensors[5] = distance_from_sensors[5];
			distance_from_sensors[5] = distance_cur;
			NumberInDistance(distance_from_sensors[5], poz);
		}
		else if(poz == sensors_numbers[6][1])
		{
			distance_prev_from_sensors[6] = distance_from_sensors[6];
			distance_from_sensors[6] = distance_cur;
			NumberInDistance(distance_from_sensors[6], poz);
		}
		else if(poz == sensors_numbers[7][1])
		{
			distance_prev_from_sensors[7] = distance_from_sensors[7];
			distance_from_sensors[7] = distance_cur;
			NumberInDistance(distance_from_sensors[7], poz);
		}
		CanSendMess(STATUS_REG);
	}
	
}

uint8_t ProcessingSensorID(uint8_t *data)
{
	uint16_t id_sensor = *(uint16_t *)(&data[0]);
	for(int i = 0; i < 8; i++)
	{
		if(id_sensor == sensors_numbers[i][0])
			return sensors_numbers[i][1];
	}
	
	for(int i = 0; i < 8; i++)
	{
		if((sensors_numbers[i][1] == 0xFFFF) || (sensors_numbers[i][1] == 0x0000))
		{
			if(id_sensor != 0xFFFF)
			{
				sensors_numbers[i][0] = id_sensor;
				sensors_numbers[i][1] = i + 1;
				WriteNumberSensorAndPosition();
				return i + 1;
			}
			else
				return 0xFF;
		}
	}
    return 0xFE;
}
