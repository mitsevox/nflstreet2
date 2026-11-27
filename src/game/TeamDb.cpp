/* Game-database helpers for teams and the music playlist: opens, filters
   and reads the team table (name, logo, colours, type), creates new teams
   with a random logo, colours and name and fills them with created players,
   loads a team's depth chart onto a side of the field, and keeps the saved
   EA Trax playlist rows. */
#include <string.h>

#include "game/DbCursor.h"
#include "game/Query_8008352C.h"
#include "game/Object_8008044C.h"
#include "game/AutoDepth.h"
#include "game/DepthChartSide.h"
#include "game/fn_801D2B7C.h"
#include "game/TDbQryDeleteRow.h"
#include "game/TDbCompilePerformOp.h"
#include "game/SyncRandGetRange.h"

extern "C" {
void PlyrObjsSetTeamIds(unsigned char side, int *pList);
int TDbTblDestroy(int handle, int table);
void TDbInsertRow(int handle, int table, DbColumnValue *pList, int *pResult, int flags);
int TDbTblFindUnusedId(int handle, int *pTable);
int TDbTblExists(int a, int tag);
int MemFill(void *pDest, int size, int value, int width);
int TDbTblColGetInfo(int handle, int table, int column, int *pInfo);
void FESndUpdate(int a);
int DbCursorGetRow(DbCursor *pObject);
int DbCursorGetValue(DbCursor *pObject, int key);
void GameInfoSet(int index, int value);
void PlayerNamesOpen(void);
void PlayerNamesClose(void);
int PlayerCreateRandom(int a, int b);
int PlayerCreateAtPosition(int a, int b, int c);
void *UIGLibraryGetGlobal(int index);
int UIGLibraryLoadItem(void *pObject, int a, int b);
int UIGLibraryUnLoadItem(void *pObject, int a, int b);
int DbFindUnusedPlayerIds(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022A508(int a, int b, int c, int d, int e);
int DbFindUnusedTeamIds(int handle, int table, int *pIds, unsigned short *pCount);
int DbUtilRandomRange(unsigned int low, unsigned int high);
void DbFnigSetHomeOffPlaybook(int a);
void DbFnigSetHomeDefPlaybook(int a);
void DbFnigSetAwayOffPlaybook(int a);
void DbFnigSetAwayDefPlaybook(int a);
int DbFileTblLoad(int a, int tag);
int DbFileTblDestroy(int a, int tag);
int SyncRandGetIntRange(int stream, int low, int high);
}

static int _TeamDb_aPlaylistSortKeys[8] = { 0x54534C50, 0x44494E53, 0, 0, -1, -1, 3, 0 };
static int _TeamDb_aColorColumns[3] = { 0x31434D54, 0x32434D54, 0x33434D54 };
static int _TeamDb_aTeamSortKeys[8] = { 0x4D414554, 0x44524F54, 0, 0, -1, -1, 3, 0 };
static int _TeamDb_aPositionColumns[14] = {
    0x5A425150, 0x5A425250, 0x46525750, 0x42525750, 0x4C4C4F50, 0x434C4F50, 0x524C4F50,
    0x4C4C4450, 0x524C4450, 0x46424C50, 0x42424C50, 0x4C424450, 0x43424450, 0x52424450,
};

static AutoDepthPlayer_t *_TeamDb_pAutoDepth = 0;
static int _TeamDb_iAutoDepthStream;

extern "C" {

unsigned int PlaylistDbGetFreeKey(DbCursor *pObject)
{
    unsigned int i;

    for (i = 0; i <= 39; i++) {
        if (DbCursorFindInt(pObject, pObject->mUnknown12, i, 0, 0) == 0) {
            break;
        }
    }
    return i;
}

void PlaylistDbOpen(DbCursor *pObject, Query_8008352C *pQuery)
{
    Query_8008352C query;
    void *pColumns = 0;

    if (pQuery) {
        query.mUnknown0 = pQuery->mUnknown0;
        query.mUnknown4 = pQuery->mUnknown4;
        query.mUnknown8 = pQuery->mUnknown8;
    } else {
        query.mUnknown0 = 0;
        query.mUnknown4 = 0;
        query.mUnknown8 = 0;
    }

    switch (query.mUnknown0) {
    case 0:
        pColumns = 0;
        break;
    case 1:
        pColumns = _TeamDb_aPlaylistSortKeys;
        break;
    }

    if (query.mUnknown4 == 0) {
        DbCursorOpen(pObject, 0x54534C50, 0x4B504C50, pColumns, 0, 0x45564153);
    }
}

int PlaylistDbFirst(DbCursor *pObject);
int PlaylistDbNext(DbCursor *pObject);
unsigned char PlaylistDbGetIstx(DbCursor *pObject);
void PlaylistDbDeleteRow(DbCursor *pObject);

void PlaylistDbRemoveStationEntries(DbCursor *pObject)
{
    int more = PlaylistDbFirst(pObject);

    while (more) {
        if (PlaylistDbGetIstx(pObject) == 0) {
            int row = DbCursorGetRow(pObject);
            PlaylistDbDeleteRow(pObject);
            more = DbCursorSeek(pObject, row);
        } else {
            more = PlaylistDbNext(pObject);
        }
    }
}

void PlaylistDbClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int PlaylistDbFirst(DbCursor *pObject)
{
    return DbCursorFirst(pObject);
}

int PlaylistDbNext(DbCursor *pObject)
{
    return DbCursorNext(pObject);
}

int PlaylistDbFindEntry(DbCursor *pObject, int a, int b, int c)
{
    int found = 0;
    int more;

    if (a != 0) {
        for (more = DbCursorFindInt(pObject, 0x58545349, 1, 0, 0); more;
             more = DbCursorFindInt(pObject, 0x58545349, 1, 1, 0)) {
            if (DbCursorGetInt(pObject, 0x44494E53) == c) {
                found = 1;
                break;
            }
        }
    } else {
        for (more = DbCursorFindInt(pObject, 0x44495453, b, 0, 0); more;
             more = DbCursorFindInt(pObject, 0x44495453, b, 1, 0)) {
            if (DbCursorGetInt(pObject, 0x44494E53) == c && DbCursorGetInt(pObject, 0x58545349) == 0) {
                found = 1;
                break;
            }
        }
    }
    return found;
}

int PlaylistDbGetCount(DbCursor *pObject)
{
    return DbCursorGetRowCount(pObject);
}

unsigned char PlaylistDbGetIstx(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x58545349);
}

int PlaylistDbGetStationId(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x44495453);
}

int PlaylistDbGetSongId(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x44494E53);
}

static inline void _FilterSetNodes(DbFilter *pFilter, int kind, DbFilter *pLeft, DbFilter *pRight, int op)
{
    pFilter->mUnknown32 = op;
    pFilter->mUnknown0.mKind = kind;
    pFilter->mUnknown0.mValue.mNode = pLeft;
    pFilter->mUnknown16.mKind = 11;
    pFilter->mUnknown16.mValue.mNode = pRight;
}

static inline void _FilterSetColumn(DbFilter *pFilter, int kind, unsigned int table, unsigned int column,
                                    int valueKind, int value)
{
    pFilter->mUnknown32 = 0x10003;
    pFilter->mUnknown0.mKind = kind;
    pFilter->mUnknown0.mValue.mLong = ((long long)table << 32) | column;
    pFilter->mUnknown16.mKind = valueKind;
    pFilter->mUnknown16.mValue.mInt = value;
}

void PlaylistDbDeleteRow(DbCursor *pObject)
{
    int info[4];
    DbFilter arg;
    QueryResult result;
    DbColumnValue list[2];

    TDbTblColGetInfo(pObject->mUnknown4, pObject->mUnknown8, pObject->mUnknown12, info);
    int column = pObject->mUnknown12;
    list[0].Set(-1, column, 0);
    list[1].SetEnd();
    pObject->Read(list);
    int value = list[0].mValue;

    _FilterSetColumn(&arg, 6, pObject->mUnknown8, pObject->mUnknown12, info[0], value);
    TDbQryDeleteRow(pObject->mUnknown4, (DbQueryTable *)pObject->mUnknown20, &arg, &result, 0);
}

void PlaylistDbAddEntry(DbCursor *pObject, int a, int b, int c)
{
    DbColumnValue list[5];
    int result[4];

    list[0].mColumnTag = 0x4B504C50;
    list[0].mTableTag = 0x54534C50;
    list[0].mValue = PlaylistDbGetFreeKey(pObject);
    list[1].mTableTag = 0x54534C50;
    list[1].mColumnTag = 0x44495453;
    if (a == 0) {
        list[1].mValue = b;
    } else {
        list[1].mValue = -1;
    }
    list[2].mTableTag = 0x54534C50;
    list[2].mColumnTag = 0x44494E53;
    list[2].mValue = c;
    list[3].mColumnTag = 0x58545349;
    list[3].mTableTag = 0x54534C50;
    list[3].mValue = a;
    list[4].SetEnd();
    TDbInsertRow(pObject->mUnknown4, pObject->mUnknown8, list, result, 0);
}

void TeamDbOpenByDgid(DbCursor *pObject, void *pColumns, int tag, int value)
{
    DbFilter arg;

    _FilterSetColumn(&arg, 6, 0x4D414554, 0x44494744, 3, value);
    DbCursorOpen(pObject, 0x4D414554, 0x44494754, pColumns, &arg, tag);
}

void TeamDbOpenTypeZero(DbCursor *pObject, void *pColumns, int tag)
{
    DbFilter arg;
    int value = 0;

    _FilterSetColumn(&arg, 6, 0x4D414554, 0x50595454, 3, value);
    DbCursorOpen(pObject, 0x4D414554, 0x44494754, pColumns, &arg, tag);
}

void TeamDbOpenTypeZeroOrFive(DbCursor *pObject, void *pColumns, int tag)
{
    DbFilter root;
    DbFilter left;
    DbFilter right;

    _FilterSetNodes(&root, 11, &left, &right, 0x2000A);
    left.Set(6, 0x4D41455450595454LL, 3);
    left.mUnknown16.mValue.mInt = 0;
    right.Set(6, 0x4D41455450595454LL, 3);
    right.mUnknown16.mValue.mInt = 5;
    DbCursorOpen(pObject, 0x4D414554, 0x44494754, pColumns, &root, tag);
}

void TeamDbOpenTypeZeroWithLogo(DbCursor *pObject, void *pColumns, int tag, int logo)
{
    DbFilter root;
    DbFilter left;
    DbFilter right;

    root.Set(11, &left, &right);
    left.Set(6, 0x4D41455450595454LL, 3);
    left.mUnknown16.mValue.mInt = 0;
    right.Set(6, 0x4D4145544C474C54LL, 3);
    right.mUnknown16.mValue.mInt = logo;
    DbCursorOpen(pObject, 0x4D414554, 0x44494754, pColumns, &root, tag);
}

void TeamDbOpenByTmur(DbCursor *pObject, void *pColumns, int tag, unsigned char flag)
{
    DbFilter root;
    DbFilter left;
    DbFilter right;
    DbFilter leftLeft;
    DbFilter leftRight;

    root.Set(11, &left, &right);
    left.Set(11, &leftLeft, &leftRight);
    right.SetUnknown32(6, 0x4D41455450595454LL, 3, 0x10006);
    right.mUnknown16.mValue.mInt = 17;
    if (flag) {
        leftLeft.mUnknown16.mValue.mInt = 0;
    } else {
        leftLeft.mUnknown16.mValue.mInt = 1;
    }
    leftLeft.SetUnknown32(6, 0x4D41455452554D54LL, 3, 0x10006);
    leftRight.SetUnknown32(6, 0x4D41455450595454LL, 3, 0x10006);
    leftRight.mUnknown16.mValue.mInt = 2;
    DbCursorOpen(pObject, 0x4D414554, 0x44494754, pColumns, &root, tag);
}

void TeamDbSetPlayersTgti(int id)
{
    TDbCompilePerformOp(0, "use 'TATS' update 'YALP' set 'ITGT' = \x85 where 'DIGT' = \x82\n", id, id);
}

void TeamDbOpenQuery(DbCursor *pObject, TeamQuery *pQuery)
{
    TeamDbOpen(pObject, pQuery, 0);
}

void TeamDbOpen(DbCursor *pObject, TeamQuery *pQuery, int tag)
{
    void *pColumns = 0;
    TeamQuery query;

    if (pQuery) {
        query.mUnknown0 = pQuery->mUnknown0;
        query.mUnknown4 = pQuery->mUnknown4;
        query.mUnknown8 = pQuery->mUnknown8;
    }

    switch (query.mUnknown0) {
    case 0:
        break;
    case 1:
        pColumns = _TeamDb_aTeamSortKeys;
        break;
    }

    switch (query.mUnknown4) {
    case 0:
        DbCursorOpen(pObject, 0x4D414554, 0x44494754, pColumns, 0, tag);
        break;
    case 1:
        TeamDbOpenByTmur(pObject, pColumns, tag, query.mUnknown8);
        break;
    case 2:
        TeamDbOpenByDgid(pObject, pColumns, tag, query.mUnknown8);
        break;
    case 3:
        TeamDbOpenTypeZero(pObject, pColumns, tag);
        break;
    case 4:
        TeamDbOpenTypeZeroOrFive(pObject, pColumns, tag);
        break;
    case 5:
        TeamDbOpenTypeZeroWithLogo(pObject, pColumns, tag, query.mUnknown8);
        break;
    }
}

void TeamDbClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

void TeamDbGetName(DbCursor *pObject, char *pBuffer, int size)
{
    DbCursorGetString(pObject, 0x414E4454, (int)pBuffer, size);
}

int TeamDbGetId(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x44494754);
}

int TeamDbGetToid(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x44494F54);
}

int TeamDbGetType(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x50595454);
}

int TeamDbSeekId(DbCursor *pObject, int id, int *pResult)
{
    return DbCursorFindInt(pObject, 0x44494754, id, 0, pResult);
}

int TeamDbSeekTmur(DbCursor *pObject, int id, int *pResult)
{
    return DbCursorFindInt(pObject, 0x52554D54, id, 0, pResult);
}

void TeamDbGetColors(DbCursor *pObject, unsigned char *pValues)
{
    DbColumnValue list[4];
    int i;

    for (i = 0; i < 3; i++) {
        list[i].Set(0x4D414554, _TeamDb_aColorColumns[i], 0);
    }
    list[3].SetEnd();
    pObject->Read(list);
    for (i = 0; i < 3; i++) {
        pValues[i] = list[i].mValue;
    }
}

int TeamDbGetLogo(DbCursor *pObject)
{
    return DbCursorGetValue(pObject, 0x4C474C54);
}

void TeamDbSetLogo(DbCursor *pObject, int value)
{
    DbCursorSetValue(pObject, 0x4C474C54, value);
}

unsigned char TeamDbGetColor1(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x31434D54);
}

unsigned char TeamDbGetColor2(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x32434D54);
}

unsigned char TeamDbGetColor3(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x33434D54);
}

void TeamDbSetColor1(DbCursor *pObject, unsigned char value)
{
    DbCursorSetInt(pObject, 0x31434D54, value);
}

void TeamDbSetColor2(DbCursor *pObject, unsigned char value)
{
    DbCursorSetInt(pObject, 0x32434D54, value);
}

void TeamDbSetColor3(DbCursor *pObject, unsigned char value)
{
    DbCursorSetInt(pObject, 0x33434D54, value);
}

void TeamDbSetName(DbCursor *pObject, char *pText, int length)
{
    DbCursorSetString(pObject, 0x414E4454, pText, length);
}

int TeamDbGetTrof(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x464F5254);
}

int TeamDbGetTrde(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x45445254);
}

int TeamDbGetTrov(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x564F5254);
}

int TeamDbGetTmur(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x52554D54);
}

int TeamDbGetRandomId(void)
{
    DbCursor cursor;
    TeamQuery query;
    int id;

    query.mUnknown4 = 3;
    TeamDbOpenQuery(&cursor, &query);
    DbCursorSeek(&cursor, (signed char)SyncRandGetIntRange(1, 0, DbCursorGetRowCount(&cursor) - 1));
    id = DbCursorGetValue(&cursor, 0x44494754);
    TeamDbClose(&cursor);
    return id;
}

int TeamDbGetCtdl(DbCursor *pObject)
{
    return DbCursorGetInt(pObject, 0x4C445443) != 0;
}

void TeamDbSetCtdl(DbCursor *pObject, int value)
{
    if (value) {
        DbCursorSetInt(pObject, 0x4C445443, 1);
    } else {
        DbCursorSetInt(pObject, 0x4C445443, 0);
    }
}

int TeamDbInsert(const char *pName, int type, int logo)
{
    unsigned short count = 1;
    int id;

    DbFindUnusedTeamIds(0x54415453, 0x4D414554, &id, &count);
    TDbCompilePerformOp(0,
                "use 'TATS' insert into 'MAET' set 'DIGT' = \x82 and 'PYTT' = \x82 and 'DIOT' = \x82 and "
                "'DROT' = \x82 and 'LGLT' = \x82 and 'SIVT' = \x83 and 'RUMT' = \x85 and 'ANDT' = \x88 and "
                "'LDTC' = \x82\n",
                id, type, id, 0, logo, 1, 3, pName, 1);
    return id;
}

void TeamDbGetRandomLogoColors(int *pLogo, int *pFirst, int *pSecond, int *pThird);
void TeamDbGetRandomName(int logo, char *pName, int size);

int TeamDbCreate(int type, int logo, const char *pName)
{
    char name[33];
    int values[4];
    int id;

    TeamDbGetRandomLogoColors(&values[0], &values[1], &values[2], &values[3]);
    if (logo != -1) {
        values[0] = logo;
    }
    if (pName && strlen(pName)) {
        strncpy(name, pName, 33);
    } else {
        TeamDbGetRandomName(values[0], name, 33);
    }
    values[0] += 45;
    if (values[0] < 46 || values[0] > 132) {
        values[0] = DbUtilRandomRange(46, 133);
    }
    id = TeamDbInsert(name, type, values[0]);
    TDbCompilePerformOp(0, "use 'TATS' update 'MAET' set '1CMT' = \x85 and '2CMT' = \x85 and '3CMT' = \x85 where 'DIGT' = \x85\n",
                values[1], values[2], values[3], id);
    return id;
}

void TeamDbGetRandomLogoColors(int *pLogo, int *pFirst, int *pSecond, int *pThird)
{
    QueryCursor cursor;
    QueryResult result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = TDbCompilePerformOp(&result, "use 'TATS' declare \x8a cursor for select * from 'LTPS'\n", &cursor);
    // FAKEMATCH: dead increment of the unused status; its branch makes a block boundary after the
    // declare call that lasts until after register allocation (flow deletes the increment)
    if (status != 0) status++;
    cursor.mUnknown4 = SyncRandGetIntRange(1, 0, result.mUnknown0 - 1);
    TDbCompilePerformOp(0, "use 'TATS' fetch from \x8a 'LGLT' into \x85 and '1CMT' into \x85 and '2CMT' into \x85 and '3CMT' into \x85\n",
                &cursor, pLogo, pFirst, pSecond, pThird);
    if (cursor.mUnknown0) {
        TDbSQLDestroyCursor(&cursor);
    }
}

void TeamDbGetRandomName(int logo, char *pName, int size)
{
    QueryCursor cursor;
    QueryResult result;
    int flag = 0;

    if (TDbTblExists(0, 0x43544E52)) {
        flag = 1;
        DbFileTblLoad(0, 0x43544E52);
    }
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = TDbCompilePerformOp(&result, "declare \x8a cursor for select * from 'CTNR' where ('LGLT' = \x82)\n", &cursor, logo);
    // FAKEMATCH: dead increment of the unused status, as in TeamDbGetRandomLogoColors
    if (status != 0) status++;
    int count = result.mUnknown0;
    if (count > 0) {
        cursor.mUnknown4 = SyncRandGetIntRange(1, 0, count - 1);
        TDbCompilePerformOp(0, "fetch from \x8a 'ETNR' into \x88\n", &cursor, pName);
    } else {
        strncpy(pName, "Playaz", size);
    }
    if (cursor.mUnknown0) {
        TDbSQLDestroyCursor(&cursor);
    }
    if (flag) {
        DbFileTblDestroy(0, 0x43544E52);
    }
}

void TeamDbCreatePlayers(int a, int *pIds, int *pCounts, int count, int *pOut, int total)
{
    int prev;
    int k;
    int i;
    int j;

    PlayerNamesOpen();
    prev = -1;
    k = 0;
    if (count) {
        for (i = 0; i < count; i++) {
            int n = pCounts[i];

            for (j = 0; j < n; j++) {
                prev = pOut[k] = PlayerCreateAtPosition(pIds[k], a, prev);
                k++;
                FESndUpdate(1);
            }
        }
    }
    while (k < total) {
        prev = pOut[k++] = PlayerCreateRandom(a, prev);
        FESndUpdate(1);
    }
    PlayerNamesClose();
}

void TeamDbAutoPickPlayers(int a, int b, int *pOut, unsigned int count, int *pIn, unsigned int size)
{
    int *pList = (int *)fn_801D2B7C((size + 1) * 4, 0, 0);
    int *pIds = (int *)fn_801D2B7C(count * 4, 0, 0);
    int excluded[15];
    unsigned int i;
    unsigned int j;

    memcpy(pList, pIn, size * 4);
    MemFill(excluded, sizeof(excluded), 0xFF, 4);
    pList[size] = 0x7FFF;
    _TeamDb_iAutoDepthStream = SyncRandGetRange(0, 5);
    AutoDepthBuild(_TeamDb_iAutoDepthStream, pList, &_TeamDb_pAutoDepth);
    for (i = 0; i < count; i++) {
        int id;
        int category;

        AutoDepthSelect(_TeamDb_pAutoDepth, pList, excluded, &id, &category);
        pIds[i] = id;
        excluded[i] = category;
        for (j = 0; j < size; j++) {
            if (id == pList[j]) {
                memmove(&pList[j], &pList[j + 1], (size - j) * 4);
                size--;
            }
        }
    }
    AutoDepthFree(&_TeamDb_pAutoDepth);
    memcpy(pOut, pIds, count * 4);
    fn_801D2BD0(pList);
    fn_801D2BD0(pIds);
}

void TeamDbCopyPlayers(int team, int *pIds, unsigned int count);

void TeamDbLoadSideWithCopies(int team, int *pList, int side, int count)
{
    DepthChartSide_t record;
    DbCursor query;
    Object_8008044C cursor;
    int i;

    PlyrObjsSetTeamIds(side, pList);
    DepthChartGetSide(side, &record);
    TeamDbCopyPlayers(team, record.mUnknown, count);
    TeamDbOpen(&query, 0, 0x54415453);
    TeamDbSeekId(&query, team, 0);
    int type = TeamDbGetType(&query);
    TeamDbClose(&query);
    if (side == 0) {
        GameInfoSet(0, team);
        fn_8022A508(0, team, team, type, -1);
        DbFnigSetHomeOffPlaybook(0);
        DbFnigSetHomeDefPlaybook(0);
    } else {
        GameInfoSet(1, team);
        fn_8022A508(1, team, team, type, -1);
        DbFnigSetAwayOffPlaybook(0);
        DbFnigSetAwayDefPlaybook(0);
    }
    PlayerCursorOpen(&cursor, 0, 0x54415453);
    for (i = 0; i < count; i++) {
        PlayerDbSeekId(&cursor, record.mUnknown[i], 0);
        PlayerDbSetPickedFlag(&cursor, side, 1);
    }
    PlayerCursorClose(&cursor);
}

void TeamDbLoadSide(int team, int *pList, int side, int count)
{
    DepthChartSide_t record;
    DbCursor query;
    Object_8008044C cursor;
    int i;

    PlyrObjsSetTeamIds(side, pList);
    DepthChartGetSide(side, &record);
    TeamDbOpen(&query, 0, 0x54415453);
    TeamDbSeekId(&query, team, 0);
    int type = TeamDbGetType(&query);
    TeamDbClose(&query);
    if (side == 0) {
        GameInfoSet(0, team);
        fn_8022A508(0, team, team, type, -1);
        DbFnigSetHomeOffPlaybook(0);
        DbFnigSetHomeDefPlaybook(0);
    } else {
        GameInfoSet(1, team);
        fn_8022A508(1, team, team, type, -1);
        DbFnigSetAwayOffPlaybook(0);
        DbFnigSetAwayDefPlaybook(0);
    }
    PlayerCursorOpen(&cursor, 0, 0x54415453);
    for (i = 0; i < count; i++) {
        PlayerDbSeekId(&cursor, record.mUnknown[i], 0);
        PlayerDbSetPickedFlag(&cursor, side, 1);
    }
    PlayerCursorClose(&cursor);
}

int TeamDbFindDepthSlot(int id, int half, int *pList);

void TeamDbCopyPlayers(int team, int *pIds, unsigned int count)
{
    int copy[14];
    unsigned short found = count;
    int table = -1;
    int *pNewIds = (int *)fn_801D2B7C(count * 4, 0, 0);
    int *pOldIds = (int *)fn_801D2B7C(count * 4, 0, 0);
    unsigned int i;
    unsigned int j;

    DbFindUnusedPlayerIds(0x54415453, 0x59414C50, pNewIds, &found);
    for (i = 0; i < count; i++) {
        TDbTblFindUnusedId(0x54415453, &table);
        pOldIds[i] = pIds[i];
        TDbCompilePerformOp(0, "use 'TATS' select into \x8c * from 'YALP' where ('DIGP' = \x82)\n", table, pOldIds[i]);
        TDbCompilePerformOp(0, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82 where ('DIGP' = \x82)\n", table, team,
                    pNewIds[i], pOldIds[i]);
        TDbCompilePerformOp(0, "use 'TATS' insert into \x8c.'YALP' * select * from \x8c\n", 0x54415453, table);
        TDbTblDestroy(0x54415453, table);
    }
    for (i = 0; i < 14; i++) {
        copy[i] = pIds[i];
    }
    for (i = 0; i < count; i++) {
        for (j = 0; j <= 1; j++) {
            pIds[TeamDbFindDepthSlot(pOldIds[i], j, copy)] = pNewIds[i];
        }
    }
    fn_801D2BD0(pNewIds);
    fn_801D2BD0(pOldIds);
}

int TeamDbFindDepthSlot(int id, int half, int *pList)
{
    int i = half == 0 ? 7 : 0;
    int end = half == 0 ? 13 : 6;

    for (; i <= end; i++) {
        if (pList[i] == id) {
            break;
        }
    }
    return i;
}

void TeamDbLoadLibraryItem(int value)
{
    UIGLibraryLoadItem(UIGLibraryGetGlobal(1), 4, value);
}

void TeamDbUnloadLibraryItem(int value)
{
    UIGLibraryUnLoadItem(UIGLibraryGetGlobal(1), 4, value);
}

void TstrDbOpen(DbCursor *pObject)
{
    DbCursorOpen(pObject, 0x52545354, 0x59545453, 0, 0, 0x54415453);
}

void TstrDbClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int TstrDbSeek(DbCursor *pObject, int value, int *pResult)
{
    return DbCursorFindInt(pObject, 0x59545453, value, 0, pResult);
}

int TstrDbGetPositionValue(DbCursor *pObject, int category)
{
    return DbCursorGetInt(pObject, _TeamDb_aPositionColumns[category]);
}

}
