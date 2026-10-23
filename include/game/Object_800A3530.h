#ifndef GAME_OBJECT_800A3530_H
#define GAME_OBJECT_800A3530_H

#include "game/Table_80089904.h"
#include "game/Object_8003DEC4.h"
#include "engine/Record_800D81C8.h"

/* Object the motion-phase callbacks of lbl_8030EFB4 receive. Only the
   accessed fields are declared. */
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

typedef int (*Callback_800A3530)(Table_80089904 *pTable, unsigned short key, void *pRecord,
                                 Record_800D81C8 *pEntries, Object_800A3530 *p, unsigned int phase);

extern "C" {
int fn_800A3530(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                Object_800A3530 *p, unsigned int phase);
int fn_800A37D8(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                Object_800A3530 *p, unsigned int phase);
int fn_800A3898(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                Object_800A3530 *p, unsigned int phase);
int fn_800A3B10(Object_800A3530 *p);
}

#endif
