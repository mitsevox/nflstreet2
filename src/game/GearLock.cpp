/* Tracks which pieces of player gear are locked or newly unlocked in a profile's saved database,
   and answers whether a gear category has new items for the gear menu. */

#include "game/DbCursor.h"
#include "game/TDbCompilePerformOp.h"

#include "game/DbQueryTable.h"

extern "C" {
int TDbTblDestroy(int handle, int table);
int TDbTblFindUnusedId(int handle, int *pTable);
int TDbQryColStats(int a, void *b, void *c, unsigned long long key, QueryResult *pValue, QueryResult *pResult);
int DbUserGetId(int index);
int DbUserFindIndex(int a);
int DbUserGetDb(int handle);
int DbUserGetCurrent(void);
}

extern "C" {

void GearLockOpen(DbCursor *pObject, signed char db)
{
    DbCursorOpen(pObject, 0x5245474C, 0x594B5047, 0, 0, DbUserGetDb(DbUserGetId(db)));
}

void GearLockClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

void GearLockGetFlags(DbCursor *pObject, int key, unsigned char *pA, unsigned char *pB)
{
    *pA = 0;
    *pB = 0;
    if (DbCursorFindInt(pObject, 0x594B5047, key, 0, 0)) {
        if (DbCursorGetInt(pObject, 0x4B434C47)) {
            *pA = 1;
        }
        if (DbCursorGetInt(pObject, 0x574E5247)) {
            *pB = 1;
        }
    }
}

int GearLockIsLocked(DbCursor *pObject, int key)
{
    int result = 0;

    if (DbCursorFindInt(pObject, 0x594B5047, key, 0, 0) && DbCursorGetInt(pObject, 0x4B434C47)) {
        result = 1;
    }
    return result;
}

int GearIsLocked(int key)
{
    DbCursor cursor;
    int result;

    GearLockOpen(&cursor, DbUserFindIndex(DbUserGetCurrent()));
    result = GearLockIsLocked(&cursor, key);
    GearLockClose(&cursor);
    return result;
}

void GearLockClearNew(DbCursor *pObject, int id)
{
    if (DbCursorFindInt(pObject, 0x594B5047, id, 0, 0)) {
        DbCursorSetInt(pObject, 0x574E5247, 0);
    }
}

int GearHasNew(int type, int a, int b)
{
    QueryResult result;
    DbQueryTable tables[3];
    DbFilter join;
    DbFilter typeFilter;
    DbFilter both;
    DbFilter idFilter;
    DbFilter extra;
    QueryResult value;
    int table;
    int found = 0;
    DbFilter *pFilter;
    DbFilter *pExtra = 0;

    int db = DbUserGetDb(DbUserGetCurrent());
    TDbTblFindUnusedId(0x54415453, &table);
    if (TDbCompilePerformOp(&result, "use \x8c select into \x8c.\x8c * from \x8c where 'WNRG' = 1 and 'KCLG' = 0\n",
                    db, 0x54415453, table, 0x5245474C) != 23) {
        unsigned int t = table;
        unsigned long long column = 0x594B5047;
        join.Set(6, 0x52414547594B5047LL, 6);
        join.mUnknown16.mValue.mLong = ((unsigned long long)t << 32) | column;
        typeFilter.Set(6, 0x5241454749545247LL, 3);
        typeFilter.mUnknown16.mValue.mInt = type;
        pFilter = &typeFilter;
        if (a >= 0) {
            both.Set(11, pFilter, &idFilter);
            idFilter.Set(6, 0x5241454749545347LL, 3);
            idFilter.mUnknown16.mValue.mInt = a;
            pFilter = &both;
        }
        if (b == 0) {
            unsigned long long column2 = 0x4B4C4347;
            pExtra = &extra;
            pExtra->Set(6, ((unsigned long long)table << 32) | column2, 3, 0);
        }
        tables[0].Set(0x52414547, 0, pFilter);
        tables[1].Set(table, 2, &join);
        tables[2].Set(-1, 2, 0);
        if (TDbQryColStats(0x54415453, tables, pExtra, ((unsigned long long)(unsigned int)table << 32) | 0x574E5247,
                        &value, 0) != 23) {
            found = 1;
        }
    }
    TDbTblDestroy(0x54415453, table);
    return found;
}

void GearUnlock(int key)
{
    DbCursor cursor;

    GearLockOpen(&cursor, DbUserFindIndex(DbUserGetCurrent()));
    if (DbCursorFindInt(&cursor, 0x594B5047, key, 0, 0)) {
        DbCursorSetInt(&cursor, 0x4B434C47, 0);
        DbCursorSetInt(&cursor, 0x574E5247, 1);
    }
    GearLockClose(&cursor);
}

void GearLock(int key)
{
    DbCursor cursor;

    GearLockOpen(&cursor, DbUserFindIndex(DbUserGetCurrent()));
    if (DbCursorFindInt(&cursor, 0x594B5047, key, 0, 0)) {
        DbCursorSetInt(&cursor, 0x4B434C47, 1);
        DbCursorSetInt(&cursor, 0x574E5247, 0);
    }
    GearLockClose(&cursor);
}

void GearUnlockAll(signed char db)
{
    DbCursor cursor;

    GearLockOpen(&cursor, db);
    if (DbCursorFirst(&cursor)) {
        do {
            DbCursorSetInt(&cursor, 0x4B434C47, 0);
            DbCursorSetInt(&cursor, 0x574E5247, 1);
        } while (DbCursorNext(&cursor));
    }
    GearLockClose(&cursor);
}

void GearLockAll(signed char db)
{
    DbCursor cursor;

    GearLockOpen(&cursor, db);
    if (DbCursorFirst(&cursor)) {
        do {
            DbCursorSetInt(&cursor, 0x4B434C47, 1);
            DbCursorSetInt(&cursor, 0x574E5247, 0);
        } while (DbCursorNext(&cursor));
    }
    GearLockClose(&cursor);
}

}
