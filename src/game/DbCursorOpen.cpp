/* Opens the game's T3DB database cursors: checks the database version, and opens a cursor on a
   table (optionally sorted and filtered) for the record wrappers to read and write. */

#include "game/DbCursor.h"
#include "game/DbQueryTable.h"
#include "game/fn_801FCE10.h"

extern "C" {
int fn_801FA0BC(int handle, DbQueryTable *pTables, DbFilter *pFilter, void *pSort, int *pCursor,
                QueryResult *pResult);
int fn_801FA148(int cursor);

void DbCheckVersion(int handle)
{
    DbQueryTable tables[2];
    QueryResult result;
    DbColumnValue columns[2];
    int cursor = 0;

    tables[0].Set(0x52455653);
    tables[1].Set(-1);
    fn_801FA0BC(handle, tables, 0, 0, &cursor, &result);
    columns[0].Set(0x52455653, 0x52455653);
    columns[0].mValue = 0;
    columns[1].Set(-1, -1);
    columns[1].mValue = 0;
    fn_801FA228(cursor, 1, 0, columns);
    if (columns[0].mValue != 0xB2A) {
        *(char *)0 = 0;
    }
    fn_801FA148(cursor);
}

void DbCursorOpenTable(DbCursor *pObject, int a, int b)
{
    DbCursorOpen(pObject, a, b, 0, 0, 0);
}

void DbCursorOpen(DbCursor *pObject, int a, int b, void *c, void *d, int e)
{
    DbQueryTable *tables = (DbQueryTable *)pObject->mUnknown20;
    QueryResult result;

    pObject->mUnknown4 = e;
    pObject->mUnknown12 = b;
    pObject->mUnknown8 = a;
    tables[0].Set(a, 2, (DbFilter *)d);
    tables[1].Set(-1);
    fn_801FA0BC(pObject->mUnknown4, tables, 0, c, &pObject->mUnknown0, &result);
    if (result.mUnknown0 != 0) {
        pObject->mUnknown16 = 0;
    } else {
        pObject->mUnknown16 = -1;
    }
}
}
