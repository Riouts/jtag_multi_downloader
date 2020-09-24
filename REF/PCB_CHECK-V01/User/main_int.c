/*--------------------------------------------------------------------*/
/*
����汾Ver1.4.1  Ӳ���汾ΪPAPBK150030��VER1-4
��ÿ���޸Ķ�������Ӧ��˵����������Ҫ��֤2016��2��3��
��ҪĿ���ǿ˷���Ҫ����ʱ��Ƶ������������ע��ƻ���ֻ�������������
����ۼ����������������ӵ͵�������ʱ��

*/
/*
�����ֶ�ʽ����2016��2��23��,�˷���������������ص�����·ѹ���������
�������Ӳ�������
*/
//����˵��if needed

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

unsigned char *P_RXD;//��������ָ��                        //IO�ڵ�ģʽ������BSP_Config.c�ڽ���
unsigned int Num_RXD=0;//Ҫ��ӡ�ֽ���λ����ֽ���

unsigned char TxBuffer[256]={0,2,3,};//���ڷ��ͻ�����
unsigned char RxBuffer[256]; //���ڽ��ջ�����
unsigned char Key1_Value=1;
unsigned char Key2_Value=1;

uint8_t   Time2_500ms_OK = 0x00;
uint8_t   PWM_Switch_State = 0;
uint8_t   power_state = 0;                   /* ���ػ�״̬��־λ */
uint8_t   cnt = 0;
uint8_t   OverVol_Flag = 0;
uint8_t   mppt = 6;                          //MPPT�ĳ�ʼֵ��Ϊ6�������ֵ���˹���
uint16_t  ADC_BAT_Voltage=0x00;              //�ڲ���ص�ѹ����
uint16_t  ADC_PV_Voltage=0;                  //PV��ѹ����
uint16_t  ADC_Temp_Voltage=0;                //�¶Ȳ��������ڵ�ظ���
uint16_t  ADC_Icharge_Voltage=0;             //����������
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
uint8_t   dir=0;                     //����ʱ����Ϊ0���Կ˷���������������2016��2��3��
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
/*--------------------------------------------------------------------*/ //������

int main(void)
{
  // u8 i1,j1;                                      //����һϵ�б��������ʼ��
  //	 ADC_InitTypeDef ADC_InitStructure;  
	//   delay100ms();
    SystemInit();
    RCC_Configuration();                 //STM32ʱ�ӳ�ʼ��
    NVIC_Configuration();                //�ж�����������
    GPIO_Configuration();                //��Ƭ��IO��ʼ��
    Adc_Init();
    TIM3_Mode_Config();
    Exit_Configuration();
    Timer2_Configuration();
    USART_Configuration();  //USART1���� 
  //  SysTick_init();		     //��ʱ��ʼ��
    SPI2_Init(); 			     //��ʼ��SPIӲ����
	  P_RXD=RxBuffer;//����ָ��ָ����ջ�����
	/* Resets ADC1 */ 
    OLED_ON = 0x01;
    OLED_Init();			 //��ʼ��OLED      
/*
				//	OLED_ShowString(1,0, "ADC' OLED TEST");  
						OLED_ShowString(16,0,"      WELCOME  ");  
				//	OLED_ShowString(24,16,"      TO  ");  
				//	OLED_ShowString(24,32,"     USE  ");
				//	OLED_ShowString(8,48,"   OUR  PRODUCT  ");
*/ 
						OLED_ShowCHinese(6,16,4);//��
						OLED_ShowCHinese(27,16,10);//ѹ
						OLED_ShowString(48,16,"5.06V");  
						OLED_ShowCHinese(6,32,4);//��
						OLED_ShowCHinese(27,32,11);//��
						OLED_ShowString(48,32,"1.2A");  
/*
				//  OLED_ShowString(1,48,"2015-11-06");  
						OLED_ShowCHinese(10,48,12);//��
						OLED_ShowCHinese(30,48,13);//��
						OLED_ShowCHinese(80,48,18);//��
						OLED_ShowCHinese(100,48,19);//��
*/
/*
				{                             //������ʾ����
						OLED_ShowString(1,0,"Hanergy.Co.Ltd  ");  

						OLED_ShowCHinese(10,48,12);//��
						OLED_ShowCHinese(30,48,13);//��
						OLED_ShowCHinese(80,48,18);//��
						OLED_ShowCHinese(100,48,19);//��
				}
				*/
		LED4=0x00;        
    LED3=0x00;        
    LED2=0x00;        
    LED1=0x00;  
		Load_ON=0x01;                 //���Ĭ�Ϲر�
		Dummy_Load=0x01;              //�ٸ���Ĭ�Ͽ���
  /* Infinite loop */
	 delay5ms();
				Iout0=0.14;

/*Dummy_Load=0x00;   
	for(i=0;i<20;i++)
	{
		 TIM_SetCompare2(TIM3,i);
		 delay1s();
				 adc_Uout     = Get_Adc_Average(2,10);
				 Uout         = 11*((float)adc_Uout*(3.3/4096));	//�����ѹ����		
				 adc_Iout     =  Get_Adc_Average(3,20);          //�������������������
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
					 //   TIM_SetCompare2(TIM3,++led0pwmval);                       //��������Ƿ���Ҫ����Ҫ����
/*---------------------------------------------------------------------------*/
	//��һ�׶Σ��ٸ��ش򿪣��渺�عر�		
							if(Dummy_Load==0x01)
								{
									 if((adc_Iout>50)&&(adc_Uout>541)&&(Dummy_Load==0x01))      //0.16��������� , 0.16������£��ܶ಻ͨ����Ϊ0.14    //�����������׼�Ŀ��Էŵ�0.12
										 {
												t3++;
												Open_Flag++;
										 }
										if((adc_Iout<50)&&(Dummy_Load==0x01))
												Open_Flag  = 0x01;
										if(Open_Flag>3)
										 {
												Dummy_Load = 0x00;              //�򿪼ٸ���	
											  delay5ms();
											//  LED1       = 0x01;
												Load_ON    = 0x00;              //�������̫С���ر����
												Open_Flag  = 0x01;				 
										 }
								}  	 
						
							
				  }
	/*	
					if(t2>4)                              //Һ����ɨ����ʱ�����
				 {
							OLED_Clear1();
							show_chinese();
					 OLED_ShowNum(48,48,led0pwmval,3,16);
							t2=1;
					    start_flag=0;
		     }	
*/
					
/****************************************************/  //AD������ʽ
				 adc_Upv      = Get_Adc_Average(1,6);
			//	 Upv          = 11*((float)adc_Upv*(3.3/4096));	  //PV��ѹ����
				 adc_Uout     = Get_Adc_Average(2,6);
			//	 Uout         = 11*((float)adc_Uout*(3.3/4096));	//�����ѹ����			 
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
				 adc_Iout     =  Get_Adc_Average(3,18);          //�������������������
			 //  Iout         =  1*((float)adc_Iout*(3.3/4096))/0.4;//-0.005;	
				 
			//	 Iout+=Iout0;
		//		 Iout/=2;
		//		 Iout0=Iout;
				 
		          //����������ҪУ׼���߽��в�������Ľ�һ������Ҫ��0.1%
		//		 if(Iout>2.5)   //2.2                               //�����������
				 if(adc_Iout>1241)
				 {
						 TIM_SetCompare2(TIM3,10); 	 
				 }
	
					 
				 
				 
/*---------------------------------------------------------------------------*/	
//�ڶ��׶Σ��渺�ش򿪣��ٸ��عر�,��˿����������������������㣬�����»�һֱ���		  		 
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
												 Load_ON     = 0x01;              //�������̫С���ر����	
												 LED1        = 0x00;								 
												 Dummy_Load  = 0x01;              //�򿪼ٸ���		
												 Stop_Flag   = 0x01;					 
												 cnt++;
										 }
						   }
							else
							 {
								 if(Stop_Flag>1036)
										 {
												 Load_ON     = 0x01;              //�������̫С���ر����	
												 LED1        = 0x00;								 
												 Dummy_Load  = 0x01;              //�򿪼ٸ���		
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

//����������
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void show_chinese(void)
{       
						OLED_ShowCHinese(6,16,4);//��
						OLED_ShowCHinese(27,16,10);//ѹ
					  OLED_ShowString(42,16,":");  
					  OLED_ShowString(70,16,".");  
					  OLED_ShowString(110,16,"V");  
						Uout1=Uout;
						adcx=Uout1;
						OLED_ShowNum(46,16,adcx,3,16);//??ASCII??	   	OLED_Refresh_Gram();//��ʾ��ѹֵ��������
						Uout1-=adcx;
						Uout1*=1000;
						OLED_ShowNum(80,16,Uout1,3,16);//??ASCII????? 
	          if(Uout1<100)
               OLED_ShowString(80,16,"0"); 
				    if(Uout1<10)
					     OLED_ShowString(88,16,"0");	
						OLED_ShowCHinese(6,32,4);//��
						OLED_ShowCHinese(27,32,11);//��
					  OLED_ShowString(42,32,":");  
					  OLED_ShowString(70,32,"."); 
					  OLED_ShowString(110,32,"A"); 
						Iout1=Iout;
						adcx=Iout1;
						OLED_ShowNum(46,32,adcx,3,16);//??ASCII??	   	OLED_Refresh_Gram();//��ʾ����ֵ��������   
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
				 //   OLED_Init();			 //��ʼ��OLED      
						OLED_ShowString(1,0, "ADC' OLED TEST");        //��һ�е���ʾ
						OLED_ShowString(1,16,"Hanergy.Co.Ltd  ");      //�ڶ��е���ʾ
						OLED_ShowString(1,32,"2015-08-13");            //�����е���ʾ
						OLED_ShowString(1,48,"CH0_DCV: ");             //�����е���ʾ
					//	OLED_ShowString(63,48,"_VOL: ");   
						OLED_ShowString(110,48,"V. ");                 //�����е���ʾ
				}
}


//���°���������ʾ���5S���ҵĵ�ǰ������
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
/*********************************************************/  //�ж�ռ�������ı仯����
							//5V���ж�
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
/*************************************************************/	//�ж�PWM��������޺����ޣ���0��99�ɵ�
								if(led0pwmval>100)
									led0pwmval=100;
							//	if(led0pwmval<1)
						//			led0pwmval=1;
								
/*************************************************************/ //�������ԣ������ѹ�͹�������
								if(((adc_Uout>608)&&(adc_Iout<=745))||((adc_Uout>618)&&(adc_Iout>745)))
								{
									if(led0pwmval>1)
									{
										led0pwmval-=2;
						      	//TIM_SetCompare2(TIM3,led0pwmval);                    //��ʱ�ȹ̶����һ��ռ�ձ�
										
									}
									else led0pwmval=0;
									TIM_SetCompare2(TIM3,led0pwmval); 
								}
								/*
								else if ((Upv<5.6)&&(led0pwmval==100))
								    {
								       TIM_SetCompare2(TIM3,50);                    //��ʱ�ȹ̶����һ��ռ�ձ�  �൱������һ����ת
											 led0pwmval=50;
										}
               */
								    
								else
							      TIM_SetCompare2(TIM3,led0pwmval);           //�ı�ռ�ձ�
							}
             else
							TIM_SetCompare2(TIM3,0);          //��ʱ�ȹ̶����һ��ռ�ձ�
}

//////////////////////////////////////////////////////////����д�ģ�����ϵͳ���ȶ�

/*
void PWM_out_5V(void)                                        //̧�������ѹ���Դ������������������
{
			  		if((Upv>PVol)||(Upv==PVol))
							{							

							//5V���ж�
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
						      	  TIM_SetCompare2(TIM3,0);                    //��ʱ�ȹ̶����һ��ռ�ձ�
										}
								}
								
//								else if ((Upv<5.6)&&(led0pwmval==100))
//								    {
//								       TIM_SetCompare2(TIM3,50);                    //��ʱ�ȹ̶����һ��ռ�ձ�  �൱������һ����ת
//											 led0pwmval=50;
//										}
               
								    
								else
								{
							      TIM_SetCompare2(TIM3,led0pwmval);           //�ı�ռ�ձ�
								//  OverVol_Flag=0;
								}
							}
             else
							TIM_SetCompare2(TIM3,0);          //��ʱ�ȹ̶����һ��ռ�ձ�
}

*/

void PWM_out_12V(void)
{
			  		if((Upv>10)||(Upv==10))
							{
/*********************************************************/  //�ж�ռ�������ı仯����
								PWM_Switch_State = 0x01;
						//		PWM_control2();               //����ѹ�����㷨����������ã����Ȳ���
						//		PWM_control1();               //ȫɨ������㷨��������һ�㣬���Ƚϸߣ�ռ��ʱ���
						//		PWM_control();                 //�Ŷ��۲취�������ԽϺã����Ƚϸߣ�ռ��ʱ����
						//		PWM_control(); 
						//	TIM_SetCompare2(TIM3,30);          //��ʱ�ȹ̶����һ��ռ�ձ�
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
/*************************************************************/	//�ж�PWM��������޺����ޣ���0��99�ɵ�
								if(led0pwmval>100)
									led0pwmval=100;
								if(led0pwmval<1)
									led0pwmval=1;
								
/*************************************************************/ //�������ԣ������ѹ�͹�������
								if(Uout>12.26)
						      	TIM_SetCompare2(TIM3,0);                    //��ʱ�ȹ̶����һ��ռ�ձ�
								else if ((Uout<10.6)&&(led0pwmval==100))
						      	TIM_SetCompare2(TIM3,30);                    //��ʱ�ȹ̶����һ��ռ�ձ�  
								else
							      TIM_SetCompare2(TIM3,led0pwmval);           //�ı�ռ�ձ�
							}
             else
							TIM_SetCompare2(TIM3,0);          //��ʱ�ȹ̶����һ��ռ�ձ�
}

void PWM_out_19V(void)
{
			  		if((Upv>16)||(Upv==16))
							{
/*********************************************************/  //�ж�ռ�������ı仯����
								PWM_Switch_State = 0x01;
						//		PWM_control2();               //����ѹ�����㷨����������ã����Ȳ���
						//		PWM_control1();               //ȫɨ������㷨��������һ�㣬���Ƚϸߣ�ռ��ʱ���
						//		PWM_control();                 //�Ŷ��۲취�������ԽϺã����Ƚϸߣ�ռ��ʱ����
						//		PWM_control(); 
						//	TIM_SetCompare2(TIM3,30);          //��ʱ�ȹ̶����һ��ռ�ձ�
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
/*************************************************************/	//�ж�PWM��������޺����ޣ���0��99�ɵ�
								if(led0pwmval>100)
									led0pwmval=100;
								if(led0pwmval<1)
									led0pwmval=1;
								
/*************************************************************/ //�������ԣ������ѹ�͹�������
								if(Uout>19.26)
						      	TIM_SetCompare2(TIM3,0);                    //��ʱ�ȹ̶����һ��ռ�ձ�
								else if ((Uout<16)&&(led0pwmval==100))
						      	TIM_SetCompare2(TIM3,30);                    //��ʱ�ȹ̶����һ��ռ�ձ�  
								else
							      TIM_SetCompare2(TIM3,led0pwmval);           //�ı�ռ�ձ�
							}
             else
							TIM_SetCompare2(TIM3,0);          //��ʱ�ȹ̶����һ��ռ�ձ�
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
void SPI2_Init(void)           //Ӳ��SPI2�ڳ�ʼ��

{
  SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
  /* Enable SPI2 and GPIOB clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE) ;//ʹ��SPI2��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��IO��ʱ��
  /* Configure SPI2 pins: SCK, MISO and MOSI */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Configure PB.12 as Output push-pull, used as Flash Chip select */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_ResetBits(GPIOB, GPIO_Pin_12);//Ƭѡ�ź�Ϊ��
  
  /* SPI1 configuration */ 
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI����Ϊ˫��˫��ȫ˫��
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;	 //����Ϊ��SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;	//SPI���ͽ���8λ֡�ṹ
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //ʱ�����ո�
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//���ݲ����ڵڶ���ʱ����
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;	//�ڲ�NSS�ź���SSIλ����
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;//������Ԥ��ƵֵΪ2
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;//���ݴ����MSBλ��ʼ
  SPI_InitStructure.SPI_CRCPolynomial = 7; //SPI_CRCPolynomial����������CRCֵ����Ķ���ʽ
  SPI_Init(SPI2, &SPI_InitStructure);
  
  /* Enable SPI2  */
  SPI_Cmd(SPI2, ENABLE);
}
/*--------------------------------------------------------------------------------------------------*/
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/


/*-----------------------------------------------------------------------------------*/
//�������ν���



