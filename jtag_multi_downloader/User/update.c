#include "main.h"
/*----------------------------------------------------*/  
#define IAP_ADDR        0X08000000
#define App_ADDR        0X08004000        //IAP����Ԥ��16KBytes Flash
extern uint8_t UART_recv_buf[3];
extern uint8_t FP_Update_Flag; 

//��ȡ������־λ
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
//�޸�������־λ
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
//ǰ���������boot ǰ������
void  WorkingsForUpdate(void)
{
    u16 *Ptr;
    Ptr=(u16*)(&UART_recv_buf[3]);

 //  WDI ();
    if(FP_Update_Flag==1)
    {
        __disable_irq();
        FP_Update_Flag=0;
        WriteUpdateFlag(BKP_DR1 ,0xAA55);  //�޸ı�־λ
        WriteUpdateFlag(BKP_DR2 ,*Ptr++);  //�޸ı�־λ
        WriteUpdateFlag(BKP_DR3 ,*Ptr++);  //�޸ı�־λ
        WriteUpdateFlag(BKP_DR4 ,*Ptr++);  //�޸ı�־λ
        WriteUpdateFlag(BKP_DR5 ,*Ptr++);  //�޸ı�־λ
        WriteUpdateFlag(BKP_DR6 ,*Ptr++);  //�޸ı�־λ
        
       // WDI ();
        //�ָ���ģ����Ĭ��״̬
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

//����ת����
void AppJumpToBoot(void)
{
    uint32_t  SpInitVal;                                     //IAP�����SP��ֵ.
    uint32_t  JumpAddr;                                   //IAP�������ת��ַ.��,IAP��������.
    void    (*pIapFun)(void);                             //����һ������ָ��.����ָ��APP�������.
    
   // NVIC_DeInit ();                                       //�ָ�NVICΪ��λ״̬.ʹ�жϲ��ٷ���.
    
    SpInitVal = *(uint32_t *)IAP_ADDR;              //ȡAPP��SP��ֵ.
    JumpAddr = *(uint32_t *)(IAP_ADDR + 4);       //ȡ�������.
    
	__set_MSP(SpInitVal);
    pIapFun = (void (*)(void))JumpAddr;            //������ת����.
    (*pIapFun) ();                                            //��ת.���ٷ���.

}



















