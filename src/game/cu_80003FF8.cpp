#include "game/Object_800785C0.h"
#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_8007F12C.h"
#include "game/fn_8007F828.h"
#include "game/fn_801FCE10.h"

static int lbl_802F3E60[7] = {0, 1, 2, 4, 8, 9, 13};
static int lbl_803EB8F0 = -1;
static int lbl_803EB8F4 = -1;
static int lbl_803EB8F8 = -1;
static unsigned char lbl_803EB8FC = 0;

extern "C" {
int fn_801F9980(int handle, int *pTable);
int fn_801F967C(int handle, int table);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_800812B0(Object_8008044C *pObject, int index);
void fn_8008135C(Object_8008044C *pObject, int index, int value);
int fn_8008454C(int type, int logo, const char *pName);
void fn_80084808(int a, int *pIds, int *pCounts, int count, int *pOut, int total);
void fn_80083DE4(int id);
void fn_800256F8(int mode);
void fn_8002B5B8(int value);
int fn_8022F4BC(void);
int fn_80186B38(int db);
void fn_80186F30(signed char index, unsigned char pad);
void fn_8002B714(int value);
void fn_8001ED80(int value);
void fn_800785CC(unsigned char id, int level);
void fn_80083E1C(Object_8007A334 *pObject, Query_80083E40 *pQuery);
int fn_80079864(Object_800785C0 *pRecord, int id);
int fn_80084388(void);
void fn_8018D7E0(void);
int fn_8008406C(Object_8007A334 *pObject, int id, int *pResult);
int fn_80083FBC(Object_8007A334 *pObject);
void fn_8001441C(int team, int id);
void fn_8007CAEC(int index, int value);
float fn_80237260(int stream);
void fn_800A2F3C(int value);

int fn_80003FF8(int sourceTeam)
{
    QueryResult result;
    int ids[10];
    QueryCursor cursor = {0, 0, -1, 0};
    unsigned short teamCount = 1;
    unsigned short count;
    int team;
    int table = -1;
    int player;

    fn_8022C628(0x454D4147, 0x4D414554, &team, &teamCount);
    fn_801F9980(0x454D4147, &table);
    fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from 'MAET' where ('DIGT' = \x82)\n", 0x54415453, 0x454D4147, table, sourceTeam);
    fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", 0x454D4147, table, team, sourceTeam);
    fn_801FCE10(&result, "use \x8c insert into 'MAET' * select * from \x8c\n", 0x454D4147, table);
    fn_801F967C(0x454D4147, table);
    fn_801FCE10(&result, "use \x8c update 'MAET' set 'RUMT' = \x85 and 'OLFT' = 0 and 'SIVT' = 1 and 'DIGD' = \x82 where ('DIGT' = \x85)\n", 0x454D4147, 3, 8, team);
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c where ('DIGT' = \x85) order by 'DIGP'\n", 0x54415453, &cursor, &player, 0x59414C50, sourceTeam);
    if (status != 23) {
        count = result.mUnknown0;
        fn_80229AA4(0x454D4147, 0x59414C50, ids, &count);
        for (unsigned int i = 0; i < count; i++) {
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801F9980(0x454D4147, &table);
            fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where ('DIGP' = \x82)\n", 0x54415453, 0x454D4147, table, 0x59414C50, player);
            fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIGP' = \x85 and 'DIOP' = \x85 where ('DIGP' = \x82)\n", 0x454D4147, table, sourceTeam, ids[i], player, player);
            fn_801FCE10(&result, "use \x8c insert into 'YALP' * select * from \x8c\n", 0x454D4147, table);
            fn_801FCE10(&result, "use \x8c update 'YALP' set 'ITGT' = \x85 where 'DIGP' = \x82\n", 0x454D4147, sourceTeam, ids[i]);
            fn_801F967C(0x454D4147, table);
        }
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    return team;
}

void fn_800042D8(int team)
{
    Object_8008044C cursor;
    Desc_8008044C desc;
    desc.mUnknown4 = 1;
    desc.mUnknown8 = team;
    fn_8008044C(&cursor, &desc, 0x54415453);
    if (fn_8007A444((Object_8007A334 *)&cursor)) {
        do {
            for (int i = 0; i < 10; i++) {
                unsigned int value = fn_800812B0(&cursor, i);
                value = (unsigned int)((float)value * 0.13f) * 5;
                value = value == 0 ? 1 : (value > 100 ? 100 : value);
                fn_8008135C(&cursor, i, value);
            }
        } while (fn_8007A510((Object_8007A334 *)&cursor));
    }
    fn_8008056C(&cursor);
}

int fn_80004440(int *pTeam)
{
    int players[10];
    int team = fn_8008454C(6, -1, 0);
    int counts[7] = {1, 1, 1, 1, 1, 1, 1};
    fn_80084808(team, lbl_802F3E60, counts, 7, players, 10);
    fn_800042D8(team);
    fn_80083DE4(team);
    int gameTeam = fn_80003FF8(team);
    if (pTeam) *pTeam = gameTeam;
    return team;
}

void fn_80004504(unsigned char id)
{
    Object_8007A334 cursor;
    lbl_803EB8FC = 0;
    fn_800256F8(0);
    fn_8002B5B8(2);
    fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
    fn_80186F30(-1, 0);
    fn_8002B714(1023);
    fn_8001ED80(5);
    fn_800785CC(id, fn_8007F828(0));
    Object_800785C0 *pRecord = fn_800785C0();
    fn_8007F97C();
    fn_80083E1C(&cursor, 0);
    int team;
    if (fn_80079864(pRecord, 4)) {
        lbl_803EB8FC = 1;
        team = 0;
    } else if (pRecord->mUnknown198) {
        team = pRecord->mUnknown198;
    } else if (lbl_803EB8F0 == pRecord->mUnknown0 && lbl_803EB8F4 != -1 && lbl_803EB8F8 == fn_8022F4BC()) {
        team = lbl_803EB8F4;
    } else {
        team = fn_80084388();
        lbl_803EB8F4 = team;
        lbl_803EB8F0 = pRecord->mUnknown0;
        lbl_803EB8F8 = fn_8022F4BC();
    }
    fn_8018D7E0();
    fn_8008406C(&cursor, 1, 0);
    int otherTeam = fn_80083FBC(&cursor);
    fn_80083F68(&cursor);
    fn_8001441C(0, team);
    fn_8001441C(1, otherTeam);
    switch (pRecord->mUnknown1B8) {
    case 0:
        fn_8007CAEC(2, 1);
        break;
    case 1:
        fn_8007CAEC(2, 0);
        break;
    default:
        if (!(fn_80237260(1) >= 0.5f)) fn_8007CAEC(2, 1);
        else fn_8007CAEC(2, 0);
        break;
    }
    fn_800A2F3C(pRecord->mUnknown1BC);
    if (pRecord->mUnknown19C == 0) {
        fn_8007F6F8(14, 0);
        fn_8007F6F8(1, pRecord->mUnknown1A0);
    } else {
        fn_8007F6F8(14, 1);
        fn_8007F6F8(2, pRecord->mUnknown1A0);
    }
    fn_8007F6F8(8, pRecord->mUnknown1A7);
    fn_8007F6F8(19, 1);
}

void fn_8000473C(int team, int value)
{
    Object_8007A334 cursor;
    lbl_803EB8FC = 0;
    fn_8007F97C();
    fn_800256F8(1);
    fn_8002B5B8(2);
    fn_8002B714(1023);
    fn_8001ED80(6);
    fn_80186F30(fn_80186B38(fn_8022F4BC()), 1);
    fn_80186F30(-1, 0);
    fn_8018D7E0();
    fn_80083E1C(&cursor, 0);
    fn_8008406C(&cursor, 1, 0);
    int otherTeam = fn_80083FBC(&cursor);
    fn_80083F68(&cursor);
    fn_8001441C(0, team);
    fn_8001441C(1, otherTeam);
    fn_8007CAEC(2, 1);
    fn_800A2F3C(value);
    fn_8007F6F8(14, 0);
    fn_8007F6F8(1, 36);
    fn_8007F6F8(8, 1);
    fn_8007F6F8(19, 1);
}

}

extern "C" int fn_8000485C(void)
{
    return lbl_803EB8FC;
}
