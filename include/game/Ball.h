#ifndef GAME_BALL_H
#define GAME_BALL_H

#include "game/Object_80039F5C.h"
#include "game/cu_8003EC04.h"

/* The part of an Ball_t entry that the block snapshot saves,
   restores and checksums. */
struct BallState_t {
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
    /* State machine of src/game/BallState.cpp: current state and its
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
    int mUnknownD4;
    int mUnknownD8;
    float mUnknownDC;
    float mUnknownE0;
    int mUnknownE4;
    float mUnknownE8;
    float mUnknownEC;
    float mUnknownF0;
    int mIndex;
};

/* 0xF8-byte entry of BallBlock_t; BallGet returns entry i. */
struct Ball_t {
    Block_80170E64 *mpUnknown00;
    BallState_t mState;
};

/* Header of the 'ball' block that BallsStart allocates: entry count, the
   current entry and the collision record set of the entries. */
struct BallBlockHeader_t {
    unsigned char mCount;
    unsigned char mCurrent;
    Set_8003EE6C *mpRecords;
};

/* Allocated with room for mCount entries. */
struct BallBlock_t {
    BallBlockHeader_t mHeader;
    Ball_t mEntries[1];
};

extern "C" {
void BallsReplayRecord(int a);
void BallsReplayPlayback(int a, int b, int c, int d, float e);
void BallsReplayRegister(void);
void BallSetCurrent(unsigned char index);
Ball_t *BallGetCurrent(void);
unsigned char BallGetCurrentIndex(void);
unsigned char BallGetIndex(Ball_t *pBall);
unsigned char BallFindByModel(Block_80170E64 *pBlock);
void BallsCreateModels(int a);
void BallsDestroyModels(int a);
void BallsProcessMotion(float step);
void BallsProcessStates(float step);
void BallsProcessCollision(float step);
void BallsSyncModels(float step);
void BallsResetScales(void);
void BallReleaseStill(Ball_t *pBall, int a, int b);
void BallRelease(Ball_t *pBall, int a, int b);
void BallGiveToPlayer(Ball_t *pBall, Object_80039F5C *p);
Ball_t *BallGet(int index);
Object_80039F5C *BallGetHolder(Ball_t *pBall);
Object_80039F5C *BallGetLastHolder(Ball_t *pBall);
Object_80039F5C *BallGetCurrentHolder(void);
Object_80039F5C *BallGetCurrentLastHolder(void);
Object_80039F5C *BallGetTarget(Ball_t *pBall);
void BallSetTarget(Ball_t *pBall, Object_80039F5C *p);
Object_80039F5C *BallGetCurrentTarget(void);
void BallSetCurrentTarget(Object_80039F5C *p);
Ball_t *BallFindHeldBy(Object_80039F5C *p);
Ball_t *BallFindTargeting(Object_80039F5C *p);
void BallGetPosition(Ball_t *pBall, Vector_80039F5C *pOut);
void BallSetPosition(Ball_t *pBall, Vector_80039F5C *pPos);
void BallGetTopPosition(Ball_t *pBall, Vector_80039F5C *pOut);
void BallSetPrevPosition(Ball_t *pBall, Vector_80039F5C *p);
void BallSetRotation(Ball_t *pBall, int *pAngles);
void BallGetVelocity(Ball_t *pBall, Vector_80039F5C *pOut);
void BallSetVelocity(Ball_t *pBall, Vector_80039F5C *p);
void BallGetSpin(Ball_t *pBall, Vector_80039F5C *pOut);
void BallClearSpin(Ball_t *pBall);
int BallGetStateFrames(Ball_t *pBall);
int BallGetStateStartTick(Ball_t *pBall);
void BallsStart(int count);
int BallGetLandingPoint(Ball_t *pBall, Vector_80039F5C *pOut);
int BallGetLandingTime(Ball_t *pBall, float *pOut);
void BallUpdateCollRecord(Record_8003EC04 *pRecord);
Block_80170E64 *BallGetModel(Ball_t *pBall);
Set_8003EE6C *BallGetCollRecords(void);
void BallsMirror(void);
void BallSetTransferKind(Ball_t *pBall, int value);
int BallGetTransferKind(Ball_t *pBall);
int BallGetLastToucher(Ball_t *pBall);
int BallsExist(void);
unsigned char BallsGetCount(void);
void BallsSetVisible(int on);
void BallSetVisible(Ball_t *pBall, int on);
unsigned char BallIsVisible(Ball_t *pBall);
void BallKickUp(Ball_t *pBall, int decay);
}

#endif
