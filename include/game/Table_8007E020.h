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

#endif
