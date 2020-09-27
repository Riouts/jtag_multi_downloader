#include "main.h"
				  
////////////////////////////////////////////////////////////////////////////////// 
	   
//��ʼ��ADC,ADC ģ��ĳ�ʼ��
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	//GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 

	RCC_ADCCLKConfig(RCC_PCLK2_Div2);   //����ADC��Ƶ����2 24M/2=12M,ADC���ʱ�䲻�ܳ���14M



	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	
	
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	
  ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȼ��
  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
uint16_t Get_Adc(uint8_t ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_1Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ7.5+12.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

/*
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u16 ad_val=0,ad_max=0,ad_min=0xfff;
	u8 t,t1;//,i,j;
	
	for(t=0;t<times;t++)
	{
		t1=15;
		while(t1--);
		
		//temp_val+=Get_Adc(ch);
		ad_val=Get_Adc(ch);
		temp_val+=ad_val;
		if(ad_max<ad_val)ad_max=ad_val;
		if(ad_min>ad_val)ad_min=ad_val;		
	}

	temp_val-=ad_max;
	temp_val-=ad_min;
	
	times-=2;
	return temp_val/times;
} 	 
*/


u8 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u16 ad_val=0,ad_max=0,ad_min=0xfff;
	u8 t,t1;//,i,j;
	
	for(t=0;t<times;t++)
	{
		t1=15;
		while(t1--);
		
		//temp_val+=Get_Adc(ch);
		ad_val=Get_Adc(ch);
		temp_val+=ad_val;
		if(ad_max<ad_val)ad_max=ad_val;
		if(ad_min>ad_val)ad_min=ad_val;		
	}

	temp_val-=ad_max;
	temp_val-=ad_min;
	
	times-=2;
	temp_val/=times;
	temp_val>>=4;
	
	return temp_val;
} 	 

























