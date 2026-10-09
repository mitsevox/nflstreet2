#include "game/Object_800EA284.h"
#include "game/Record_800B15FC.h"
#include "game/cu_80089330.h"
#include "game/cu_80136B1C.h"
#include "game/cu_80142BB4.h"
#include "game/fn_802270D4.h"

#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

extern "C" {
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_800E9528(Object_80039F5C *p);
void fn_8013A3BC(Object_80137ABC *pBall);
int fn_8013BA58(Object_80137ABC *pBall, int *pOut);
int fn_8013BA88(Object_80137ABC *pBall, void *pData, int value);
int fn_80178348(void);
int fn_801C4E98(void *p, const char *pName);
void fn_80227264(Vector_80039F5C *pOut, Vector_80039F5C *pV, float scale);
void fn_802271F0(Vector_80039F5C *pOut, Vector_80039F5C *pIn);
void fn_8022765C(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB);
float fn_802278D0(Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227930(Vector_80039F5C *pOut, Vector_80039F5C *pA, Vector_80039F5C *pB, float t);
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pPoint, Vector_80039F5C *pOut, float *pDist,
                 float *pT);
}

extern "C" void fn_80138590(Object_80137ABC *pBall)
{
    if (pBall) {
        pBall->mState.mUnknownF0 = 0.1f;
    }
}

extern "C" int fn_801385A8(Object_80137ABC *pBall)
{
    int result = 0;

    if (pBall) {
        Object_80039F5C *p = fn_80137AD0(pBall);

        if (p) {
            Vector_80039F5C pos;
            Vector_80039F5C left;
            Vector_80039F5C right;

            fn_80137D58(pBall, &pos);
            fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "lwrist"), &left, 0);
            fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, "rwrist"), &right, 0);
            if (fn_802278D0(&pos, &left) > 0.09f) {
                result = fn_802278D0(&pos, &right) > 0.09f;
            }
        }
    }
    return result;
}

extern "C" void fn_80138690(Object_80137ABC *pBall, Vector_80039F5C *pCenter, Vector_80039F5C *pDir,
                            Contact_80089330 *pContact, int push, float value)
{
    float x = pBall->mState.mUnknown54.mX;
    float y = pBall->mState.mUnknown54.mY;
    float z = pBall->mState.mUnknown54.mZ;
    Body_80142D98 motion;
    float length;
    float scale;

    motion.mUnknown0.mX = x - pCenter->mX;
    motion.mUnknown0.mY = y - pCenter->mY;
    motion.mUnknown0.mZ = z - pCenter->mZ;
    motion.mUnknown36 = 0.875f;
    fn_80142D98(&motion, pDir, value);
    if (push && fn_802270D4(&motion.mUnknown12) < 0.040000003f) {
        Vector_80039F5C step;

        fn_80143150(&step, pDir, 0.040000003f);
        if (step.mZ >= 0.0f) {
            step.mZ = 0.0f;
        }
        fn_8022765C(&motion.mUnknown12, &motion.mUnknown12, &step);
    }
    scale = fn_802270D4(&motion.mUnknown12);
    length = scale;
    if (scale > 0.20000002f) {
        scale = 0.20000002f;
    }
    fn_80227264(&motion.mUnknown12, &motion.mUnknown12, scale / length);
    motion.mUnknown12.mX += pCenter->mX;
    motion.mUnknown12.mY += pCenter->mY;
    motion.mUnknown12.mZ += pCenter->mZ;
    motion.mUnknown12.mX = CLAMP(motion.mUnknown12.mX, -0.17f, 0.17f);
    motion.mUnknown12.mY = CLAMP(motion.mUnknown12.mY, -0.17f, 0.17f);
    motion.mUnknown12.mZ = CLAMP(motion.mUnknown12.mZ, -0.2f, 0.05f);
    pBall->mState.mUnknown54.mX = motion.mUnknown12.mX;
    pBall->mState.mUnknown54.mY = motion.mUnknown12.mY;
    pBall->mState.mUnknown54.mZ = motion.mUnknown12.mZ;
}

extern "C" void fn_80138880(Vector_80039F5C *pOut, Object_80039F5C *p, Vector_80039F5C *pPos, unsigned char sub)
{
    Segment_80138CC0 *pSegment = &p->mpUnknown3092->mpUnknown36[sub].mSegment16;
    Vector_80039F5C down;
    Vector_80039F5C nearest;
    float dist;
    float value;

    fn_80227970(&pSegment->mUnknown0, &pSegment->mUnknown10, pPos, &nearest, &dist, &value);
    fn_802276B4(pOut, pPos, &nearest);
    fn_802271F0(pOut, pOut);
    switch (sub) {
    case 0:
        value = 0.2f;
        break;
    case 2:
    case 4:
    case 9:
    case 10:
        value = 0.5f;
        break;
    case 1:
    case 3:
        value = 0.25f;
        break;
    case 5:
    case 7:
        value = 0.25f;
        break;
    case 6:
    case 8:
        value = 0.35f;
        break;
    default:
        value = 0.5f;
        break;
    }
    down.mX = 0.0f;
    down.mY = 0.0f;
    down.mZ = -1.0f;
    fn_80227930(pOut, &down, pOut, value);
    fn_802271F0(pOut, pOut);
}

extern "C" void fn_801389D4(Object_80137ABC *pBall, Object_80039F5C *p, Contact_80089330 *pContact, unsigned char sub,
                            Vector_80039F5C *pPos)
{
    Segment_80142C5C ball;
    Segment_80142C5C target;
    Vector_80039F5C dir;
    Vector_80039F5C span;
    unsigned char hitA;
    unsigned char hitB;
    int flag = 0;
    float value;

    ball.mUnknown0.mX = pBall->mState.mPos.mX;
    ball.mUnknown0.mY = pBall->mState.mPos.mY;
    ball.mUnknown0.mZ = pBall->mState.mPos.mZ;
    ball.mUnknown12.mX = pBall->mState.mUnknown28.mX;
    ball.mUnknown12.mY = pBall->mState.mUnknown28.mY;
    ball.mUnknown12.mZ = pBall->mState.mUnknown28.mZ;
    target.mUnknown0.mX = p->mpUnknown3092->mpUnknown32[sub].mUnknown0;
    target.mUnknown0.mY = p->mpUnknown3092->mpUnknown32[sub].mUnknown4;
    target.mUnknown0.mZ = p->mpUnknown3092->mpUnknown32[sub].mUnknown8;
    target.mUnknown12.mX = p->mpUnknown3092->mpUnknown36[sub].mUnknown0;
    target.mUnknown12.mY = p->mpUnknown3092->mpUnknown36[sub].mUnknown4;
    target.mUnknown12.mZ = p->mpUnknown3092->mpUnknown36[sub].mUnknown8;
    if (fn_80142C5C(&ball, &target, &hitA, &hitB) && !fn_8013BA88(pBall, p, sub)) {
        fn_8009BD2C(p, &pBall->mState.mUnknownCC);
        fn_80138880(&dir, p, &pBall->mState.mUnknown28, sub);
        if (hitA) {
            pBall->mState.mPos = pPos ? *pPos : pBall->mState.mUnknown28;
        }
        switch (sub) {
        case 0:
            value = 0.12f;
            break;
        case 2:
        case 4:
        case 9:
        case 10:
            flag = 1;
            value = 0.05f;
            break;
        case 1:
        case 3:
        case 6:
        case 8:
            value = 0.08f;
            break;
        case 5:
        case 7:
            value = 0.09f;
            break;
        default:
            value = 0.08f;
            break;
        }
        fn_802276B4(&span, &target.mUnknown0, &target.mUnknown12);
        fn_8013A3BC(pBall);
        fn_80138690(pBall, &span, &dir, pContact, 1, value);
        if (fn_8013BA58(pBall, 0) == 4 && flag && p->mpState->mId == 28) {
            fn_8013847C(pBall, 1);
            if (fn_80178348() == p->mIdBytes[2]) {
                Record_800B15FC *pRecord = fn_800B15FC();

                fn_8009BD2C(p, &pRecord->mUnknown0);
                pRecord->mUnknownC = p->mMotion.mPos.mX;
                pRecord->mUnknown10 = p->mMotion.mPos.mY;
                pRecord->mUnknown14 = 36;
                fn_800B1508();
            }
        }
        if (fn_8013BA58(pBall, 0) == 4) {
            int id = p->mpState->mId;

            if (id != 28 && id != 58 && id != 5) {
                fn_800E9528(p);
            }
        }
    }
}
