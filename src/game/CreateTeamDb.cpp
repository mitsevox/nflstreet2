/* Created team: the team a user builds on the create-a-team screens, kept in
   the created-team tables of each user's save database. Stores the team and
   its players from the game's team and player tables and loads them back,
   creates a new team row and fills it with the players of a team style,
   computes the team's offence, defence and overall ratings from its players,
   adds and removes players, backs the tables up and restores them, and clears
   the team. */
#include "game/fn_801FCE10.h"
#include "game/fn_801F9908.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8022F478.h"
#include "game/DbCursor.h"
#include "game/Query_8008352C.h"
#include "game/DbQueryTable.h"
#include "game/Object_8008044C.h"
#include "game/FaceFeatures.h"
#include "game/FMCAPPORT.h"

extern "C" {
int fn_8022F358(int);
int fn_8022F4BC(void);
int fn_8022F3D4(int);
void CreateTeamClearTables(int);
void CreateTeamUpdateRatings(int);
int fn_801F9980(int, int *);
int fn_801F967C(int, int);
void fn_801F9718(int, int, DbColumnValue *, int *, int);
int fn_801F9D70(int, int, DbFilter *, unsigned short *);
int fn_8022C628(int, int, int *, unsigned short *);
int fn_80229AA4(int, int, int *, unsigned short *);
int MemCardFilesNeedsSave(int, int);
void MemCardFilesStoreChecksum(int, int);
int PortraitAllocSlot(int, int);
int PlayerDbGetHairStyle(Object_8008044C *);
int PlayerDbGetPlht(Object_8008044C *);
int fn_80081E3C(Object_8008044C *);
int fn_80082280(Object_8008044C *);
int fn_800822D4(Object_8008044C *);
int PlayerDbGetPlex(Object_8008044C *);
int PlayerDbGetHairColor(Object_8008044C *);
int PlayerDbGetFacialHairColor(Object_8008044C *);
void fn_8015F638(int, int, int, int *);
void PlaTexCacheGetHairTexture(int, int *, int *);
int PlaTexCacheGetCapFaceId(int);
void fn_8018C48C(int);
void fn_8018C344(int database, int firstTable, int secondTable,
                 int *pFirstCopy, int *pSecondCopy);
void fn_8018C3EC(int firstTable, int secondTable);
int fn_80186F7C(unsigned char);
int fn_80186B38(int);
int GauntletGetCurrentTeam(int);
void GauntletReset(int);
int fn_8022EF8C(int, int);
int fn_8022EFBC(int, int);
void CreateTeamPlayerCursorOpen(DbCursor *pCursor, int index);
void CreateTeamPlayerCursorClose(DbCursor *pCursor);
}

static int _CreateTeamDb_aTeamTags[16] = {
    0x44494754, 0x44494F54, 0x50595454, 0x44524F54, 0x45445254, 0x464F5254, 0x564F5254, 0x4C474C54, 0x49524454, 0x31434D54, 0x32434D54, 0x33434D54, 0x4C445443, 0x414E5354, 0x414E4C54, 0x414E4454
};
static int _CreateTeamDb_aDefaultValues[13] = {
    0x00000000, 0x00000000, 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000066, 0x00000000, 0x00000035, 0x0000003C, 0x00000075, 0x00000001
};
static char *_CreateTeamDb_apNames[3] = {"NEW", "New Team", "New Team"};

static float _CreateTeamDb_afOffenseWeights[10] = {
    0.16f, 0.12f, 0.10f, 0.14f, 0.20f, 0.0f, 0.06f, 0.08f, 0.0f, 0.0f
};
static float _CreateTeamDb_afDefenseWeights[10] = {
    0.12f, 0.0f, 0.0f, 0.0f, 0.11f, 0.26f, 0.0f, 0.0f, 0.23f, 0.23f
};
static float _CreateTeamDb_afOverallWeights[10] = {
    0.27f, 0.10f, 0.06f, 0.12f, 0.28f, 0.18f, 0.05f, 0.06f, 0.14f, 0.14f
};

extern "C" {
void CreateTeamCalcPlayerRatings(int *pRatings, float *pOffense, float *pDefense, float *pOverall)
{
    float offenseWeight = 0.0f;
    float defenseWeight = 0.0f;
    float overallWeight = 0.0f;
    *pOffense = 0.0f;
    *pDefense = 0.0f;
    *pOverall = 0.0f;
    for (int i = 0; i < 10; i++) {
        *pOffense += pRatings[i] * _CreateTeamDb_afOffenseWeights[i];
        offenseWeight += _CreateTeamDb_afOffenseWeights[i];
        *pDefense += pRatings[i] * _CreateTeamDb_afDefenseWeights[i];
        defenseWeight += _CreateTeamDb_afDefenseWeights[i];
        *pOverall += pRatings[i] * _CreateTeamDb_afOverallWeights[i];
        overallWeight += _CreateTeamDb_afOverallWeights[i];
    }
    *pOffense /= offenseWeight;
    *pDefense /= defenseWeight;
    *pOverall /= overallWeight;
}

void CreateTeamCalcRatings(int index, int *pOffense, int *pDefense, int *pOverall)
{
    DbCursor cursor;
    CreateTeamPlayerCursorOpen(&cursor, index);
    int count = DbCursorGetRowCount(&cursor);
    float offenseTotal = 0.0f;
    float defenseTotal = 0.0f;
    float overallTotal = 0.0f;
    if (DbCursorFirst(&cursor)) {
        do {
            int ratings[10];
            float offense;
            float defense;
            float overall;
            PlayerGetGearRatings((Object_8008044C *)&cursor, ratings);
            CreateTeamCalcPlayerRatings(ratings, &offense, &defense, &overall);
            offenseTotal += offense;
            defenseTotal += defense;
            overallTotal += overall;
        } while (DbCursorNext(&cursor));
    }
    double offense = offenseTotal * 1.6 / count;
    if (offense >= 1.0) {
        *pOffense = (int)(offense <= 99.0 ? offense : 99.0);
    } else {
        *pOffense = 1;
    }
    double defense = defenseTotal * 1.6 / count;
    if (defense >= 1.0) {
        *pDefense = (int)(defense <= 99.0 ? defense : 99.0);
    } else {
        *pDefense = 1;
    }
    double overall = overallTotal * 1.6 / count;
    if (overall >= 1.0) {
        *pOverall = (int)(overall <= 99.0 ? overall : 99.0);
    } else {
        *pOverall = 1;
    }
    CreateTeamPlayerCursorClose(&cursor);
}

void CreateTeamUpdateRatings(int index)
{
    int handle = fn_8022F3D4(fn_8022F358(index));
    int offense;
    int defense;
    int overall;
    QueryResult result;
    CreateTeamCalcRatings(index, &offense, &defense, &overall);
    fn_801FCE10(&result,
        "use \x8c update 'MTRC' set 'FORT' = \x82 and 'EDRT' = \x82 and 'VORT' = \x82\n",
        handle, offense, defense, overall);
}

void CreateTeamClearTables(int source)
{
    QueryResult result;
    DbQueryTable tables[2];

    tables[0].Set(0x59505243);
    tables[1].Set(-1);
    fn_801F9908(source, tables, 0, &result, 0);
    tables[0].Set(0x4D545243);
    tables[1].Set(-1);
    fn_801F9908(source, tables, 0, &result, 0);
}
void CreateTeamStore(int source, int team, int index)
{
    QueryResult result;
    int table = -1;
    QueryCursor cursor = {0, 0, -1, 0};
    int player;
    int destination = fn_8022F3D4(fn_8022F358(index));
    CreateTeamClearTables(destination);
    fn_801F9980(destination, &table);
    fn_801FCE10(0, "use \x8c select into \x8c.\x8c * from 'MAET' where ('DIGT' = \x82)\n", source, destination, table, 0);
    fn_801FCE10(0, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", destination, table, 0, 0);
    fn_801FCE10(0, "use \x8c insert into 'MTRC' * select * from \x8c\n", destination, table);
    fn_801F967C(destination, table);
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from 'YALP' where 'DIGT' = \x85 order by 'DIGP'\n", source, &cursor, &player, team);
    unsigned int count = result.mUnknown0;
    for (unsigned int i = 0; i < count; i++) {
        fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        fn_801F9980(destination, &table);
        fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from 'YALP' where ('DIGP' = \x82)\n", source, destination, table, player);
        fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82\n", destination, table, 0, i);
        fn_801FCE10(0, "use \x8c insert into 'YPRC' * select * from \x8c\n", destination, table);
        fn_801F967C(destination, table);
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    CreateTeamUpdateRatings(index);
}

int CreateTeamLoad(int source, int teamTable, int playerTable, int destination,
                int rumt, int *pOriginalIds, int preserveOriginal)
{
    QueryResult result;
    int ids[16];
    unsigned short teamCount = 1;
    unsigned short count;
    int team;
    int table = -1;
    QueryCursor cursor = {0, 0, -1, 0};
    int player;
    fn_8022C628(destination, 0x4D414554, &team, &teamCount);
    fn_801F9980(destination, &table);
    fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where ('DIGT' = \x82)\n", source, destination, table, teamTable, 0);
    fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", destination, table, team, team);
    fn_801FCE10(&result, "use \x8c insert into 'MAET' * select * from \x8c\n", destination, table);
    fn_801F967C(destination, table);
    fn_801FCE10(&result, "use \x8c update 'MAET' set 'RUMT' = \x85 and 'OLFT' = 0 and 'SIVT' = 1 and 'DIGD' = \x82 where ('DIGT' = \x85)\n", destination, rumt, 8, team);
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    int code = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c order by 'DIGP'\n", source, &cursor, &player, playerTable);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        count = result.mUnknown0;
        fn_80229AA4(destination, 0x59414C50, ids, &count);
        for (unsigned int i = 0; i < count; i++) {
            if (destination == 0x54415453) pOriginalIds[i] = ids[i];
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801F9980(destination, &table);
            fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where ('DIGP' = \x82)\n", source, destination, table, playerTable, player);
            if (preserveOriginal) {
                fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIGP' = \x85 where ('DIGP' = \x82)\n", destination, table, team, ids[i], player);
            } else {
                fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIGP' = \x85 and 'DIOP' = \x85 where ('DIGP' = \x82)\n", destination, table, team, ids[i], pOriginalIds[i], player);
            }
            fn_801FCE10(&result, "use \x8c insert into 'YALP' * select * from \x8c\n", destination, table);
            fn_801FCE10(&result, "use \x8c update 'YALP' set 'ITGT' = \x85 where 'DIGP' = \x82\n", destination, team, ids[i]);
            fn_801F967C(destination, table);
        }
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    return team;
}

int CreateTeamLoadAll(int destination, int rumt, int index, int *pOriginalIds, int preserveOriginal)
{
    int source = fn_8022F3D4(fn_8022F358(index));
    return CreateTeamLoad(source, 0x4D545243, 0x59505243, destination, rumt, pOriginalIds, preserveOriginal);
}

void CreateTeamSyncCreatedPlayers(int index)
{
    QueryResult result;
    int player, ytrp, oldPxsp;
    int source = fn_8022F3D4(fn_8022F358(index));
    QueryCursor cursor = {0, 0, -1, 0};
    int hadState = MemCardFilesNeedsSave(2, index);
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    int code = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from 'YPRC' order by 'DIGP'\n", source, &cursor, &player);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        unsigned int count = result.mUnknown0;
        for (unsigned int i = 0; i < count; i++) {
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801FCE10(0, "use \x8c select 'YTRP' into \x85 from 'YPRC' where 'DIGP' = \x82\n", source, &ytrp, player);
            if (ytrp == 1) {
                int mapped = PortraitAllocSlot((unsigned char)index, 0);
                fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 from 'YPRC' where 'DIGP' = \x82\n", source, &oldPxsp, player);
                fn_801FCE10(0, "use \x8c update 'YPRC' set 'PXSP' = \x85 where 'DIGP' = \x82\n", source, mapped, player);
                fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", source, mapped, oldPxsp);
            }
        }
    }
    if (!hadState) MemCardFilesStoreChecksum(2, index);
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
}

int CreateTeamInsertNew()
{
    DbColumnValue list[17];
    unsigned short count = 1;
    int team;
    fn_8022C628(0x54415453, 0x4D414554, &team, &count);
    for (unsigned int i = 0; i < 13; i++) {
        list[i].Set(0x4D414554, _CreateTeamDb_aTeamTags[i]);
        list[i].mValue = _CreateTeamDb_aDefaultValues[i];
    }
    for (unsigned int i = 0; i < 3; i++) {
        list[i + 13].mValue = (int)_CreateTeamDb_apNames[i];
        list[i + 13].Set(0x4D414554, _CreateTeamDb_aTeamTags[i + 13]);
    }
    list[0].mValue = team;
    list[16].SetEnd();
    fn_801F9718(0x54415453, 0x4D414554, list, 0, 0);
    return team;
}

void CreateTeamCopyStylePlayers(int index, int team, int rumt)
{
    DbFilter arg;
    QueryResult result;
    QueryCursor cursor = {0, 0, -1, 0};
    int ids[16];
    unsigned short total, count;
    int saved = fn_8022F4BC();
    fn_8022F478(fn_8022F358(index));
    fn_8022F3D4(fn_8022F358(index));
    arg.Set(6, 0x5244524344494754LL, 2, rumt);
    fn_801F9D70(0x54415453, 0x52445243, &arg, &total);
    count = total;
    fn_80229AA4(0x54415453, 0x59414C50, ids, &count);
    int player, table;
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 from 'RDRC' where 'DIGT' = \x82 order by 'DIGP'\n", &cursor, &player, rumt);
    for (unsigned int i = 0; i < count; i++) {
        fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        fn_801F9980(0x54415453, &table);
        fn_801FCE10(&result, "use 'TATS' select into \x8c * from 'RDRC' where ('DIGP' = \x85)\n", table, player);
        fn_801FCE10(&result, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x85\n", table, team, ids[i]);
        fn_801FCE10(&result, "use 'TATS' insert into 'YALP' * select * from \x8c\n", table);
        fn_801FCE10(0, "use 'TATS' update 'YALP' set 'PXSP' = \x85 where 'DIGP' = \x85\n", i, ids[i]);
        Object_8008044C object;
        FaceFeatures_t block;
        FMCAPPORTValues values;
        FMCAPPORTText text60, text20;
        int resultIds[2], unknown52, unknown56;
        fn_8008044C(&object, 0, 0x54415453);
        PlayerDbSeekId(&object, ids[i], 0);
        int value6E = PlayerDbGetHairStyle(&object);
        int value6C = PlayerDbGetPlht(&object);
        int value72 = fn_80081E3C(&object);
        int value73 = fn_80082280(&object);
        int value74 = fn_800822D4(&object);
        int value76 = PlayerDbGetPlex(&object);
        unsigned int color18 = PlayerDbGetHairColor(&object);
        unsigned int color19 = PlayerDbGetFacialHairColor(&object);
        fn_80082138(&object, &block);
        FaceMorphBuildWeights(&block, &values);
        fn_8015F638(value6E, value6C, 0, resultIds);
        PlaTexCacheGetHairTexture(value6E, &unknown52, &unknown56);
        int unknown8 = PlaTexCacheGetCapFaceId(value72 + 1);
        int unknown12 = value73 * 3 + value74 + 0x33BA;
        fn_801C1F94(&text60, 0, sizeof(text60));
        fn_801C1F94(&text20, 0, sizeof(text20));
        text60.mChars[18] = color18 + 0x80;
        text20.mChars[19] = color19 + 0x80;
        gFMCAPPORT.SetEntry(i, 0xFFFF, unknown8, unknown12, 0xA7, &text20,
            resultIds[0], unknown52, unknown56, &text60, &values, value76);
        fn_8008056C(&object);
        fn_801F967C(0x54415453, table);
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    gFMCAPPORT.Start();
    fn_8022F478(saved);
}

int CreateTeamGetStylePoints(int value)
{
    if (value == 5) return 8000;
    return 200;
}
int CreateTeamExists(int index)
{
    unsigned short count = 0;
    int found = 0;
    fn_801F9D70(fn_8022F3D4(fn_8022F358(index)), 0x4D545243, 0, &count);
    if (count) found = 1;
    return found;
}
int CreateTeamHasPlayers(int index)
{
    unsigned short count = 0;
    int found = 0;
    fn_801F9D70(fn_8022F3D4(fn_8022F358(index)), 0x59505243, 0, &count);
    if (count) found = 1;
    return found;
}
void CreateTeamLoadUserTeams()
{
    int ids[16];
    fn_8018C48C(0x54415453);
    fn_8018C48C(0x454D4147);
    for (unsigned char i = 0; i <= 1; i++) {
        int index = fn_80186F7C(i);
        if (index != -1 && CreateTeamExists(index)) {
            CreateTeamSyncCreatedPlayers(index);
            CreateTeamLoadAll(0x54415453, i, index, ids, 0);
            CreateTeamLoadAll(0x454D4147, i, index, ids, 0);
        }
    }
}
int CreateTeamLoadToStats(int index, int rumt)
{
    int ids[16];
    fn_8018C48C(0x54415453);
    CreateTeamSyncCreatedPlayers(index);
    return CreateTeamLoadAll(0x54415453, rumt, index, ids, 1);
}
void CreateTeamStoreFromStats(int index, int team)
{
    CreateTeamStore(0x54415453, team, index);
}
void CreateTeamClear()
{
    int source = fn_8022F3D4(fn_8022F4BC());
    if (!GauntletGetCurrentTeam(fn_80186B38(fn_8022F4BC())))
        GauntletReset(fn_80186B38(fn_8022F4BC()));
    QueryResult result;
    DbQueryTable tables[2];
    QueryCursor cursor;
    int pxsp, diop, ytrp, selected;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use \x8c declare \x8a cursor for select 'PXSP' and 'DIOP' and 'YTRP' from 'YPRC'\n", source, &cursor);
    for (unsigned int i = 0; i < result.mUnknown0; i++) {
        pxsp = i; diop = 0; ytrp = 0;
        fn_801FCE10(0, "fetch from \x8a 'PXSP' into \x85 and 'DIOP' into \x85 and 'YTRP' into \x85\n", &cursor, &pxsp, &diop, &ytrp);
        if (diop != 0x7FF4 && ytrp == 1)
            fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", source, i, pxsp);
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    if (fn_801FCE10(&result, "use \x8c select 'PXSP' into \x85 from 'YPRC' where 'DIOP' = \x85\n", source, &selected, 0x7FF4) == 0)
        fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", source, 8, selected);
    CreateTeamClearTables(source);
    tables[0].Set(0x4E494843);
    tables[1].Set(-1);
    fn_801F9908(source, tables, 0, &result, 0);
    fn_8022EF8C(0x54415453, 0x4E494843);
    fn_801FCE10(&result, "use 'TATS' insert into \x8c.'NIHC' * select * from 'NIHC'\n", source);
    fn_8022EFBC(0x54415453, 0x4E494843);
    tables[0].Set(0x47504843);
    tables[1].Set(-1);
    fn_801F9908(source, tables, 0, &result, 0);
    fn_8022EF8C(0x54415453, 0x47504843);
    fn_801FCE10(&result, "use 'TATS' insert into \x8c.'GPHC' * select * from 'GPHC'\n", source);
    fn_8022EFBC(0x54415453, 0x47504843);
    tables[0].Set(0x47505443);
    tables[1].Set(-1);
    fn_801F9908(source, tables, 0, &result, 0);
    for (unsigned int i = 0; i <= 31; i++)
        fn_801FCE10(0, "use \x8c insert into \x8c.'GPTC' set 'MGTC' = \x82 and '1STC' = 0 and '2STC' = 0\n", source, source, i);
    fn_801FCE10(&result, "use \x8c update 'REGL' set 'KCLG' = 1 where 'KLCG' = 1\n", source);
}
void CreateTeamDeletePlayer(int unused, int player)
{
    QueryResult result;
    DbQueryTable tables[2];
    DbFilter arg;
    arg.Set(6, 0x59414C5044494750LL, 3, player);
    tables[0].Set(0x59414C50);
    tables[1].Set(-1);
    fn_801F9908(0x54415453, tables, &arg, &result, 0);
}
int CreateTeamDeleteStandIn(int id)
{
    QueryResult result;
    fn_801FCE10(&result, "use 'TATS' delete from 'YALP' where 'DIOP' = \x82 and 'DIGT' = \x85\n", 0x7FF4, id);
    return result.mUnknown0 == 1;
}
int CreateTeamCountStandIns(int id)
{
    QueryResult result;
    int selected = 0;
    fn_801FCE10(&result, "use 'TATS' select count(*) into \x82 from 'YALP' where ('DIOP' = \x82 and 'DIGT' = \x85 )\n", &selected, 0x7FF4, id);
    return selected;
}
void CreateTeamAddPlayer(int team, int player, int useDefault)
{
    QueryResult result;
    int table = -1;
    unsigned short count = 1;
    int id;
    fn_801F9980(0x54415453, &table);
    fn_80229AA4(0x54415453, 0x59414C50, &id, &count);
    fn_801FCE10(&result, "use 'TATS' select into \x8c * from 'YALP' where ('DIGP' = \x82)\n", table, player);
    if (useDefault) player = 0x7FF4;
    fn_801FCE10(0, "use 'TATS' update \x8c set 'DIGP' = \x82 and 'DIOP' = \x82 and 'ITGT' = \x82 and 'DBTP' = \x82 and 'DFTP' = \x82 and 'CDHP' = \x82 and 'DIGT' = \x82\n", table, id, player, team, 0, 0, 0, team);
    fn_801FCE10(0, "use 'TATS' insert into 'YALP' * select * from \x8c\n", table);
    fn_801F967C(0x54415453, table);
}
void CreateTeamBackup(int *pFirstCopy, int *pSecondCopy, int database)
{
    fn_8018C344(database, 0x4D545243, 0x59505243, pFirstCopy, pSecondCopy);
}
void CreateTeamFreeBackup(int firstTable, int secondTable)
{
    fn_8018C3EC(firstTable, secondTable);
}
void CreateTeamRestore(int first, int second)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    CreateTeamClearTables(handle);
    fn_801FCE10(0, "use \x8c insert into \x8c.'MTRC' * select * from \x8c\n", 0x54415453, handle, first);
    fn_801FCE10(0, "use \x8c insert into \x8c.'YPRC' * select * from \x8c\n", 0x54415453, handle, second);
}
void CreateTeamPlayerCursorOpen(DbCursor *pCursor, int index)
{
    DbCursorOpen(pCursor, 0x59505243, 0x44494750, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}
void CreateTeamPlayerCursorClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}
}
