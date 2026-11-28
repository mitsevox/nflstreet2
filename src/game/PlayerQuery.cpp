/* Player table queries: finds free player ids and creates a new player record, opens player cursors
   filtered by team or other columns for the roster screens, copies a team's player rows between the
   game and profile databases, and runs the three position-group fastcursors the team pick screen
   walks. */

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/PlayerCreateRecord.h"
#include "game/DbQuery.h"
#include "game/TDbCompilePerformOp.h"

extern "C" {
extern int lbl_802D68D0[];
extern int lbl_802D6950[];
extern int lbl_802D6990[];
int TDbTblDefaultDbGet(void);
int _TDbQrySelect(int, DbTableRef *, DbExpression *, void *, int *, DbQueryResult *);
int TDbQryDestroy(int);
int DbFileTblLoad(int, int);
int DbFileTblDestroy(int, int);
int DbUserGetId(int);
int DbUserGetDb(int);
void PlayerRecordSetDefaults(PlayerCreateRecord_t *);
void PlayerRecordRandomName(PlayerCreateRecord_t *);
void PlayerRecordRandomFace(PlayerCreateRecord_t *);
void PlayerRecordRandomAttributes(PlayerCreateRecord_t *);
void PlayerRecordFixup(PlayerCreateRecord_t *);
void PlayerRecordInsert(int, PlayerCreateRecord_t *, int, int);
void SndgMusicPumpFrame(int);
}

/* These fast cursors are also accessed by the selector, fetch and close
   functions below. The halfword at +4 can be overwritten independently. */
extern "C" {
QueryCursor _PlayerQuery_sTeamsCursor;
QueryCursor _PlayerQuery_sTeam34Cursor;
QueryCursor _PlayerQuery_sPrtyCursor;
}

extern "C" int PlayerRecordFindFreeIds(int db, int table, int *out, unsigned short *count, int start)
{
    int result = 0;
    QueryCursor cursor;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int row;
    if (start < 0)
        result = TDbCompilePerformOp(0, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c order by 'DIGP' asc\n", db, &cursor, &row, table);
    else
        result = TDbCompilePerformOp(0, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c where 'DIGP' >= \x82 order by 'DIGP' asc\n", db, &cursor, &row, table, start);
    int previous = start;
    int high = 0x7FFF;
    int next = -1;
    unsigned short filled = 0;
    while (result == 0 && filled < *count) {
        result = TDbCompilePerformOp(0, "fetch from \x8a\n", &cursor);
        if (result == 0) {
            if (row > previous + 1) {
                next = previous + 1;
                for (;;) {
                    if (result != 0 || next >= row || filled >= *count || next > 0x7F14) goto gap_done;
                    out[filled] = next;
                    filled++;
                    next++;
                }
            gap_done:;
            }
            if (next > row) high = next; else high = row;
            previous = row;
        }
    }
    int valid = 0;
    if (result == 0 || result == 23 || result == 21 || result == 20) valid = 1;
    if (valid == 1) {
        if (cursor.mUnknown0 != 0) result = TDbSQLDestroyCursor(&cursor);
        else result = 0;
    } else if (cursor.mUnknown0 != 0) TDbSQLDestroyCursor(&cursor);
    if (result == 0 && filled < *count) {
        if (high == 0x7FFF) next = 0; else next = high + 1;
        for (;;) {
            if (filled >= *count || next > 0x7F14) goto fill_done;
            out[filled] = next;
            filled++;
            next++;
        }
    fill_done:;
    }
    *count = filled;
    return result;
}

extern "C" int PlayerRecordCreate(int source, int value, int reset, int start)
{
    char first[16], last[16], other[16];
    PlayerCreateRecord_t record;
    first[0] = 0;
    last[0] = 0;
    PlayerRecordSetDefaults(&record);
    record.mUnknown04 = first;
    record.mUnknown08 = last;
    record.mUnknown0C = other;
    unsigned short count = 1;
    PlayerRecordFindFreeIds(0x54415453, 0x59414C50, &record.mUnknown00, &count, start);
    record.mUnknown10 = value;
    record.mUnknown14 = value;
    PlayerRecordRandomName(&record);
    SndgMusicPumpFrame(0);
    PlayerRecordRandomFace(&record);
    SndgMusicPumpFrame(0);
    PlayerRecordRandomAttributes(&record);
    SndgMusicPumpFrame(0);
    PlayerRecordFixup(&record);
    SndgMusicPumpFrame(0);
    if (reset) {
        // FAKEMATCH: store order; mUnknown18 is cleared last (the first scheduling pass then puts it fourth, as in the target)
        record.mUnknown10C = 0x41;
        record.mUnknown118 = 2;
        record.mUnknown1C = 1;
        record.mUnknown110 = 0;
        record.mUnknownC8 = 0;
        record.mUnknownC4 = 0;
        record.mUnknownCC = 0;
        record.mUnknownD0 = 0;
        record.mUnknownD4 = 0;
        record.mUnknownD8 = 0;
        record.mUnknownDC = 0;
        record.mUnknownE0 = 0;
        record.mUnknownE4 = 0;
        record.mUnknownE8 = 0;
        record.mUnknownB8 = 0;
        record.mUnknownBC = 0;
        record.mUnknownC0 = 0;
        record.mUnknownA8 = 0;
        record.mUnknownAC = 0;
        record.mUnknownB0 = 0;
        record.mUnknownB4 = 0;
        record.mUnknown6C = 0;
        record.mUnknown70 = 0;
        record.mUnknown74 = 0;
        record.mUnknown84 = 0;
        record.mUnknown88 = 0;
        record.mUnknown8C = 0;
        record.mUnknown90 = 0;
        record.mUnknown94 = 0;
        record.mUnknown98 = 0;
        record.mUnknown9C = 0;
        record.mUnknown18 = 0;
    }
    SndgMusicPumpFrame(0);
    PlayerRecordInsert(0x59414C50, &record, source, 0x1AD);
    SndgMusicPumpFrame(0);
    return record.mUnknown00;
}

/* The query cursor identities are distinct in adjacent source. These
   wrappers use the common query entry point with this caller's object. */
extern "C" void PlayerCursorOpenAll(Object_8008044C *p, void *arg, int flags)
{
    DbCursorOpen(reinterpret_cast<DbCursor *>(p), 0x59414C50, 0x44494750, arg, 0, flags);
}
extern "C" void PlayerCursorOpenByTeam(Object_8008044C *p, void *arg, int selector, int flags)
{
    DbFilter node;
    node.Set(6, 0x59414C5044494754LL, 3, selector);
    DbCursorOpen(reinterpret_cast<DbCursor *>(p), 0x59414C50, 0x44494750, arg, &node, flags);
}
extern "C" void PlayerCursorOpenByPlig(Object_8008044C *p, void *arg, int flags)
{
    DbFilter node;
    // FAKEMATCH: the operand value is held in a local, as the selector parameter of the sibling wrappers is
    int selector = 1;
    node.Set(6, 0x59414C5047494C50LL, 3, selector);
    DbCursorOpen(reinterpret_cast<DbCursor *>(p), 0x59414C50, 0x44494750, arg, &node, flags);
}
extern "C" void PlayerCursorOpenByPrty(Object_8008044C *p, void *arg, int selector, int flags)
{
    DbFilter node;
    node.Set(6, 0x59414C5059545250LL, 3, selector);
    DbCursorOpen(reinterpret_cast<DbCursor *>(p), 0x59414C50, 0x44494750, arg, &node, flags);
}
extern "C" void PlayerCursorOpenByTeamAndId(Object_8008044C *p, void *arg, int selector, int value, int flags)
{
    DbFilter root, left, right;
    root.Set(11, &left, &right);
    left.Set(6, 0x59414C5044494754LL, 3, selector);
    right.SetUnknown32(6, 0x59414C5044494750LL, 3, 0x10006);
    right.mUnknown16.mValue.mInt = value;
    DbCursorOpen(reinterpret_cast<DbCursor *>(p), 0x59414C50, 0x44494750, arg, &root, flags);
}
extern "C" void PlayerRecordWriteById(int value, int handle, int table, DbColumnValue *columns)
{
    DbQueryResult result;
    DbTableRef tables[2];
    DbExpression node;
    tables[0].Set(table, 2, &node);
    tables[1].Set(-1);
    unsigned long long column = 0x44494750;
    node.Set(6, ((unsigned long long)table << 32) | column, 3, value);
    TDbQrySetFirstRow(handle, tables, 0, columns, &result, 0);
}

extern "C" void PlayerRecordCopyTeam(int selector, int index, int mode)
{
    if (index == -1 && mode == 0) return;
    int cursor = 0;
    int source, destination, from, to;
    int created = 0;
    if (mode) {
        from = 0x52475250;
        if (index == -1) {
            source = 0x54415453;
            DbFileTblLoad(source, from);
            created = 1;
        } else source = DbUserGetDb(DbUserGetId(index));
        destination = 0x54415453;
        to = 0x59414C50;
    } else {
        destination = DbUserGetDb(DbUserGetId(index));
        source = 0x54415453;
        from = 0x59414C50;
        to = 0x52475250;
    }
    DbTableRef tables[2];
    DbColumnValue columns[24];
    DbExpression node;
    for (int i = 0; i < 22; ++i) columns[i].Set(from, lbl_802D68D0[i], 0);
    columns[22].Set(from, 0x44494750);
    columns[22].mValue = 0;
    columns[23].SetEnd();
    if (selector == 0x3FF) tables[0].Set(from);
    else {
        unsigned long long column = 0x44494754;
        node.Set((static_cast<unsigned long long>(static_cast<unsigned int>(from)) << 32) | column, 0x10003, selector);
        tables[0].Set(from, 2, &node);
    }
    tables[1].Set(-1);
    DbQueryResult status;
    int result = _TDbQrySelect(source, tables, 0, 0, &cursor, &status);
    if (result != 0) {
        if (result == 23) goto done;
    }
    if (result != 23) {
        if (TDbQryRetrieve(cursor, 1, 0, columns) == 0) {
            do {
                for (int i = 21; i >= 0; --i) columns[i].mTableTag = to;
                columns[22].mColumnTag = -1;
                columns[22].mTableTag = -1;
                PlayerRecordWriteById(columns[22].mValue, destination, to, columns);
                for (int i = 21; i >= 0; --i) columns[i].mTableTag = from;
                columns[22].mColumnTag = 0x44494750;
                columns[22].mTableTag = from;
            } while (TDbQryRetrieve(cursor, 0, 1, columns) == 0);
        }
    }
done:
    TDbQryDestroy(cursor);
    if (created) DbFileTblDestroy(0x54415453, from);
}

extern "C" void PlayerCursorOpenDefault(Object_8008044C *p, Desc_8008044C *desc)
{
    int tag = TDbTblDefaultDbGet();
    PlayerCursorOpen(p, desc, tag);
}
extern "C" void PlayerCursorOpen(Object_8008044C *p, Desc_8008044C *desc, int tag)
{
    void *arg = 0;
    Desc_8008044C local;
    if (desc) {
        local.mUnknown0 = desc->mUnknown0;
        local.mUnknown4 = desc->mUnknown4;
        local.mUnknown8 = desc->mUnknown8;
        local.mUnknown12 = desc->mUnknown12;
    }
    switch (local.mUnknown0) {
    // FAKEMATCH: the empty case 0 leaves no compare in the target; it only shapes the dispatch tree
    case 0: break;
    case 1: arg = lbl_802D6950; break;
    case 2: arg = lbl_802D6990; break;
    }
    switch (local.mUnknown4) {
    case 0: PlayerCursorOpenAll(p, arg, tag); break;
    case 1: PlayerCursorOpenByTeam(p, arg, local.mUnknown8, tag); break;
    case 2: PlayerCursorOpenByPlig(p, arg, tag); break;
    case 3: PlayerCursorOpenByPrty(p, arg, local.mUnknown8, tag); break;
    case 4: PlayerCursorOpenByTeamAndId(p, arg, local.mUnknown8, local.mUnknown12, tag); break;
    }
}
extern "C" void PlayerCursorClose(Object_8008044C *p)
{
    DbCursorClose(reinterpret_cast<DbCursor *>(p));
}

extern "C" int PlayerQueryOpen(int *id, int *pos, int *value, int a, int b, int c, int mode)
{
    DbQueryResult result;
    result.mCount = 0;
    if (static_cast<unsigned int>(b) > 15) b = a;
    if (static_cast<unsigned int>(c) > 15) c = a;
    switch (mode) {
    case 0:
        _PlayerQuery_sTeamsCursor.mUnknown0 = 0;
        _PlayerQuery_sTeamsCursor.mUnknown4 = 0;
        _PlayerQuery_sTeamsCursor.mUnknown8 = -1;
        _PlayerQuery_sTeamsCursor.mUnknown12 = 0;
        if (a != 255 && a != -1)
            TDbCompilePerformOp(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where (('OPBP' = \x82) or ('OPBP' = \x82) or ('OPBP' = \x82)) and ('DIGT' >= 1 && 'DIGT' <= 32) order by 'DIGP' asc\n", &_PlayerQuery_sTeamsCursor, id, pos, value, a, b, c);
        else
            TDbCompilePerformOp(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where ('DIGT' >= 1 && 'DIGT' <= 32) order by 'DIGP' asc\n", &_PlayerQuery_sTeamsCursor, id, pos, value);
        break;
    case 1:
        _PlayerQuery_sTeam34Cursor.mUnknown0 = 0;
        _PlayerQuery_sTeam34Cursor.mUnknown4 = 0;
        _PlayerQuery_sTeam34Cursor.mUnknown8 = -1;
        _PlayerQuery_sTeam34Cursor.mUnknown12 = 0;
        if (a != 255 && a != -1)
        {
            // FAKEMATCH: dead self-increment of a dead status keeps the target's dead cmpwi r3,0 after this call
            int status = TDbCompilePerformOp(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where (('OPBP' = \x82) or ('OPBP' = \x82) or ('OPBP' = \x82)) and ('DIGT' = \x82) order by 'DIGP' asc\n", &_PlayerQuery_sTeam34Cursor, id, pos, value, a, b, c, 34);
            if (status != 0) status++;
        }
        else
        {
            // FAKEMATCH: dead self-increment of a dead status keeps the target's dead cmpwi r3,0 after this call
            int status = TDbCompilePerformOp(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where ('DIGT' = \x82) order by 'DIGP' asc\n", &_PlayerQuery_sTeam34Cursor, id, pos, value, 34);
            if (status != 0) status++;
        }
        break;
    case 2:
        _PlayerQuery_sPrtyCursor.mUnknown0 = 0;
        _PlayerQuery_sPrtyCursor.mUnknown4 = 0;
        _PlayerQuery_sPrtyCursor.mUnknown8 = -1;
        _PlayerQuery_sPrtyCursor.mUnknown12 = 0;
        if (a != 255 && a != -1)
        {
            // FAKEMATCH: dead self-increment of a dead status keeps the target's dead cmpwi r3,0 after this call
            int status = TDbCompilePerformOp(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where (('OPBP' = \x82) or ('OPBP' = \x82) or ('OPBP' = \x82)) and ('YTRP' = \x82) order by 'DIGP' asc\n", &_PlayerQuery_sPrtyCursor, id, pos, value, a, b, c, 1);
            if (status != 0) status++;
        }
        else
            TDbCompilePerformOp(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 and 'OPBP' into \x82 and 'PXSP' into \x82 from 'YALP' where ('YTRP' = \x82) order by 'DIGP' asc\n", &_PlayerQuery_sPrtyCursor, id, pos, value, 1);
        break;
    }
    return result.mCount;
}
extern "C" void PlayerQueryFetch(int which)
{
    switch (which) {
    case 0: TDbCompilePerformOp(0, "fetch from \x8a\n", &_PlayerQuery_sTeamsCursor); break;
    case 1: TDbCompilePerformOp(0, "fetch from \x8a\n", &_PlayerQuery_sTeam34Cursor); break;
    case 2: TDbCompilePerformOp(0, "fetch from \x8a\n", &_PlayerQuery_sPrtyCursor); break;
    }
}
extern "C" void PlayerQuerySetRow(unsigned short value, int which)
{
    switch (which) {
    case 0: _PlayerQuery_sTeamsCursor.mUnknown4 = value; break;
    case 1: _PlayerQuery_sTeam34Cursor.mUnknown4 = value; break;
    case 2: _PlayerQuery_sPrtyCursor.mUnknown4 = value; break;
    }
}
extern "C" void PlayerQueryClose(int which)
{
    switch (which) {
    case 0: if (_PlayerQuery_sTeamsCursor.mUnknown0) TDbSQLDestroyCursor(&_PlayerQuery_sTeamsCursor); break;
    case 1: if (_PlayerQuery_sTeam34Cursor.mUnknown0) TDbSQLDestroyCursor(&_PlayerQuery_sTeam34Cursor); break;
    case 2: if (_PlayerQuery_sPrtyCursor.mUnknown0) TDbSQLDestroyCursor(&_PlayerQuery_sPrtyCursor); break;
    }
}
