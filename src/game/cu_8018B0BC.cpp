#include "game/fn_801FCE10.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
void fn_8018B014(int handle);
int fn_801F9980(int handle, int *pTable);
int fn_801F967C(int handle, int table);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80029D74(int type, int index);
void fn_80029CE0(int type, int index);
int fn_8008A900(int value, int group);
void fn_8018B6F0(int index);

void fn_8018B0BC(int source, int team, int index)
{
    QueryResult result;
    int table = -1;
    QueryCursor cursor = {0, 0, -1, 0};
    int player;
    int destination = fn_8022F3D4(fn_8022F358(index));
    fn_8018B014(destination);
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

#if defined(DECOMP_COMPARE)
int fn_8018B2A8(int source, int teamTable, int playerTable, int destination,
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
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from \x8c order by 'DIGP'\n", source, &cursor, &player, playerTable);
    if (status != 23) {
        if (*pCount <= 0) *pCount = result.mUnknown0;
        count = *pCount;
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

int fn_8018B5E4(int destination, int rumt, int index, int *pOriginalIds,
                int *pCount, int preserveOriginal)
{
    int source = fn_8022F3D4(fn_8022F358(index));
    fn_8018B6F0(index);
    *pCount = 0;
    return fn_8018B2A8(source, 0x4D455453, 0x59505453, destination, rumt,
                       pCount, pOriginalIds, preserveOriginal);
}

int fn_8018B66C(int destination, int rumt, int index, int *pOriginalIds,
                int preserveOriginal)
{
    int source = fn_8022F3D4(fn_8022F358(index));
    fn_8018B6F0(index);
    int count = 1;
    return fn_8018B2A8(source, 0x4D455453, 0x59505453, destination, rumt,
                       &count, pOriginalIds, preserveOriginal);
}

void fn_8018B6F0(int index)
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
    int status = fn_801FCE10(&result, "use \x8c declare \x8a fastcursor for select 'DIGP' into \x82 from 'YPTS' order by 'DIGP'\n", handle, &cursor, &player);
    if (status != 23) {
        unsigned int count = result.mUnknown0;
        for (unsigned int i = 0; i < count; i++) {
            fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            fn_801FCE10(0, "use \x8c select 'YTRP' into \x85 from 'YPTS' where 'DIGP' = \x82\n", handle, &ytrp, player);
            if (ytrp == 1) {
                int pxsp = fn_8008A900((unsigned char)index, 1);
                fn_801FCE10(0, "use \x8c select 'PXSP' into \x85 from 'YPTS' where 'DIGP' = \x82\n", handle, &oldPxsp, player);
                fn_801FCE10(0, "use \x8c update 'YPTS' set 'PXSP' = \x85 where 'DIGP' = \x82\n", handle, pxsp, player);
                fn_801FCE10(0, "use \x8c update 'PPRC' set 'PXSP' = \x85 where 'PXSP' = \x85\n", handle, pxsp, oldPxsp);
            }
        }
    }
    if (!state) fn_80029CE0(2, index);
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
}
#endif
}
