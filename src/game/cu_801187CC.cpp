#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Block_803EB028.h"
#include "game/Query_800CE770.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800B65A0.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802270D4.h"
#include "game/fn_80178D18.h"
#include "game/fn_802372EC.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

/* View of the block at player +1032 used by fn_80118B4C. */
struct Block_80118B4C {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[28];
    float mUnknown52;
};

/* View of the block at player +1032 used by fn_80119020. */
struct Block_80119020 {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[71];
    unsigned char mUnknown95;
    char mUnknown96[5];
    unsigned char mUnknown101;
    short mUnknown102;
    unsigned char mUnknown104;
    unsigned char mUnknown105;
};

/* View of the block at player +1032 used by fn_801194F0. */
struct Block_801194F0 {
    int mUnknown0;
    char mUnknown4[16];
    int mUnknown20;
    char mUnknown24[16];
    float mUnknown40;
    char mUnknown44[8];
    float mUnknown52;
    char mUnknown56[39];
    unsigned char mUnknown95;
};

extern "C" {
int fn_800A7F08(int team);
int fn_801C4E98(void *p, const char *name);
void fn_80227930(void *pOut, void *pA, void *pB, float t);
int fn_801784C4(void);
extern const char lbl_8029DB78[];
int fn_800CA5CC(Object_80039F5C *p, int kind, int apply);
int fn_800CE4A8(Query_800CE770 *p);
int fn_8011F1CC(void);
int fn_801CFFD0(int a, int b);
int fn_801CFE40(float y, float x);
int fn_800C8BAC(Object_80039F5C *p, int which);
int fn_8011A994(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_8011A2C4(Object_80039F5C *p, Object_80039F5C *pOther, Pair_8011BAE0 pair, int a);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **ppBlocker);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int a);
void fn_801187CC(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_80227890(void *pA, void *pB);
float fn_80237260(int stream);
extern Block_803EB028 *lbl_803EB028;
extern float lbl_803EB020;
extern float lbl_803ECB08;
extern int lbl_802DAC38[];
int fn_8011F32C(void);
int fn_80177C38(void);
int fn_801787A0(void);
int fn_80178308(void);
int fn_801783AC(int value);
unsigned int fn_8011E188(void);
Object_80039F5C *fn_80124C28(Object_80039F5C *p, float *pOut, int angle, float length, float width, int facing);
float fn_802270A4(void *);
int fn_80178320(void);
int fn_800A851C(int team, Object_80039F5C *p);
int fn_800A8444(int team);
int fn_80113BCC(Object_80039F5C *p);
void fn_8011BAE0(Pair_8011BAE0 *pOut);
void fn_802276B4(void *pOut, void *pA, void *pB);
extern int lbl_802DAC20[];
}

extern "C" void fn_801187CC(Object_80039F5C *p, Object_80039F5C *pOther)
{
    Vector_80039F5C a;
    Vector_80039F5C b;
    Vector_80039F5C mid;

    if (fn_800A7F08(p->mIdBytes[2]) == 2) {
        fn_8009BF5C(p, fn_801C4E98(p->mpUnknown4->mpUnknown100, lbl_8029DB78), &a, 0);
        fn_8009BF5C(pOther, fn_801C4E98(pOther->mpUnknown4->mpUnknown100, lbl_8029DB78), &b, 0);
        fn_80227930(&mid, &b, &a, 0.75f);
        if (fn_801784C4() != 0) {
            mid.mX = -mid.mX;
            mid.mY = -mid.mY;
        }
    }
}

extern "C" int fn_80118B4C(Object_80039F5C *p, Pair_8011BAE0 *pPair)
{
    Block_80118B4C *pBlock = (Block_80118B4C *)&p->mBlock1032;
    Query_800CE770 query;
    Object_80039F5C *pOther;
    Block_80118B4C *pOtherBlock;
    unsigned int count;
    float roll;
    int result;
    int close;
    float slow;
    Point_8017886C delta;
    int moves[2];

    fn_800CA5CC(p, 8, 0);
    result = 0;
    close = 0;
    if (!fn_80137C48(p) && (p->mUnknown1032 == 2 || p->mUnknown1032 == 3)) {
        pOther = fn_8009BCE8(&p->mUnknown1036);
        pOtherBlock = (Block_80118B4C *)&pOther->mBlock1032;
        if (fn_800CA5CC(pOther, 8, 0) && fn_800B65A0(pOther->mIdBytes[2]) == 255) {
            fn_8011F1CC();
        }
        if (fn_8011F1CC() && lbl_803EB028->mUnknown84 <= 45) goto done;
        if (fn_801CFFD0(p->mMotion.mFacing, 0x400000) > 0x400000
            || pOther->mMotion.mPos.mY < fn_80177FE0().mY - lbl_803EB020) {
            close = 1;
        }
        if (lbl_803EB028->mUnknown84 <= 45 && !close) goto done;
        slow = lbl_803ECB08 * 0.2f;
        if (p->mMotion.mUnknown28 <= slow || pOther->mMotion.mUnknown28 <= slow) goto done;
        if (!fn_8011A994(p, pOther)) goto done;
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801CFFD0(pOther->mUnknown512.mUnknown4, angle) > 0x438E38
            && pOther->mUnknown512.mUnknown0 >= 0.4f
            && (p->mUnknown8 == 255 || p->mpState->mId != 96)) {
            goto done;
        }
        if (fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos) >= 12.25f) goto done;
        if (!fn_80124714(p, pOther, 0)) goto done;
        count = 0;
        roll = fn_80237260(0);
        fn_8011A2C4(p, pOther, *pPair, 1);
        if (pBlock->mUnknown20 != 1 || close) {
            if (roll < pBlock->mUnknown52) {
                if (roll < pBlock->mUnknown52 * 0.5f) {
                    moves[count++] = lbl_802DAC38[0];
                } else {
                    moves[count++] = lbl_802DAC38[1];
                }
            } else if (roll < pOtherBlock->mUnknown52) {
                int blocked = 0;
                Object_80039F5C *pCarrier = fn_80137B40();
                if (pCarrier) {
                    Vector_80039F5C toCarrier;
                    fn_802276B4(&toCarrier, &pCarrier->mMotion.mPos, &pOther->mMotion.mPos);
                    int heading = fn_801CFE40(toCarrier.mY, toCarrier.mX);
                    if (fn_80124714(pOther, fn_80137B40(), 0) && fn_802270D4(&toCarrier) < 6.0f) {
                        blocked = fn_801CFFD0(heading, pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0)) <= 0x555554;
                    }
                }
                if (!blocked) {
                    moves[count++] = lbl_802DAC38[2];
                }
            }
        }

        fn_800CE770(&query);
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        if (p->mpState->mId == 96) {
            query.mUnknown36 = 0x66666;
            query.mUnknown44 = 0.45f;
        } else {
            query.mUnknown36 = 0xE38E3;
            query.mUnknown44 = 0.4f;
        }
        for (unsigned char i = 0; i < count; i++) {
            query.mUnknown52 = moves[i];
            if (fn_800CE4A8(&query)) {
                result = 1;
                if (moves[i] == lbl_802DAC38[0] || moves[i] == lbl_802DAC38[2]) {
                    fn_8011E1BC(p, pOther, 0, 5);
                    fn_8011E33C(pOther, p, 5);
                    if (moves[i] == lbl_802DAC38[0]) {
                        fn_801187CC(p, pOther);
                    }
                } else {
                    fn_8011E1BC(p, pOther, 0, 6);
                    fn_8011E33C(pOther, p, 6);
                }
                fn_800CA5CC(p, 8, 1);
                if (fn_800B65A0(pOther->mIdBytes[2]) != 255 || !fn_8011F1CC()) {
                    fn_800CA5CC(pOther, 8, 1);
                }
                break;
            }
        }
    }
done:
    return result;
}

extern "C" void fn_80119020(void)
{
    Query_800CE770 query;
    Vector_80039F5C ball;

    if (fn_8011F32C() || fn_80177C38() || fn_801787A0()) return;

    unsigned char i = 0;
    fn_80137D58(fn_801374BC(), &ball);
    int team = fn_80178308();
    unsigned int count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        Block_80119020 *pBlock = (Block_80119020 *)&p->mBlock1032;
        if (fn_80137C48(p)) continue;
        if (p->mUnknown1032 != 4 && p->mUnknown1032 != 2 && p->mUnknown1032 != 3) continue;
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
        Block_80119020 *pOtherBlock = (Block_80119020 *)&pOther->mBlock1032;
        if (pBlock->mUnknown105 || !pOtherBlock->mUnknown102) {
            int odds = p->mRatings[2] + p->mRatings[0] + (int)p->mUnknown2904Float + p->mRatings[7];
            odds /= 4;
            odds += fn_802372EC(0, 75);
            int diff = pOther->mRatings[2] + pOther->mRatings[4] + pOther->mRatings[5] + (int)pOther->mUnknown2904Float;
            diff /= 4;
            diff += fn_802372EC(0, 75);
            diff -= odds;
            if (p->mUnknown1052 == 1) {
                switch (p->mUnknown2914) {
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 24:
                    if (pBlock->mUnknown105 || fn_8011E188() > 179) {
                        diff /= 4;
                    } else {
                        diff = 0;
                    }
                    break;
                }
            } else {
                int late = 0;
                if (!fn_801783AC(0) && fn_80177FE0().mY - ball.mY > 2.0f) {
                    late = 1;
                } else if (fn_8011E188() <= 59) {
                    late = 1;
                }
                if (late) diff = 0;
            }
            if ((pBlock->mUnknown0 == 4 || pBlock->mUnknown0 == 7) && pBlock->mUnknown95) {
                diff /= 2;
            }
            if (pBlock->mUnknown105 || (diff > 0 && (int)fn_802372EC(0, 100) < diff)) {
                pBlock->mUnknown104 = 1;
            }
            if (pBlock->mUnknown104) {
                diff += p->mRatings[0] - pOther->mRatings[0];
                if ((int)fn_802372EC(0, 100) < diff) pBlock->mUnknown101 = 0; else pBlock->mUnknown101 = 1;
            }
            pBlock->mUnknown105 = 0;
        }
        if (!pBlock->mUnknown104) continue;

        int go = 1;
        if (pBlock->mUnknown0 == 2 || pBlock->mUnknown0 == 3) {
            Point_8017886C delta;
            go = 0;
            fn_80227690(&delta, &ball, &p->mMotion.mPos);
            int angle = fn_801CFE40(delta.mY, delta.mX);
            fn_80227690(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
            if (fn_801CFFD0(angle, fn_801CFE40(delta.mY, delta.mX)) > 0x600000 || fn_802270A4(&delta) < 3.0f) {
                float dist;
                Object_80039F5C *pNear = fn_80124C28(p, &dist, 0x355555, 4.0f, 0.5f, p->mMotion.mFacing);
                if (pNear == pOther || !pNear) go = 1;
            }
        }
        if (!go) continue;
        if (!fn_8011A994(p, pOther)) continue;

        int done;
        fn_800CE770(&query);
        query.mUnknown36 = 0xE38E3;
        query.mUnknown44 = 0.4f;
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        if (!pBlock->mUnknown101) {
            query.mUnknown52 = 79;
            done = fn_800CE4A8(&query);
        } else {
            query.mUnknown52 = 25;
            done = fn_800CE4A8(&query);
        }
        if (done) {
            fn_8011E1BC(p, pOther, 0, 5);
            fn_8011E33C(pOther, p, 5);
        }
    }
}

extern "C" void fn_801194F0(void)
{
    Query_800CE770 query;
    int moves[4];
    Pair_8011BAE0 pair;

    unsigned char i = 0;
    int team = fn_80178308();
    fn_8011BAE0(&pair);
    unsigned int count = fn_80178D70(team);
    for (; i < count; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        fn_800CA5CC(p, 8, 0);
        Block_801194F0 *pBlock = (Block_801194F0 *)&p->mBlock1032;
        if (fn_80137C48(p)) continue;
        if (p->mUnknown1032 != 2 && p->mUnknown1032 != 3) continue;
        if (fn_80237260(0) >= 1.0f) continue;

        int covered = 0;
        Object_80039F5C *pOther = fn_8009BCE8(&p->mUnknown1036);
        if (fn_800A851C(fn_80178320(), pOther) && fn_800A8444(fn_80178320())) {
            covered = 1;
        }
        Block_801194F0 *pOtherBlock = (Block_801194F0 *)&pOther->mBlock1032;
        fn_800CA5CC(pOther, 8, 0);
        if (fn_8011F1CC() && lbl_803EB028->mUnknown84 <= 45) continue;
        if (covered) continue;
        float slow = lbl_803ECB08 * 0.14f;
        if (p->mMotion.mUnknown28 <= slow && pOther->mMotion.mUnknown28 <= slow) continue;
        if (!fn_8011A994(p, pOther) && !fn_80113BCC(pOther)) continue;

        Point_8017886C delta;
        fn_80227690(&delta, &p->mMotion.mPos, &pOther->mMotion.mPos);
        int angle = fn_801CFE40(delta.mY, delta.mX);
        if (fn_801CFFD0(pOther->mUnknown512.mUnknown4, angle) > 0x51C71B
            && pOther->mUnknown512.mUnknown0 >= 0.4f) {
            continue;
        }
        angle = (angle + 0x800000) & 0xFFFFFF;
        if (fn_801CFFD0(angle, p->mMotion.mFacing + fn_800C8BAC(p, 0)) > 0x555554) continue;
        if (fn_80227890(&p->mMotion.mPos, &pOther->mMotion.mPos) >= 12.25f) continue;
        if (!fn_80124714(p, pOther, 0)) continue;

        fn_8011A2C4(p, pOther, pair, 1);
        unsigned char num = 0;
        if (lbl_803EB028->mUnknown84 > 12) {
            int tryOther = 1;
            if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.2f
                && fn_801CFFD0(angle, p->mMotion.mFacing + fn_800C8BAC(p, 0)) <= 0x155554) {
                if (fn_80237260(0) < pBlock->mUnknown52) {
                    moves[num] = lbl_802DAC20[3];
                    num++;
                    tryOther = 0;
                }
            } else if (pOther->mMotion.mUnknown28 > lbl_803ECB08 * 0.2f && !fn_80113BCC(pOther)) {
                if (fn_80237260(0) < pBlock->mUnknown52) {
                    moves[num] = lbl_802DAC20[2];
                    num++;
                    tryOther = 0;
                }
            }
            if (tryOther && !fn_80113BCC(pOther)) {
                int blocked = 0;
                Object_80039F5C *pCarrier = fn_80137B40();
                if (pCarrier) {
                    Vector_80039F5C toCarrier;
                    fn_802276B4(&toCarrier, &pCarrier->mMotion.mPos, &pOther->mMotion.mPos);
                    int heading = fn_801CFE40(toCarrier.mY, toCarrier.mX);
                    if (fn_80124714(pOther, fn_80137B40(), 0) && fn_802270D4(&toCarrier) < 6.0f) {
                        blocked = fn_801CFFD0(heading, pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0)) <= 0x555554;
                    }
                }
                if (!blocked) {
                    if (pOther->mMotion.mUnknown28 > lbl_803ECB08 * 0.2f
                        && fn_801CFFD0(angle + 0x800000, pOther->mMotion.mFacing + fn_800C8BAC(pOther, 0)) <= 0x155554) {
                        if (fn_80237260(0) < pOtherBlock->mUnknown52) {
                            moves[num] = lbl_802DAC20[0];
                            num++;
                        }
                    } else if (p->mMotion.mUnknown28 > lbl_803ECB08 * 0.2f) {
                        if (fn_80237260(0) < pOtherBlock->mUnknown52) {
                            moves[num] = lbl_802DAC20[5];
                            num++;
                        }
                    }
                }
            }
        }
        if (!fn_80113BCC(pOther)) {
            if (pBlock->mUnknown95) {
                if (pBlock->mUnknown40 > 0.16f && pBlock->mUnknown20 != 1) {
                    moves[num] = lbl_802DAC20[4];
                    num++;
                }
            } else if (pOtherBlock->mUnknown40 > 0.16f) {
                moves[num] = lbl_802DAC20[1];
                num++;
            }
        }

        fn_800CE770(&query);
        query.mpUnknown0 = p;
        query.mpUnknown4 = pOther;
        query.mUnknown36 = 0xE38E3;
        query.mUnknown44 = 0.4f;
        for (unsigned char j = 0; j < num; j++) {
            query.mUnknown52 = moves[j];
            if (fn_800CE4A8(&query)) {
                if (moves[j] == lbl_802DAC20[3] || moves[j] == lbl_802DAC20[0]
                    || moves[j] == lbl_802DAC20[5] || moves[j] == lbl_802DAC20[2]) {
                    fn_8011E1BC(p, pOther, 0, 5);
                    fn_8011E33C(pOther, p, 5);
                    if (moves[j] == lbl_802DAC20[3] || moves[j] == lbl_802DAC20[2]) {
                        fn_801187CC(p, query.mpUnknown4);
                    }
                } else {
                    fn_8011E1BC(p, pOther, 0, 6);
                    fn_8011E33C(pOther, p, 6);
                }
                fn_800CA5CC(p, 8, 1);
                fn_800CA5CC(pOther, 8, 1);
                break;
            }
        }
    }
}
