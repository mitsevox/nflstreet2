#include "game/Object_8008044C.h"
#include "game/Table_8007E020.h"
#include "game/fn_8018BE68.h"
#include "game/fn_801FCE10.h"

#if defined(DECOMP_COMPARE)
int lbl_802EADE4[16] = {
    0x44494754, 0x44494F54, 0x50595454, 0x44524F54, 0x45445254, 0x464F5254, 0x564F5254, 0x4C474C54,
    0x49524454, 0x31434D54, 0x32434D54, 0x33434D54, 0x4C445443, 0x414E5354, 0x414E4C54, 0x414E4454,
};
char *lbl_802EAE24[3] = {"Story", "Story Team", "Story Team"};
int lbl_802EAE30[10] = {0, 4, 1, 3, 2, 5, 6, 7, 8, 9};
int lbl_802EAE58[7] = {0, 1, 2, 4, 8, 9, 13};
#endif

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_801F9908(int handle, Table_8007E020 *pTables, Object_80023BBC *pFilter,
                QueryResult *pResult, int flags);
int fn_801F9980(int handle, int *pTable);
int fn_801F967C(int handle, int table);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_80029D74(int type, int index);
void fn_80029CE0(int type, int index);
int fn_8008A900(int value, int group);
void fn_8018B6F0(int index);

void fn_8018B014(int handle)
{
    QueryResult result;
    Table_8007E020 tables[2];

    tables[0].Set(0x59505453);
    tables[1].Set(-1);
    fn_801F9908(handle, tables, 0, &result, 0);
    tables[0].Set(0x4D455453);
    tables[1].Set(-1);
    fn_801F9908(handle, tables, 0, &result, 0);
}

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

int fn_8008454C(int a, int b, int c);
unsigned int fn_801C3180(const char *pText);
void fn_8018C48C(int handle);
void fn_8018C344(int database, int firstTable, int secondTable,
                 int *pFirstCopy, int *pSecondCopy);
void fn_8018C3EC(int firstTable, int secondTable);
int fn_80186F7C(unsigned char index);
int fn_8018E874(int index, int n);
int fn_801F9D70(int handle, int table, Object_80023BBC *pFilter, unsigned short *pCount);
int fn_8007A934(Object_8007A334 *pObject, int key);
void fn_8018B8B0(Object_8008044C *pObject);

void fn_8018B950(int index)
{
    Object_8008044C object;
    fn_8008044C(&object, 0, 0x54415453);
    if (fn_800809C4(&object, index, 0)) fn_8018B8B0(&object);
    fn_8008056C(&object);
}

void fn_8018B9D4(Object_8007A334 *pCursor, int index)
{
    fn_8007A334(pCursor, 0x4D455453, 0x44494754, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void fn_8018BA2C(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int fn_8018BA4C(void)
{
    Object_8007A334 cursor;
    int id = fn_8008454C(6, -1, 0);
    fn_80083E40(&cursor, 0, 0x54415453);
    if (fn_80084034(&cursor, id, 0)) {
        for (int i = 0; i < 3; i++) {
            char *pText = lbl_802EAE24[i];
            int length = fn_801C3180(pText);
            fn_8007ADD4(&cursor, lbl_802EADE4[i + 13], pText, length);
        }
    }
    fn_80083F68(&cursor);
    return id;
}

int fn_8018BD9C(int index)
{
    unsigned short count = 0;
    int found = 0;
    fn_801F9D70(fn_8022F3D4(fn_8022F358(index)), 0x4D455453, 0, &count);
    if (count) found = 1;
    return found;
}

int fn_8018BDFC(int index, int rumt, int *pIds, int *pCount)
{
    int ids[8];
    int *p;
    if (pIds) p = pIds;
    else p = ids;
    fn_8018C48C(0x54415453);
    return fn_8018B5E4(0x54415453, rumt, index, p, pCount, 1);
}

int fn_8018BE68(int index, int rumt, Result_8018BE68 *pOut)
{
    Result_8018BE68 result;
    Result_8018BE68 *p;
    if (pOut) p = pOut;
    else p = &result;
    fn_8018C48C(0x54415453);
    return fn_8018B66C(0x54415453, rumt, index, &p->mUnknown0, 1);
}

int fn_8018BECC(int index, int rumt, Result_8018BE68 *pOut)
{
    Result_8018BE68 result;
    Result_8018BE68 *p;
    if (pOut) p = pOut;
    else p = &result;
    return fn_8018B66C(0x54415453, rumt, index, &p->mUnknown0, 1);
}

void fn_8018BF10(int index, int team)
{
    fn_8018B0BC(0x54415453, team, index);
}

void fn_8018C008(int *pFirstCopy, int *pSecondCopy, int database)
{
    fn_8018C344(database, 0x4D455453, 0x59505453, pFirstCopy, pSecondCopy);
}

void fn_8018C044(int firstTable, int secondTable)
{
    fn_8018C3EC(firstTable, secondTable);
}

int fn_8018C0E8(int index, int *pTeam)
{
    Object_8007A334 cursor;
    fn_8018B9D4(&cursor, index);
    *pTeam = fn_8007A98C(&cursor, 0x44494754);
    fn_8018BA2C(&cursor);
    return 1;
}

int fn_8018C1E0(Object_8007A334 *pCursor)
{
    int value = 132;
    if (fn_8007A444(pCursor)) value = fn_8007A934(pCursor, 0x4C474C54);
    return value;
}

void fn_8018C230(int reset, int count)
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
        if (!reset && count == 1) skip = fn_8018E874(index, 1);
        else skip = 0;
        if (index != -1 && fn_8018BD9C(index) && !skip) {
            fn_8018B6F0(index);
            fn_8018B2A8(fn_8022F3D4(fn_8022F358(index)), 0x4D455453, 0x59505453, 0x54415453,
                        i, &count, ids, 0);
        }
    }
}
#endif
}
