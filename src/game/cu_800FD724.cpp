#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
#include "game/Class_80297CE8.h"
#include "game/Command_800CEE74.h"
#include "game/Input_800B6D34.h"
#include "game/Lookup_8012078C.h"
#include "game/Message_800F01CC.h"
#include "game/Object_80039F5C.h"
#include "game/Object_8017886C.h"
#include "game/Plan_80121264.h"
#include "game/Record_800B15FC.h"
#include "game/Record_8011F518.h"
#include "game/Team_80167A8C.h"
#include "game/State_803EB098.h"
#include "game/cu_80067C10.h"
#include "game/Query_800CE770.h"
#include "game/Table_80089904.h"
#include "game/cu_80136B1C.h"
#include "game/fn_800670B4.h"
#include "game/fn_800AD9B4.h"
#include "game/fn_800F06F4.h"
#include "game/fn_80163E94.h"
#include "game/fn_8016871C.h"
#include "game/fn_80177FE0.h"
#include "game/fn_80178D18.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_802270D4.h"
#include "game/fn_80227638.h"
#include "game/fn_8022781C.h"
#include "game/fn_802372EC.h"
#include "game/fn_80238174.h"
#include "game/Record_800DB60C.h"
#include "game/fn_801BE60C.h"

struct Block_800FD650 {
    float mUnknown0;
    float mUnknown4;
    float mUnknown8;
    float mUnknown12;
    unsigned int mUnknown16;
};
extern "C" {
int fn_801CFE40(float y, float x);
void fn_80227690(void *pOut, void *pA, void *pB);
void fn_800FD724(Object_80039F5C *p);
}

extern "C" void fn_800FD724(Object_80039F5C *p)
{
    if (p && (p->mpState->mId == 3 || p->mpState->mId == 19)) {
        Block_800FD650 *pBlock = (Block_800FD650 *)&p->mUnknown336;
        Point_8017886C delta;
        Point_8017886C target;

        target.mX = pBlock->mUnknown0;
        target.mY = pBlock->mUnknown4;
        fn_80227690(&delta, &target, &p->mMotion.mPos);
        p->mpState->mUnknown1 = (int)(fn_802270A4(&delta) * 8.0f);
        p->mpState->mUnknown2 = fn_801CFE40(delta.mY, delta.mX) >> 17;
    }
}
