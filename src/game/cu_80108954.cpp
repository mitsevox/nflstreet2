#include "game/fn_801248D4.h"
#include "game/Queue_800EFE0C.h"
#include "game/State_800FDA58.h"
#include <math.h>
#include <string.h>
#include "game/fn_800B65A0.h"
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
#include "game/Block_801BE60C.h"

/* The 88-byte block at player +336 as fn_80109150 initialises it and
   fn_80108954 updates it. */
struct Block_80109150 {
    char mUnknown0[36];
    int mUnknown36;
    int mUnknown40;
    float mUnknown44;
    unsigned char mUnknown48;
    unsigned char mUnknown49;
    unsigned char mUnknown50;
    unsigned char mUnknown51;
    unsigned char mUnknown52;
    unsigned char mUnknown53;
    unsigned char mUnknown54;
    char mUnknown55[1];
    unsigned char mUnknown56;
    unsigned char mUnknown57;
    short mUnknown58;
    unsigned char mUnknown60;
    unsigned char mUnknown61;
    unsigned char mUnknown62;
    unsigned char mUnknown63;
    unsigned char mUnknown64;
    unsigned char mUnknown65;
    unsigned char mUnknown66;
    char mUnknown67[21];
};

/* Output of fn_801076F0. */
struct Result_801076F0 {
    Point_8017886C mUnknown0;
    Point_8017886C mUnknown8;
    int mUnknown16;
    int mUnknown20;
    int mUnknown24;
    int mUnknown28;
    float mUnknown32;
    float mUnknown36;
    float mUnknown40;
};

extern "C" {
int fn_801CFFD0(int a, int b);
}

extern "C" void fn_80108954(Object_80039F5C *p, Object_80039F5C *pOther, Result_801076F0 *pInfo) {
    Block_80109150 *pBlock = (Block_80109150 *)&p->mUnknown336;

    if (pOther != 0 && pBlock->mUnknown49 == 3) {
        pBlock->mUnknown53 = 1;
        if (pBlock->mUnknown44 <= 0.7f && fn_801CFFD0(pInfo->mUnknown20, p->mMotion.mUnknown32) > 0x78E38E) {
            pBlock->mUnknown52 = 1;
        }
        if (pBlock->mUnknown57 != 0 ||
            (pBlock->mUnknown61 != 0 && pBlock->mUnknown54 != 0 && pInfo->mUnknown40 < 2.0f)) {
            pBlock->mUnknown57 = 1;
            pBlock->mUnknown40 = (pInfo->mUnknown20 + 0x800000) & 0xFFFFFF;
            if (fn_801CFFD0(p->mMotion.mFacing, pBlock->mUnknown40) > 0xAAAAA) {
                pBlock->mUnknown36 = pInfo->mUnknown20;
            } else {
                pBlock->mUnknown48 = 12;
            }
        }
    }
    if (pOther != 0 && pOther->mpState->mId == 28 &&
        fn_801CFFD0(pInfo->mUnknown20 + 0x800000, p->mMotion.mFacing) <= 0x471C71) {
        pBlock->mUnknown53 = 1;
    }
}
