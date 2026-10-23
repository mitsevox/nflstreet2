#include "game/Team_80167A8C.h"
#include "game/cu_80136B1C.h"
#include "game/Block_801BE60C.h"
#include "game/fn_802270D4.h"
#include "game/Item_80097440.h"

extern "C" {
int fn_80097160(Object_80039F5C *p, float value);
int fn_801CFE40(float y, float x);
void fn_80227538(Point_80167910 *pOut, int angle, float length);
void fn_8009A5DC(int a, int b, void *pA, int *pB);
int fn_8009A298(int handle);
void fn_80096E74(Object_80039F5C *p, Vector_80039F5C *pVec, void *pData);
unsigned char *fn_8009CD00(Object_80039F5C *p, void (*pCallback)(Object_80039F5C *, Vector_80039F5C *, void *),
                           int right, int a, int b);
int fn_8023790C(void);
float fn_80178A08(void);
int fn_801CFFD0(int a, int b);
void fn_80137EC4(Object_80137ABC *pBall, Vector_80039F5C *pOut);
void fn_80227384(void *, void *, int);
void fn_80227638(void *, void *, void *);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_80137EFC(Object_80137ABC *pBall, Vector_80039F5C *pOut);
extern Block_80099630 *lbl_803EC92C;
extern float lbl_803EA2C4;
}

extern "C" int fn_80097160(Object_80039F5C *p, float duration)
{
    int *pFirst;
    int *pSecond = 0;
    unsigned char firstKind;
    unsigned char secondKind = 3;
    Data_80096E74 *pData = 0;
    unsigned char unknown;
    int handle;
    unsigned int type;

    if (p->mpState->mId == 28) {
        fn_8009A5DC(p->mpState->mUnknown1, p->mpState->mUnknown2, &unknown, &handle);
        type = fn_8009A298(handle);
        switch (type) {
        case 0:
            pFirst = &p->mUnknown108;
            firstKind = 0;
            break;
        case 1:
            pFirst = &p->mUnknown200;
            firstKind = 1;
            break;
        case 2:
            pFirst = &p->mUnknown200;
            firstKind = 1;
            pSecond = &p->mUnknown108;
            secondKind = 0;
            break;
        default:
            pSecond = 0;
            pFirst = 0;
            secondKind = 3;
            firstKind = 3;
            break;
        }
        if (pFirst != 0) {
            pData = (Data_80096E74 *)fn_8009CD00(p, fn_80096E74, firstKind, (unsigned int)duration, 2);
            if (pData != 0) {
                pData->mUnknown4 = firstKind;
                pData->mUnknown0 = fn_8023790C() + (unsigned int)duration + 2;
            }
        }
        if (pSecond != 0) {
            pData = (Data_80096E74 *)fn_8009CD00(p, fn_80096E74, secondKind, (unsigned int)duration, 2);
            if (pData != 0) {
                pData->mUnknown4 = secondKind;
                pData->mUnknown0 = fn_8023790C() + (unsigned int)duration + 2;
            }
        }
    }
    return pData != 0;
}

extern "C" int fn_8009780C(Object_80039F5C *p, Object_80137ABC *pBall)
{
    Vector_80039F5C velocity;

    float rate;

    fn_80137EFC(pBall, &velocity);
    rate = lbl_803EA2C4;
    return __builtin_fabsf(velocity.mZ / rate + 0.0029814816f) > 1e-07f;
}

extern "C" int fn_80097864(Object_80039F5C *p)
{
    if (__builtin_fabsf(p->mMotion.mPos.mX) > fn_80178A08() - 4.0f) {
        Point_8017886C direction;

        direction.mX = p->mMotion.mPos.mX;
        direction.mY = 0.0f;
        if (fn_801CFFD0(direction.Heading(), p->mMotion.mUnknown32) <= 0x355554) {
            return 1;
        }
    }
    return 0;
}

extern "C" void fn_800978F8(Object_80039F5C *p, Item_80097440 *pItem, Point_80167910 *pTarget, Vector_80039F5C *pPos,
                            float time, int *pTurn, Object_80137ABC *pBall)
{
    Vector_80039F5C ballPos;
    Point_80167910 target;
    Point_80167910 offset;
    Point_80167910 start;
    Point_80167910 velocity;
    Point_80167910 delta;
    int angle;
    int facing;

    if (p == 0 || pItem == 0 || pTurn == 0 || pBall == 0) {
        return;
    }
    fn_80137EC4(pBall, &ballPos);
    angle = (fn_801CFE40(ballPos.mY, ballPos.mX) + 0x800000) & 0xFFFFFF;
    target.mX = pTarget->mX;
    target.mY = pTarget->mY;
    fn_80227384(&offset, pPos, angle);
    fn_80227638(&start, &p->mMotion.mPos, &offset);
    fn_80227690(&velocity, &target, &start);
    lbl_803EC92C->mUnknown4.mUnknownC = time;
    lbl_803EC92C->mUnknown4.mUnknown18 = velocity.mX / time;
    lbl_803EC92C->mUnknown4.mUnknown1C = velocity.mY / time;
    fn_80227690(&delta, pPos, &pItem->mUnknown14);
    facing = p->mMotion.mFacing & 0xFFFFFF;
    *pTurn = fn_801CFFD0(angle, facing);
    if (((angle - facing) & 0xFFFFFF) > 0x800000) {
        *pTurn = -*pTurn;
    }
    if (fn_802270A4(&velocity) > 2.0f) {
        fn_80227538(&velocity, fn_801CFE40(velocity.mY, velocity.mX), 2.0f);
        lbl_803EC92C->mUnknown4.mUnknown18 = velocity.mX / time;
        lbl_803EC92C->mUnknown4.mUnknown1C = velocity.mY / time;
    }
}
