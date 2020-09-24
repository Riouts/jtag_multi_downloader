/** $Id$ $DateTime$
 *  @file UART.h
 *  @brief This header file declares exported UART 
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
#ifndef _UART_H
#define _UART_H

#define UART_send_buf_length 16         /* 定义串口发送缓冲区容量 */
#define UART_recv_buf_length 26         /* 定义串口接收缓冲区容量 */


/** 
* @fn UART_DP 
* @brief  UART_DP 
* @param[in] unsigned char. 
* @param[out] none. 
* @return none. 
*/
void UART_DP(unsigned char x);

/** 
* @fn UART_Send_Key1 
* @brief  UART_Send_Key1 
* @param[in] uint8,uint8,uint8. 
* @param[out] none. 
* @return none. 
*/
void UART2_Send_Key1(uint16_t cmd_is_KB_RC, uint16_t cmd_Key_State, uint16_t cmd_Key1);

/** 
* @fn UART_Send_Key2 
* @brief  UART_Send_Key2 
* @param[in] uint8,uint8,uint8. 
* @param[out] none. 
* @return none. 
*/
void UART2_Send_Key2(uint16_t cmd_is_KB_RC, uint16_t cmd_Key_State, uint16_t cmd_Key1,uint16_t cmd_Key2);

/** 
* @fn UART_proc 
* @brief  UART_proc 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void UART_proc(void);

/** 
* @fn UART_Send_Alarm 
* @brief  UART_Send_Alarm 
* @param[in] uint8,uint8. 
* @param[out] none. 
* @return none. 
*/
void UART2_Send_Alarm(uint16_t cmd_Fun, uint16_t cmd_State);
/** 
* @fn UART_recv_buf_CLR 
* @brief  UART_recv_buf_CLR
* @param[in] none 
* @param[out] none. 
* @return none. 
*/
void UART_recv_buf_CLR(void);

/** 
* @fn USART2_IRQHandler
* @brief  USART2_IRQHandler
* @param[in] none 
* @param[out] none. 
* @return none. 
*/
void USART2_Init(void);
/** 
* @fn Send_char
* @brief  Send_char
* @param[in] none 
* @param[out] none. 
* @return none. 
*/
void Usart2_send_char(uint16_t Data);

#endif

