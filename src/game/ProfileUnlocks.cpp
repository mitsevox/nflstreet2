/* Keeps what a profile has unlocked in its saved database: which team logos are locked or new,
   which offensive and defensive plays are in the user's playbook, and which teams are hidden. */

#include "game/DbCursor.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_801FA844(int a, void *b, void *c, unsigned long long key, QueryResult *pValue, QueryResult *pResult);
int DbCursorGetValue(DbCursor *pObject, int key);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int handle);
int fn_8022F4BC(void);
}

static int _Playbook_aTables[2] = { 0x504F5355, 0x50445355 };

extern "C" {

void LogoLockOpen(DbCursor *pObject, signed char db)
{
    DbCursorOpen(pObject, 0x474C4B4C, 0x4C474C54, 0, 0, fn_8022F3D4(fn_8022F358(db)));
}

void LogoLockClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int LogoLockGetId(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x4C474C54);
}

int LogoLockIsLocked(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x4B4C474C) != 0;
}

int LogoIsNew(int a)
{
    unsigned char result = 0;
    DbCursor cursor;

    LogoLockOpen(&cursor, fn_8022F384(fn_8022F4BC()));
    if (DbCursorFindInt(&cursor, 0x4C474C54, a, 0, 0)) {
        result = DbCursorGetInt(&cursor, 0x574E5247) != 0;
    }
    LogoLockClose(&cursor);
    return result;
}

void LogoClearNew(int a)
{
    DbCursor cursor;

    LogoLockOpen(&cursor, fn_8022F384(fn_8022F4BC()));
    if (DbCursorFindInt(&cursor, 0x4C474C54, a, 0, 0)) {
        DbCursorSetInt(&cursor, 0x574E5247, 0);
    }
    LogoLockClose(&cursor);
}

void LogoUnlock(int a)
{
    DbCursor cursor;

    LogoLockOpen(&cursor, fn_8022F384(fn_8022F4BC()));
    if (DbCursorFindInt(&cursor, 0x4C474C54, a, 0, 0)) {
        DbCursorSetInt(&cursor, 0x4B4C474C, 0);
    }
    LogoLockClose(&cursor);
}

int PlaybookGetMaxOrder(DbCursor *pObject)
{
    QueryResult result;
    QueryResult value;

    fn_801FA844(pObject->mUnknown4, pObject->mUnknown20, 0,
                ((unsigned long long)(unsigned int)pObject->mUnknown8 << 32) | 0x58505355,
                &value, &result);
    return value.mUnknown4;
}

void PlaybookOpen(DbCursor *pObject, signed char db, int index)
{
    int handle = fn_8022F3D4(fn_8022F358(db));
    DbCursorOpen(pObject, _Playbook_aTables[index], 0x44505355, 0, 0, handle);
}

void PlaybookClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

void PlaybookUnlockPlay(int index, int a)
{
    DbCursor cursor;

    PlaybookOpen(&cursor, fn_8022F384(fn_8022F4BC()), index);
    if (DbCursorFindValue(&cursor, 0x44505355, a, 0, 0)) {
        DbCursorSetValue(&cursor, 0x58505355, PlaybookGetMaxOrder(&cursor) + 1);
    }
    PlaybookClose(&cursor);
}

void PlaybookUnlockAll(signed char db, int index)
{
    DbCursor cursor;

    PlaybookOpen(&cursor, db, index);
    if (DbCursorFirst(&cursor)) {
        do {
            if (DbCursorGetValue(&cursor, 0x58505355) == -1) {
                DbCursorSetValue(&cursor, 0x58505355, PlaybookGetMaxOrder(&cursor) + 1);
            }
        } while (DbCursorNext(&cursor));
    }
    PlaybookClose(&cursor);
}

void PlaybookResetOrder(signed char db, int index)
{
    int fetched = 1;
    int open = 1;
    DbCursor cursor;
    QueryCursor query;
    int value;
    int table;
    int i = 0;
    int row;

    table = index == 0 ? 0x504F5355 : 0x50445355;
    fn_8022F3D4(fn_8022F358(db));
    query.mUnknown0 = 0;
    query.mUnknown4 = 0;
    query.mUnknown8 = -1;
    query.mUnknown12 = 0;
    int status = fn_801FCE10(0, "use 'TATS' declare \x8a fastcursor for select 'XPSU' into \x85 from \x8c\n",
                             &query, &value, table);
    if (status == 0) {
        PlaybookOpen(&cursor, db, index);
        row = DbCursorFirst(&cursor);
        while (open && fetched && row) {
            query.mUnknown4 = i++;
            if (query.mUnknown0 && QUERY_STATUS_ACCEPTED(status) == 1 && status != 0x15) {
                status = fn_801FCE10(0, "fetch from \x8a\n", &query);
                if (QUERY_STATUS_ACCEPTED(status) == 1 && status != 0x15) {
                    DbCursorSetValue(&cursor, 0x58505355, value);
                    row = DbCursorNext(&cursor);
                } else {
                    fetched = 0;
                }
            } else {
                open = 0;
            }
        }
        PlaybookClose(&cursor);
    }
    if (query.mUnknown0) {
        fn_801FCFA0(&query);
    }
}

void TeamLockOpen(DbCursor *pObject, int db)
{
    DbCursorOpen(pObject, 0x4D45544C, 0x44494754, 0, 0, fn_8022F3D4(fn_8022F358(db)));
}

void TeamLockClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int TeamLockIsHidden(DbCursor *pObject, int id)
{
    int result = 0;

    if (DbCursorFindInt(pObject, 0x44494754, id, 0, 0)) {
        result = !DbCursorGetInt(pObject, 0x53495654);
    }
    return result;
}

void TeamUnlock(int db, int id)
{
    DbCursor cursor;

    TeamLockOpen(&cursor, db);
    if (DbCursorFindInt(&cursor, 0x44494754, id, 0, 0)) {
        DbCursorSetInt(&cursor, 0x53495654, 1);
    }
    TeamLockClose(&cursor);
}

void TeamLock(int db, int id)
{
    DbCursor cursor;

    TeamLockOpen(&cursor, db);
    if (DbCursorFindInt(&cursor, 0x44494754, id, 0, 0)) {
        DbCursorSetInt(&cursor, 0x53495654, 0);
    }
    TeamLockClose(&cursor);
}

void TeamUnlockAll(int db)
{
    DbCursor cursor;

    TeamLockOpen(&cursor, db);
    if (DbCursorFirst(&cursor)) {
        do {
            DbCursorSetInt(&cursor, 0x53495654, 1);
        } while (DbCursorNext(&cursor));
    }
    TeamLockClose(&cursor);
}

void TeamLockAll(int db)
{
    DbCursor cursor;

    TeamLockOpen(&cursor, db);
    if (DbCursorFirst(&cursor)) {
        do {
            DbCursorSetInt(&cursor, 0x53495654, 0);
        } while (DbCursorNext(&cursor));
    }
    TeamLockClose(&cursor);
}

}
