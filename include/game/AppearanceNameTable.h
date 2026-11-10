#ifndef GAME_APPEARANCENAMETABLE_H
#define GAME_APPEARANCENAMETABLE_H

#include "game/DbTableCursor.h"

/* Defined in src/game/AppearanceNameTable.cpp: a DbTableCursor cursor member with
   the vtable pointer after it (0x34 bytes). */
class AppearanceNameTable {
public:
    AppearanceNameTable();
    virtual ~AppearanceNameTable();
    void GetItemName(int a, int b, int c);

private:
    DbTableCursor mUnknown0;
};

#endif
