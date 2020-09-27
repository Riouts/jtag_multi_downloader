/** $Id$ $DateTime$
 *  @file system.h
 *  @brief This header file declares exported system 
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
#ifndef _SYSTEM_H
#define _SYSTEM_H

/** 
* @fn Wait_power_on 
* @brief  Wait_power_on 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Wait_power_on(void);

/** 
* @fn go_power_on 
* @brief  go_power_on 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void go_power_on(void);

/** 
* @fn jiji 
* @brief  jiji 
* @param[in] uint8. 
* @param[out] none. 
* @return none. 
*/
void jiji(uint8_t count);

/** 
* @fn system_Init 
* @brief  system_Init 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void system_Init(void);

/** 
* @fn Mcu_Module_Init 
* @brief  Mcu_Module_Init
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Mcu_Module_Init(void);

/** 
* @fn AVB_cool_reset 
* @brief  AVB_cool_reset 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void AVB_cool_reset(void);

/** 
* @fn AVB_System_WatchDog 
* @brief  AVB_System_WatchDog 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void System_Power_WatchDog(void);

/** 
* @fn AVB_States_WatchDog 
* @brief  AVB_States_WatchDog 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void AVB_States_WatchDog(void);

/** 
* @fn AVB_FanNet_WatchDog 
* @brief  AVB_FanNet_WatchDog 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void AVB_FanNet_WatchDog(void);

/** 
* @fn RCC_Configuration
* @brief  RCC_Configuration 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void RCC_Configuration(void);
/** 
* @fn GPIO_Configuration
* @brief  GPIO_Configuration
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/

void RCC_Configuration1(void);

 void GPIO_Configuration(void);
/** 
* @fn AVB_FanNet_WatchDog 
* @brief  AVB_FanNet_WatchDog 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void NVIC_Configuration(void);

/** 
* @fn AVB_FanNet_WatchDog 
* @brief  AVB_FanNet_WatchDog 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/

void USART_Configuration(void);

void SET_PA15PB3PB4(void);

#endif


