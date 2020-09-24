#ifndef _DELAY_H
#define _DELAY_H
#include "stdint.h"

/**
*@Delay2TCK 
*@brief  Delay2TCK
*@param[in] uint32_t. 
*@param[out] none. 
*@return none. 
**/
void Delay2TCK(uint32_t Count);
void I2C_delay(void);
void delay5ms(void);
void delay100ms(void);
void delay1s(void);
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
void delay_s(uint16_t s);
#endif


