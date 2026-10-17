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

/* View of the block at player +336 that fn_800F4E14 and fn_800F6158
   address. */
struct Object_800F4E14 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    char mUnknown16[4];
    int mUnknown20;
    unsigned char mUnknown24;
};

extern "C" {
int fn_8011F1A4(void);
unsigned char fn_8011F4C8(void);
void fn_800C89F0(Object_80039F5C *p, int angle, int a, int b, float scale);
void fn_80227538(Point_8017886C *pOut, int angle, float length);
void fn_8011E3EC(Object_80039F5C *p, int a);
int fn_800F4E14(Object_80039F5C *p, Object_800F4E14 *pInfo);
}

extern "C" void fn_800F60BC(Object_80039F5C *p) {
    int facing = p->mMotion.mFacing & 0xFFFFFF;

    if ((facing >= 0x755556 && facing <= 0x8AAAAA) || facing < 0xAAAAA || facing > 0xF55556) {
        if (fn_8011F1A4() && fn_8011F4C8() > 3) {
            fn_800C89F0(p, 0x400000, 2, 0, 1.0f);
        }
    }
}

extern "C" int fn_800F6158(Object_80039F5C *p) {
    Object_800F4E14 *pBlock = (Object_800F4E14 *)&p->mUnknown336;
    Vector_80039F5C *pPos = &p->mMotion.mPos;
    int result;

    pBlock->mUnknown20 = (p->mpState->mUnknown2 << 17) & 0xFE0000;
    result = fn_800F4E14(p, pBlock);
    if (!result) {
        Point_8017886C offset;
        unsigned char distance = p->mpState->mUnknown1;

        pBlock->mUnknown8 = (distance >> 3) + (distance & 7) * 0.14285715f;
        pBlock->mUnknown12 = p->mpState->mUnknown3[0] * 0.003921569f;
        fn_80227538(&offset, pBlock->mUnknown20, pBlock->mUnknown8);
        pBlock->mUnknown0 = p->mMotion.mPos.mX + offset.mX;
        pBlock->mUnknown4 = pPos->mY + offset.mY;
        pBlock->mUnknown24 = result;
        fn_8011E3EC(p, 3);
        p->mUnknown512.mUnknown14 = 1;
        p->mUnknown512.mUnknown8 = pBlock->mUnknown20;
        p->mUnknown512.mUnknown4 = pBlock->mUnknown20;
        p->mUnknown512.mUnknown0 = pBlock->mUnknown12;
    }
    return 0;
}
