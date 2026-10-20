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

/* View of the block at player +336 as fn_8010AF48 resets it. */
struct Block_8010AF48 {
    int mUnknown0;
    short mUnknown4;
    unsigned char mUnknown6;
    unsigned char mUnknown7;
    unsigned char mUnknown8;
};

extern "C" {
void fn_8009BD60(Object_80039F5C *p);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
}

extern "C" void fn_8010AECC(Object_80039F5C *p, unsigned char a, unsigned char b, unsigned char c) {
    fn_8009BD60(p);
    p->mUnknown1008.mUnknown0 = a;
    p->mUnknown1008.mUnknown1 = b;
    p->mUnknown1008.mUnknown2 = c;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 83, p, 1.0f);
    p->mUnknown512.mUnknown14 = 0;
    p->mFlags &= ~0x40000;
    p->mFlags &= ~4;
}

extern "C" int fn_8010AF48(Object_80039F5C *p) {
    Block_8010AF48 *pBlock;

    p->mUnknown336 = -1;
    pBlock = (Block_8010AF48 *)&p->mUnknown336;
    pBlock->mUnknown4 = 0;
    pBlock->mUnknown6 = 0;
    pBlock->mUnknown8 = 0;
    pBlock->mUnknown7 = 0;
    if (!(p->mFlags & 0x40000)) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 91, p, 1.0f);
    }
    return 0;
}
