/*
 * Loads game-database tables from a named file. DbGame gives it the file name when the game
 * database starts and takes it back when it stops; the game then loads a database's tables from
 * that file through the file I/O device, and destroys tables it no longer needs, one at a time,
 * from a list of table ids, or for every table that a list table flags.
 */
#include "engine/dbfile.h"
#include "engine/dbutil.h"
#include "engine/tdbiofio.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"
#include <string.h>

extern int TDbLoadFromFile(int db, int file, char *pName, int mode, TDbIODevice_t *pDevice);
extern int TDbTblDestroy(int db, int tbl);
extern int TDbTblExists(int db, int tbl);

static char *_DbFile_pFileName = 0;

int DbFileInit(const char *pName)
{
    _DbFile_pFileName = DbUtilAlloc(strlen(pName) + 1, 1);
    strcpy(_DbFile_pFileName, pName);
    return 0;
}

void DbFileShutdown(void)
{
    DbUtilFree(_DbFile_pFileName);
    _DbFile_pFileName = 0;
}

int DbFileTblLoad(int db, int file)
{
    return TDbLoadFromFile(db, file, _DbFile_pFileName, 3, &tdbiofioCallback);
}

int DbFileTblDestroy(int db, int tbl)
{
    return TDbTblDestroy(db, tbl);
}

int DbFileTblLoadList(int db, int *pTbls)
{
    int status = 0;
    unsigned short i;

    for (i = 0; pTbls[i] != -1; i++) {
        if (TDbTblExists(db, pTbls[i]) != 0) {
            status = DbFileTblLoad(db, pTbls[i]);
            if (QUERY_STATUS_ACCEPTED(status) != 1) {
                return status;
            }
            status = 0;
        }
    }
    return status;
}

int DbFileTblDestroyList(int db, int *pTbls)
{
    int status = 0;
    unsigned short i;

    for (i = 0; pTbls[i] != -1; i++) {
        if (TDbTblExists(db, pTbls[i]) == 0) {
            status = DbFileTblDestroy(db, pTbls[i]);
            if (status != 0) {
                return status;
            }
        }
    }
    return status;
}

int DbFileTblLoadSelected(int db, int listTbl, int flagCol)
{
    struct QueryCursor cursor;
    int tbl;
    int status;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, "use \214 declare \212 cursor for select * from \214 where (\214 = \202)\n", db, &cursor, listTbl, flagCol, 1);
    if (status == 0) {
        do {
            status = TDbCompilePerformOp(0, "fetch from \212 'FERT' into \202\n", &cursor, &tbl);
            if (status == 0 && TDbTblExists(db, tbl) != 0) {
                status = DbFileTblLoad(db, tbl);
                if (QUERY_STATUS_ACCEPTED(status) == 1) {
                    status = 0;
                }
            }
        } while (status == 0);
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

int DbFileTblDestroySelected(int db, int listTbl, int flagCol)
{
    struct QueryCursor cursor;
    int tbl;
    int status;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(0, "use \214 declare \212 cursor for select * from \214 where (\214 = \202)\n", db, &cursor, listTbl, flagCol, 1);
    if (status == 0) {
        do {
            status = TDbCompilePerformOp(0, "fetch from \212 'FERT' into \202\n", &cursor, &tbl);
            if (status == 0 && TDbTblExists(db, tbl) == 0) {
                status = DbFileTblDestroy(db, tbl);
            }
        } while (status == 0);
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
