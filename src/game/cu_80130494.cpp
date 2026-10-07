#include <math.h>
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_80054130.h"
#include "game/Object_8017886C.h"
#include "game/cu_80067C10.h"
#include "game/cu_80136B1C.h"
#include "game/fn_801C1F94.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80178D18.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
#define CLAMP(v, lo, hi) ((v) < (lo) ? (lo) : ((v) > (hi) ? (hi) : (v)))

struct Block_80130494 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    int mUnknown16;
    char mUnknown20[4];
    unsigned int mUnknown24;
    int mUnknown28;
    unsigned short mUnknown32;
    unsigned short mUnknown34;
    char mUnknown36[20];
    int mUnknown56;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
};

extern "C" {
void fn_8009A8D4(void *p);
void fn_8009BD2C(Object_80039F5C *p, int *pRef);
void fn_8009CE88(Object_80039F5C *p, int *pRecord, int a);
void fn_8009CEE4(Object_80039F5C *p, int ref, int joint, int a, int b);
int fn_8009F0B8(Object_80039F5C *p, int angle);
void fn_800F0BF8(Object_80039F5C *p, int a, int angle);
int fn_800FD2AC(Object_80039F5C *p);
int fn_800FD41C(Object_80039F5C *p);
int fn_8010A2DC(Object_80039F5C *p, int a, int b);
int fn_80112928(Object_80039F5C *p);
Object_80039F5C *fn_801244F0(Object_80039F5C *p, int team, int a, unsigned char count, float *pOut, int b);
Object_80039F5C *fn_801245DC(Object_80039F5C *p, int team, int a, unsigned char count, int angle, float *pOut, int b);
int fn_80178320(void);
int fn_801783AC(int bit);
float fn_80178A08(void);
float fn_80178A44(void);
int fn_801BE648(void *p);
int fn_801C4E98(void *p, const char *pName);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80237260(int stream);
float fn_8022781C(Vector_80039F5C *pA, Vector_80039F5C *pB);
void fn_80227970(Vector_80039F5C *pA, Vector_80039F5C *pB, Vector_80039F5C *pPoint, Vector_80039F5C *pOut, float *pDist,
                 float *pT);
void fn_800FD724(Object_80039F5C *p);
}

static float lbl_803EB128 = 4.0f;
static float lbl_803EB12C = 5.0f;
static float lbl_803EB130 = 40.0f;
static float lbl_803EB134 = 30.0f;
static float lbl_803EB138 = 50.0f;

extern "C" int fn_80130494(Object_80039F5C *p, Block_80130494 *pBlock)
{
    int angle = pBlock->mUnknown16;
    int found = 0;
    unsigned char i;
    unsigned int count = fn_80178D18(fn_80178320());

    for (i = 0; i < count; i++) {
        int check = 0;
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);

        switch (pOther->mpState->mId) {
        case 10:
        case 11:
        case 58:
        case 85:
        case 92:
            check = 1;
            break;
        }
        if (pOther->mFlags & 0x800) {
            check = 1;
        }
        if (pOther->mFlags & 0x4000) {
            check = 1;
        }
        if (check && !(fn_8022781C(&p->mMotion.mPos, &pOther->mMotion.mPos) > lbl_803EB12C)) {
            Point_8017886C delta;
            int dir;

            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            dir = fn_801CFE40(delta.mY, delta.mX);
            if (fn_801CFFD0(dir, angle) < (int)(lbl_803EB130 * 46603.38f)) {
                int offset = (int)(p->mUnknown560.mFlags.mBytes[0] ? lbl_803EB138 : lbl_803EB134);

                if (p->mpState->mUnknown4 == 19) {
                    if ((p->mpState->mUnknown6 * 0x20000 - angle & 0xFFFFFF) > 0x800000) {
                        found = 1;
                        angle -= (int)(offset * 46603.38f);
                    } else {
                        found = 1;
                        angle += (int)(offset * 46603.38f);
                    }
                } else if ((dir - angle & 0xFFFFFF) > 0x800000) {
                    found = 1;
                    angle += (int)(offset * 46603.38f);
                } else {
                    found = 1;
                    angle -= (int)(offset * 46603.38f);
                }
            }
        }
        if (found) {
            break;
        }
    }
    if (found
        && ((p->mMotion.mPos.mX > fn_80178A08() - lbl_803EB128 && fn_801CFFD0(angle, 0) <= 0x3FFFFF)
            || (p->mMotion.mPos.mX < lbl_803EB128 - fn_80178A08() && fn_801CFFD0(angle, 0x800000) <= 0x3FFFFF))) {
        found = 0;
    }
    if (found) {
        pBlock->mUnknown16 = angle;
    } else {
        pBlock->mUnknown16 = pBlock->mUnknown56;
    }
    return found;
}

extern "C" int fn_80130764(Object_80039F5C *p, Block_80130494 *pBlock)
{
    int angle = pBlock->mUnknown16;
    Object_80039F5C *pBest = 0;
    int found = 0;
    int bestDiff = 0x1000000;
    unsigned int count = 7;
    unsigned char i;

    for (i = 0; i < count; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);

        switch (pOther->mUnknown2914) {
        case 10:
        case 11:
        case 12: {
            Point_8017886C delta;
            int diff;

            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            diff = fn_801CFE40(delta.mY, delta.mX);
            diff = fn_801CFFD0(p->mMotion.mUnknown32, diff);
            if (diff <= bestDiff) {
                bestDiff = diff;
                pBest = pOther;
            }
            break;
        }
        }
    }
    if (pBest) {
        float dist = fn_8022781C(&p->mMotion.mPos, &pBest->mMotion.mPos);
        float value = 17.0f;

        value += (3.75f - dist) * 2.1333334f;
        value = CLAMP(value, 17.0f, 25.0f);

        if (dist < 3.75f && bestDiff <= 0xC16C0) {
            if (pBest->mMotion.mPos.mX <= p->mMotion.mPos.mX) {
                angle -= 0x133333;
            } else {
                angle += 0x133333;
            }
            found = 1;
        }
        if ((p->mMotion.mPos.mX > fn_80178A08() - lbl_803EB128 && fn_801CFFD0(angle, 0) <= 0x3FFFFF)
            || (p->mMotion.mPos.mX < lbl_803EB128 - fn_80178A08() && fn_801CFFD0(angle, 0x800000) <= 0x3FFFFF)) {
            found = 0;
        }
        if (found) {
            pBlock->mUnknown16 = angle;
        } else {
            pBlock->mUnknown16 = pBlock->mUnknown56;
        }
    } else {
        found = 0;
    }
    return found;
}

extern "C" int fn_80130948(Object_80039F5C *p, Block_80130494 *pBlock)
{
    int found = 0;
    Object_80054130 *pObject = fn_80054130();
    unsigned int i;

    for (i = 0; i < pObject->mUnknown88; i++) {
        Vector_80039F5C a;
        Vector_80039F5C b;
        Vector_80039F5C nearest;
        float dist;
        float t;

        fn_800541AC(&pObject->mUnknown8C[i], &a, &b);
        b.mZ = 0.0f;
        a.mZ = 0.0f;
        fn_80227970(&a, &b, &p->mMotion.mPos, &nearest, &dist, &t);
        if (dist < lbl_803EB128 * lbl_803EB128) {
            Point_8017886C delta;
            int dir;

            fn_80227690(&delta, &nearest, &p->mMotion.mPos);
            dir = fn_801CFE40(delta.mY, delta.mX);
            if (fn_801CFFD0(dir, p->mMotion.mUnknown32) <= 0x3FFFFF) {
                if ((dir - p->mMotion.mUnknown32 & 0xFFFFFF) <= 0x7FFFFF) {
                    pBlock->mUnknown16 = dir - 0x438E39 & 0xFFFFFF;
                } else {
                    pBlock->mUnknown16 = dir + 0x438E39 & 0xFFFFFF;
                }
                found = 1;
                break;
            }
        }
    }
    return found;
}

extern "C" int fn_80130A94(Object_80039F5C *p, Block_80130494 *pBlock)
{
    int result = 0;

    if (fn_801BE648(p->mpUnknown792) == 86) {
        fn_800F0BF8(p, 4, pBlock->mUnknown16);
        result = 1;
    }
    return result;
}

extern "C" int fn_80130AEC(Object_80039F5C *p)
{
    float dist;

    if (fn_801245DC(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1), 0x11C71C, &dist, 1) && dist < 5.0f) {
        return 0;
    }
    if (fn_801244F0(p, p->mIdBytes[2] ^ 1, 0, fn_80178D18(p->mIdBytes[2] ^ 1), &dist, 0) && dist < 2.5f) {
        return 0;
    }
    return 1;
}

extern "C" int fn_80130BC8(Object_80039F5C *p, Block_80130494 *pBlock)
{
    unsigned int angle = pBlock->mUnknown16 & 0xFFFFFF;
    unsigned int facing = p->mMotion.mFacing & 0xFFFFFF;
    int ok = pBlock->mUnknown12 > 0.72f && facing + 0x71C70 <= 0x8E38E1 && angle + 0x71C70 <= 0x8E38E1;

    if (ok && fn_801CFFD0(p->mUnknown512.mUnknown4, p->mMotion.mUnknown32) > 0x155555) {
        ok = 0;
    }
    if (ok && p->mpState->mUnknown4 == 19) {
        Point_8017886C delta;

        delta.mX = pBlock->mUnknown0 - p->mMotion.mPos.mX;
        delta.mY = pBlock->mUnknown4 - p->mMotion.mPos.mY;
        if (fn_802270A4(&delta) < 1.0f
            && fn_801CFFD0(p->mMotion.mUnknown32, p->mpState->mUnknown6 << 17 & 0xFFFFFF) > 0x155555) {
            ok = 0;
        }
    }
    return ok;
}

extern "C" int fn_80130CF0(Object_80039F5C *p)
{
    Block_80130494 *pBlock = (Block_80130494 *)&p->mUnknown336;
    int result;
    int moved;
    float margin;

    fn_8009A8D4(pBlock->mUnknown36);
    result = fn_800FD2AC(p);
    pBlock->mUnknown12 = MIN(pBlock->mUnknown12, 1.0f);
    moved = 0;
    if (fabs(pBlock->mUnknown0) > fn_80178A08() - 3.0f) {
        pBlock->mUnknown0 = MIN(pBlock->mUnknown0, fn_80178A08() - 3.0f);
        pBlock->mUnknown0 = MAX(pBlock->mUnknown0, 3.0f - fn_80178A08());
        moved = 1;
    }
    unsigned char *pInfo = &p->mpState->mUnknown4;

    if (pInfo[0] == 20 && (pInfo[2] == 5 || pInfo[2] == 7)) {
        margin = 4.5f;
    } else {
        margin = 3.0f;
    }
    if (pBlock->mUnknown4 > fn_80178A44() - margin) {
        pBlock->mUnknown4 = MIN(pBlock->mUnknown4, fn_80178A44() - margin);
        moved = 1;
    }
    if (moved == 1) {
        Point_8017886C delta;

        delta.mX = pBlock->mUnknown0;
        delta.mY = pBlock->mUnknown4;
        fn_80227690(&delta, &delta, &p->mMotion.mPos);
        pBlock->mUnknown8 = fn_802270A4(&delta);
        pBlock->mUnknown16 = fn_801CFE40(delta.mY, delta.mX);
    }
    pBlock->mUnknown24 = 0;
    pBlock->mUnknown60 = 0;
    pBlock->mUnknown61 = 0;
    pBlock->mUnknown34 = 0;
    pBlock->mUnknown32 = 0;
    pBlock->mUnknown28 = (int)((int)((1.0f - p->mRatings[3] / 255.0f) * 5.0f) + 2.0f);
    pBlock->mUnknown56 = pBlock->mUnknown16;
    if (fn_80130A94(p, pBlock)) {
        result = 0;
    }
    return result;
}

extern "C" int fn_80130F88(Object_80039F5C *p)
{
    Block_80130494 *pBlock = (Block_80130494 *)&p->mUnknown336;
    int result;

    fn_801374BC();
    if (fn_8010A2DC(p, 0, -1) == 1) {
        pBlock->mUnknown61 = 1;
        pBlock->mUnknown60 = 0;
        p->mUnknown512.mUnknown15 = 0;
    }
    pBlock->mUnknown24++;
    if (!(p->mFlags & 0x4000) && fn_80137B40() && fn_801783AC(0)) {
        Message_800F01CC message;

        fn_801C1F94(&message, 0, 4);
        message.mId = 33;
        fn_800F053C(0, p->mpState, &message, p);
        return 1;
    }
    if (!fn_80130764(p, pBlock)) {
        fn_80130494(p, pBlock);
    }
    fn_80130948(p, pBlock);
    result = fn_800FD41C(p);
    if (fn_80130BC8(p, pBlock)) {
        int move = 1;

        if (pBlock->mUnknown60 == 0 && (pBlock->mUnknown34 == 18 || pBlock->mUnknown34 == 19)
            && fn_80237260(0) < 0.5f) {
            move = pBlock->mUnknown34;
        }
        p->mUnknown512.mUnknown15 = move;
    } else {
        p->mUnknown512.mUnknown15 = pBlock->mUnknown34;
    }
    if (pBlock->mUnknown60 == 1 && --pBlock->mUnknown32 & 0x8000) {
        pBlock->mUnknown60 = 0;
        pBlock->mUnknown34 = 0;
    }
    if (!result) {
        if (--pBlock->mUnknown28 < 0 || fn_8009F0B8(p, 0x2AAAAA)) {
            pBlock->mUnknown28 = (int)((int)((1.0f - p->mRatings[3] / 255.0f) * 5.0f) + 2.0f);
            if (fn_80112928(p)) {
                result = 1;
            }
        }
        if (!result && pBlock->mUnknown60 == 0 && p->mUnknown16 != 2 && fn_800F06F4(0, p->mpState, 19, 1) == 0xFFFF) {
            Vector_80039F5C delta;
            float dist;

            delta.mX = pBlock->mUnknown0 - p->mMotion.mPos.mX;
            delta.mY = pBlock->mUnknown4 - p->mMotion.mPos.mY;
            dist = fn_802270A4(&delta);
            if (dist > 2.5f && dist < 6.0f) {
                Object_80039F5C *pCarrier;

                if (pBlock->mUnknown61 == 0 && fn_801CFFD0(pBlock->mUnknown16, p->mMotion.mFacing) <= 0x38E37
                    && fn_80130AEC(p) == 1 && fn_80137B40()) {
                    int dir;
                    int side;

                    fn_80137D58(fn_801374BC(), &delta);
                    fn_80227690(&delta, &delta, &p->mMotion.mPos);
                    dir = fn_801CFE40(delta.mY, delta.mX);
                    side = fn_801CFFD0(p->mMotion.mFacing, dir + 0x400000) <= 0x3FFFFF;
                    pBlock->mUnknown34 = side ? 19 : 18;
                    pBlock->mUnknown32 = fn_802372EC(0, 40) + 40;
                    fn_80067E3C(98, &p->mMotion.mPos, p->mId, 0, 0, 0);
                    pBlock->mUnknown60 = 1;
                    pBlock->mUnknown61 = 1;
                }
                if (pBlock->mUnknown60 == 0 && pBlock->mUnknown24 > 5 && (pCarrier = fn_80137B40()) != 0) {
                    int ref;

                    fn_8009BD2C(pCarrier, &ref);
                    fn_8009CEE4(p, ref, fn_801C4E98(pCarrier->mpUnknown4->mpUnknown100, "up_torso"), 8, 2);
                }
            }
        }
    } else {
        fn_8009CE88(p, &p->mUnknown16, 8);
    }
    return result;
}

extern "C" int fn_801313DC(Object_80039F5C *p)
{
    fn_8009CE88(p, &p->mUnknown16, 8);
    fn_800FD724(p);
    return 1;
}
