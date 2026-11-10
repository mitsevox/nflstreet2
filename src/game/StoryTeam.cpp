/* Story team: the team a user builds in the story mode, kept in the story-team
   tables of each user's save database. Creates the team and its first player,
   copies the team and its players between the user's save tables and the
   game's team and player tables, backs them up and restores them, and moves or
   deletes its players. */
#include "game/FaceFeatures.h"
#include "game/FMCAPPORT.h"
#include "game/Object_8008044C.h"
#include "game/Request_802329F0.h"
#include "game/DbQueryTable.h"
#include "game/StoryTeam.h"
#include "game/fn_801C1F94.h"
#include "game/fn_801F9908.h"
#include "game/fn_801FCE10.h"
#include "game/fn_8022F478.h"

int _StoryTeam_aTeamTags[16] = {
    0x44494754, 0x44494F54, 0x50595454, 0x44524F54, 0x45445254, 0x464F5254, 0x564F5254, 0x4C474C54,
    0x49524454, 0x31434D54, 0x32434D54, 0x33434D54, 0x4C445443, 0x414E5354, 0x414E4C54, 0x414E4454,
};
char *_StoryTeam_apNames[3] = {"Story", "Story Team", "Story Team"};
int _StoryTeam_aDefaultAttrs[10] = {0, 4, 1, 3, 2, 5, 6, 7, 8, 9};
int _StoryTeam_aPositions[7] = {0, 1, 2, 4, 8, 9, 13};

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_801F9980(int handle, int *pTable);
int fn_801F967C(int handle, int table);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80029D74(int type, int index);
void fn_80029CE0(int type, int index);
int PortraitAllocSlot(int value, int group);
void StoryTeamSyncCreatedPlayer(int index);

void StoryTeamClearTables(int handle)
{
    QueryResult result;
    DbQueryTable tables[2];

    tables[0].Set(0x59505453);
    tables[1].Set(-1);
    fn_801F9908(handle, tables, 0, &result, 0);
    tables[0].Set(0x4D455453);
    tables[1].Set(-1);
    fn_801F9908(handle, tables, 0, &result, 0);
}

void StoryTeamStore(int source, int team, int index)
{
    QueryResult result;
    int table = -1;
    QueryCursor cursor = {0, 0, -1, 0};
    int player;
    int destination = fn_8022F3D4(fn_8022F358(index));
    StoryTeamClearTables(destination);
    fn_801F9980(destination, &table);
    fn_801FCE10(0, "use \x8c select into \x8c.\x8c * from 'MAET' where ('DIGT' = \x82)\n", source, destination, table, team);
    fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", destination, table, 0, 0);
    fn_801FCE10(&result, "use \x8c insert into 'METS' * select * from \x8c\n", destination, table);
    fn_801F967C(destination, table);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from 'YALP' where 'DIGT' = \x85 order by 'DIGP'\n", source, &cursor, &player, team);
    unsigned int count = result.mUnknown0;
    for (unsigned int i = 0; i < count; i++) {
        fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        fn_801F9980(destination, &table);
        fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from 'YALP' where ('DIGP' = \x82)\n", source, destination, table, player);
        fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82\n", destination, table, 0, i);
        fn_801FCE10(0, "use \x8c insert into 'YPTS' * select * from \x8c\n", destination, table);
        fn_801F967C(destination, table);
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
}

int StoryTeamLoad(int source, int teamTable, int playerTable, int destination,
                int rumt, int *pCount, int *pOriginalIds, int preserveOriginal)
{
    QueryResult result;
    int ids[8];
    unsigned short teamCount = 1;
    unsigned short count;
    int team;
    int table = -1;
    QueryCursor cursor = {0, 0, -1, 0};
    int player;
    int ytrp;
    fn_8022C628(destination, 0x4D414554, &team, &teamCount);
    fn_801F9980(destination, &table);
    fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where ('DIGT' = \x82)\n", source, destination, table, teamTable, 0);
    fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", destination, table, team, team);
    fn_801FCE10(&result, "use \x8c insert into 'MAET' * select * from \x8c\n", destination, table);
    fn_801F967C(destination, table);
    fn_801FCE10(&result, "use \x8c update 'MAET' set 'RUMT' = \x85 and 'OLFT' = 0 and 'SIVT' = 1 and 'DIGD' = \x82 where ('DIGT' = \x85)\n", destination, rumt, 8, team);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int code = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c order by 'DIGP'\n", source, &cursor, &player, playerTable);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        if (*pCount <= 0) {
            count = *pCount = result.mUnknown0;
        } else {
            count = *pCount;
        }
        fn_80229AA4(destination, 0x59414C50, ids, &count);
        for (unsigned int i = 0; i < count; i++) {
            if (destination == 0x54415453) pOriginalIds[i] = ids[i];
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801F9980(destination, &table);
            fn_801FCE10(0, "use \x8c select 'YTRP' into \x85 from \x8c where 'DIGP' = \x82\n", source, &ytrp, playerTable, player);
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

int StoryTeamLoadAll(int destination, int rumt, int index, int *pOriginalIds,
                int *pCount, int preserveOriginal)
{
    int source = fn_8022F3D4(fn_8022F358(index));
    StoryTeamSyncCreatedPlayer(index);
    *pCount = 0;
    return StoryTeamLoad(source, 0x4D455453, 0x59505453, destination, rumt,
                       pCount, pOriginalIds, preserveOriginal);
}

int StoryTeamLoadOne(int destination, int rumt, int index, int *pOriginalIds,
                int preserveOriginal)
{
    int source = fn_8022F3D4(fn_8022F358(index));
    StoryTeamSyncCreatedPlayer(index);
    int count = 1;
    return StoryTeamLoad(source, 0x4D455453, 0x59505453, destination, rumt,
                       &count, pOriginalIds, preserveOriginal);
}

void StoryTeamSyncCreatedPlayer(int index)
{
    QueryResult result;
    int player;
    int ytrp;
    int oldPxsp;
    int handle = fn_8022F3D4(fn_8022F358(index));
    QueryCursor cursor = {0, 0, -1, 0};
    int state = fn_80029D74(2, index);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int code = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from 'YPTS' order by 'DIGP'\n", handle, &cursor, &player);
    if (status != 0 && status != 23) {
        code = status;
    }
    if (status != 23) {
        unsigned int count = result.mUnknown0;
        for (unsigned int i = 0; i < count; i++) {
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801FCE10(0, "use \x8c select 'YTRP' into \x85 from 'YPTS' where 'DIGP' = \x82\n", handle, &ytrp, player);
            if (ytrp == 1) {
                int pxsp = PortraitAllocSlot((unsigned char)index, 1);
                fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 from 'YPTS' where 'DIGP' = \x82\n", handle, &oldPxsp, player);
                fn_801FCE10(0, "use \x8c update 'YPTS' set 'PXSP' = \x85 where 'DIGP' = \x82\n", handle, pxsp, player);
                fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", handle, pxsp, oldPxsp);
            }
        }
    }
    if (!state) fn_80029CE0(2, index);
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
}

int fn_8008454C(int type, int logo, const char *pName);
unsigned int fn_801C3180(const char *pText);
void fn_8018C48C(int handle);
void fn_8018C344(int database, int firstTable, int secondTable,
                 int *pFirstCopy, int *pSecondCopy);
void fn_8018C3EC(int firstTable, int secondTable);
int fn_80186F7C(unsigned char index);
int StoryTestIndexedFlag(int index, int n);
int fn_801F9D70(int handle, int table, DbFilter *pFilter, unsigned short *pCount);
int DbCursorGetValue(DbCursor *pObject, int key);
void PlayerDbSetRating(Object_8008044C *pObject, int index, int value);
int fn_8022F4BC(void);
int fn_8022F384(int a);
void StorySetNew(int index, int value);
int fn_802294F4(void);
int fn_80229554(void);
void fn_800828FC(void);
void fn_800829D8(void);
int fn_80082AE4(int a, int b);
int fn_8022C8F0(unsigned int low, unsigned int high);
int PlayerDbGetHairStyle(Object_8008044C *pObject);
int PlayerDbGetPlht(Object_8008044C *pObject);
int fn_80081E3C(Object_8008044C *pObject);
int fn_80082280(Object_8008044C *pObject);
int fn_800822D4(Object_8008044C *pObject);
int PlayerDbGetPlex(Object_8008044C *pObject);
int PlayerDbGetHairColor(Object_8008044C *pObject);
int PlayerDbGetFacialHairColor(Object_8008044C *pObject);
void fn_8015F638(int a, int b, int c, int *pResult);
int PlaTexCacheGetCapFaceId(int a);
void PlaTexCacheGetHairTexture(int a, int *pId, int *pPalette);

void StoryPlayerSetDefaults(Object_8008044C *pObject)
{
    for (int i = 0; i < 10; i++) {
        PlayerDbSetRating(pObject, _StoryTeam_aDefaultAttrs[i], 1);
    }
    fn_8007AA90((DbCursor *)pObject, 0x44494F50, -1);
    fn_8007AA90((DbCursor *)pObject, 0x54474850, 0x41);
    fn_8007AA90((DbCursor *)pObject, 0x54475750, 0);
    fn_8007AA90((DbCursor *)pObject, 0x54425950, 2);
}

extern char lbl_802EBE24[];

void StoryPlayerResetById(int id)
{
    Object_8008044C object;
    fn_8008044C(&object, 0, 0x54415453);
    if (PlayerDbSeekId(&object, id, 0)) StoryPlayerSetDefaults(&object);
    fn_8008056C(&object);
}

void StoryTeamCursorOpen(DbCursor *pCursor, int index)
{
    DbCursorOpen(pCursor, 0x4D455453, 0x44494754, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void StoryTeamCursorClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int StoryTeamCreate(void)
{
    DbCursor cursor;
    int id = fn_8008454C(6, -1, 0);
    fn_80083E40(&cursor, 0, 0x54415453);
    if (fn_80084034(&cursor, id, 0)) {
        for (int i = 0; i < 3; i++) {
            char *pText = _StoryTeam_apNames[i];
            int length = fn_801C3180(pText);
            fn_8007ADD4(&cursor, _StoryTeam_aTeamTags[i + 13], pText, length);
        }
    }
    fn_80083F68(&cursor);
    return id;
}

void StoryTeamCreatePlayer(int index, int value)
{
    Request_802329F0 request;
    int busy = fn_802294F4();
    if (!busy) {
        request.mMode = 0;
        request.mSize = 0x96000;
        request.mpName = lbl_802EBE24;
        request.mCount = 1;
        fn_802329F0(&request);
    }
    fn_800828FC();
    int k = fn_8022C8F0(0, 7);
    int id = fn_80082AE4(_StoryTeam_aPositions[k], value);
    fn_800829D8();
    if (!busy) fn_80229554();
    StoryPlayerResetById(id);
    fn_801FCE10(0, "use 'TATS' update 'YALP' set 'YTRP' = \x85 where 'DIGP' = \x85\n", 1, id);
    fn_801FCE10(0, "use 'TATS' update 'YALP' set 'PXSP' = \x85 where 'DIGP' = \x85\n", 7, id);

    Object_8008044C object;
    FaceFeatures_t block;
    FMCAPPORTValues values;
    FMCAPPORTText text60;
    FMCAPPORTText text20;
    int ids[2];
    int unknown52;
    int unknown56;

    fn_8008044C(&object, 0, 0x54415453);
    PlayerDbSeekId(&object, id, 0);
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
    fn_8015F638(value6E, value6C, 0, ids);
    PlaTexCacheGetHairTexture(value6E, &unknown52, &unknown56);
    int unknown8 = PlaTexCacheGetCapFaceId(value72 + 1);
    int unknown12 = value73 * 3 + value74 + 0x33BA;
    fn_801C1F94(&text60, 0, sizeof(text60));
    fn_801C1F94(&text20, 0, sizeof(text20));
    text60.mChars[18] = color18 + 0x80;
    text20.mChars[19] = color19 + 0x80;
    FMCAPPORT *pPort = &gFMCAPPORT;
    pPort->SetEntry(7, 0xFFFF, unknown8, unknown12, 0xA7, &text20, ids[0], unknown52, unknown56, &text60,
                    &values, value76);
    pPort->Start();
    fn_8008056C(&object);
}

void CopyRdrcPlayersToTeam(int index, int team, int rumt)
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

int StoryTeamExists(int index)
{
    unsigned short count = 0;
    int found = 0;
    fn_801F9D70(fn_8022F3D4(fn_8022F358(index)), 0x4D455453, 0, &count);
    if (count) found = 1;
    return found;
}

int StoryTeamLoadToStats(int index, int rumt, int *pIds, int *pCount)
{
    int ids[8];
    int *p;
    if (pIds) p = pIds;
    else p = ids;
    fn_8018C48C(0x54415453);
    return StoryTeamLoadAll(0x54415453, rumt, index, p, pCount, 1);
}

int StoryTeamLoadOneToStats(int index, int rumt, StoryTeamIdBlock_t *pOut)
{
    StoryTeamIdBlock_t result;
    StoryTeamIdBlock_t *p;
    if (pOut) p = pOut;
    else p = &result;
    fn_8018C48C(0x54415453);
    return StoryTeamLoadOne(0x54415453, rumt, index, &p->mUnknown0, 1);
}

int StoryTeamAddOneToStats(int index, int rumt, StoryTeamIdBlock_t *pOut)
{
    StoryTeamIdBlock_t result;
    StoryTeamIdBlock_t *p;
    if (pOut) p = pOut;
    else p = &result;
    return StoryTeamLoadOne(0x54415453, rumt, index, &p->mUnknown0, 1);
}

void StoryTeamStoreFromStats(int index, int team)
{
    StoryTeamStore(0x54415453, team, index);
}

void StoryTeamClear(void)
{
    DbQueryTable tables[2];
    QueryResult result;
    int pxsp;
    int handle = fn_8022F3D4(fn_8022F4BC());
    fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 from 'YPTS'\n", handle, &pxsp);
    fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", handle, 7, pxsp);
    StoryTeamClearTables(handle);
    tables[0].Set(0x43455453);
    tables[1].Set(-1);
    fn_801F9908(handle, tables, 0, &result, 0);
    StorySetNew(fn_8022F384(fn_8022F4BC()), 1);
}

void StoryTeamBackup(int *pFirstCopy, int *pSecondCopy, int database)
{
    fn_8018C344(database, 0x4D455453, 0x59505453, pFirstCopy, pSecondCopy);
}

void StoryTeamFreeBackup(int firstTable, int secondTable)
{
    fn_8018C3EC(firstTable, secondTable);
}

void StoryTeamRestore(int firstTable, int secondTable)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    StoryTeamClearTables(handle);
    fn_801FCE10(0, "use \x8c insert into \x8c.'METS' * select * from \x8c\n", 0x54415453, handle, firstTable);
    fn_801FCE10(0, "use \x8c insert into \x8c.'YPTS' * select * from \x8c\n", 0x54415453, handle, secondTable);
}

int StoryTeamGetId(int index, int *pTeam)
{
    DbCursor cursor;
    StoryTeamCursorOpen(&cursor, index);
    *pTeam = DbCursorGetInt(&cursor, 0x44494754);
    StoryTeamCursorClose(&cursor);
    return 1;
}

void StoryPlayerMoveToTeam(int team, int player)
{
    QueryResult result;
    fn_801FCE10(&result, "use 'TATS' update 'YALP' set 'DIGT' = \x82 and 'ITGT' = \x82 and 'DIOP' = \x82 and 'DBTP' = \x82 and 'DFTP' = \x82 and 'CDHP' = \x82 where 'DIGP' = \x82\n",
                team, team, -1, 0, 0, 0, player);
}

void StoryPlayerDelete(int player, int team)
{
    QueryResult result;
    fn_801FCE10(&result, "use 'TATS' delete from 'YALP' where 'DIGT' = \x82 and 'DIGP' = \x82\n", team, player);
}

int StoryTeamGetLogo(DbCursor *pCursor)
{
    int value = 132;
    if (DbCursorFirst(pCursor)) value = DbCursorGetValue(pCursor, 0x4C474C54);
    return value;
}

void StoryTeamLoadUserTeams(int reset, int count)
{
    int ids[8];
    if (reset) {
        fn_8018C48C(0x54415453);
        fn_8018C48C(0x454D4147);
    }
    for (unsigned char i = 0; i <= 1; i++) {
        int index = fn_80186F7C(i);
        if (index == -1) continue;
        int skip;
        if (!reset && count == 1) skip = StoryTestIndexedFlag(index, 1);
        else skip = 0;
        if (index != -1 && StoryTeamExists(index) && !skip) {
            StoryTeamSyncCreatedPlayer(index);
            StoryTeamLoad(fn_8022F3D4(fn_8022F358(index)), 0x4D455453, 0x59505453, 0x54415453,
                        i, &count, ids, 0);
        }
    }
}
}
