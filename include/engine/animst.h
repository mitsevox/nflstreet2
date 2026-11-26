#ifndef ENGINE_ANIMST_H
#define ENGINE_ANIMST_H

#include "engine/animchan.h"
#include "engine/animemot.h"

/* 64-byte per-slot payload; its layout is the caller's (see fn_801BE60C). */
struct Block_801BE60C;

/* One of the four state slots: +0 key, +2 status, +4 flags, +6 state
   reference, +8 delay, +0xC payload, +0x4C weight fade. */
typedef struct AnimStSlot_t {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    short mUnknown6;
    float mUnknown8;
    unsigned char mUnknownC[64];
    AnimWgt_t mUnknown4C;
} AnimStSlot_t;

typedef struct AnimStInfo_t {
    unsigned char mUnknown0[4];
    AnimStSlot_t mUnknown4[4];
} AnimStInfo_t;

typedef int (*AnimStSelectAnimFunc_t)(AnimStateAnimList_t *pList, unsigned short key, AnimHeader_t *pObject,
                                      AnimChannel_t *pChannels, void *pOwner, int event);

typedef struct AnimStStateDefs_t {
    unsigned short mUnknown0;
    AnimStSelectAnimFunc_t *mpUnknown4;
} AnimStStateDefs_t;

/* Transition data an AnimFileStateTran_t rule points at. */
typedef struct AnimTranInfo_t {
    unsigned char mUnknown0[4];
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    float mUnknown8;
    unsigned short mUnknownC;
    unsigned short mUnknownE;
} AnimTranInfo_t;

extern AnimStateTransList_t lbl_803D4F50;

#ifdef __cplusplus
extern "C" {
#endif
int _AnimStCallSelectAnimFunc(unsigned short type, unsigned short key, void *pOwner, int event, AnimHeader_t *pObject,
                AnimChannel_t *pChannels);
void _AnimStOrganizeInfo(AnimStInfo_t *p);
void _AnimStEndState(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pChannels, int index,
                 void *pOwner);
unsigned short _AnimStMakeUniqueTransitionState(AnimStInfo_t *p);
int fn_801BE068(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pChannels, unsigned short key,
                float frames, void *pOwner);
struct Block_801BE60C *fn_801BE60C(AnimStInfo_t *p, unsigned short key);
unsigned short fn_801BE648(AnimStInfo_t *p);
void fn_801BE760(AnimStInfo_t *p, unsigned short key, unsigned short flags);
void AnimStSetStateDelay(AnimStInfo_t *p, unsigned short key, float value);
int _AnimTranGetStateTransitions(unsigned short type, unsigned short key);
void _AnimTranDoTransition(AnimStInfo_t *p, AnimHeader_t *pObject, AnimChannel_t *pChannels, unsigned short key,
                 unsigned short previous, int state, void *pOwner);
#ifdef __cplusplus
}
#endif

#endif
