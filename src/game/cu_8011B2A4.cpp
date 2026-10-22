#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/cu_80136B1C.h"
#include "game/fn_80177FE0.h"
#include <math.h>

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
int fn_8011F1CC(void);
int fn_8011F2F8(void);
int fn_801783AC(int bit);
int fn_801CFFD0(int a, int b);
}

extern "C" int fn_8011B2A4(Entry_8011AFCC *pEntry)
{
    Object_800B26B0 *pMotion;
    Point_8017886C origin;
    Vector_80039F5C ball;

    if ((pEntry->mpUnknown60->mFlags & 0x800)
        || (pEntry->mpUnknown60->mUnknown1032 >= 4 && pEntry->mpUnknown60->mUnknown1032 <= 6)) {
        return 0;
    }
    pMotion = &pEntry->mpUnknown60->mMotion;
    origin = fn_80177FE0();
    if (fn_8011F1CC() && !fn_801783AC(0) && !fn_801783AC(13)) {
        State_80039F5C *pState;
        unsigned int id;

        if (pEntry->mUnknown76 == 1) {
            return 0;
        }
        pState = pEntry->mpUnknown60->mpState;
        id = pState->mId;
        if (id == 51) {
            id = pState[1].mId;
        }
        switch (id) {
        case 22:
        case 40:
        case 92:
            if (pEntry->mpUnknown60->mUnknown8 != 0xFF && (pEntry->mpUnknown60->mFlags & 0x4000)) {
                if (lbl_803EB028->mUnknown84 < 20) {
                    if (pMotion->mPos.mY <= origin.mY + 2.5f) {
                        break;
                    }
                } else if (pMotion->mPos.mY <= origin.mY + 3.5f) {
                    if (pMotion->mPos.mY <= origin.mY) {
                        break;
                    }
                    if (fn_801CFFD0(pEntry->mpUnknown60->mMotion.mUnknown32, 0xC00000) <= 0x200000
                        && pEntry->mpUnknown60->mMotion.mUnknown28 >= lbl_803ECB08 * 0.4f) {
                        break;
                    }
                }
            } else if (lbl_803EB028->mUnknown84 < 20) {
                if (pMotion->mPos.mY <= origin.mY + 2.5f) {
                    break;
                }
            } else {
                if (pMotion->mPos.mY <= origin.mY) {
                    break;
                }
                if (fn_8011F2F8() && fabsf(pMotion->mPos.mX - origin.mX) >= 5.0f
                    && pMotion->mPos.mY <= origin.mY + 5.0f) {
                    break;
                }
            }
            return 0;
        case 89:
            return 0;
        }
    }
    fn_80138064(fn_801374BC(), &ball);
    return pMotion->mPos.mY - ball.mY >= -15.0f;
}
