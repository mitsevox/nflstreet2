#include "game/Object_80039F5C.h"
#include "game/Query_800CE770.h"
#include "game/cu_80136B1C.h"
#include "game/fn_8022781C.h"
#include "game/Move_8011AB38.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

struct Block_803EB028 {
    int mUnknown0;
    char mUnknown4[80];
    unsigned int mUnknown84;
    unsigned char mUnknown88;
    unsigned char mUnknown89;
    unsigned char mUnknown90;
    char mUnknown91[1];
};

extern "C" {
extern Block_803EB028 *lbl_803EB028;
extern float lbl_803EB080;
extern float lbl_803EB084;
extern float lbl_803EB08C;
extern float lbl_803EB090;
extern Move_8011AB38 *lbl_802DAF8C[2][3][5];
int fn_80178320(void);
int fn_8011F1A4(void);
int fn_8011F1CC(void);
int fn_801787A0(void);
float fn_80237260(int stream);
int fn_800A851C(int team, Object_80039F5C *p);
int fn_800CE4A8(Query_800CE770 *pQuery);
int fn_800CD2B4(int mode, Object_80039F5C *p);
int fn_800EC758(Object_80039F5C *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
void fn_801187CC(Object_80039F5C *p, Object_80039F5C *pOther);
}

/* View of the block at player +1072 used by fn_8011A608 and fn_8011A7B4. */
struct Block_8011A608 {
    float mUnknown0;
    char mUnknown4[4];
    float mUnknown8;
    char mUnknown12[4];
    int mUnknown16;
    char mUnknown20[8];
    float mUnknown28;
    char mUnknown32[23];
    unsigned char mUnknown55;
};

extern "C" int fn_8011A608(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_8011A608 *pBlock = (Block_8011A608 *)&p->mUnknown1072;
    Block_8011A608 *pOtherBlock = (Block_8011A608 *)&pOther->mUnknown1072;
    int pass = 0;
    int result = 0;
    Query_800CE770 query;

    if (fn_800A851C(fn_80178320(), pOther)) {
        return 0;
    }
    if ((fn_8011F1CC() && fn_80237260(0) > lbl_803EB080) || (fn_8011F1A4() && fn_80237260(0) > lbl_803EB084)) {
        float chance = fn_80237260(0);

        if (chance < pBlock->mUnknown8) {
            fn_800CE770(&query);
            query.mUnknown36 = 0xE38E3;
            query.mUnknown44 = 0.4f;
            query.mpUnknown0 = p;
            query.mpUnknown4 = pOther;
            if (lbl_803EB028->mUnknown84 <= 24) {
                query.mUnknown52 = 150;
                result = fn_800CE4A8(&query);
            } else {
                query.mUnknown52 = 56;
                result = fn_800CE4A8(&query);
                if (result) {
                    pass = 1;
                }
            }
        } else if (chance < pOtherBlock->mUnknown8) {
            fn_800CE770(&query);
            query.mUnknown36 = 0xE38E3;
            query.mUnknown44 = 0.4f;
            query.mUnknown52 = 61;
            query.mpUnknown0 = p;
            query.mpUnknown4 = pOther;
            result = fn_800CE4A8(&query);
        }
    }
    if (result) {
        fn_8011E1BC(p, pOther, 0, 5);
        fn_8011E33C(pOther, p, 5);
        if (pass) {
            fn_801187CC(p, pOther);
        }
    }
    return result;
}

extern "C" Move_8011AB38 *fn_8011A7B4(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Block_8011A608 *pBlock = (Block_8011A608 *)&p->mUnknown1072;
    Block_8011A608 *pOtherBlock = (Block_8011A608 *)&pOther->mUnknown1072;
    int side;
    float limit;
    int dir;

    if (p->mUnknown1052 == 1) {
        side = 1;
        limit = 0.06f;
    } else {
        side = 0;
        limit = 0.175f;
    }
    if (fn_801CFFD0(pOther->mMotion.mFacing, p->mMotion.mFacing) > 0x671C72) {
        dir = 0;
    } else if (((p->mMotion.mFacing - pOther->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
        dir = 1;
    } else {
        dir = 2;
    }
    if (pBlock->mUnknown55) {
        if (pBlock->mUnknown0 > limit) {
            return lbl_802DAF8C[side][dir][1];
        }
    } else if (pOtherBlock->mUnknown0 > limit) {
        if (pOtherBlock->mUnknown28 > pBlock->mUnknown28) {
            return lbl_802DAF8C[side][dir][2];
        }
        if (((pOtherBlock->mUnknown16 - pOther->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
            return lbl_802DAF8C[side][dir][4];
        }
        return lbl_802DAF8C[side][dir][3];
    } else if (pOtherBlock->mUnknown28 > pBlock->mUnknown28) {
        if (((pOtherBlock->mUnknown16 - pOther->mMotion.mFacing) & 0xFFFFFF) > 0x800000) {
            return lbl_802DAF8C[side][dir][4];
        }
        return lbl_802DAF8C[side][dir][3];
    }
    return lbl_802DAF8C[side][dir][0];
}

extern "C" int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Pair_8011BAE0 delta;

    fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
    if (fn_801CFFD0(fn_801CFE40(delta.mUnknown4, delta.mUnknown0), pOther->mMotion.mFacing) > (int)(lbl_803EB08C * 46603.38f)) {
        Object_80039F5C *pCarrier = fn_80137B40();

        if (pCarrier != 0 && fn_8022781C(&pOther->mMotion.mPos, &pCarrier->mMotion.mPos) > lbl_803EB090) {
            return 0;
        }
    }
    if (fn_801787A0()) {
        return 0;
    }
    switch (pOther->mpState->mId) {
    case 22:
    case 92:
        return (pOther->mFlags >> 10) & 1;
    case 12:
    case 94:
        return p->mUnknown1040 == pOther->mId && fn_800CD2B4(1, pOther) == 0;
    case 1:
    case 5:
    case 10:
    case 15:
    case 16:
    case 17:
    case 28:
    case 50:
    case 58:
    case 91:
        return 0;
    case 57:
        return fn_800EC758(pOther);
    }
    return 1;
}

