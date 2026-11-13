/* Game database helpers for the front end: the tutorial lesson table (title,
   description, status), and the pose and tattoo tables of create-a-player. */

#include "game/DbSortKey.h"
#include "game/DbCursor.h"

extern "C" {
int DbCursorGetValue(DbCursor *pObject, int key);

int LessonTableSeek(DbCursor *pObject, int a, int *pResult)
{
    return DbCursorFindInt(pObject, 0x4449564D, a, 0, pResult);
}

int LessonTableGetCILM(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x43494C4D);
}

int LessonTableGetCISM(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x4349534D);
}

int LessonTableGetDIRM(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x4449524D);
}

void LessonTableGetTitle(DbCursor *pObject, char *pData, int size)
{
    DbCursorGetString(pObject, 0x5449544D, (int)pData, size);
}

void LessonTableGetDescription(DbCursor *pObject, char *pData, int size)
{
    DbCursorGetString(pObject, 0x4353444D, (int)pData, size);
}

void PoseTableOpen(DbCursor *pObject)
{
    DbSortKey keys[2];

    keys[0].Set(0x54425753, 0x524F5753, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pObject, 0x54425753, -1, keys, 0, 0x54415453);
}

void PoseTableClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

void PoseTableSeek(DbCursor *pCursor, int value, int *pResult)
{
    DbCursorFindInt(pCursor, 0x554E5753, value, 0, pResult);
}

void PoseTableGetName(DbCursor *pCursor, char *pBuffer, int size)
{
    DbCursorGetString(pCursor, 0x414E5753, (int)pBuffer, size);
}

int PoseTableGetNumber(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x554E5753);
}

void TattooTableOpen(DbCursor *pCursor, int type)
{
    DbFilter arg;
    DbSortKey keys[2];

    arg.Set(6, 0x4F5441544C544154LL, 3, type);
    keys[0].Set(0x4F544154, 0x524F5454, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pCursor, 0x4F544154, -1, keys, &arg, 0x54415453);
}

void TattooTableClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

void TattooTableGetName(DbCursor *pCursor, char *pBuffer, int size)
{
    DbCursorGetString(pCursor, 0x4E544154, (int)pBuffer, size);
}

int TattooTableGetId(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49544154);
}
}
