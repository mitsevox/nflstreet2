/* Reads the list of hair styles from the game database for the player appearance screens: opens the
   HAIR table in display order, finds a style by id and reads its name and model. */

#include "game/DbCursor.h"
#include "game/DbSortKey.h"

extern "C" {

void HairListOpen(DbCursor *pObject)
{
    DbSortKey keys[2];

    keys[0].Set(0x52494148, 0x524F5248, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pObject, 0x52494148, -1, keys, 0, 0x54415453);
}

void HairListClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

void HairListFind(DbCursor *pObject, int id, int *pResult)
{
    DbCursorFindInt(pObject, 0x52414850, id, 0, pResult);
}

void HairListGetName(DbCursor *pObject, char *pBuffer, int size)
{
    fn_8007AA3C(pObject, 0x4D4E5248, (int)pBuffer, size);
}

int HairListGetId(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x52414850);
}

int HairListGetModel(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x444D5248);
}

}
