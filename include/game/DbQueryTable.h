#ifndef GAME_DBQUERYTABLE_H
#define GAME_DBQUERYTABLE_H

#include "game/DbCursor.h"

struct DbQueryTable {
    void Set(int tag, int type = 2, DbFilter *filter = 0)
    {
        mFilter = filter;
        mTag = tag;
        mUnknown4 = type;
    }

    int mTag;
    int mUnknown4;
    DbFilter *mFilter;
};

extern "C" {
int fn_801F9D70(int handle, int table, DbFilter *pFilter, unsigned short *pCount);
int fn_801FA148(int cursor);
int fn_801FA290(int handle, DbQueryTable *pTables, DbFilter *pFilter, DbColumnValue *pColumns);
}

#endif
