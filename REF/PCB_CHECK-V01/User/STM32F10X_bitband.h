#ifndef __STM32F10x_BITBAND_H
#define __STM32F10x_BITBAND_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/*---------------------------------------------------------------------------*/
//别名区  ADDRESS=0x4200 0000 + (0x0001 100C*0x20) + (bitx*4)	;bitx:第x位
// 把“位带地址＋位序号”转换别名地址宏
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
//把该地址转换成一个指针
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR( BITBAND(addr, bitnum)  )

#define GPIOA_ODR    (GPIOA_BASE+12) //0x4001080C
#define GPIOB_ODR    (GPIOB_BASE+12) //0x40010C0C
#define GPIOC_ODR    (GPIOC_BASE+12) //0x4001100C
#define GPIOD_ODR    (GPIOD_BASE+12) //0x4001140C
#define GPIOE_ODR    (GPIOE_BASE+12) //0x4001180C

#define GPIOA_IDR    (GPIOA_BASE+8)  //0x4001080C
#define GPIOB_IDR    (GPIOB_BASE+8)  //0x40010C0C
#define GPIOC_IDR    (GPIOC_BASE+8)  //0x4001100C
#define GPIOD_IDR    (GPIOD_BASE+8)  //0x4001140C
#define GPIOE_IDR    (GPIOE_BASE+8)  //0x4001180C

/*--------------------------------GPIO Output-------------------------------------------*/
#define PA0OUT   BIT_ADDR(GPIOA_ODR,0)   //PA0输出
#define PA1OUT   BIT_ADDR(GPIOA_ODR,1)   //PA1输出
#define PA2OUT   BIT_ADDR(GPIOA_ODR,2)   //PA2输出
#define PA3OUT   BIT_ADDR(GPIOA_ODR,3)   //PA3输出
#define PA4OUT   BIT_ADDR(GPIOA_ODR,4)   //PA4输出
#define PA5OUT   BIT_ADDR(GPIOA_ODR,5)   //PA5输出
#define PA6OUT   BIT_ADDR(GPIOA_ODR,6)   //PA6输出
#define PA7OUT   BIT_ADDR(GPIOA_ODR,7)   //PA7输出
#define PA8OUT   BIT_ADDR(GPIOA_ODR,8)   //PA8输出
#define PA9OUT   BIT_ADDR(GPIOA_ODR,9)   //PA9输出
#define PA10OUT  BIT_ADDR(GPIOA_ODR,10)  //PA10输出
#define PA11OUT  BIT_ADDR(GPIOA_ODR,11)  //PA11输出
#define PA12OUT  BIT_ADDR(GPIOA_ODR,12)  //PA12输出
#define PA13OUT  BIT_ADDR(GPIOA_ODR,13)  //PA13输出
#define PA14OUT  BIT_ADDR(GPIOA_ODR,14)  //PA14输出
#define PA15OUT  BIT_ADDR(GPIOA_ODR,15)  //PA15输出

#define PB0OUT   BIT_ADDR(GPIOB_ODR,0)   //PB0输出    
#define PB1OUT   BIT_ADDR(GPIOB_ODR,1)   //PB1输出    
#define PB2OUT   BIT_ADDR(GPIOB_ODR,2)   //PB2输出    
#define PB3OUT   BIT_ADDR(GPIOB_ODR,3)   //PB3输出    
#define PB4OUT   BIT_ADDR(GPIOB_ODR,4)   //PB4输出    
#define PB5OUT   BIT_ADDR(GPIOB_ODR,5)   //PB5输出    
#define PB6OUT   BIT_ADDR(GPIOB_ODR,6)   //PB6输出    
#define PB7OUT   BIT_ADDR(GPIOB_ODR,7)   //PB7输出    
#define PB8OUT   BIT_ADDR(GPIOB_ODR,8)   //PB8输出    
#define PB9OUT   BIT_ADDR(GPIOB_ODR,9)   //PB9输出    
#define PB10OUT  BIT_ADDR(GPIOB_ODR,10)  //PB10输出   
#define PB11OUT  BIT_ADDR(GPIOB_ODR,11)  //PB11输出   
#define PB12OUT  BIT_ADDR(GPIOB_ODR,12)  //PB12输出   
#define PB13OUT  BIT_ADDR(GPIOB_ODR,13)  //PB13输出   
#define PB14OUT  BIT_ADDR(GPIOB_ODR,14)  //PB14输出   
#define PB15OUT  BIT_ADDR(GPIOB_ODR,15)  //PB15输出   

#define PC0OUT   BIT_ADDR(GPIOC_ODR,0)   //PC0输出    
#define PC1OUT   BIT_ADDR(GPIOC_ODR,1)   //PC1输出    
#define PC2OUT   BIT_ADDR(GPIOC_ODR,2)   //PC2输出    
#define PC3OUT   BIT_ADDR(GPIOC_ODR,3)   //PC3输出    
#define PC4OUT   BIT_ADDR(GPIOC_ODR,4)   //PC4输出    
#define PC5OUT   BIT_ADDR(GPIOC_ODR,5)   //PC5输出    
#define PC6OUT   BIT_ADDR(GPIOC_ODR,6)   //PC6输出    
#define PC7OUT   BIT_ADDR(GPIOC_ODR,7)   //PC7输出    
#define PC8OUT   BIT_ADDR(GPIOC_ODR,8)   //PC8输出    
#define PC9OUT   BIT_ADDR(GPIOC_ODR,9)   //PC9输出    
#define PC10OUT  BIT_ADDR(GPIOC_ODR,10)  //PC10输出   
#define PC11OUT  BIT_ADDR(GPIOC_ODR,11)  //PC11输出   
#define PC12OUT  BIT_ADDR(GPIOC_ODR,12)  //PC12输出   
#define PC13OUT  BIT_ADDR(GPIOC_ODR,13)  //PC13输出   
#define PC14OUT  BIT_ADDR(GPIOC_ODR,14)  //PC14输出   
#define PC15OUT  BIT_ADDR(GPIOC_ODR,15)  //PC15输出   

#define PD0OUT   BIT_ADDR(GPIOD_ODR,0)   //PD0输出    
#define PD1OUT   BIT_ADDR(GPIOD_ODR,1)   //PD1输出    
#define PD2OUT   BIT_ADDR(GPIOD_ODR,2)   //PD2输出    
#define PD3OUT   BIT_ADDR(GPIOD_ODR,3)   //PD3输出    
#define PD4OUT   BIT_ADDR(GPIOD_ODR,4)   //PD4输出    
#define PD5OUT   BIT_ADDR(GPIOD_ODR,5)   //PD5输出    
#define PD6OUT   BIT_ADDR(GPIOD_ODR,6)   //PD6输出    
#define PD7OUT   BIT_ADDR(GPIOD_ODR,7)   //PD7输出    
#define PD8OUT   BIT_ADDR(GPIOD_ODR,8)   //PD8输出    
#define PD9OUT   BIT_ADDR(GPIOD_ODR,9)   //PD9输出    
#define PD10OUT  BIT_ADDR(GPIOD_ODR,10)  //PD10输出   
#define PD11OUT  BIT_ADDR(GPIOD_ODR,11)  //PD11输出   
#define PD12OUT  BIT_ADDR(GPIOD_ODR,12)  //PD12输出   
#define PD13OUT  BIT_ADDR(GPIOD_ODR,13)  //PD13输出   
#define PD14OUT  BIT_ADDR(GPIOD_ODR,14)  //PD14输出   
#define PD15OUT  BIT_ADDR(GPIOD_ODR,15)  //PD15输出   

#define PE0OUT   BIT_ADDR(GPIOE_ODR,0)   //PE0输出    
#define PE1OUT   BIT_ADDR(GPIOE_ODR,1)   //PE1输出    
#define PE2OUT   BIT_ADDR(GPIOE_ODR,2)   //PE2输出    
#define PE3OUT   BIT_ADDR(GPIOE_ODR,3)   //PE3输出    
#define PE4OUT   BIT_ADDR(GPIOE_ODR,4)   //PE4输出    
#define PE5OUT   BIT_ADDR(GPIOE_ODR,5)   //PE5输出    
#define PE6OUT   BIT_ADDR(GPIOE_ODR,6)   //PE6输出    
#define PE7OUT   BIT_ADDR(GPIOE_ODR,7)   //PE7输出    
#define PE8OUT   BIT_ADDR(GPIOE_ODR,8)   //PE8输出    
#define PE9OUT   BIT_ADDR(GPIOE_ODR,9)   //PE9输出    
#define PE10OUT  BIT_ADDR(GPIOE_ODR,10)  //PE10输出   
#define PE11OUT  BIT_ADDR(GPIOE_ODR,11)  //PE11输出   
#define PE12OUT  BIT_ADDR(GPIOE_ODR,12)  //PE12输出   
#define PE13OUT  BIT_ADDR(GPIOE_ODR,13)  //PE13输出   
#define PE14OUT  BIT_ADDR(GPIOE_ODR,14)  //PE14输出   
#define PE15OUT  BIT_ADDR(GPIOE_ODR,15)  //PE15输出   

/*--------------------------------GPIO Input-------------------------------------------*/
#define PA0IN   BIT_ADDR(GPIOA_IDR,0)   //PA0输入        
#define PA1IN   BIT_ADDR(GPIOA_IDR,1)   //PA1输入       
#define PA2IN   BIT_ADDR(GPIOA_IDR,2)   //PA2输入        
#define PA3IN   BIT_ADDR(GPIOA_IDR,3)   //PA3输入        
#define PA4IN   BIT_ADDR(GPIOA_IDR,4)   //PA4输入        
#define PA5IN   BIT_ADDR(GPIOA_IDR,5)   //PA5输入        
#define PA6IN   BIT_ADDR(GPIOA_IDR,6)   //PA6输入        
#define PA7IN   BIT_ADDR(GPIOA_IDR,7)   //PA7输入        
#define PA8IN   BIT_ADDR(GPIOA_IDR,8)   //PA8输入        
#define PA9IN   BIT_ADDR(GPIOA_IDR,9)   //PA9输入        
#define PA10IN  BIT_ADDR(GPIOA_IDR,10)  //PA10输入       
#define PA11IN  BIT_ADDR(GPIOA_IDR,11)  //PA11输入       
#define PA12IN  BIT_ADDR(GPIOA_IDR,12)  //PA12输入       
#define PA13IN  BIT_ADDR(GPIOA_IDR,13)  //PA13输入       
#define PA14IN  BIT_ADDR(GPIOA_IDR,14)  //PA14输入       
#define PA15IN  BIT_ADDR(GPIOA_IDR,15)  //PA15输入       
                                                         
#define PB0IN   BIT_ADDR(GPIOB_IDR,0)   //PB0输入            
#define PB1IN   BIT_ADDR(GPIOB_IDR,1)   //PB1输入            
#define PB2IN   BIT_ADDR(GPIOB_IDR,2)   //PB2输入            
#define PB3IN   BIT_ADDR(GPIOB_IDR,3)   //PB3输入            
#define PB4IN   BIT_ADDR(GPIOB_IDR,4)   //PB4输入            
#define PB5IN   BIT_ADDR(GPIOB_IDR,5)   //PB5输入            
#define PB6IN   BIT_ADDR(GPIOB_IDR,6)   //PB6输入            
#define PB7IN   BIT_ADDR(GPIOB_IDR,7)   //PB7输入            
#define PB8IN   BIT_ADDR(GPIOB_IDR,8)   //PB8输入            
#define PB9IN   BIT_ADDR(GPIOB_IDR,9)   //PB9输入            
#define PB10IN  BIT_ADDR(GPIOB_IDR,10)  //PB10输入           
#define PB11IN  BIT_ADDR(GPIOB_IDR,11)  //PB11输入           
#define PB12IN  BIT_ADDR(GPIOB_IDR,12)  //PB12输入           
#define PB13IN  BIT_ADDR(GPIOB_IDR,13)  //PB13输入           
#define PB14IN  BIT_ADDR(GPIOB_IDR,14)  //PB14输入           
#define PB15IN  BIT_ADDR(GPIOB_IDR,15)  //PB15输入           
                                                         
#define PC0IN   BIT_ADDR(GPIOC_IDR,0)   //PC0输入             
#define PC1IN   BIT_ADDR(GPIOC_IDR,1)   //PC1输入             
#define PC2IN   BIT_ADDR(GPIOC_IDR,2)   //PC2输入             
#define PC3IN   BIT_ADDR(GPIOC_IDR,3)   //PC3输入             
#define PC4IN   BIT_ADDR(GPIOC_IDR,4)   //PC4输入             
#define PC5IN   BIT_ADDR(GPIOC_IDR,5)   //PC5输入             
#define PC6IN   BIT_ADDR(GPIOC_IDR,6)   //PC6输入             
#define PC7IN   BIT_ADDR(GPIOC_IDR,7)   //PC7输入             
#define PC8IN   BIT_ADDR(GPIOC_IDR,8)   //PC8输入             
#define PC9IN   BIT_ADDR(GPIOC_IDR,9)   //PC9输入             
#define PC10IN  BIT_ADDR(GPIOC_IDR,10)  //PC10输入            
#define PC11IN  BIT_ADDR(GPIOC_IDR,11)  //PC11输入            
#define PC12IN  BIT_ADDR(GPIOC_IDR,12)  //PC12输入            
#define PC13IN  BIT_ADDR(GPIOC_IDR,13)  //PC13输入            
#define PC14IN  BIT_ADDR(GPIOC_IDR,14)  //PC14输入            
#define PC15IN  BIT_ADDR(GPIOC_IDR,15)  //PC15输入            
                                                         
#define PD0IN   BIT_ADDR(GPIOD_IDR,0)   //PD0输入        
#define PD1IN   BIT_ADDR(GPIOD_IDR,1)   //PD1输入        
#define PD2IN   BIT_ADDR(GPIOD_IDR,2)   //PD2输入        
#define PD3IN   BIT_ADDR(GPIOD_IDR,3)   //PD3输入        
#define PD4IN   BIT_ADDR(GPIOD_IDR,4)   //PD4输入        
#define PD5IN   BIT_ADDR(GPIOD_IDR,5)   //PD5输入        
#define PD6IN   BIT_ADDR(GPIOD_IDR,6)   //PD6输入        
#define PD7IN   BIT_ADDR(GPIOD_IDR,7)   //PD7输入        
#define PD8IN   BIT_ADDR(GPIOD_IDR,8)   //PD8输入        
#define PD9IN   BIT_ADDR(GPIOD_IDR,9)   //PD9输入        
#define PD10IN  BIT_ADDR(GPIOD_IDR,10)  //PD10输入       
#define PD11IN  BIT_ADDR(GPIOD_IDR,11)  //PD11输入       
#define PD12IN  BIT_ADDR(GPIOD_IDR,12)  //PD12输入       
#define PD13IN  BIT_ADDR(GPIOD_IDR,13)  //PD13输入       
#define PD14IN  BIT_ADDR(GPIOD_IDR,14)  //PD14输入       
#define PD15IN  BIT_ADDR(GPIOD_IDR,15)  //PD15输入       
                                                         
#define PE0IN   BIT_ADDR(GPIOE_IDR,0)  //PE0输入          
#define PE1IN   BIT_ADDR(GPIOE_IDR,1)  //PE1输入          
#define PE2IN   BIT_ADDR(GPIOE_IDR,2)  //PE2输入          
#define PE3IN   BIT_ADDR(GPIOE_IDR,3)  //PE3输入          
#define PE4IN   BIT_ADDR(GPIOE_IDR,4)  //PE4输入          
#define PE5IN   BIT_ADDR(GPIOE_IDR,5)  //PE5输入          
#define PE6IN   BIT_ADDR(GPIOE_IDR,6)  //PE6输入          
#define PE7IN   BIT_ADDR(GPIOE_IDR,7)  //PE7输入          
#define PE8IN   BIT_ADDR(GPIOE_IDR,8)  //PE8输入          
#define PE9IN   BIT_ADDR(GPIOE_IDR,9)  //PE9输入          
#define PE10IN  BIT_ADDR(GPIOE_IDR,10) //PE10输入         
#define PE11IN  BIT_ADDR(GPIOE_IDR,11) //PE11输入         
#define PE12IN  BIT_ADDR(GPIOE_IDR,12) //PE12输入         
#define PE13IN  BIT_ADDR(GPIOE_IDR,13) //PE13输入         
#define PE14IN  BIT_ADDR(GPIOE_IDR,14) //PE14输入         
#define PE15IN  BIT_ADDR(GPIOE_IDR,15) //PE15输入         

                                                
#ifdef __cplusplus                              
}                                               
#endif                                          
                                                
#endif /* __STM32F10x_BITBAND_H */              
