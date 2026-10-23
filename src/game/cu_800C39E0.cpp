#include "game/Object_80039F5C.h"
#include "game/Block_800DE3B0.h"
#include "game/Table_80089904.h"
#include "game/fn_801BA2A8.h"

extern "C" {
int fn_801BE068(void *, void *, void *, unsigned short, void *, float);
void fn_800C38C4(Object_80039F5C *p, Block_800DE3B0 *pBlock, int key);
void fn_800D8140(State_800D8140 *pState, Object_80039F5C *p, int value);
void fn_800D81C8(State_800D8140 *pState, Object_80039F5C *p);
void fn_800DEC10(Object_80039F5C *p, Block_800DE3B0 *pBlock);
void fn_800DF654(Object_80039F5C *p, Block_801BE60C *pRecord);
int fn_801784C4(void);
int fn_801BA6B0(Record_800D81C8 *pChannel);
void fn_801BA6BC(Record_800D81C8 *pChannel, int enable);
Block_801BE60C *fn_801BE60C(void *p, unsigned short key);
unsigned short fn_801BE648(void *p);
void fn_801BE760(void *p, unsigned short key, unsigned short flags);
}

extern "C" void fn_800C39E0(Object_80039F5C *p, int a, int index, int value, int flag)
{
    if (flag != 0) {
        index |= 0x8000;
    }
    p->mUnknown1008.mUnknown0 = index;
    p->mUnknown1008.mUnknown1 = (unsigned int)index >> 8;
    p->mUnknown1008.mUnknown2 = value;
    p->mUnknown1011 = (unsigned int)value >> 8;
    fn_801BE068(p->mpUnknown792, p->mpUnknown796, p->mpUnknown800, a, p, 1.0f);
}


extern "C" int fn_800C3A4C(Table_80089904 *pTable, unsigned short key, void *pA, Record_800D81C8 *pEntries,
                           Object_80039F5C *p, unsigned int mode)
{
    Block_800DE3B0 *pBlock = (Block_800DE3B0 *)fn_801BE60C(p->mpUnknown792, key);

    switch (mode) {
    case 0: {
        int index;

        fn_801BE760(p->mpUnknown792, key, 1);
        index = p->mUnknown1008.mUnknown0 | (p->mUnknown1008.mUnknown1 << 8);
        pBlock->mUnknown1D = fn_801BA2A8(pA, pEntries, p->mUnknown1008.mUnknown2 | (p->mUnknown1011 << 8),
                                         index & 0x7FFF, key, p, 1.0f);
        pBlock->mUnknown18 = key;
        p->mFlags |= 0x200;
        fn_800C38C4(p, pBlock, index);
        if (pBlock->mUnknown1F) {
            Record_800D81C8 *pEntry = &pEntries[pBlock->mUnknown1D];

            fn_801BA6BC(pEntry, fn_801BA6B0(pEntry) == 0);
            pBlock->mUnknown1F = fn_801BA6B0(&pEntries[pBlock->mUnknown1D]);
        }
        fn_800D8140(&pBlock->mUnknown20, p, pBlock->mUnknown1D);
        pBlock->mUnknown1E = fn_801784C4();
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown792) == key) {
            int side = fn_801784C4();

            if (side != pBlock->mUnknown1E) {
                pBlock->mUnknown1E = side;
                fn_800DF654(p, (Block_801BE60C *)pBlock);
            }
            fn_800DEC10(p, pBlock);
            fn_800D81C8(&pBlock->mUnknown20, p);
        }
        break;
    case 1:
    case 3:
        pBlock->mUnknown1C = 0;
        p->mFlags &= ~0x200;
        break;
    }
    return 0;
}
