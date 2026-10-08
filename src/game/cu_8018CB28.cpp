#include "game/fn_801FCE10.h"
#include "game/fn_801C1F94.h"
#include "game/fn_8022F478.h"
#include "game/Object_8007A334.h"
#include "game/Query_8008352C.h"
#include "game/Object_8008044C.h"
#include "game/Block_80307980.h"
#include "game/FMCAPPORT.h"

extern "C" {
int fn_8022F358(int);
int fn_8022F4BC(void);
int fn_8022F3D4(int);
void fn_8018CA80(int);
void fn_8018CA14(int);
int fn_801F9980(int, int *);
int fn_801F967C(int, int);
void fn_801F9718(int, int, ColumnValue_802D6424 *, int *, int);
void fn_801F9908(int, char *, Object_80023BBC *, int *, int);
int fn_801F9D70(int, int, Object_80023BBC *, unsigned short *);
int fn_8022C628(int, int, int *, unsigned short *);
int fn_80229AA4(int, int, int *, unsigned short *);
int fn_80029D74(int, int);
void fn_80029CE0(int, int);
int fn_8008A900(int, int);
int fn_80080E98(Object_8008044C *);
int fn_80080E70(Object_8008044C *);
int fn_80081E3C(Object_8008044C *);
int fn_80082280(Object_8008044C *);
int fn_800822D4(Object_8008044C *);
int fn_80080E48(Object_8008044C *);
int fn_800810E0(Object_8008044C *);
int fn_80081134(Object_8008044C *);
void fn_8015F638(int, int, int, int *);
void fn_8016139C(int, int *, int *);
int fn_8016128C(int);
void fn_8018C48C(int);
void fn_8018C344(int database, int firstTable, int secondTable,
                 int *pFirstCopy, int *pSecondCopy);
void fn_8018C3EC(int firstTable, int secondTable);
int fn_80186F7C(unsigned char);
int fn_80186B38(int);
int fn_8018F228(int);
void fn_8018F41C(int);
int fn_8022EF8C(int, int);
int fn_8022EFBC(int, int);
}

static int lbl_802EAE74[16] = {
    0x44494754, 0x44494F54, 0x50595454, 0x44524F54, 0x45445254, 0x464F5254, 0x564F5254, 0x4C474C54, 0x49524454, 0x31434D54, 0x32434D54, 0x33434D54, 0x4C445443, 0x414E5354, 0x414E4C54, 0x414E4454
};
static int lbl_802EAEB4[13] = {
    0x00000000, 0x00000000, 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000066, 0x00000000, 0x00000035, 0x0000003C, 0x00000075, 0x00000001
};
static int lbl_802EAEE8[3] = {
    0x802AA338, 0x802AA33C, 0x802AA33C
};

extern "C" {
void fn_8018CB28(int source, int team, int index)
{
    QueryResult result;
    int table = -1;
    QueryCursor cursor;
    int player;
    fn_801C1F94(&cursor, 0, sizeof(cursor));
    cursor.mUnknown8 = -1;
    int destination = fn_8022F3D4(fn_8022F358(index));
    fn_8018CA80(destination);
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
    fn_8018CA14(index);
}

int fn_8018CD1C(int source, int teamTable, int playerTable, int destination,
                int rumt, int *pOriginalIds, int preserveOriginal)
{
    QueryResult result;
    int ids[16];
    unsigned short teamCount = 1;
    unsigned short count;
    int team;
    int table = -1;
    QueryCursor cursor;
    int player;
    fn_801C1F94(&cursor, 0, sizeof(cursor));
    cursor.mUnknown8 = -1;
    fn_8022C628(destination, 0x4D414554, &team, &teamCount);
    fn_801F9980(destination, &table);
    fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where ('DIGT' = \x82)\n", source, destination, table, teamTable, 0);
    fn_801FCE10(&result, "use \x8c update \x8c set 'DIGT' = \x85 and 'DIOT' = \x85\n", destination, table, team, team);
    fn_801FCE10(&result, "use \x8c insert into 'MAET' * select * from \x8c\n", destination, table);
    fn_801F967C(destination, table);
    fn_801FCE10(&result, "use \x8c update 'MAET' set 'RUMT' = \x85 and 'OLFT' = 0 and 'SIVT' = 1 and 'DIGD' = \x82 where ('DIGT' = \x85)\n", destination, rumt, 8, team);
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c order by 'DIGP'\n", source, &cursor, &player, playerTable);
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

int fn_8018D018(int destination, int rumt, int index, int *pOriginalIds, int preserveOriginal)
{
    int source = fn_8022F3D4(fn_8022F358(index));
    return fn_8018CD1C(source, 0x4D545243, 0x59505243, destination, rumt, pOriginalIds, preserveOriginal);
}

void fn_8018D07C(int index)
{
    QueryResult result;
    QueryCursor cursor;
    int player, ytrp, oldPxsp;
    int source = fn_8022F3D4(fn_8022F358(index));
    fn_801C1F94(&cursor, 0, sizeof(cursor));
    cursor.mUnknown8 = -1;
    int hadState = fn_80029D74(2, index);
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from 'YPRC' order by 'DIGP'\n", source, &cursor, &player);
    if (status != 23) {
        unsigned int count = result.mUnknown0;
        for (unsigned int i = 0; i < count; i++) {
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801FCE10(0, "use \x8c select 'YTRP' into \x85 from 'YPRC' where 'DIGP' = \x82\n", source, &ytrp, player);
            if (ytrp == 1) {
                int mapped = fn_8008A900((unsigned char)index, 0);
                fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 from 'YPRC' where 'DIGP' = \x82\n", source, &oldPxsp, player);
                fn_801FCE10(0, "use \x8c update 'YPRC' set 'PXSP' = \x85 where 'DIGP' = \x82\n", source, mapped, player);
                fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", source, mapped, oldPxsp);
            }
        }
    }
    if (!hadState) fn_80029CE0(2, index);
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
}

int fn_8018D23C()
{
    ColumnValue_802D6424 list[17];
    unsigned short count = 1;
    int team;
    fn_8022C628(0x54415453, 0x4D414554, &team, &count);
    for (unsigned int i = 0; i < 13; i++) {
        list[i].Set(0x4D414554, lbl_802EAE74[i], lbl_802EAEB4[i]);
    }
    for (unsigned int i = 0; i < 3; i++) {
        list[i + 13].Set(0x4D414554, lbl_802EAE74[i + 13], lbl_802EAEE8[i]);
    }
    list[0].mValue = team;
    list[16].SetEnd();
    fn_801F9718(0x54415453, 0x4D414554, list, 0, 0);
    return team;
}

void fn_8018D358(int index, int team, int rumt)
{
    Object_80023BBC arg;
    QueryResult result;
    QueryCursor cursor;
    int ids[16];
    unsigned short total, count;
    fn_801C1F94(&cursor, 0, sizeof(cursor));
    cursor.mUnknown8 = -1;
    int saved = fn_8022F4BC();
    fn_8022F478(fn_8022F358(index));
    int source = fn_8022F3D4(fn_8022F358(index));
    arg.Set(6, 0x5244524344494754LL, 2, rumt);
    fn_801F9D70(0x54415453, 0x52445243, &arg, &total);
    count = total;
    fn_80229AA4(0x54415453, 0x59414C50, ids, &count);
    int player, table;
    cursor.mUnknown0 = 0; cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1; cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use 'TATS' declare \x8a fastcursor for select 'DIGP' into \x85 from 'RDRC' where 'DIGT' = \x82 order by 'DIGP'\n", source, &cursor, &player, rumt);
    for (unsigned int i = 0; i < count; i++) {
        fn_801FCE10(0, "fetch from \x8a\n", &cursor);
        fn_801F9980(0x54415453, &table);
        fn_801FCE10(&result, "use 'TATS' select into \x8c * from 'RDRC' where ('DIGP' = \x85)\n", table, player);
        fn_801FCE10(&result, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x85\n", table, team, ids[i]);
        fn_801FCE10(&result, "use 'TATS' insert into 'YALP' * select * from \x8c\n", table);
        fn_801FCE10(0, "use 'TATS' update 'YALP' set 'PXSP' = \x85 where 'DIGP' = \x85\n", i, ids[i]);
        Object_8008044C object;
        Block_80307980 block;
        FMCAPPORTValues values;
        FMCAPPORTText text60, text20;
        int resultIds[2], unknown52, unknown56;
        fn_8008044C(&object, 0, 0x54415453);
        fn_800809C4(&object, ids[i], 0);
        int value6E = fn_80080E98(&object);
        int value6C = fn_80080E70(&object);
        int value72 = fn_80081E3C(&object);
        int value73 = fn_80082280(&object);
        int value74 = fn_800822D4(&object);
        int value76 = fn_80080E48(&object);
        int color18 = fn_800810E0(&object);
        int color19 = fn_80081134(&object);
        fn_80082138(&object, &block);
        fn_80046804(&block, &values);
        fn_8015F638(value6E, value6C, 0, resultIds);
        fn_8016139C(value6E, &unknown52, &unknown56);
        int unknown8 = fn_8016128C(value72 + 1);
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
    gFMCAPPORT.ClearEntries();
    fn_8022F478(saved);
}

int fn_8018D70C(int value)
{
    if (value == 5) return 8000;
    return 200;
}
int fn_8018D720(int index)
{
    unsigned short count = 0;
    int found = 0;
    fn_801F9D70(fn_8022F3D4(fn_8022F358(index)), 0x4D545243, 0, &count);
    if (count) found = 1;
    return found;
}
int fn_8018D780(int index)
{
    unsigned short count = 0;
    int found = 0;
    fn_801F9D70(fn_8022F3D4(fn_8022F358(index)), 0x59505243, 0, &count);
    if (count) found = 1;
    return found;
}
void fn_8018D7E0()
{
    int ids[16];
    fn_8018C48C(0x54415453);
    fn_8018C48C(0x454D4147);
    for (unsigned char i = 0; i <= 1; i++) {
        int index = fn_80186F7C(i);
        if (index != -1 && fn_8018D720(index)) {
            fn_8018D07C(index);
            fn_8018D018(0x54415453, i, index, ids, 0);
            fn_8018D018(0x454D4147, i, index, ids, 0);
        }
    }
}
void fn_8018D890(int index, int rumt)
{
    int ids[16];
    fn_8018C48C(0x54415453);
    fn_8018D07C(index);
    fn_8018D018(0x54415453, rumt, index, ids, 1);
}
void fn_8018D8EC(int index, int team)
{
    fn_8018CB28(0x54415453, team, index);
}
void fn_8018D918()
{
    int source = fn_8022F3D4(fn_8022F4BC());
    if (!fn_8018F228(fn_80186B38(fn_8022F4BC())))
        fn_8018F41C(fn_80186B38(fn_8022F4BC()));
    QueryResult result;
    Query_8008352C columns[2];
    QueryCursor cursor = {0, 0, -1, 0};
    int player, pxsp, ytrp, selected;
    fn_801FCE10(&result, "use \x8c declare \x8a cursor for select 'PXSP' and 'DIOP' and 'YTRP' from 'YPRC'\n", source, &cursor);
    for (unsigned int i = 0; i < result.mUnknown0; i++) {
        player = i; pxsp = 0; ytrp = 0;
        fn_801FCE10(0, "fetch from \x8a 'PXSP' into \x85 and 'DIOP' into \x85 and 'YTRP' into \x85\n", &cursor, &player, &pxsp, &ytrp);
        if (pxsp != 0x7FF4 && ytrp == 1)
            fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", source, i, player);
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    if (fn_801FCE10(&result, "use \x8c select 'PXSP' into \x85 from 'YPRC' where 'DIOP' = \x85\n", source, &selected, 0x7FF4) == 0)
        fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", source, 8, selected);
    fn_8018CA80(source);
    columns[0].mUnknown0 = 0x4E494843;
    columns[0].mUnknown4 = 2; columns[0].mUnknown8 = 0;
    columns[1].mUnknown0 = -1;
    columns[1].mUnknown4 = 2; columns[1].mUnknown8 = 0;
    fn_801F9908(source, (char *)columns, 0, (int *)&result, 0);
    fn_8022EF8C(0x54415453, 0x4E494843);
    fn_801FCE10(&result, "use 'TATS' insert into \x8c.'NIHC' * select * from 'NIHC'\n", source);
    fn_8022EFBC(0x54415453, 0x4E494843);
    columns[0].mUnknown0 = 0x47504843;
    columns[0].mUnknown4 = 2; columns[0].mUnknown8 = 0;
    columns[1].mUnknown0 = -1;
    columns[1].mUnknown4 = 2; columns[1].mUnknown8 = 0;
    fn_801F9908(source, (char *)columns, 0, (int *)&result, 0);
    fn_8022EF8C(0x54415453, 0x47504843);
    fn_801FCE10(&result, "use 'TATS' insert into \x8c.'GPHC' * select * from 'GPHC'\n", source);
    fn_8022EFBC(0x54415453, 0x47504843);
    columns[0].mUnknown0 = 0x47505443;
    columns[0].mUnknown4 = 2; columns[0].mUnknown8 = 0;
    columns[1].mUnknown0 = -1;
    columns[1].mUnknown4 = 2; columns[1].mUnknown8 = 0;
    fn_801F9908(source, (char *)columns, 0, (int *)&result, 0);
    for (unsigned int i = 0; i <= 31; i++)
        fn_801FCE10(0, "use \x8c insert into \x8c.'GPTC' set 'MGTC' = \x82 and '1STC' = 0 and '2STC' = 0\n", source, source, i);
    fn_801FCE10(&result, "use \x8c update 'REGL' set 'KCLG' = 1 where 'KLCG' = 1\n", source);
}
void fn_8018DC18(int unused, int player)
{
    QueryResult result;
    Query_8008352C columns[2];
    Object_80023BBC arg;
    arg.Set(6, 0x59414C5044494750LL, 3, player);
    columns[0].mUnknown0 = 0x59414C50;
    columns[0].mUnknown4 = 2; columns[0].mUnknown8 = 0;
    columns[1].mUnknown0 = -1;
    columns[1].mUnknown4 = 2; columns[1].mUnknown8 = 0;
    fn_801F9908(0x54415453, (char *)columns, &arg, (int *)&result, 0);
}
int fn_8018DCBC(int id)
{
    QueryResult result;
    fn_801FCE10(&result, "use 'TATS' delete from 'YALP' where 'DIOP' = \x82 and 'DIGT' = \x85\n", 0x7FF4, id);
    return result.mUnknown0 == 1;
}
int fn_8018DD04(int id)
{
    QueryResult result;
    int selected = 0;
    fn_801FCE10(&result, "use 'TATS' select count(*) into \x82 from 'YALP' where ('DIOP' = \x82 and 'DIGT' = \x85 )\n", &selected, 0x7FF4, id);
    return selected;
}
void fn_8018DD4C(int team, int player, int useDefault)
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
void fn_8018DE40(int *pFirstCopy, int *pSecondCopy, int database)
{
    fn_8018C344(database, 0x4D545243, 0x59505243, pFirstCopy, pSecondCopy);
}
void fn_8018DE7C(int firstTable, int secondTable)
{
    fn_8018C3EC(firstTable, secondTable);
}
void fn_8018DE9C(int first, int second)
{
    int handle = fn_8022F3D4(fn_8022F4BC());
    fn_8018CA80(handle);
    fn_801FCE10(0, "use \x8c insert into \x8c.'MTRC' * select * from \x8c\n", 0x54415453, handle, first);
    fn_801FCE10(0, "use \x8c insert into \x8c.'YPRC' * select * from \x8c\n", 0x54415453, handle, second);
}
void fn_8018DF20(Object_8007A334 *pCursor, int index)
{
    fn_8007A334(pCursor, 0x59505243, 0x44494750, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}
void fn_8018DF78(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}
}
