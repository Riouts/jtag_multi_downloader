#ifndef  _LED_H
#define  _LED_H
#include "stm32f10x.h"

#define Bit_LED_STATUS           0x01
#define Bit_LED_RECORD           0x02
#define Bit_LED_HD               0x04
#define Bit_LED_BF               0x08
#define Bit_LED_ALARM            0x10
#define Bit_LED_RC               0x20
#define Bit_LED_NET1             0x40
#define Bit_LED_NET2             0x80

//void HC595_Wr_Byte(u8 leddata);
void LedBlinkControl(void);
void LedRefresh(void);
void LedAllOn(void);
void LedAllOff(void);
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ������ʹ��

//********************************************************************************

//OLEDģʽ����
//0:4�ߴ���ģʽ                                                    //���������2015��11��2��17

#define OLED_MODE 0
		    						  
//-----------------OLED�˿ڶ���----------------  					   

#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//CS      //��λ(0)  Ƭѡ�ź�
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_12)            //��λ(1)

/*
#define OLED_RS_Clr() GPIO_ResetBits(GPIOC,GPIO_Pin_6)//A0        //A0��DC��ͬһ���źţ�ԭ����������PC6���˴���PA8
#define OLED_RS_Set() GPIO_SetBits(GPIOC,GPIO_Pin_6)
*/
#define OLED_RS_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_8)//DC
#define OLED_RS_Set() GPIO_SetBits(GPIOA,GPIO_Pin_8)


////PC0~7,��Ϊ������

//#define DATAOUT(x) GPIO_Write(GPIOC,x);//���  

//ʹ��4�ߴ��нӿ�ʱʹ�� 

//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//CLK
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)//DIN
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)

 		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����
//OLED�����ú���
void OLED_WR_Byte(unsigned char  dat,unsigned char  cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);	
void OLED_Refresh_Gram1(void);
extern void OLED_Clear1(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char  x,unsigned char  y,unsigned char  t);
void OLED_Fill(unsigned char  x1,unsigned char  y1,unsigned char  x2,unsigned char  y2,unsigned char  dot);
void OLED_ShowCHinese(unsigned char  x,unsigned char  y,unsigned char  no);
void OLED_ShowChar(unsigned char  x,unsigned char  y,unsigned char  chr,unsigned char  size,unsigned char  mode);
void OLED_ShowNum(unsigned char  x,unsigned char  y,unsigned int num,unsigned char  len,unsigned char  size);
void OLED_ShowString(unsigned char  x,unsigned char  y,const unsigned char  *p);	 
void LCD_Set_Pos(unsigned char  x, unsigned char  y) ;
void OLED_Set_Pos(unsigned char x, unsigned char y);



#endif  
	 
////////////////////////////////////////////////////////////////////////////////////////////////////////




