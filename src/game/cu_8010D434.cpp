#include "engine/cu_801B9F00.h"
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

struct State_8010D80C {
    Vector_80039F5C mUnknown0;
    char mUnknown12[4];
    float mUnknown16;
    char mUnknown20[6];
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

extern "C" {
int fn_801BA6B0(Entry_800EAC9C *pEntry);
void fn_801BA6BC(Entry_800EAC9C *pEntry, int flag);
int fn_801BE068(void *a, void *b, void *c, unsigned short d, void *pRecord, float e);
}

extern "C" void fn_8010D434(Object_80039F5C *p, State_8010D80C *pState) {
    p->mFlags &= ~4;
    if (p->mUnknown1008.mUnknown0 == 2) {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 176, p, 1.0f);
    } else {
        fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, 37, p, 1.0f);
    }
    if (pState->mUnknown27) {
        Record_800D81C8 *pEntries = p->mpUnknown800;
        Record_800D81C8 *pEntry = &pEntries[fn_801BA5A8(p->mpUnknown796, pEntries, 37, 0)];

        fn_801BA6BC(pEntry, !fn_801BA6B0(pEntry));
    }
    pState->mUnknown26 = 1;
}
