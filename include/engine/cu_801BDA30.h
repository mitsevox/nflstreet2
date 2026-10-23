#ifndef ENGINE_CU_801BDA30_H
#define ENGINE_CU_801BDA30_H

#include "engine/cu_801B9F00.h"
#include "engine/cu_801BA818.h"

/* 64-byte per-slot payload; its layout is the caller's (see fn_801BE60C). */
struct Block_801BE60C;

/* One of the four state slots: +0 key, +2 status, +4 flags, +6 state
   reference, +8 delay, +0xC payload, +0x4C weight fade. */
typedef struct Slot_801BE594 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    unsigned short mUnknown4;
    short mUnknown6;
    float mUnknown8;
    unsigned char mUnknownC[64];
    Block_801BF3C8 mUnknown4C;
} Slot_801BE594;

typedef struct Collection_801BE594 {
    unsigned char mUnknown0[4];
    Slot_801BE594 mUnknown4[4];
} Collection_801BE594;

typedef int (*Handler_801BDA30)(List_801BAB88 *pList, unsigned short key, Object_801BA03C *pObject,
                                Record_800D81C8 *pChannels, void *pOwner, int event);

typedef struct Handlers_801BDA30 {
    unsigned short mUnknown0;
    Handler_801BDA30 *mpUnknown4;
} Handlers_801BDA30;

/* Transition data a StateTran_801BAC1C rule points at. */
typedef struct Transition_801BEFA4 {
    unsigned char mUnknown0[4];
    unsigned short mUnknown4;
    unsigned short mUnknown6;
    float mUnknown8;
    unsigned short mUnknownC;
    unsigned short mUnknownE;
} Transition_801BEFA4;

extern List_801BAC1C lbl_803D4F50;

#ifdef __cplusplus
extern "C" {
#endif
int fn_801BDA30(unsigned short type, unsigned short key, void *pOwner, int event, Object_801BA03C *pObject,
                Record_800D81C8 *pChannels);
void fn_801BDAC0(Collection_801BE594 *p);
void fn_801BDBD4(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pChannels, int index,
                 void *pOwner);
unsigned short fn_801BDF38(Collection_801BE594 *p);
int fn_801BE068(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pChannels, unsigned short key,
                float frames, void *pOwner);
struct Block_801BE60C *fn_801BE60C(Collection_801BE594 *p, unsigned short key);
unsigned short fn_801BE648(Collection_801BE594 *p);
void fn_801BE760(Collection_801BE594 *p, unsigned short key, unsigned short flags);
void fn_801BE798(Collection_801BE594 *p, unsigned short key, float value);
int fn_801BE82C(unsigned short type, unsigned short key);
void fn_801BE99C(Collection_801BE594 *p, Object_801BA03C *pObject, Record_800D81C8 *pChannels, unsigned short key,
                 unsigned short previous, int state, void *pOwner);
#ifdef __cplusplus
}
#endif

#endif
