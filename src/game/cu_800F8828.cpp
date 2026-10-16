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

/* View of the block at player +336 used by fn_800F846C, fn_800F8828,
   fn_800F8A88 and fn_800FA0DC. */
struct Block_800F8A88 {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    int mUnknown16;
    unsigned char mUnknown20;
    unsigned char mUnknown21;
    unsigned char mUnknown22;
    unsigned char mUnknown23;
    unsigned char mUnknown24;
    unsigned char mUnknown25;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
int fn_80178320(void);
}

extern "C" void fn_800F8828(Object_80039F5C *p, Object_80039F5C *pOther, Block_800F8A88 *pBlock) {
    if (p && pOther) {
        Point_8017886C origin;

        origin = fn_80177FE0();
        p->mpState->mUnknown2 |= pBlock->mUnknown25;
        if (fabsf(p->mMotion.mPos.mY - origin.mY) <= 5.0f && fabsf(pOther->mMotion.mPos.mY - origin.mY) <= 5.0f
            && pBlock->mUnknown25 == 2) {
            p->mpState->mUnknown2 &= ~pBlock->mUnknown25;
        }
    }
}

extern "C" void fn_800F88E4(Object_80039F5C *p, Object_80039F5C *pTarget) {
    unsigned char *pMine = &p->mpState->mUnknown2;
    unsigned char *pTheirs = 0;
    Object_80039F5C *pFound = 0;
    unsigned short i;
    unsigned int n = fn_80178D18(fn_80178320());

    for (i = 0; i < n; i++) {
        Object_80039F5C *pOther = fn_80039F5C(fn_80178320(), i);

        if (pOther->mpState->mId == 22 && pTarget == fn_8009BCE8(&pOther->mUnknown336) && pOther != p) {
            pFound = pOther;
            pTheirs = &pFound->mpState->mUnknown2;
        }
    }
    if (pFound && fn_8022781C(&pFound->mMotion.mPos, &pTarget->mMotion.mPos) < 5.0f
        && fn_8022781C(&p->mMotion.mPos, &pTarget->mMotion.mPos) < 5.0f) {
        Vector_80039F5C ball;
        int right;

        fn_80137D58(fn_801374BC(), &ball);
        right = pTarget->mMotion.mPos.mX > ball.mX;
        *pTheirs &= ~1;
        *pMine &= ~1;
        *pTheirs &= ~2;
        *pMine &= ~2;
        if ((right && pFound->mMotion.mPos.mX < p->mMotion.mPos.mX)
            || (!right && pFound->mMotion.mPos.mX > p->mMotion.mPos.mX)) {
            *pTheirs |= 2;
            *pMine |= 1;
        } else {
            *pTheirs |= 1;
            *pMine |= 2;
        }
    }
}
