#include <string.h>

#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"
#include "game/cu_8003E214.h"
#include "game/fn_8003B6BC.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801FCE10.h"
#include "game/fn_802372EC.h"

/* Optional second argument of fn_8008352C: three words, copied only when
   the pointer is non-null. */
struct Query_8008352C {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
};

extern "C" {
void fn_8003DE74(unsigned char side, int *pList);
void *fn_801C2030(void *dst, const void *src, unsigned int n);
unsigned int fn_801C3180(const char *pText);
char *fn_801C2EF0(char *pDest, const char *pSource, int count);
int fn_801F967C(int handle, int table);
void fn_801F9718(int handle, int table, ColumnValue_802D6424 *pList, int *pResult, int flags);
void fn_801F9908(int handle, char *pName, Object_80023BBC *pArg, int *pResult, int flags);
int fn_801F9980(int handle, int *pTable);
int fn_801F9A90(int a, int tag);
int fn_801D34D0(void *pDest, int size, int value, int width);
void fn_801F9BB4(int handle, int table, int column, int *pInfo);
void fn_80023024(int a);
int fn_8007A43C(Object_8007A334 *pObject);
int fn_8007A934(Object_8007A334 *pObject, int key);
void fn_8007CAEC(int index, int value);
void fn_800828FC(void);
void fn_800829D8(void);
int fn_80082A64(int a, int b);
int fn_80082AB0(int a, int b, int c);
void *fn_8021EA44(int index);
int fn_8021E2B4(void *pObject, int a, int b);
int fn_8021E72C(void *pObject, int a, int b);
int fn_80229AA4(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022A508(int a, int b, int c, int d, int e);
int fn_8022C628(int handle, int table, int *pIds, unsigned short *pCount);
int fn_8022C8F0(unsigned int low, unsigned int high);
void fn_8022DC7C(int a);
void fn_8022DCB0(int a);
void fn_8022DCE4(int a);
void fn_8022DD18(int a);
int fn_8022EF8C(int a, int tag);
int fn_8022EFBC(int a, int tag);
int fn_80237390(int stream, int low, int high);
}

static int lbl_802D6B08[8] = { 0x54534C50, 0x44494E53, 0, 0, -1, -1, 3, 0 };
static int lbl_802D6B28[3] = { 0x31434D54, 0x32434D54, 0x33434D54 };
static int lbl_802D6B34[8] = { 0x4D414554, 0x44524F54, 0, 0, -1, -1, 3, 0 };
static int lbl_802D6B54[14] = {
    0x5A425150, 0x5A425250, 0x46525750, 0x42525750, 0x4C4C4F50, 0x434C4F50, 0x524C4F50,
    0x4C4C4450, 0x524C4450, 0x46424C50, 0x42424C50, 0x4C424450, 0x43424450, 0x52424450,
};

static Record_8003E214 *lbl_803EA7E8 = 0;
static int lbl_803EC86C;

extern "C" {

unsigned int fn_800834CC(Object_8007A334 *pObject)
{
    unsigned int i;

    for (i = 0; i <= 39; i++) {
        if (fn_8007A7F4(pObject, pObject->mUnknown12, i, 0, 0) == 0) {
            break;
        }
    }
    return i;
}

void fn_8008352C(Object_8007A334 *pObject, Query_8008352C *pQuery)
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
        pColumns = lbl_802D6B08;
        break;
    }

    if (query.mUnknown4 == 0) {
        fn_8007A334(pObject, 0x54534C50, 0x4B504C50, pColumns, 0, 0x45564153);
    }
}

int fn_80083664(Object_8007A334 *pObject);
int fn_80083684(Object_8007A334 *pObject);
unsigned char fn_800837D8(Object_8007A334 *pObject);
void fn_80083854(Object_8007A334 *pObject);

void fn_800835D0(Object_8007A334 *pObject)
{
    int more = fn_80083664(pObject);

    while (more) {
        if (fn_800837D8(pObject) == 0) {
            int row = fn_8007A43C(pObject);
            fn_80083854(pObject);
            more = fn_8007A600(pObject, row);
        } else {
            more = fn_80083684(pObject);
        }
    }
}

void fn_80083644(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_80083664(Object_8007A334 *pObject)
{
    return fn_8007A444(pObject);
}

int fn_80083684(Object_8007A334 *pObject)
{
    return fn_8007A510(pObject);
}

int fn_800836A4(Object_8007A334 *pObject, int a, int b, int c)
{
    int found = 0;
    int more;

    if (a != 0) {
        for (more = fn_8007A7F4(pObject, 0x58545349, 1, 0, 0); more;
             more = fn_8007A7F4(pObject, 0x58545349, 1, 1, 0)) {
            if (fn_8007A98C(pObject, 0x44494E53) == c) {
                found = 1;
                break;
            }
        }
    } else {
        for (more = fn_8007A7F4(pObject, 0x44495453, b, 0, 0); more;
             more = fn_8007A7F4(pObject, 0x44495453, b, 1, 0)) {
            if (fn_8007A98C(pObject, 0x44494E53) == c && fn_8007A98C(pObject, 0x58545349) == 0) {
                found = 1;
                break;
            }
        }
    }
    return found;
}

int fn_800837B8(Object_8007A334 *pObject)
{
    return fn_8007A410(pObject);
}

unsigned char fn_800837D8(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x58545349);
}

int fn_80083804(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x44495453);
}

int fn_8008382C(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x44494E53);
}

void fn_80083854(Object_8007A334 *pObject)
{
    int info[4];
    Object_80023BBC arg;
    int result[4];
    ColumnValue_802D6424 list[2];

    fn_801F9BB4(pObject->mUnknown4, pObject->mUnknown8, pObject->mUnknown12, info);
    list[0].Set(-1, pObject->mUnknown12);
    list[0].mValue = 0;
    list[1].SetEnd();
    pObject->Read(list);
    int value = list[0].mValue;

    unsigned int table = pObject->mUnknown8;
    unsigned int column = pObject->mUnknown12;
    arg.Set(6, ((unsigned long long)table << 32) | column, info[0], value);
    fn_801F9908(pObject->mUnknown4, pObject->mUnknown20, &arg, result, 0);
}

void fn_80083934(Object_8007A334 *pObject, int a, int b, int c)
{
    ColumnValue_802D6424 list[5];
    int result[4];

    list[0].mColumnTag = 0x4B504C50;
    list[0].mTableTag = 0x54534C50;
    list[0].mValue = fn_800834CC(pObject);
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
    fn_801F9718(pObject->mUnknown4, pObject->mUnknown8, list, result, 0);
}

void fn_80083A10(Object_8007A334 *pObject, void *pColumns, int tag, int value)
{
    Object_80023BBC arg;

    arg.Set(6, 0x4D41455444494744LL, 3, value);
    fn_8007A334(pObject, 0x4D414554, 0x44494754, pColumns, &arg, tag);
}

void fn_80083A88(Object_8007A334 *pObject, void *pColumns, int tag)
{
    Object_80023BBC arg;

    arg.Set(6, 0x4D41455450595454LL, 3, 0);
    fn_8007A334(pObject, 0x4D414554, 0x44494754, pColumns, &arg, tag);
}

void fn_80083B00(Object_8007A334 *pObject, void *pColumns, int tag)
{
    Object_80023BBC root;
    Object_80023BBC left;
    Object_80023BBC right;

    root.mUnknown32 = 0x2000A;
    root.mUnknown0 = 11;
    root.mUnknown8.mNode = &left;
    root.mUnknown16 = 11;
    root.mUnknown24.mNode = &right;
    left.Set(6, 0x4D41455450595454LL, 3);
    left.mUnknown24.mInt = 0;
    right.Set(6, 0x4D41455450595454LL, 3);
    right.mUnknown24.mInt = 5;
    fn_8007A334(pObject, 0x4D414554, 0x44494754, pColumns, &root, tag);
}

void fn_80083BC4(Object_8007A334 *pObject, void *pColumns, int tag, int logo)
{
    Object_80023BBC root;
    Object_80023BBC left;
    Object_80023BBC right;

    root.Set(11, &left, &right);
    left.Set(6, 0x4D41455450595454LL, 3);
    left.mUnknown24.mInt = 0;
    right.Set(6, 0x4D4145544C474C54LL, 3);
    right.mUnknown24.mInt = logo;
    fn_8007A334(pObject, 0x4D414554, 0x44494754, pColumns, &root, tag);
}

void fn_80083C98(Object_8007A334 *pObject, void *pColumns, int tag, unsigned char flag)
{
    Object_80023BBC root;
    Object_80023BBC left;
    Object_80023BBC right;
    Object_80023BBC leftLeft;
    Object_80023BBC leftRight;

    root.Set(11, &left, &right);
    left.Set(11, &leftLeft, &leftRight);
    right.SetUnknown32(6, 0x4D41455450595454LL, 3, 0x10006);
    right.mUnknown24.mInt = 17;
    if (flag) {
        leftLeft.mUnknown24.mInt = 0;
    } else {
        leftLeft.mUnknown24.mInt = 1;
    }
    leftLeft.SetUnknown32(6, 0x4D41455452554D54LL, 3, 0x10006);
    leftRight.SetUnknown32(6, 0x4D41455450595454LL, 3, 0x10006);
    leftRight.mUnknown24.mInt = 2;
    fn_8007A334(pObject, 0x4D414554, 0x44494754, pColumns, &root, tag);
}

void fn_80083DE4(int id)
{
    fn_801FCE10(0, "use 'TATS' update 'YALP' set 'ITGT' = \x85 where 'DIGT' = \x82\n", id, id);
}

void fn_80083E1C(Object_8007A334 *pObject, Query_80083E40 *pQuery)
{
    fn_80083E40(pObject, pQuery, 0);
}

void fn_80083E40(Object_8007A334 *pObject, Query_80083E40 *pQuery, int tag)
{
    void *pColumns = 0;
    Query_80083E40 query;

    if (pQuery) {
        query.mUnknown0 = pQuery->mUnknown0;
        query.mUnknown4 = pQuery->mUnknown4;
        query.mUnknown8 = pQuery->mUnknown8;
    }

    switch (query.mUnknown0) {
    case 0:
        break;
    case 1:
        pColumns = lbl_802D6B34;
        break;
    }

    switch (query.mUnknown4) {
    case 0:
        fn_8007A334(pObject, 0x4D414554, 0x44494754, pColumns, 0, tag);
        break;
    case 1:
        fn_80083C98(pObject, pColumns, tag, query.mUnknown8);
        break;
    case 2:
        fn_80083A10(pObject, pColumns, tag, query.mUnknown8);
        break;
    case 3:
        fn_80083A88(pObject, pColumns, tag);
        break;
    case 4:
        fn_80083B00(pObject, pColumns, tag);
        break;
    case 5:
        fn_80083BC4(pObject, pColumns, tag, query.mUnknown8);
        break;
    }
}

void fn_80083F68(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

void fn_80083F88(Object_8007A334 *pObject, char *pBuffer, int size)
{
    fn_8007AA3C(pObject, 0x414E4454, (int)pBuffer, size);
}

int fn_80083FBC(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x44494754);
}

int fn_80083FE4(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x44494F54);
}

int fn_8008400C(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x50595454);
}

int fn_80084034(Object_8007A334 *pObject, int id, int *pResult)
{
    return fn_8007A7F4(pObject, 0x44494754, id, 0, pResult);
}

int fn_8008406C(Object_8007A334 *pObject, int id, int *pResult)
{
    return fn_8007A7F4(pObject, 0x52554D54, id, 0, pResult);
}

void fn_800840A4(Object_8007A334 *pObject, unsigned char *pValues)
{
    ColumnValue_802D6424 list[4];
    int i;

    for (i = 0; i < 3; i++) {
        list[i].Set(0x4D414554, lbl_802D6B28[i], 0);
    }
    list[3].SetEnd();
    pObject->Read(list);
    for (i = 0; i < 3; i++) {
        pValues[i] = list[i].mValue;
    }
}

int fn_80084158(Object_8007A334 *pObject)
{
    return fn_8007A934(pObject, 0x4C474C54);
}

void fn_80084180(Object_8007A334 *pObject, int value)
{
    fn_8007AA90(pObject, 0x4C474C54, value);
}

unsigned char fn_800841AC(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x31434D54);
}

unsigned char fn_800841D8(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x32434D54);
}

unsigned char fn_80084204(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x33434D54);
}

void fn_80084230(Object_8007A334 *pObject, unsigned char value)
{
    fn_8007ABA4(pObject, 0x31434D54, value);
}

void fn_8008425C(Object_8007A334 *pObject, unsigned char value)
{
    fn_8007ABA4(pObject, 0x32434D54, value);
}

void fn_80084288(Object_8007A334 *pObject, unsigned char value)
{
    fn_8007ABA4(pObject, 0x33434D54, value);
}

void fn_800842B4(Object_8007A334 *pObject, char *pText, int length)
{
    fn_8007ADD4(pObject, 0x414E4454, pText, length);
}

int fn_800842E8(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x464F5254);
}

int fn_80084310(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x45445254);
}

int fn_80084338(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x564F5254);
}

int fn_80084360(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x52554D54);
}

int fn_80084388(void)
{
    Object_8007A334 cursor;
    Query_80083E40 query;
    int id;

    query.mUnknown4 = 3;
    fn_80083E1C(&cursor, &query);
    fn_8007A600(&cursor, (signed char)fn_80237390(1, 0, fn_8007A410(&cursor) - 1));
    id = fn_8007A934(&cursor, 0x44494754);
    fn_80083F68(&cursor);
    return id;
}

int fn_80084438(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x4C445443) != 0;
}

void fn_80084470(Object_8007A334 *pObject, int value)
{
    if (value) {
        fn_8007ABA4(pObject, 0x4C445443, 1);
    } else {
        fn_8007ABA4(pObject, 0x4C445443, 0);
    }
}

int fn_800844B8(const char *pName, int type, int logo)
{
    unsigned short count = 1;
    int id;

    fn_8022C628(0x54415453, 0x4D414554, &id, &count);
    fn_801FCE10(0,
                "use 'TATS' insert into 'MAET' set 'DIGT' = \x82 and 'PYTT' = \x82 and 'DIOT' = \x82 and "
                "'DROT' = \x82 and 'LGLT' = \x82 and 'SIVT' = \x83 and 'RUMT' = \x85 and 'ANDT' = \x88 and "
                "'LDTC' = \x82\n",
                id, type, id, 0, logo, 1, 3, pName, 1);
    return id;
}

void fn_8008463C(int *pLogo, int *pFirst, int *pSecond, int *pThird);
void fn_800846F4(int logo, char *pName, int size);

int fn_8008454C(int type, int logo, const char *pName)
{
    char name[33];
    int values[4];
    int id;

    fn_8008463C(&values[0], &values[1], &values[2], &values[3]);
    if (logo != -1) {
        values[0] = logo;
    }
    if (pName && fn_801C3180(pName)) {
        fn_801C2EF0(name, pName, 33);
    } else {
        fn_800846F4(values[0], name, 33);
    }
    values[0] += 45;
    if (values[0] < 46 || values[0] > 132) {
        values[0] = fn_8022C8F0(46, 133);
    }
    id = fn_800844B8(name, type, values[0]);
    fn_801FCE10(0, "use 'TATS' update 'MAET' set '1CMT' = \x85 and '2CMT' = \x85 and '3CMT' = \x85 where 'DIGT' = \x85\n",
                values[1], values[2], values[3], id);
    return id;
}

void fn_8008463C(int *pLogo, int *pFirst, int *pSecond, int *pThird)
{
    QueryCursor cursor;
    QueryResult result;

    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "use 'TATS' declare \x8a cursor for select * from 'LTPS'\n", &cursor);
    cursor.mUnknown4 = fn_80237390(1, 0, result.mUnknown0 - 1);
    fn_801FCE10(0, "use 'TATS' fetch from \x8a 'LGLT' into \x85 and '1CMT' into \x85 and '2CMT' into \x85 and '3CMT' into \x85\n",
                &cursor, pLogo, pFirst, pSecond, pThird);
    if (cursor.mUnknown0) {
        fn_801FCFA0(&cursor);
    }
}

void fn_800846F4(int logo, char *pName, int size)
{
    QueryCursor cursor;
    QueryResult result;
    int flag = 0;

    if (fn_801F9A90(0, 0x43544E52)) {
        flag = 1;
        fn_8022EF8C(0, 0x43544E52);
    }
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    fn_801FCE10(&result, "declare \x8a cursor for select * from 'CTNR' where ('LGLT' = \x82)\n", &cursor, logo);
    int count = result.mUnknown0;
    if (count > 0) {
        cursor.mUnknown4 = fn_80237390(1, 0, count - 1);
        fn_801FCE10(0, "fetch from \x8a 'ETNR' into \x88\n", &cursor, pName);
    } else {
        fn_801C2EF0(pName, "Playaz", size);
    }
    if (cursor.mUnknown0) {
        fn_801FCFA0(&cursor);
    }
    if (flag) {
        fn_8022EFBC(0, 0x43544E52);
    }
}

void fn_80084808(int a, int *pIds, int *pCounts, int count, int *pOut, int total)
{
    int prev;
    int k;
    int i;
    int j;

    fn_800828FC();
    prev = -1;
    k = 0;
    if (count) {
        for (i = 0; i < count; i++) {
            int n = pCounts[i];

            for (j = 0; j < n; j++) {
                prev = pOut[k] = fn_80082AB0(pIds[k], a, prev);
                k++;
                fn_80023024(1);
            }
        }
    }
    while (k < total) {
        prev = pOut[k++] = fn_80082A64(a, prev);
        fn_80023024(1);
    }
    fn_800829D8();
}

void fn_80084908(int a, int b, int *pOut, unsigned int count, int *pIn, unsigned int size)
{
    int *pList = (int *)fn_801D2B7C((size + 1) * 4, 0, 0);
    int *pIds = (int *)fn_801D2B7C(count * 4, 0, 0);
    int excluded[15];
    unsigned int i;
    unsigned int j;

    memcpy(pList, pIn, size * 4);
    fn_801D34D0(excluded, sizeof(excluded), 0xFF, 4);
    pList[size] = 0x7FFF;
    lbl_803EC86C = fn_802372EC(0, 5);
    fn_8003E710(lbl_803EC86C, pList, &lbl_803EA7E8);
    for (i = 0; i < count; i++) {
        int id;
        int category;

        fn_8003EB2C(lbl_803EA7E8, pList, excluded, &id, &category);
        pIds[i] = id;
        excluded[i] = category;
        for (j = 0; j < size; j++) {
            if (id == pList[j]) {
                fn_801C2030(&pList[j], &pList[j + 1], (size - j) * 4);
                size--;
            }
        }
    }
    fn_8003E8B8(&lbl_803EA7E8);
    memcpy(pOut, pIds, count * 4);
    fn_801D2BD0(pList);
    fn_801D2BD0(pIds);
}

void fn_80084DAC(int team, int *pIds, unsigned int count);

void fn_80084A8C(int team, int *pList, int side, int count)
{
    Record_8003B6BC record;
    Object_8007A334 query;
    Object_8008044C cursor;
    int i;

    fn_8003DE74(side, pList);
    fn_8003B6BC(side, &record);
    fn_80084DAC(team, record.mUnknown, count);
    fn_80083E40(&query, 0, 0x54415453);
    fn_80084034(&query, team, 0);
    int type = fn_8008400C(&query);
    fn_80083F68(&query);
    if (side == 0) {
        fn_8007CAEC(0, team);
        fn_8022A508(0, team, team, type, -1);
        fn_8022DC7C(0);
        fn_8022DCB0(0);
    } else {
        fn_8007CAEC(1, team);
        fn_8022A508(1, team, team, type, -1);
        fn_8022DCE4(0);
        fn_8022DD18(0);
    }
    fn_8008044C(&cursor, 0, 0x54415453);
    for (i = 0; i < count; i++) {
        fn_800809C4(&cursor, record.mUnknown[i], 0);
        fn_80081F50(&cursor, side, 1);
    }
    fn_8008056C(&cursor);
}

void fn_80084C24(int team, int *pList, int side, int count)
{
    Record_8003B6BC record;
    Object_8007A334 query;
    Object_8008044C cursor;
    int i;

    fn_8003DE74(side, pList);
    fn_8003B6BC(side, &record);
    fn_80083E40(&query, 0, 0x54415453);
    fn_80084034(&query, team, 0);
    int type = fn_8008400C(&query);
    fn_80083F68(&query);
    if (side == 0) {
        fn_8007CAEC(0, team);
        fn_8022A508(0, team, team, type, -1);
        fn_8022DC7C(0);
        fn_8022DCB0(0);
    } else {
        fn_8007CAEC(1, team);
        fn_8022A508(1, team, team, type, -1);
        fn_8022DCE4(0);
        fn_8022DD18(0);
    }
    fn_8008044C(&cursor, 0, 0x54415453);
    for (i = 0; i < count; i++) {
        fn_800809C4(&cursor, record.mUnknown[i], 0);
        fn_80081F50(&cursor, side, 1);
    }
    fn_8008056C(&cursor);
}

int fn_80084F50(int id, int half, int *pList);

void fn_80084DAC(int team, int *pIds, unsigned int count)
{
    int copy[14];
    unsigned short found = count;
    int table = -1;
    int *pNewIds = (int *)fn_801D2B7C(count * 4, 0, 0);
    int *pOldIds = (int *)fn_801D2B7C(count * 4, 0, 0);
    unsigned int i;
    unsigned int j;

    fn_80229AA4(0x54415453, 0x59414C50, pNewIds, &found);
    for (i = 0; i < count; i++) {
        fn_801F9980(0x54415453, &table);
        pOldIds[i] = pIds[i];
        fn_801FCE10(0, "use 'TATS' select into \x8c * from 'YALP' where ('DIGP' = \x82)\n", table, pOldIds[i]);
        fn_801FCE10(0, "use 'TATS' update \x8c set 'DIGT' = \x82 and 'DIGP' = \x82 where ('DIGP' = \x82)\n", table, team,
                    pNewIds[i], pOldIds[i]);
        fn_801FCE10(0, "use 'TATS' insert into \x8c.'YALP' * select * from \x8c\n", 0x54415453, table);
        fn_801F967C(0x54415453, table);
    }
    for (i = 0; i < 14; i++) {
        copy[i] = pIds[i];
    }
    for (i = 0; i < count; i++) {
        for (j = 0; j <= 1; j++) {
            pIds[fn_80084F50(pOldIds[i], j, copy)] = pNewIds[i];
        }
    }
    fn_801D2BD0(pNewIds);
    fn_801D2BD0(pOldIds);
}

int fn_80084F50(int id, int half, int *pList)
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

void fn_80084FA8(int value)
{
    fn_8021E2B4(fn_8021EA44(1), 4, value);
}

void fn_80084FE4(int value)
{
    fn_8021E72C(fn_8021EA44(1), 4, value);
}

void fn_80085020(Object_8007A334 *pObject)
{
    fn_8007A334(pObject, 0x52545354, 0x59545453, 0, 0, 0x54415453);
}

void fn_80085060(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_80085080(Object_8007A334 *pObject, int value, int *pResult)
{
    return fn_8007A7F4(pObject, 0x59545453, value, 0, pResult);
}

int fn_800850B8(Object_8007A334 *pObject, int category)
{
    return fn_8007A98C(pObject, lbl_802D6B54[category]);
}

}
