#ifndef GAME_FCHR_CURSOR_H
#define GAME_FCHR_CURSOR_H

#include "game/DbTableCursor.h"

/* DbTableCursor cursor with vtable 0x802938C0, which repeats the entries of
   the base vtable 0x802AB4F8 except the destructor 0x80083454. The members
   0x80190098-0x801901A4 pass fixed column and table tags to the base
   entries. */
class FchrCursor : public DbTableCursor {
public:
    void OpenFchrTable();
    int FindFchrRow(int id, int *pResult);
    int GetFchrPffh();
    void GetFchrFhdcText(char *pBuffer, int size);
    int GetFchrFhstCode();
};

#endif
