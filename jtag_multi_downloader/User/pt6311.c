
/** $Id$ $DateTime$ 
*  @file pt6311.c 
*  @brief This file implements all TPB_FP in whole system. 
*  @author gaoyanlei<gaoyl@bstar.com.cn>
*  @date 2012-07-26    modify for dvx 
*/
/******************************************************************************
*@note    Copyright 2012, BeiJing Bluestar Corporation, Limited
                     ALL RIGHTS RESERVED 
Permission is hereby granted to licensees of BeiJing Bluestar, Inc. products 
to use or abstract this computer program for the sole purpose of implementing 
a product based on BeiJing Bluestar, Inc. products. No other rights to 
reproduce, use, or disseminate this computer program,whether in part or  in 
whole, are granted. BeiJing Bluestar, Inc. makes no representation or 
warranties with respect to the performance of this computer program, and 
specifically disclaims any responsibility for any damages, special or consequential, 
connected with the use of this program. 
For details, see http://www.bstar.com.cn/
******************************************************************************/
#include <main.h>
#include "absacc.h"

#define     DISPLAY_MODE    0x0B       /* 显示模式设定 12grids 16segments */
#define     WRITE_VFD_DATA  0x40       /* 写VFD显示数据，地址自增模式 */
#define     READ_KEY_DATA   0x42       /* 读键值，地址自增模式 */
#define     SET_ADDRESS     0xC0       /* 地址设置 */
#define     DISPLAY_ON      0x8b       /* 开显示，占空比10/16 */
#define     DISPLAY_OFF     0x81       /* 关显示，占空比1/8 */

/**
*  VFD定义 
*/
#define MOTION_DETECT       1
#define ALARM_DISABLE       2
#define KEY_LOCK            3
#define FRAME_QUALITY       4
#define HD_WRITE_STATE      5
#define YT_CTRL_MODE        6
#define TIME_RECORD         7
#define ALARM_ENABLE        8
#define ALARM_STATE         9
#define NET_WORK            10

#define LINE_1              11
#define LINE_2              12
#define POINT_1             13
#define POINT_2             14

#define RECORD              15
#define CAM                 16
#define HD                  17
#define LOSS                18
#define ALA                 19
#define RAPID_BACK          20
#define STOP                21
#define SINGLE_FRAME        22
#define BACK_END            23
#define RAPID_FORWARD       24
#define PAUSE               25
#define PLAY                26
#define RECORD_PLAY         27

/**
*  VFD扫描按键对应键值表 
*/

#define RECORD_KEY              0x30
#define PLAY_KEY                0x31
#define STOP_KEY                0x32
#define RAPID_BACK_KEY          0x33

#define RAPID_FORWARD_KEY       0x34
#define PAUSE_SINGLE_FRAME_KEY  0x35
#define BACK_BEGIN_KEY          0x36
#define BACK_END_KEY            0x37

#define MULTI_PICTURE_KEY       0x21
#define FN_KEY                  0xf0
#define CLEAR_ALARM_KEY         0x22
#define MESSAGE_KEY             0x20
#define INPUT_METHOD      0x41

#define ESC_KEY                 0x00
#define LEFT_KEY                0x03
#define MENU_KEY                0x05
#define RIGHT_KEY               0x04

#define DOWN_KEY                0x02
#define UP_KEY                  0x01
#define NUM1_KEY                0x11
#define NUM2_KEY                0x12

#define NUM3_KEY                0x13
#define NUM4_KEY                0x14
#define NUM5_KEY                0x15
#define NUM6_KEY                0x16

#define NUM7_KEY                0x17
#define NUM8_KEY                0x18
#define NUM9_KEY                0x19
#define NUM0_KEY                0x10

#define SECOND_VIEW_KEY         0x3a
#define TIMER_KEY               0x3b
#define MOTO_DETECT_KEY         0x3c                 //移动侦测 
#define BF_KEY                  0x3d                           //布防撤防

#define INTERPHONE_KEY          0x3e
#define PICTURE_QUALITY_KEY     0x3f
#define ADD_KEY                 0x1a
#define SUB_KEY                 0x1b

#define PWR_OFF_KEY             0xee   /* 关机键 */


uint8_t  BSR_KEY_VALUE[] = {
/**
* K1                 K2                      K3              K4 
*/
  RECORD_KEY,        PLAY_KEY,               STOP_KEY,       RAPID_BACK_KEY, 
  RAPID_FORWARD_KEY, PAUSE_SINGLE_FRAME_KEY, BACK_BEGIN_KEY, BACK_END_KEY, 
  MULTI_PICTURE_KEY, FN_KEY,                 CLEAR_ALARM_KEY,MESSAGE_KEY,                                                                  
  ESC_KEY,           LEFT_KEY,               MENU_KEY,       RIGHT_KEY,
  DOWN_KEY,          UP_KEY,                 NUM1_KEY,       NUM2_KEY,                                          
  NUM3_KEY,          NUM4_KEY,               NUM5_KEY,       NUM6_KEY,
  NUM7_KEY,          NUM8_KEY,               NUM9_KEY,       NUM0_KEY,                                            
  SECOND_VIEW_KEY,   TIMER_KEY,              MOTO_DETECT_KEY,BF_KEY,
  INTERPHONE_KEY,    PICTURE_QUALITY_KEY,    ADD_KEY,        SUB_KEY,
};

uint8_t CurKeyValue = 0xff;
uint8_t OldKeyValue = 0xff;


uint8_t Fn_key_state_flg = 0;              /* Fn按键状态标志位 */
uint8_t YT_key_state_flg = 0;              /* 云台按键状态标志位 */

uint8_t key_UpD_State_flg1 = 0;            /* 1按键状态标志位,0：抬起;1:按下 */
uint8_t key_UpD_State_flg2 = 0;            /* 2按键状态标志位,0：抬起;1:按下 */
uint8_t key_UpD_State_flg3 = 0;            /* 3按键状态标志位,0：抬起;1:按下 */


/********************************************************2012-07-28*****/

uint16_t key_FnYT_state = 0;              /* 按键Fn和YT状态 */

uint8_t key_ComplexKey[2] = {0,0};       /* 同时按下复合按键数组 */
uint8_t key_ComplexKey_Cur[2] = {0,0};   /* 当前同时按下复合按键数组 */
uint8_t key_ComplexKey_Old[2] = {0,0};   /* 上次同时按下复合按键数组 */
uint8_t key_ComplexKey_Count = 0;        /* 同时按下复合按键个数 */
uint8_t key_ComplexKey_Cur_Count = 0;    /* 当前同时按下复合按键个数*/
uint8_t key_ComplexKey_Old_Count = 0;    /* 上次同时按下复合按键个数*/
uint8_t key_buf1[5] = {0,0,0,0,0};
uint8_t key_buf[5] = {0,0,0,0};
extern uint8_t bit_beep;                   /* 蜂鸣器短响2声标志位 */
extern uint8_t System_Model;             /* 前板跳线组合码寄存器 */
extern uint8_t CloseCounter;             /* 主板冷启动次数寄存器 */

extern uint8_t Fn_key_timer;             /* Fn按键3秒失效计时器 */

extern uint8_t AVB_Run;                    /* 主板运行状态标志位 */

/** 
* @fn Pt6311_Write_Byte 
* @brief  Pt6311_Write_Byte 
* @param[in] uint8. 
* @param[out] none. 
* @return none. 
*/
void Pt6311_Write_Byte(uint8_t dat)
{
    uint8_t i = 0;
    WDI ();
	
    VFD_CLK = 0;
        __NOP();
	 __NOP();
	 __NOP();
    for(i = 0; i < 8; i++)
    {   /* 将数据按位移入pt6311 */
        if(dat & 0x01 == 1)
            VFD_DATO = 1;
        else
            VFD_DATO = 0;
            
        Delay2TCK(10);
        
        VFD_CLK = 1;   /* 产生一个 上升沿 */
            
        Delay2TCK(10);
	      
        dat = dat >> 1;
        
        Delay2TCK(10);
	      
        VFD_CLK = 0;
        
        Delay2TCK(10);

    }
}

/** 
* @fn Pt6311_Read_Byte 
* @brief  Pt6311_Read_Byte 
* @param[in] none. 
* @param[out] none. 
* @return uint8. 
*/
uint8_t Pt6311_Read_Byte(void)
{
    uint8_t i = 0;
    uint8_t dat = 0;
    for(i = 0; i < 8; i++)
    {   /* 按位从pt6311读入一个字节 */
        dat = dat >> 1;
        VFD_CLK = 0;   /* 产生一个下降沿 */
        
        Delay2TCK(5);
        
        VFD_CLK = 1;
       
        Delay2TCK(5);
       
        if(VFD_DATI == 1)
            dat |= 0x80;
        else
            dat &= 0x7f;
            
       Delay2TCK(5);
    }
    return dat;
}


/** 
* @fn Pt6311_Init 
* @brief  Pt6311_Init 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void Pt6311_Init(void)
{

    key_buf[0] = key_buf[1] = key_buf[2] = key_buf[3] = key_buf[4] = 0;
    key_buf1[0] = key_buf1[1] = key_buf1[2] = key_buf1[3] = key_buf1[4] = 0;	
    CurKeyValue = 0xff;
    OldKeyValue = 0xff;

    
    VFD_STB = 0;
    Pt6311_Write_Byte(WRITE_VFD_DATA); /* 写数据到vfd命令 */
    VFD_STB = 1;
    Delay2TCK(5);
    VFD_STB = 0;
    Pt6311_Write_Byte(SET_ADDRESS);    /* 设置地址为0 */
    VFD_STB = 1;
    Delay2TCK(5);
    VFD_STB = 0;
    Pt6311_Write_Byte(DISPLAY_MODE);   /* 设置VFD模式，12Grid 16segments */
    VFD_STB = 1;
    Delay2TCK(5);
    VFD_STB = 0;
    Pt6311_Write_Byte(DISPLAY_ON);     /* 开显示，1/8占空比 */
    VFD_STB = 1;
}

/** 
* @fn HextoBCD 
* @brief  HextoBCD 
* @param[in] uint8. 
* @param[out] none. 
* @return uint8. 
*/
uint8_t HextoBCD(uint8_t hex)
{
    uint8_t BCD = 0; 
    uint8_t temp = 0;
    BCD = (hex % 10) & 0x0f;
    temp = hex / 10;
    BCD = BCD | ((temp << 4) & 0xf0);
    return BCD;
}

/** 
* @fn test_24c16 
* @brief  test_24c16 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void test_24c16(void)
{
    static unsigned char test = 0;
    Single_Write(0xae,255,test);
    delay100ms();
    delay100ms();
    if(Single_Read(0xae,255) != test)
    {
        bit_beep = 1;
    }
    //DisPlayNumVfd(1, HextoBCD(test));
   // DisPlayNumVfd(2, 0);
    //DisPlayNumVfd(3, 0);
    //if(test++ >= 99)
        test = 0;
}

/** 
* @fn Read_key 
* @brief  Read_key 
* @param[in] none. 
* @param[out] none. 
* @return uint8. 
*/
uint8_t Read_key(void)
{
    uint8_t count = 0;
    uint8_t key_buf1[5] = {0,0,0,0,0};
    uint8_t key_buf[5] = {0,0,0,0,0};
    uint8_t keycount= 0;
    uint8_t KeyNumber[2]={0,0};

    union  keys{
                       uint32_t   KeyArray;
			                  uint8_t   KeyChar[4];
                  
                   }KeyData;
	  for(count=0;count<4;count++)
		{
      KeyData.KeyChar[count]= 0x00;
    }
    key_ComplexKey_Count = 0;
    key_ComplexKey[1] = key_ComplexKey[0] = 0xff;
	
    WDI();
    VFD_STB = 0;
    Delay2TCK(5);
    Pt6311_Write_Byte(READ_KEY_DATA);  // 发送读取键值的命令 (VFD_PAD)
    Delay2TCK(5);
    VFD_DATO = 1;
    Delay2TCK(5);
    for(count = 0; count < 5; count++)
    {
          key_buf[count] = Pt6311_Read_Byte();
    }
    VFD_STB = 1;
    Delay2TCK(5);
    VFD_STB = 0;
    Delay2TCK(5);
    Pt6311_Write_Byte(READ_KEY_DATA);  //发送读取键值的命令 (VFD_PAD); 
    Delay2TCK(5);
    VFD_DATO = 1;
    Delay2TCK(5);
    for(count = 0; count < 5; count++)
    {
        key_buf1[count] = Pt6311_Read_Byte();
    }
    Delay2TCK(5);
    VFD_STB = 1;
    Delay2TCK(5);
    for(count= 0; count < 5; count++)
    {
        if(key_buf[count] !=  key_buf1[count])
            return 0xfe;               //去抖动 
    }
   
     /**
    *  工厂测试模式LED 
    */
    if(key_buf[3] == 0x30)//同时按左右键
    {
       LedAllOn();
    }

    for(count=0;count<4;count++)
    {
        KeyData.KeyChar[count]= key_buf[count];
    }
     if(KeyData.KeyArray>0)                                              //查找按键号
    {
         for(count = 0; count < 32; count++)
         {
                keycount++;
                if(KeyData.KeyArray & 0x00000001)
                {
                    KeyNumber[key_ComplexKey_Count]= keycount;
                    key_ComplexKey_Count++;
                    if(key_ComplexKey_Count >= 2)
                    break ;
                }
                KeyData.KeyArray >>= 1;
          }  
		 
          for(count=0;count<key_ComplexKey_Count;count++)                           //按键值映射
          {
               switch(KeyNumber[count])
               {
                    case 0x01:
			        key_ComplexKey[count] = NUM1_KEY;
			       break;
                    case 0x02:
			        key_ComplexKey[count] = NUM2_KEY;		
			        break;
			case 0x03:
			        key_ComplexKey[count] = NUM3_KEY;
			        break;
			case 0x04:
			        key_ComplexKey[count] = NUM4_KEY;
			       break;
			case 0x05:
			        key_ComplexKey[count] = NUM5_KEY;
                            break;
			case 0x06:
				 key_ComplexKey[count] = NUM6_KEY;
			       break;
			case 0x07:
				 key_ComplexKey[count] = NUM7_KEY;
			        break;
			case 0x08:
				 key_ComplexKey[count] = NUM8_KEY;
			        break;
			case 0x09:
				 key_ComplexKey[count] = NUM9_KEY;
                            break;
			case 0x0A:
				 key_ComplexKey[count] = NUM0_KEY;
			       break;
			case 0x0B:
				 key_ComplexKey[count] = MESSAGE_KEY;
			       break;
			case 0x0C:
				 key_ComplexKey[count] = SUB_KEY;
			        break;
			case 0x0D:
				 key_ComplexKey[count] = RECORD_KEY;
			        break;
			case 0x0E:
				 key_ComplexKey[count] = PLAY_KEY;
			       break;
			case 0x0F:
				 key_ComplexKey[count] = PAUSE_SINGLE_FRAME_KEY;//M型前板丝印值映射
				 Fn_key_state_flg = 1;
                           break;	
			case 0x10:
				 key_ComplexKey[count] = MULTI_PICTURE_KEY;        //M型前板丝印值映射
				 Fn_key_state_flg = 1;
			       break;
			case 0x11:
				 key_ComplexKey[count] = ESC_KEY;
			        break;
                    case 0x12:
				 key_ComplexKey[count] = BF_KEY;
				 if(0x00000001==VfdYT)                                          //映射到与老vfd相同功能的键值                                 
				 {
                                 key_ComplexKey[count] = RECORD_KEY;
				 }
			        break;
			case 0x13:
				 key_ComplexKey[count] = CLEAR_ALARM_KEY;
				  if(0x00000001==VfdYT)                                        //映射到与老vfd相同功能的键值 
				 {
                                 key_ComplexKey[count] = RAPID_BACK_KEY;
				 }
			        break;
			case 0x14:
				 key_ComplexKey[count] = SECOND_VIEW_KEY;
				  if(0x00000001==VfdYT)                                       //映射到与老vfd相同功能的键值 
				 {
                                 key_ComplexKey[count] = BACK_BEGIN_KEY;
				 }
			        break;
			case 0x15:
				 key_ComplexKey[count] = PAUSE_SINGLE_FRAME_KEY;
				  if(0x00000001==VfdYT)                                     //映射到与老vfd相同功能的键值 
				 {
                                 key_ComplexKey[count] = PLAY_KEY;
				 }
                            break;
			case 0x16:
				 key_ComplexKey[count] = RAPID_BACK_KEY;
				  if(0x00000001==VfdYT)                                      //映射到与老vfd相同功能的键值 (变倍-) 
				 {
                                 key_ComplexKey[count] = RAPID_FORWARD_KEY;
				 }
			        break;
			case 0x17:
				 key_ComplexKey[count] = MULTI_PICTURE_KEY;
				  if(0x00000001==VfdYT)                                     //映射到与老vfd相同功能的键值(聚焦-) 
				 {
                                 key_ComplexKey[count] =  BACK_END_KEY;
				 }
			       break;
			case 0x18:
				 key_ComplexKey[count] = STOP_KEY;
			        break;
			case 0x19:
				 key_ComplexKey[count] = RAPID_FORWARD_KEY;//PAUSE_SINGLE_FRAME_KEY;
                            if(0x00000001==VfdYT)
				 {
                                key_ComplexKey[count] =PAUSE_SINGLE_FRAME_KEY;
				 }
                           break;
			case 0x1A:
				 key_ComplexKey[count] = INPUT_METHOD; 
			        break;
			case 0x1B:
				 key_ComplexKey[count] = UP_KEY;
			       break;
			case 0x1C:
				 key_ComplexKey[count] = DOWN_KEY;
			       break;
			case 0x1D:
				 key_ComplexKey[count] = LEFT_KEY;
			        break;
			case 0x1E:
				 key_ComplexKey[count] = RIGHT_KEY;
			       break;
			case 0x1F:
				 key_ComplexKey[count] = MENU_KEY;
                           break;
			case 0x20:
                           break;
			default:
			       break;
		  }
	    }
		if(key_ComplexKey_Count>=0x01)
		{
		       return  key_ComplexKey[0];
		}

		else
		{
		      return 0xFF;
		}
	}
  	else
      {
		 return 0xFF;
	}
    
}

	
/** 
* @fn KeyProcess 
* @brief  KeyProcess 
* @param[in] none. 
* @param[out] none. 
* @return none. 
*/
void KeyProcess(void)
{
    uint8_t key = 0;
    key = Read_key();
    if(key == 0xfe)
        return;                        /* 如果是按键抖动 */
    if(key == 0xf0)
    {                                    /* 如果按键是Fn */
        Fn_key_state_flg = 1;
        return;
    }
    switch (key_ComplexKey_Count)
    {
        case 1:
            if((key != 0xff) && (key != OldKeyValue)&& (!key_UpD_State_flg1))
            {
                OldKeyValue = CurKeyValue; /* 存储上次按键值 */
                CurKeyValue = key;         /* 存储当前按键值 */
                /**
                * 存储上次按键个数
                */
                key_ComplexKey_Old_Count = key_ComplexKey_Cur_Count;
                /**
                * 存储当前按键个数
                */
                key_ComplexKey_Cur_Count = key_ComplexKey_Count;    
                key_UpD_State_flg1 = 1;
                key_FnYT_state = 0;
                YT_key_state_flg = VfdYT;
                key_FnYT_state = Key_State_Process();
                key_FnYT_state |= 0x02;
                if(AVB_Run)
                {  
                    WDI();
                    UART2_Send_Key1(0x11, key_FnYT_state, CurKeyValue);
		   }
		}
            break;
        case 2:
            if((key != 0xff) && (!key_UpD_State_flg2))
            {
                key_ComplexKey_Old[0] = key_ComplexKey_Cur[0];/*存储上次按键值*/
                key_ComplexKey_Old[1] = key_ComplexKey_Cur[1];/*存储上次按键值*/
                key_ComplexKey_Cur[0] = key_ComplexKey[0];    /*存储当前按键值*/
                key_ComplexKey_Cur[1] = key_ComplexKey[1];    /*存储当前按键值*/
                /** 
                * 存储上次按键个数 
                */
                key_ComplexKey_Old_Count = key_ComplexKey_Cur_Count; 
                /** 
                * 存储当前按键个数 
                */
                key_ComplexKey_Cur_Count = key_ComplexKey_Count;
                key_UpD_State_flg2 = 1;
                key_FnYT_state = 0;
                YT_key_state_flg = VfdYT;
                key_FnYT_state = Key_State_Process();
                key_FnYT_state |= 0x02;
                if(AVB_Run)
                {
                    WDI();
                    UART2_Send_Key2(0x11, key_FnYT_state,
                         key_ComplexKey_Cur[0], key_ComplexKey_Cur[1]);		
                }
		}
            break;
        default:
            if(key_ComplexKey_Cur_Count == 1)
            {
                if((key == 0xff) && (key_UpD_State_flg1))
                {
                    key_UpD_State_flg1 = key_UpD_State_flg2 =
                        key_UpD_State_flg3 = 0;
                    OldKeyValue = 0xff;
                    key_FnYT_state = 0;
                    YT_key_state_flg = VfdYT;
                    key_FnYT_state = Key_State_Process();
                    key_FnYT_state |= 0x01;
                    if(AVB_Run)
                    {
                        WDI();
                        UART2_Send_Key1(0x11, key_FnYT_state, CurKeyValue);
			}
                    /**
                    * Fn状态位在发送键值后清除，如果没有键值发送，等待3S延时失效
                    */
                    Fn_key_timer = 0;
                    Fn_key_state_flg = 0;
                }
            }
            if(key_ComplexKey_Cur_Count == 2)
            {
                if((key == 0xff) && (key_UpD_State_flg2))
                {
                    key_UpD_State_flg1 = key_UpD_State_flg2 =
                        key_UpD_State_flg3 = 0;
                    OldKeyValue = 0xff;
                    key_FnYT_state = 0;
                    YT_key_state_flg = VfdYT;
                    key_FnYT_state = Key_State_Process();
                    key_FnYT_state |= 0x01;
                    if(AVB_Run)
                    {
                        WDI();
                        UART2_Send_Key2(0x11, key_FnYT_state,
                            key_ComplexKey_Cur[0], key_ComplexKey_Cur[1]);
                    }
			               /**
                    * Fn状态位在发送键值后清除，如果没有键值发送，等待3S延时失效
                    */
                     Fn_key_timer = 0;
                    Fn_key_state_flg = 0;
                }
            }
            break;
    }
}

/** 
* @fn Key_State_Process 
* @brief  Key_State_Process 
* @param[in] none. 
* @param[out] none. 
* @return uint8. 
*/
uint16_t Key_State_Process(void)
{
    if(Fn_key_state_flg)
    {
        key_FnYT_state |= 0x80;
    }
    if(YT_key_state_flg)
    {
        key_FnYT_state |= 0x40;
    }
    return key_FnYT_state;
}

