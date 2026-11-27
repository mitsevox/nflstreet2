/* Team and player table upkeep for the 'TATS' game database: copies a user
   profile's two tables into fresh 'TATS' tables and destroys them again, and
   deletes the created teams (team types 5 and 6) with their players and the
   players of the tournament's teams from a database that is not in use. */
#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

extern "C" {
int DbUserGetDb(int handle);
int TDbTblFindUnusedId(int handle, int *pTable);
int TDbTblDestroy(int handle, int table);
int TDbExists(int handle);
void PortraitFreeAllSlots(void);
int TournamentGetTeamList(int *pList);

void TeamTablesCopy(int database, int firstTable, int secondTable,
                int *pFirstCopy, int *pSecondCopy)
{
    int source = DbUserGetDb(database);
    TDbTblFindUnusedId(0x54415453, pFirstCopy);
    TDbCompilePerformOp(0, "use \x8c select into \x8c.\x8c * from \x8c\n", source, 0x54415453, *pFirstCopy, firstTable);
    TDbTblFindUnusedId(0x54415453, pSecondCopy);
    TDbCompilePerformOp(0, "use \x8c select into \x8c.\x8c * from \x8c\n", source, 0x54415453, *pSecondCopy, secondTable);
}

void TeamTablesDestroy(int firstTable, int secondTable)
{
    TDbTblDestroy(0x54415453, firstTable);
    TDbTblDestroy(0x54415453, secondTable);
}

void TeamTablesDeleteTeamPlayers(int handle, int team)
{
    if (TDbExists(handle) == 0) {
        TDbCompilePerformOp(0, "use \x8c delete from 'YALP' where 'DIGT' = \x82\n", handle, team);
    }
}

void TeamTablesPurgeCreated(int handle)
{
    QueryCursor cursor;
    int teams[8];
    int team;
    if (TDbExists(handle) == 0) {
        PortraitFreeAllSlots();
        int status = TDbCompilePerformOp(0, "use \x8c declare \x8a cursor for select 'DIGT' from 'MAET' where 'PYTT' = \x82 or 'PYTT' = \x82\n", handle, &cursor, 6, 5);
        while (status == 0) {
            status = TDbCompilePerformOp(0, "fetch from \x8a 'DIGT' into \x85\n", &cursor, &team);
            if (status == 0) {
                status = TDbCompilePerformOp(0, "use \x8c delete from 'YALP' where 'DIGT' = \x82\n", handle, team);
            }
        }
        if (QUERY_STATUS_ACCEPTED(status) == true) {
            if (cursor.mUnknown0) {
                status = TDbSQLDestroyCursor(&cursor);
            } else {
                status = 0;
            }
        } else {
            if (cursor.mUnknown0) {
                TDbSQLDestroyCursor(&cursor);
            }
        }
        if (status == 0) {
            status = TDbCompilePerformOp(0, "use \x8c delete from 'MAET' where 'PYTT' = \x82 or 'PYTT' = \x82\n", handle, 6, 5);
            if (QUERY_STATUS_ACCEPTED(status) == true) {
                status = 0;
            }
            if (status == 0) {
                status = TDbCompilePerformOp(0, "use \x8c delete from 'YALP' where 'YTRP' = \x82 or 'YTRP' = \x82\n", handle, 1, 2);
                if (QUERY_STATUS_ACCEPTED(status) == true) {
                    status = 0;
                }
            }
        }
        int count = TournamentGetTeamList(teams);
        for (int i = 0; i < count; i++) {
            TeamTablesDeleteTeamPlayers(0x54415453, teams[i]);
        }
    }
}
}
