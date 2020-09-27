#include "main.h"
/*----------------------------------------------------*/  
#define IAP_ADDR        0X08000000
#define App_ADDR        0X08004000        //IAP部分预留16KBytes Flash
extern uint8_t UART_recv_buf[3];
extern uint8_t FP_Update_Flag; 

//读取升级标志位
uint16_t ReadUpdateFlag(uint16_t  BKP_Register )
{
  uint16_t  bkData = 0; 
  /* Enable PWR and BKP clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); 
  /* Enable write access to Backup domain */
  PWR_BackupAccessCmd(ENABLE);
  /*Read the BKP_DR1*/
  bkData = BKP_ReadBackupRegister(BKP_Register);
  PWR_BackupAccessCmd(DISABLE);
  return (bkData);
}
//修改升级标志位
void  WriteUpdateFlag(uint16_t  BKP_Register ,uint16_t FlagData)
{
  /* Enable PWR and BKP clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE); 
  /* Enable write access to Backup domain */
  PWR_BackupAccessCmd(ENABLE);
  /*Write the BKP_DR1*/
  BKP_WriteBackupRegister(BKP_Register, FlagData);
  PWR_BackupAccessCmd(DISABLE);
}
//前板软件进入boot 前服务函数
void  WorkingsForUpdate(void)
{
    u16 *Ptr;
    Ptr=(u16*)(&UART_recv_buf[3]);

 //  WDI ();
    if(FP_Update_Flag==1)
    {
        __disable_irq();
        FP_Update_Flag=0;
        WriteUpdateFlag(BKP_DR1 ,0xAA55);  //修改标志位
        WriteUpdateFlag(BKP_DR2 ,*Ptr++);  //修改标志位
        WriteUpdateFlag(BKP_DR3 ,*Ptr++);  //修改标志位
        WriteUpdateFlag(BKP_DR4 ,*Ptr++);  //修改标志位
        WriteUpdateFlag(BKP_DR5 ,*Ptr++);  //修改标志位
        WriteUpdateFlag(BKP_DR6 ,*Ptr++);  //修改标志位
        
       // WDI ();
        //恢复各模块至默认状态
	 TIM_DeInit(TIM2);
	 TIM_DeInit(TIM3);
	 TIM_DeInit(TIM6);
	 TIM_DeInit(TIM7);
	 USART_DeInit(USART1);
	 USART_DeInit(USART2);
	 EXTI_DeInit();
	 GPIO_DeInit(GPIOB);
	 GPIO_DeInit(GPIOC);
	 //WWDG_DeInit();
	 __enable_irq();
	 AppJumpToBoot();	 
	 
    }
}

//长跳转函数
void AppJumpToBoot(void)
{
    uint32_t  SpInitVal;                                     //IAP程序的SP初值.
    uint32_t  JumpAddr;                                   //IAP程序的跳转地址.即,IAP程序的入口.
    void    (*pIapFun)(void);                             //定义一个函数指针.用于指向APP程序入口.
    
   // NVIC_DeInit ();                                       //恢复NVIC为复位状态.使中断不再发生.
    
    SpInitVal = *(uint32_t *)IAP_ADDR;              //取APP的SP初值.
    JumpAddr = *(uint32_t *)(IAP_ADDR + 4);       //取程序入口.
    
	__set_MSP(SpInitVal);
    pIapFun = (void (*)(void))JumpAddr;            //生成跳转函数.
    (*pIapFun) ();                                            //跳转.不再返回.

}



















