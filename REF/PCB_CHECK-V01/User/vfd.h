
#ifndef _vfd_H
#define _vfd_H

/*位带别名区地址*/
#define SRAM_BASE_BIT      0x22000000
#define SRAM_BitAddr(ByteOffset,BitOffset)   (SRAM_BASE_BIT+((ByteOffset*8)+BitOffset)*4)
//把该地址转换成一个指针
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR( BITBAND(addr, bitnum)  )

#define VfdBitBuf0_0  MEM_ADDR(SRAM_BitAddr(0,0))
#define VfdBitBuf0_1  MEM_ADDR(SRAM_BitAddr(0,1)) 
#define VfdBitBuf0_2  MEM_ADDR(SRAM_BitAddr(0,2)) 
#define VfdBitBuf0_3  MEM_ADDR(SRAM_BitAddr(0,3))  
#define VfdBitBuf0_4  MEM_ADDR(SRAM_BitAddr(0,4)) 
#define VfdBitBuf0_5  MEM_ADDR(SRAM_BitAddr(0,5)) 
#define VfdBitBuf0_6  MEM_ADDR(SRAM_BitAddr(0,6)) 
#define VfdBitBuf0_7  MEM_ADDR(SRAM_BitAddr(0,7)) 
                                                   
#define VfdBitBuf1_0  MEM_ADDR(SRAM_BitAddr(1,0))
#define VfdBitBuf1_1  MEM_ADDR(SRAM_BitAddr(1,1)) 
#define VfdBitBuf1_2  MEM_ADDR(SRAM_BitAddr(1,2)) 
#define VfdBitBuf1_3  MEM_ADDR(SRAM_BitAddr(1,3))  
#define VfdBitBuf1_4  MEM_ADDR(SRAM_BitAddr(1,4)) 
#define VfdBitBuf1_5  MEM_ADDR(SRAM_BitAddr(1,5)) 
#define VfdBitBuf1_6  MEM_ADDR(SRAM_BitAddr(1,6)) 
#define VfdBitBuf1_7  MEM_ADDR(SRAM_BitAddr(1,7)) 
                                                  
#define VfdBitBuf2_0  MEM_ADDR(SRAM_BitAddr(2,0))
#define VfdBitBuf2_1  MEM_ADDR(SRAM_BitAddr(2,1)) 
#define VfdBitBuf2_2  MEM_ADDR(SRAM_BitAddr(2,2)) 
#define VfdBitBuf2_3  MEM_ADDR(SRAM_BitAddr(2,3))  
#define VfdBitBuf2_4  MEM_ADDR(SRAM_BitAddr(2,4)) 
#define VfdBitBuf2_5  MEM_ADDR(SRAM_BitAddr(2,5)) 
#define VfdBitBuf2_6  MEM_ADDR(SRAM_BitAddr(2,6)) 
#define VfdBitBuf2_7  MEM_ADDR(SRAM_BitAddr(2,7)) 
                                                  
#define VfdBitBuf3_0  MEM_ADDR(SRAM_BitAddr(3,0))
#define VfdBitBuf3_1  MEM_ADDR(SRAM_BitAddr(3,1)) 
#define VfdBitBuf3_2  MEM_ADDR(SRAM_BitAddr(3,2)) 
#define VfdBitBuf3_3  MEM_ADDR(SRAM_BitAddr(3,3))  
#define VfdBitBuf3_4  MEM_ADDR(SRAM_BitAddr(3,4)) 
#define VfdBitBuf3_5  MEM_ADDR(SRAM_BitAddr(3,5)) 
#define VfdBitBuf3_6  MEM_ADDR(SRAM_BitAddr(3,6)) 
#define VfdBitBuf3_7  MEM_ADDR(SRAM_BitAddr(3,7)) 
                                                  
#define VfdBitBuf4_0  MEM_ADDR(SRAM_BitAddr(4,0)) 
#define VfdBitBuf4_1  MEM_ADDR(SRAM_BitAddr(4,1)) 
#define VfdBitBuf4_2  MEM_ADDR(SRAM_BitAddr(4,2)) 
#define VfdBitBuf4_3  MEM_ADDR(SRAM_BitAddr(4,3)) 
#define VfdBitBuf4_4  MEM_ADDR(SRAM_BitAddr(4,4)) 
#define VfdBitBuf4_5  MEM_ADDR(SRAM_BitAddr(4,5)) 
#define VfdBitBuf4_6  MEM_ADDR(SRAM_BitAddr(4,6)) 
#define VfdBitBuf4_7  MEM_ADDR(SRAM_BitAddr(4,7)) 
                                                  
#define VfdBitBuf5_0  MEM_ADDR(SRAM_BitAddr(5,0)) 
#define VfdBitBuf5_1  MEM_ADDR(SRAM_BitAddr(5,1)) 
#define VfdBitBuf5_2  MEM_ADDR(SRAM_BitAddr(5,2)) 
#define VfdBitBuf5_3  MEM_ADDR(SRAM_BitAddr(5,3)) 
#define VfdBitBuf5_4  MEM_ADDR(SRAM_BitAddr(5,4)) 
#define VfdBitBuf5_5  MEM_ADDR(SRAM_BitAddr(5,5)) 
#define VfdBitBuf5_6  MEM_ADDR(SRAM_BitAddr(5,6)) 
#define VfdBitBuf5_7  MEM_ADDR(SRAM_BitAddr(5,7)) 
                                                 
#define VfdBitBuf6_0  MEM_ADDR(SRAM_BitAddr(6,0)) 
#define VfdBitBuf6_1  MEM_ADDR(SRAM_BitAddr(6,1)) 
#define VfdBitBuf6_2  MEM_ADDR(SRAM_BitAddr(6,2)) 
#define VfdBitBuf6_3  MEM_ADDR(SRAM_BitAddr(6,3)) 
#define VfdBitBuf6_4  MEM_ADDR(SRAM_BitAddr(6,4)) 
#define VfdBitBuf6_5  MEM_ADDR(SRAM_BitAddr(6,5)) 
#define VfdBitBuf6_6  MEM_ADDR(SRAM_BitAddr(6,6)) 
#define VfdBitBuf6_7  MEM_ADDR(SRAM_BitAddr(6,7)) 
                                                   
#define VfdBitBuf7_0  MEM_ADDR(SRAM_BitAddr(7,0)) 
#define VfdBitBuf7_1  MEM_ADDR(SRAM_BitAddr(7,1)) 
#define VfdBitBuf7_2  MEM_ADDR(SRAM_BitAddr(7,2)) 
#define VfdBitBuf7_3  MEM_ADDR(SRAM_BitAddr(7,3)) 
#define VfdBitBuf7_4  MEM_ADDR(SRAM_BitAddr(7,4)) 
#define VfdBitBuf7_5  MEM_ADDR(SRAM_BitAddr(7,5)) 
#define VfdBitBuf7_6  MEM_ADDR(SRAM_BitAddr(7,6)) 
#define VfdBitBuf7_7  MEM_ADDR(SRAM_BitAddr(7,7)) 

#define VfdPic1          VfdBitBuf1_3
#define VfdPic2          VfdBitBuf0_2
#define VfdPic3          VfdBitBuf1_2
#define VfdPic4          VfdBitBuf0_1
#define VfdPic5          VfdBitBuf1_1
#define VfdPic6          VfdBitBuf0_0

#define VfdMontDetect    VfdBitBuf0_3
#define VfdBFArrow       VfdBitBuf0_4
#define VfdLock          VfdBitBuf0_5
#define VfdS             VfdBitBuf0_6
#define VfdHdLed         VfdBitBuf0_7
#define VfdYT            VfdBitBuf1_0
#define VfdTimeRecode    VfdBitBuf1_4
#define VfdBFFrame       VfdBitBuf1_5
#define VfdAlarmLed      VfdBitBuf1_6
#define VfdNet           VfdBitBuf1_7

#define VfdRecord        VfdBitBuf2_0
#define VfdCam           VfdBitBuf2_1
#define VfdHd            VfdBitBuf2_2
#define VfdLoss          VfdBitBuf2_3
#define Vfdala           VfdBitBuf2_5
#define VfdRapidBack     VfdBitBuf2_7
#define VfdStop          VfdBitBuf3_0
#define VfdSingleFrame   VfdBitBuf3_1
#define VfdBackEnd       VfdBitBuf3_2
#define VfdRapidForward  VfdBitBuf3_3
#define VfdPause         VfdBitBuf3_4
#define VfdPlay          VfdBitBuf3_5

#define NUMBER1          VfdBitBuf4_0
#define NUMBER2          VfdBitBuf5_1
#define NUMBER3          VfdBitBuf4_1
#define NUMBER4          VfdBitBuf5_2
#define NUMBER5          VfdBitBuf6_0
#define NUMBER6          VfdBitBuf7_1
#define NUMBER7          VfdBitBuf6_1
#define NUMBER8          VfdBitBuf7_2
#define NUMBER9          VfdBitBuf4_2
#define NUMBER10         VfdBitBuf5_3
#define NUMBER11         VfdBitBuf4_7
#define NUMBER12         VfdBitBuf4_3
#define NUMBER13         VfdBitBuf6_2
#define NUMBER14         VfdBitBuf7_3
#define NUMBER15         VfdBitBuf6_7
#define NUMBER16         VfdBitBuf6_3
#define NUMBER17         VfdBitBuf5_4
#define NUMBER18         VfdBitBuf5_0
#define NUMBER19         VfdBitBuf4_4
#define NUMBER20         VfdBitBuf5_5
#define NUMBER21         VfdBitBuf7_4
#define NUMBER22         VfdBitBuf7_0
#define NUMBER23         VfdBitBuf6_4
#define NUMBER24         VfdBitBuf7_5
#define NUMBER25         VfdBitBuf4_5
#define NUMBER26         VfdBitBuf5_6
#define NUMBER27         VfdBitBuf5_7
#define NUMBER28         VfdBitBuf4_6
#define NUMBER29         VfdBitBuf6_5
#define NUMBER30         VfdBitBuf7_6
#define NUMBER31         VfdBitBuf7_7
#define NUMBER32         VfdBitBuf6_6

#endif

