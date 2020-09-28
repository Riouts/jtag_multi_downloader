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
* 1、支持内部VDD多档位电压检测，并且可以产生中断
* 2、支持端口电压检测，并且可以产生中断或复位
* 3、LVD挡位：4.2V/3.9V/3.6V/3.0V/2.6V/2.4V/2.0V/1.9V
*	************************************************************************************
*									 应用注意事项
*	1、LVD有效的中断和复位都可以唤醒空闲/掉电模式。
*	2、LVD检测选择位选择检测P2.6端口电压时，检测VDD电压无效。
*	3、LVD检测VDD电压不能产生复位，电压点必须设置在BOR电压之上。
*	4、掉电/空闲模式下LVD消抖会自动关闭，退出掉电/空闲模式又会自动打开。
*	5、禁止LVD中断允许位，只要允许检测，LVDF也可被置1，但即使此时EA被置1，也不会产生中断
*	   请求。
*	************************************************************************************
*  								       客户服务
*	 感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ
*	****************************技术支持QQ：3198093779**********************************
*   ************************************************************************************
**/

#define ALLOCATE_EXTERN
#include "HC89S003F4.h"

unsigned char guc_Write_a= 0;	//写入数据
unsigned char guc_Read_a = 0; //用于存放读取的数据

void Flash_EraseBlock(unsigned int fui_Address);//扇区擦除
void FLASH_WriteData(unsigned int fui_Address, unsigned char fuc_SaveData);//写入一个数据
void Flash_ReadData(unsigned int fui_Address,unsigned char fuc_SaveArr);   //读一个数据

/***************************************************************************************
  * @实现效果	 将VDD的LVD检测电压消抖时间设置为16.0625us，当电压低4.2V且持续时间超过
  *				     16.0625us，进入LVD中断，擦写FLASH。
  * @注意事项  本范例无法仿真，并且测试时需要拔下仿真器，外部增加大电容，延长掉电时间，
	             LVD电压下降到BOR电压时长至少大于6Ms,一个扇区擦除时长为5MS，写一个字节时
							 长为23us。
***************************************************************************************/
void main()
{
/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗
		                        //本例程为方便测试关闭看门狗，实际使用中，建议客户打开看门狗，详见WDT复位例程
	CLKSWR = 0x51;						//选择内部高频RC为系统时钟，内部高频RC 2分频，Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1分频得到Fcpu，Fcpu=16MHz 
  FREQ_CLK = 0x10;					//指明当前系统时钟
/***********************************LVD配置初始化**************************************/
	LVDC = 0xA7;						  //LVD设置
	//	消抖时间 = 	(0xFF + 2) * 1/Fcpu
	//			 =	(0xFF + 2) / 16000000	（当前的CPU时钟）
	//			 =	16.0625us
	//	现在程序检测的是 VDD 的电压，4.2V
	LVDDBC = 0xFF;						//设置消抖时间    
	EA = 1;								    //使能总中断
	while(1);
}

/***************************************************************************************
  * @说明  	LVD中断服务函数
  * @参数   无
  * @返回值 无
  * @注     无
***************************************************************************************/
void LVD_Rpt() interrupt LVD_VECTOR
{
	if(LVDC&0x08)					                //判断LVD中断标志位
	{	
		LVDC &=~ 0x08;					            //清除LVD中断标志位
		EA=0;
		Flash_ReadData(0x2B00,guc_Read_a);	//读取地址0x2B00所在扇区	
		guc_Write_a=guc_Read_a++;		
		Flash_EraseBlock(0x2B00);
		FLASH_WriteData(0x2B00,guc_Write_a);//在地址0x2B00写入数据	
		Flash_ReadData(0x2B00,guc_Read_a);	//读取地址0x2B00所在扇区				
		EA=1;
	}
}

/**
  * @说明  	扇区擦除，约消耗5ms的时间
  * @参数  	fui_Address ：被擦除的扇区内的任意一个地址
  * @返回值 无
  * @注		  只要操作扇区里面的任意一个地址，就可以擦除此扇区
  */
void Flash_EraseBlock(unsigned int fui_Address)
{
	IAP_CMD = 0xF00F;				//Flash解锁
	IAP_ADDR = fui_Address;	//写入擦除地址
	IAP_CMD = 0xD22D;				//选择操作方式， 扇区擦除
	IAP_CMD = 0xE11E; 			//触发后IAP_ADDRL&IAP_ADDRH指向0xFF，同时自动锁定
}

/**
  * @说明  	写入一个字节数据到Flash里面
  * @参数  	fui_Address ：FLASH地址
  *	@参数	  fucp_SaveData：写入的数据
  * @返回值 无
  * @注		  写之前必须先对操作的扇区进行擦除
  */
void FLASH_WriteData(unsigned int fui_Address, unsigned char fuc_SaveData)
{
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				  //Flash解锁
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				  //字节编程
	IAP_CMD=0xE11E;				  //触发一次操作
}

/**
  * @说明  	从FLASH里面读指定地址的数据
  * @参数  	fui_Address ：FLASH地址
  *	@参数  	fuc_SaveArr ：读取的数据
  * @返回值 无
  * @注		  无
  */
void Flash_ReadData(unsigned int fui_Address,unsigned char fuc_SaveArr)
{
	fuc_SaveArr=*((unsigned char code *)(fui_Address));//读取数据
}
