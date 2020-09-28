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
*	1��16λCRC��
*	2��CRC����У�����CRC-CCITT����ʽ����0x1021��
*	3����ֵ����Ϊ0x0000��0xFFFF��
*	4��������������ͬһ�Ĵ�����
*	************************************************************************************
*									 Ӧ��ע������
*	1��ÿд��һ�δ��������ݣ������������ǰһ�μ�������ͬ���ɡ�
*	2��д������ʱ���Զ�����CRC���㣬����������Զ��رա�
*	************************************************************************************
*  								       �ͻ�����
*	��л��ʹ�����ǵĵ�Ƭ���������ִ����Ժ�����ʹ�ô������ʡ�������Ϻ�оʥ���ӹٷ�QQȺ
*	****************************����֧��Ⱥ��201030494***********************************
*   ************************************************************************************
**/

#define	ALLOCATE_EXTERN
#include "HC89S003F4.h"
#include "string.h"

unsigned int CRC_CalcCRC(unsigned char *fucp_CheckArr,unsigned int fui_CheckLen);                  //д����ҪУ������ݲ��ҷ���У��ֵ
void Flash_EraseBlock(unsigned int fui_Address);                                                   //��������
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address);                        //д��һ���ֽ����ݵ�Flash����
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr);//д�����ⳤ�ȵ����ݵ�FLASH����
void Flash_ReadArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr); //��FLASH�����ȡ���ⳤ�ȵ�����
void Delay(unsigned int fui_i);			                                                               //��ʱ����

unsigned char guc_StoredData_a[5] = {0x01,0x02,0x03,0x04,0x05};  //�洢������
unsigned char guc_ReadData_a[5] = {0x00};                        //��ȡ������			
unsigned int  gui_CRCStoredValue = 0;	                           //CRCУ��洢����
unsigned int  gui_CRCReadValue = 0;		                           //CRCУ���ȡ����

/**************************************************************************************
  * @ʵ��Ч��     ��0X2B00��ַд�ֽڣ�CRCУ�飬���У��ֵ����ȷ��ȷ��ȴ�������LED1��˸
  * @��������     ��0X2B00��ַд�ֽ�
**************************************************************************************/
void main()
{
/************************************ϵͳ��ʼ��****************************************/
	WDTCCR = 0x00;						//�رտ��Ź�
		                        //������Ϊ������Թرտ��Ź���ʵ��ʹ���У�����ͻ��򿪿��Ź������WDT��λ����
	CLKSWR = 0x51;						//ѡ���ڲ���ƵRCΪϵͳʱ�ӣ��ڲ���ƵRC 2��Ƶ��Fosc=16MHz
	CLKDIV = 0x01;						//Fosc 1��Ƶ�õ�Fcpu��Fcpu=16MHz 
/**********************************������ó�ʼ��**************************************/
	P0M0 = P0M0&0xF0|0x08;		//P00����Ϊ�������
/**********************************CRC���ó�ʼ��***************************************/
	FREQ_CLK = 0x10;					//ָ����ǰϵͳʱ��
	
//	Flash_EraseBlock(0x2B00);			//�����׵�ַΪ0x2B00������������
//	Flash_WriteArr(0x2B00,5,guc_StoredData_a);//��0x2B00��ʼ������д����
//  ������������ʱ��CRC�����CRCУ��ֵ�᲻һ������һֱ��while(1)���ȴ����粻���Σ�CRCУ����ͬ��LED��˸						
	
	Flash_ReadArr(0x2B00,5,guc_ReadData_a);	             //��ȡ��ַ0x2B00��������
	CRCC = 0x07;						                             //CRC��λ��LSB first����λ��ֵΪ0xFFFF
	gui_CRCReadValue = CRC_CalcCRC(guc_ReadData_a,5);    //���������������CRCֵ
	CRCC = 0x07;						                             //CRC��λ��LSB first����λ��ֵΪ0xFFFF
	gui_CRCStoredValue = CRC_CalcCRC(guc_StoredData_a,5);//У��洢�����ݵ�CRCֵ
	if(gui_CRCStoredValue != gui_CRCReadValue)           //�Ƚ�����CRCУ��ֵ
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
  * @˵��  	д����ҪУ������ݲ�����У����
  * @����  	*fucp_CheckArr : CRCУ�������׵�ַ
  * @����  	fui_CheckLen : CRCУ�����ݳ���
  *         ȡֵ��Χ 0 - 65535
  * @����ֵ CRCУ������
  			    ��λ��ǰ����λ�ں�
  * @ע		  ��
  */
unsigned int CRC_CalcCRC(unsigned char *fucp_CheckArr,unsigned int fui_CheckLen)
{
	while(fui_CheckLen--)CRCL = *(fucp_CheckArr++);
	return CRCR;
}

/**
  * @˵��  	����������Լ����5ms��ʱ��
  * @����  	fui_Address ���������������ڵ�����һ����ַ
  * @����ֵ ��
  * @ע		  ֻҪ�����������������һ����ַ���Ϳ��Բ���������
  */
#pragma disable							 //ȷ������ʱ������жϵ��µ���ʧ��
void Flash_EraseBlock(unsigned int fui_Address)
{
	IAP_CMD = 0xF00F;				    //Flash����
	IAP_ADDR = fui_Address;			//д�������ַ
	IAP_CMD = 0xD22D;				    //ѡ�������ʽ�� ��������
	IAP_CMD = 0xE11E; 				  //������IAP_ADDRL&IAP_ADDRHָ��0xFF��ͬʱ�Զ�����
}

/**
  * @˵��  	д��һ���ֽ����ݵ�Flash����
  * @����  	fui_Address ��FLASH��ַ
  *	@���� 	fucp_SaveData��д������ݴ��������׵�ַ
  * @����ֵ ��
  * @ע	  	д֮ǰ�����ȶԲ������������в���
  */
#pragma disable							//ȷ������ʱ������жϵ��µ���ʧ��
void FLASH_WriteData(unsigned char fuc_SaveData, unsigned int fui_Address)
{
	IAP_DATA = fuc_SaveData;
	IAP_CMD=0xF00F;				    //Flash����
	IAP_ADDR = fui_Address;
	IAP_CMD=0xB44B;				    //�ֽڱ��
	IAP_CMD=0xE11E;			     	//����һ�β���
}

/**
  * @˵��  	д�����ⳤ�ȵ����ݵ�FLASH����
  * @����  	fui_Address ��FLASH��ʼ��ַ
  *	@���� 	fuc_Length �� д�����ݳ���
  *			    ȡֵ��Χ��0x00-0xFF
  *	@����	 *fucp_SaveArr��д������ݴ��������׵�ַ
  * @����ֵ ��
  * @ע		  д֮ǰ�����ȶԲ������������в���
  */ 
#pragma disable							//ȷ������ʱ������жϵ��µ���ʧ��
void Flash_WriteArr(unsigned int fui_Address,unsigned char fuc_Length,unsigned char *fucp_SaveArr)
{
	unsigned char fui_i = 0;
	for(fui_i=0;fui_i<fuc_Length;fui_i++)
	{
		FLASH_WriteData(*(fucp_SaveArr++), fui_Address++); 
	}
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

/**
  * @˵��  	��ʱ����
  * @����  	fui_i : ��ʱʱ��
  * @����ֵ ��
  * @ע   	Fcpu = 16MHz��fui_i = 1ʱ����ʱʱ��ԼΪ1Ms
  */
void Delay(unsigned int fui_i)
{
	unsigned int fui_j;
	for(;fui_i > 0;fui_i --)
	for(fui_j = 1596;fui_j > 0;fui_j --);
}