/** $Id$ $DateTime$
 *  @file 24C16.h
 *  @brief This header file declares exported AT24C16 
 *  @version 0.0.1
 *  @since 0.0.1
 *  @author guoyumin<guoym@bstar.com.cn> 
 *  @date 2009-09-15    Created it
 */
/******************************************************************************
*@note
    Copyright 2007, BeiJing Bluestar Corporation, Limited ALL RIGHTS RESERVED
Permission is hereby granted to licensees of BeiJing Bluestar, Inc. products
to use or abstract this computer program for the sole purpose of implementing
a product based on BeiJing Bluestar, Inc. products. No other rights to reproduce, 
use, or disseminate this computer program,whether in part or in whole, are 
granted. BeiJing Bluestar, Inc. makes no representation or warranties with 
respect to the performance of this computer program, and specifically disclaims
any responsibility for any damages, special or consequential, connected with the
use of this program.For details, see http://www.bstar.com.cn/ 
******************************************************************************/
#ifndef _24c16_H
#define _24c16_H



/** 
* @fn iic_send_start 
* @brief  iic_send_start 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void iic_send_start(void);

/** 
* @fn iic_send_stop 
* @brief  iic_send_stop 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void iic_send_stop(void);  /* IIC操作结束 */

/** 
* @fn iic_send_char 
* @brief  iic_send_char 
* @param[in] x send char. 
* @param[out] none. 
* @return none. 
*/
void iic_send_char(uint8_t x);   /* 向IIC送出字节 */

/** 
* @fn Iic_read_byte 
* @brief  Iic_read_byte 
* @param[in] read byte form addr. 
* @param[out] none. 
* @return read byte. 
*/
uint8_t Iic_read_byte(uint16_t addr); 

/** 
* @fn Iic_write_byte 
* @brief  Iic_write_byte 
* @param[in] weite byte x to addr. 
* @param[out] none. 
* @return none. 
*/
void Iic_write_byte(uint16_t addr, uint8_t x); 

#endif







