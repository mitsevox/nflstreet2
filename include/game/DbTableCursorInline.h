#ifndef GAME_DB_TABLE_CURSOR_INLINE_H
#define GAME_DB_TABLE_CURSOR_INLINE_H

#include "game/DbTableCursor.h"

/* Inline definition of the DbTableCursor constructor (the body of
   0x8018FD64: vtable 0x802AB4F8, then the DbCursor constructor), for
   files that construct the object inline. */
inline DbTableCursor::DbTableCursor() {}

/* Constructs the cursor and opens it on a table in one step. */
inline DbTableCursor::DbTableCursor(int a, int b, void *c, void *d, int e)
{
    OpenTable(a, b, c, d, e);
}

#endif
