/*
 * Loads game-database tables from a named file. DbGame gives it the file name when the game
 * database starts and takes it back when it stops; the game then loads a database's tables from
 * that file through the file I/O device, and destroys tables it no longer needs.
 */
#include "engine/dbfile.h"
#include "engine/dbutil.h"
#include "engine/tdbiofio.h"
#include <string.h>

extern int fn_801F9064(int db, int file, char *pName, int mode, TDbIODevice_t *pDevice);
extern int fn_801F967C(int db, int tbl);

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
    return fn_801F9064(db, file, _DbFile_pFileName, 3, &tdbiofioCallback);
}

int DbFileTblDestroy(int db, int tbl)
{
    return fn_801F967C(db, tbl);
}
