/* The 'SRPT' module of the game database and the team-id helpers next to it: when the database
   modules start it reads every 'SRPT' row into a small table (four halfwords per row), drops the
   'SRPT' table from the database and keeps the game start and resume hooks it was given; it also
   deletes the cached rows of selected teams and finds unused team ids. */

#include "engine/dbutil.h"
#include "engine/llmemory.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

typedef struct DbSrptRow_t {
    unsigned short mEdrh;
    unsigned short mEdrl;
    unsigned short mCarh;
    unsigned short mCarl;
} DbSrptRow_t;

typedef struct DbSrptCallbacks_t {
    int (*mpBeginGameFunc)(int a, int b, int c, int d);
    int (*mpResumeGameFunc)(int a, int b, int c, int d);
} DbSrptCallbacks_t;

extern int TDbQryGetCount(int ref, unsigned short *pCount);
extern int TDbTblExists(int db, int tbl);
extern int DbCacheDeleteRows(int id, int a, int b);
int DbTatsCopyTblDestroy(int db, int tbl);

extern char _DbSrpt_szFetchTeamIdQuery[];
extern char _DbSrpt_szDeclareSrptQuery[];
extern char _DbSrpt_szFetchSrptQuery[];
extern char _DbSrpt_szDeclareTeamsByFlagQuery[];
extern char _DbSrpt_szDeclareTeamsByFlagTypeQuery[];
extern char _DbSrpt_szDeclareTeamIdsQuery[];

static DbSrptRow_t _DbSrpt_aRows[11];
static unsigned char _DbSrpt_bHasTable = 0;
static int (*_DbSrpt_pBeginGameFunc)(int a, int b, int c, int d) = 0;
static int (*_DbSrpt_pResumeGameFunc)(int a, int b, int c, int d) = 0;

int DbSrptDeleteCursorTeams(struct QueryCursor cursor, int a)
{
    unsigned short total;
    int *pIds;
    int id;
    int status;
    unsigned short count;
    unsigned short i;

    pIds = 0;
    status = TDbQryGetCount(cursor.mUnknown0, &total);
    if (status == 0) {
        pIds = DbUtilAlloc(total * 4, 0);
    }
    count = 0;
    if (status == 0) {
        while (status == 0) {
            status = TDbCompilePerformOp(0, _DbSrpt_szFetchTeamIdQuery, &cursor, &id);
            if (status == 0) {
                pIds[count] = id;
                count++;
            }
        }
        if (QUERY_STATUS_ACCEPTED(status) == 1) {
            status = 0;
        }
        if (status == 0) {
            for (i = 0; i < count; i++) {
                status = DbCacheDeleteRows(pIds[i], 0, a);
                if (status != 0) {
                    break;
                }
            }
        }
    }
    if (pIds != 0) {
        DbUtilFree(pIds);
    }
    return status;
}

int DbSrptModuleInit(DbSrptCallbacks_t *pCallbacks)
{
    struct QueryCursor cursor;
    int status = 0;
    int index;
    unsigned short a;
    unsigned short b;
    unsigned short c;
    unsigned short d;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, _DbSrpt_szDeclareSrptQuery, &cursor);
    while (status == 0) {
        status = TDbCompilePerformOp(0, _DbSrpt_szFetchSrptQuery, &cursor, &index, &a, &b, &c, &d);
        if (status == 0) {
            _DbSrpt_aRows[index].mEdrh = a;
            _DbSrpt_aRows[index].mEdrl = b;
            _DbSrpt_aRows[index].mCarh = c;
            _DbSrpt_aRows[index].mCarl = d;
        }
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    if (status == 0) {
        status = DbTatsCopyTblDestroy(0, 0x53525054);
    } else {
        DbTatsCopyTblDestroy(0, 0x53525054);
    }
    _DbSrpt_bHasTable = 0;
    if (status == 0) {
        _DbSrpt_bHasTable = TDbTblExists(0, 0x53525054) == 0;
        if (pCallbacks != 0) {
            _DbSrpt_pBeginGameFunc = pCallbacks->mpBeginGameFunc;
            _DbSrpt_pResumeGameFunc = pCallbacks->mpResumeGameFunc;
        }
    }
    return status;
}

void DbSrptModuleShutdown(void)
{
    MemFill((char *)_DbSrpt_aRows, 88, 0, 4);
    _DbSrpt_bHasTable = 0;
    _DbSrpt_pBeginGameFunc = 0;
    _DbSrpt_pResumeGameFunc = 0;
}

int DbSrptDeleteUnflaggedTeams(int a)
{
    struct QueryCursor cursor;
    int status = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, _DbSrpt_szDeclareTeamsByFlagQuery, &cursor, 0);
    if (status == 0) {
        status = DbSrptDeleteCursorTeams(cursor, a);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return status;
}

int DbSrptDeleteUnflaggedTypedTeams(int a)
{
    struct QueryCursor cursor;
    int status = 0;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, _DbSrpt_szDeclareTeamsByFlagTypeQuery, &cursor, 0, 5, 1);
    if (status == 0) {
        status = DbSrptDeleteCursorTeams(cursor, a);
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return status;
}

int DbFindUnusedTeamIds(int db, int tbl, int *pIds, unsigned short *pCount)
{
    struct QueryCursor cursor;
    int status = 0;
    int id;
    int prev;
    int next;
    int last;
    unsigned short count;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, _DbSrpt_szDeclareTeamIdsQuery, db, &cursor, tbl);
    prev = -1;
    next = -1;
    last = 1023;
    count = 0;
    while (status == 0 && count < *pCount) {
        status = TDbCompilePerformOp(0, _DbSrpt_szFetchTeamIdQuery, &cursor, &id);
        if (status == 0) {
            if (id > prev + 1) {
                next = prev + 1;
                while (status == 0 && next < id) {
                    if (count < *pCount && next <= 1008) {
                        pIds[count] = next;
                        count++;
                        next++;
                    } else {
                        break;
                    }
                }
            }
            if (next > id) {
                last = next;
            } else {
                last = id;
            }
            prev = id;
        }
    }
    if (QUERY_STATUS_ACCEPTED(status) == 1) {
        if (cursor.mUnknown0 != 0) {
            status = TDbSQLDestroyCursor(&cursor);
        } else {
            status = 0;
        }
    } else if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    if (status == 0 && count < *pCount) {
        if (last == 1023) {
            next = 0;
        } else {
            next = last + 1;
        }
        while (count < *pCount) {
            if (next <= 1008) {
                pIds[count] = next;
                count++;
                next++;
            } else {
                break;
            }
        }
    }
    *pCount = count;
    return status;
}

int DbSrptBeginGame(int a, int b, int c, int d)
{
    int err = 0;

    if (_DbSrpt_pBeginGameFunc != 0) {
        err = _DbSrpt_pBeginGameFunc(a, b, c, d);
    }
    return err;
}

int DbSrptResumeGame(int a, int b, int c, int d)
{
    int err = 0;

    if (_DbSrpt_pResumeGameFunc != 0) {
        err = _DbSrpt_pResumeGameFunc(a, b, c, d);
    }
    return err;
}

