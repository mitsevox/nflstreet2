#ifndef GAME_TABLE_8007E020_H
#define GAME_TABLE_8007E020_H

#include "game/Object_8007A334.h"

struct Table_8007E020 {
    void Set(int tag, int type = 2, Object_80023BBC *filter = 0)
    {
        mFilter = filter;
        mTag = tag;
        mUnknown4 = type;
    }

    int mTag;
    int mUnknown4;
    Object_80023BBC *mFilter;
};

extern "C" {
int fn_801F9D70(int handle, int table, Object_80023BBC *pFilter, unsigned short *pCount);
int fn_801FA148(int cursor);
int fn_801FA290(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter, ColumnValue_802D6424 *pColumns);
}

#endif
