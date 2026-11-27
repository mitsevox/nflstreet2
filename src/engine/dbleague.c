/* The league lists of the game database: when the module starts it reads every conference id
   ('FNOC'), every division with its conference ('IVID') and every team of the listed types with
   its conference and division ('MAET', in team order) into arrays from the database heap, and
   frees them when it stops. */

#include "engine/dbutil.h"
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

static int *_DbLeague_pConferences = 0;
static unsigned short _DbLeague_iNumConferences = 0;
static int (*_DbLeague_pDivisions)[2] = 0;
static unsigned short _DbLeague_iNumDivisions = 0;
static int (*_DbLeague_pTeams)[3] = 0;
static unsigned short _DbLeague_iNumTeams = 0;

int DbLoadConferenceIds(void)
{
    struct QueryCursor cursor;
    struct QueryResult result;
    unsigned short i;
    int status = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(&result, "declare \x8a cursor for select * from 'FNOC' where ('DIGC' >= \x82) and ('DIGC' <= \x82) order by 'DIGC' asc\n",
                                 &cursor, 0, 1);
    _DbLeague_iNumConferences = result.mUnknown0;
    if (status == 0 && _DbLeague_iNumConferences != 0) {
        _DbLeague_pConferences = DbUtilAlloc(_DbLeague_iNumConferences * 4, 1);
        i = 0;
        do {
            status = TDbCompilePerformOp(0, "fetch from \x8a 'DIGC' into \x82\n", &cursor, &_DbLeague_pConferences[i]);
            i++;
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

void DbLeagueFreeConferences(void)
{
    if (_DbLeague_pConferences != 0) {
        DbUtilFree(_DbLeague_pConferences);
        _DbLeague_pConferences = 0;
        _DbLeague_iNumConferences = 0;
    }
}

int DbLoadDivisionIds(void)
{
    struct QueryCursor cursor;
    struct QueryResult result;
    unsigned short i;
    int status = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(&result, "declare \x8a cursor for select * from 'IVID' where ('DIGD' >= \x82) and ('DIGD' <= \x82) order by 'DIGD' asc\n",
                                 &cursor, 0, 7);
    _DbLeague_iNumDivisions = result.mUnknown0;
    if (status == 0 && _DbLeague_iNumDivisions != 0) {
        _DbLeague_pDivisions = DbUtilAlloc(_DbLeague_iNumDivisions * 8, 1);
        i = 0;
        do {
            status = TDbCompilePerformOp(0, "fetch from \x8a 'DIGD' into \x82 and 'DIGC' into \x82\n", &cursor,
                                         &_DbLeague_pDivisions[i][0], &_DbLeague_pDivisions[i][1]);
            i++;
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

void DbLeagueFreeDivisions(void)
{
    if (_DbLeague_pDivisions != 0) {
        DbUtilFree(_DbLeague_pDivisions);
        _DbLeague_pDivisions = 0;
        _DbLeague_iNumDivisions = 0;
    }
}

int DbLoadTeamList(void)
{
    struct QueryCursor cursor;
    struct QueryResult result;
    unsigned short i;
    int status = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    status = TDbCompilePerformOp(&result, "declare \x8a cursor for select * from 'MAET' where ('PYTT' >= \x82) and ('PYTT' <= \x82) and ('PYTT' != \x82) order by 'DROT' asc\n",
                                 &cursor, 0, 8, 1);
    _DbLeague_iNumTeams = result.mUnknown0;
    if (status == 0 && _DbLeague_iNumTeams != 0) {
        _DbLeague_pTeams = DbUtilAlloc(_DbLeague_iNumTeams * 12, 1);
        i = 0;
        do {
            status = TDbCompilePerformOp(0, "fetch from \x8a 'DIGT' into \x82 and 'DIGC' into \x82 and 'DIGD' into \x82\n", &cursor,
                                         &_DbLeague_pTeams[i][0], &_DbLeague_pTeams[i][1], &_DbLeague_pTeams[i][2]);
            i++;
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

void DbLeagueFreeTeams(void)
{
    if (_DbLeague_pTeams != 0) {
        DbUtilFree(_DbLeague_pTeams);
        _DbLeague_pTeams = 0;
        _DbLeague_iNumTeams = 0;
    }
}

int DbLeagueLoad(void);
void DbLeagueFree(void);

int DbLeagueModuleInit(void)
{
    return DbLeagueLoad();
}

void DbLeagueModuleShutdown(void)
{
    DbLeagueFree();
}

int DbLeagueLoad(void)
{
    int result;
    if (_DbLeague_pConferences != 0) {
        DbLeagueFreeConferences();
    }
    if (_DbLeague_pDivisions != 0) {
        DbLeagueFreeDivisions();
    }
    if (_DbLeague_pTeams != 0) {
        DbLeagueFreeTeams();
    }
    result = DbLoadConferenceIds();
    if (result == 0) {
        result = DbLoadDivisionIds();
        if (result == 0) {
            result = DbLoadTeamList();
        }
    }
    return result;
}

void DbLeagueFree(void)
{
    DbLeagueFreeTeams();
    DbLeagueFreeDivisions();
    DbLeagueFreeConferences();
}
