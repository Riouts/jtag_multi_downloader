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

unsigned int CRC_CalcCRC(unsigned char *fucp_CheckArr,unsigned int fui_CheckLen);                  //写入需要校验的数据并且返回校验值
void Flash_EraseBlock(unsigned int fui_Address);                                                   //扇区擦除
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address);                        //写入一个字节数据到Flash里面
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//写入任意长度的数据到FLASH里面
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr); //从FLASH里面读取任意长度的数据
void Delay(unsigned int fui_i);			                                                               //延时函数

unsigned char guc_StoredData_a[5] = {0x01,0x02,0x03,0x04,0x05};  //存储的数据
unsigned char guc_ReadData_a[5] = {0x00};                        //读取的数据			
unsigned int  gui_CRCStoredValue = 0;	                           //CRC校验存储数据
unsigned int  gui_CRCReadValue = 0;		                           //CRC校验读取数据

/**************************************************************************************
  * @实现效果     往0X2B00地址写字节，CRC校验，如果校验值不正确正确则等待，否则LED1闪烁
  * @操作步骤     往0X2B00地址写字节
**************************************************************************************/
void main()
{
/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗
		                        //本例程为方便测试关闭看门狗，实际使用中，建议客户打开看门狗，详见WDT复位例程
	CLKSWR = 0x51;						//选择内部高频RC为系统时钟，内部高频RC 2分频，Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1分频得到Fcpu，Fcpu=16MHz 
/**********************************相关配置初始化**************************************/
	P0M0 = P0M0&0xF0|0x08;		//P00设置为推挽输出
/**********************************CRC配置初始化***************************************/
	FREQ_CLK = 0x10;					//指明当前系统时钟
	
//	Flash_EraseBlock(0x2B00);			//擦除首地址为0x2B00的扇区的数据
//	Flash_WriteArr(0x2B00,5,guc_StoredData_a);//从0x2B00开始向里面写数据
//  以上两句屏蔽时，CRC下面的CRC校验值会不一样，会一直在while(1)处等待，如不屏蔽，CRC校验相同，LED闪烁						
	
	Flash_ReadArr(0x2B00,5,guc_ReadData_a);	             //读取地址0x2B00所在扇区
	CRCC = 0x07;						                             //CRC复位，LSB first，复位初值为0xFFFF
	gui_CRCReadValue = CRC_CalcCRC(guc_ReadData_a,5);    //计算读出扇区数据CRC值
	CRCC = 0x07;						                             //CRC复位，LSB first，复位初值为0xFFFF
	gui_CRCStoredValue = CRC_CalcCRC(guc_StoredData_a,5);//校验存储的数据的CRC值
	if(gui_CRCStoredValue != gui_CRCReadValue)           //比较两个CRC校验值
	{
		while(1);
	}
	while(1)
	{
		P0_0 =~ P0_0;
		Delay(250);
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

/**
  * @说明  	扇区擦除，约消耗5ms的时间
  * @参数  	fui_Address ：被擦除的扇区内的任意一个地址
  * @返回值 无
  * @注		  只要操作扇区里面的任意一个地址，就可以擦除此扇区
  */
#pragma disable							 //确保调整时不会进中断导致调整失败
void Flash_EraseBlock(unsigned int fui_Address)
{
	IAP_CMD = 0xF00F;				    //Flash解锁
	IAP_ADDR = fui_Address;			//写入擦除地址
	IAP_CMD = 0xD22D;				    //选择操作方式， 扇区擦除
	IAP_CMD = 0xE11E; 				  //触发后IAP_ADDRL&IAP_ADDRH指向0xFF，同时自动锁定
}

/**
  * @说明  	写入一个字节数据到Flash里面
  * @参数  	fui_Address ：FLASH地址
  *	@参数 	fucp_SaveData：写入的数据存放区域的首地址
  * @返回值 无
  * @注	  	写之前必须先对操作的扇区进行擦除
  */
#pragma disable							//确保调整时不会进中断导致调整失败
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				    //Flash解锁
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				    //字节编程
	IAP_CMD=0xE11E;			     	//触发一次操作
}

/**
  * @说明  	写入任意长度的数据到FLASH里面
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数 	fuc_Length ： 写入数据长度
  *			    取值范围：0x00-0xFF
  *	@参数	 *fucp_SaveArr：写入的数据存放区域的首地址
  * @返回值 无
  * @注		  写之前必须先对操作的扇区进行擦除
  */ 
#pragma disable							//确保调整时不会进中断导致调整失败
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	unsigned char fui_i = 0;
	for(fui_i=0;fui_i<fuc_Length;fui_i++)
	{
		FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
	}
}

/**
  * @说明  	从FLASH里面读取任意长度的数据
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数	  fuc_Length ：读取数据长度
  *			    取值范围：0x00-0xFF
  *	@参数	 *fucp_SaveArr：读取数据存放的区域首地址
  * @返回值 无
  * @注		  无
  */
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	while(fuc_Length--)
	*(fucp_SaveArr++)=*((unsigned char code *)(fui_Address++));//读取数据
}

/**
  * @说明  	延时函数
  * @参数  	fui_i : 延时时间
  * @返回值 无
  * @注   	Fcpu = 16MHz，fui_i = 1时，延时时间约为1Ms
  */
void Delay(unsigned int fui_i)
{
	unsigned int fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --);
}