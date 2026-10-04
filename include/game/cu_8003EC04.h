#ifndef GAME_CU_8003EC04_H
#define GAME_CU_8003EC04_H

#include "game/cu_80089330.h"

/* 48-byte sub-record of a collision record: three 16-byte float groups. The
   first holds a sphere (centre, radius at +12); the second and third hold the
   two ends of a capsule (radius at +28). */
struct Sub_8003EC54 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknownC;
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
    float mUnknown1C;
    float mUnknown20;
    float mUnknown24;
    float mUnknown28;
    char mUnknown2C[4];
};

/* 48-byte collision record with two sub-record arrays, which fn_8003EC04
   swaps before running the type callback registered with fn_8003EDD8. */
struct Record_8003EC04 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    char mUnknownC[4];
    float mUnknown10;
    float mUnknown14;
    float mUnknown18;
    char mUnknown1C[4];
    Sub_8003EC54 *mpUnknown20;
    Sub_8003EC54 *mpUnknown24;
    int mUnknown28;
    unsigned short mUnknown2C;
    unsigned char mUnknown2E;
    unsigned char mUnknown2F;
};

/* Record pool created by fn_8003EE6C: a record array and two sub-record arrays. */
struct Set_8003EE6C {
    Record_8003EC04 *mpUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknownC;
    int mUnknown10;
    Sub_8003EC54 *mpUnknown14;
    Sub_8003EC54 *mpUnknown18;
};

typedef void (*Callback_802DCF9C)(Record_8003EC04 *pRecord);
typedef void (*Callback_8003EE2C)(Record_8003EC04 *pA, Record_8003EC04 *pB, ContactList_8030BD74 *pContacts);

extern "C" {
void fn_8003EC04(Record_8003EC04 *pRecord);
void fn_8003EC54(Record_8003EC04 *pRecord);
void fn_8003ED30(int value);
void fn_8003EDB8(void);
void fn_8003EDD8(unsigned char type, unsigned char count, Callback_802DCF9C pCallback);
void fn_8003EE00(unsigned char type);
void fn_8003EE2C(unsigned char a, unsigned char b, Callback_8003EE2C pCallback);
Set_8003EE6C *fn_8003EE6C(int count, int subCount);
void fn_8003EF5C(Set_8003EE6C *pSet);
Record_8003EC04 *fn_8003EFB8(Set_8003EE6C *pSet, unsigned char type, int owner);
void fn_8003F04C(Set_8003EE6C *pSet);
void fn_8003F0AC(Set_8003EE6C *pA, Set_8003EE6C *pB);
void fn_8003F1B8(Record_8003EC04 *pA, Record_8003EC04 *pB);
int fn_8003F4E8(Record_8003EC04 *pA, Record_8003EC04 *pB, Record_8003EC04 *pBase);
void fn_8003F60C(Set_8003EE6C *pSet);
}

#endif
