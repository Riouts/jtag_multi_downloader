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


#define		PM51_OK	    	PB7IN
#define		PM51_FAIL			PB9IN
#define   PM51_BUSY     PB8IN

#define		KEY1			PC15IN
#define		KEY2			PC14IN

#define		PRT_DTR		PA7IN

//GPIOA
#define 	RCLK_ON 			PA8OUT=1
#define 	RCLK_OFF 	  	PA8OUT=0
#define 	BEEP_ON 			PA11OUT=1
#define 	BEEP_OFF 			PA11OUT=0
//GPIOB
#define 	PM51_START_ON 	PB6OUT=1
#define 	PM51_START_OFF 	PB6OUT=0

#define 	DATA_ON 			PB15OUT=1
#define 	DATA_OFF 			PB15OUT=0

#define 	SRCLK_ON 			PB14OUT=1
#define 	SRCLK_OFF 		PB14OUT=0

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

