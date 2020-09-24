#ifndef  _UPDATE_H
#define _UPDATE_H

void AppJumpToBoot(void);
uint16_t ReadUpdateFlag(uint16_t  BKP_Register);
void  WriteUpdateFlag(uint16_t  BKP_Register ,uint16_t FlagData);
void AppJumpToBoot(void);
void  WorkingsForUpdate(void);

#endif


