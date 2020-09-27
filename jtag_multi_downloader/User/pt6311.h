/** $Id$ $DateTime$
 *  @file pt6311.h
 *  @brief This header file declares exported pt6311 
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
#ifndef _PT6311_H
#define _PT6311_H

/** 
* @fn Pt6311_Write_Byte 
* @brief  Pt6311_Write_Byte 
* @param[in] uint8. 
* @param[out] none. 
* @return none. 
*/
void Pt6311_Write_Byte(uint8_t dat);

/** 
* @fn Pt6311_Read_Byte 
* @brief  Pt6311_Read_Byte 
* @param[in] none. 
* @param[out] none. 
* @return uint8. 
*/
uint8_t Pt6311_Read_Byte(void);

/** 
* @fn Pt6311_Init 
* @brief  Pt6311_Init 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Pt6311_Init(void);

/** 
* @fn Read_key 
* @brief  Read_key 
* @param[in] none. 
* @param[out] none. 
* @return uint8. 
*/
uint8_t Read_key(void);

/** 
* @fn KeyProcess 
* @brief  KeyProcess 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void KeyProcess(void);

/** 
* @fn Key_State_Process 
* @brief  Key_State_Process 
* @param[in] none. 
* @param[out] none. 
* @return uint8. 
*/
uint16_t Key_State_Process(void);


#endif




