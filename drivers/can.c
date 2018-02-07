// can driver for analyzes of death zone
// input-output unit
// file: can.c

#include "can.h"

void InitCan1(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
 /*   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); 
	RCC_APB2PeriphClockCmd(CAN1_Periph, ENABLE); 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);*/
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
    
    //can RX pin
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = CAN1_RX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAN1_PORT, &GPIO_InitStructure);
    
    // can TX pin
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = CAN1_TX;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(CAN1_PORT, &GPIO_InitStructure);
    
    CAN_DeInit(CAN1);
    CAN_InitTypeDef CAN_InitStructure;
 //   CAN_StructInit(&CAN_InitStructure);
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);
    
    // CAN init 
    
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = ENABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
//    CAN_InitStructure.CAN_Mode = CAN_Mode_Silent_LoopBack;
 //   CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1  = CAN_BS1_4tq;
    CAN_InitStructure.CAN_BS2  = CAN_BS2_4tq;
    CAN_InitStructure.CAN_Prescaler = 16;
     while(CAN_Init(CAN1, &CAN_InitStructure) == CAN_InitStatus_Failed); //bylo u Ganchara?
  //  CAN_Init(CAN1, &CAN_InitStructure);
    
    // CAN filter
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    CAN_FilterInitStructure.CAN_FilterNumber =          0;
    CAN_FilterInitStructure.CAN_FilterMode =            CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale =           CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh =          0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow =       0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh =      0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow =       0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment =  0;
    CAN_FilterInitStructure.CAN_FilterActivation =      ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
    
    // NVIC init
    // CAN FIFO0 message pending interrupt enable
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 12; //bylo u Ganchara
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void CAN1_RX0_IRQHandler(void)
{
    CanRxMsg RxMessage;
    
    RxMessage.StdId =   0x00;
    RxMessage.ExtId =   0x00;
    RxMessage.IDE =     0x00;
    RxMessage.RTR =     0x00;
    RxMessage.FMI =     0x00;
    RxMessage.DLC =     0x00;
    RxMessage.Data[0] = 0x00;
    RxMessage.Data[1] = 0x00;
    RxMessage.Data[2] = 0x00;
    RxMessage.Data[3] = 0x00;
    RxMessage.Data[4] = 0x00;
    RxMessage.Data[5] = 0x00;
    RxMessage.Data[6] = 0x00;
    RxMessage.Data[7] = 0x00;
    
    if(CAN_GetITStatus(CAN1, CAN_IT_FMP0) != RESET)
    {
        CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
        CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
    }
    
    CommandProcessing(&RxMessage);
}

void SendMsgToCan1(CanTxMsg *TxMessage)
{
    CAN_Transmit(CAN1, TxMessage);
}

void SendTestToCan1(void)
{
    CanTxMsg TxMessage;
	TxMessage.StdId = 0x00;			
	TxMessage.ExtId = 0x18FF0000;							
	TxMessage.IDE = CAN_Id_Extended;				
	TxMessage.RTR = CAN_RTR_DATA;					
	TxMessage.DLC = 8;								
	TxMessage.Data[0] = 0x00;						
	TxMessage.Data[1] = 0x01;						
	TxMessage.Data[2] = 0x02;		
    TxMessage.Data[3] = 0x03;
    TxMessage.Data[4] = 0x04;
    TxMessage.Data[5] = 0x05;
    TxMessage.Data[6] = 0x06;
    TxMessage.Data[7] = 0x07;

	CAN_Transmit(CAN1, &TxMessage);
}

void SendMsgToCan(uint8_t *buf, uint32_t id)
{
    CanTxMsg TxMessage;
    int i;
	TxMessage.StdId = 0x00;			
	TxMessage.ExtId = id;							
	TxMessage.IDE = CAN_Id_Extended;				
	TxMessage.RTR = CAN_RTR_DATA;					
	TxMessage.DLC = 8;	
    for(i = 0; i < 8; i++)
        TxMessage.Data[i] = buf[i];
    CAN_Transmit(CAN1, &TxMessage);
}
