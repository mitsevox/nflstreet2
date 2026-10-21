#ifndef ENGINE_CU_801B9F00_H
#define ENGINE_CU_801B9F00_H

#include "engine/Record_800D81C8.h"

#ifdef __cplusplus
extern "C" {
#endif
int fn_801B9D00(int op);
int fn_801B9D50(int op);
void fn_801B9D84(unsigned int state);
void fn_801B9DA8(void *pUser);
void fn_801B9DCC(void);
void fn_801B9DDC(void);
void fn_801B9EDC(Object_801BA03C *pList, unsigned short a, unsigned short b, unsigned short count);
int fn_801B9EF8(void);
int fn_801B9F00(Object_801BA03C *pList, Record_800D81C8 *pChannels);
int fn_801BA154(Object_801BA03C *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef);
void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index);
void fn_801BA398(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state);
unsigned short fn_801BA568(Object_801BA03C *pList, Record_800D81C8 *pChannels, unsigned short state);
unsigned short fn_801BA5A8(Object_801BA03C *pList, Record_800D81C8 *pChannels, unsigned short state, int index);
void fn_801BA60C(Object_801BA03C *pList, Record_800D81C8 *pChannels, int state, float delay);
int fn_801BA650(Record_800D81C8 *pChannel, float time, void *pUser);
void fn_801BC67C(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t);
int fn_801BD4C0(Block_801BD6D4 *p, Anim_801BAB34 *pScript);
int fn_801BD4E4(Block_801BD6D4 *p, float step);
float fn_801BD60C(Anim_801BAB34 *pScript);
unsigned short fn_801BD6DC(Anim_801BAB34 *pScript);
void fn_801BD710(Block_801BD6D4 *p, float rate);
void fn_801BF3C8(Block_801BF3C8 *p, int type, float a, void *pSource, float b);
void fn_801BF46C(Block_801BF3C8 *p, float step);
void fn_801BF4A8(Block_801BF3C8 *p, unsigned int frames, float from, float to);
void fn_801BF530(Block_801BF3C8 *p, unsigned char frames, unsigned char hold, float from, float to);
#ifdef __cplusplus
}
#endif

#endif
