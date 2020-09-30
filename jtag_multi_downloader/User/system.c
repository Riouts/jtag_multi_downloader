
/******************************************************************************
该函数主要实现系统时钟配置和I/O口的初始化设置
******************************************************************************/
#include "main.h"
/*******************************************************************************
系统时钟初始化设置 和GPIO的初始化
*******************************************************************************/
//GPIOA
#define RCLK_PIN	 			GPIO_Pin_8					
#define BEEP_PIN	 			GPIO_Pin_11
#define PRT_DTR_PIN		 	GPIO_Pin_7

//GPIOB
#define DATA_PIN 				GPIO_Pin_15
#define	SRCLK_PIN 			GPIO_Pin_14

#define	PM51_START_PIN 			GPIO_Pin_6
#define	PM51_OK_PIN 		  	GPIO_Pin_7
#define	PM51_BUSY_PIN 			GPIO_Pin_8
#define	PM51_FAIL_PIN 			GPIO_Pin_9

//GPIOC
#define KEY1_PIN 				GPIO_Pin_15
#define KEY2_PIN 				GPIO_Pin_14


void RCC_Configuration(void) 
{  
	
	//	ErrorStatus HSEStartUpStatus;   
	
	RCC_DeInit();
  RCC_HSICmd(ENABLE);//使能内部高速晶振 ;
  RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);//选择内部高速时钟作为系统时钟SYSCLOCK=8MHZ 
	RCC_HCLKConfig(RCC_SYSCLK_Div1);//选择HCLK时钟源为系统时钟SYYSCLOCK
  RCC_PCLK1Config(RCC_HCLK_Div2);//APB1时钟为4M 
  RCC_PCLK2Config(RCC_HCLK_Div1);//APB2时钟为8M
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);//使能APB2外设GPIOB时钟
	
	//  HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待外部时钟就绪

 // if(HSEStartUpStatus == SUCCESS)
 // {
	    // Enable Prefetch Buffer 启用预取缓冲器 

    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /// Flash 2 wait state FLASH设置2个等待周期
    FLASH_SetLatency(FLASH_Latency_2);
	
 	/*
    /// HCLK = SYSCLK 设置系统设置
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /// PCLK2 = HCLK PCLK2时钟=主时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    // PCLK1 = HCLK/2 PCLK1时钟为主时钟1/2
    RCC_PCLK1Config(RCC_HCLK_Div2);
*/
    // PLLCLK = 8MHz * 3 = 24 MHz 设置时钟为24M
  //  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_3);
		
		
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_2);

    // Enable PLL 使能PLL
    RCC_PLLCmd(ENABLE);

    // Wait till PLL is ready 等待PLL工作稳定
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    // Select PLL as system clock source 选择PLL做为系统时钟源
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // Wait till PLL is used as system clock source 准备就绪，开始干活
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
  RCC_HSEConfig(RCC_HSE_ON);//使能外部时钟 

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待外部时钟就绪

  if(HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer 启用预取缓冲器 */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state FLASH设置2个等待周期*/
    FLASH_SetLatency(FLASH_Latency_2);
 
    /* HCLK = SYSCLK 设置系统设置*/
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK PCLK2时钟=主时钟*/
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 PCLK1时钟为主时钟1/2*/
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 3 = 24 MHz 设置时钟为24M*/
  RCC_PLLConfig(RCC_PLLSource_PREDIV1, RCC_PLLMul_3);
		
		//RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_3);

    /* Enable PLL 使能PLL*/ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready 等待PLL工作稳定*/
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source 选择PLL做为系统时钟源*/
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source 准备就绪，开始干活*/
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
	else RCC_Configuration();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
}

/*******************************************************************************
GPIO口的初始化设置和相关配置，主要是I/O口的输入输出模式 模式配置注意核查
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

   //PWR_BackupAccessCmd(ENABLE);
   //RCC_LSEConfig(RCC_LSE_OFF);
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);        //使能GPIO时钟使能，GPIOA和GPIOB时钟使能
	
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO ,ENABLE );
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);
	
//采样用的IO口的初始化
  GPIO_InitStructure.GPIO_Pin = RCLK_PIN | BEEP_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = PRT_DTR_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	                                                                                 
  GPIO_InitStructure.GPIO_Pin = DATA_PIN | SRCLK_PIN | PM51_START_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = PM51_OK_PIN | PM51_BUSY_PIN | PM51_FAIL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	
	PWR_BackupAccessCmd(ENABLE);
	RCC_LSEConfig(RCC_LSE_OFF);
	BKP_TamperPinCmd(DISABLE);
	BKP_ITConfig(DISABLE); 



	GPIO_InitStructure.GPIO_Pin = KEY1_PIN | KEY2_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	PWR_BackupAccessCmd(DISABLE);


	
	/*********************初始化串口IO配置**********************************/         //串口为何要这么配置

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
  //GPIO_Init(GPIOA, &GPIO_InitStructure);			 //设置PA10引脚模式
	/*****************************************************************************************************/
/*
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);			                                       //设置GPIO.PB12
*/
  

	PM51_START_ON;
}
/********************************************************************************/
void NVIC_Configuration(void)
{
   //#ifdef  VECT_TAB_RAM
#if defined (VECT_TAB_RAM)
   /* Set the Vector Table base location at 0x20000000 */ 
   NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); //设置中断向量在RAM中
   //#elif defined(VECT_TAB_FLASH_IAP)
   //  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);
#else  /* VECT_TAB_FLASH  */
   /* Set the Vector Table base location at 0x08000000 */ 
   NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x000000); //设置中断向量在FLASH中  
#endif
	
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
}
/*************************************************************************/

/**********************************************************************
* 名    称：USART_Configuration()
* 功    能：串口配置
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：串口初始化函数
***********************************************************************/
 void USART_Configuration(void)                        
{

	NVIC_InitTypeDef NVIC_InitStructure;
	
/* USART1 and USART1 configuration ------------------------------------------------------*/
  /* USART and USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */

  USART_InitTypeDef USART_InitStructure;
//  USART_ClockInitTypeDef  USART_InitClock;						//定义串口初始化时钟结构体

	/*
	  USART_InitClock.USART_Clock = USART_Clock_Disable; 				//串口时钟禁止
  USART_InitClock.USART_CPOL = USART_CPOL_Low; 					    //时钟下降沿有效
  USART_InitClock.USART_CPHA = USART_CPHA_2Edge;					//数据在第二个时钟沿捕捉
  USART_InitClock.USART_LastBit = USART_LastBit_Disable;			//最后数据位的时钟脉冲不输出到SCLK引脚
																	
  USART_ClockInit(USART1,&USART_InitClock);//初始化USART1外围时钟，按照 USART_ClockInitStruct 内的参数.
	*/
	
  USART_InitStructure.USART_BaudRate = 115200;
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
  
   __disable_irq();               //关闭总中断
	
    /**
    *  初始化定时器6
    */
   // Timer6_Configuration();
   /**
    * 初始化定时器2
    */
   
  // Timer2_Configuration();

      /**
    * 初始化定时器3
    */
     //  TIM3_Mode_Config();

      /**
    * 初始化定时器7
    */
  // Timer7_Configuration();

       /**
    *  初始化串口 
    */
  //  USART2_Init();
    /**
    *  初始化红外遥控 
    */
  // IR_Init();
    
    /**
    *  看门狗初始化
    */
   //IWDG_Init();

   //开总中断
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

