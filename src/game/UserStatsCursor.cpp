/* Opens and closes the cursor on a profile's user statistics row (wins, losses, streak and
   other totals). */

#include "game/DbCursor.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);

void UserStatsOpen(DbCursor *pObject, int index)
{
    DbCursorOpen(pObject, 0x54535055, 0x776E5355, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void UserStatsClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}
}
