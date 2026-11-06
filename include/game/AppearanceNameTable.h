#ifndef GAME_APPEARANCENAMETABLE_H
#define GAME_APPEARANCENAMETABLE_H

#include "game/Class_8018FD64.h"

/* Defined in src/game/AppearanceNameTable.cpp: a Class_8018FD64 cursor member with
   the vtable pointer after it (0x34 bytes). */
class AppearanceNameTable {
public:
    AppearanceNameTable();
    virtual ~AppearanceNameTable();
    void GetItemName(int a, int b, int c);

private:
    Class_8018FD64 mUnknown0;
};

#endif
