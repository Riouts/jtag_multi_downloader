#ifndef _timer_H
#define _timer_H

/*
* @fn Timer2_Configuration 
* @brief  Timer2_Configuration
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Timer2_Configuration(void);
/** 
* @fn Timer6_Configuration 
* @brief  Timer6_Configuration
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Timer6_Configuration(void);

/** 
* @fn Timer7_Configuration 
* @brief  Timer7_Configuration
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Timer7_Configuration(void);

/** 
* @fn TIM2_IRQHandler 
* @brief  TIM2_IRQHandler
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void TIM2_IRQHandler(void);

/** 
* @fn TIM3_IRQHandler 
* @brief  TIM3_IRQHandler
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Timer3_Configuration(void);
/** 
* @fn TIM3_Mode_Config
* @brief  TIM3_Mode_Config
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void  TIM3_Mode_Config(void);
/** 
* @fn TIM6_DAC_IRQHandler 
* @brief  TIM6_DAC_IRQHandler
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/

void Timer4_Configuration(void);

void TIM4_IRQHandler(void);

void TIM6_DAC_IRQHandler(void);

/** 
* @fn TIM7_IRQHandler 
* @brief  TIM7_IRQHandler
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void TIM7_IRQHandler(void);


void PWM_Out_Off(void);
void PWM_Out_On(void);

#endif
