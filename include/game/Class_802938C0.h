#ifndef GAME_CLASS_802938C0_H
#define GAME_CLASS_802938C0_H

#include "game/Class_8018FD64.h"

/* Class_8018FD64 cursor with vtable 0x802938C0, which repeats the entries of
   the base vtable 0x802AB4F8 except the destructor 0x80083454. The members
   0x80190098-0x801901A4 pass fixed column and table tags to the base
   entries. */
class Class_802938C0 : public Class_8018FD64 {
public:
    virtual ~Class_802938C0();

    void fn_80190098();
    int fn_801900D4(int id, int *pResult);
    int fn_80190120();
    void fn_8019015C(char *pBuffer, int size);
    int fn_801901A4();
};

#endif
