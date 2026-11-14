/* Game-database access for the controller ports: the 'OCMT' table that says which side (team 0
   or 1) each port plays for, and the 'LRTC' table that holds the player each port controls.
   Opens and walks the port rows, counts the ports with a player on a side, finds a side's port,
   and sets or reads a port's controlled player. */
#include "game/DbCursor.h"
#include "game/DbSortKey.h"

extern "C" {
unsigned char PortDbCountSidePlayers(int team);
int PortDbHasSides(void);
int GameTextGetPadPlayer(int value);
void fn_801F9718(int handle, int table, DbColumnValue *pList, int *pResult, int flags);
int fn_801F9A90(int handle, int table);
}

static DbSortKey _PortDb_aSideSortKeys[2] = {
    {0x4F434D54, 0x6469676C, 0, 0},
    {-1, -1, 3, 0}
};

extern "C" {

void PortDbOpenSides(DbCursor *pCursor)
{
    DbCursorOpenTable(pCursor, 0x4F434D54, -1);
}

void PortDbCloseSides(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int PortDbGetPort(DbCursor *pCursor)
{
    return DbCursorGetValue(pCursor, 0x6469676C);
}

int PortDbGetSide(DbCursor *pCursor)
{
    return DbCursorGetValue(pCursor, 0x554E4C53);
}

int PortDbSideHasPlayers(int team)
{
    int result;
    if (PortDbHasSides()) {
        result = PortDbCountSidePlayers(team) != 0;
    } else {
        result = team == 0;
    }
    return result;
}

unsigned char PortDbCountSidePlayers(int team)
{
    DbCursor cursor;
    unsigned char count = 0;
    PortDbOpenSides(&cursor);
    int valid = DbCursorFirst(&cursor);
    while (valid) {
        int value = PortDbGetPort(&cursor);
        if (PortDbGetSide(&cursor) == team && GameTextGetPadPlayer(value) != -1) {
            count++;
        }
        valid = DbCursorNext(&cursor);
    }
    PortDbCloseSides(&cursor);
    return count;
}

unsigned char PortDbGetSidePort(int team)
{
    DbCursor cursor;
    unsigned char result = 255;
    DbCursorOpen(&cursor, 0x4F434D54, 0x6469676C, _PortDb_aSideSortKeys, 0, 0x454D4147);
    if (DbCursorFindInt(&cursor, 0x554E4C53, team, 0, 0)) {
        result = DbCursorGetInt(&cursor, 0x6469676C);
    }
    DbCursorClose(&cursor);
    return result;
}

void PortDbSetControlledPlayer(int key, int value)
{
    DbCursor cursor;
    DbCursor *pCursor = &cursor;
    DbCursorOpen(pCursor, 0x4C525443, 0x6469676C, 0, 0, 0x454D4147);
    if (!DbCursorFindValue(pCursor, 0x6469676C, key, 0, 0)) {
        DbColumnValue columns[4];
        int result[4];
        columns[0].mColumnTag = 0x6469676C;
        columns[0].mTableTag = 0x4C525443;
        columns[0].mValue = key;
        columns[1].mColumnTag = 0x44494755;
        columns[1].mTableTag = 0x4C525443;
        columns[1].mValue = 0;
        columns[2].mColumnTag = 0x44494750;
        columns[2].mTableTag = 0x4C525443;
        columns[2].mValue = value;
        columns[3].SetEnd();
        fn_801F9718(pCursor->mUnknown4, pCursor->mUnknown8, columns, result, 0);
    } else {
        DbCursorSetValue(pCursor, 0x44494750, value);
    }
    DbCursorClose(&cursor);
}

int PortDbGetControlledPlayer(int key)
{
    int result = -1;
    DbCursor cursor;
    DbCursorOpen(&cursor, 0x4C525443, 0x6469676C, 0, 0, 0x454D4147);
    if (DbCursorFindValue(&cursor, 0x6469676C, key, 0, 0)) {
        result = DbCursorGetValue(&cursor, 0x44494750);
    }
    DbCursorClose(&cursor);
    return result;
}

int PortDbHasSides(void)
{
    return fn_801F9A90(0, 0x4F434D54) == 0;
}

}
