#ifndef GAME_FN_800A3530_H
#define GAME_FN_800A3530_H

#include "game/Table_80089904.h"
#include "game/Object_80039F5C.h"
#include "engine/Record_800D81C8.h"

/* Motion-phase callbacks of the lbl_8030EFB4 table. */
typedef int (*Callback_800A3530)(Table_80089904 *pTable, unsigned short key, void *pRecord,
                                 Record_800D81C8 *pEntries, Object_80039F5C *p, unsigned int phase);

extern "C" {
int fn_800A3530(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                Object_80039F5C *p, unsigned int phase);
int fn_800A37D8(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                Object_80039F5C *p, unsigned int phase);
int fn_800A3898(Table_80089904 *pTable, unsigned short key, void *pRecord, Record_800D81C8 *pEntries,
                Object_80039F5C *p, unsigned int phase);
int fn_800A3B10(Object_80039F5C *p);
}

#endif
