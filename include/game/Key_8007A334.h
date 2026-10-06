#ifndef GAME_KEY_8007A334_H
#define GAME_KEY_8007A334_H

/* Sort/key entry list passed as the third argument of fn_8007A334. */
struct Key_8007A334 {
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
