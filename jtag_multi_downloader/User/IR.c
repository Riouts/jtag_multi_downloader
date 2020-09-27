/** $Id$ $DateTime$ 
*  @file IR.c 
*  @brief This file implements all IPCs in whole system. 
*  @version 0.0.1 
*  @since 0.0.1 
*  @author tianzhizhong<tzz@bstar.com.cn> 
*  @date 2007-05-18    Created it 
*  @author tianzhizhong<tzz@bstar.com.cn> 
*  @date 2007-05-16    do some modifications 
*  @author luoyuanhao<luoyh@bstar.com.cn> 
*  @date 2009-05-16    modify for dvx 
*/
/******************************************************************************
*@note    Copyright 2007, BeiJing Bluestar Corporation, Limited
                     ALL RIGHTS RESERVED 
Permission is hereby granted to licensees of BeiJing Bluestar, Inc. products 
to use or abstract this computer program for the sole purpose of implementing 
a product based on BeiJing Bluestar, Inc. products. No other rights to 
reproduce, use, or disseminate this computer program,whether in part or  in 
whole, are granted. BeiJing Bluestar, Inc. makes no representation or 
warranties with respect to the performance of this computer program, and 
specifically disclaims any responsibility for any damages, special or consequential, 
connected with the use of this program. 
For details, see http://www.bstar.com.cn/
******************************************************************************/
#include "main.h"

typedef struct
{
    uint8_t IR_key;
    uint8_t IR_SB_FLAG:1;
    uint8_t IR_keyup:1;
    uint8_t NewIRcode:1;     /* ָʾ����������32λ��󣬾������µ�ң����*/
    uint8_t bit_off_power:1;
    uint8_t DataRight:1;
    uint8_t IR_power_off:1;
    uint8_t IR_FLAG:1;
    uint8_t IR_keydown_flag:1;

    uint8_t IR_YES:1;
    uint8_t FlagIrSendData:1;
    uint8_t unuse:6;

    uint16_t IRkey_temp;
    uint8_t Power_off_time;
    uint8_t IRCODE;
    uint8_t RIRCODE;
    uint8_t timeH;
    uint8_t timeL;                       /* ����TH1 TL��ֵ */

    uint16_t IRtime;
    uint16_t time_us;                    /* �����½���֮���ʱ�� */
    uint16_t dm;                         /* ,i,j,k; */
    uint8_t cn;

    uint16_t customcode;                 /* ��8�û��� */
    uint8_t  Hcustomcode, Lcustomcode;    /* ��8 */
    uint16_t datacode;                   /* 8λ�������� */
    uint8_t  Rdatacode;                   /* 8λ�����ݷ��� */

    uint8_t tBeep;                       /* ����������2����־λ */
}
_IRSYSTEM;

_IRSYSTEM IrSystem;

extern uint8_t AVB_Run;                    /* ��������״̬��־λ */
extern uint8_t Fn_key_state_flg;           /* Fn����״̬��־λ */
extern uint8_t Fn_key_timer;             /* Fn����3��ʧЧ��ʱ�� */
extern uint8_t YT_key_state_flg;           /* ��̨����״̬��־λ */
extern uint16_t key_FnYT_state;           /* ����Fn��YT״̬ */

extern uint8_t bit_beep;                   /* ��������2����־λ */

//extern uint32_t VfdYT;
/** 
* @Exit_Configuration 
* @brief  Exit_Configuration 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/

void Exit_Configuration(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 EXTI_InitTypeDef EXTI_InitStructure;
 NVIC_InitTypeDef NVIC_InitStructure;
  
  //�ⲿ�ж�ʹ�õ�RCCʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOʱ��  

  //�ⲿ�ж�ʹ�õ�GPIO����
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  

  /* Connect EXTI Line9 to PC.9 */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource9);

  /* Configure EXTI Line12 to generate an interrupt on falling edge */
  //�����ⲿ�ж�  
  EXTI_InitStructure.EXTI_Line = EXTI_Line9;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  //�ⲿ�ж�ʹ�õ�NVIC����
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI15_10 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/** 
* @fn IR_Init 
* @brief  IR_Init 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void IR_Init(void)
{
    uint8_t i = 0;
    uint8_t *p = (uint8_t *) (&IrSystem.IR_key);
    for(i = 0; i < sizeof(IrSystem); i++)
    {
        *p = 0;
        p++;
    }
    Exit_Configuration();
    Timer2_Configuration();
    TIM_SetCounter(TIM2, 0x0000);
    TIM_Cmd(TIM2, DISABLE);
    IrSystem.IR_YES = 1;
}

/** 
* @fn IR_Init 
* @brief  IR_Init 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void EXTI9_5_IRQHandler(void)
{
     
    //__disable_irq();               //�ر����ж�
   EXTI->IMR |= (~EXTI_Line9);                              //��
	if(EXTI_GetFlagStatus(EXTI_Line9)!= RESET)
  {  
  	 EXTI_ClearITPendingBit(EXTI_Line9);
    if((!IrSystem.IR_YES) && (!IrSystem.bit_off_power))
    {
       return;
    }   
    TIM_Cmd(TIM2,DISABLE);                         //��ͣ��ʱ��   
    IrSystem.time_us=TIM_GetCounter(TIM2);                //��ȡ�������Ĵ�����ֵ
    TIM_SetCounter(TIM2, 0x0000); 
    TIM_Cmd(TIM2,ENABLE);                           //�򿪶�ʱ��
     // WDI();	
    if((IrSystem.time_us>12900)&&(IrSystem.time_us<14106))
		{
        IrSystem.cn = 1;
        IrSystem.dm = 0x0000;
    }   
    //����������,�Ͱ�cn��0    
    if(IrSystem.cn < 34)
    {
        if((IrSystem.time_us>1031)&&(IrSystem.time_us<1221))
        {   
            IrSystem.dm = IrSystem.dm | 0x0000;
            if(IrSystem.cn < 33)
                IrSystem.dm = IrSystem.dm >> 1;
        }
        else if((IrSystem.time_us>2062)&&(IrSystem.time_us<2441))
        {
            IrSystem.dm = IrSystem.dm | 0x8000;
            if(IrSystem.cn < 33)
                IrSystem.dm = IrSystem.dm >> 1;
        }
        if(IrSystem.cn == 16)
        {
            IrSystem.customcode = IrSystem.dm;
            IrSystem.dm = 0x0000;
        }
        else if(IrSystem.cn == 33)
        {
            IrSystem.datacode = IrSystem.dm;
            IrSystem.dm = 0x0000;
        }
    }
    else if((IrSystem.time_us>10851) && (IrSystem.time_us<12478))
    {   
        if(IrSystem.bit_off_power)
        {
            if(IrSystem.Power_off_time++ > 40)
            {
                IrSystem.bit_off_power = 0;
                IrSystem.Power_off_time = 0;
                IrSystem.IR_power_off = 1;     //�ػ�                
                IrSystem.IRkey_temp = 0x45;//IR_PWR_OFF_KEY; 
                key_FnYT_state = 0;
                YT_key_state_flg = VfdYT;
                key_FnYT_state = Key_State_Process();
                key_FnYT_state |= 0x02;
                if(AVB_Run)
                {
                    UART2_Send_Key1(0x18, key_FnYT_state, IrSystem.IRkey_temp); 
                }
                IrSystem.IR_power_off = 0;
            }
        }
        else
        {
            IrSystem.bit_off_power = 0;
            IrSystem.Power_off_time = 0;
        }
        TIM_Cmd(TIM2,DISABLE);                              //��ͣ��ʱ��
    }  
    //�����ظ��� 
    IrSystem.cn++;
    if(IrSystem.cn == 34)
    {    
        IrSystem.NewIRcode = 1;
        TIM_Cmd(TIM2,DISABLE);                              //��ͣ��ʱ��
    }
    /**
    * ����32λ�룬����������� 
    */
   // EXTI->IMR |= EXTI_Line9;                              //���ⲿ�ж�9
    IrSystem.IRtime = 0;
   }
   EXTI->IMR |= EXTI_Line9;                              //���ⲿ�ж�9
     // __enable_irq();                             //�����ж�
}

/** 
* @fn IRProcess 
* @brief  IRProcess 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void IRProcess(void)
{
	  unsigned char temp = 0;

    WDI();
    IrSystem.FlagIrSendData = FALSE;
    if(IrSystem.NewIRcode == 1)
    {
        IrSystem.IRCODE = IrSystem.datacode;       /* ���� */
        IrSystem.RIRCODE = IrSystem.datacode >> 8; /* ���뷴�� */


		     temp = ~IrSystem.RIRCODE;
        if((IrSystem.customcode != 0x2c40)&&(temp!= IrSystem.IRCODE))               //��0x402c����Ϊ2c40(ԭ�ȴ����������)
        {
            IrSystem.DataRight = 0;
            IrSystem.datacode = 0;
            IrSystem.customcode = 0;
        }
        /**
        * У�� 
        */
        else if(IrSystem.IR_YES)
        {   /* �����Ƭ��������� */
            IrSystem.DataRight = 1;
            IrSystem.IR_YES = 0;
        }
        else
        {
            IrSystem.DataRight = 0;
        }
        IrSystem.NewIRcode = 0;
    }
    if(IrSystem.DataRight == 1)
    {   /* ������ȷ�İ��������� */
        IrSystem.DataRight = 0;
        if(!IrSystem.IR_keyup && IrSystem.IR_keydown_flag)
        {   /* δ��̧���ֵ,���������µİ��������,����֮ǰ�İ���̧����Ϣ */
            if(IrSystem.IRkey_temp != 0xff)
            {
                key_FnYT_state = 0;
                YT_key_state_flg = VfdYT;
                key_FnYT_state = Key_State_Process();
                key_FnYT_state |= 0x01;
                if(AVB_Run)
                {
                    UART2_Send_Key1(0x18, key_FnYT_state,IrSystem.IRkey_temp);
                }
		  /**
                * Fn״̬λ�ڷ��ͼ�ֵ����������û�м�ֵ���ͣ��ȴ�3S��ʱʧЧ
                */
                Fn_key_timer = 0;
                Fn_key_state_flg = 0;
            }
            IrSystem.IRkey_temp = 0xff;
            IrSystem.IR_keyup = 1;
        }
        IrSystem.IR_keydown_flag = 0;          /* δ���Ͱ��µļ�ֵ */
        IrSystem.IR_FLAG = 1;
        IrSystem.NewIRcode = 0;
        IrSystem.IR_key = IrSystem.IRCODE;     /* ��ȡң������ֵ */
        switch (IrSystem.IR_key)
        {
            case 0x12:         /* 0 */
                IrSystem.IRkey_temp = 0x12;    /* NUM0; */
                break;
            case 0x09:         /* 1 */
                IrSystem.IRkey_temp = 0x09;    /* NUM1; */
                break;
            case 0x1d:         /* 2 */
                IrSystem.IRkey_temp = 0x1d;    /* NUM2; */
                break;
            case 0x1f:         /* 3 */
                IrSystem.IRkey_temp = 0x1f;    /* NUM3; */
                break;
            case 0x0d:         /* 4 */
                IrSystem.IRkey_temp = 0x0d;    /* NUM4; */
                break;
            case 0x19:         /* 5 */
                IrSystem.IRkey_temp = 0x19;    /* NUM5; */
                break;
            case 0x1b:         /* 6 */
                IrSystem.IRkey_temp = 0x1b;    /* NUM6; */
                break;
            case 0x11:         /* 7 */
                IrSystem.IRkey_temp = 0x11;    /* NUM7; */
                break;
            case 0x15:         /* 8 */
                IrSystem.IRkey_temp = 0x15;    /* NUM8; */
                break;
            case 0x17:         /* 9 */
                IrSystem.IRkey_temp = 0x17;    /* NUM9; */
                break;
            case 0x56:         /* ��/-�� */
                IrSystem.IRkey_temp = 0x56;    /* IR_JIAN_KEY; */
                break;
            case 0x57:         /* "#/+" */
                IrSystem.IRkey_temp = 0x57;    /* IR_JIA_KEY; */
                break;
            case 0x00:         /* ������ */
                IrSystem.IRkey_temp = 0x00;    /* IR_LOCK_KEY; */
                break;
            case 0x08:
                 IrSystem.IRkey_temp = 0x08;   /* DOUBLE_SPEAK_KEY1;*/
                break;
            case 0x0a:
                IrSystem.IRkey_temp = 0x0a;  /* YT_CTRL_KEY1; */
                break;
            case 0x0c:         /* ������� */
                IrSystem.IRkey_temp = 0x0c;    /* CLEAR_ALARM_KEY1; */
                break;
            case 0x13:         /* �˵� */
                IrSystem.IRkey_temp = 0x13;    /* MENU_KEY1; */
                break;
            case 0x10:
                Fn_key_state_flg = 1;  /* ң�ذ���Fn���⴦�� */
                break;
            case 0x06:
                IrSystem.IRkey_temp = 0x06;   /* ESC_KEY1; */
                break;
            case 0x5c:         /* ��Ϣ��ʾ */
                IrSystem.IRkey_temp = 0x5c;    /* MESSAGE_KEY1; */
                break;
            case 0x4f:         /* ֹͣ */
                IrSystem.IRkey_temp = 0x4f;    /* STOP_KEY1; */
                break;
            case 0x07:         /* ����/��ͣ */
                IrSystem.IRkey_temp = 0x07;    /* PLAY_KEY1; */
                break;
            case 0x0e:         /* ���� */
                IrSystem.IRkey_temp = 0x0e;    /* LEFT_KEY1; */
                break;
            case 0x1a:         /* ���� */
                IrSystem.IRkey_temp = 0x1a;    /* RIGHT_KEY1; */
                break;
            case 0x03:         /* ���� */
                IrSystem.IRkey_temp = 0x03;    /* UP_KEY1; */
                break;
            case 0x02:         /* ���� */
                IrSystem.IRkey_temp = 0x02;    /* DOWN_KEY1; */
                break;
            case 0x48:         /* ¼�� */
                IrSystem.IRkey_temp = 0x48;    /* RECORD_KEY1; */
                break;
            case 0x18:         /* ���� */
                IrSystem.IRkey_temp = 0x18;    /* IR_SEARCH_KEY; */
                break;
            case 0x51:         /* ������ */
                IrSystem.IRkey_temp = 0x51;    /* IR_BUFANG_KEY; */
                break;
            case 0x50:         /* �໭�� */
                IrSystem.IRkey_temp = 0x50;    /* FULL_SCREEN_KEY1; */
                break;
            case 0x52:         /* ���ˡ�<-��*/
                IrSystem.IRkey_temp = 0x52;    /* RAPID_BACK_KEY1; */
                break;
            case 0x53:         /* ������->��*/
                IrSystem.IRkey_temp = 0x53;    /* RAPID_FORWARD_KEY1; */
                break;
            case 0x4a:         /* ����ѡ�� */
                IrSystem.IRkey_temp = 0x4a;    /* PIC_QUALITY_KEY1; */
                break;
            case 0x49:         /* ���� */
                IrSystem.IRkey_temp = 0x49;    /* IR_BACKUP_KEY; */
                break;
            case 0x1c:         /* ���� */
                IrSystem.IRkey_temp = 0x1c;    /* IR_STOP_KEY; */
                break;
            case 0x4e:         /* ��ʱ */
                IrSystem.IRkey_temp = 0x4e;    /* IR_TIME_KEY; */
                break;
            case 0x14:         /* ��� */
                IrSystem.IRkey_temp = 0x14;    /* SINGLE_FRAME_KEY1; */
                break;
            case 0x41:         /* �豸 */
                IrSystem.IRkey_temp = 0x41;    /* IR_SB_KEY; */
                bit_beep = 1;
                break;
            case 0x45:         /* �ػ� */
                IrSystem.bit_off_power = 1;    /* ң�ذ����ػ����⴦�� */
                IrSystem.IRkey_temp = 0xff;    /* ���ⰴ�¹ػ���������0x00��ֵ */
                break;
            default:
                IrSystem.IRkey_temp = 0xff;
                break;
        }
        if(IrSystem.IRkey_temp != 0xff)
        {
            /**
            *  �����·��ͼ�ֵ 
            */
            key_FnYT_state = 0;
            YT_key_state_flg = VfdYT;
            key_FnYT_state = Key_State_Process();
            key_FnYT_state |= 0x02;
            if(AVB_Run)
            	{
                UART2_Send_Key1(0x18, key_FnYT_state, IrSystem.IRkey_temp);
            	}
            IrSystem.IR_keydown_flag = 1;
            IrSystem.IR_YES = 1;                /* ��Ƭ�����ܲ�������� */
        }
    }
    /**
    *  ����̧�𰴼� 
    */
   // POWER_STB=~POWER_STB;//������䣬�ύʱӦɾ��
    if(IrSystem.IR_FLAG == 1)
    {
        if((IrSystem.IRtime >= 200) && (IrSystem.IR_keyup != 1))
        {   /* ����̧�� */
            if(IrSystem.IRkey_temp != 0xff)
            {
                key_FnYT_state = 0;
                YT_key_state_flg = VfdYT;
                key_FnYT_state = Key_State_Process();
                key_FnYT_state |= 0x01;
                if(AVB_Run)
                {
			             UART2_Send_Key1(0x18, key_FnYT_state, IrSystem.IRkey_temp);
            	   }
                /**
                * Fn״̬λ�ڷ��ͼ�ֵ����������û�м�ֵ���ͣ��ȴ�3S��ʱʧЧ
                */
                Fn_key_timer = 0;
                Fn_key_state_flg = 0;
            }
            IrSystem.IR_keyup = 1;             /* ̧�𰴼� */
            IrSystem.IRkey_temp = 0xff;
            IrSystem.IR_FLAG = 0;
            IrSystem.IRtime = 0;
            IrSystem.IR_YES = 1;               /* ��Ƭ�����ܲ�������� */
        }
        else
        {
            IrSystem.IRtime++;
            IrSystem.IR_keyup = 0;             /* δ��̧���ֵ */
        }
    }
}
