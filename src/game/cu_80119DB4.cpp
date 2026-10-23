#include "game/Block_803EB028.h"
#include "game/Object_80039F5C.h"
#include "game/fn_80177FE0.h"
#include <math.h>

struct Record_80118894 {
    char mUnknown0[64];
    float mUnknown64;
    char mUnknown68[8];
    float mUnknown76;
};

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

/* View of the block at player +1072 as fn_80119DB4 and fn_8011A2C4 use it:
   four values at +24..+36 (handed to fn_800ABF00) and three multipliers at
   +40..+48. */
struct Block_80119DB4 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    int mUnknown16;
    int mUnknown20;
    float mUnknown24;
    float mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
    float mUnknown44;
    float mUnknown48;
    char mUnknown52[3];
    unsigned char mUnknown55;
    unsigned char mUnknown56;
};

extern "C" {
extern Block_803EB028 *lbl_803EB028;
extern float lbl_803EB02C;
extern float lbl_803EB030;
extern float lbl_803EB034;
extern float lbl_803EB038;
extern float lbl_803EB03C;
extern float lbl_803EB040;
extern float lbl_803EB044;
extern float lbl_803EB048;
extern float lbl_803EB04C;
extern float lbl_803EB050;
extern float lbl_803EB054;
extern float lbl_803EB058;
extern float lbl_803EB05C;
extern float lbl_803EB060;
extern float lbl_803EB064;
extern float lbl_803EB068;
extern float lbl_803EB06C;
extern float lbl_803EB070;
extern float lbl_803EB074;
extern float lbl_803EB078;
extern float lbl_803EB07C;
extern float lbl_803ECB08;
extern float lbl_803EB088;
float fn_80237260(int stream);
int fn_800E1554(Object_80039F5C *p);
void fn_80227690(Point_8017886C *pOut, Point_8017886C *pA, Point_8017886C *pB);
int fn_801783AC(int bit);
float fn_800AC004(int team, float value);
float fn_800AD204(int team, int value);
int fn_800B65A0(int team);
float fn_8016B938(void);
float fn_8016B974(void);
Object_80039F5C *fn_80137B40(void);
void fn_800ABF00(int team, Block_80119DB4 *p);
int fn_800CA5CC(Object_80039F5C *p, int kind, int value);
void fn_80118894(Record_80118894 *pA, Record_80118894 *pB, int a, int b, Object_80039F5C *pPlayerA, Object_80039F5C *pPlayerB);
}

extern "C" void fn_80119DB4(Object_80039F5C *p, Object_80039F5C *pOther, int apply)
{
    Block_80119DB4 *pBlock = (Block_80119DB4 *)&p->mUnknown1072;
    Block_80119DB4 *pOtherBlock = (Block_80119DB4 *)&pOther->mUnknown1072;
    Record_80118894 *pRecord = (Record_80118894 *)&p->mUnknown1032;
    Record_80118894 *pOtherRecord = (Record_80118894 *)&pOther->mUnknown1032;
    short *pRatings = p->mRatings;
    short *pOtherRatings = pOther->mRatings;
    int first = p->mUnknown1052 == 1;
    Object_80039F5C *pCarrier;

    pBlock->mUnknown24 = pRatings[7] * lbl_803EB050 + p->mUnknown2904Float * lbl_803EB054;
    pBlock->mUnknown28 = pRatings[7];
    pBlock->mUnknown32 = pRatings[7] * lbl_803EB060 + p->mUnknown2904Float * lbl_803EB064;
    pBlock->mUnknown36 = pRatings[7] * lbl_803EB070 + p->mUnknown2904Float * lbl_803EB074;
    pOtherBlock->mUnknown24 = pOtherRatings[9] * lbl_803EB058 + pOther->mUnknown2904Float * lbl_803EB05C;
    pOtherBlock->mUnknown28 = pOtherRatings[9];
    pOtherBlock->mUnknown32 = pOtherRatings[9] * lbl_803EB068 + pOther->mUnknown2904Float * lbl_803EB06C;
    pOtherBlock->mUnknown36 = pOtherRatings[9] * lbl_803EB078 + pOther->mUnknown2904Float * lbl_803EB07C;
    if (first && fn_801783AC(0) == 0) {
        float scale;

        pOtherBlock->mUnknown32 += pOtherBlock->mUnknown32 * lbl_803EB02C;
        scale = lbl_803EB028->mUnknown84;
        if (scale > lbl_803EB030) {
            scale = lbl_803EB030;
        }
        scale = fn_800AC004(pOther->mIdBytes[2], scale / lbl_803EB030);
        pBlock->mUnknown24 -= pBlock->mUnknown24 * scale;
        pBlock->mUnknown28 -= pBlock->mUnknown28 * scale;
        pBlock->mUnknown32 -= pBlock->mUnknown32 * scale;
        pBlock->mUnknown36 -= pBlock->mUnknown36 * scale;
    } else if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.4f) {
        pBlock->mUnknown24 += pBlock->mUnknown24 * lbl_803EB034;
        pBlock->mUnknown32 += pBlock->mUnknown32 * lbl_803EB034;
    }
    pCarrier = fn_80137B40();
    if (pCarrier != 0 && fn_800B65A0(pCarrier->mIdBytes[2]) != 0xFF && fn_800B65A0(pOther->mIdBytes[2]) == 0xFF) {
        float bonus = fn_8016B938();

        if (first && (pCarrier->mFlags & 0x8000)) {
            float other = fn_8016B974();

            if (bonus < other) {
                bonus = other;
            }
        }
        pOtherBlock->mUnknown24 += pOtherBlock->mUnknown24 * (bonus * lbl_803EB038);
        pOtherBlock->mUnknown28 += pOtherBlock->mUnknown28 * (bonus * lbl_803EB03C);
        pOtherBlock->mUnknown32 += pOtherBlock->mUnknown32 * (bonus * lbl_803EB040);
        pOtherBlock->mUnknown36 += pOtherBlock->mUnknown36 * (bonus * lbl_803EB044);
    }
    if (first && pCarrier != 0 && (pCarrier->mFlags & 0x8000)) {
        pBlock->mUnknown24 *= lbl_803EB048;
        pBlock->mUnknown28 *= lbl_803EB048;
        pBlock->mUnknown32 *= lbl_803EB048;
        pBlock->mUnknown36 *= lbl_803EB048;
        pOtherBlock->mUnknown24 *= lbl_803EB04C;
        pOtherBlock->mUnknown28 *= lbl_803EB04C;
        pOtherBlock->mUnknown32 *= lbl_803EB04C;
        pOtherBlock->mUnknown36 *= lbl_803EB04C;
    }
    if (fabsf(p->mMotion.mPos.mX) > 4.0f) {
        pBlock->mUnknown36 *= fn_800AD204(p->mIdBytes[2], p->mRatings[7]);
    }
    pBlock->mUnknown24 *= pBlock->mUnknown40;
    pBlock->mUnknown28 *= pBlock->mUnknown44;
    pBlock->mUnknown32 *= pBlock->mUnknown48;
    pOtherBlock->mUnknown24 *= pOtherBlock->mUnknown40;
    pOtherBlock->mUnknown28 *= pOtherBlock->mUnknown44;
    pOtherBlock->mUnknown32 *= pOtherBlock->mUnknown48;
    fn_800ABF00(p->mIdBytes[2], pBlock);
    fn_800ABF00(pOther->mIdBytes[2], pOtherBlock);
    if (apply) {
        fn_80118894(pRecord, pOtherRecord, fn_800CA5CC(p, 8, 0), fn_800CA5CC(pOther, 8, 0), p, pOther);
    }
}

extern "C" void fn_8011A2C4(Object_80039F5C *p, Object_80039F5C *pOther, Pair_8011BAE0 spot, int apply)
{
    Point_8017886C delta;
    Block_80119DB4 *pBlock = (Block_80119DB4 *)&p->mUnknown1072;
    Block_80119DB4 *pOtherBlock;
    Block_8011E240 *pState;
    Object_800B26B0 *pMotion;
    int angle;
    float share;
    float chance;
    float first;
    float second;
    float one;

    fn_80227690(&delta, (Point_8017886C *)&spot, (Point_8017886C *)&pOther->mMotion.mPos);
    pOtherBlock = (Block_80119DB4 *)&pOther->mUnknown1072;
    pState = &p->mBlock1032;
    pMotion = &p->mMotion;
    angle = delta.Heading();
    fn_80119DB4(p, pOther, apply);

    share = pBlock->mUnknown28 / (pBlock->mUnknown28 + pOtherBlock->mUnknown28);
    pBlock->mUnknown56 = fn_80237260(0) < share;
    pOtherBlock->mUnknown56 = pBlock->mUnknown56 ^ 1;
    if (pOtherBlock->mUnknown56) {
        share = 1.0f - share;
    }
    if (fn_80237260(0) >= share) {
        second = share * fn_80237260(0);
    } else {
        second = share * share;
    }

    share = pBlock->mUnknown24 / (pBlock->mUnknown24 + pOtherBlock->mUnknown24);
    pBlock->mUnknown55 = fn_80237260(0) < share;
    pOtherBlock->mUnknown55 = pBlock->mUnknown55 ^ 1;
    if (pOtherBlock->mUnknown55) {
        share = 1.0f - share;
    }
    if (fn_80237260(0) >= share) {
        first = share * fn_80237260(0);
    } else {
        first = share * share;
    }

    share = pBlock->mUnknown32 / (pBlock->mUnknown32 + pOtherBlock->mUnknown32);
    if (fn_800E1554(pOther)) {
        share = 0.0f;
    }
    if (fn_80237260(0) >= share) {
        chance = share * fn_80237260(0);
    } else {
        chance = share * share;
    }
    pBlock->mUnknown8 = chance;
    pOtherBlock->mUnknown8 = 1.0f - chance;

    share = pBlock->mUnknown36 / (pBlock->mUnknown36 + pOtherBlock->mUnknown36);
    if (fn_800E1554(pOther)) {
        share = 0.0f;
    }
    pBlock->mUnknown12 = share * lbl_803EB088;
    pOtherBlock->mUnknown12 = 1.0f - share;

    if (pBlock->mUnknown56) {
        pBlock->mUnknown20 = (angle - 0x800000) & 0xFFFFFF;
        pOtherBlock->mUnknown20 = angle;
        if (pBlock->mUnknown55) {
            pOtherBlock->mUnknown16 = pBlock->mUnknown16 = pMotion->mFacing;
            if (pState->mUnknown20 == 1 && fn_80177FE0().mY - pMotion->mPos.mY < 1.5f) {
                first = 0.0f;
            }
        } else {
            pBlock->mUnknown16 = pOtherBlock->mUnknown16 = pOther->mUnknown512.mUnknown4;
            first *= 0.5f;
            second *= 0.5f;
        }
    } else {
        pOtherBlock->mUnknown20 = (angle - 0x800000) & 0xFFFFFF;
        pBlock->mUnknown20 = angle;
        if (pOtherBlock->mUnknown55) {
            pBlock->mUnknown16 = pOtherBlock->mUnknown16 = angle;
        } else {
            pOtherBlock->mUnknown16 = pBlock->mUnknown16 = pMotion->mFacing;
            first *= 0.5f;
            if (pState->mUnknown20 == 1 && fn_80177FE0().mY - pMotion->mPos.mY < 1.5f) {
                first = 0.0f;
            }
            second *= 0.5f;
        }
    }
    pBlock->mUnknown0 = first;
    pOtherBlock->mUnknown0 = first;
    pBlock->mUnknown4 = second;
    pOtherBlock->mUnknown4 = second;
}
