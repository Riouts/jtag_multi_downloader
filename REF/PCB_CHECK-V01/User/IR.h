/** $Id$ $DateTime$
 *  @file IR.h
 *  @brief This header file declares exported IR 
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
#ifndef _IR_H
#define _IR_H

/** 
* @fn IR_Init 
* @brief  IR_Init 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void IR_Init(void);

/** 
* @fn IRProcess 
* @brief  IRProcess 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void IRProcess(void);

/** 
* @fn IRProcess 
* @brief  IRProcess 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void EXTI9_5_IRQHandler(void);

#endif









