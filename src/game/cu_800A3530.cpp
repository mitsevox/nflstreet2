#include "game/Table_80089904.h"
#include "game/Block_801BE60C.h"
#include "game/fn_801BE60C.h"
#include "game/fn_801BA2A8.h"
#include "game/Object_8003DEC4.h"
#include "engine/Record_800D81C8.h"

/* Player-like object the motion-phase callbacks of lbl_8030EFB4 receive.
   Only the accessed fields are declared. */
struct Object_800A3530 {
    char mUnknown0[4];
    Object_8003DEC4 *mpUnknown4;
    char mUnknown8[0x31C];
    void *mpUnknown324;
    Object_801BA03C *mpUnknown328;
    Record_800D81C8 *mpUnknown32C;
    char mUnknown330[0xC4];
    unsigned char mUnknown3F4;
    unsigned char mUnknown3F5;
    unsigned char mUnknown3F6;
};

extern "C" {
void fn_801BE3C0(void *p, unsigned short key, int type, float from, void *pSource, float to);
float fn_801BD660(void *pScript, int key);
float fn_801BD6D4(Block_801BD6D4 *p);
void fn_800425D4(Object_8003DEC4 *pObject);
void fn_801BA384(Object_801BA03C *pList, Record_800D81C8 *pChannels, int index);
void fn_801BE420(void *p, Object_801BA03C *pObject, Record_800D81C8 *pRecords, void *pOwner, float step);
int fn_800A3B10(Object_800A3530 *p);
void fn_800A3D68(int value);
extern int lbl_803EC93C;
extern int lbl_803EC940;
}

extern "C" int fn_800A3530(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_800A3530 *p, unsigned int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown324, key);
    switch (phase) {
    case 0:
        fn_801BE760(p->mpUnknown324, key, 1);
        if (p->mUnknown3F4 < table->mCount) {
            int entry = fn_801BA2A8(record, entries, table->mEntries[p->mUnknown3F4].mUnknown0,
                                    table->mEntries[p->mUnknown3F4].mUnknown2, key, p, 1.0f);
            block->mUnknown0Word = entry;
            block->mUnknown4Unsigned =
                (unsigned int)fn_801BD660(p->mpUnknown32C[entry].mUnknown4C.mpUnknown0, 0x8000);
            p->mpUnknown4->mUnknown20 |= 0x10;
        }
        block->mUnknown8Byte = p->mUnknown3F6;
        break;
    case 1:
        if (block->mUnknown8Byte == 1 && fn_801BE648(p->mpUnknown324) == key) {
            Data1_801BF4A8 data;
            data.mUnknown4 = 1;
            data.mUnknown0 = 1.0f;
            fn_801BE3C0(p->mpUnknown324, key, 1, 1.0f, &data, 0.0f);
            fn_801BE068(p->mpUnknown324, p->mpUnknown328, p->mpUnknown32C, 2, p, 1.0f);
        }
        break;
    case 2:
        if (block->mUnknown8Byte == 1 && fn_801BE648(p->mpUnknown324) == key
            && (unsigned int)((float)block->mUnknown4Unsigned
                              - fn_801BD6D4(&p->mpUnknown32C[block->mUnknown0Word].mUnknown4C)) <= 7) {
            Data1_801BF4A8 data;
            data.mUnknown4 = 8;
            data.mUnknown0 = 1.0f;
            fn_801BE3C0(p->mpUnknown324, key, 1, 1.0f, &data, 0.0f);
            fn_801BE068(p->mpUnknown324, p->mpUnknown328, p->mpUnknown32C, 2, p, 1.0f);
        }
        break;
    case 3:
        if (block->mUnknown8Byte == 1) {
            fn_800A3D68(0);
            if (!fn_800A3B10(p))
                fn_800425D4(p->mpUnknown4);
        }
        break;
    }
    return 0;
}

extern "C" int fn_800A37D8(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_800A3530 *p, unsigned int phase)
{
    switch (phase) {
    case 0:
        fn_801BA2A8(record, entries, lbl_803EC93C, lbl_803EC940, key, p, 1.0f);
        p->mpUnknown4->mUnknown20 |= 0x10;
        break;
    case 1:
        if (!fn_800A3B10(p))
            fn_800425D4(p->mpUnknown4);
        break;
    case 2:
        break;
    case 3:
        if (!fn_800A3B10(p))
            fn_800425D4(p->mpUnknown4);
        break;
    }
    return 0;
}

extern "C" int fn_800A3898(Table_80089904 *table, unsigned short key, void *record,
                           Record_800D81C8 *entries, Object_800A3530 *p, unsigned int phase)
{
    Block_801BE60C *block = fn_801BE60C(p->mpUnknown324, key);
    switch (phase) {
    case 0: {
        fn_801BE760(p->mpUnknown324, key, 1);
        int index = (signed char)p->mUnknown3F4;
        int entry = fn_801BA2A8(record, entries, table->mEntries[index].mUnknown0,
                                table->mEntries[index].mUnknown2, key, p, 1.0f);
        block->mUnknown0Word = entry;
        block->mUnknown4Unsigned =
            (unsigned int)fn_801BD660(p->mpUnknown32C[entry].mUnknown4C.mpUnknown0, 0x8000);
        p->mpUnknown4->mUnknown20 |= 0x10;
        p->mpUnknown4->mUnknown20 &= ~0x40000;
        break;
    }
    case 2:
        if (fn_801BE648(p->mpUnknown324) == key) {
            p->mpUnknown4->mUnknown20 |= 0x40000;
            if (block->mUnknown4Unsigned
                    - (unsigned int)fn_801BD6D4(&p->mpUnknown32C[block->mUnknown0Word].mUnknown4C) <= 7) {
            Data1_801BF4A8 data;
                data.mUnknown4 = 8;
                data.mUnknown0 = 1.0f;
                fn_801BE3C0(p->mpUnknown324, key, 1, 1.0f, &data, 0.0f);
                fn_801BE068(p->mpUnknown324, p->mpUnknown328, p->mpUnknown32C, 2, p, 1.0f);
            }
        }
        break;
    case 1:
        if (fn_801BE648(p->mpUnknown324) == key) {
            Data1_801BF4A8 data;
            data.mUnknown4 = 1;
            data.mUnknown0 = 1.0f;
            fn_801BE3C0(p->mpUnknown324, key, 1, 1.0f, &data, 0.0f);
            fn_801BE068(p->mpUnknown324, p->mpUnknown328, p->mpUnknown32C, 2, p, 1.0f);
        }
        break;
    case 3:
        if (fn_801BE648(p->mpUnknown324) == key && !fn_800A3B10(p))
            fn_800425D4(p->mpUnknown4);
        break;
    }
    return 0;
}

extern "C" void fn_800A3B5C(Object_800A3530 *p)
{
    if (p->mpUnknown328 != 0) {
        for (int i = 0; i < p->mpUnknown328->mUnknown4; i++) {
            if (p->mpUnknown32C[i].mUnknown1 == 2)
                fn_801BA384(p->mpUnknown328, p->mpUnknown32C, i);
        }
        fn_801BE420(p->mpUnknown324, p->mpUnknown328, p->mpUnknown32C, p, 1.0f);
        fn_801BE420(p->mpUnknown324, p->mpUnknown328, p->mpUnknown32C, p, 1.0f);
    }
    fn_800425D4(p->mpUnknown4);
}
