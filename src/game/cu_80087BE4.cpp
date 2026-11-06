#include "game/DbCursor.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);

void fn_80087BE4(DbCursor *pObject, int index)
{
    DbCursorOpen(pObject, 0x54535055, 0x776E5355, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void fn_80087C3C(DbCursor *pObject)
{
    DbCursorClose(pObject);
}
}
