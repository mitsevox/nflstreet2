/* The team depth charts ('THCD', and the game copy 'AGCD'): which player stands at each depth
   of each of the 26 positions. Writes a player into a position and depth, places the fourteen
   players of a lineup through the slot-to-position table, and keeps the tables of how deep
   each position goes and which positions stand in for each other. */

#include "game/TDbCompilePerformOp.h"
#include "game/QueryStatus.h"

typedef struct DbThcdSlotPos_t {
    int mSlot;
    int mPosition;
    unsigned char mDepth;
} DbThcdSlotPos_t;

typedef struct DbThcdFallback_t {
    int mPosition;
    signed char mRank;
} DbThcdFallback_t;

static int _DbThcd_iState = 0;

static DbThcdSlotPos_t _DbThcd_aSlotPositions[29] = {
    {0, 0, 0},
    {1, 1, 0},
    {1, 3, 2},
    {1, 4, 1},
    {1, 25, 0},
    {3, 3, 1},
    {3, 4, 0},
    {3, 2, 0},
    {2, 3, 0},
    {2, 4, 2},
    {2, 1, 1},
    {4, 5, 0},
    {5, 7, 0},
    {6, 9, 0},
    {8, 10, 0},
    {7, 12, 0},
    {10, 11, 0},
    {10, 14, 1},
    {10, 13, 0},
    {9, 14, 0},
    {9, 15, 0},
    {9, 18, 0},
    {9, 17, 1},
    {12, 17, 0},
    {12, 15, 1},
    {12, 16, 2},
    {11, 16, 0},
    {13, 16, 1},
    {14, 26, 0}
};

static unsigned short _DbThcd_aMaxDepth[26] = {
    3, 4, 3, 6, 3, 3, 3, 3, 3, 3, 3, 3, 5, 3, 4, 3, 5, 3, 3, 3, 3, 5, 5, 3, 3, 3
};

static DbThcdFallback_t _DbThcd_aFallback[26][10] = {
    {{0, 0}, {3, 1}, {1, 2}, {20, 3}, {19, 4}, {2, 5}, {4, 6}, {31, -1}, {31, -1}, {31, -1}},
    {{1, 0}, {2, 1}, {3, 2}, {4, 3}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}},
    {{2, 0}, {4, 1}, {1, 2}, {14, 3}, {13, 4}, {15, 4}, {12, 5}, {10, 6}, {11, 6}, {31, -1}},
    {{3, 0}, {16, 1}, {1, 2}, {4, 3}, {2, 4}, {17, 5}, {18, 6}, {0, 7}, {31, -1}, {31, -1}},
    {{4, 0}, {2, 1}, {3, 2}, {14, 3}, {13, 4}, {15, 4}, {1, 5}, {31, -1}, {31, -1}, {31, -1}},
    {{5, 0}, {9, 0}, {6, 1}, {8, 1}, {7, 4}, {4, 5}, {2, 6}, {12, 7}, {10, 8}, {11, 8}},
    {{6, 0}, {8, 0}, {5, 1}, {9, 1}, {7, 4}, {4, 5}, {2, 6}, {12, 7}, {10, 8}, {11, 8}},
    {{7, 0}, {6, 1}, {8, 1}, {5, 2}, {9, 2}, {4, 3}, {2, 6}, {12, 7}, {10, 8}, {11, 8}},
    {{8, 0}, {6, 0}, {9, 1}, {5, 1}, {7, 2}, {4, 3}, {2, 6}, {12, 7}, {10, 8}, {11, 8}},
    {{9, 0}, {5, 0}, {8, 1}, {6, 1}, {7, 2}, {4, 3}, {2, 6}, {12, 7}, {10, 8}, {11, 8}},
    {{10, 0}, {11, 0}, {13, 1}, {15, 1}, {14, 2}, {12, 3}, {18, 4}, {31, -1}, {31, -1}, {31, -1}},
    {{11, 0}, {10, 0}, {15, 1}, {13, 1}, {14, 2}, {12, 3}, {18, 4}, {31, -1}, {31, -1}, {31, -1}},
    {{12, 0}, {10, 1}, {11, 1}, {13, 2}, {15, 2}, {14, 3}, {18, 4}, {31, -1}, {31, -1}, {31, -1}},
    {{13, 0}, {15, 0}, {14, 1}, {10, 2}, {11, 2}, {12, 3}, {18, 4}, {31, -1}, {31, -1}, {31, -1}},
    {{14, 0}, {13, 1}, {15, 1}, {10, 2}, {11, 2}, {12, 3}, {18, 4}, {31, -1}, {31, -1}, {31, -1}},
    {{15, 0}, {13, 0}, {14, 1}, {11, 2}, {10, 2}, {12, 3}, {18, 4}, {31, -1}, {31, -1}, {31, -1}},
    {{16, 0}, {17, 1}, {18, 2}, {3, 3}, {13, 4}, {15, 4}, {14, 5}, {31, -1}, {31, -1}, {31, -1}},
    {{17, 0}, {18, 1}, {16, 2}, {3, 3}, {13, 4}, {15, 4}, {14, 5}, {31, -1}, {31, -1}, {31, -1}},
    {{18, 0}, {17, 1}, {16, 2}, {13, 3}, {15, 3}, {14, 4}, {31, -1}, {31, -1}, {31, -1}, {31, -1}},
    {{19, 0}, {20, 1}, {0, 2}, {1, 3}, {2, 4}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}},
    {{20, 0}, {19, 1}, {0, 2}, {1, 3}, {2, 4}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}},
    {{21, 0}, {22, 0}, {16, 0}, {3, 0}, {1, 0}, {17, 0}, {18, 0}, {2, 0}, {4, 0}, {31, -1}},
    {{22, 0}, {21, 0}, {16, 0}, {3, 0}, {1, 0}, {17, 0}, {18, 0}, {2, 0}, {4, 0}, {31, -1}},
    {{23, 0}, {19, 0}, {20, 0}, {0, 0}, {1, 0}, {2, 0}, {31, -1}, {31, -1}, {31, -1}, {31, -1}},
    {{24, 0}, {7, 0}, {6, 0}, {8, 0}, {5, 0}, {9, 0}, {4, -1}, {31, -1}, {31, -1}, {31, -1}},
    {{25, 0}, {1, 0}, {2, 0}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}, {31, -1}}
};

int DbThcdModuleInit(void)
{
    return 0;
}

void DbThcdModuleShutdown(void)
{
    _DbThcd_iState = 0;
}

unsigned short DbThcdGetMaxDepth(int position)
{
    return _DbThcd_aMaxDepth[position];
}

int DbThcdFillFromRoster(int team)
{
    struct QueryCursor cursor;
    int player;
    int position;
    unsigned char flag;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a fastcursor for select 'DIGP' into \x82 and 'SOPP' into \x82 and 'OHFP' into \x83 from 'YALP' where ('DIGT' = \x82)\n",
                              &cursor, &player, &position, &flag, team);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a\n", &cursor);
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return err;
}

int DbThcdSumRatings(int table, int team, int *pTotal)
{
    struct QueryCursor cursor;
    int player;
    int position;
    int rating;
    int err;

    *pTotal = 0;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c where ('DIGT' = \x82) order by 'pedd' asc\n",
                              &cursor, table, team);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a 'DIGP' into \x82 and 'SOPP' into \x82\n", &cursor, &player, &position);
        if (err == 0) {
            err = TDbCompilePerformOp(0, "select 'RVOP' into \x82 from \x8c where ('DIGP' = \x82)\n", &rating, 0x59414C50,
                                      player);
            *pTotal += rating;
        }
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return err;
}

int DbThcdSetEntry(int table, int team, int player, int position, int depth)
{
    unsigned char found;
    int result = 0;
    if (depth == 31) {
        result = TDbCompilePerformOp(0, "select max('pedd') into \x80 from \x8c where ('DIGT' = \x82) and ('SOPP' = \x82)\n",
                                     &found, table, team, position);
        if (QUERY_STATUS_ACCEPTED(result) == 1) {
            if (result == 0) {
                depth = found + 1;
            } else {
                depth = 0;
            }
            result = 0;
        }
    }
    if (result == 0 && (unsigned int)depth < _DbThcd_aMaxDepth[position]) {
        result = TDbCompilePerformOp(0, "delete from \x8c where ('DIGT' = \x82) and ('SOPP' = \x82) and ('pedd' = \x82)\n",
                                     table, team, position, depth);
        if (result == 0) {
            result = TDbCompilePerformOp(0, "insert into \x8c set 'DIGT' = \x82 and 'DIGP' = \x82 and 'SOPP' = \x82 and 'pedd' = \x82\n",
                                         table, team, player, position, depth);
        }
    }
    return result;
}

int DbThcdGetPositionPlayers(int table, int team, int position, int *pPlayers, int max)
{
    struct QueryCursor cursor;
    int count = 0;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c where ('DIGT' = \x82) and ('SOPP' = \x82) order by 'pedd' asc\n",
                              &cursor, table, team, position);
    while (err == 0 && count < max) {
        err = TDbCompilePerformOp(0, "fetch from \x8a 'DIGP' into \x82\n", &cursor, &pPlayers[count]);
        if (err == 0) {
            count++;
        }
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return count;
}

int DbThcdGetDepth(int player, int position, int *pDepth)
{
    return TDbCompilePerformOp(0, "select 'pedd' into \x82 from depthTableRef where ('DIGP' = \x82) and ('SOPP' = \x82)\n",
                               pDepth, player, position);
}

int DbThcdRemovePlayerPosition(int table, int player, int position)
{
    return TDbCompilePerformOp(0, "delete from \x8c where ('DIGP' = \x82) and ('SOPP' = \x82)\n", table, player, position);
}

int DbThcdRemovePlayer(int table, int player)
{
    struct QueryCursor cursor;
    int position;
    int depth;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c where ('DIGP' = \x82)\n", &cursor, table, player);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a 'SOPP' into \x82 and 'pedd' into \x82\n", &cursor, &position, &depth);
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return TDbCompilePerformOp(0, "delete from \x8c where ('DIGP' = \x82)\n", table, player);
}

int DbThcdCopyTeam(int dst, int src, int team)
{
    unsigned short count;
    int err = TDbCompilePerformOp(0, "select count(*) into \x81 from \x8c where ('DIGT' = \x82)\n", &count, src, team);

    if (err == 0 && count != 0) {
        err = TDbCompilePerformOp(0, "select into \x8c * from \x8c where ('DIGT' = \x82)\n", dst, src, team);
    }
    return err;
}

int DbThcdRebuildTeam(int table, int team)
{
    struct QueryCursor cursor;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c order by 'RVOP' desc\n", &cursor, 0x59414C50);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a\n", &cursor);
        if (err == 0) {
            err = TDbCompilePerformOp(0, "insert into \x8c set 'DIGT' = \x82 and 'SOPP' = \x81 and 'DIGP' = \x82 and 'pedd' = \x81\n",
                                      table, team, 0, 0, 0);
        }
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return TDbCompilePerformOp(0, "delete from \x8c where ('DIGT' = \x82)\n", table, team);
}

int DbThcdReadTeam(int table, int team, int *pPlayers, int *pPositions, int *pDepths)
{
    struct QueryCursor cursor;
    int position;
    int i = 0;
    int err;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    err = TDbCompilePerformOp(0, "declare \x8a cursor for select * from \x8c inner join \x8c on (\x8c.'DIGP' = \x8c.'DIGP') where (\x8c.'DIGT' = \x82) order by \x8c.'pedd' asc\n",
                              &cursor, table, 0x59414C50, table, 0x59414C50, table, team, table);
    while (err == 0) {
        err = TDbCompilePerformOp(0, "fetch from \x8a \x8c.'DIGP' into \x82 and \x8c.'SOPP' into \x82 and \x8c.'SOPP' into \x82 and \x8c.'pedd' into \x82\n",
                                  &cursor, table, &pPlayers[i], table, &pPositions[i], 0x59414C50, &position, table,
                                  &pDepths[i]);
        i++;
    }
    if (cursor.mUnknown0 != 0) {
        TDbSQLDestroyCursor(&cursor);
    }
    return err;
}

int DbThcdGetFallbackPosition(int position, int index)
{
    if ((unsigned short)index > 9) {
        return 31;
    }
    return _DbThcd_aFallback[position][index].mPosition;
}

int DbThcdBeginGame(int home, int away, int mode, int arg)
{
    return 0;
}

int DbThcdResumeGame(int home, int away, int homeCshg, int awayCsag)
{
    return 0;
}

int DbThcdSetSlotPlayer(int table, int team, int player, int slot)
{
    unsigned char i = 0;
    int value;
    int result = 0;
    do {
        value = _DbThcd_aSlotPositions[i].mSlot;
        if (value == slot) {
            result = DbThcdSetEntry(table, team, player, _DbThcd_aSlotPositions[i].mPosition,
                                    _DbThcd_aSlotPositions[i].mDepth);
        }
        i++;
    } while (value != 14);
    return result;
}

int DbThcdSetLineup(int team, int *pPlayers, int table)
{
    DbThcdSetSlotPlayer(table, team, pPlayers[0], 0);
    DbThcdSetSlotPlayer(table, team, pPlayers[1], 1);
    DbThcdSetSlotPlayer(table, team, pPlayers[2], 2);
    DbThcdSetSlotPlayer(table, team, pPlayers[3], 3);
    DbThcdSetSlotPlayer(table, team, pPlayers[4], 4);
    DbThcdSetSlotPlayer(table, team, pPlayers[5], 5);
    DbThcdSetSlotPlayer(table, team, pPlayers[6], 6);
    DbThcdSetSlotPlayer(table, team, pPlayers[7], 7);
    DbThcdSetSlotPlayer(table, team, pPlayers[8], 8);
    DbThcdSetSlotPlayer(table, team, pPlayers[9], 9);
    DbThcdSetSlotPlayer(table, team, pPlayers[10], 10);
    DbThcdSetSlotPlayer(table, team, pPlayers[11], 11);
    DbThcdSetSlotPlayer(table, team, pPlayers[12], 12);
    DbThcdSetSlotPlayer(table, team, pPlayers[13], 13);
    return 0;
}

int DbThcdSetLineups(int home, int *pHomePlayers, int away, int *pAwayPlayers, int table)
{
    DbThcdSetLineup(home, pHomePlayers, table);
    DbThcdSetLineup(away, pAwayPlayers, table);
    return 0;
}
