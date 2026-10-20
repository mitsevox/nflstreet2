#include "game/Object_80039F5C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_802270D4.h"
#include "game/fn_802372EC.h"
#include "game/fn_80178D18.h"
#include <math.h>

struct Pair_8011BAE0 {
    float mUnknown0;
    float mUnknown4;
};

struct Entry_8011AFCC {
    int mUnknown0;
    char mUnknown4[56];
    Object_80039F5C *mpUnknown60;
    int mUnknown64;
    float mUnknown68;
    float mUnknown72;
    unsigned char mUnknown76;
    char mUnknown77[3];
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
extern float lbl_803ECB08;
int fn_80178308(void);
int fn_80178320(void);
int fn_8011F1CC(void);
int fn_800A2178(void);
int fn_800ACFFC(int team, int value);
int fn_80113BCC(Object_80039F5C *p);
int fn_801CFE40(float y, float x);
int fn_801CFFD0(int a, int b);
void fn_80227690(void *pOut, void *pA, void *pB);
int fn_8011B2A4(Entry_8011AFCC *pEntry);
void fn_8011AFCC(Entry_8011AFCC *pEntries);
void fn_8011B138(Entry_8011AFCC *pEntries);
}

extern "C" void fn_8011B4F8(Entry_8011AFCC *pEntry)
{
    float score;

    if (fn_8011B2A4(pEntry) == 1) {
        Object_800B26B0 *pMotion = &pEntry->mpUnknown60->mMotion;
        Object_80039F5C *p;
        int near;

        if (pEntry->mUnknown72 < 80.0f) {
            score = 80.0f - pEntry->mUnknown72;
        } else {
            score = 5.0f;
        }
        if (pMotion->mUnknown28 > lbl_803ECB08 * 0.5f && fn_801CFFD0(pEntry->mUnknown64, pMotion->mUnknown32) > 0x4E38E3) {
            pEntry->mUnknown76 = 1;
            score *= 0.8f;
        }
        switch (pEntry->mpUnknown60->mQueue[0].mId) {
        case 10:
        case 11:
            score *= 0.33333334f;
            break;
        }
        if (fn_8011F1CC()) {
            score += fabsf(pMotion->mPos.mX - fn_80177FE0().mX) * 0.25f;
        } else {
            int angle = fn_801CFFD0(pEntry->mUnknown64, pMotion->mFacing);

            if (angle > 0x600000) {
                score *= 0.083333336f;
            } else if (angle > 0x400000) {
                score *= 0.16666667f;
            }
        }
        p = pEntry->mpUnknown60;
        near = 0;
        if (p->mUnknown8 != 0xFF) {
            near = fabsf(p->mMotion.mPos.mY - fn_80177FE0().mY) <= 5.5f
                && fabsf(pEntry->mpUnknown60->mMotion.mPos.mX - fn_80177FE0().mX) <= 2.0f;
        }
        if (near) {
            score *= 10.0f;
        }
    } else {
        score = 5.0f;
    }
    pEntry->mUnknown68 = score;
}

extern "C" void fn_8011B6E8(Entry_8011AFCC *pEntries, Pair_8011BAE0 target)
{
    unsigned char count = 0;
    unsigned char i = 0;
    int team = fn_80178320();
    unsigned int n = fn_80178D70(team);

    for (; i < n; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        int skip = 0;

        switch (p->mQueue[0].mId) {
        case 16:
        case 32:
        case 89:
            skip = 1;
            break;
        case 17:
            if (!fn_80113BCC(p)) {
                skip = 1;
            }
            break;
        }
        if (!skip) {
            Pair_8011BAE0 delta;

            pEntries[count].mpUnknown60 = p;
            pEntries[count].mUnknown0 = 0;
            fn_80227690(&delta, &target, &p->mMotion.mPos);
            pEntries[count].mUnknown72 = fn_802270A4(&delta);
            pEntries[count].mUnknown64 = fn_801CFE40(delta.mUnknown4, delta.mUnknown0);
            pEntries[count].mUnknown76 = 0;
            fn_8011B4F8(&pEntries[count]);
            count++;
        }
    }
    pEntries[count].mpUnknown60 = 0;
    pEntries[count].mUnknown0 = 0;
    pEntries[count].mUnknown68 = 0.0f;
    if (lbl_803EB028->mUnknown88) {
        fn_8011B138(pEntries);
    }
}

extern "C" void fn_8011B83C(Entry_8011AFCC *pEntries, Pair_8011BAE0 target)
{
    unsigned char count = 0;
    unsigned char i = 0;
    int team = fn_80178308();
    unsigned int n = fn_80178D70(team);

    for (; i < n; i++) {
        Object_80039F5C *p = fn_80039F5C(team, i);
        int mode;

        switch (p->mUnknown1052) {
        case 1:
        case 2:
            break;
        default:
            continue;
        }
        mode = p->mUnknown1032;
        if (mode == 5 || mode == 6 || mode == 0) {
            continue;
        }
        if (mode == 4 || mode == 7) {
            short rating;
            int chance;

            if (!(fn_8011F1CC() && lbl_803EB028->mUnknown84 != 0)
                && (fn_8011F1CC() || lbl_803EB028->mUnknown84 <= 60)) {
                continue;
            }
            rating = p->mRatings[7];
            if (fn_800A2178() == 7 || fn_800A2178() == 8) {
                rating *= 3;
            }
            chance = fn_800ACFFC(p->mIdBytes[2], rating);
            if (chance <= 152 && fn_802372EC(0, 100) > chance * 0.6535948f) {
                continue;
            }
        }
        {
            Pair_8011BAE0 delta;

            pEntries[count].mpUnknown60 = p;
            pEntries[count].mUnknown0 = 0;
            fn_80227690(&delta, &target, &p->mMotion.mPos);
            pEntries[count].mUnknown72 = fn_802270A4(&delta);
            pEntries[count].mUnknown64 = fn_801CFE40(delta.mUnknown4, delta.mUnknown0);
            pEntries[count].mUnknown68 = pEntries[count].mUnknown72;
            switch (p->mUnknown2914) {
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                pEntries[count].mUnknown68 *= 0.5f;
                if (p->mRatings[7] > 152) {
                    pEntries[count].mUnknown68 *= 0.01f;
                }
                break;
            }
            if (p->mUnknown1052 == 1) {
                pEntries[count].mUnknown76 = 0;
            } else {
                pEntries[count].mUnknown76 = 1;
            }
            count++;
        }
    }
    pEntries[count].mpUnknown60 = 0;
    pEntries[count].mUnknown0 = 0;
    pEntries[count].mUnknown68 = 0.0f;
    fn_8011AFCC(pEntries);
}

