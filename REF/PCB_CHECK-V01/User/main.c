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

// �ܽŶ���: AD�ܽţ�  V14_AD:ADC1-1; I_V14:ADC1-3; PV+_AD:ADC1-4; I_PVin:ADC1-5; I_out:ADC1-6; BAT_AD:ADC1-8(PB0); TEMP_AD:ADC1-9(PB1); 
// �ܽŶ���: ����ܽţ�V14_ONOFF:PA2; PWMCTR��PA7;  LOAD_ON: PA11; LED_G: PA12;   LED_R:PA15;   DUMMY_LOAD:PB14;

/*--------------------------------------------------------------------*/
#include<main.h>
#include<math.h>
#include<stm32f10x_spi.h>
#include<bmp.h>
/*--------------------------------------------------------------------*/

/*
#define BAT_Voltage_4V1     3358
#define BAT_Voltage_3V9     3194
#define BAT_Voltage_3V7     3031
#define BAT_Voltage_3V6     2949
#define BAT_Voltage_3V2     2621
#define PVol                4.7//5 //4

#define PVol0                460

#define PWM_START            1
#define PWM_END		           61
*/
/*--------------------------------------------------------------------*/

/*
unsigned char *P_RXD;//��������ָ��                        //IO�ڵ�ģʽ������BSP_Config.c�ڽ���
unsigned int Num_RXD=0;//Ҫ��ӡ�ֽ���λ����ֽ���

//unsigned char TxBuffer[256]={0,2,3,};//���ڷ��ͻ�����
//unsigned char RxBuffer[256]; //���ڽ��ջ�����
unsigned char Key1_Value=1;
unsigned char Key2_Value=1;

uint8_t   Time2_500ms_OK = 0x00;
uint8_t   PWM_Switch_State = 0;
uint8_t   power_state = 0;                   // ���ػ�״̬��־λ 


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

uint8_t   Time2_500ms_Cnt = 0x00;
uint8_t   Key_UpD_Flg=0x00;
uint8_t   Load_ON_Flg=0x00;
uint16_t  led0pwmval=1;//0;
uint8_t   dir=0;                     //����ʱ����Ϊ0���Կ˷���������������2016��2��3��
uint8_t   IN_PUT_State=0;


uint16_t adcx;
uint16_t adc_Upv;
uint16_t adc_Uout;
uint16_t adc_Ipv;
uint16_t adc_Iout;

uint16_t TEMP_VALUE;
short 		TEMP_BAT;

uint16_t adc_Temp,TEMP_V;
uint8_t  Send_data=0,beep_st=0;

u16 adc_12V,adc_36V;
float V12,V36;
u8 V12_8,V36_8;
u8 PWM_val,PWM_UP;
u8 S6_recnum;
u8 S6_data[14];
u8 USART1_recnum;
u8 USART1_recdata[20];
u8 USART1_Senddata[20];
u8 USB_Send[30];

u8 Pulse_num=0,Pulse_mode=1;
*/

/*
#define CURRENT_MIN     640
//������С����Ϊ(3.3*640/4096/0.2/100)*1000=25.8mA

#define CURRENT_MAX    1024
//����������Ϊ(3.3*1024/4096/0.2/100)*1000=41.25mA

#define V3V_MIN     1728
//����3V��С��ѹΪ3.3*1728/4096*2=2.78V

#define V3V_MAX    1872
//����3V����ѹΪ3.3*1872/4096*2=3.02V


#define V1V_MIN     1424
//����1.2V��С��ѹΪ3.3*1424/4096=1.15V
*/

#define CURRENT_MIN    20
//40
//������С����Ϊ(3.3*40/256/0.2/100)*1000=25.8mA

#define CURRENT_MAX    32
//64
//����������Ϊ(3.3*64/256/0.2/100)*1000=41.25mA

#define SHORT_CURRENT 93
//��·��������Ϊ(3.3*93/256/0.2/100)*1000=60mA

#define V3V_MIN     109
//����3V��С��ѹΪ3.3*110/256*2=2.81V

#define V3V_MAX    118
//����3V����ѹΪ3.3*117/256*2=3.04V


#define V1V_MIN     90
//����1.2V��С��ѹΪ3.3*90/256=1.16V

#define V1V_MAX    95
//����1.2V����ѹΪ3.3*95/256=1.22V

#define AVERAGE_MAX  93
//112
//����ֱ����ѹ���ֵΪ2.0*112/256=0.875V

#define AVERAGE_MIN  60
//41
//����ֱ����ѹ���ֵΪ2.0*41/256=0.32V

#define LIGHT_AD_MAX_DELTA_PERCENT  30
//����ƿذ�й�ADֵ����Թ�װ��·��й�ADֵ���ƫ��İٷֱ�

#define LIGHT_AD_MIN  0
//30
//������Թ�װ��·��й�ADֵ��Сֵ--��������ǿ����Сֵ

#define LIGHT_AD_MAX  255
//180
//������Թ�װ��·��й�ADֵ��Сֵ--��������ǿ����Сֵ

#define TH_MIN			150
//�������ģʽ�µƿذ���С����ֵ



u8 beep_st=0;
u8 rec_data_num,USART1_recnum,USART1_recdata[16];

u8 USART2_senddata[30],USART2_recdata[30];


PCB_INFO pcb_check_info[4][4];


/*---------------------------------------------------------------------*/
/*
void Led_Reflash_CHARGE1(void);
void GPIO_Configuration(void);
//void TIM3_Configuration(void);

void delay100ms(void);
void delay5ms(void);
void delay1s(void);
void delay1ms(void);

void PWM_out_5V(void);
void PWM_out_5V1(void);
void PWM_out_12V(void);
void PWM_out_19V(void);
void Key_control(void);
void Get_AD_result(void);
void Led_control(void);
void Init_all(void);
void SPI2_Init(void);
void show_chinese(void);
void show_english(void);
*/


void Usart1_send_char(uint16_t Data);
void print_char(uint16_t Data);
short Get_Temprate(void);
/*--------------------------------------------------------------------*/ //������

/*CRC*/ 
unsigned char auchCRCHi[] = 
{ 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

unsigned char auchCRCLo[] = 
{ 0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04,
	0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
	0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
	0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
	0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
	0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
	0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
	0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
	0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
	0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
	0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
	0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
	0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
	0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
	0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80, 0x40 
};


const char str_poweron[]={"���԰��ϵ�"};
const char str_start[]={"��ʼ���"};

const char str_light0[]={"�����⣺"};
const char str_dark[]={"����̫��"};
const char str_bright[]={"����̫ǿ"};

const char str_num[]={"���ϵ�·���ţ�"};
const char str_current[]={"��    ����"};
const char str_mA[]={"mA"};
const char str_short[]={"--��·"};
const char str_3V[]={"3V  ��ѹ��"};
const char str_1V[]={"1.2V��ѹ��"};
const char str_light[]={"�й�ADֵ��"};
const char str_dcv[]={"ֱ����ѹ��"};
const char str_out[]={"���״̬��"};
const char str_readlighterr[]={"��ȡ�й�ADֵ����"};
const char str_readtxerr[]={"��ȡ���ݳ���"};
const char str_th[]={"����  ֵ��"};

u32 CRC_Compute(u8 * pushMsg,u8 usDataLen) 
{ 
	u8 uchCRCHi = 0xff;
	u8 uchCRCLo = 0xff;
	
	u8 uIndex; 
	while(usDataLen--)
	{
		uIndex = uchCRCLo^ *pushMsg++;
		uchCRCLo = uchCRCHi^ auchCRCHi[uIndex];
		uchCRCHi = auchCRCLo[uIndex];
	}
	return (((u16)uchCRCHi) << 8 | uchCRCLo);
}	

void Usart1_send_str(const char *str)
{
	u8 i,j;
	j=strlen(str);
	for(i=0;i<j;i++)Usart1_send_char(str[i]);
}

void print_str(const char *str)
{
	u8 i,j;
	j=strlen(str);
	for(i=0;i<j;i++)print_char(str[i]);
}

//��ӡ3λ����,��ѡ�Ƿ�ӻس�
void print_num(u8 n,u8 enter)
{
	u8 j;
	
	j=n/100+0x30;
	print_char(j);
	j=(n%100)/10+0x30;
	print_char(j);
	j=n%10+0x30;
	print_char(j);
	
	if(enter==1)print_char(0x0d);//�س�
	
}

//��ӡ��ѹֵ 3λ����/100 V
void print_voltage(u16 n)
{
	u8 j;
	
	j=n/100+0x30;
	print_char(j);
	print_char(0x2E);	//.
	j=(n%100)/10+0x30;
	print_char(j);
	j=n%10+0x30;
	print_char(j);
	print_char(0x56);	//V
	
	print_char(0x0d);	//�س�
	
}


//ͨ��2��HC595��ʾ16��LEDָʾ��
void Show_led(u16 led_data)
{
	u8 i;
	
	RCLK_OFF;
	SRCLK_OFF;
	//DATA_OFF;
	delay_us(3);
	
	for(i=0;i<16;i++)
	{
		if((led_data&0x8000)==0)DATA_OFF;
		else DATA_ON;
		led_data<<=1;
		
		SRCLK_ON;
		delay_us(3);
		SRCLK_OFF;
	}
	DATA_OFF;
	delay_us(3);
	RCLK_ON;
	delay_us(3);
	RCLK_OFF;
	
}


/*
//ͨ��HC595��ʾ8��LEDָʾ��
void Show_led(u8 led_data)
{
	u8 i;
	
	RCLK_OFF;
	SRCLK_OFF;
	//DATA_OFF;
	delay_us(3);
	
	for(i=0;i<8;i++)
	{
		if((led_data&0x80)==0)DATA_OFF;
		else DATA_ON;
		led_data<<=1;
		
		SRCLK_ON;
		delay_us(3);
		SRCLK_OFF;
	}
	DATA_OFF;
	delay_us(3);
	RCLK_ON;
	delay_us(3);
	RCLK_OFF;
	
}
*/


//ͨ��HC595����ǰ����8���ƿذ��Դ
void SET_POWER1(u8 con_data)
{
	u8 i;
	
	RCLK1_OFF;
	SRCLK1_OFF;
	//DATA_OFF;
	delay_us(3);
	
	for(i=0;i<8;i++)
	{
		if((con_data&0x80)==0)EN_D1_OFF;
		else EN_D1_ON;
		con_data<<=1;
		
		SRCLK1_ON;
		delay_us(3);
		SRCLK1_OFF;
	}
	EN_D1_OFF;
	delay_us(3);
	RCLK1_ON;
	delay_us(3);
	RCLK1_OFF;
	
}

//ͨ��HC595���ƺ�����8���ƿذ��Դ
void SET_POWER2(u8 con_data)
{
	u8 i;
	
	RCLK2_OFF;
	SRCLK2_OFF;
	//DATA_OFF;
	delay_us(3);
	
	for(i=0;i<8;i++)
	{
		if((con_data&0x80)==0)EN_D2_OFF;
		else EN_D2_ON;
		con_data<<=1;
		
		SRCLK2_ON;
		delay_us(3);
		SRCLK2_OFF;
	}
	EN_D2_OFF;
	delay_us(3);
	RCLK2_ON;
	delay_us(3);
	RCLK2_OFF;
	
}

void SET_COLAB(u8 i)
{
				if(i==0)
				{
					COL_A_OFF;
					COL_B_OFF;
				}
				else if(i==1)
				{
					COL_A_ON;
					COL_B_OFF;					
				}
				else if(i==2)
				{
					COL_A_OFF;
					COL_B_ON;					
				}				
				else //if(i==3)
				{
					COL_A_ON;
					COL_B_ON;					
				}
		//		delay_ms(5);	
}

void SET_ROWAB(u8 j)
{
					if(j==0)
					{
						ROW_A_OFF;
						ROW_B_OFF;
					}
					else if(j==1)
					{
						ROW_A_ON;
						ROW_B_OFF;					
					}
					else if(j==2)
					{
						ROW_A_OFF;
						ROW_B_ON;					
					}				
					else //if(j==3)
					{
						ROW_A_ON;
						ROW_B_ON;					
					}
					delay_ms(5);
}

int main(void)
{
		u8  i,j,m,flag_rec;
		//u8  key2_down=0;
		//u16 tempv_16=0,power_con=0xffff;
		u16 led_data=0,k;
		u16 light_ad=0,max_light_ad,min_light_ad;
		float f_val;
	
		//u32 delay_val=0;
	
		//u8 key_down=0,key1_down=0,v_short=0,power_down=0;
	  //u8 flag_rec;
//		u32 tmpreg1;//,tmpreg2;
	
  //	 ADC_InitTypeDef ADC_InitStructure;  
	//   delay100ms();
    SystemInit();
    RCC_Configuration1();                 //STM32ʱ�ӳ�ʼ��
    NVIC_Configuration();                //�ж�����������
    GPIO_Configuration();                //��Ƭ��IO��ʼ��
	
		
			
    Adc_Init();
  //  TIM3_Mode_Config();
 //   Exit_Configuration();
    Timer2_Configuration();
 //   Timer4_Configuration();	
	
    USART_Configuration();  //USART1���� 
	
		SET_PA15PB3PB4();
	
	//		ENV12_OFF;


  //  SysTick_init();		     //��ʱ��ʼ��
 //   SPI2_Init(); 			     //��ʼ��SPIӲ����
//	  P_RXD=RxBuffer;//����ָ��ָ����ջ�����
	/* Resets ADC1 */ 
	
		SET_POWER1(0);
		SET_POWER2(0);
		Show_led(0Xffff);
		
//		delay_ms(100);

  //  USART_ClearFlag(USART1, USART_FLAG_TC);
		
		Usart1_send_char(0x30);
		Usart1_send_char(0x31);

//		SET_POWER1(0);
//		SET_POWER2(0);
		
	//	Show_led(0X00);
		
		delay_ms(1000);
		
		Show_led(0);
		
	
/*		
		for(i=0;i<10;i++)
		{
			beep_st=1;
			delay_ms(200);			
		
			beep_st=0;
			delay_ms(200);	
		}
*/

	//	for(i=0;i<10;i++)
	//	{
	//		delay_ms(1000);
			Usart1_send_str(str_poweron);
	//	}
			print_char(0x0d);
			

		while(1)
		{
			while(1)
			{
				if(KEY3==1)
				{
					delay_ms(10);
					if(KEY3==1)break;
				}
			}
			
			
			delay_ms(200);
			Show_led(0);

			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
			
//��ȡ���Ե�·���ϸй�ADֵ
			delay_ms(5);
			light_ad=Get_Adc_Average(8,10);
			f_val=light_ad*1.65;		//��Ϊ��Ӧ�ο���ѹΪ2V��ADֵ--�ƿذ�AD�ο���ѹΪ2V
			k=(u16)f_val;
			
			if(k>255)k=255;
			light_ad=k;
			
	
			k=light_ad*LIGHT_AD_MAX_DELTA_PERCENT;
			k/=100;
			
			max_light_ad=light_ad+k;
			if(max_light_ad>252)max_light_ad=252;
			min_light_ad=light_ad-k;
			
/*			
			Usart1_send_char(0x0);
			Usart1_send_str(str_light);
			
			j=light_ad/100+0x30;
			Usart1_send_char(j);
			j=(light_ad%100)/10+0x30;
			Usart1_send_char(j);
			j=light_ad%10+0x30;
			Usart1_send_char(j);
	
			Usart1_send_char(0x0d);//�س�
			
			delay_ms(1000);
			
		}
		
		{
*/				
			Usart1_send_char(light_ad);	
			Usart1_send_char(min_light_ad);
			Usart1_send_char(max_light_ad);
			
			if((light_ad<LIGHT_AD_MIN)||(light_ad>LIGHT_AD_MAX))
			{

				
				beep_st=1;

				delay_ms(100);
				
				beep_st=0;
				delay_ms(100);
				beep_st=1;
				delay_ms(100);
				beep_st=0;
				delay_ms(100);
				beep_st=1;
				delay_ms(100);
				beep_st=0;
				Show_led(0xffff);
				
				print_char(0);
				print_str(str_light0);
				print_num(light_ad,0);
				print_char(0x28);		//(
				print_num(LIGHT_AD_MIN,0);
				print_char(0x2d);		//-
				print_num(LIGHT_AD_MAX,0);								
				print_char(0x29);		//)
				if(light_ad<LIGHT_AD_MIN)print_str(str_dark);
				else print_str(str_bright);
				print_char(0x0d);
				print_char(0x0d);
				print_char(0x0d);
				
				Usart1_send_char(light_ad);
				Usart1_send_char(LIGHT_AD_MIN);
				Usart1_send_char(LIGHT_AD_MAX);
				if(light_ad<LIGHT_AD_MIN)Usart1_send_str(str_dark);
				else Usart1_send_str(str_bright);						
			}
			else	//�����й��������Χ�ڣ����Կ�ʼ����
			{
			//TIM_ITConfig(TIM2,TIM_IT_CC1,DISABLE);
			
			beep_st=1;
			SET_POWER1(0xff);
			SET_POWER2(0xff);
		
			
			
			delay_ms(300);
			beep_st=0;
			
			Usart1_send_str(str_start);
//			TIM_ITConfig(TIM2,TIM_IT_CC1,DISABLE);
			
			delay_ms(4000);
			
//��ȡ16���ƿذ��ϵ��ĵ�����3V��ѹ��1.2V��ѹ���ϵ�����״̬
			for(i=0;i<4;i++)	//��ѭ��
			{
				SET_COLAB(i);
				
				for(j=0;j<4;j++)	//���������μ��4���ƿذ�
				{
					SET_ROWAB(j);
					
					pcb_check_info[i][j].current=Get_Adc_Average(0,10);
					
					delay_ms(5);
					pcb_check_info[i][j].V_3V=Get_Adc_Average(4,10);
					if(pcb_check_info[i][j].V_3V>10)pcb_check_info[i][j].V_3V+=1;	//�������

					
					delay_ms(5);
					pcb_check_info[i][j].V_1V=Get_Adc_Average(1,10);
					if(pcb_check_info[i][j].V_1V>10)pcb_check_info[i][j].V_1V+=1;	//�������
		
					
					if(O_OUT==1)pcb_check_info[i][j].out_st=0;
					else pcb_check_info[i][j].out_st=1;
					
				}
			}
			
			
//��ȡ16���ƿذ巢�͵ĸй�ADֵ���ݣ�ÿ���ƿذ���200ms�ڶ�ȡ
			USART1_recnum=0;
			rec_data_num=4;
			for(i=0;i<4;i++)	//��ѭ��
			{
				SET_COLAB(i);
				
				for(j=0;j<4;j++)	//���������μ��4���ƿذ�
				{
					SET_ROWAB(j);

					pcb_check_info[i][j].light_ad=0;
					
					
					k=1;
					k<<=(4*i+j);
					Show_led(k);
					
					flag_rec=0;
					USART1->SR&=~0X3FF;
			//		delay_ms(100);
					m=USART_ReceiveData(USART1);
					USART_ClearITPendingBit(USART1,USART_IT_RXNE);
					//USART_ClearFlag(USART1,USART_FLAG_RXNE);
					USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
					
					for(m=0;m<40;m++)//Ҫ�����������5ms�ڽ���4���ֽڣ��������½���
					{
						if((flag_rec==1)&&(USART1_recnum<4))
						{
							USART1_recnum=0;
							flag_rec=0;
						}
						if((USART1_recnum>0)&&(USART1_recnum<4))flag_rec=1;
						delay_ms(5);
					}

					Show_led(0);
					delay_ms(50);
					
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);		
					
					if(USART1_recnum==4)
					{
						pcb_check_info[i][j].light_ad=USART1_recdata[1];
						pcb_check_info[i][j].read_light=1;
					}
					else
					{
						pcb_check_info[i][j].read_light=0;
					}
					USART1_recnum=0;
					Usart1_send_char(pcb_check_info[i][j].light_ad);
					
				//	delay_ms(100);
				}
			}
			
			delay_s(8);
//��ȡ16���ƿذ��ϵ��Լ���ɺ�����״̬��ӦΪ��
			for(i=0;i<4;i++)	//��ѭ��
			{
				SET_COLAB(i);
				
				for(j=0;j<4;j++)	//���������μ��4���ƿذ�
				{
					SET_ROWAB(j);
					
					if(O_OUT==1)pcb_check_info[i][j].out_st+=10;
					
				}
			}
			
			rec_data_num=10;
			for(i=0;i<4;i++)	//��ѭ��
			{
				SET_COLAB(i);
				
				for(j=0;j<4;j++)	//���������μ��4���ƿذ�
				{
					SET_ROWAB(j);
					USART1_recnum=0;
					for(m=0;m<10;m++)pcb_check_info[i][j].tx_data[m]=0;

					k=1;
					k<<=(4*i+j);
					Show_led(k);
					
					flag_rec=0;
					
					USART1->SR&=~0X3FF;
			//		delay_ms(100);
					m=USART_ReceiveData(USART1);
					USART_ClearITPendingBit(USART1,USART_IT_RXNE);
					//USART_ClearFlag(USART1,USART_FLAG_RXNE);
					USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
					
					for(m=0;m<40;m++)//Ҫ�����������5ms�ڽ���10���ֽڣ��������½���
					{
						if((flag_rec==1)&&(USART1_recnum<10))
						{
							USART1_recnum=0;
							flag_rec=0;
						}
						if((USART1_recnum>0)&&(USART1_recnum<10))flag_rec=1;
						delay_ms(5);
					}

					Show_led(0);
					delay_ms(50);
					
					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);		
					
					if(USART1_recnum==10)
					{
						pcb_check_info[i][j].read_tx=1;
						for(m=0;m<10;m++)
							pcb_check_info[i][j].tx_data[m]=USART1_recdata[m];
					}
					else
					{
						pcb_check_info[i][j].read_tx=0;
					}
					USART1_recnum=0;
					//Usart1_send_char(pcb_check_info[i][j].light_ad);
					
				//	delay_ms(100);
				}
			}
	//		USART1_recnum=0;
			
			m=0;
			for(i=0;i<4;i++)	
			{
				for(j=0;j<4;j++)
				{
					if(pcb_check_info[i][j].out_st>0)m++;
					
					pcb_check_info[i][j].out_st+=100;
				}
			}
			
	//	  TIM_ITConfig(TIM2,TIM_IT_CC1,ENABLE);

			
//���ӵ������Ŀ�궯����֮����ÿ��ģ��������״̬ӦΪ��
			
			
//��ȡ����״̬			
			for(k=0;k<20;k++)
			{
				if(m>=16)break;
				
				beep_st=1;
				delay_ms(100);
				beep_st=0;
				delay_ms(400);
				
				for(i=0;i<4;i++)	//��ѭ��
				{
					SET_COLAB(i);
					
					for(j=0;j<4;j++)	//���������μ��4���ƿذ�
					{
						SET_ROWAB(j);
						
						if(pcb_check_info[i][j].out_st==100)
						{
							if(O_OUT==1)
							{
								//if(pcb_check_info[i][j].out_st>=100)
								//{
									pcb_check_info[i][j].out_st-=100;
									m++;
							//	}
							}
						}
					}
				}
			}
			
	//�رյ��
			
			
			
			delay_ms(100);
			
			SET_POWER1(0);
			SET_POWER2(0);
			
		//	Usart1_send_char(light_ad);
			
			print_char(0);			//�ո�
			
			led_data=0;
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					Usart1_send_char(pcb_check_info[i][j].current);
					Usart1_send_char(pcb_check_info[i][j].V_3V);					
					Usart1_send_char(pcb_check_info[i][j].V_1V);	
					Usart1_send_char(pcb_check_info[i][j].out_st);
					Usart1_send_char(pcb_check_info[i][j].read_light);
					Usart1_send_char(pcb_check_info[i][j].light_ad);
					Usart1_send_char(pcb_check_info[i][j].read_tx);
					Usart1_send_char(pcb_check_info[i][j].tx_data[1]);
					Usart1_send_char(pcb_check_info[i][j].tx_data[4]);					

					if((pcb_check_info[i][j].current<CURRENT_MIN)||(pcb_check_info[i][j].current>CURRENT_MAX)
					 ||(pcb_check_info[i][j].V_3V<V3V_MIN)||(pcb_check_info[i][j].V_3V>V3V_MAX)
					 ||(pcb_check_info[i][j].V_1V<V1V_MIN)||(pcb_check_info[i][j].V_1V>V1V_MAX)
					 ||(pcb_check_info[i][j].out_st>0)
					 ||(pcb_check_info[i][j].read_tx==0)
					 ||(pcb_check_info[i][j].tx_data[1]<TH_MIN)
					 ||(pcb_check_info[i][j].tx_data[4]<AVERAGE_MIN)||(pcb_check_info[i][j].tx_data[4]>AVERAGE_MAX)
					 ||(pcb_check_info[i][j].read_light==0)
					 ||(pcb_check_info[i][j].light_ad<min_light_ad)||(pcb_check_info[i][j].light_ad>max_light_ad))
					// ||((pcb_check_info[i][j].read_light==1)&&((pcb_check_info[i][j].light_ad<min_light_ad)||(pcb_check_info[i][j].light_ad>max_light_ad))))
					{
						pcb_check_info[i][j].check_status=1;
						k=1;
						k<<=(4*i+j);
						led_data|=k;
						//��ӡ���ϵ�·����
						print_char(0);			//���ַ�					
						print_str(str_num);		//
						print_char(i+0x31);		//�к�
						print_char(0x2d);			//-
						print_char(j+0x31);		//�к�
						print_char(0x0d);			//�س�
					//	delay_ms(200);
						
						//��ӡ���ϵ���ֵ
						if((pcb_check_info[i][j].current<CURRENT_MIN)||(pcb_check_info[i][j].current>CURRENT_MAX))
						{
							print_str(str_current);
							//print_num(pcb_check_info[i][j].current,1);
							k=pcb_check_info[i][j].current*165;
							k>>=8;
							print_num(k,0);
							print_str(str_mA);
							
							if(pcb_check_info[i][j].current>SHORT_CURRENT)
							{
								print_str(str_short);
							}
							print_char(0x0d);	//�س�
							
						//	delay_ms(200);
						}
						
						//��·���߶���ʱ����ӡ����������Ϣ
						if((pcb_check_info[i][j].current<2)||(pcb_check_info[i][j].current>SHORT_CURRENT))
						{
							;
						}
						else	//û�ж�·��û�е�Դ�߶���ʱ����ӡ����������Ϣ
						{
							if(pcb_check_info[i][j].read_light==0)//��ȡ�ƿذ�й�ADֵ����ʱ
							{
								print_str(str_readlighterr);
								print_char(0x0d);								
							}
							//����ȡ�ĸй�ADֵ
							else if((pcb_check_info[i][j].light_ad<min_light_ad)||(pcb_check_info[i][j].light_ad>max_light_ad))
							{
								print_str(str_light);
								print_num(pcb_check_info[i][j].light_ad,0);
								print_char(0x28);		//(
								print_num(min_light_ad,0);
								print_char(0x2d);		//-
								print_num(light_ad,0);								
								print_char(0x2d);		//-
								print_num(max_light_ad,0);
								print_char(0x29);		//)
								print_char(0x0d);
								//delay_ms(200);							
							}
							
							//���3V��ѹֵ
							if((pcb_check_info[i][j].V_3V<V3V_MIN)||(pcb_check_info[i][j].V_3V>V3V_MAX))
							{
								print_str(str_3V);
								k=pcb_check_info[i][j].V_3V*165;
								k>>=6;
								print_voltage(k);								
							}
							
							//���1.2V��ѹֵ
							if((pcb_check_info[i][j].V_1V<V1V_MIN)||(pcb_check_info[i][j].V_1V>V1V_MAX))
							{
								print_str(str_1V);
								k=pcb_check_info[i][j].V_1V*165;
								k>>=7;
								print_voltage(k);		
							}
							//������״̬
							if(pcb_check_info[i][j].out_st>0)
							{
								print_str(str_out);
								print_num(pcb_check_info[i][j].out_st,1);
							}
							
							if(pcb_check_info[i][j].read_tx==0)	//��ȡ�ƿذ����ݳ���ʱ
							{
								print_str(str_readtxerr);
								print_char(0x0d);								
							}
							else 	//��ȡ������ȷʱ
							{
								//������ģʽ�µ�����ֵ
								if(pcb_check_info[i][j].tx_data[1]<TH_MIN)
								{
									print_str(str_th);
									print_num(pcb_check_info[i][j].tx_data[1],1);
								}
								//���ֱ����ѹֵ
								if((pcb_check_info[i][j].tx_data[4]<AVERAGE_MIN)||(pcb_check_info[i][j].tx_data[4]>AVERAGE_MAX))
								{
									print_str(str_dcv);
									k=pcb_check_info[i][j].tx_data[4]*100;
									k>>=7;
									print_voltage(k);																	
								}
							}
						}
					}
					else
					{
						pcb_check_info[i][j].check_status=0;
					}
				}
			}
			
			//��ӡ2���س����Ƴ���ӡ��Ϣ
			if(led_data>0)
			{
				print_char(0x0d);			//�س�
				print_char(0x0d);			//�س�
	
			}
			Show_led(led_data);

			beep_st=1;
			if(led_data>0)
			{
				//beep_st=1;
				delay_ms(100);
				beep_st=0;
				delay_ms(100);
				beep_st=1;
				delay_ms(100);
				beep_st=0;
				delay_ms(100);
				beep_st=1;
				delay_ms(100);
				beep_st=0;

			}
			else
			{
				delay_ms(600);
				beep_st=0;
				
			}
			
		}
		}

}

//����������

///////////
void Usart1_send_char(uint16_t Data)
{
	//	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==0);
    USART_SendData(USART1,Data);	
    while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==0);
	//  delay1ms();
	 //delay1ms();
	// delay1ms();
    USART_ClearFlag(USART1, USART_FLAG_TC);
}

///////////
void print_char(uint16_t Data)
{
	//	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==0);
    USART_SendData(USART3,Data);	
    while(USART_GetFlagStatus(USART3, USART_FLAG_TC)==0);
	//  delay1ms();
	 //delay1ms();
	// delay1ms();
    USART_ClearFlag(USART3, USART_FLAG_TC);
}

//�����¶�ֵ*10+500
short Get_Temprate(void)    //
{
   // u32 adcx;
    short result;
    float temperate;
		u16 adc_Temp;
    adc_Temp=Get_Adc_Average(ADC_Channel_16,10);  //
    temperate=(float)adc_Temp*(3.3/4096);       //
    temperate=(1.43-temperate)/0.0043+75;   //25+50
    result=temperate*10;                  //
		//result+=500;
    return result;
}


void USART1_IRQHandler(void)
{
		u8 i,j,k,sdata,rec_err=0;

	/*
		USART_GetFlagStatus(USART1, USART_FLAG_ORE);
		USART_ClearFlag(USART1,USART_FLAG_ORE);
	
		if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)			
	//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
*/
	
			if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
			{
				USART_ClearFlag(USART1, USART_FLAG_ORE);
			}

			if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
			{
				USART_ClearITPendingBit(USART1, USART_IT_RXNE); 

//			LED2_ON;
			//USART_SendData(USART2, USART_ReceiveData(USART2));
			sdata=USART_ReceiveData(USART1);
			
	//		Usart1_send_char(sdata);
			
			if(rec_data_num==4)	//���յƿذ��ϵ���͵ĸй�ADֵ����
			{
				if(USART1_recnum==0)
				{
					if(sdata!=0xfa)rec_err=1;
				}
				else if(USART1_recnum==2)
				{
					if(sdata!=USART1_recdata[1])rec_err=1;
				}
				else if(USART1_recnum==3)
				{
					k=0xfb;
					k+=USART1_recdata[1];
					k+=USART1_recdata[2];
					
					if(sdata!=k)rec_err=1;
				}
				
				if(rec_err==0)
				{
					if(USART1_recnum<4)
					{
						//USB_Send[1+S6_recnum]=sdata;
						USART1_recdata[USART1_recnum]=sdata;
						USART1_recnum++;
						/*
						if(USART1_recnum==4)
						{
							USART1_recnum++;
							USART1_recnum--;
						}
						*/
					}							
				//	USART1_recnum++;
				}
				else USART1_recnum=0;				
			}
			else //if(rec_data_num==10)	//���յƿذ忪ʼ̽���ʱ���͵�����
			{
				if(USART1_recnum==0)
				{
					if (sdata!=0x35)rec_err=1;
				}
				else if(USART1_recnum==9)
				{
					j=1;
					for(i=0;i<9;i++)j+=USART1_recdata[i];
					if (sdata!=j)rec_err=1;
				}

				if(rec_err==0)
				{
					if(USART1_recnum<10)
					{
						//USB_Send[1+S6_recnum]=sdata;
						USART1_recdata[USART1_recnum]=sdata;
						USART1_recnum++;
					}							
				//	USART1_recnum++;
				}
				else USART1_recnum=0;				
				
			}
			
	//	 USART1->SR&=~0X3FF;

			//if(sdata
			//Usart1_send_char(sdata);
//			LED2_OFF;
		
		}
		
		
		else if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
		{
			sdata = USART1->SR;
			sdata = USART1->DR;
			USART_ClearITPendingBit(USART1,USART_IT_IDLE);
		//	ReceiveState = 1;
		}		
		
}


/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void USART2_IRQHandler(void)
//{

//}
