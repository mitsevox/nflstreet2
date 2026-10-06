#ifndef GAME_CU_80136B1C_H
#define GAME_CU_80136B1C_H

#include "game/Object_80039F5C.h"
#include "game/cu_8003EC04.h"

/* Rotation built by fn_801EBEF8 from three angles and reset by fn_801EB488. */
struct Quat_801EB488 {
    float mX;
    float mY;
    float mZ;
    float mW;
};

/* The part of an Object_80137ABC entry that the block snapshot saves,
   restores and checksums. */
struct State_80137ABC {
    Record_8003EC04 *mpRecord;
    unsigned int mFlags;
    Vector_80039F5C mPos;
    Quat_801EB488 mUnknown18;
    Vector_80039F5C mUnknown28;
    Quat_801EB488 mUnknown34;
    float mUnknown44;
    Vector_80039F5C mUnknown48;
    Vector_80039F5C mUnknown54;
    Quat_801EB488 mUnknown60;
    Vector_80039F5C mUnknown70;
    Vector_80039F5C mUnknown7C;
    Vector_80039F5C mUnknown88;
    Vector_80039F5C mUnknown94;
    int mUnknownA0;
    /* State machine of src/game/cu_8013B874.cpp: current state and its
       argument, then the previous state and its argument. */
    int mState;
    int mStateArg;
    int mPrevState;
    int mPrevStateArg;
    int mUnknownB4;
    int mUnknownB8;
    int mUnknownBC;
    int mUnknownC0;
    int mUnknownC4;
    int mUnknownC8;
    int mUnknownCC;
    int mUnknownD0;
    char mUnknownD4[16];
    int mUnknownE4;
    float mUnknownE8;
    float mUnknownEC;
    float mUnknownF0;
    int mIndex;
};

/* 0xF8-byte entry of Set_80137F98; fn_80137ABC returns entry i. */
struct Object_80137ABC {
    Block_80170E64 *mpUnknown00;
    State_80137ABC mState;
};

/* Header of the 'ball' block that fn_80137F98 allocates: entry count, the
   current entry and the collision record set of the entries. */
struct Header_80137F98 {
    unsigned char mCount;
    unsigned char mCurrent;
    Set_8003EE6C *mpRecords;
};

/* Allocated with room for mCount entries. */
struct Set_80137F98 {
    Header_80137F98 mHeader;
    Object_80137ABC mEntries[1];
};

extern "C" {
void fn_80137314(int a);
void fn_8013737C(int a, int b, int c, int d, float e);
void fn_8013740C(void);
void fn_8013745C(unsigned char index);
Object_80137ABC *fn_801374BC(void);
unsigned char fn_801374D4(void);
unsigned char fn_801374E0(Object_80137ABC *pBall);
unsigned char fn_80137534(Block_80170E64 *pBlock);
void fn_80137588(int a);
void fn_8013764C(int a);
void fn_801376B8(float step);
void fn_80137758(float step);
void fn_801377C4(float step);
void fn_80137864(void);
void fn_801378C0(void);
void fn_8013791C(Object_80137ABC *pBall, int a, int b);
void fn_801379B4(Object_80137ABC *pBall, int a, int b);
void fn_80137A04(Object_80137ABC *pBall, Object_80039F5C *p);
Object_80137ABC *fn_80137ABC(int index);
Object_80039F5C *fn_80137AD0(Object_80137ABC *pBall);
Object_80039F5C *fn_80137B08(Object_80137ABC *pBall);
Object_80039F5C *fn_80137B40(void);
Object_80039F5C *fn_80137B64(void);
Object_80039F5C *fn_80137B88(Object_80137ABC *pBall);
void fn_80137BC0(Object_80137ABC *pBall, Object_80039F5C *p);
Object_80039F5C *fn_80137BEC(void);
void fn_80137C10(Object_80039F5C *p);
Object_80137ABC *fn_80137C48(Object_80039F5C *p);
Object_80137ABC *fn_80137CD0(Object_80039F5C *p);
void fn_80137D58(Object_80137ABC *pBall, Vector_80039F5C *pOut);
void fn_80137D74(Object_80137ABC *pBall, Vector_80039F5C *pPos);
void fn_80137DC8(Object_80137ABC *pBall, Vector_80039F5C *pOut);
void fn_80137E74(Object_80137ABC *pBall, Vector_80039F5C *p);
void fn_80137E90(Object_80137ABC *pBall, int *pAngles);
void fn_80137EC4(Object_80137ABC *pBall, Vector_80039F5C *pOut);
void fn_80137EE0(Object_80137ABC *pBall, Vector_80039F5C *p);
void fn_80137EFC(Object_80137ABC *pBall, Vector_80039F5C *pOut);
void fn_80137F18(Object_80137ABC *pBall);
int fn_80137F88(Object_80137ABC *pBall);
int fn_80137F90(Object_80137ABC *pBall);
void fn_80137F98(int count);
int fn_80138064(Object_80137ABC *pBall, Vector_80039F5C *pOut);
int fn_801380AC(Object_80137ABC *pBall, float *pOut);
void fn_801380DC(Record_8003EC04 *pRecord);
Block_80170E64 *fn_8013825C(Object_80137ABC *pBall);
Set_8003EE6C *fn_80138264(void);
void fn_80138270(void);
void fn_80138398(Object_80137ABC *pBall, int value);
int fn_801383A0(Object_80137ABC *pBall);
int fn_801383A8(Object_80137ABC *pBall);
int fn_801383B0(void);
unsigned char fn_801383C8(void);
void fn_801383E4(int on);
void fn_80138440(Object_80137ABC *pBall, int on);
unsigned char fn_8013846C(Object_80137ABC *pBall);
void fn_8013847C(Object_80137ABC *pBall, int decay);
}

#endif
