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

/* View of the block at player +336 that fn_8010D508 fills: a position, a
   scale, an animation pair and two flag bytes. */
struct Block_8010D508 {
    Vector_80039F5C mUnknown0;
    char mUnknown12[4];
    float mUnknown16;
    int mUnknown20;
    unsigned short mUnknown24;
    unsigned char mUnknown26;
    unsigned char mUnknown27;
};

/* View of the record a Table_80089904 entry points to, as fn_8010D508 reads
   it: two positions at +8 and +20 and a scale at +32. */
struct Info_8010D508 {
    char mUnknown0[8];
    Vector_80039F5C mUnknown8;
    Vector_80039F5C mUnknown20;
    float mUnknown32;
};

extern "C" {
int fn_8009C4B0(Table_80089904 *pTable, Key_80110630 *pKey);
void fn_8009BD60(Object_80039F5C *p);
void fn_8010D434(Object_80039F5C *p, Block_8010D508 *pBlock);
void fn_80227264(void *pOut, void *pV, float scale);
void fn_80227384(void *pOut, void *pV, int angle);
void fn_8022765C(void *pOut, void *pA, void *pB);
void fn_80227690(void *pOut, void *pA, void *pB);
extern Table_80089904 lbl_80319ED8;
}

extern "C" void fn_8010D508(Object_80039F5C *p) {
    State_80039F5C *pState = p->mpState;
    Block_8010D508 *pBlock = (Block_8010D508 *)&p->mUnknown336;
    int close = 0;
    int flip = 0;
    int index;
    Object_80039F5C *pCarrier;
    Info_8010D508 *pInfo;
    Vector_80039F5C offset;
    Vector_80039F5C pivot;

    pBlock->mUnknown27 = 0;
    fn_8009BD60(p);
    pCarrier = fn_80137AD0(fn_801374BC());
    if (fn_8022781C(&p->mMotion.mPos, &pCarrier->mMotion.mPos) < 2.5f) {
        fn_801BBC3C(1, 0x25, &lbl_80319ED8);
        p->mUnknown1008.mUnknown0 = 1;
        close = 1;
    } else {
        fn_801BBC3C(1, 0xB0, &lbl_80319ED8);
        p->mUnknown1008.mUnknown0 = 2;
    }
    p->mUnknown1008.mUnknown1 = pState->mUnknown1;
    index = fn_8009C4B0(&lbl_80319ED8, &p->mUnknown1008);
    pBlock->mUnknown24 = lbl_80319ED8.mEntries[index].mUnknown0;
    pBlock->mUnknown20 = lbl_80319ED8.mEntries[index].mUnknown2;
    pInfo = (Info_8010D508 *)lbl_80319ED8.mEntries[index].mpInfo;
    pBlock->mUnknown16 = pInfo->mUnknown32;
    offset = pInfo->mUnknown8;
    pivot = pInfo->mUnknown20;
    

    if (flip) {
        offset.mY = -offset.mY;
        pivot.mY = -pivot.mY;
    }
    pBlock->mUnknown0.mX = offset.mX;
    pBlock->mUnknown0.mY = offset.mY;
    pBlock->mUnknown0.mZ = offset.mZ;
    fn_80227690(pBlock, pBlock, &pivot);
    fn_80227264(pBlock, pBlock, p->mUnknown768);
    fn_80227638(pBlock, pBlock, &pivot);
    fn_80227384(pBlock, pBlock, p->mMotion.mFacing);
    fn_8022765C(pBlock, pBlock, &p->mMotion.mPos);
    if (close) {
        fn_8010D434(p, pBlock);
    } else {
        pBlock->mUnknown26 = close;
    }
}
