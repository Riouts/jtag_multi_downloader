#include "ds18b20.h"
//#include "delay.h"	

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//DS18B20��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
  
const unsigned char b20rom[4][8]={
{0x28,0xff,0xdb,0x95,0x54,0x14,0x1,0x6a},	
{0x28,0xff,0x7c,0x92,0x54,0x14,0x1,0x8e},
{0x28,0xff,0xdb,0x95,0x54,0x14,0x1,0x6a},
{0x28,0xff,0x7c,0x92,0x54,0x14,0x1,0x8e},

};	 

//��λDS18B20
void DS18B20_Rst(void)	   
{                 
	//DS18B20_IO_OUT(); //SET PA0 OUTPUT
	GPIOB->CRL&=0XFFFFFF0F;
	GPIOB->CRL|=0X30;
	DS18B20_DQ_OUT=1;
    DS18B20_DQ_OUT=0; //����DQ
    delay_us(700);    //����750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(300);     //300US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_IO_IN();//SET PA0 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)
		return 1;	    
	return 0;
}
//��DS18B20��ȡһ��λ
//����ֵ��1/0
uint8_t DS18B20_Read_Bit(void) 			 // read one bit
{
    uint8_t data;
	DS18B20_IO_OUT();//SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; 
	delay_us(2);
    DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();//SET PA0 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    delay_us(50);           
    return data;
}
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
uint8_t DS18B20_Read_Byte(void)    // read one byte
{        
    uint8_t i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(uint8_t dat)     
 {             
    uint8_t j;
    uint8_t testb;
	DS18B20_IO_OUT();//���� PA0 Ϊ���ģʽ;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
}
//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	//��λds18b20   
		DS18B20_Check();//���ds18b20�Ƿ����	 
    DS18B20_Write_Byte(0xcc);// skip rom  д���ֽ�
    DS18B20_Write_Byte(0x44);// convert   
} 
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS18B20�Ĵ���
//����1:������
//����0:����    	 
uint8_t DS18B20_Init(void)
{
	/*
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PORTA��ʱ�� 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PORTA0 �������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_0);    //���1
*/
	DS18B20_Rst();

	return DS18B20_Check();
}  
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
short DS18B20_Get_Temp(void)
{
    uint8_t temp;//,k;
    uint8_t TL,TH;
	short tem;
    DS18B20_Start ();                    // ds1820 start convert
 //   DS18B20_Rst();
 //   DS18B20_Check();	 
 
	/*
			DS18B20_Write_Byte(0x55);
			for(k=0;k<8;k++)
			{
				DS18B20_Write_Byte(b20rom[0][k]);
			}
		*/	
		delay_ms(500);
		DS18B20_Rst();
	
		DS18B20_Write_Byte(0xCC);
    DS18B20_Write_Byte(0xbe);// convert	    
    TL=DS18B20_Read_Byte(); // LSB   
    TH=DS18B20_Read_Byte(); // MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    tem=(float)tem*0.625;//ת��     
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
} 
 
