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

/* View of the block at player +336 used by fn_800F930C. */
struct Block_800F930C {
    int mRef;
    int mUnknown4;
    int mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
};

extern "C" int fn_800F930C(Object_80039F5C *p) {
    Block_800F930C *pBlock = (Block_800F930C *)&p->mUnknown336;
    Object_80039F5C *pOther = fn_8009BCE8(&pBlock->mRef);

    if (pOther) {
        Vector_80039F5C delta;

        fn_802276B4(&delta, &pOther->mMotion.mPos, &p->mMotion.mPos);
        if (fabsf(delta.mX) <= 4.0f && delta.mY <= -3.0f && pBlock->mUnknown16 <= 60) {
            if (delta.mX > 0.0f) {
                pBlock->mUnknown8 = 0x100000;
            } else {
                pBlock->mUnknown8 = 0x700000;
            }
            pBlock->mUnknown4 = 0xC00000;
            pBlock->mUnknown12 = 0.33f;
            return 1;
        }
    }
    return 0;
}
