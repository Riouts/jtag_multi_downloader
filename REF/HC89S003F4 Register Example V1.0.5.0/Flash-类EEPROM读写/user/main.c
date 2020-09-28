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
*	1、Flash擦写次数10万次以上
*	2、扇区擦除时间约5ms，且擦除时不响应任何中断，但会置相关标志位，擦除完成后响应
*	3、可设置应用程序读保护，应用程序写保护（以4K字节为保护单位）
*	4、可以设置仿真器扇区读保护，扇区写保护（以4K字节为保护单位）
*	5、设置保护后无法擦写程序，读取的数据全为零
* 6、每一颗MCU在出厂时会固化一个CHIP_ID，一共8个字节，一颗芯片一个ID，不会重复
*	************************************************************************************
*									 应用注意事项
*	1、CPU时钟需要配置为1-16MHz之间的正整数，且Flash擦写之前需要配置FREQ_CLK寄存器，该寄
*	   存器值即为当前CPU时钟频率。
*	2、扇区擦除写入过程中不能被打断
*	3、数据存放地址需要在程序存放地址之后
*	4、第二复位向量使能时，无法在仿真环境下查看code区数据
* 5、Flsah操作最低电压限制为2.0V，所以建议进行Flash操作前进行电压检测或者打开BOR，BOR电
*    压建议设置为2.4V及2.4V以上
*	6、建议在进行IAP操作前先判断LVD电压，等待电压稳定后再进行IAP操作
*	7、IAP操作函数应与与程序区分开,详情请查阅IAP操作应用手册
*	8、建议在进行Flash擦写操作前关闭中断，擦写完成后再打开中断
*	************************************************************************************
*  								       客户服务
*	感谢您使用我们的单片机，若发现错误或对函数的使用存在疑问。请添加上海芯圣电子官方QQ群
*	****************************技术支持群：201030494***********************************
*   ************************************************************************************
**/

#define ALLOCATE_EXTERN
#include "HC89S003F4.h"

void Flash_EraseBlock(unsigned int fui_Address);//扇区擦除
void FLASH_WriteData(unsigned char fui_Address, unsigned int fuc_SaveData);//写入一个数据
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//写入任意长度数据
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//读取任意长度数据

unsigned char guc_Write_a[5] = {0x11,0x12,0x13,0x14,0x15};	//写入数据
unsigned char guc_Read_a[5] = {0x00};			//用于存放读取的数据
unsigned char guc_Uartflag = 0;					  //发送标志位
unsigned char guc_Uartcnt = 0;					  //发送计数
unsigned char guc_Uartbuf_a[2] = {0x00};	//缓存数组

/***************************************************************************************
  * @实现效果	在地址0x3B00到0x3B04连续写入5个数据，通过串口工具发送地址可以读取相对应
  				    的数据。当检测到VDD电压值低于LVD设置电压值，LED亮；检测到VDD电压值高于
              LVD设定电压值，LED灭。
  * @操作步骤 接上RXD TXD短路帽，通过串口工具向单片机发送以0x2B为帧头的数据，返回对应
              对应地址的数据。
***************************************************************************************/
void main()
{
/************************************系统初始化****************************************/
	WDTCCR = 0x00;						//关闭看门狗
		                        //本例程为方便测试关闭看门狗，实际使用中，建议客户打开看门狗，详见WDT复位例程
	CLKSWR = 0x51;						//选择内部高频RC为系统时钟，内部高频RC 2分频，Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1分频得到Fcpu，Fcpu=16MHz 
/**********************************相关配置初始化**************************************/
	P0M0 = P0M0&0xF0|0x08;		//P03设置为上拉输出	
	P2M0 = P2M0&0x0F|0x80;		//P21设置为推挽输出
	P0M1 = P0M1&0x0F|0x20;		//P03设置为上拉输出
	P0_0=1;
	TXD_MAP = 0x21;					  //TXD映射P21
	RXD_MAP = 0x03;					  //RXD映射P03		
	T4CON = 0x06;						  //T4工作模式：UART1波特率发生器
  TH4 = 0xFF;
	TL4 = 0x98;							  //波特率9600
	SCON2 = 0x02;						  //8位UART，波特率可变
	SCON = 0x10;						  //允许串行接收
	IE |= 0x10;							  //使能串口中断
/**********************************Flash配置初始化*************************************/
	FREQ_CLK = 0x10;				  //指明当前系统时钟	
	LVDC = 0xAC;						  //LVD设置3.0V,禁止中断
	//	消抖时间 = 	(0xFF + 2) * 1/Fcpu
	//			 =	(0xFF + 2) / 16000000	（当前的CPU时钟）
	//			 =	16.0625us
	LVDDBC = 0xFF;					  //设置消抖时间
	LVDC &=~ 0x08;			      //清除LVD中断标志位 

	Flash_EraseBlock(0x3B00);	//擦除地址0x2B00所在扇区
	Flash_WriteArr(0x3B00,5,guc_Write_a);//在地址0x2B00写入数据
	Flash_ReadArr(0x3B00,5,guc_Read_a);	//读取地址0x2B00所在扇区
	EA = 1;								    //使能总中断
	while(1)
	{
		if(guc_Uartflag)
		{
			IE &=~ 0x10;				   //失能UART1中断
			if(guc_Uartbuf_a[0] == 0x3B)
			{
				switch(guc_Uartbuf_a[1])
				{
					case 0x00:	SBUF = guc_Read_a[0];//发送8位串口数据
								break;
					case 0x01:	SBUF = guc_Read_a[1];//发送8位串口数据
								break;
					case 0x02:	SBUF = guc_Read_a[2];//发送8位串口数据
								break;
					case 0x03:	SBUF = guc_Read_a[3];//发送8位串口数据
								break;
					case 0x04:	SBUF = guc_Read_a[4];//发送8位串口数据
								break;
					default:break;
					while(!(SCON&0x02));	//等待发送完毕
					SCON &=~ 0x02;;			  //清除发送中断标志位
				}
				IE |= 0x10;						  //UART1中断使能
				guc_Uartflag = 0;				//标志位清零
				guc_Uartcnt = 0;				//标志位清零
				SCON |= 0x10;					  //UART1接收使能	
			}
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
	if(SCON&0x01)							  //判断接收中断标志位
	{
		guc_Uartbuf_a[guc_Uartcnt++] = SBUF;//转存8位串口接收数据
		if(guc_Uartcnt >= 2)
		{
			SCON &=~ 0x10;					//失能UART1接收
			guc_Uartflag = 1;
		}
		SCON &=~ 0x01;						//清除接收中断标志位
	}
}
/**
  * @说明  	扇区擦除，，约消耗5ms的时间，
  *         该函数需绝对地址编译，详情请查阅IAP操作应用手册
  * @参数  	fui_Address ：被擦除的扇区内的任意一个地址
  * @返回值 无
  * @注		  只要操作扇区里面的任意一个地址，就可以擦除此扇区
  */
void Flash_EraseBlock(unsigned int fui_Address)
{
	while(1)
	{
		LVDC &=~ 0x08;			  //清除LVD中断标志位
		P0_0=0;		
		if((LVDC&0x08)==0)		break;
	}
	P0_0=1;		
	EA=0;
	IAP_CMD = 0xF00F;				//Flash解锁
	IAP_ADDR = fui_Address;	//写入擦除地址
	IAP_CMD = 0xD22D;				//选择操作方式， 扇区擦除
	IAP_CMD = 0xE11E; 			//触发后IAP_ADDRL&IAP_ADDRH指向0xFF，同时自动锁定
	EA=1;
}

/**
  * @说明  	写入一个字节数据到Flash里面
  *         该函数需绝对地址编译，详情请查阅IAP操作应用手册
  * @参数  	fui_Address ：FLASH地址
  *	@参数	  fucp_SaveData：写入的数据
  * @返回值 无
  * @注		  写之前必须先对操作的扇区进行擦除
  */
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	while(1)
	{
		LVDC &=~ 0x08;			   //清除LVD中断标志位
		P0_0=0;		
		if((LVDC&0x08)==0)		break;
	}
	P0_0=1;	
	EA=0;
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				   //Flash解锁
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				   //字节编程
	IAP_CMD=0xE11E;				   //触发一次操作
	EA=1;
}

/**
  * @说明  	写入任意长度的数据到FLASH里面
  *         该函数需绝对地址编译，详情请查阅IAP操作应用手册
  * @参数  	fui_Address ：FLASH起始地址
  *	@参数	  fuc_Length ： 写入数据长度
  *			    取值范围：0x00-0xFF
  *	@参数  *fucp_SaveArr：写入的数据存放区域的首地址
  * @返回值 无
  * @注		  写之前必须先对操作的扇区进行擦除
  */
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	unsigned char fui_i = 0;
	EA=0;
	for(fui_i=0;fui_i<fuc_Length;fui_i++)
	{
		FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
	}
	EA=1;
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