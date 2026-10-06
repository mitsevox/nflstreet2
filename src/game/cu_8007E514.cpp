#include "game/Object_8007A334.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_801FA844(int a, char *b, int c, unsigned long long key, QueryResult *pValue, QueryResult *pResult);
int fn_8007A934(Object_8007A334 *pObject, int key);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int handle);
int fn_8022F4BC(void);
}

static int lbl_803EA7B0[2] = { 0x504F5355, 0x50445355 };

extern "C" {

void fn_8007E514(Object_8007A334 *pObject, signed char db)
{
    fn_8007A334(pObject, 0x474C4B4C, 0x4C474C54, 0, 0, fn_8022F3D4(fn_8022F358(db)));
}

void fn_8007E56C(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_8007E58C(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x4C474C54);
}

int fn_8007E5B4(Object_8007A334 *pObject)
{
    return fn_8007A98C(pObject, 0x4B4C474C) != 0;
}

int fn_8007E5EC(int a)
{
    unsigned char result = 0;
    Object_8007A334 cursor;

    fn_8007E514(&cursor, fn_8022F384(fn_8022F4BC()));
    if (fn_8007A7F4(&cursor, 0x4C474C54, a, 0, 0)) {
        result = fn_8007A98C(&cursor, 0x574E5247) != 0;
    }
    fn_8007E56C(&cursor);
    return result;
}

void fn_8007E69C(int a)
{
    Object_8007A334 cursor;

    fn_8007E514(&cursor, fn_8022F384(fn_8022F4BC()));
    if (fn_8007A7F4(&cursor, 0x4C474C54, a, 0, 0)) {
        fn_8007ABA4(&cursor, 0x574E5247, 0);
    }
    fn_8007E56C(&cursor);
}

void fn_8007E738(int a)
{
    Object_8007A334 cursor;

    fn_8007E514(&cursor, fn_8022F384(fn_8022F4BC()));
    if (fn_8007A7F4(&cursor, 0x4C474C54, a, 0, 0)) {
        fn_8007ABA4(&cursor, 0x4B4C474C, 0);
    }
    fn_8007E56C(&cursor);
}

int fn_8007E7D4(Object_8007A334 *pObject)
{
    QueryResult result;
    QueryResult value;

    fn_801FA844(pObject->mUnknown4, pObject->mUnknown20, 0,
                ((unsigned long long)(unsigned int)pObject->mUnknown8 << 32) | 0x58505355,
                &value, &result);
    return value.mUnknown4;
}

void fn_8007E828(Object_8007A334 *pObject, signed char db, int index)
{
    int handle = fn_8022F3D4(fn_8022F358(db));
    fn_8007A334(pObject, lbl_803EA7B0[index], 0x44505355, 0, 0, handle);
}

void fn_8007E888(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

void fn_8007E8A8(int index, int a)
{
    Object_8007A334 cursor;

    fn_8007E828(&cursor, fn_8022F384(fn_8022F4BC()), index);
    if (fn_8007A894(&cursor, 0x44505355, a, 0, 0)) {
        fn_8007AA90(&cursor, 0x58505355, fn_8007E7D4(&cursor) + 1);
    }
    fn_8007E888(&cursor);
}

void fn_8007E954(signed char db, int index)
{
    Object_8007A334 cursor;

    fn_8007E828(&cursor, db, index);
    if (fn_8007A444(&cursor)) {
        do {
            if (fn_8007A934(&cursor, 0x58505355) == -1) {
                fn_8007AA90(&cursor, 0x58505355, fn_8007E7D4(&cursor) + 1);
            }
        } while (fn_8007A510(&cursor));
    }
    fn_8007E888(&cursor);
}

void fn_8007EA04(signed char db, int index)
{
    int fetched = 1;
    int open = 1;
    Object_8007A334 cursor;
    QueryCursor query;
    int value;
    int table;
    int i = 0;
    int row;

    table = index == 0 ? 0x504F5355 : 0x50445355;
    fn_8022F3D4(fn_8022F358(db));
    query.mUnknown0 = 0;
    query.mUnknown4 = 0;
    query.mUnknown8 = -1;
    query.mUnknown12 = 0;
    int status = fn_801FCE10(0, "use 'TATS' declare \x8a fastcursor for select 'XPSU' into \x85 from \x8c\n",
                             &query, &value, table);
    if (status == 0) {
        fn_8007E828(&cursor, db, index);
        row = fn_8007A444(&cursor);
        while (open && fetched && row) {
            query.mUnknown4 = i++;
            if (query.mUnknown0 && QUERY_STATUS_ACCEPTED(status) == 1 && status != 0x15) {
                status = fn_801FCE10(0, "fetch from \x8a\n", &query);
                if (QUERY_STATUS_ACCEPTED(status) == 1 && status != 0x15) {
                    fn_8007AA90(&cursor, 0x58505355, value);
                    row = fn_8007A510(&cursor);
                } else {
                    fetched = 0;
                }
            } else {
                open = 0;
            }
        }
        fn_8007E888(&cursor);
    }
    if (query.mUnknown0) {
        fn_801FCFA0(&query);
    }
}

void fn_8007EBDC(Object_8007A334 *pObject, int db)
{
    fn_8007A334(pObject, 0x4D45544C, 0x44494754, 0, 0, fn_8022F3D4(fn_8022F358(db)));
}

void fn_8007EC34(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

int fn_8007EC54(Object_8007A334 *pObject, int id)
{
    int result = 0;

    if (fn_8007A7F4(pObject, 0x44494754, id, 0, 0)) {
        result = !fn_8007A98C(pObject, 0x53495654);
    }
    return result;
}

void fn_8007ECBC(int db, int id)
{
    Object_8007A334 cursor;

    fn_8007EBDC(&cursor, db);
    if (fn_8007A7F4(&cursor, 0x44494754, id, 0, 0)) {
        fn_8007ABA4(&cursor, 0x53495654, 1);
    }
    fn_8007EC34(&cursor);
}

void fn_8007ED50(int db, int id)
{
    Object_8007A334 cursor;

    fn_8007EBDC(&cursor, db);
    if (fn_8007A7F4(&cursor, 0x44494754, id, 0, 0)) {
        fn_8007ABA4(&cursor, 0x53495654, 0);
    }
    fn_8007EC34(&cursor);
}

void fn_8007EDE4(int db)
{
    Object_8007A334 cursor;

    fn_8007EBDC(&cursor, db);
    if (fn_8007A444(&cursor)) {
        do {
            fn_8007ABA4(&cursor, 0x53495654, 1);
        } while (fn_8007A510(&cursor));
    }
    fn_8007EC34(&cursor);
}

void fn_8007EE70(int db)
{
    Object_8007A334 cursor;

    fn_8007EBDC(&cursor, db);
    if (fn_8007A444(&cursor)) {
        do {
            fn_8007ABA4(&cursor, 0x53495654, 0);
        } while (fn_8007A510(&cursor));
    }
    fn_8007EC34(&cursor);
}

}
