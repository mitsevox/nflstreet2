#include "game/Object_80039F5C.h"
#include "game/Block_801BE60C.h"

extern "C" void fn_800A42BC(Object_80039F5C *p, Block_801BE60C *pBlock)
{
    float scale = 0.4f;

    pBlock->mUnknown8 = 1.0f;
    if (p->mRatings[0] > 127) {
        pBlock->mUnknown8 = (float)(short)(p->mRatings[0] - 127) / 128.0f * scale + 1.0f;
    }
}

#include "game/Table_80089904.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801BA2A8.h"
#include "game/Message_800F01CC.h"
#include "engine/Record_800D81C8.h"

extern "C" {
void fn_800A4294(Object_80039F5C *p, Block_801BE60C *pBlock);
unsigned short fn_800A414C(Table_80089904 *table, Object_80039F5C *p, Block_801BE60C *pBlock);
unsigned short fn_800A4358(Table_80089904 *table, Object_80039F5C *p, Block_801BE60C *pBlock);
float fn_801CFFA0(float value);
void fn_801BD81C(Block_801BD6D4 *p, float scale);
void fn_801C1F94(void *p, int value, unsigned int size);
void fn_800F00D4(int a, State_80039F5C *pState, Message_800F01CC *pMessage, Object_80039F5C *p);
}

extern "C" int fn_800A44C0(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_80039F5C *p, unsigned int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown792, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown792, key, 1);
        fn_800A4294(p, block);
        fn_800A42BC(p, block);
        unsigned short index;
        if (fn_801BE648(p->mpUnknown792) == 185)
            index = fn_800A414C(table, p, block);
        else
            index = fn_800A4358(table, p, block);
        int entry = fn_801BA2A8(record, entries, table->mEntries[index].mUnknown0,
                                table->mEntries[index].mUnknown2, key, p, 1.0f);
        block->mUnknown0Word = entry;
        fn_801BD81C(&entries[entry].mUnknown4C, fn_801CFFA0(block->mUnknown8));
        block->mUnknown10Word = (int)((float)block->mUnknownCWord / block->mUnknown4);
        p->mFlags &= ~4;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            p->mMotion.mFacing = (p->mMotion.mFacing + block->mUnknown10Word) & 0xFFFFFF;
            entries[block->mUnknown0Word].mUnknownC =
                (entries[block->mUnknown0Word].mUnknownC + block->mUnknown10Word) & 0xFFFFFF;
            if (p->mUnknown9[0] != 1 && (p->mFlags & 0x800)) {
                Message_800F01CC message;
                fn_801C1F94(&message, 0, sizeof(message));
                message.mId = 11;
                message.mUnknown1[0] = p->mUnknown9[0];
                fn_800F00D4(0, p->mpState, &message, p);
                return 1;
            }
            if (p->mFlags & 4) {
                p->mFlags &= ~4;
                p->mFlags &= ~0x800;
                block->mUnknown10Word = 0;
            }
        }
        break;
    }
    return 0;
}
