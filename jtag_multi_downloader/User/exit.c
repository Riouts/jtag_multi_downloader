#include "main.h"

/*
extern uint8_t  Key_UpD_Flg;
extern uint8_t  Leds_Light_TimeCnt;
extern uint8_t  PWM_Switch_State;
extern uint8_t   Load_ON_Flg;
extern uint8_t   Run_Flag;
extern uint8_t  t;
extern uint8_t  t1;
extern uint8_t  IN_PUT_State;
void delay100ms(void);
void delay5ms(void);
*/

void Exit_Configuration(void)
{
 GPIO_InitTypeDef GPIO_InitStructure;
 EXTI_InitTypeDef EXTI_InitStructure;
 NVIC_InitTypeDef NVIC_InitStructure;
  
  //外部中断使用的RCC时钟
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);//使能GPIOB和复用功能时钟
	
  //外部中断使用的GPIO配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;              //PB12 中断唤醒
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 

/*
	  //PB1配置为外部中断
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;               //PB1->PV_INT组件输入中断唤醒
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
*/

/*//PB11配置为外部中断
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;             //PB11->INPUT_INTUSB输入中断唤醒
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	*/

	///////////////////////////////////////////
	/*
   //PB14配置为外部中断
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;              //PB14负载中断
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure); 
	*/
  /* Connect EXTI Line1,10,11,14 to PB.1,10,11,14 */
	
	//GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
//PIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
//	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);

  /* Configure EXTI Line12 to generate an interrupt on falling edge */
  //配置外部中断  
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

/*
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
*/

/*
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  //EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
	*/
	/*
  EXTI_InitStructure.EXTI_Line = EXTI_Line14;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  */
  //外部中断使用的NVIC配置
  /* Configure one bit for preemption priority */
 // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI15_10 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
/*	
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  //NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
*/
}
//////////////////////////////////////////////////////////////////////////////////////////////
//中断函数，以下是中断子函数
void EXTI15_10_IRQHandler(void)
{
     
	if(EXTI_GetFlagStatus(EXTI_Line10)!= RESET)
  {  
		  EXTI->IMR |= (~EXTI_Line10);                            //
  	 EXTI_ClearITPendingBit(EXTI_Line10);
		
	/*	
		 //if(PWM_Switch_State==0x00)
     Key_UpD_Flg++;
		// t1=1;
		 Run_Flag = 1;
		// delay5ms();                        //增加延时等待时钟准备完毕
    // Key_UpD_Flg=0x01;
    // RCC_Configuration();                 //STM32时钟初始化
    // ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
		
		*/
		
    EXTI->IMR |= EXTI_Line10;                              //打开外部中断10
   }
	//////////////////////////////////////////////////////////////////////////////////////////
	 	if(EXTI_GetFlagStatus(EXTI_Line11)!= RESET)            //PB11是USB输入电压唤醒
  {  
		
		
		 EXTI->IMR |= (~EXTI_Line11);                            //
  	 EXTI_ClearITPendingBit(EXTI_Line11);
		{
			/*
			         delay100ms();
			  //       delay100ms();			
			         delay100ms();			                          //这几个delay是为了克服microUSb的充电系统初始化问题
      				 IN_PUT_State = 1;	
							 Run_Flag = 1;
			*/
	/*-----------------------------------------------------------------*/		
		//	delay5ms();
		//		Leds_Light_TimeCnt=GPIO_ReadInputDataBit(GPIOB,11);
			
	/*-----------------------------------------------------------------*/		
		 }
     EXTI->IMR |= EXTI_Line11;                              //打开外部中断10
  }
	////////////////////////////////////////////////////////////////////////////////////////
	/*
		if(EXTI_GetFlagStatus(EXTI_Line14)!= RESET)
		{
		 EXTI->IMR |= (~EXTI_Line14);                            //
  	 EXTI_ClearITPendingBit(EXTI_Line14);
			USB_EN = 0x01;
			OUT_EN = 0x01;
			Load_ON_Flg=0x01;
			Run_Flag=1;
     // RCC_Configuration();                 //STM32时钟初始化
	   // ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1					  
		  EXTI->IMR |= EXTI_Line14;                              //打开外部中断14
		}
	*/

}
/*-----------------------------------------------------------------------------------*/// 组件电压唤醒函数

/*
void EXTI1_IRQHandler(void)           //PV组件电压唤醒，PB1口
{ 		    		    				     		    
	EXTI->IMR |= (~EXTI_Line1);   		  
	if(EXTI_GetFlagStatus(EXTI_Line1)!= RESET)
  {  
  	 EXTI_ClearITPendingBit(EXTI_Line1);
		{
		 PWM_Switch_State = 0x01;
		 Run_Flag = 0x01;
     EXTI->IMR |= EXTI_Line1;                              //打开外部中断1
		}
	//	*((u32 *)0xE000ED0C) = 0x05fa0004;    //系统复位		

  }
}
*/

/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
//程序代码段结束





