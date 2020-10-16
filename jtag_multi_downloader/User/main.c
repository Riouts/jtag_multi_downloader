/*
软件版本Ver1.0
硬件: 
版本:
2020年9月24日 崔巍
RA3003 4x6拼板的测试工装底板STM32F103C8T6的CPU程序
*/

/*
管脚定义：
1. 上位机uart(usart1)：PA9(tx), PA10(rx)
2. 无源嗡鸣器：PA11
3. 用户功能开关：PC15
4. 串入并出移位：PB15(数据)，PB14(shift clock)，PA8(latch)
5. PM51烧写器i/o：
	ok:		input	PB7 
	fail:	input	PB9
	start:	output	PB6
	busy:	input	PB8
6. 热敏打印机：
	prt_dtr: PA7
	mcu_rx3: PB11
	mcu_tx3: PB10
*/

/*--------------------------------------------------------------------*/
#include<main.h>
#include<math.h>
#include<stm32f10x_spi.h>
#include<bmp.h>
/*--------------------------------------------------------------------*/
u8 beep_st=0;
u8 rec_data_num,USART1_recnum,USART1_recdata[16];

void Usart1_send_char(uint16_t Data);//uart1发送一个字节
void Usart1_send_str(const char *str);//uart1发送字符串
void change_chan(u8 chan);//切换通道0~23
void beep_result(u8 mode);//0/1/2：开始/成功/失败
void print_char(uint16_t Data);//热敏打印机打印一个字节ascii
void print_num(u8 n,u8 enter);//热敏打印机打印3位整数
void print_voltage(u16 n);//热敏打印机打印打印电压
void printer_str(const char *str);//热敏打印机打印字串
void printer_test(void);
void printer_writeBytes(const char a, const char b);
/*--------------------------------------------------------------------*/

const char str_poweron[]={"上电成功"};
const char str_init_ok[]={"初始化完成"};
const char str_start[]={"开始"};
const char str_finish[]={"结束"};
const char str_trigger[]={"触发"};
const char str_go_chan[]={"切换"};
const char str_pm51_busy[]={"."};
const char str_pm51_ok[]={"正常"};
const char str_pm51_fail[]={"失败     "};

#define ASCII_TAB '\t' //!< Horizontal tab
#define ASCII_LF '\n'  //!< Line feed
#define ASCII_FF '\f'  //!< Form feed
#define ASCII_CR '\r'  //!< Carriage return
#define ASCII_DC2 18   //!< Device control 2
#define ASCII_ESC 27   //!< Escape
#define ASCII_FS 28    //!< Field separator
#define ASCII_GS 29    //!< Group separator

void printer_writeBytes(const char a, const char b)
{
	print_char(a);
	print_char(b);
}

void printer_test()
{
	printer_writeBytes(ASCII_DC2, 'T');
}

//打印3位整数,可选是否加回车
void print_num(u8 n,u8 enter)
{
	u8 j;
	
	j=n/100+0x30;
	print_char(j);
	j=(n%100)/10+0x30;
	print_char(j);
	j=n%10+0x30;
	print_char(j);
	
	if(enter==1)print_char(0x0d);//回车
	
}

//打印电压值 3位整数/100 V
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
	
	print_char(0x0d);	//回车
	
}

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

void printer_str(const char *str)
{
	u8 i,j;
	j=strlen(str);
	for(i=0;i<j;i++)
	{
		print_char(str[i]);
		delay_ms(10);
	}	
}

void beep_result(u8 mode)
{
	switch (mode)
	{
	case 0/* constant-expression */:
		beep_st = 1;
		delay_ms(500);
		beep_st = 0;
		break;
	case 1/* constant-expression */:
		beep_st = 1;
		delay_ms(100);
		beep_st = 0;
		break;
	case 2/* constant-expression */:
		beep_st = 1;
		delay_ms(1000);
		beep_st = 0;
		break;	
	default:
		break;
	}
}

void Usart1_send_str(const char *str)
{
	u8 i,j;
	j=strlen(str);
	for(i=0;i<j;i++)Usart1_send_char(str[i]);
}

//通过3个74HC595控制24个路通道
void change_chan(u8 chan)
{
	u8 i;
	u32 chan_bit_selector;

	RCLK_OFF;//latch
	SRCLK_OFF;//shift clock

	chan_bit_selector = 0x01 << chan;

	delay_us(3);
	
	for(i=0;i<24;i++)
	{
		if((chan_bit_selector&0x00800000)==0)
			DATA_OFF;
		else
			DATA_ON;

		chan_bit_selector <<= 1;
		
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
			
			if(rec_data_num==4)	//接收灯控板上电后发送的感光AD值数据
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
			else //if(rec_data_num==10)	//接收灯控板开始探测后定时发送的数据
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

int main(void)
{
	u8 i;  //just for index
	char temp_str[100];

    SystemInit();
    RCC_Configuration1();                //STM32时钟初始化
    NVIC_Configuration();                //中断向量表设置
    GPIO_Configuration();                //单片机IO初始化
    Timer2_Configuration();				 //控制buzzer用
    USART_Configuration();  			 //USART1配置
	
	delay_ms(1000);

	Usart1_send_str(str_poweron);
	Usart1_send_str(str_init_ok);

	while(1)
	{
		while(1)	//查询按钮（按下为高）
		{
			if(KEY1==1)
			{
				delay_ms(10);
				if(KEY1==1)
					break;
			}
		}
			
		beep_result(0);	
		Usart1_send_str(str_start);
		USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);//禁止接收中断
			
////////////////////////////////////////////////////////////////////////////
		printer_str("\r\n");
		printer_str("\r\n");
		printer_str("\r\n");
		printer_str(str_start);
		printer_str("\r\n");
		printer_str("\r\n");

		for(i=0;i<24;i++)
		{
			change_chan(i);
			
			delay_ms(100);

			PM51_START_OFF;
			delay_ms(100);
			PM51_START_ON;
			delay_ms(500);

			while (1 == PM51_BUSY)
			{
				Usart1_send_str(str_pm51_busy);
				//printer_str(str_pm51_busy);
				delay_ms(100);
			}
			
			if (1 == PM51_OK)
			{
				//Usart1_send_str(str_pm51_ok);
				//printer_str(str_pm51_ok);
				beep_result(1);
			}
			
			if (1 == PM51_FAIL)
			{
				sprintf(temp_str, "%3d", i);
				Usart1_send_str(temp_str);
				printer_str(temp_str);				
				Usart1_send_str(str_pm51_fail);
				printer_str(str_pm51_fail);
				Usart1_send_str("\r\n");
				printer_str("\r\n");
				beep_result(2);
			}
		}
		printer_str("\r\n");
		printer_str("\r\n");
		printer_str("\r\n");
		
	}

}



