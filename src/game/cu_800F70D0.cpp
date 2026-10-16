#include <math.h>
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Message_800F01CC.h"
#include "game/State_803EB098.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"

extern "C" {
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_800F6AD8(float *p);
}

extern "C" void fn_800F70D0(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pTarget, Point_8017886C *pOut) {
    if (p && pOther && pOut) {
        Point_8017886C origin;
        Point_8017886C delta;

        origin = fn_80177FE0();
        fn_80227690(&delta, pTarget, &p->mMotion.mPos);
        if (!(p->mpState->mUnknown2 & 2)) {
            if (pTarget->mY < origin.mY) {
                pOut->mY = pTarget->mY - p->mMotion.mPos.mY + 2.0f;
            } else if (p->mMotion.mPos.mY > pTarget->mY) {
                float dy = pTarget->mY - p->mMotion.mPos.mY;

                pOut->mY = fabsf(dy) > 1.0f ? dy + 1.0f : 0.0f;
            } else {
                pOut->mY = pTarget->mY - p->mMotion.mPos.mY - 1.0f;
            }
        } else if (p->mMotion.mPos.mY < pTarget->mY) {
            float dy = pTarget->mY - p->mMotion.mPos.mY;

            pOut->mY = fabsf(dy) > 1.0f ? dy - 1.0f : 0.0f;
        } else {
            pOut->mY = pTarget->mY - p->mMotion.mPos.mY + 1.0f;
        }
        fn_800F6AD8(&pOut->mX);
    }
}
