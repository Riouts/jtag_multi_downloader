#include<main.h>

/*
extern uint8_t  Time2_500ms_OK;
extern uint8_t   Leds_Light_TimeCnt;
extern uint8_t   PWM_Switch_State;
extern uint8_t  Key_UpD_Flg;
extern u8 PWM_val,PWM_UP;
extern u8 S6_recnum,Send_data;
//extern u8 USB_Send[30];
extern u8 USART1_recdata[20];
extern u8 beep_st;


extern u8 Pulse_num,Pulse_mode;
*/


/**************************************************************/
void Timer6_Configuration(void)
{
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  NVIC_InitTypeDef          NVIC_InitStructure;
  //------------------------------------------------------------
  //�򿪶�ʱ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  //------------------------------------------------------------
  //TIMx�Ĵ�������Ϊȱʡֵ
  TIM_DeInit(TIM6);
  TIM_TimeBaseStructure.TIM_Period=499;      //�Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler=23999;  //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ1mms
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM6, DISABLE);//ʹ��ARRԤװ�ػ�����
  TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); 
  TIM_Cmd(TIM6, ENABLE);	//����ʱ�� 
  //------------------------------------------------------------
  //����TIM6�ж�
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =TIM6_DAC_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/***************************************************************/
void Timer7_Configuration(void)
{
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  NVIC_InitTypeDef          NVIC_InitStructure;
  //------------------------------------------------------------
  //�򿪶�ʱ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  //------------------------------------------------------------
  TIM_DeInit(TIM7);
  TIM_TimeBaseStructure.TIM_Period=100;		 //�Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler=23999;  //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ1mms
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM7, DISABLE);//ʹ��ARRԤװ�ػ�����
  TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE); 
  TIM_Cmd(TIM7, ENABLE);	//����ʱ�� 
  //------------------------------------------------------------
  //����TIM7�ж�
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =TIM7_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
/*************************************************************************/
void Timer2_Configuration(void)
{
	/*
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  NVIC_InitTypeDef          NVIC_InitStructure;
  //------------------------------------------------------------
  //�򿪶�ʱ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  //------------------------------------------------------------
  TIM_DeInit(TIM2);
  TIM_TimeBaseStructure.TIM_Period=500;		 //�Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler=23999;  //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ1mms
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM2, ENABLE);//ʹ��ARRԤװ�ػ�����
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); 
  TIM_Cmd(TIM2, ENABLE);	//����ʱ�� 
  //------------------------------------------------------------
  //����TIM2�ж�
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	*/
	
	    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
			NVIC_InitTypeDef          NVIC_InitStructure;

			RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
			TIM_DeInit(TIM2);
	
     TIM_TimeBaseStructure.TIM_Period =19;  //  10us*20->5kHz
     TIM_TimeBaseStructure.TIM_Prescaler = 239; //24MHZ/(239+1) =100Khz      
     TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //24MHZ 
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //Mode;
     TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
     TIM_Cmd(TIM2, ENABLE);

		 
     NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;  
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);		 
		 
     TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE);
     TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 );			 
}

/*************************************************************************/
void Timer3_Configuration(void)
{

  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  NVIC_InitTypeDef          NVIC_InitStructure;
  //------------------------------------------------------------
  //�򿪶�ʱ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  //------------------------------------------------------------
  TIM_DeInit(TIM3);
  TIM_TimeBaseStructure.TIM_Period=200;		 //�Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler=23999;        //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ1mms
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_ARRPreloadConfig(TIM3, DISABLE);//ʹ��ARRԤװ�ػ�����
  TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
  TIM_Cmd(TIM3, DISABLE);	//����ʱ�� 
  //------------------------------------------------------------
  //����TIM3�ж�
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;
 // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =5;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =6;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void Timer4_Configuration(void)
{
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  NVIC_InitTypeDef          NVIC_InitStructure;
  //------------------------------------------------------------
  //�򿪶�ʱ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  //------------------------------------------------------------
  //TIMx�Ĵ�������Ϊȱʡֵ
  TIM_DeInit(TIM4);
  TIM_TimeBaseStructure.TIM_Period=65;      //�Զ���װ�ؼĴ������ڵ�ֵ
  TIM_TimeBaseStructure.TIM_Prescaler=7999;  //TIMx ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ1mms
 // TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
//  TIM_ARRPreloadConfig(TIM6, ENABLE);//ʹ��ARRԤװ�ػ�����
//  TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE); 
//  TIM_Cmd(TIM6, ENABLE);	//����ʱ�� 
	
	   TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //48MHZ 
     TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //Mode;
     TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
     TIM_Cmd(TIM4, ENABLE);
    // TIM_ITConfig(TIM4,TIM_IT_CC1,ENABLE);
     TIM_ClearITPendingBit(TIM4, TIM_IT_CC1 );	
	
  //------------------------------------------------------------
  //����TIM6�ж�
  //NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;//TIM6_DAC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


/*************************************************************************/
void TIM6_DAC_IRQHandler(void)
{
 
   if(TIM_GetITStatus(TIM6,TIM_IT_Update)!=RESET)
   {
      WDI();
      //����жϱ�־
      TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
  //    SEC_CYCLE_MARK =1;
  //    AVB_timeout_counter++;
		  
   }
}
/************************************************************************/

void TIM7_IRQHandler(void)
{
 
   if(TIM_GetITStatus(TIM7,TIM_IT_Update)!=RESET)
   {
      WDI();
      //����жϱ�־
      TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
//      AVB_States_WatchDog();
   }
}
/*************************************************************************/
void TIM2_IRQHandler(void)	//������Դ������	//2.5kHz
{
 

     if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
     {
        // for LED test
			 /*
        if (GPIOA->ODR & 0x04 ) 
	    GPIOA->ODR &= (~0x04);
        else
	    GPIOA->ODR |= 0x04;
				*/
       // if (TimeCount<0xff) TimeCount++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_CC1 );	
				
				if(beep_st==0)
				{
					BEEP_OFF;
				}
				else
				{
					if((beep_st%2)==1)
					{
						BEEP_ON;
					}
					else
					{
						BEEP_OFF;
					}
					beep_st++;
					if(beep_st>100)beep_st=1;
				}
			 
     }  
}

/*************************************************************************/

/*
void TIM3_IRQHandler(void)
{
 
   if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
   {
      WDI();
      //����жϱ�־
      TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
   //   LedBlinkControl();
  }
}


void TIM4_IRQHandler(void)
{
	if(PWM_UP==1)
	{
		TIM_SetCompare2(TIM3,PWM_val);
		PWM_val++;
		if(PWM_val>20)PWM_val++;
		if(PWM_val>60)PWM_val++;
		if(PWM_val>=120)
			PWM_UP=0;
	}
	else
	{
		TIM_SetCompare2(TIM3,PWM_val);	
		PWM_val--;
		if(PWM_val>20)PWM_val--;
		if(PWM_val>60)PWM_val--;
		
		if(PWM_val<2)
			PWM_UP=1;		
	}
	TIM_ClearITPendingBit(TIM4, TIM_IT_CC1 );	
}
*/

//

//          |  PA.06: (TIM3_CH1)  |
//          |  PA.07: (TIM3_CH2)  |
//    	|  PB.00: (TIM3_CH3)  | 
//  		|  PB.01: (TIM3_CH4)  |

/**********************************************************************************/


/*
 * ��������TIM3_Mode_Config
 * ����  ������TIM3�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */



 void TIM3_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	 uint16_t CCR2_Val = 0;
 //------------------------------------------------------------
  //�򿪶�ʱ����ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/* PWM�źŵ�ƽ����ֵ */
	//u16 CCR1_Val = 500;        

	//u16 CCR3_Val = 250;
	//u16 CCR4_Val = 125;

/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
    TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 72 KHz.
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 199;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 1;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz 10����20KHz  ��2016��2��19�ն�Ϊ4,Ƶ��Ϊ48KHz���������΢��
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR2_ValʱΪ�ߵ�ƽ

  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��2

  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
}


//PWM
/*
void PWM_Out_Off(void)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_Cmd(TIM3, DISABLE);                   //ʹ�ܶ�ʱ��3	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 //����PA7Ϊ��������
  PA7OUT=0x00;
  MOS_B_CTRL=0x00;
}
*/

/*
void PWM_Out_On(void)
{
  
  GPIO_InitTypeDef GPIO_InitStructure;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);				 //����PA7Ϊ��������
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
  MOS_B_CTRL=0x01;
}
*/

/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/

