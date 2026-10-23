#include <math.h>
#include "game/Block_803EB028.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/fn_80177FE0.h"

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

struct Score_8011D0BC {
    float mValue;
    unsigned char mValid;
};

/* 80-byte entry of the two lists fn_8011D9B8 builds; terminated by a null
   player. +4 caches one score per opposing player index, with its valid byte. */
struct Entry_8011AFCC {
    Entry_8011AFCC *mpUnknown0;
    Score_8011D0BC mUnknown4[7];
    Object_80039F5C *mpUnknown60;
    int mUnknown64;
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    char mUnknown77[3];
};

extern "C" {
extern Block_803EB028 *lbl_803EB028;
extern float lbl_803EB014;
extern float lbl_803EB018;
extern float lbl_803EB01C;
extern float lbl_803EB094;
extern float lbl_803ECB08;
void fn_80227690(void *pOut, void *pA, void *pB);
float fn_802270A4(void *p);
int fn_801CFFD0(int a, int b);
float fn_801CFB94(int angle);
int fn_801783AC(int bit);
Object_80039F5C *fn_80137B40(void);
int fn_800C8BAC(Object_80039F5C *p, int a);
int fn_8011F1A4(void);
int fn_8011F1CC(void);
int fn_8011F2F8(void);
unsigned char fn_8011F4C8(void);
int fn_8011E484(Object_80039F5C *p, Object_80039F5C *pOther);
void fn_8011D8B4(Entry_8011AFCC *pEntries);
void fn_8011E1BC(Object_80039F5C *p, Object_80039F5C *pA, Object_80039F5C *pB, int value);
void fn_8011E33C(Object_80039F5C *p, Object_80039F5C *pOther, int value);
void fn_8011E938(Object_80039F5C *p);
int fn_80124714(Object_80039F5C *p, Object_80039F5C *pOther, Object_80039F5C **pOut);

float fn_8011BCDC(Entry_8011AFCC *pEntry, Entry_8011AFCC *pTarget, Pair_8011BAE0 from, Point_8017886C ball,
                             int a, int b, float weight)
{
    Object_80039F5C *p = pEntry->mpUnknown60;
    Object_80039F5C *pOther = pTarget->mpUnknown60;
    Object_800B26B0 *pMotion = &p->mMotion;
    Object_800B26B0 *pOtherMotion = &pOther->mMotion;
    Point_8017886C delta;
    float across;
    float length;

    fn_80227690(&delta, pMotion, pOtherMotion);
    across = fabsf(delta.mX);
    length = fn_802270A4(&delta);
    delta.Heading();
    if (pTarget->mpUnknown60->mFlags & 0x800) {
        weight *= 0.5f;
    }
    if (!a) {
        switch (pTarget->mpUnknown60->mUnknown2914) {
        case 10:
        case 11:
        case 12:
            if (lbl_803EB028->mUnknown84 < 180
                && ((pMotion->mPos.mX < ball.mX && pOtherMotion->mPos.mX > ball.mX)
                    || (pMotion->mPos.mX > ball.mX && pOtherMotion->mPos.mX < ball.mX))) {
                if (across > lbl_803EB014 * 0.5f) {
                    weight *= 0.5f;
                }
            } else if (across > lbl_803EB014) {
                weight *= 0.5f;
            }
            break;
        default: {
            float limit;

            if ((pOtherMotion->mUnknown32 & 0xFFFFFF) > 0x800000) {
                limit = ball.mY + 2.0f;
            } else {
                limit = ball.mY;
            }

            if (pOtherMotion->mPos.mY > limit) {
                switch (pTarget->mpUnknown60->mpState->mId) {
                case 22:
                case 40:
                case 92:
                    if (!b) {
                        if (pOtherMotion->mPos.mY > ball.mY + 5.0f) {
                            return 0.0f;
                        }
                        if (pOtherMotion->mPos.mY > ball.mY + 3.0f && (length > 5.0f || !fn_8011F2F8())) {
                            weight *= 0.5f;
                        }
                    }
                case 2:
                case 30:
                case 51:
                    if (across > lbl_803EB018) {
                        if (across < lbl_803EB018 * 1.5f && b) {
                            weight *= 0.5f;
                        } else {
                            return 0.0f;
                        }
                    }
                    break;
                case 85:
                    if (pOtherMotion->mPos.mY > ball.mY + 2.0f) {
                        return 0.0f;
                    }
                    if (pTarget->mpUnknown60->mUnknown8 == 0xFF) {
                        return 0.0f;
                    }
                    break;
                case 24:
                    break;
                default:
                    return 0.0f;
                }
            } else if (across > 8.0f) {
                return 0.0f;
            }
            if (fn_80137B40() != 0 && !(fn_80137B40()->mFlags & 0x8000)) {
                int close = fabsf(pTarget->mpUnknown60->mMotion.mPos.mY - fn_80177FE0().mY) <= 1.5f
                            && fabsf(pTarget->mpUnknown60->mMotion.mPos.mX - fn_80177FE0().mX) <= 3.0f;

                if (close) {
                    if (pOtherMotion->mUnknown28 > lbl_803ECB08 * 0.5f) {
                        if (fn_801CFFD0(pTarget->mUnknown64, pOtherMotion->mUnknown32) < 0x2AAAAA) {
                            weight *= 1.5f;
                        }
                    } else {
                        switch (pTarget->mpUnknown60->mpState->mId) {
                        case 2:
                        case 30:
                        case 51:
                            weight *= 1.5f;
                            break;
                        }
                    }
                }
            }
            break;
        }
        }
    }
    if (pEntry->mpUnknown60->mUnknown1048 != pTarget->mpUnknown60->mId) {
        switch (pEntry->mpUnknown60->mUnknown2914) {
        case 6:
        case 8:
            if (lbl_803EB028->mUnknown84 <= 30 || b) {
                break;
            }
            goto deep;
        case 4:
        case 5:
        case 9:
            if (lbl_803EB028->mUnknown84 < 15 && !b) {
                if ((pOtherMotion->mPos.mX > ball.mX && pMotion->mPos.mX < ball.mX)
                    || (pOtherMotion->mPos.mX < ball.mX && pMotion->mPos.mX > ball.mX)) {
                    weight *= 0.75f;
                }
                if (length > 2.0f) {
                    switch (pTarget->mpUnknown60->mUnknown2914) {
                    case 10:
                    case 11:
                    case 12:
                        if (fabsf(pMotion->mPos.mX - from.mUnknown0) > fabsf(pOtherMotion->mPos.mX - from.mUnknown0)) {
                            weight *= 0.95f;
                        }
                        break;
                    default:
                        weight *= 0.9f;
                        break;
                    }
                }
            }
            break;
        case 7:
        case 24:
            if (fabsf(from.mUnknown0 - ball.mX) < lbl_803EB01C && lbl_803EB028->mUnknown84 < 180) {
                switch (pTarget->mpUnknown60->mUnknown2914) {
                case 10:
                case 11:
                case 12:
                    if (across > lbl_803EB01C) {
                        return 0.0f;
                    }
                    if (lbl_803EB028->mUnknown89 && lbl_803EB028->mUnknown84 < 90
                        && pTarget->mpUnknown60->mId != pEntry->mpUnknown60->mUnknown560.mUnknown40) {
                        weight *= 0.75f;
                    }
                    break;
                case 14:
                    if (across > lbl_803EB01C) {
                        return 0.0f;
                    }
                    if (across > 2.5f && lbl_803EB028->mUnknown84 < 60) {
                        weight *= 0.5f;
                    }
                    break;
                default:
                    if (pTarget->mpUnknown60->mFlags & 0x4000) {
                        if (across > lbl_803EB01C) {
                            return 0.0f;
                        }
                    } else if (across > 2.5f) {
                        return 0.0f;
                    }
                    if (lbl_803EB028->mUnknown84 < 60 && across < 2.5f) {
                        weight *= 1.25f;
                    }
                    if (pOtherMotion->mPos.mY < fn_80177FE0().mY + 15.0f) {
                        weight *= 1.0f - (pOtherMotion->mPos.mY - fn_80177FE0().mY) * (1.0f / 15.0f);
                    } else {
                        return 0.0f;
                    }
                    break;
                }
            }
            break;
        case 1:
        case 2:
            if (length > 4.0f && fn_8011F1CC()) {
                Object_80039F5C *pBlocker;

                if (fn_80124714(pEntry->mpUnknown60, pTarget->mpUnknown60, &pBlocker) == 0) {
                    if (pBlocker->mIdBytes[2] == pEntry->mpUnknown60->mIdBytes[2] && pBlocker->mUnknown1032 == 1
                        && !(pBlocker->mFlags & 0x800)) {
                        Point_8017886C gap;

                        fn_80227690(&gap, pOtherMotion, &pBlocker->mMotion.mPos);
                        if (fn_802270A4(&gap) < 2.0f && fn_801CFFD0(gap.Heading(), pBlocker->mMotion.mFacing) < 0x400000) {
                            weight *= 0.5f;
                        }
                    }
                } else if (fabsf(pOtherMotion->mPos.mX) > fabsf(pMotion->mPos.mX)) {
                    weight *= 1.5f;
                }
            }
            break;
        default:
        deep:
            if (pOtherMotion->mPos.mY > ball.mY + 2.0f) {
                weight *= 0.75f;
            }
            break;
        }
    }
    return weight;
}

float fn_8011C4E0(Entry_8011AFCC *pEntry, Entry_8011AFCC *pTarget, Pair_8011BAE0 from, Point_8017886C ball,
                             float weight, int a)
{
    Object_80039F5C *pOther = pTarget->mpUnknown60;
    Object_80039F5C *p;
    Object_800B26B0 *pMotion;
    Object_800B26B0 *pOtherMotion;
    Point_8017886C delta;
    float across;
    float length;
    int angle;
    int deep;
    int turn;

    if (pOther->mFlags & 0x800) {
        return 0.0f;
    }
    p = pEntry->mpUnknown60;
    pMotion = &p->mMotion;
    pOtherMotion = &pOther->mMotion;
    deep = 0;
    fn_80227690(&delta, pMotion, pOtherMotion);
    across = fabsf(delta.mX);
    length = fn_802270A4(&delta);
    angle = delta.Heading();
    if (fn_8011F1A4()) {
        deep = fn_8011F4C8() > 3;
    }
    if (!a) {
        if (lbl_803EB028->mUnknown84 <= 64) {
            if (!deep && lbl_803EB028->mUnknown84 <= 1 && pOtherMotion->mPos.mY - ball.mY > 2.0f) {
                return 0.0f;
            }
            switch (pEntry->mpUnknown60->mUnknown2914) {
            case 5:
            case 9:
                if (pEntry->mpUnknown60->mUnknown2914 == 5 && deep && fn_8011F1A4() && (fn_8011F4C8() & 1)) {
                    if (pOtherMotion->mPos.mY - ball.mY > 2.0f && pMotion->mPos.mX > pOtherMotion->mPos.mX
                        && across > 2.0f) {
                        return 0.0f;
                    }
                } else if (pEntry->mpUnknown60->mUnknown2914 == 9 && deep && (!fn_8011F1A4() || !(fn_8011F4C8() & 1))) {
                    if (pOtherMotion->mPos.mY - ball.mY > 2.0f && pMotion->mPos.mX < pOtherMotion->mPos.mX
                        && across > 2.0f) {
                        return 0.0f;
                    }
                }
            case 6:
            case 7:
            case 8:
                if (pTarget->mpUnknown60->mId == pEntry->mpUnknown60->mUnknown560.mUnknown40) {
                    weight *= 1.1f;
                } else if (across > 0.85f) {
                    weight *= 0.95f;
                }
            case 4:
            case 24:
                if (length > 5.0f) {
                    return 0.0f;
                }
                if (pMotion->mPos.mY < ball.mY + 1.0f) {
                    if (across > 2.0f) {
                        weight -= length;
                        if (across > 3.5f) {
                            weight *= 0.5f;
                        }
                    } else {
                        if (length > 6.0f) {
                            weight *= 0.5f;
                        } else {
                            weight += 8.0f - length;
                        }
                        if (lbl_803EB028->mUnknown84 <= 3 && pEntry->mUnknown72 < 1.75f
                            && pEntry->mpUnknown60->mUnknown2914 != 7) {
                            weight *= 1.025f;
                        }
                    }
                }
                break;
            case 3:
                if (across > 4.0f) {
                    return 0.0f;
                }
                if (across > 0.5f) {
                    weight -= 16.0f;
                }
                break;
            case 1:
            case 2:
                if (deep && pEntry->mpUnknown60->mUnknown2914 == 2 && pOtherMotion->mPos.mY < ball.mY) {
                    if ((fn_8011F1A4() && (fn_8011F4C8() & 1) && pMotion->mPos.mX > pOtherMotion->mPos.mX)
                        || ((!fn_8011F1A4() || !(fn_8011F4C8() & 1)) && pMotion->mPos.mX < pOtherMotion->mPos.mX)) {
                        weight *= 1.1f;
                    }
                }
                break;
            default:
                weight -= 16.0f;
                break;
            }
        } else if (deep && pEntry->mpUnknown60->mUnknown2914 == 2 && pMotion->mPos.mY < ball.mY - 1.0f
                   && pOtherMotion->mPos.mY < ball.mY) {
            if (((fn_8011F1A4() && (fn_8011F4C8() & 1) && p->mMotion.mPos.mX > pOther->mMotion.mPos.mX)
                 || (fn_8011F1A4() && (fn_8011F4C8() & 1) == 0 && pMotion->mPos.mX < pOtherMotion->mPos.mX))
                && fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1036) == 0 && length < 6.0f && length > 2.25f
                && fn_80124714(pEntry->mpUnknown60, pTarget->mpUnknown60, 0)) {
                weight *= 1.2f;
            }
        }
    } else if (pMotion->mPos.mY > from.mUnknown4) {
        if (length > pEntry->mUnknown72 * 2.5f) {
            weight *= 0.75f;
        }
        if (pOtherMotion->mPos.mY < from.mUnknown4) {
            weight *= 0.5f;
        }
    } else if (length > pEntry->mUnknown72) {
        return 0.0f;
    }
    if (lbl_803EB028->mUnknown84 != 0 && pTarget->mpUnknown60->mpState->mId != 51) {
        if (fn_801CFFD0(pMotion->mFacing + fn_800C8BAC(pEntry->mpUnknown60, 0), (angle + 0x800000) & 0xFFFFFF) > 0x555555) {
            if (pMotion->mPos.mY < from.mUnknown4 || (pMotion->mPos.mY < ball.mY && !a)) {
                return 0.0f;
            }
        }
        if (length < 25.0f) {
            turn = fn_801CFFD0(pMotion->mFacing, (angle - 0x800000) & 0xFFFFFF);

            if (a || pMotion->mPos.mY > ball.mY || (turn > 0x2E38E3 && lbl_803EB028->mUnknown84 > 30)) {
                turn = fn_801CFFD0(pTarget->mUnknown64, pEntry->mUnknown64);
                weight *= fn_801CFB94(turn / 4);
                turn = fn_801CFFD0(pEntry->mUnknown64, angle);
                weight *= fn_801CFB94(turn / 3);
            }
            weight *= fn_801CFB94(fn_801CFFD0(pMotion->mFacing + fn_800C8BAC(pEntry->mpUnknown60, 0), (angle - 0x800000) & 0xFFFFFF) / 4);
        }
    }
    if (pEntry->mpUnknown60->mUnknown1139 == 1) {
        weight *= 0.75f;
    }
    return weight;
}

float fn_8011CC10(Entry_8011AFCC *pEntry, Entry_8011AFCC *pOther, Pair_8011BAE0 pair, Point_8017886C ball, int bit,
                  int a, int c, int b)
{
    Vector_80039F5C *pPos = &pEntry->mpUnknown60->mMotion.mPos;
    Vector_80039F5C *pOtherPos = &pOther->mpUnknown60->mMotion.mPos;
    Point_8017886C delta;
    float distance;
    float score;
    int angle;

    if (!bit && (pEntry->mpUnknown60->mBlock1032.mUnknown100 & 1)
        && fabsf(pOther->mpUnknown60->mMotion.mPos.mX - ball.mX) < 4.0f && pOtherPos->mY < ball.mY + 3.0f) {
        return 0.0f;
    }
    score = 0.0f;
    if (!bit && pEntry->mpUnknown60->mUnknown8 == 255 && pEntry->mUnknown76 == 1 && pOther->mUnknown76 == 1
        && pPos->mY > pOtherPos->mY + 1.0f) {
        return score;
    }
    fn_80227690(&delta, pPos, pOtherPos);
    distance = fn_802270A4(&delta);
    score = distance;
    angle = fn_801CFE40(delta.mY, delta.mX);
    if (score > 88.0f) {
        score = 88.0f;
    }
    score = 88.0f - score;
    if (distance < 2.1f && fn_8011E484(pEntry->mpUnknown60, pOther->mpUnknown60)) {
        score *= 1.2f;
    }
    switch (pEntry->mpUnknown60->mUnknown1052) {
    case 1:
        score = fn_8011BCDC(pEntry, pOther, pair, ball, bit, c, score);
        break;
    case 2:
        score = fn_8011C4E0(pEntry, pOther, pair, ball, score, bit);
        break;
    }
    if (score == 0.0f) {
        return 0.0f;
    }
    if (bit && fn_801CFFD0(pEntry->mUnknown64, (angle - 0x800000) & 0xFFFFFF) <= 0x38E38D && pPos->mY < pOtherPos->mY) {
        score *= 0.5f;
    }
    if (a && pEntry->mpUnknown60->mUnknown8 == 255 && pPos->mY > pOtherPos->mY) {
        return 0.0f;
    }
    if ((pEntry->mpUnknown60->mUnknown1032 == 7 && fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1040) == pOther->mpUnknown60)
        || fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1036) == pOther->mpUnknown60) {
        if ((a && distance < 4.5f && fn_801CFFD0(angle, ((Object_800B26B0 *)pOtherPos)->mFacing) <= 0x3FFFFF)
            || (b && pOtherPos->mY < ball.mY + 2.0f)) {
            score *= lbl_803EB094;
        }
        if (!c && distance < 6.0f && distance > 2.25f) {
            if (fn_80124714(pEntry->mpUnknown60, pOther->mpUnknown60, 0)) {
                if (b || fn_801CFFD0(angle, ((Object_800B26B0 *)pOtherPos)->mFacing) <= 0x3FFFFF) {
                    score *= 1.1f;
                }
            } else if (bit || (a && pPos->mY > ball.mY)) {
                score *= 0.9f;
            }
        }
    }
    if (pEntry->mpUnknown60->mUnknown1032 == 3) {
        if (pOther->mpUnknown60 == fn_8009BCE8(&pEntry->mpUnknown60->mUnknown1036)) {
            score *= 1.1f;
            if (pOther->mpUnknown60->mUnknown8 != 255) {
                score *= 2.0f;
            }
        } else {
            score *= 0.85f;
        }
    }
    if (pEntry->mpUnknown60->mUnknown8 != 255 && fn_801CFFD0(angle, ((Object_800B26B0 *)pPos)->mUnknown32) > 0x6AAAAB) {
        score *= 20.0f;
    }
    return score;
}

void fn_8011D0BC(Entry_8011AFCC *pA, Entry_8011AFCC *pB, Pair_8011BAE0 pair)
{
    int bit = fn_801783AC(0);
    Point_8017886C ball = fn_80177FE0();
    int a = fn_8011F1A4();
    int b = fn_8011F1CC();
    int changed;

    if (pB->mpUnknown60 == 0 || pA->mpUnknown60 == 0) {
        return;
    }
    do {
        Entry_8011AFCC *pEntry;
        Entry_8011AFCC *pOther;
        Entry_8011AFCC *pScan;
        Entry_8011AFCC *pBest;

        for (pEntry = pA; pEntry->mpUnknown60 != 0; pEntry++) {
            float best = 1.0f;

            pBest = 0;

            for (pOther = pB; pOther->mpUnknown60 != 0; pOther++) {
                if (pOther->mUnknown68 > 5.0f) {
                    int index = pOther->mpUnknown60->mIdBytes[1];
                    float value;

                    if (pEntry->mUnknown4[index].mValid) {
                        value = pEntry->mUnknown4[index].mValue;
                    } else {
                        value = fn_8011CC10(pEntry, pOther, pair, ball, bit, a, 0, b);
                        pEntry->mUnknown4[index].mValue = value;
                        pEntry->mUnknown4[index].mValid = 1;
                    }
                    if (value > best) {
                        best = value;
                        pBest = pOther;
                    }
                }
            }
            pEntry->mpUnknown0 = pBest;
            pEntry->mUnknown68 = best;
        }
        changed = 0;
        pEntry = pA;
        while (pEntry->mpUnknown60 != 0) {
            if (pEntry->mpUnknown0 != 0) {
                for (pBest = pScan = pEntry; pScan->mpUnknown60 != 0; pScan++) {
                    if (pScan[1].mpUnknown0 == pBest->mpUnknown0) {
                        changed = 1;
                        if (pScan[1].mUnknown68 > pBest->mUnknown68) {
                            pBest->mpUnknown0 = 0;
                            pBest->mUnknown68 = 0.0f;
                            pBest = &pScan[1];
                        } else {
                            pScan[1].mpUnknown0 = 0;
                            pScan[1].mUnknown68 = 0.0f;
                        }
                    }
                }
                if (pBest->mpUnknown60 != 0 && pBest->mpUnknown0 != 0) {
                    Object_80039F5C *pBlocker = 0;
                    Object_80039F5C *pMarked;

                    if (!fn_80124714(pBest->mpUnknown60, pBest->mpUnknown0->mpUnknown60, &pBlocker)) {
                        Point_8017886C delta;

                        fn_80227690(&delta, &pBest->mpUnknown60->mMotion.mPos, &pBlocker->mMotion.mPos);
                        if (fn_802270A4(&delta) < 1.5f) {
                            for (pOther = pB; pOther->mpUnknown60 != 0; pOther++) {
                                if (pOther->mpUnknown60 == pBlocker) {
                                    if (pOther->mUnknown68 > 5.0f) {
                                        pBest->mpUnknown0 = pOther;
                                        changed = 1;
                                        for (pScan = pEntry; pScan->mpUnknown60 != 0; pScan++) {
                                            if (pScan != pBest && pScan->mpUnknown0 == pOther) {
                                                pScan->mpUnknown0 = 0;
                                                pScan->mUnknown68 = 0.0f;
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    pMarked = fn_8009BCE8(&pBest->mpUnknown0->mpUnknown60->mUnknown1036);
                    if (pMarked != pBest->mpUnknown60) {
                        if (pMarked) {
                            if (pMarked->mUnknown1040 == pBest->mpUnknown0->mpUnknown60->mId) {
                                Object_80039F5C *pPartner = fn_8009BCE8(&pMarked->mUnknown1036);

                                fn_8011E1BC(pMarked, pPartner, 0, 4);
                                fn_8011E33C(pPartner, pMarked, 4);
                            } else {
                                fn_8011E1BC(pMarked, 0, 0, 1);
                            }
                        }
                        if (pBest->mpUnknown60->mUnknown1032 == 4 || pBest->mpUnknown60->mUnknown1032 == 7) {
                            Object_80039F5C *pPartner = fn_8009BCE8(&pBest->mpUnknown60->mUnknown1036);
                            short saved = pBest->mpUnknown60->mBlock1032.mUnknown102;

                            fn_8011E1BC(pBest->mpUnknown60, pPartner, pBest->mpUnknown0->mpUnknown60, 7);
                            pBest->mpUnknown60->mBlock1032.mUnknown102 = saved;
                            fn_8011E33C(pPartner, pBest->mpUnknown60, 4);
                            fn_8011E33C(pBest->mpUnknown0->mpUnknown60, pBest->mpUnknown60, 8);
                        } else {
                            if (pBest->mpUnknown0->mpUnknown60->mId == lbl_803EB028->mUnknown0) {
                                fn_8011E1BC(pBest->mpUnknown60, pBest->mpUnknown0->mpUnknown60, 0, 3);
                                fn_8011E938(0);
                            } else {
                                fn_8011E1BC(pBest->mpUnknown60, pBest->mpUnknown0->mpUnknown60, 0, 2);
                            }
                            fn_8011E33C(pBest->mpUnknown0->mpUnknown60, pBest->mpUnknown60, 8);
                        }
                    }
                    pBest->mpUnknown0->mUnknown68 = 0.0f;
                    fn_8011D8B4(pBest);
                }
                pEntry = pA;
            } else {
                pEntry++;
            }
        }
    } while (changed);
}

}
