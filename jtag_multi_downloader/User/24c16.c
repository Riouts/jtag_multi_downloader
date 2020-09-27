/** $Id$ $DateTime$ 
*  @file 24C16.c 
*  @brief This file implements all IPCs in whole system. 
*  @version 0.0.1 
*  @since 0.0.1 
*  @author tianzhizhong<tzz@bstar.com.cn> 
*  @date 2007-05-18    Created it 
*  @author tianzhizhong<tzz@bstar.com.cn> 
*  @date 2007-05-16    do some modifications 
*  @author luoyuanhao<luoyh@bstar.com.cn> 
*  @date 2009-05-16    modify for dvx 
*/
/******************************************************************************
*@note    Copyright 2007, BeiJing Bluestar Corporation, Limited
                     ALL RIGHTS RESERVED 
Permission is hereby granted to licensees of BeiJing Bluestar, Inc. products 
to use or abstract this computer program for the sole purpose of implementing 
a product based on BeiJing Bluestar, Inc. products. No other rights to 
reproduce, use, or disseminate this computer program,whether in part or  in 
whole, are granted. BeiJing Bluestar, Inc. makes no representation or 
warranties with respect to the performance of this computer program, and 
specifically disclaims any responsibility for any damages, special or consequential, 
connected with the use of this program. 
For details, see http://www.bstar.com.cn/
******************************************************************************/
#include "main.h"

uint8_t IIC_OK = 0;


/** 
* @fn iic_send_start 
* @brief  iic_send_start 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void iic_send_start(void)  /*IIC操作开始*/
{
    IIC_SCL = 0;
    Delay2TCK(20);
    IIC_SDAO = 1;
    Delay2TCK(20);
    IIC_SCL = 1;
    Delay2TCK(20);
    IIC_SDAO = 0;
    Delay2TCK(20);
    IIC_SCL = 0;
    Delay2TCK(20);
    return;
}

/** 
* @fn iic_send_stop 
* @brief  iic_send_stop 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void iic_send_stop(void)   /* IIC操作结束 */
{
    IIC_SCL = 0;
    Delay2TCK(20);
    IIC_SDAO = 0;
    Delay2TCK(20);
    IIC_SCL = 1;
    Delay2TCK(20);
    IIC_SDAO = 1;
    Delay2TCK(20);
    return;
}

/** 
* @fn iic_send_char 
* @brief  iic_send_char 
* @param[in] x send char. 
* @param[out] none. 
* @return none. 
*/
void iic_send_char(uint8_t x)/* 向IIC送出字节 */
{
    uint8_t count = 0;
    IIC_SCL = 0;
    Delay2TCK(8);
    for(count = 0; count < 8; count++)
    {
        IIC_SDAO = x & 0x80;
        Delay2TCK(20);
        IIC_SCL = 1;
        Delay2TCK(20);
        Delay2TCK(20);
        IIC_SCL = 0;
        Delay2TCK(20);
        x <<= 1;
    }
    IIC_SDAO = 1;
    Delay2TCK(20);
    IIC_SCL = 1;
    Delay2TCK(20);
    IIC_OK = IIC_SDAO;
    IIC_OK = ~IIC_OK;
    Delay2TCK(20);
    IIC_SCL = 0;
    Delay2TCK(20);
    return;
}

/** 
* @fn iic_rece_char 
* @brief  iic_rece_char 
* @param[in] none. 
* @param[out] none. 
* @return rece char. 
*/
uint8_t iic_rece_char(void)  /* 从IIC接收字节 */
{
    uint8_t count = 0;
    uint8_t  buf = 0;
    IIC_SCL = 0;
    Delay2TCK(20);
    IIC_SDAO = 1;
    Delay2TCK(20);
    IIC_SCL = 1;
    Delay2TCK(20);
    for(count = 0; count < 8; count++)
    {
        buf <<= 1;
        if(IIC_SDAI == 0)
        {
            buf &= 0xfe;
        }
        else
        {
            buf |= 0x01;
        }
        Delay2TCK(20);
        IIC_SCL = 0;
        Delay2TCK(20);        
        IIC_SCL = 1;
        Delay2TCK(20);
    }
    IIC_OK = IIC_SDAI;
    Delay2TCK(20);
    IIC_SCL = 0;
    Delay2TCK(20);
    return buf;
}

/** 
* @fn Iic_read_byte 
* @brief  Iic_read_byte 
* @param[in] read byte form addr. 
* @param[out] none. 
* @return read byte. 
*/
uint8_t Iic_read_byte(uint16_t addr)  
{   /* 从EEPROM的指定地址处读取1个字节数据 */
    union
    {
        uint16_t word;
        struct
        {
            uint8_t low;
            uint8_t high;
        }
        bytes;
    }
    u1;
    uint8_t x = 0;
    uint8_t command_w = 0; 
    uint8_t command_r = 0;
    u1.word = 0;
    u1.bytes.high = 0;
    u1.bytes.low = 0;
    u1.word = addr;
    command_w = 0xa0 | ((u1.bytes.high << 1) & 0x0e);
    command_r = command_w | 0x1;
    iic_send_start();
    iic_send_char(command_w);
    iic_send_char(u1.bytes.low);
    iic_send_start();
    iic_send_char(command_r);
    x = iic_rece_char();
    iic_send_stop();
    return x;
}

/** 
* @fn Iic_write_byte 
* @brief  Iic_write_byte 
* @param[in] weite byte x to addr. 
* @param[out] none. 
* @return none. 
*/
void Iic_write_byte(uint16_t addr, uint8_t x) 
{   /* 向EEPROM的指定地址写入一个字节数据 */
    union
    {
        uint16_t word;
        struct
        {
            uint8_t low;
            uint8_t high;
					  
        }
        bytes;
    }
    u1;
    uint8_t command_w = 0;
    u1.word = 0;
    u1.bytes.high = 0;
    u1.bytes.low = 0;
    u1.word = addr;
    command_w = 0xa0 | ((u1.bytes.high << 1) & 0x0e);
    iic_send_start();
    iic_send_char(command_w);
    iic_send_char(u1.bytes.low);
    iic_send_char(x);
    iic_send_stop();
    Iic_write_delay();
    return;
}
