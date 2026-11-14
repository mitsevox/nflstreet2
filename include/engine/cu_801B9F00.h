#ifndef ENGINE_CU_801B9F00_H
#define ENGINE_CU_801B9F00_H

#include "engine/Record_800D81C8.h"

#ifdef __cplusplus
extern "C" {
#endif
int _AnimDoUserOpcodeCallback(int op);
int _AnimDoUserOpcodeSkipCallback(int op);
void _AnimUserCallbackPushState(unsigned int state);
void _AnimUserCallbackPushInfo(void *pUser);
void _AnimUserCallbackPopState(void);
void _AnimUserCallbackPopInfo(void);
void AnimInitHeader(AnimHeader_t *pList, unsigned short a, unsigned short b, unsigned short count);
int AnimGetSeqVersion(void);
int fn_801B9F00(AnimHeader_t *pList, Record_800D81C8 *pChannels);
int fn_801BA154(AnimHeader_t *pList, Record_800D81C8 *pChannels, int slot, int anim, float weight, int state,
                void *pUser, unsigned short stateRef);
void fn_801BA384(AnimHeader_t *pList, Record_800D81C8 *pChannels, int index);
void fn_801BA398(AnimHeader_t *pList, Record_800D81C8 *pChannels, int state);
unsigned short fn_801BA568(AnimHeader_t *pList, Record_800D81C8 *pChannels, unsigned short state);
unsigned short fn_801BA5A8(AnimHeader_t *pList, Record_800D81C8 *pChannels, unsigned short state, int index);
void fn_801BA60C(AnimHeader_t *pList, Record_800D81C8 *pChannels, int state, float delay);
int fn_801BA650(Record_800D81C8 *pChannel, float time, void *pUser);
void fn_801BC67C(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t);
int AnimSeqStart(AnimSeq_t *p, AnimScript_t *pScript);
int AnimSeqGrow(AnimSeq_t *p, float step);
float AnimSeqGetLife(AnimScript_t *pScript);
unsigned short AnimSeqGetNumFrames(AnimScript_t *pScript);
void AnimSeqSetRate(AnimSeq_t *p, float rate);
void AnimWgtSet(AnimWgt_t *p, int type, float a, void *pSource, float b);
void AnimWgtProcess(AnimWgt_t *p, float step);
void AnimWgtSetLinear(AnimWgt_t *p, unsigned int frames, float from, float to);
void AnimWgtSetLinearInAndOut(AnimWgt_t *p, unsigned char frames, unsigned char hold, float from, float to);
#ifdef __cplusplus
}
#endif

#endif
