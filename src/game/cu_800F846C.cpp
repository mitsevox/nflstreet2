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
int fn_801CFE40(float y, float x);
void fn_800F6B2C(Object_80039F5C *p, Point_8017886C *pDelta);
extern float lbl_803EAE40;
extern float lbl_803EAE44;
extern float lbl_803EAE48;
}

extern "C" void fn_800F846C(Object_80039F5C *p, Object_80039F5C *pOther, Point_8017886C *pOut) {
    if (p && pOther && pOut) {
        Block_800F8A88 *pBlock = (Block_800F8A88 *)&p->mUnknown336;
        float offset;
        float distance;

        pOut->mY = lbl_803EAE40 + fn_80177FE0().mY - p->mMotion.mPos.mY;
        if (pOther->mMotion.mPos.mX > fn_80177FE0().mX) {
            offset = lbl_803EAE48;
        } else {
            offset = -lbl_803EAE48;
        }
        pOut->mX = pOther->mMotion.mPos.mX + offset - p->mMotion.mPos.mX;
        fn_800F6B2C(p, pOut);
        distance = fn_802270A4(pOut);
        pBlock->mUnknown8 = fn_801CFE40(pOut->mY, pOut->mX) & 0xFFFFFF;
        pBlock->mUnknown4 = 0xC00000;
        if (distance > lbl_803EAE44) {
            pBlock->mUnknown12 = 0.5f;
        } else {
            pBlock->mUnknown12 = 0.25f;
        }
        pBlock->mUnknown24 = 0;
    }
}
