/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _MAIN_H
#define _MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stdio.h"
#include "string.h"
#include "stm32f10x.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_iwdg.h"
#include "absacc.h"
#include "STM32F10X_bitband.h"
#include "core_cm3.h"
#include "misc.h"
#include "timer.h"
#include "iwdg.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "system.h"
#include "stm32f10x_pwr.h"
#include "led.h"
#include "stm32f10x_bkp.h"
#include "update.h"
#include "stm32f10x_wwdg.h"
#include "stdint.h"
#include "adc.h"
#include "stm32f10x_adc.h"
#include "exit.h"
#include "delay.h"
#include "ds18b20.h"

/*---------------------------------------------------------------------------*/

#define FPVersion '5'                  /* 前板主版本号 */
#define FPsubVersion 0x06              /* 前板从版本号 */




#define true  1
#define false 0

#define TRUE  1
#define FALSE 0



//#define   LED1_ON     	PC15OUT=0
//#define		LED1_OFF    	PC15OUT=1
//#define   LED2_ON     	PA0OUT=0
//#define   LED2_OFF    	PA0OUT=1

#define		PRT_DTR		PA7IN
#define		O_OUT			PB3IN

#define		KEY1			PC15IN
#define		KEY2			PC14IN
#define		KEY3			PC13IN

//GPIOA

#define 	MOTO_FORW_ON 	PA5OUT=1
#define 	MOTO_FORW_OFF PA5OUT=0

#define 	MOTO_BACK_ON 	PA6OUT=1
#define 	MOTO_BACK_OFF PA6OUT=0

#define 	RCLK1_ON 			PA8OUT=1
#define 	RCLK1_OFF 		PA8OUT=0
#define 	BEEP_ON 			PA11OUT=1
#define 	BEEP_OFF 			PA11OUT=0

#define 	COL_A_ON 			PA12OUT=1
#define 	COL_A_OFF 		PA12OUT=0

#define 	COL_B_ON 			PA15OUT=1
#define 	COL_B_OFF 		PA15OUT=0

//GPIOB
#define 	LED_CON_ON 		PB1OUT=1
#define 	LED_CON_OFF 	PB1OUT=0

#define 	EN_D2_ON 			PB4OUT=1
#define 	EN_D2_OFF 		PB4OUT=0

#define 	SRCLK2_ON			PB5OUT=1
#define 	SRCLK2_OFF		PB5OUT=0

#define 	RCLK2_ON 			PB6OUT=1
#define 	RCLK2_OFF 		PB6OUT=0

#define 	RCLK_ON 			PB7OUT=1
#define 	RCLK_OFF 			PB7OUT=0

#define 	DATA_ON 			PB8OUT=1
#define 	DATA_OFF 			PB8OUT=0

#define 	SRCLK_ON 			PB9OUT=1
#define 	SRCLK_OFF 		PB9OUT=0

#define 	ROW_A_ON 			PB12OUT=1
#define 	ROW_A_OFF 		PB12OUT=0

#define 	ROW_B_ON 			PB13OUT=1
#define 	ROW_B_OFF 		PB13OUT=0

#define 	SRCLK1_ON 		PB14OUT=1
#define 	SRCLK1_OFF 		PB14OUT=0

#define 	EN_D1_ON 			PB15OUT=1
#define 	EN_D1_OFF 		PB15OUT=0

/*
#define 	IF1_CON_ON 			PB0OUT=1
#define 	IF1_CON_OFF			PB0OUT=0

#define 	VDDPA1_C_ON 	PB1OUT=0
#define 	VDDPA1_C_OFF 	PB1OUT=1

#define 	SRCLK_ON 			PB3OUT=1
#define 	SRCLK_OFF 		PB3OUT=0

#define 	VDDPA2_C_ON 	PB4OUT=0
#define 	VDDPA2_C_OFF 	PB4OUT=1

#define 	VDD2_CON_ON		PB5OUT=0
#define 	VDD2_CON_OFF		PB5OUT=1

#define 	IF2_CON_ON 			PB6OUT=1
#define 	IF2_CON_OFF 		PB6OUT=0

#define 	VDDPA4_C_ON 		PB7OUT=0
#define 	VDDPA4_C_OFF 		PB7OUT=1
#define 	VDD4_CON_ON 		PB8OUT=0
#define 	VDD4_CON_OFF 		PB8OUT=1
#define 	IF4_CON_ON 			PB9OUT=1
#define 	IF4_CON_OFF 		PB9OUT=0
#define 	VDD1_CON_ON 		PB10OUT=0
#define 	VDD1_CON_OFF 		PB10OUT=1
#define 	ENV12_ON 				PB11OUT=1
#define 	ENV12_OFF 			PB11OUT=0
#define 	CHECK_END_ON 		PB13OUT=1
#define 	CHECK_END_OFF 	PB103OUT=0

#define 	IC1_FLAG_ON 			PB14OUT=1
#define 	IC1_FLAG_OFF 			PB14OUT=0
#define 	IC2_FLAG_ON 			PB15OUT=1
#define 	IC2_FLAG_OFF 			PB15OUT=0
*/
/*---------------------------------------------------------*/


//PCB CHECK INFO
typedef struct
{
    u8    check_status;      //测试状态标志
    u8   	current;        		//电流值
    u8   	V_3V;     					//3V电压值
    u8   	V_1V;     					//1.2V电压值
    u8 	 	out_st;       			//输出状态---3次检测全正确为0，
															//第一次检测应为高，否则加1，第二次检测应为低，否则加10，第三次检测应为高，否则加100
		u8		read_light; 
		u8 		light_ad;					//感光AD值
		u8		read_tx;
    u8    tx_data[16];       //发送数据
}PCB_INFO;


extern u8 beep_st;
extern PCB_INFO pcb_check_info[4][4];
extern u8 rec_data_num,USART1_recnum,USART1_recdata[16];

extern void USART1_IRQHandler(void);

#define    WDI()  IWDG_ReloadCounter()
#define    AVB_OVER_TIME  240             /* 主板看门狗超时值 */

#endif

