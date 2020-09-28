/**
*   ************************************************************************************
*								�Ϻ�оʥ���ӹɷ����޹�˾
*								    www.holychip.cn
*	************************************************************************************
*	@Examle Version		V1.0.5.0
*	@Demo 	Version		V1.0.4.0
*	@Date				2019.12.27
*	************************************************************************************
*									 ģ�����ܽ���
*	1��Flash��д����10�������
*	2����������ʱ��Լ5ms���Ҳ���ʱ����Ӧ�κ��жϣ���������ر�־λ��������ɺ���Ӧ
*	3��������Ӧ�ó����������Ӧ�ó���д��������4K�ֽ�Ϊ������λ��
*	4���������÷���������������������д��������4K�ֽ�Ϊ������λ��
*	5�����ñ������޷���д���򣬶�ȡ������ȫΪ��
* 6��ÿһ��MCU�ڳ���ʱ��̻�һ��CHIP_ID��һ��8���ֽڣ�һ��оƬһ��ID�������ظ�
*	************************************************************************************
*									 Ӧ��ע������
*	1��CPUʱ����Ҫ����Ϊ1-16MHz֮�������������Flash��д֮ǰ��Ҫ����FREQ_CLK�Ĵ������ü�
*	   ����ֵ��Ϊ��ǰCPUʱ��Ƶ�ʡ�
*	2����������д������в��ܱ����
*	3�����ݴ�ŵ�ַ��Ҫ�ڳ����ŵ�ַ֮��
*	4���ڶ���λ����ʹ��ʱ���޷��ڷ��滷���²鿴code������
* 5��Flsah������͵�ѹ����Ϊ2.0V�����Խ������Flash����ǰ���е�ѹ�����ߴ�BOR��BOR��
*    ѹ��������Ϊ2.4V��2.4V����
*	6�������ڽ���IAP����ǰ���ж�LVD��ѹ���ȴ���ѹ�ȶ����ٽ���IAP����
*	7��IAP��������Ӧ����������ֿ�,���������IAP����Ӧ���ֲ�
*	8�������ڽ���Flash��д����ǰ�ر��жϣ���д��ɺ��ٴ��ж�
*	************************************************************************************
*  								       �ͻ�����
*	��л��ʹ�����ǵĵ�Ƭ���������ִ����Ժ�����ʹ�ô������ʡ�������Ϻ�оʥ���ӹٷ�QQȺ
*	****************************����֧��Ⱥ��201030494***********************************
*   ************************************************************************************
**/

#define ALLOCATE_EXTERN
#include "HC89S003F4.h"

void Flash_EraseBlock(unsigned int fui_Address);//��������
void FLASH_WriteData(unsigned char fui_Address, unsigned int fuc_SaveData);//д��һ������
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//д�����ⳤ������
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//��ȡ���ⳤ������

unsigned char guc_Write_a[5] = {0x11,0x12,0x13,0x14,0x15};	//д������
unsigned char guc_Read_a[5] = {0x00};			//���ڴ�Ŷ�ȡ������
unsigned char guc_Uartflag = 0;					  //���ͱ�־λ
unsigned char guc_Uartcnt = 0;					  //���ͼ���
unsigned char guc_Uartbuf_a[2] = {0x00};	//��������

/***************************************************************************************
  * @ʵ��Ч��	�ڵ�ַ0x3B00��0x3B04����д��5�����ݣ�ͨ�����ڹ��߷��͵�ַ���Զ�ȡ���Ӧ
  				    �����ݡ�����⵽VDD��ѹֵ����LVD���õ�ѹֵ��LED������⵽VDD��ѹֵ����
              LVD�趨��ѹֵ��LED��
  * @�������� ����RXD TXD��·ñ��ͨ�����ڹ�����Ƭ��������0x2BΪ֡ͷ�����ݣ����ض�Ӧ
              ��Ӧ��ַ�����ݡ�
***************************************************************************************/
void main()
{
/************************************ϵͳ��ʼ��****************************************/
	WDTCCR = 0x00;						//�رտ��Ź�
		                        //������Ϊ������Թرտ��Ź���ʵ��ʹ���У�����ͻ��򿪿��Ź������WDT��λ����
	CLKSWR = 0x51;						//ѡ���ڲ���ƵRCΪϵͳʱ�ӣ��ڲ���ƵRC 2��Ƶ��Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1��Ƶ�õ�Fcpu��Fcpu=16MHz 
/**********************************������ó�ʼ��**************************************/
	P0M0 = P0M0&0xF0|0x08;		//P03����Ϊ�������	
	P2M0 = P2M0&0x0F|0x80;		//P21����Ϊ�������
	P0M1 = P0M1&0x0F|0x20;		//P03����Ϊ�������
	P0_0=1;
	TXD_MAP = 0x21;					  //TXDӳ��P21
	RXD_MAP = 0x03;					  //RXDӳ��P03		
	T4CON = 0x06;						  //T4����ģʽ��UART1�����ʷ�����
  TH4 = 0xFF;
	TL4 = 0x98;							  //������9600
	SCON2 = 0x02;						  //8λUART�������ʿɱ�
	SCON = 0x10;						  //�����н���
	IE |= 0x10;							  //ʹ�ܴ����ж�
/**********************************Flash���ó�ʼ��*************************************/
	FREQ_CLK = 0x10;				  //ָ����ǰϵͳʱ��	
	LVDC = 0xAC;						  //LVD����3.0V,��ֹ�ж�
	//	����ʱ�� = 	(0xFF + 2) * 1/Fcpu
	//			 =	(0xFF + 2) / 16000000	����ǰ��CPUʱ�ӣ�
	//			 =	16.0625us
	LVDDBC = 0xFF;					  //��������ʱ��
	LVDC &=~ 0x08;			      //���LVD�жϱ�־λ 

	Flash_EraseBlock(0x3B00);	//������ַ0x2B00��������
	Flash_WriteArr(0x3B00,5,guc_Write_a);//�ڵ�ַ0x2B00д������
	Flash_ReadArr(0x3B00,5,guc_Read_a);	//��ȡ��ַ0x2B00��������
	EA = 1;								    //ʹ�����ж�
	while(1)
	{
		if(guc_Uartflag)
		{
			IE &=~ 0x10;				   //ʧ��UART1�ж�
			if(guc_Uartbuf_a[0] == 0x3B)
			{
				switch(guc_Uartbuf_a[1])
				{
					case 0x00:	SBUF = guc_Read_a[0];//����8λ��������
								break;
					case 0x01:	SBUF = guc_Read_a[1];//����8λ��������
								break;
					case 0x02:	SBUF = guc_Read_a[2];//����8λ��������
								break;
					case 0x03:	SBUF = guc_Read_a[3];//����8λ��������
								break;
					case 0x04:	SBUF = guc_Read_a[4];//����8λ��������
								break;
					default:break;
					while(!(SCON&0x02));	//�ȴ��������
					SCON &=~ 0x02;;			  //��������жϱ�־λ
				}
				IE |= 0x10;						  //UART1�ж�ʹ��
				guc_Uartflag = 0;				//��־λ����
				guc_Uartcnt = 0;				//��־λ����
				SCON |= 0x10;					  //UART1����ʹ��	
			}
		}
	}
}

/***************************************************************************************
  * @˵��  	UART1�жϷ�����
  *	@����	  ��
  * @����ֵ ��
  * @ע		  ��
***************************************************************************************/
void UART1_Rpt(void) interrupt UART1_VECTOR
{
	if(SCON&0x01)							  //�жϽ����жϱ�־λ
	{
		guc_Uartbuf_a[guc_Uartcnt++] = SBUF;//ת��8λ���ڽ�������
		if(guc_Uartcnt >= 2)
		{
			SCON &=~ 0x10;					//ʧ��UART1����
			guc_Uartflag = 1;
		}
		SCON &=~ 0x01;						//��������жϱ�־λ
	}
}
/**
  * @˵��  	������������Լ����5ms��ʱ�䣬
  *         �ú�������Ե�ַ���룬���������IAP����Ӧ���ֲ�
  * @����  	fui_Address ���������������ڵ�����һ����ַ
  * @����ֵ ��
  * @ע		  ֻҪ�����������������һ����ַ���Ϳ��Բ���������
  */
void Flash_EraseBlock(unsigned int fui_Address)
{
	while(1)
	{
		LVDC &=~ 0x08;			  //���LVD�жϱ�־λ
		P0_0=0;		
		if((LVDC&0x08)==0)		break;
	}
	P0_0=1;		
	EA=0;
	IAP_CMD = 0xF00F;				//Flash����
	IAP_ADDR = fui_Address;	//д�������ַ
	IAP_CMD = 0xD22D;				//ѡ�������ʽ�� ��������
	IAP_CMD = 0xE11E; 			//������IAP_ADDRL&IAP_ADDRHָ��0xFF��ͬʱ�Զ�����
	EA=1;
}

/**
  * @˵��  	д��һ���ֽ����ݵ�Flash����
  *         �ú�������Ե�ַ���룬���������IAP����Ӧ���ֲ�
  * @����  	fui_Address ��FLASH��ַ
  *	@����	  fucp_SaveData��д�������
  * @����ֵ ��
  * @ע		  д֮ǰ�����ȶԲ������������в���
  */
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	while(1)
	{
		LVDC &=~ 0x08;			   //���LVD�жϱ�־λ
		P0_0=0;		
		if((LVDC&0x08)==0)		break;
	}
	P0_0=1;	
	EA=0;
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				   //Flash����
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				   //�ֽڱ��
	IAP_CMD=0xE11E;				   //����һ�β���
	EA=1;
}

/**
  * @˵��  	д�����ⳤ�ȵ����ݵ�FLASH����
  *         �ú�������Ե�ַ���룬���������IAP����Ӧ���ֲ�
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@����	  fuc_Length �� д�����ݳ���
  *			    ȡֵ��Χ��0x00-0xFF
  *	@����  *fucp_SaveArr��д������ݴ��������׵�ַ
  * @����ֵ ��
  * @ע		  д֮ǰ�����ȶԲ������������в���
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
  * @˵��  	��FLASH�����ȡ���ⳤ�ȵ�����
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@����	  fuc_Length ����ȡ���ݳ���
  *			    ȡֵ��Χ��0x00-0xFF
  *	@����	 *fucp_SaveArr����ȡ���ݴ�ŵ������׵�ַ
  * @����ֵ ��
  * @ע		  ��
  */
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	while(fuc_Length--)
	*(fucp_SaveArr++)=*((unsigned char code *)(fui_Address++));//��ȡ����
}