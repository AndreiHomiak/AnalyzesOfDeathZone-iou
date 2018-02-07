#include "videoswitch.h"

void InitVideoSwitch(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC |
                           RCC_APB2Periph_AFIO, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_StructInit(&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = CTLA1 | CTLB1 | CTLC1 | CTLD1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = CTLA2 | CTLB2 | CTLC2 | CTLD2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //POWER_CAMERA_PIN
    GPIO_InitStructure.GPIO_Pin = POWER_CAMERA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    //SWPOWER_CAMERA_PIN
    GPIO_InitStructure.GPIO_Pin = SWPOWER_CAMERA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    //DG_CAMERA_PIN
    GPIO_InitStructure.GPIO_Pin = DG_CAMERA_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t ChoiceVideoChannel(uint8_t VideoSwitch_1, uint8_t VideoSwitch_2)
{   
    uint8_t ret = 0;

    switch(VideoSwitch_1)
    {
        case OUT_CAMERA_1:
            GPIO_ResetBits(GPIOC, CTLA1);
            GPIO_ResetBits(GPIOC, CTLB1);
            GPIO_ResetBits(GPIOC, CTLC1);
            GPIO_SetBits(GPIOC, CTLD1);
            break;
        case OUT_CAMERA_2:
            GPIO_SetBits(GPIOC, CTLA1);
            GPIO_ResetBits(GPIOC, CTLB1);
            GPIO_ResetBits(GPIOC, CTLC1);
            GPIO_SetBits(GPIOC, CTLD1);
            break;
        case OUT_CAMERA_3:
            GPIO_ResetBits(GPIOC, CTLA1);
            GPIO_SetBits(GPIOC, CTLB1);
            GPIO_ResetBits(GPIOC, CTLC1);
            GPIO_SetBits(GPIOC, CTLD1);
            break;
        case OUT_CAMERA_4:
            GPIO_SetBits(GPIOC, CTLA1);
            GPIO_SetBits(GPIOC, CTLB1);
            GPIO_ResetBits(GPIOC, CTLD1);
            GPIO_SetBits(GPIOC, CTLD1);
            break;
        case OUT_CAMERA_5:
            GPIO_ResetBits(GPIOC, CTLA1);
            GPIO_ResetBits(GPIOC, CTLB1);
            GPIO_SetBits(GPIOC, CTLC1);
            GPIO_SetBits(GPIOC, CTLD1);
            break;
        case OUT_CAMERA_6:
            GPIO_SetBits(GPIOC, CTLA1);
            GPIO_ResetBits(GPIOC, CTLB1);
            GPIO_SetBits(GPIOC, CTLC1);
            GPIO_SetBits(GPIOC, CTLD1);
            break;
        default:
            ret = 1; break;//!!!!!!!!!!!!!!!!!
    }
    
    switch(VideoSwitch_2)
    {
        case OUT_CAMERA_7:
            GPIO_ResetBits(GPIOC, CTLA2);
            GPIO_ResetBits(GPIOC, CTLB2);
            GPIO_ResetBits(GPIOC, CTLC2);
            GPIO_SetBits(GPIOC, CTLD2);
            break;
        case OUT_CAMERA_8:
            GPIO_SetBits(GPIOC, CTLA2);
            GPIO_ResetBits(GPIOC, CTLB2);
            GPIO_ResetBits(GPIOC, CTLC2);
            GPIO_SetBits(GPIOC, CTLD2);
            break;
        case OUT_CAMERA_9:
            GPIO_ResetBits(GPIOC, CTLA2);
            GPIO_SetBits(GPIOC, CTLB2);
            GPIO_ResetBits(GPIOC, CTLC2);
            GPIO_SetBits(GPIOC, CTLD2);
            break;
        case OUT_CAMERA_10:
            GPIO_SetBits(GPIOC, CTLA2);
            GPIO_SetBits(GPIOC, CTLB2);
            GPIO_ResetBits(GPIOC, CTLD2);
            GPIO_SetBits(GPIOC, CTLD2);
            break;
        case OUT_CAMERA_11:
            GPIO_ResetBits(GPIOC, CTLA2);
            GPIO_ResetBits(GPIOC, CTLB2);
            GPIO_SetBits(GPIOC, CTLC2);
            GPIO_SetBits(GPIOC, CTLD2);
            break;
        case OUT_CAMERA_12:
            GPIO_SetBits(GPIOC, CTLA2);
            GPIO_ResetBits(GPIOC, CTLB2);
            GPIO_SetBits(GPIOC, CTLC2);
            GPIO_SetBits(GPIOC, CTLD2);
            break;
        default:
            if(ret == 1)
                ret = 3;
            else
                ret = 2;
            break;
    }
    
    return ret;
}

void VideoSwitch_1_Mute(void)
{
    GPIO_SetBits(GPIOC, CTLB1);
    GPIO_SetBits(GPIOC, CTLC1);
    GPIO_SetBits(GPIOC, CTLD1);
}

void VideoSwitch_2_Mute(void)
{
    GPIO_SetBits(GPIOA, CTLB2);
    GPIO_SetBits(GPIOA, CTLC2);
    GPIO_SetBits(GPIOA, CTLD2);
}

void VideoSwitch_1_Standby(void)
{
    GPIO_ResetBits(GPIOC, CTLD1);
}

void VideoSwitch_2_Standby(void)
{
    GPIO_ResetBits(GPIOA, CTLD2);
}

void EnableCameras(void)
{
    GPIO_SetBits(GPIOC, POWER_CAMERA_PIN);
    GPIO_SetBits(GPIOB, SWPOWER_CAMERA_PIN);
}

void DisableCameras(void)
{
    GPIO_ResetBits(GPIOC, POWER_CAMERA_PIN);
    GPIO_ResetBits(GPIOB, SWPOWER_CAMERA_PIN);
}

uint8_t GetStateVideoAdapter(void)
{
    uint8_t Dg = GPIO_ReadOtputDataBit(GPIOB, DG_CAMERA_PIN);
    return Dg;
}

//check!!!!!!!!!!!!!!!
uint8_t CameraDiagnostic(void)
{
    uint8_t In, Dg, flag = 0;
    In = 0x00;
    GPIO_ResetBits(GPIOB, SWPOWER_CAMERA_PIN);
    GPIO_ResetBits(GPIOC, POWER_CAMERA_PIN);
    Dg = GPIO_ReadOtputDataBit(GPIOB, DG_CAMERA_PIN);
    if(In == Dg)
        flag = 1;
    
    In = 0x01;
    GPIO_SetBits(GPIOC, POWER_CAMERA_PIN);
    GPIO_SetBits(GPIOB, SWPOWER_CAMERA_PIN);
    Dg = GPIO_ReadOtputDataBit(GPIOB, DG_CAMERA_PIN);
    if(In == Dg)
    {
        if(flag == 1)
            return CAMERA_NORMAL;
        else
            return CAMERA_NOT_NORMAL;
    }
    else
        return CAMERA_NOT_NORMAL;
    
}
    