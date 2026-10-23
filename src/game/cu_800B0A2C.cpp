#include "game/Object_80039F5C.h"
#include "game/Block_800B0CFC.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"

extern "C" {
int fn_80178308(void);
int fn_801486A0(void);

extern float lbl_803ECB08;
}

extern "C" int fn_800B0A2C(Object_80039F5C *p, int value)
{
    if (p == 0 || lbl_803EAB14->mUnknown2E4 == 0) {
        return 0;
    }

    int result = 1;
    int team = fn_80178308();
    unsigned short i = 0;
    unsigned int count = fn_80178D18(team);

    for (; i < count; i++) {
        Object_80039F5C *pPlayer = fn_80039F5C(team, i);
        if (pPlayer->mpState->mId != 61 && pPlayer->mMotion.mUnknown28 > lbl_803ECB08 * 0.14f) {
            result = 0;
            break;
        }
    }
    if (result) {
        if (p->mpState->mId == 61) {
            if (lbl_803EAB14->mUnknown2E0 == value) {
                result = 0;
            } else {
                lbl_803EAB14->mUnknown2E0 = 2;
            }
            if (fn_801486A0() == 2) {
                result = 0;
            }
        } else if (lbl_803EAB14->mUnknown2E0 != value && lbl_803EAB14->mUnknown2E0 == 2) {
            if (p->mMotion.mPos.mX < fn_80177FE0().mX + -4.0f) {
                lbl_803EAB14->mUnknown2E0 = 1;
            } else if (p->mMotion.mPos.mX > fn_80177FE0().mX + 4.0f) {
                lbl_803EAB14->mUnknown2E0 = 0;
            }
        }
    }
    return result;
}
