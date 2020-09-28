/**
*   ************************************************************************************
*								上海芯圣电子股份有限公司
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.5.0
*	@Demo 	Version		V1.0.4.0
*	@Date				2019.12.27
*	************************************************************************************
*									 模块性能介绍
*	1、MCU的定时器0，1共有四种工作方式
*	   方式0：16位自动重装定时器/计数器
*	   方式1：16位定时器/计数器
*	   方式2：8位自动重装定时器/计数器
*	   方式3：T0分成两个（TL0/TH0）独立的8位定时器/计数器（T1无此模式）
*	************************************************************************************
*									 应用注意事项
*	1、方式3时T0占用T1的TR1、TF1及中断源，由于TR1被T0占用，此时需要关闭T1可将T1设为工作
*	   方式3
*	2、在方式0（Mode0）时THx(x = 0,1)和TLx(x = 0,1)读写操作遵循先高位后低位。并且在修改
*	   重载数据时，低位无论有无改变，只要高位被修改，低位都必须再写入一次，方式 1、2、3
*	   时无此要求
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
*   ************************************************************************************
**/

#define ALLOCATE_EXTERN
#include "HC89S003F4.h"

/***************************************************************************************
  * @实现效果	T1定时时间1ms，每1ms进入一次中断，P00翻转
***************************************************************************************/
void main()
{
/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗
	                          //本例程为方便测试关闭看门狗，实际使用中，建议客户打开看门狗，详见WDT复位例程	
	CLKSWR = 0x51;						//选择内部高频RC为系统时钟，内部高频RC 2分频，Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1分频得到Fcpu，Fcpu=16MHz 
/**********************************相关配置初始化**************************************/
	P0M0 = P0M0&0xF0|0x08;		//P00设置为推挽输出
/**********************************TIM1配置初始化**************************************/
	TCON1 = 0x00;						  //T1定时器时钟为Fosc
	TMOD = 0x00;						  //16位重装载定时器/计数器

	//Tim1计算时间 	= (65536 - 0xFACB) * (1 / (Fosc /Timer分频系数))
	//				= 1333 / (16000000 / 12)
	//				= 1 ms

	//定时1ms
	//反推初值 	= 65536 - ((1/1000) / (1/(Fosc / Timer分频系数)))
	//		   	= 65536 - ((1/1000) / (1/(16000000 / 12)))
	//			= 65536 - 1333
	//			= 0xFACB
	
	TH1 = 0xFA;
	TL1 = 0xCB;
	IE |= 0x08;							  //打开T1中断
	TCON |= 0x40;						  //使能T1
    
	EA = 1;								    //打开总中断
	while(1);
}

/***************************************************************************************
  * @说明  	T1中断服务函数
  *	@参数	  无
  * @返回值 无
  * @注		  无
***************************************************************************************/
void TIMER1_Rpt(void) interrupt TIMER1_VECTOR
{
	u16 count;
	count++;
	if(count>=1000)
	{ 
		count=0;
	  P0_0 =~ P0_0;						  //P00翻转
	}
}