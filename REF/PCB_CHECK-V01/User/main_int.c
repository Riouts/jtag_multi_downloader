/*--------------------------------------------------------------------*/
/*
软件版本Ver1.4.1  硬件版本为PAPBK150030—VER1-4
请每次修改都作出相应的说明，并且需要验证2016年2月3日
主要目的是克服快要充满时的频繁重启动现象，注意苹果手机的特殊性问题
如果累计两次重启，则增加低电流持续时间

*/
/*
电流分段式控制2016年2月23日,克服输出端有其它负载导致线路压降降低情况
配合最新硬件的设计
*/
//其它说明if needed

/*--------------------------------------------------------------------*/
#include<main.h>
#include<math.h>
#include<stm32f10x_spi.h>
#include<bmp.h>
/*--------------------------------------------------------------------*/
#define BAT_Voltage_4V1     3358
#define BAT_Voltage_3V9     3194
#define BAT_Voltage_3V7     3031
#define BAT_Voltage_3V6     2949
#define BAT_Voltage_3V2     2621
#define PVol                4

#define PVol0                460

/*--------------------------------------------------------------------*/

unsigned char *P_RXD;//接收数据指针                        //IO口的模式配置在BSP_Config.c内进行
unsigned int Num_RXD=0;//要打印字节区位码的字节数

unsigned char TxBuffer[256]={0,2,3,};//串口发送缓冲区
unsigned char RxBuffer[256]; //串口接收缓冲区
unsigned char Key1_Value=1;
unsigned char Key2_Value=1;

uint8_t   Time2_500ms_OK = 0x00;
uint8_t   PWM_Switch_State = 0;
uint8_t   power_state = 0;                   /* 开关机状态标志位 */
uint8_t   cnt = 0;
uint8_t   OverVol_Flag = 0;
uint8_t   mppt = 6;                          //MPPT的初始值定为6，这个数值不宜过大
uint16_t  ADC_BAT_Voltage=0x00;              //内部电池电压采样
uint16_t  ADC_PV_Voltage=0;                  //PV电压采样
uint16_t  ADC_Temp_Voltage=0;                //温度采样，放在电池附近
uint16_t  ADC_Icharge_Voltage=0;             //充电电流采样
uint8_t   Leds_Light_TimeCnt=0x00;
uint8_t   Leds_Battery_TimeCnt=0x00;
uint8_t   Leds_PV_TimeCnt=0x00;
uint8_t   cnt1 = 0;
uint8_t   t;
uint8_t   i;
uint8_t   j;
uint16_t  t1 = 1;
uint8_t   t2 = 1;
uint8_t   t3 = 1;
uint8_t   t4 = 1;
uint16_t   Stop_Flag = 1;
uint8_t   start_flag = 0;
uint8_t   PWM[100];
uint16_t  t_off = 1;
uint8_t   Open_Flag = 0;
uint8_t   Run_Flag;
float     PV_Voltage;
float     BAT_Voltage;
float     Temp_Voltage;
float     Icharge_Voltage;
float     Icharge[100];
float     Icharge1[2];
uint8_t   Time2_500ms_Cnt = 0x00;
uint8_t   Key_UpD_Flg=0x00;
uint8_t   Load_ON_Flg=0x00;
uint16_t  led0pwmval=1;//0;
uint8_t   dir=0;                     //启动时更换为0，以克服超调，更改日期2016年2月3日
uint8_t   IN_PUT_State=0;

/**********************************************************************/
uint16_t adcx;
uint16_t adc_Upv;
uint16_t adc_Uout;
uint16_t adc_Ipv;
uint16_t adc_Iout;
float    temp;
float    Upv;
float    Uout;
float    Uout1;
float    Udes=0;;
float    Ipv;
float    Iout,Iout0;  
float    Iout1;

/*---------------------------------------------------------------------*/
void Led_Reflash_CHARGE1(void);
void GPIO_Configuration(void);
void TIM3_Configuration(void);
void USART_Configuration(void);
void delay100ms(void);
void delay5ms(void);
void delay1s(void);
void delay1ms(void);

void PWM_out_5V(void);
void PWM_out_12V(void);
void PWM_out_19V(void);
void Key_control(void);
void Get_AD_result(void);
void Led_control(void);
void Init_all(void);
/**************************************************************************/
void SPI2_Init(void);
void show_chinese(void);
void show_english(void);
/*--------------------------------------------------------------------*/ //主函数

int main(void)
{
  // u8 i1,j1;                                      //定义一系列变量及其初始化
  //	 ADC_InitTypeDef ADC_InitStructure;  
	//   delay100ms();
    SystemInit();
    RCC_Configuration();                 //STM32时钟初始化
    NVIC_Configuration();                //中断向量表设置
    GPIO_Configuration();                //单片机IO初始化
    Adc_Init();
    TIM3_Mode_Config();
    Exit_Configuration();
    Timer2_Configuration();
    USART_Configuration();  //USART1配置 
  //  SysTick_init();		     //延时初始化
    SPI2_Init(); 			     //初始化SPI硬件口
	  P_RXD=RxBuffer;//接收指针指向接收缓冲区
	/* Resets ADC1 */ 
    OLED_ON = 0x01;
    OLED_Init();			 //初始化OLED      
/*
				//	OLED_ShowString(1,0, "ADC' OLED TEST");  
						OLED_ShowString(16,0,"      WELCOME  ");  
				//	OLED_ShowString(24,16,"      TO  ");  
				//	OLED_ShowString(24,32,"     USE  ");
				//	OLED_ShowString(8,48,"   OUR  PRODUCT  ");
*/ 
						OLED_ShowCHinese(6,16,4);//电
						OLED_ShowCHinese(27,16,10);//压
						OLED_ShowString(48,16,"5.06V");  
						OLED_ShowCHinese(6,32,4);//电
						OLED_ShowCHinese(27,32,11);//流
						OLED_ShowString(48,32,"1.2A");  
/*
				//  OLED_ShowString(1,48,"2015-11-06");  
						OLED_ShowCHinese(10,48,12);//汉
						OLED_ShowCHinese(30,48,13);//能
						OLED_ShowCHinese(80,48,18);//联
						OLED_ShowCHinese(100,48,19);//创
*/
/*
				{                             //永久显示内容
						OLED_ShowString(1,0,"Hanergy.Co.Ltd  ");  

						OLED_ShowCHinese(10,48,12);//汉
						OLED_ShowCHinese(30,48,13);//能
						OLED_ShowCHinese(80,48,18);//联
						OLED_ShowCHinese(100,48,19);//创
				}
				*/
		LED4=0x00;        
    LED3=0x00;        
    LED2=0x00;        
    LED1=0x00;  
		Load_ON=0x01;                 //输出默认关闭
		Dummy_Load=0x01;              //假负载默认开启
  /* Infinite loop */
	 delay5ms();
				Iout0=0.14;

/*Dummy_Load=0x00;   
	for(i=0;i<20;i++)
	{
		 TIM_SetCompare2(TIM3,i);
		 delay1s();
				 adc_Uout     = Get_Adc_Average(2,10);
				 Uout         = 11*((float)adc_Uout*(3.3/4096));	//输出电压采样		
				 adc_Iout     =  Get_Adc_Average(3,20);          //采样次数可以酌情减少
			   Iout         =  1*((float)adc_Iout*(3.3/4096))/0.4;//-0.005;	
		
							show_chinese();
					 OLED_ShowNum(48,48,i,3,16);		 
		delay1s();
		delay1s();
		
	}
	*/
	LED1=1;
	delay5ms();
	delay5ms();
	delay5ms();
	delay5ms();
	LED1=0;
 //  TIM_SetCompare2(TIM3,10);
//Dummy_Load=0x01;   
//  while (1);

   while (1)
   {
		 LED1=1;
		 
		 	 PWM_out_5V(); 
		   t1++;
		   if(t1>300)//1018)
			   {
							t1=1;
							t2++;
					 //   LED4=~LED4;
					 //   TIM_SetCompare2(TIM3,++led0pwmval);                       //该条语句是否需要，需要斟酌
/*---------------------------------------------------------------------------*/
	//第一阶段，假负载打开，真负载关闭		
							if(Dummy_Load==0x01)
								{
									 if((adc_Iout>50)&&(adc_Uout>541)&&(Dummy_Load==0x01))      //0.16看具体情况 , 0.16的情况下，很多不通过改为0.14    //极个别采样不准的可以放到0.12
										 {
												t3++;
												Open_Flag++;
										 }
										if((adc_Iout<50)&&(Dummy_Load==0x01))
												Open_Flag  = 0x01;
										if(Open_Flag>3)
										 {
												Dummy_Load = 0x00;              //打开假负载	
											  delay5ms();
											//  LED1       = 0x01;
												Load_ON    = 0x00;              //输出电流太小，关闭输出
												Open_Flag  = 0x01;				 
										 }
								}  	 
						
							
				  }
	/*	
					if(t2>4)                              //液晶屏扫描间隔时间控制
				 {
							OLED_Clear1();
							show_chinese();
					 OLED_ShowNum(48,48,led0pwmval,3,16);
							t2=1;
					    start_flag=0;
		     }	
*/
					
/****************************************************/  //AD采样程式
				 adc_Upv      = Get_Adc_Average(1,6);
			//	 Upv          = 11*((float)adc_Upv*(3.3/4096));	  //PV电压采样
				 adc_Uout     = Get_Adc_Average(2,6);
			//	 Uout         = 11*((float)adc_Uout*(3.3/4096));	//输出电压采样			 
				// if((Uout<4.9)&&(start_flag==0))
					if((adc_Uout<553)&&(start_flag==0))
				 {
					 if(led0pwmval<98)
					 {
						  led0pwmval+=2;
							TIM_SetCompare2(TIM3,led0pwmval);
					 }
			//			 TIM_SetCompare2(TIM3,60);  
				//		 led0pwmval=60;
						 start_flag=1;
				 }
				 adc_Iout     =  Get_Adc_Average(3,18);          //采样次数可以酌情减少
			 //  Iout         =  1*((float)adc_Iout*(3.3/4096))/0.4;//-0.005;	
				 
			//	 Iout+=Iout0;
		//		 Iout/=2;
		//		 Iout0=Iout;
				 
		          //电流采样需要校准或者进行采样电阻的进一步精度要求0.1%
		//		 if(Iout>2.5)   //2.2                               //输出过流保护
				 if(adc_Iout>1241)
				 {
						 TIM_SetCompare2(TIM3,10); 	 
				 }
	
					 
				 
				 
/*---------------------------------------------------------------------------*/	
//第二阶段，真负载打开，假负载关闭,兼顾空载情况，若是输出能力充足，空载下会一直输出		  		 
		  if(Dummy_Load==0x00)
		   {
					// if((Iout>0.06)&&(Iout<0.45)&&(Upv<5.8)&&(Dummy_Load==0x00))
		//				 if((Iout>0.06)&&(Iout<0.4)&&(Dummy_Load==0x00))
					if((adc_Iout>30)&&(adc_Iout<199)&&(Dummy_Load==0x00))
							 {
								    t_off++;
							 }
					// if((Iout>0.45)&&(Dummy_Load==0x00))
						if((adc_Iout>223)&&(Dummy_Load==0x00))
							 t_off=0x01;
					 if(t_off>600)//2016)
					     {
									 Stop_Flag++;
								   t_off=0x01;
						   }
						if(cnt<3)
						   {
								 if(Stop_Flag>236)
										 {
												 Load_ON     = 0x01;              //输出电流太小，关闭输出	
												 LED1        = 0x00;								 
												 Dummy_Load  = 0x01;              //打开假负载		
												 Stop_Flag   = 0x01;					 
												 cnt++;
										 }
						   }
							else
							 {
								 if(Stop_Flag>1036)
										 {
												 Load_ON     = 0x01;              //输出电流太小，关闭输出	
												 LED1        = 0x00;								 
												 Dummy_Load  = 0x01;              //打开假负载		
												 Stop_Flag   = 0x01;					 
												 cnt++;
										 } 
							  }
			  }
			 
				if(cnt>6)
					cnt=0;
			 
				LED1=0;

				
				delay1ms();
	
			
/*---------------------------------------------------------------------------*/				 
    }
}

//主函数结束
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_chinese(void)
{       
						OLED_ShowCHinese(6,16,4);//电
						OLED_ShowCHinese(27,16,10);//压
					  OLED_ShowString(42,16,":");  
					  OLED_ShowString(70,16,".");  
					  OLED_ShowString(110,16,"V");  
						Uout1=Uout;
						adcx=Uout1;
						OLED_ShowNum(46,16,adcx,3,16);//??ASCII??	   	OLED_Refresh_Gram();//显示电压值整数部分
						Uout1-=adcx;
						Uout1*=1000;
						OLED_ShowNum(80,16,Uout1,3,16);//??ASCII????? 
	          if(Uout1<100)
               OLED_ShowString(80,16,"0"); 
				    if(Uout1<10)
					     OLED_ShowString(88,16,"0");	
						OLED_ShowCHinese(6,32,4);//电
						OLED_ShowCHinese(27,32,11);//流
					  OLED_ShowString(42,32,":");  
					  OLED_ShowString(70,32,"."); 
					  OLED_ShowString(110,32,"A"); 
						Iout1=Iout;
						adcx=Iout1;
						OLED_ShowNum(46,32,adcx,3,16);//??ASCII??	   	OLED_Refresh_Gram();//显示电流值整数部分   
						Iout1-=adcx;
						Iout1*=1000;
				    OLED_ShowNum(80,32,Iout1,3,16);//??ASCII????? 
	          if(Iout1<100)		
				       OLED_ShowString(80,32,"0"); 
				    if(Iout1<10)
					     OLED_ShowString(88,32,"0");
			  	//LEDA=!LEDA;
}
void show_english(void)
{
				{
				 //   OLED_Init();			 //初始化OLED      
						OLED_ShowString(1,0, "ADC' OLED TEST");        //第一行的显示
						OLED_ShowString(1,16,"Hanergy.Co.Ltd  ");      //第二行的显示
						OLED_ShowString(1,32,"2015-08-13");            //第三行的显示
						OLED_ShowString(1,48,"CH0_DCV: ");             //第四行的显示
					//	OLED_ShowString(63,48,"_VOL: ");   
						OLED_ShowString(110,48,"V. ");                 //第四行的显示
				}
}


//按下按键，则显示大概5S左右的当前电量，
void Key_control(void)
{
				if(Key_UpD_Flg==0x01) 
				  {
						    if(t1>2)
								// Led_Reflash_UNCHARGE();
                // for(t=0;t<5;t++)	
                 delay100ms();
						     if(t1%32==0)
                 Key_UpD_Flg=0x00;							
					}	
         else
			    { LED4=0x01;    LED3=0x01;     LED2=0x01;       LED1=0x01;		}					 
}

/*--------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////
void PWM_out_5V(void)
{
			 // 		if((Upv>PVol)||(Upv==PVol))
						if((adc_Upv>PVol0)||(adc_Upv==PVol0))
							{							
/*********************************************************/  //判断占空因数的变化趋势
							//5V的判断
								 {
										PWM_Switch_State = 0x01;
									 if((adc_Iout<745)||(adc_Iout==745))
										 {
													if((adc_Uout>598)||(adc_Uout==598))
														dir = 0;
													if((adc_Uout<581)||(adc_Uout==5.15))
														dir=1;
													if((adc_Uout>581)&&(adc_Uout<598))
														dir = 2;
										 }
									 if(adc_Iout>745)
										 {
													if((adc_Uout>609)||(adc_Uout==609))
														dir = 0;
													if((adc_Uout<592)||(adc_Uout==592))
														dir=1;
													if((adc_Uout>592)&&(adc_Uout<609))
														dir = 2;
										 }
										
										if(dir==0)
											if(led0pwmval>0)led0pwmval--;
										if(dir==1)
	//										led0pwmval=led0pwmval+5;
										  led0pwmval++;
										else
											;
								 }
/*************************************************************/	//判断PWM的输出上限和下限，从0到99可调
								if(led0pwmval>100)
									led0pwmval=100;
							//	if(led0pwmval<1)
						//			led0pwmval=1;
								
/*************************************************************/ //保护策略，输出过压和过流保护
								if(((adc_Uout>608)&&(adc_Iout<=745))||((adc_Uout>618)&&(adc_Iout>745)))
								{
									if(led0pwmval>1)
									{
										led0pwmval-=2;
						      	//TIM_SetCompare2(TIM3,led0pwmval);                    //暂时先固定输出一个占空比
										
									}
									else led0pwmval=0;
									TIM_SetCompare2(TIM3,led0pwmval); 
								}
								/*
								else if ((Upv<5.6)&&(led0pwmval==100))
								    {
								       TIM_SetCompare2(TIM3,50);                    //暂时先固定输出一个占空比  相当于设置一个跳转
											 led0pwmval=50;
										}
               */
								    
								else
							      TIM_SetCompare2(TIM3,led0pwmval);           //改变占空比
							}
             else
							TIM_SetCompare2(TIM3,0);          //暂时先固定输出一个占空比
}

//////////////////////////////////////////////////////////后来写的，导致系统不稳定

/*
void PWM_out_5V(void)                                        //抬高输出电压，以此来增加输出电流能力
{
			  		if((Upv>PVol)||(Upv==PVol))
							{							

							//5V的判断
								 {
										PWM_Switch_State = 0x01;
									  
//									 if((Iout<1.12)||(Iout==1.12))
//										 {
//													if((Uout>(5.32+Udes))||(Uout==(5.32+Udes)))
//														dir = 0;
//													if((Uout<(5.18+Udes))||(Uout==(5.18+Udes)))
//														dir=1;
//													if((Uout>(5.18+Udes))&&(Uout<(5.32+Udes)))
//														dir = 2;
//										 }
									 if((Iout<1.12)||(Iout==1.12))
										 {
													if((Uout>5.26)||(Uout==5.26))
														dir = 0;
													if((Uout<5.18)||(Uout==5.18))
														dir=1;
													if((Uout>5.18)&&(Uout<5.26))
														dir = 2;
										 }
									 if(Iout>1.12)
										 {
													if((Uout>5.36)||(Uout==5.36))
														dir = 0;
													if((Uout<5.25)||(Uout==5.25))
														dir=1;
													if((Uout>5.25)&&(Uout<5.36))
														dir = 2;
										 }
										
										if(dir==0)
											led0pwmval--;
										if(dir==1)
	//										led0pwmval=led0pwmval+5;
										  led0pwmval++;
										else
											;
								 }

								if(led0pwmval>100)
									led0pwmval=100;
								if(led0pwmval<1)
									led0pwmval=1;
								

								if(((Uout>5.36)&&(Iout<1.1))||((Uout>5.42)&&(Iout>1.1)))
//								if(Uout>5.39)
								{
									//  OverVol_Flag++;
									//  if(OverVol_Flag>2)
										{
									//	  OverVol_Flag=0;
						      	  TIM_SetCompare2(TIM3,0);                    //暂时先固定输出一个占空比
										}
								}
								
//								else if ((Upv<5.6)&&(led0pwmval==100))
//								    {
//								       TIM_SetCompare2(TIM3,50);                    //暂时先固定输出一个占空比  相当于设置一个跳转
//											 led0pwmval=50;
//										}
               
								    
								else
								{
							      TIM_SetCompare2(TIM3,led0pwmval);           //改变占空比
								//  OverVol_Flag=0;
								}
							}
             else
							TIM_SetCompare2(TIM3,0);          //暂时先固定输出一个占空比
}

*/

void PWM_out_12V(void)
{
			  		if((Upv>10)||(Upv==10))
							{
/*********************************************************/  //判断占空因数的变化趋势
								PWM_Switch_State = 0x01;
						//		PWM_control2();               //定电压控制算法，快速性最好，精度不高
						//		PWM_control1();               //全扫描控制算法，快速性一般，精度较高，占用时序多
						//		PWM_control();                 //扰动观察法，快速性较好，精度较高，占用时序少
						//		PWM_control(); 
						//	TIM_SetCompare2(TIM3,30);          //暂时先固定输出一个占空比
								if((Uout>12.15)||(Uout==12.15))
									dir = 0;
								if((Uout<11.9)||(Uout==11.9))
									dir=1;
								if((Uout>11.9)&&(Uout<12.15))
									dir = 2;
								if(dir==0)
									led0pwmval--;
								if(dir==1)
									led0pwmval++;
								else
									;
/*************************************************************/	//判断PWM的输出上限和下限，从0到99可调
								if(led0pwmval>100)
									led0pwmval=100;
								if(led0pwmval<1)
									led0pwmval=1;
								
/*************************************************************/ //保护策略，输出过压和过流保护
								if(Uout>12.26)
						      	TIM_SetCompare2(TIM3,0);                    //暂时先固定输出一个占空比
								else if ((Uout<10.6)&&(led0pwmval==100))
						      	TIM_SetCompare2(TIM3,30);                    //暂时先固定输出一个占空比  
								else
							      TIM_SetCompare2(TIM3,led0pwmval);           //改变占空比
							}
             else
							TIM_SetCompare2(TIM3,0);          //暂时先固定输出一个占空比
}

void PWM_out_19V(void)
{
			  		if((Upv>16)||(Upv==16))
							{
/*********************************************************/  //判断占空因数的变化趋势
								PWM_Switch_State = 0x01;
						//		PWM_control2();               //定电压控制算法，快速性最好，精度不高
						//		PWM_control1();               //全扫描控制算法，快速性一般，精度较高，占用时序多
						//		PWM_control();                 //扰动观察法，快速性较好，精度较高，占用时序少
						//		PWM_control(); 
						//	TIM_SetCompare2(TIM3,30);          //暂时先固定输出一个占空比
								if((Uout>19.15)||(Uout==19.15))
									dir = 0;
								if((Uout<18.9)||(Uout==18.9))
									dir=1;
								if((Uout>18.9)&&(Uout<19.15))
									dir = 2;
								if(dir==0)
									led0pwmval--;
								if(dir==1)
									led0pwmval++;
								else
									;
/*************************************************************/	//判断PWM的输出上限和下限，从0到99可调
								if(led0pwmval>100)
									led0pwmval=100;
								if(led0pwmval<1)
									led0pwmval=1;
								
/*************************************************************/ //保护策略，输出过压和过流保护
								if(Uout>19.26)
						      	TIM_SetCompare2(TIM3,0);                    //暂时先固定输出一个占空比
								else if ((Uout<16)&&(led0pwmval==100))
						      	TIM_SetCompare2(TIM3,30);                    //暂时先固定输出一个占空比  
								else
							      TIM_SetCompare2(TIM3,led0pwmval);           //改变占空比
							}
             else
							TIM_SetCompare2(TIM3,0);          //暂时先固定输出一个占空比
}


/*---------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------*/
void Led_control(void)
{
				if((PV_Voltage>PVol)||(PV_Voltage==PVol)||(IN_PUT_State == 1))

				    ;
				else
						{	
						 Key_control();				 
						}		
}


/*------------------------------------------------------------------------------------------------*/
void Led_Reflash_CHARGE1(void)
{
	  if(Time2_500ms_OK==0x01)
     {
			  Time2_500ms_OK=0x00;
			  Time2_500ms_Cnt++;  
	     {
           if(Time2_500ms_Cnt==1)
					 { 
             LED4=0x01;        
             LED3=0x01;  
 						 LED2=0x01;        
             LED1=0x01; 
					 } 
	       	 if(Time2_500ms_Cnt==2)
					 { 
             LED4=0x00;        
             LED3=0x01;
						 LED2=0x01;
						 LED1=0x01; 
             						 
					 } 
					 if(Time2_500ms_Cnt==3)
					 { 
             LED4=0x00;        
             LED3=0x00;
						 LED2=0x01;
						 LED1=0x01; 
             						 
					 } 
					 if(Time2_500ms_Cnt==4)
					 { 
             LED4=0x00;        
             LED3=0x00;
						 LED2=0x00;
						 LED1=0x01;  						 
					 } 
					 if(Time2_500ms_Cnt==5)
					 { 
             LED4=0x00;        
             LED3=0x00;
						 LED2=0x00;
						 LED1=0x00;  						 
					 } 
           if(Time2_500ms_Cnt>=5)
					 {
					   Time2_500ms_Cnt=0;
					 }
	       }
		}
}
void SPI2_Init(void)           //硬件SPI2口初始化

{
  SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable SPI2 and GPIOB clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE) ;//使能SPI2的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//使能IO口时钟
  /* Configure SPI2 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure PB.12 as Output push-pull, used as Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB, GPIO_Pin_12);//片选信号为低
  
  /* SPI1 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //时钟悬空高
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//数据捕获于第二个时钟沿
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	//内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//波特率预分频值为2
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7; //SPI_CRCPolynomial定义了用于CRC值计算的多项式
  SPI_Init(SPI2, &SPI_InitStructure);
  
  /* Enable SPI2  */
  SPI_Cmd(SPI2, ENABLE);
}
/*--------------------------------------------------------------------------------------------------*/
/***********功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/


/*-----------------------------------------------------------------------------------*/
//程序代码段结束



