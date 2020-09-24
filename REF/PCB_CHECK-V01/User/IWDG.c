#include<main.h>
/*----------------------------------------------------------------------------------*/
void IWDG_Init(void)
 {
   IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
   IWDG_SetPrescaler(IWDG_Prescaler_32);
   IWDG_SetReload(2000);
   IWDG_ReloadCounter();
   IWDG_Enable();
 }    
