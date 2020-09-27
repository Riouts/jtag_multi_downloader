#include "main.h"

/**
*@Delay2TCK 
*@brief  Delay2TCK
*@param[in] uint32_t. 
*@param[out] none. 
*@return none. 
**/
void Delay2TCK(uint32_t Count)
{
    while(Count)
    {
        Count--;	
    }	
}
/**
*@Delay2TCK 
*@brief  Delay2TCK
*@param[in] uint32_t. 
*@param[out] none. 
*@return none. 
**/
void I2C_delay(void)
{
	  uint32_t count=0x20;
    while(count)
    {
        count--;	
    }	
}

void delay5ms(void)
{
   uint32_t count=0x23d4;
    while(count>0)
    {
        count--;
	      WDI();
    }	
}


void delay100ms(void)
{
    uint32_t count=0x2cca2;
    while(count)
    {
        count--;
	  WDI();
    }	
}

void delay1s(void)
{
    uint32_t count=0x1bfe54;//0x954c6;//0x1bfe54;
    while(count)
    {
        count--;
	  WDI();
    }	
}


void delay1ms(void)
{
   uint32_t count=0x072A;//0x260;//0x072A;
    while(count>0)
    {
        count--;
	      WDI();
    }	
}

//@24MHz
void delay_s(uint16_t s)
{
	while(s--){delay_ms(1000);}
}

void delay_ms(uint16_t ms)
{
	while(ms--){delay_us(975);}//去掉TIMER2中断程序执行时间
}

void delay_us(uint16_t us)
{
	u8 i=0;
	while(us--){i++;i--;i++;i--;i++;i--;i++;i--;}
}



