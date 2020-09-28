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
*	1、16位CRC。
*	2、CRC生成校验遵从CRC-CCITT多项式，即0x1021。
*	3、初值可设为0x0000或0xFFFF。
*	4、计算与结果共用同一寄存器。
*	************************************************************************************
*									 应用注意事项
*	1、每写入一次待计算数据，其计算结果是由前一次计算结果共同生成。
*	2、写入数据时，自动启动CRC计算，计算结束后自动关闭。
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
*   ************************************************************************************
**/

#define	ALLOCATE_EXTERN
#include "HC89S003F4.h"
#include "string.h"

unsigned int CRC_CalcCRC(unsigned char *fucp_CheckArr,unsigned int fui_CheckLen);//写入需要校验的数据并且返回校验值

unsigned char guc_UARTFlag;				  //UART判断标志位
unsigned char guc_UARTCnt;			  	//UART计数使用
unsigned char guc_UARTbuf_a[5];			//用于存放接收数据
unsigned char guc_i;					      //发送数据计数	
unsigned int  gui_CrcResault;			  //CRC校验值
unsigned char guc_CrcValue_a[2];		//CRC校验发送值
unsigned char guc_CrcCnt;				    //写入CRC数据计数

/**************************************************************************************
  * @实现效果	  通过PC向MCU发送5个8位数据，MCU返回CRC校验值
  * @操作步骤   接上RXD，TXD短路帽，通过串口工具向MCU发送5个8位数据，MCU返回CRC校验值
**************************************************************************************/
void main()
{
/************************************系统初始化****************************************/
	WDTCCR = 0x00;						  //关闭看门狗
		                          //本例程为方便测试关闭看门狗，实际使用中，建议客户打开看门狗，详见WDT复位例程
	CLKSWR = 0x51;						  //选择内部高频RC为系统时钟，内部高频RC 2分频，Fosc=16MHz
	CLKDIV = 0x01;						  //Fosc 1分频得到Fcpu，Fcpu=16MHz 
/**********************************相关配置初始化**************************************/
	P2M0 = P2M0&0x0F|0x80;			//P21设置为推挽输出
	P0M1 = P0M1&0x0F|0x20;			//P03设置为上拉输入
	TXD_MAP = 0x21;						  //TXD映射P21
	RXD_MAP = 0x03;						  //RXD映射P03		
	T4CON = 0x06;						    //T4工作模式：UART1波特率发生器
  TH4 = 0xFF; 
	TL4 = 0x98;							    //波特率9600
	SCON2 = 0x02;						    //8位UART，波特率可变
	SCON = 0x10;						    //允许串行接收
	IE |= 0X10;							    //使能串口中断
/**********************************CRC配置初始化***************************************/
	CRCC = 0x07;					      //CRC复位，LSB first，复位初值为0xFFFF

	EA = 1;

	while(1)
	{
		if(guc_UARTFlag)
		{
			IE &=~ 0x10;				                     //失能UART1中断
			gui_CrcResault = CRC_CalcCRC(guc_UARTbuf_a,sizeof(guc_UARTbuf_a));	
										                           //写入校验数据并获取CRC效验值
			memcpy(guc_CrcValue_a,&gui_CrcResault,2);//内存拷贝函数
			for(guc_i = 0;guc_i< 2;guc_i++)
			{
				SBUF = guc_CrcValue_a[guc_i];          //发送8位串口数据
				while(!(SCON & 0x02));
				SCON &=~ 0x02;			                   //清除发送中断标志位
			}
			CRCC = 0x07;				                     //CRC复位，LSB first，复位初值为0xFFFF
			IE |= 0x10;					                     //UART1中断使能
			guc_UARTFlag = 0;			                   //标志位清零
			guc_UARTCnt = 0;			                   //计数清零
			SCON |= 0x10;				                     //UART1接收使能
		}	
	}
}

/***************************************************************************************
  * @说明  	UART1中断服务函数
  *	@参数	  无
  * @返回值 无
  * @注		  无
***************************************************************************************/
void UART1_Rpt(void) interrupt UART1_VECTOR
{
	if(SCON&0x01)						                //判断接收中断标志位
	{	
		guc_UARTbuf_a[guc_UARTCnt++] = SBUF;  //转存8位串口接收数据
		if(guc_UARTCnt >= 5)
		{
			SCON &=~ 0x10;			               	//失能UART1接收
			guc_UARTFlag = 1;
		}
		SCON &=~ 0x01;			              		//清除接收中断标志位
	}									
}

/**
  * @说明  	写入需要校验的数据并返回校验结果
  * @参数  	*fucp_CheckArr : CRC校验数据首地址
  * @参数  	fui_CheckLen : CRC校验数据长度
  *         取值范围 0 - 65535
  * @返回值 CRC校验结果。
  			    低位在前，高位在后
  * @注		  无
  */
unsigned int CRC_CalcCRC(unsigned char *fucp_CheckArr,unsigned int fui_CheckLen)
{
	while(fui_CheckLen--)CRCL = *(fucp_CheckArr++);
	return CRCR;
}