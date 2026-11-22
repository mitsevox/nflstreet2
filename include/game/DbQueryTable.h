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
int TDbTblGetCount(int handle, int table, DbFilter *pFilter, unsigned short *pCount);
int TDbQryDestroy(int cursor);
int TDbQryGetSingleRow(int handle, DbQueryTable *pTables, DbFilter *pFilter, DbColumnValue *pColumns);
}

#endif
