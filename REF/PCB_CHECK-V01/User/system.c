
/******************************************************************************
�ú�����Ҫʵ��ϵͳʱ�����ú�I/O�ڵĳ�ʼ������
******************************************************************************/
#include "main.h"
/*******************************************************************************
ϵͳʱ�ӳ�ʼ������ ��GPIO�ĳ�ʼ��
*******************************************************************************/
//GPIOC

//#define LED1_PIN 				GPIO_Pin_15					//PC15

//GPIOA
#define MOTO_FORW_PIN 	GPIO_Pin_5
#define MOTO_BACK_PIN 	GPIO_Pin_6
#define PRT_DTR_PIN		 	GPIO_Pin_7
#define RCLK1_PIN	 			GPIO_Pin_8					
#define BEEP_PIN	 			GPIO_Pin_11
#define COL_A_PIN 			GPIO_Pin_12
#define COL_B_PIN 			GPIO_Pin_15

/*
#define SELA_PIN 				GPIO_Pin_3	    		
#define SELB_PIN 				GPIO_Pin_4	  			
#define VDDPA3_C_PIN 		GPIO_Pin_5  			
#define IF3_CON_PIN 		GPIO_Pin_6  			
#define VDD3_CON_PIN 		GPIO_Pin_7	
#define IC3_FLAG_PIN	 	GPIO_Pin_8					
#define IC4_FLAG_PIN	 	GPIO_Pin_11
#define DATA_PIN 				GPIO_Pin_12
#define RCLK_PIN 				GPIO_Pin_15
*/

//GPIOB
#define LIGHT_CHECK_PIN 		GPIO_Pin_0
#define LED_CON_PIN 		GPIO_Pin_1
#define O_OUT_PIN 			GPIO_Pin_3
#define EN_D2_PIN 			GPIO_Pin_4

#define SRCLK2_PIN 			GPIO_Pin_5
#define RCLK2_PIN 			GPIO_Pin_6
#define RCLK_PIN 				GPIO_Pin_7
#define DATA_PIN 				GPIO_Pin_8
#define	SRCLK_PIN 			GPIO_Pin_9
//#define VDD1_CON_PIN 		GPIO_Pin_10
//#define ENV12_PIN 			GPIO_Pin_11

#define ROW_A_PIN 			GPIO_Pin_12
#define ROW_B_PIN 			GPIO_Pin_13
#define SRCLK1_PIN 			GPIO_Pin_14
#define EN_D1_PIN 			GPIO_Pin_15



/*
#define IF1_CON_PIN 		GPIO_Pin_0
#define VDDPA1_C_PIN 		GPIO_Pin_1
#define SRCLK_PIN 			GPIO_Pin_3
#define VDDPA2_C_PIN 		GPIO_Pin_4

#define VDD2_CON_PIN 		GPIO_Pin_5
#define IF2_CON_PIN 		GPIO_Pin_6
#define VDDPA4_C_PIN 		GPIO_Pin_7
#define VDD4_CON_PIN 		GPIO_Pin_8
#define IF4_CON_PIN 		GPIO_Pin_9
#define VDD1_CON_PIN 		GPIO_Pin_10
#define ENV12_PIN 			GPIO_Pin_11
#define START_CHECK_PIN GPIO_Pin_12
#define CHECK_END_PIN 	GPIO_Pin_13
#define IC1_FLAG_PIN 		GPIO_Pin_14
#define IC2_FLAG_PIN 		GPIO_Pin_15
*/


//GPIOC
#define KEY1_PIN 				GPIO_Pin_15
#define KEY2_PIN 				GPIO_Pin_14
#define KEY3_PIN 				GPIO_Pin_13

void RCC_Configuration(void) 
{  
	
	//	ErrorStatus HSEStartUpStatus;   
	
	RCC_DeInit();
       RCC_HSICmd(ENABLE);//ʹ���ڲ����پ��� ;
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//ѡ���ڲ�����ʱ����Ϊϵͳʱ��SYSCLOCK=8MHZ 
	RCC_HCLKConfig(RCC_SYSCLK_Div1);//ѡ��HCLKʱ��ԴΪϵͳʱ��SYYSCLOCK
  RCC_PCLK1Config(RCC_HCLK_Div2);//APB1ʱ��Ϊ4M 
  RCC_PCLK2Config(RCC_HCLK_Div1);//APB2ʱ��Ϊ8M
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);//ʹ��APB2����GPIOBʱ��
	
	//  HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ��ⲿʱ�Ӿ���

 // if(HSEStartUpStatus == SUCCESS)
 // {
	    // Enable Prefetch Buffer ����Ԥȡ������ 

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /// Flash 2 wait state FLASH����2���ȴ�����
    FLASH_SetLatency(FLASH_Latency_2);
	
 	/*
    /// HCLK = SYSCLK ����ϵͳ����
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /// PCLK2 = HCLK PCLK2ʱ��=��ʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    // PCLK1 = HCLK/2 PCLK1ʱ��Ϊ��ʱ��1/2
    RCC_PCLK1Config(RCC_HCLK_Div2);
*/
    // PLLCLK = 8MHz * 3 = 24 MHz ����ʱ��Ϊ24M
  //  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_3);
		
		
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_2);

    // Enable PLL ʹ��PLL
    RCC_PLLCmd(ENABLE);

    // Wait till PLL is ready �ȴ�PLL�����ȶ�
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    // Select PLL as system clock source ѡ��PLL��Ϊϵͳʱ��Դ
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // Wait till PLL is used as system clock source ׼����������ʼ�ɻ�
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
		
	//}
	
}

void RCC_Configuration1(void)
{
	ErrorStatus HSEStartUpStatus;   
  
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);//ʹ���ⲿʱ�� 

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ��ⲿʱ�Ӿ���

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer ����Ԥȡ������ */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state FLASH����2���ȴ�����*/
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK ����ϵͳ����*/
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK PCLK2ʱ��=��ʱ��*/
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 PCLK1ʱ��Ϊ��ʱ��1/2*/
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 3 = 24 MHz ����ʱ��Ϊ24M*/
  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_3);
		
		//RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_3);

    /* Enable PLL ʹ��PLL*/ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready �ȴ�PLL�����ȶ�*/
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source ѡ��PLL��Ϊϵͳʱ��Դ*/
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source ׼����������ʼ�ɻ�*/
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
	else RCC_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
}

/*******************************************************************************
GPIO�ڵĳ�ʼ�����ú�������ã���Ҫ��I/O�ڵ��������ģʽ ģʽ����ע��˲�
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

   //PWR_BackupAccessCmd(ENABLE);
   //RCC_LSEConfig(RCC_LSE_OFF);
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);        //ʹ��GPIOʱ��ʹ�ܣ�GPIOA��GPIOBʱ��ʹ��
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO ,ENABLE );
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	
//�����õ�IO�ڵĳ�ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOA, &GPIO_InitStructure);			                                      //����GPIOA,PA0,PA1 ,PA4Ϊģ������
                                          
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  //GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GPIOB, &GPIO_InitStructure);			                                      //����PB0Ϊģ������



  GPIO_InitStructure.GPIO_Pin = MOTO_FORW_PIN | MOTO_BACK_PIN | RCLK1_PIN | BEEP_PIN | COL_A_PIN | COL_B_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);			                                      //����PA3~PA15Ϊ�������,Ԥ��ʹ��
	                                                                                 
	/*GPIOA Configuration: TIM3 channel2*/	  //���ø�����Ϊ�����������,���TIM3 CH2��PWM���岨��
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH2
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������                   //����PA7-PWM���
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	


	GPIO_InitStructure.GPIO_Pin = PRT_DTR_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);		
	

//	GPIO_InitStructure.GPIO_Pin = O_OUT_PIN ;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(GPIOB, &GPIO_InitStructure);		
	
	
  GPIO_InitStructure.GPIO_Pin = LED_CON_PIN|EN_D2_PIN|SRCLK2_PIN|RCLK2_PIN|RCLK_PIN|DATA_PIN|SRCLK_PIN
																|ROW_A_PIN|ROW_B_PIN |SRCLK1_PIN|EN_D1_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSEConfig(RCC_LSE_OFF);
	BKP_TamperPinCmd(DISABLE);
	BKP_ITConfig(DISABLE); 



	GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN | KEY3_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	 PWR_BackupAccessCmd(DISABLE);

/*
  GPIO_InitStructure.GPIO_Pin = TEMP1_DAT_PIN|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
*/	
	
	/*********************��ʼ������IO����**********************************/         //����Ϊ��Ҫ��ô����

 /* Configure USART1 Rx (PA.10) as input floating */  //USART2 RX(PA3)
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Configure USART2 Rx (PA.03) as input floating */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10| GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		//USART3 RX(PB11)
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  /* Configure USART1 Tx (PA.09) as alternate function push-pull */  //USART2 TX(PA2)
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_2;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		//USART3 TX(PB10)
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
		
	// Configure USART2 Tx (PA.02) as alternate function push-pull
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA,GPIO_Pin_9 | GPIO_Pin_2);

  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
 // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  //GPIO_Init(GPIOA, &GPIO_InitStructure);			 //����PA10����ģʽ
	/*****************************************************************************************************/
/*
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);			                                       //����GPIO.PB12
*/
  

	
}
/********************************************************************************/
void NVIC_Configuration(void)
{
   //#ifdef  VECT_TAB_RAM
#if defined (VECT_TAB_RAM)
   /* Set the Vector Table base location at 0x20000000 */ 
   NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); //�����ж�������RAM��
   //#elif defined(VECT_TAB_FLASH_IAP)
   //  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
#else  /* VECT_TAB_FLASH  */
   /* Set the Vector Table base location at 0x08000000 */ 
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x000000); //�����ж�������FLASH��  
#endif
	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}
/*************************************************************************/

/**********************************************************************
* ��    �ƣ�USART_Configuration()
* ��    �ܣ���������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵�������ڳ�ʼ������
***********************************************************************/
 void USART_Configuration(void)                        
{

	NVIC_InitTypeDef NVIC_InitStructure;
	
/* USART1 and USART1 configuration ------------------------------------------------------*/
  /* USART and USART1 configured as follow:
        - BaudRate = 9600 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */

  USART_InitTypeDef USART_InitStructure;
//  USART_ClockInitTypeDef  USART_InitClock;						//���崮�ڳ�ʼ��ʱ�ӽṹ��

	/*
	  USART_InitClock.USART_Clock = USART_Clock_Disable; 				//����ʱ�ӽ�ֹ
  USART_InitClock.USART_CPOL = USART_CPOL_Low; 					    //ʱ���½�����Ч
  USART_InitClock.USART_CPHA = USART_CPHA_2Edge;					//�����ڵڶ���ʱ���ز�׽
  USART_InitClock.USART_LastBit = USART_LastBit_Disable;			//�������λ��ʱ�����岻�����SCLK����
																	
  USART_ClockInit(USART1,&USART_InitClock);//��ʼ��USART1��Χʱ�ӣ����� USART_ClockInitStruct �ڵĲ���.
	*/
	
  USART_InitStructure.USART_BaudRate = 57600;//9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);

  /* Enable USART1 Receive and Transmit interrupts */
 // USART_ITConfig(USART1, USART_IT_RXNE,ENABLE);
  //USART_ITConfig(USART1, USART_IT_TC,DISABLE);

  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);

//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	
		// Enable the USART1 Interrupt
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		
		

//ENABLE USART2 AND USART3 CLOCK
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3|RCC_APB2Periph_AFIO, ENABLE);
		
	
		USART_InitStructure.USART_BaudRate = 57600;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		USART_Init(USART2, &USART_InitStructure);
		
		// Enable USART2
		USART_Cmd(USART2, ENABLE);
	
/*	
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	*/	
		
	  USART_InitStructure.USART_BaudRate = 9600; 
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; 
    USART_InitStructure.USART_StopBits = USART_StopBits_1; 
    USART_InitStructure.USART_Parity = USART_Parity_No; 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE); 
		
//	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
		
		
		USART_ClearFlag(USART1, USART_FLAG_TC);
		USART_ClearFlag(USART2, USART_FLAG_TC);
		USART_ClearFlag(USART3, USART_FLAG_TC);
		
	/*
		USART_ITConfig(USART1, USART_IT_PE, DISABLE);
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		USART_ITConfig(USART1, USART_IT_TC, DISABLE);
		USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
		USART_ITConfig(USART1, USART_IT_LBD, DISABLE);		
		USART_ITConfig(USART1, USART_IT_CTS, DISABLE);		
		USART_ITConfig(USART1, USART_IT_ERR, DISABLE);
		USART_ITConfig(USART1, USART_IT_ORE, DISABLE);
		USART_ITConfig(USART1, USART_IT_NE, DISABLE);
		USART_ITConfig(USART1, USART_IT_FE, DISABLE);		
		*/
/*		
#define USART_IT_PE                          ((uint16_t)0x0028)
#define USART_IT_TXE                         ((uint16_t)0x0727)
#define USART_IT_TC                          ((uint16_t)0x0626)
#define USART_IT_RXNE                        ((uint16_t)0x0525)
#define USART_IT_IDLE                        ((uint16_t)0x0424)
#define USART_IT_LBD                         ((uint16_t)0x0846)
#define USART_IT_CTS                         ((uint16_t)0x096A)
#define USART_IT_ERR                         ((uint16_t)0x0060)
#define USART_IT_ORE                         ((uint16_t)0x0360)
#define USART_IT_NE                          ((uint16_t)0x0260)
#define USART_IT_FE                          ((uint16_t)0x0160)
*/

}




void system_Init(void)
{
  
   __disable_irq();               //�ر����ж�
	
    /**
    *  ��ʼ����ʱ��6
    */
   // Timer6_Configuration();
   /**
    * ��ʼ����ʱ��2
    */
   
  // Timer2_Configuration();

      /**
    * ��ʼ����ʱ��3
    */
     //  TIM3_Mode_Config();

      /**
    * ��ʼ����ʱ��7
    */
  // Timer7_Configuration();

       /**
    *  ��ʼ������ 
    */
  //  USART2_Init();
    /**
    *  ��ʼ������ң�� 
    */
  // IR_Init();
    
    /**
    *  ���Ź���ʼ��
    */
   //IWDG_Init();

   //�����ж�
      __enable_irq();
}

void SET_PA15PB3PB4(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;//|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);	
	//GPIO_SetBits(GPIOB,GPIO_Pin_3); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);

}

