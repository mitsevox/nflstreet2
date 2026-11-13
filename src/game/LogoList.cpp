/* Builds the list of team logos a profile can choose from when creating a team: copies the logo
   table, keeps only the logos the profile has unlocked, sorts them and reads each logo's name and
   id. */

#include "game/DbCursor.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void LogoLockOpen(DbCursor *pObject, signed char a);
void LogoLockClose(DbCursor *pObject);
int LogoLockGetId(DbCursor *pObject);
int LogoLockIsLocked(DbCursor *pObject);
}

static int _LogoList_aSortKeys[8] = { 0x4F474F4C, 0x524F474C, 0, 0, -1, -1, 3, 0 };
static int _LogoList_iTable;

extern "C" {

void LogoListOpen(DbCursor *pObject)
{
    DbCursor cursor;
    QueryResult result;
    DbFilter arg;
    unsigned char a;

    a = fn_8022F384(fn_8022F4BC());
    fn_801F9980(0x54415453, &_LogoList_iTable);
    fn_801FCE10(&result, "use \x8c select into \x8c * from 'OGOL'\n", 0x54415453, _LogoList_iTable);
    LogoLockOpen(&cursor, a);
    if (DbCursorFirst(&cursor)) {
        do {
            if (LogoLockIsLocked(&cursor) == 0) {
                int id = LogoLockGetId(&cursor);
                fn_801FCE10(0, "use \x8c update \x8c set 'KLGL' = 0 where 'LGLT' = \x82\n", 0x54415453,
                            _LogoList_iTable, id);
            }
        } while (DbCursorNext(&cursor));
    }
    LogoLockClose(&cursor);

    unsigned int table = _LogoList_iTable;
    unsigned long long column = 0x4B4C474C;
    arg.Set(6, ((unsigned long long)table << 32) | column, 3);
    arg.mUnknown16.mValue.mInt = 0;
    DbCursorOpen(pObject, _LogoList_iTable, -1, _LogoList_aSortKeys, &arg, 0x54415453);
}

void LogoListClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
    fn_801F967C(0x54415453, _LogoList_iTable);
}

void LogoListGetName(DbCursor *pObject, char *pBuffer, int size)
{
    DbCursorGetString(pObject, 0x4D4E474C, (int)pBuffer, size);
}

int LogoListGetId(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x4C474C54) + 45;
}

void LogoListFind(DbCursor *pObject, int a, int *pResult)
{
    DbCursorFindInt(pObject, 0x4C474C54, a - 45, 0, pResult);
}

}
