/* Opens and closes the cursor on a profile's user statistics row (wins, losses, streak and
   other totals). */

#include "game/DbCursor.h"

extern "C" {
int DbUserGetId(int index);
int DbUserGetDb(int handle);

void UserStatsOpen(DbCursor *pObject, int index)
{
    DbCursorOpen(pObject, 0x54535055, 0x776E5355, 0, 0, DbUserGetDb(DbUserGetId(index)));
}

void UserStatsClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}
}
