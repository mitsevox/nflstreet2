/* The game balls: the saved 'ball' block of ball entries, their models and replay channel,
   who holds, targets and last touched each ball, and the per-frame ball loops. */

#include <math.h>
#include <string.h>

#include "game/Ball.h"
#include "game/cu_80089330.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include "game/fn_80054138.h"
#include "game/fn_80238174.h"

extern "C" {
Set_8003EE6C *fn_8003A078(void);
void fn_8003FAC4(int a);
void fn_8003FB2C(void);
Block_80170E64 *fn_8003FB54(int a, Block_80170E64 *pFirst, int b, int c, int d);
void fn_8003FBB4(int a, Block_80170E64 *pBlock);
int fn_8003FC68(void);
void fn_8003FC70(Block_80170E64 *pBlock, int a);
void fn_8003FE90(Block_80170E64 *pBlock, int a, int b, int c, int d, float e);
void fn_80030ACC(void (*pCallback0)(int a), void (*pCallback4)(int a, int b, int c, int d, float e), int size, const char *pName);
void fn_80076D7C(int id);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
int fn_800C47C4(void);
void fn_8013A440(Ball_t *pBall);
void fn_8013A6A8(Ball_t *pBall, float step);
void fn_8013A72C(Ball_t *pBall, float value);
void fn_8013AB24(Ball_t *pBall);
void fn_8013ABE0(Ball_t *pBall);
void BallStateUpdate(Ball_t *pBall, float step);
void BallStateMove(Ball_t *pBall, float step);
void BallStateChange(Ball_t *pBall, int a, int b);
int BallStateGet(Ball_t *pBall, int *pOut);
void BallHitPlayerPart(Ball_t *pBall, Object_80039F5C *p, Contact_80089330 *pContact, unsigned char sub, Vector_80039F5C *pPos);
void fn_80227538(Vector_80039F5C *pVector, int angle, float length);
float BallSweepToPart(Record_8003EC04 *pA, Record_8003EC04 *pB, unsigned char sub, Ball_t *pBall, Vector_80039F5C *pPos, unsigned char *pHit);
Set_8003EE6C *fn_801442F0(void);
void ParticlesAddBallEvent(int a, Ball_t *pBall);
int fn_801486A0(void);
void fn_801D0470(int a);
void fn_801D0494(void);
void fn_801D0860(Quat_801EB488 *pRot);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_801EB488(Quat_801EB488 *pRot);
void fn_801EB660(Quat_801EB488 *pOut, Quat_801EB488 *pA, Quat_801EB488 *pB);
void fn_801EBEF8(Quat_801EB488 *pOut, int a, int b, int c);
void fn_8022765C(float *pOut, float *pA, float *pB);
void fn_80227C2C(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void *fn_8023816C(void *pHandle);
int fn_80238258(const void *pA, const void *pB, unsigned int size);
int fn_80238278(const void *p, int size, int seed);
}

static BallBlock_t *_Ball_pSet = 0;
static int _Ball_iEntrySize;

extern "C" {

int BallBlockInit(void *p, int value)
{
    BallBlock_t *pSet = (BallBlock_t *)p;
    int i;

    pSet->mHeader.mpRecords = fn_8003EE6C(pSet->mHeader.mCount, pSet->mHeader.mCount);
    for (i = 0; i < pSet->mHeader.mCount; i++) {
        Ball_t *pBall = &pSet->mEntries[i];

        fn_801D34D0(pBall, sizeof(Ball_t), 0, 4);
        pBall->mState.mIndex = i;
        pBall->mState.mState = 0;
        pBall->mState.mStateArg = 0;
        pBall->mState.mPrevState = 0;
        pBall->mState.mPrevStateArg = 0;
        fn_8009BD2C(0, &pBall->mState.mUnknownB4);
        fn_8009BD2C(0, &pBall->mState.mUnknownC8);
        pBall->mState.mPos.mX = i * 5.0f + 15.0f;
        pBall->mState.mPos.mY = 20.0f;
        pBall->mState.mPos.mZ = 0.0f;
        fn_801EBEF8(&pBall->mState.mUnknown18, 0, 0xFFC00000, 0xFFC00000);
        fn_801EB488(&pBall->mState.mUnknown60);
        pBall->mState.mUnknownD0 = 0;
        pBall->mState.mUnknownE4 = 0;
        pBall->mState.mUnknownE8 = 1.0f;
        pBall->mState.mUnknownEC = 1.0f;
        pBall->mState.mpRecord = fn_8003EFB8(pSet->mHeader.mpRecords, 1, i);
    }
    return 0;
}

int BallBlockSyncModels(void *p, int value)
{
    BallBlock_t *pSet = (BallBlock_t *)p;
    unsigned int i;

    for (i = 0; i < pSet->mHeader.mCount; i++) {
        Ball_t *pBall = &pSet->mEntries[i];

        if (pBall->mpUnknown00) {
            fn_8013A440(pBall);
        }
    }
    return 0;
}

/* Compares two copies of the block, or returns a checksum of one. Record
   pointers are rebased from the live block to each copy. */
int BallBlockCompare(void *p, void *q)
{
    BallBlock_t *pA = (BallBlock_t *)p;
    BallBlock_t *pB = (BallBlock_t *)q;
    int result;
    int i;

    if (pB) {
        result = 0;
        result |= pA->mHeader.mCount != pB->mHeader.mCount;
        result |= pA->mHeader.mCurrent != pB->mHeader.mCurrent;
        if (!result) {
            for (i = 0; i < pA->mHeader.mCount; i++) {
                Ball_t *pBallA = &pA->mEntries[i];
                Ball_t *pBallB = &pB->mEntries[i];

                result |= fn_8003F4E8((Record_8003EC04 *)((char *)pBallA->mState.mpRecord + ((char *)pA - (char *)_Ball_pSet)),
                                      (Record_8003EC04 *)((char *)pBallB->mState.mpRecord + ((char *)pB - (char *)_Ball_pSet)),
                                      pBallA->mState.mpRecord);
                result |= pBallA->mpUnknown00 != pBallB->mpUnknown00;
                result |= fn_80238258(&pBallA->mState.mFlags, &pBallB->mState.mFlags, sizeof(BallState_t) - 4);
            }
        }
    } else {
        result = fn_80238278(pA, sizeof(BallBlockHeader_t), 0);
        for (i = 0; i < pA->mHeader.mCount; i++) {
            result = fn_80238278(&pA->mEntries[i].mState, sizeof(BallState_t), result);
        }
    }
    return result;
}

int BallBlockShutdown(void *p, int value)
{
    BallBlock_t *pSet = (BallBlock_t *)p;
    int i;

    for (i = 0; i < pSet->mHeader.mCount; i++) {
        pSet->mEntries[i].mState.mpRecord = 0;
    }
    return 0;
}

/* Saves the block followed by its record set, records and sub-records. */
int BallBlockSave(void *p, void *pBuffer)
{
    BallBlock_t *pSet = (BallBlock_t *)p;
    Set_8003EE6C *pRecords;
    short i;

    memcpy(pBuffer, pSet, sizeof(BallBlock_t) + (pSet->mHeader.mCount - 1) * sizeof(Ball_t));
    pRecords = pSet->mHeader.mpRecords;
    pBuffer = (char *)pBuffer + sizeof(BallBlock_t) + (pSet->mHeader.mCount - 1) * sizeof(Ball_t);
    memcpy(pBuffer, pRecords, sizeof(Set_8003EE6C));
    pBuffer = (char *)pBuffer + sizeof(Set_8003EE6C);
    memcpy(pBuffer, pRecords->mpUnknown0, pRecords->mUnknown4 * sizeof(Record_8003EC04));
    pBuffer = (char *)pBuffer + pRecords->mUnknown4 * sizeof(Record_8003EC04);
    for (i = 0; i < 2; i++) {
        memcpy(pBuffer, pRecords->mpUnknown14[i], pRecords->mUnknownC * sizeof(Sub_8003EC54));
        pBuffer = (char *)pBuffer + pRecords->mUnknownC * sizeof(Sub_8003EC54);
    }
    return 1;
}

/* Restores what BallBlockSave saved, keeping each entry's first word. */
int BallBlockRestore(void *p, void *pBuffer)
{
    BallBlock_t *pSet = (BallBlock_t *)p;
    BallBlock_t *pSaved = (BallBlock_t *)pBuffer;
    Set_8003EE6C *pRecords;
    Ball_t *pSrc;
    Ball_t *pDst;
    short i;

    memcpy(&pSet->mHeader, &pSaved->mHeader, sizeof(BallBlockHeader_t));
    pSrc = pSaved->mEntries;
    pDst = pSet->mEntries;
    for (i = 0; i < pSet->mHeader.mCount; i++) {
        pDst->mState = pSrc->mState;
        pDst++;
        pSrc++;
    }
    pRecords = pSet->mHeader.mpRecords;
    pBuffer = (char *)pSrc + sizeof(Set_8003EE6C);
    memcpy(pRecords->mpUnknown0, pBuffer, pRecords->mUnknown4 * sizeof(Record_8003EC04));
    pBuffer = (char *)pBuffer + pRecords->mUnknown4 * sizeof(Record_8003EC04);
    for (i = 0; i < 2; i++) {
        memcpy(pRecords->mpUnknown14[i], pBuffer, pRecords->mUnknownC * sizeof(Sub_8003EC54));
        pBuffer = (char *)pBuffer + pRecords->mUnknownC * sizeof(Sub_8003EC54);
    }
    return 1;
}

int BallBlockGetSaveSize(void *p)
{
    Set_8003EE6C *pRecords = _Ball_pSet->mHeader.mpRecords;

    return sizeof(BallBlock_t) + (_Ball_pSet->mHeader.mCount - 1) * sizeof(Ball_t) + sizeof(Set_8003EE6C)
         + pRecords->mUnknown4 * sizeof(Record_8003EC04) + pRecords->mUnknownC * sizeof(Sub_8003EC54) * 2;
}

void BallCollidePlayer(Record_8003EC04 *pA, Record_8003EC04 *pB, ContactList_8030BD74 *pContacts)
{
    Ball_t *pBall;
    Object_80039F5C *p;
    Vector_80039F5C bestPos;
    Vector_80039F5C pos;
    unsigned char hit;
    unsigned char sub;
    unsigned short state;
    int swapped;
    int bestSub;
    int best;
    unsigned int hits;
    float bestDist;
    float dist;
    int i;

    if (pA->mUnknown2E == 0) {
        Record_8003EC04 *pTemp = pA;
        swapped = 1;
        pA = pB;
        pB = pTemp;
    } else {
        swapped = 0;
    }
    pBall = BallGet(pA->mUnknown28);
    p = fn_8009BCE8(&pB->mUnknown28);
    if (p->mFlags & 0x10) {
        return;
    }
    state = BallStateGet(pBall, 0);
    if (state == 2 && p->mpState->mId != 0x38) {
        return;
    }
    if (state == 4 && p->mpState->mId == 0xF) {
        return;
    }
    if (state == 3 && p->mpState->mId == 0x19) {
        return;
    }
    bestDist = 10000.0f;
    bestSub = 0;
    best = 0;
    hits = 0;
    for (i = pContacts->mCount - 1; i >= 0; i--) {
        if (swapped == 1) {
            sub = pContacts->mpContacts[i].mUnknownC;
        } else {
            sub = pContacts->mpContacts[i].mUnknownD;
        }
        dist = BallSweepToPart(pA, pB, sub, pBall, &pos, &hit);
        if (hit) {
            hits++;
        }
        if (dist < bestDist) {
            bestDist = dist;
            bestSub = sub;
            best = i;
            bestPos.mX = pos.mX;
            bestPos.mY = pos.mY;
            bestPos.mZ = pos.mZ;
        }
    }
    if (hits > 1) {
        for (i = pContacts->mCount - 1; i >= 0; i--) {
            if (swapped == 1) {
                sub = pContacts->mpContacts[i].mUnknownC;
            } else {
                sub = pContacts->mpContacts[i].mUnknownD;
            }
            BallHitPlayerPart(pBall, p, &pContacts->mpContacts[i], sub, &bestPos);
        }
    } else {
        BallHitPlayerPart(pBall, p, &pContacts->mpContacts[best], bestSub, &bestPos);
    }
}

void BallsReplayRecord(int a)
{
    unsigned int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        fn_8003FC70(_Ball_pSet->mEntries[i].mpUnknown00, a);
    }
}

void BallsReplayPlayback(int a, int b, int c, int d, float e)
{
    unsigned int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        fn_8003FE90(_Ball_pSet->mEntries[i].mpUnknown00, a, b, c, d, e);
    }
}

void BallsReplayRegister(void)
{
    _Ball_iEntrySize = fn_8003FC68();
    fn_80030ACC(BallsReplayRecord, BallsReplayPlayback, _Ball_iEntrySize * _Ball_pSet->mHeader.mCount, "Balls");
}

void BallSetCurrent(unsigned char index)
{
    Ball_t *pBall = BallGetCurrent();

    if (pBall) {
        pBall->mState.mFlags &= ~1;
    }
    _Ball_pSet->mHeader.mCurrent = index;
    _Ball_pSet->mEntries[index].mState.mFlags |= 1;
}

Ball_t *BallGetCurrent(void)
{
    return &_Ball_pSet->mEntries[_Ball_pSet->mHeader.mCurrent];
}

unsigned char BallGetCurrentIndex(void)
{
    return _Ball_pSet->mHeader.mCurrent;
}

unsigned char BallGetIndex(Ball_t *pBall)
{
    unsigned char i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        if (&_Ball_pSet->mEntries[i] == pBall) {
            break;
        }
    }
    return i;
}

unsigned char BallFindByModel(Block_80170E64 *pBlock)
{
    unsigned char i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        if (_Ball_pSet->mEntries[i].mpUnknown00 == pBlock) {
            break;
        }
    }
    return i;
}

void BallsCreateModels(int a)
{
    Ball_t *pBalls;
    Block_80170E64 *pFirst = 0;
    unsigned int i;

    fn_8003FAC4(a);
    pBalls = _Ball_pSet->mEntries;
    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        int notFirst;

        if (i == 0) {
            notFirst = 0;
        } else {
            notFirst = 1;
        }

        pBalls[i].mpUnknown00 = fn_8003FB54(a, pFirst, fn_800C47C4(), 0xD, notFirst);
        if (i == 0) {
            pFirst = pBalls->mpUnknown00;
        }
    }
    BallSetCurrent(0);
    ParticlesAddBallEvent(5, BallGetCurrent());
}

void BallsDestroyModels(int a)
{
    unsigned int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        fn_8003FBB4(a, _Ball_pSet->mEntries[_Ball_pSet->mHeader.mCount - i - 1].mpUnknown00);
    }
    fn_8003FB2C();
}

void BallsProcessMotion(float step)
{
    unsigned int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        Object_80039F5C *p = BallGetHolder(&_Ball_pSet->mEntries[i]);

        if (p && (p->mpUnknown4->mUnknown20 & 1) == 0) {
            BallSetVisible(&_Ball_pSet->mEntries[i], 0);
        }
        BallStateMove(&_Ball_pSet->mEntries[i], step);
    }
}

void BallsProcessStates(float step)
{
    unsigned int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        BallStateUpdate(&_Ball_pSet->mEntries[i], step);
    }
}

void BallsProcessCollision(float step)
{
    Set_8003EE6C *pRecords;
    unsigned int i;

    fn_8003F04C(_Ball_pSet->mHeader.mpRecords);
    fn_8003F0AC(fn_8003A078(), _Ball_pSet->mHeader.mpRecords);
    pRecords = _Ball_pSet->mHeader.mpRecords;
    fn_8003F0AC(pRecords, fn_801442F0());
    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        fn_8013A6A8(&_Ball_pSet->mEntries[i], step);
    }
}

void BallsSyncModels(float step)
{
    unsigned int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        fn_8013A440(&_Ball_pSet->mEntries[i]);
    }
}

void BallsResetScales(void)
{
    int i;

    for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
        fn_8013ABE0(&_Ball_pSet->mEntries[i]);
    }
}

void BallReleaseStill(Ball_t *pBall, int a, int b)
{
    if (fn_801486A0() == 0 && (fn_800AD9B4() == 2 || fn_800AD9B4() == 4)) {
        return;
    }
    BallStateChange(pBall, a, b);
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown54;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown7C;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
    fn_8009BD2C(0, &pBall->mState.mUnknownB4);
}

void BallRelease(Ball_t *pBall, int a, int b)
{
    BallStateChange(pBall, a, b);
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown7C;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
    fn_8009BD2C(0, &pBall->mState.mUnknownB4);
}

void BallGiveToPlayer(Ball_t *pBall, Object_80039F5C *p)
{
    p->mFlags &= ~0x04000000;
    fn_8009BD2C(0, &pBall->mState.mUnknownCC);
    fn_8009BD2C(0, &pBall->mState.mUnknownC8);
    fn_8009BD2C(p, &pBall->mState.mUnknownB4);
    fn_8009BD2C(p, &pBall->mState.mUnknownB8);
    BallStateChange(pBall, 1, 0);
    if (fn_800AD9B4() == 3) {
        fn_80076D7C(p->mId);
    }
    pBall->mState.mUnknownD0 = 0;
    fn_8013A72C(pBall, 0.0f);
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown54;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
}

Ball_t *BallGet(int index)
{
    return &_Ball_pSet->mEntries[index];
}

Object_80039F5C *BallGetHolder(Ball_t *pBall)
{
    Object_80039F5C *p = 0;

    if (pBall) {
        p = fn_8009BCE8(&pBall->mState.mUnknownB4);
    }
    return p;
}

Object_80039F5C *BallGetLastHolder(Ball_t *pBall)
{
    Object_80039F5C *p = 0;

    if (pBall) {
        p = fn_8009BCE8(&pBall->mState.mUnknownB8);
    }
    return p;
}

Object_80039F5C *BallGetCurrentHolder(void)
{
    return BallGetHolder(BallGetCurrent());
}

Object_80039F5C *BallGetCurrentLastHolder(void)
{
    return BallGetLastHolder(BallGetCurrent());
}

Object_80039F5C *BallGetTarget(Ball_t *pBall)
{
    Object_80039F5C *p = 0;

    if (pBall) {
        p = fn_8009BCE8(&pBall->mState.mUnknownC8);
    }
    return p;
}

void BallSetTarget(Ball_t *pBall, Object_80039F5C *p)
{
    fn_8009BD2C(p, &pBall->mState.mUnknownC8);
}

Object_80039F5C *BallGetCurrentTarget(void)
{
    return BallGetTarget(BallGetCurrent());
}

void BallSetCurrentTarget(Object_80039F5C *p)
{
    fn_8009BD2C(p, &BallGetCurrent()->mState.mUnknownC8);
}

Ball_t *BallFindHeldBy(Object_80039F5C *p)
{
    unsigned char i;

    if (_Ball_pSet) {
        for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
            if (p == fn_8009BCE8(&_Ball_pSet->mEntries[i].mState.mUnknownB4)) {
                return &_Ball_pSet->mEntries[i];
            }
        }
    }
    return 0;
}

Ball_t *BallFindTargeting(Object_80039F5C *p)
{
    unsigned char i;

    if (_Ball_pSet) {
        for (i = 0; i < _Ball_pSet->mHeader.mCount; i++) {
            if (p == fn_8009BCE8(&_Ball_pSet->mEntries[i].mState.mUnknownC8)) {
                return &_Ball_pSet->mEntries[i];
            }
        }
    }
    return 0;
}

void BallGetPosition(Ball_t *pBall, Vector_80039F5C *pOut)
{
    pOut->mX = pBall->mState.mPos.mX;
    pOut->mY = pBall->mState.mPos.mY;
    pOut->mZ = pBall->mState.mPos.mZ;
}

void BallSetPosition(Ball_t *pBall, Vector_80039F5C *pPos)
{
    pBall->mState.mPos.mX = pPos->mX;
    pBall->mState.mPos.mY = pPos->mY;
    pBall->mState.mPos.mZ = pPos->mZ;
    pBall->mpUnknown00->mUnknown660 = fn_80054138(&pBall->mpUnknown00->mUnknown4.mX);
}

/* The entry position, raised to the higher capsule end of its record. */
void BallGetTopPosition(Ball_t *pBall, Vector_80039F5C *pOut)
{
    unsigned char i;

    pOut->mX = pBall->mState.mPos.mX;
    pOut->mY = pBall->mState.mPos.mY;
    pOut->mZ = pBall->mState.mPos.mZ;
    for (i = 0; i < 1; i++) {
        Sub_8003EC54 *pSub = &pBall->mState.mpRecord->mpUnknown20[i];

        if (pSub->mUnknown14 > pOut->mY) {
            pOut->mX = pSub->mUnknown10;
            pOut->mY = pSub->mUnknown14;
            pOut->mZ = pSub->mUnknown18;
        }
        if (pSub->mUnknown24 > pOut->mY) {
            pOut->mX = pSub->mUnknown20;
            pOut->mY = pSub->mUnknown24;
            pOut->mZ = pSub->mUnknown28;
        }
    }
    pOut->mY += 0.0972613543f;
}

void BallSetPrevPosition(Ball_t *pBall, Vector_80039F5C *p)
{
    pBall->mState.mUnknown28.mX = p->mX;
    pBall->mState.mUnknown28.mY = p->mY;
    pBall->mState.mUnknown28.mZ = p->mZ;
}

void BallSetRotation(Ball_t *pBall, int *pAngles)
{
    fn_801EBEF8(&pBall->mState.mUnknown18, pAngles[2], pAngles[1], pAngles[0]);
}

void BallGetVelocity(Ball_t *pBall, Vector_80039F5C *pOut)
{
    pOut->mX = pBall->mState.mUnknown54.mX;
    pOut->mY = pBall->mState.mUnknown54.mY;
    pOut->mZ = pBall->mState.mUnknown54.mZ;
}

void BallSetVelocity(Ball_t *pBall, Vector_80039F5C *p)
{
    pBall->mState.mUnknown54.mX = p->mX;
    pBall->mState.mUnknown54.mY = p->mY;
    pBall->mState.mUnknown54.mZ = p->mZ;
}

void BallGetSpin(Ball_t *pBall, Vector_80039F5C *pOut)
{
    pOut->mX = pBall->mState.mUnknown70.mX;
    pOut->mY = pBall->mState.mUnknown70.mY;
    pOut->mZ = pBall->mState.mUnknown70.mZ;
}

void BallClearSpin(Ball_t *pBall)
{
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown70;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
    fn_801EB488(&pBall->mState.mUnknown60);
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown88;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
    {
        Vector_80039F5C *pVector = &pBall->mState.mUnknown7C;

        pVector->mX = pVector->mY = pVector->mZ = 0.0f;
    }
}

int BallGetStateFrames(Ball_t *pBall)
{
    return pBall->mState.mUnknownBC;
}

int BallGetStateStartTick(Ball_t *pBall)
{
    return pBall->mState.mUnknownC0;
}

/* Allocates the block for count entries and registers its callbacks. */
void BallsStart(int count)
{
    void *pHandle;
    BallBlock_t *pSet;

    fn_8003EE2C(0, 1, BallCollidePlayer);
    pHandle = fn_80238174(0, (void **)&_Ball_pSet, sizeof(BallBlock_t) + (count - 1) * sizeof(Ball_t), 10, 0x62616C6C);
    fn_80238234(pHandle, BallBlockInit, BallBlockShutdown, BallBlockSyncModels, BallBlockCompare);
    fn_80238248(pHandle, BallBlockSave, BallBlockGetSaveSize, BallBlockRestore);
    pSet = (BallBlock_t *)fn_8023816C(pHandle);
    fn_801D34D0(pSet, sizeof(BallBlock_t), 0, 4);
    pSet->mHeader.mCount = count;
    fn_802381E0(pHandle);
}

int BallGetLandingPoint(Ball_t *pBall, Vector_80039F5C *pOut)
{
    int result = 0;

    if (pBall->mState.mFlags & 8) {
        *pOut = pBall->mState.mUnknown48;
        result = 1;
    } else {
        *pOut = pBall->mState.mPos;
    }
    return result;
}

int BallGetLandingTime(Ball_t *pBall, float *pOut)
{
    int result = 0;
    float value;

    if (pBall->mState.mFlags & 8) {
        value = pBall->mState.mUnknown44;
        result = 1;
    } else {
        value = 0.0f;
    }
    *pOut = value;
    return result;
}

/* Places the record's capsules along the entry's rotated axis. */
void BallUpdateCollRecord(Record_8003EC04 *pRecord)
{
    Ball_t *pBall = BallGet(pRecord->mUnknown28);
    Vector_80039F5C *pPos = &pBall->mState.mPos;
    Sub_8003EC54 *pSub;
    unsigned char i;

    BallGetModel(pBall);
    pRecord->mUnknown0 = pBall->mState.mPos.mX;
    pRecord->mUnknown4 = pBall->mState.mPos.mY;
    pRecord->mUnknown8 = pBall->mState.mPos.mZ;
    pRecord->mUnknown10 = pBall->mState.mPos.mZ - pRecord->mUnknown18;
    pRecord->mUnknown14 = pBall->mState.mPos.mZ + pRecord->mUnknown18;
    for (i = 0; i < 1; i++) {
        Vector_80039F5C axis;

        pSub = &pRecord->mpUnknown20[i];
        axis.mX = axis.mY = 0.0f;
        axis.mZ = 0.06940532f;
        fn_801D0470(3);
        fn_801D0494();
        fn_801D0860(&pBall->mState.mUnknown18);
        fn_80227C2C(&axis, &axis);
        pSub->mUnknown0 = pBall->mState.mPos.mX;
        pSub->mUnknown4 = pBall->mState.mPos.mY;
        pSub->mUnknown8 = pBall->mState.mPos.mZ;
        fn_8022765C(&pSub->mUnknown10, &pPos->mX, &axis.mX);
        fn_802276B4(&pSub->mUnknown20, &pPos->mX, &axis.mX);
    }
    if (!(pRecord->mUnknown2C & 2)) {
        pRecord->mUnknown18 = 0.8333334f;
        for (i = 0; i < 1; i++) {
            Sub_8003EC54 *pPair = &pRecord->mpUnknown24[i];

            pSub = &pRecord->mpUnknown20[i];
            pSub->mUnknown1C = 0.0972613543f;
            pPair->mUnknown1C = 0.0972613543f;
            pSub->mUnknownC = 0.16666667f;
            pPair->mUnknownC = 0.16666667f;
        }
        pRecord->mUnknown2C |= 2;
    }
}

Block_80170E64 *BallGetModel(Ball_t *pBall)
{
    return pBall->mpUnknown00;
}

Set_8003EE6C *BallGetCollRecords(void)
{
    return _Ball_pSet->mHeader.mpRecords;
}

/* Mirrors every entry: negates the X and Y of its vectors and turns its
   rotations by half a turn. */
void BallsMirror(void)
{
    BallBlock_t *pSet = _Ball_pSet;
    Quat_801EB488 turn;
    int i;

    for (i = 0; i < pSet->mHeader.mCount; i++) {
        Ball_t *pBall = &pSet->mEntries[i];

        pBall->mState.mPos.mX = -pBall->mState.mPos.mX;
        pBall->mState.mPos.mY = -pBall->mState.mPos.mY;
        pBall->mState.mUnknown28.mX = -pBall->mState.mUnknown28.mX;
        pBall->mState.mUnknown28.mY = -pBall->mState.mUnknown28.mY;
        pBall->mState.mUnknown54.mX = -pBall->mState.mUnknown54.mX;
        pBall->mState.mUnknown54.mY = -pBall->mState.mUnknown54.mY;
        pBall->mState.mUnknown70.mX = -pBall->mState.mUnknown70.mX;
        pBall->mState.mUnknown70.mY = -pBall->mState.mUnknown70.mY;
        pBall->mState.mUnknown94.mX = -pBall->mState.mUnknown94.mX;
        pBall->mState.mUnknown94.mY = -pBall->mState.mUnknown94.mY;
        fn_801EBEF8(&turn, 0, 0, 0x800000);
        fn_801EB660(&pBall->mState.mUnknown18, &turn, &pBall->mState.mUnknown18);
        fn_801EBEF8(&turn, 0, 0, 0x800000);
        fn_801EB660(&pBall->mState.mUnknown34, &turn, &pBall->mState.mUnknown34);
        fn_8013AB24(pBall);
    }
}

void BallSetTransferKind(Ball_t *pBall, int value)
{
    pBall->mState.mUnknownC4 = value;
}

int BallGetTransferKind(Ball_t *pBall)
{
    return pBall->mState.mUnknownC4;
}

int BallGetLastToucher(Ball_t *pBall)
{
    return pBall->mState.mUnknownCC;
}

int BallsExist(void)
{
    return _Ball_pSet != 0;
}

unsigned char BallsGetCount(void)
{
    unsigned char count;

    if (_Ball_pSet == 0) {
        count = 0;
    } else {
        count = _Ball_pSet->mHeader.mCount;
    }
    return count;
}

void BallsSetVisible(int on)
{
    BallBlock_t *pSet = _Ball_pSet;
    int i;

    if (!pSet) {
        return;
    }
    for (i = 0; i < pSet->mHeader.mCount; i++) {
        Block_80170E64 *pBlock = pSet->mEntries[i].mpUnknown00;

        if (on) {
            pBlock->mUnknown20 |= 1;
        } else {
            pBlock->mUnknown20 &= ~1;
        }
    }
}

void BallSetVisible(Ball_t *pBall, int on)
{
    Block_80170E64 *pBlock = pBall->mpUnknown00;

    if (on) {
        pBlock->mUnknown20 |= 1;
    } else {
        pBlock->mUnknown20 &= ~1;
    }
}

unsigned char BallIsVisible(Ball_t *pBall)
{
    return pBall->mpUnknown00->mUnknown20 & 1;
}

/* Copies the decaying value at +0xF0 into the Z of the vector at +0x54 and,
   when the X and Y are both near zero, gives them a random heading. */
void BallKickUp(Ball_t *pBall, int decay)
{
    Vector_80039F5C vector;

    BallGetVelocity(pBall, &vector);
    vector.mZ = pBall->mState.mUnknownF0;
    if (decay) {
        pBall->mState.mUnknownF0 -= 0.03f;
        pBall->mState.mUnknownF0 = pBall->mState.mUnknownF0 < 0.0f ? 0.0f : pBall->mState.mUnknownF0;
    }
    if (fabsf(vector.mX) < 1e-7f && fabsf(vector.mY) < 1e-7f) {
        unsigned char degrees = fn_802372EC(0, 360);

        fn_80227538(&vector, (int)(degrees * 46603.38f), 0.075f);
    }
    BallSetVelocity(pBall, &vector);
}
}
