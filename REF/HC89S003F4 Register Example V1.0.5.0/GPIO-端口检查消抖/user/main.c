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
*	1、P0xDBCT [5:0]配置的消抖时间是一个范围，分频系数*Tosc*P0xDBCT[5:0]-Tosc<消抖时间<
*	   分频系数*Tosc*(P0xDBCT[5:0]+1)-Tosc。
*	2、MCU上电复位以及其它复位功能的复位，所有的IO相关寄存器都会恢复为默认值。
*	************************************************************************************
*									 应用注意事项
*	1、在使用仿真器时，与JTAG复用的IO口会有读取或写入数据异常，因此建议使用仿真器时不要
*	   操作这几个IO口。断开仿真器使用电源供电即可以正常操作。
*	2、分配到P0.0/P0.1/P0.2这三个管脚上的功能脚、外部中断输入、故障检测引脚都受消抖控制。
*	3、P27管脚出厂默认为RST管脚，可以通过Option配置为普通IO引脚。
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
*   ************************************************************************************
**/

#define ALLOCATE_EXTERN
#include "HC89S003F4.h"

/***************************************************************************************
  * @实现效果	对P00端口的消抖时间进行设置，251.9375us<消抖时间<255.9375us。
***************************************************************************************/
void main()
{
/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗
		                        //本例程为方便测试关闭看门狗，实际使用中，建议客户打开看门狗，详见WDT复位例程
	CLKSWR = 0x51;						//选择内部高频RC为系统时钟，内部高频RC 2分频，Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1分频得到Fcpu，Fcpu=16MHz 
/**********************************端口消抖初始化**************************************/
  P0M0 = P0M0&0xF0|0x02;    //P00设置为上拉输入
	P00DBC = 0xFF;						//设置消抖时间
	//消抖时间计算
	//分频系数*Tosc*P0xDBCT[5:0]-Tosc<消抖时间<分频系数*Tosc*(P0xDBCT[5:0]+1)-Tosc
	//		  64*0.0625us*63-0.0625us<消抖时间<64*0.0625us*(63+1)-0.0625us
	//					   251.9375us<消抖时间<255.9375us

	while(1);
}