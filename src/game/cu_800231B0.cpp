#include "game/DbSortKey.h"
#include "game/DbCursor.h"

extern "C" {
int DbCursorGetValue(DbCursor *pObject, int key);

int fn_800231B0(DbCursor *pObject, int a, int *pResult)
{
    return DbCursorFindInt(pObject, 0x4449564D, a, 0, pResult);
}

int fn_800231E8(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x43494C4D);
}

int fn_80023210(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x4349534D);
}

int fn_80023238(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x4449524D);
}

void fn_80023260(DbCursor *pObject, char *pData, int size)
{
    fn_8007AA3C(pObject, 0x5449544D, (int)pData, size);
}

void fn_80023294(DbCursor *pObject, char *pData, int size)
{
    fn_8007AA3C(pObject, 0x4353444D, (int)pData, size);
}

void fn_800232C8(DbCursor *pObject)
{
    DbSortKey keys[2];

    keys[0].Set(0x54425753, 0x524F5753, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pObject, 0x54425753, -1, keys, 0, 0x54415453);
}

void fn_8002333C(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

void fn_8002335C(DbCursor *pCursor, int value, int *pResult)
{
    DbCursorFindInt(pCursor, 0x554E5753, value, 0, pResult);
}

void fn_80023394(DbCursor *pCursor, char *pBuffer, int size)
{
    fn_8007AA3C(pCursor, 0x414E5753, (int)pBuffer, size);
}

int fn_800233C8(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x554E5753);
}

void fn_800233F0(DbCursor *pCursor, int type)
{
    DbFilter arg;
    DbSortKey keys[2];

    arg.Set(6, 0x4F5441544C544154LL, 3, type);
    keys[0].Set(0x4F544154, 0x524F5454, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pCursor, 0x4F544154, -1, keys, &arg, 0x54415453);
}

void fn_80023498(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

void fn_800234B8(DbCursor *pCursor, char *pBuffer, int size)
{
    fn_8007AA3C(pCursor, 0x4E544154, (int)pBuffer, size);
}

int fn_800234EC(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49544154);
}
}
