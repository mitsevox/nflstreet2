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

/* View of the block at player +336 as the animation callbacks use it. */
struct Block_8010BC90 {
    unsigned char mUnknown0;
    char mUnknown1[2];
    unsigned char mUnknown3;
    char mUnknown4[16];
    int mUnknown20;
    unsigned short mUnknown24;
};

extern "C" {
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
int fn_801BA2A8(void *pData, void *pEntries, unsigned short value, int animation, int key, void *p, float weight);
}

extern "C" int fn_8010D834(Table_80089904 *pTable, unsigned short key, void *pData, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int mode) {
    if (mode == 0) {
        if (p->mpState->mId == 56) {
            Block_8010BC90 *pBlock = (Block_8010BC90 *)&p->mUnknown336;

            fn_801BA2A8(pData, pEntries, pBlock->mUnknown24, pBlock->mUnknown20, key, p, 1.0f);
        } else {
            int index = fn_8009C4B0(pTable, &p->mUnknown1008);

            if (index >= 0) {
                fn_801BA2A8(pData, pEntries, pTable->mEntries[index].mUnknown0, pTable->mEntries[index].mUnknown2,
                            key, p, 1.0f);
            }
        }
    }
    return 0;
}
