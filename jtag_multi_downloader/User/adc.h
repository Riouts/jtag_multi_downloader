#ifndef _adc_H
#define _adc_H

void  Adc_Init(void);
uint16_t  Get_Adc(uint8_t ch);
//uint16_t Get_Adc_Average(u8 ch,u8 times);
uint8_t Get_Adc_Average(u8 ch,u8 times);

#endif


