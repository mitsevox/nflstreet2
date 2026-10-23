#include "game/cu_8002B8F8.h"
#include "game/cu_80064864.h"
#include "game/Block_800AD634.h"
#include "game/Table_80089904.h"
#include "game/Object_8003DEC4.h"
#include "game/Block_801BE60C.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801BA2A8.h"
#include "game/Player_800ADA1C.h"

extern "C" {
int fn_8002C9A8(Type_803EA368 *p, int msg, int value);

extern Block_800AD634 *lbl_803EAAD4;
}

extern "C" void fn_800AD9C0(float value)
{
    Block_800AD634 *p = lbl_803EAAD4;

    if (p != 0 && value > 0.0f) {
        p->mUnknownC = value;
        p->mUnknown8 = 1;
        fn_800655B8();
        fn_8002C9A8(lbl_803EA368, 4, 0);
    }
}

extern "C" int fn_800ADA1C(Table_80089904 *pTable, unsigned short key, void *pA,
                           Record_800D81C8 *pRecords, Player_800ADA1C *p, unsigned int phase)
{
    int side;
    Object_8003DEC4 *pObject;
    Block_801BE60C *pBlock;

    if (pRecords == p->mUnknown4032[0]) {
        side = 0;
    } else {
        side = pRecords == p->mUnknown4032[1];
    }
    pObject = (Object_8003DEC4 *)p->mObject.mpUnknown4;
    pBlock = fn_801BE60C(p->mUnknown4528[side], key);
    switch (phase) {
    case 0:
        fn_801BA2A8(pA, pRecords,
                    pTable->mEntries[p->mObject.mUnknown1008.mUnknown0 | (p->mObject.mUnknown1008.mUnknown1 << 8)].mUnknown0,
                    pTable->mEntries[p->mObject.mUnknown1008.mUnknown0 | (p->mObject.mUnknown1008.mUnknown1 << 8)].mUnknown2,
                    key, 0, 1.0f);
        pObject->mUnknown20 |= 0x20;
        pObject->mUnknown116[side].mUnknown0 = 1;
        pBlock->mUnknown0 = side;
        break;
    case 1:
        if (side == 1) {
            pObject->mUnknown20 &= ~0x20;
        }
        pObject->mUnknown116[pBlock->mUnknown0].mUnknown0 = 0;
        break;
    case 2:
        break;
    }
    return 0;
}
