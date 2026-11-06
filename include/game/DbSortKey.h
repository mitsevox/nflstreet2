#ifndef GAME_DBSORTKEY_H
#define GAME_DBSORTKEY_H

/* Sort/key entry list passed as the third argument of DbCursorOpen. */
struct DbSortKey {
    void Set(int table, int column, int value)
    {
        mTable = table;
        mColumn = column;
        mUnknown8 = value;
    }

    int mTable;
    int mColumn;
    int mUnknown8;
    int mUnknown12;
};

#endif
