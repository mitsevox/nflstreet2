#include "game/Object_8007A334.h"
#include "game/fn_801FCE10.h"

#include "game/Table_8007E020.h"

extern "C" {
int fn_801F967C(int handle, int table);
int fn_801F9980(int handle, int *pTable);
int fn_801FA844(int a, void *b, void *c, unsigned long long key, QueryResult *pValue, QueryResult *pResult);
int fn_8022F358(int index);
int fn_8022F384(int a);
int fn_8022F3D4(int handle);
int fn_8022F4BC(void);
}

extern "C" {

void fn_8007DDC8(Object_8007A334 *pObject, signed char db)
{
    fn_8007A334(pObject, 0x5245474C, 0x594B5047, 0, 0, fn_8022F3D4(fn_8022F358(db)));
}

void fn_8007DE20(Object_8007A334 *pObject)
{
    fn_8007A3C4(pObject);
}

void fn_8007DE40(Object_8007A334 *pObject, int key, unsigned char *pA, unsigned char *pB)
{
    *pA = 0;
    *pB = 0;
    if (fn_8007A7F4(pObject, 0x594B5047, key, 0, 0)) {
        if (fn_8007A98C(pObject, 0x4B434C47)) {
            *pA = 1;
        }
        if (fn_8007A98C(pObject, 0x574E5247)) {
            *pB = 1;
        }
    }
}

int fn_8007DEE0(Object_8007A334 *pObject, int key)
{
    int result = 0;

    if (fn_8007A7F4(pObject, 0x594B5047, key, 0, 0) && fn_8007A98C(pObject, 0x4B434C47)) {
        result = 1;
    }
    return result;
}

int fn_8007DF4C(int key)
{
    Object_8007A334 cursor;
    int result;

    fn_8007DDC8(&cursor, fn_8022F384(fn_8022F4BC()));
    result = fn_8007DEE0(&cursor, key);
    fn_8007DE20(&cursor);
    return result;
}

void fn_8007DFC4(Object_8007A334 *pObject, int id)
{
    if (fn_8007A7F4(pObject, 0x594B5047, id, 0, 0)) {
        fn_8007ABA4(pObject, 0x574E5247, 0);
    }
}

int fn_8007E020(int type, int a, int b)
{
    QueryResult result;
    Table_8007E020 tables[3];
    Object_80023BBC join;
    Object_80023BBC typeFilter;
    Object_80023BBC both;
    Object_80023BBC idFilter;
    Object_80023BBC extra;
    QueryResult value;
    int table;
    int found = 0;
    Object_80023BBC *pFilter;
    Object_80023BBC *pExtra = 0;

    int db = fn_8022F3D4(fn_8022F4BC());
    fn_801F9980(0x54415453, &table);
    if (fn_801FCE10(&result, "use \x8c select into \x8c.\x8c * from \x8c where 'WNRG' = 1 and 'KCLG' = 0\n",
                    db, 0x54415453, table, 0x5245474C) != 23) {
        unsigned int t = table;
        unsigned long long column = 0x594B5047;
        join.Set(6, 0x52414547594B5047LL, 6);
        join.mUnknown16.mValue.mLong = ((unsigned long long)t << 32) | column;
        typeFilter.Set(6, 0x5241454749545247LL, 3);
        typeFilter.mUnknown16.mValue.mInt = type;
        pFilter = &typeFilter;
        if (a >= 0) {
            both.Set(11, pFilter, &idFilter);
            idFilter.Set(6, 0x5241454749545347LL, 3);
            idFilter.mUnknown16.mValue.mInt = a;
            pFilter = &both;
        }
        if (b == 0) {
            unsigned long long column2 = 0x4B4C4347;
            pExtra = &extra;
            pExtra->Set(6, ((unsigned long long)table << 32) | column2, 3, 0);
        }
        tables[0].Set(0x52414547, 0, pFilter);
        tables[1].Set(table, 2, &join);
        tables[2].Set(-1, 2, 0);
        if (fn_801FA844(0x54415453, tables, pExtra, ((unsigned long long)(unsigned int)table << 32) | 0x574E5247,
                        &value, 0) != 23) {
            found = 1;
        }
    }
    fn_801F967C(0x54415453, table);
    return found;
}

void fn_8007E274(int key)
{
    Object_8007A334 cursor;

    fn_8007DDC8(&cursor, fn_8022F384(fn_8022F4BC()));
    if (fn_8007A7F4(&cursor, 0x594B5047, key, 0, 0)) {
        fn_8007ABA4(&cursor, 0x4B434C47, 0);
        fn_8007ABA4(&cursor, 0x574E5247, 1);
    }
    fn_8007DE20(&cursor);
}

void fn_8007E324(int key)
{
    Object_8007A334 cursor;

    fn_8007DDC8(&cursor, fn_8022F384(fn_8022F4BC()));
    if (fn_8007A7F4(&cursor, 0x594B5047, key, 0, 0)) {
        fn_8007ABA4(&cursor, 0x4B434C47, 1);
        fn_8007ABA4(&cursor, 0x574E5247, 0);
    }
    fn_8007DE20(&cursor);
}

void fn_8007E3D4(signed char db)
{
    Object_8007A334 cursor;

    fn_8007DDC8(&cursor, db);
    if (fn_8007A444(&cursor)) {
        do {
            fn_8007ABA4(&cursor, 0x4B434C47, 0);
            fn_8007ABA4(&cursor, 0x574E5247, 1);
        } while (fn_8007A510(&cursor));
    }
    fn_8007DE20(&cursor);
}

void fn_8007E474(signed char db)
{
    Object_8007A334 cursor;

    fn_8007DDC8(&cursor, db);
    if (fn_8007A444(&cursor)) {
        do {
            fn_8007ABA4(&cursor, 0x4B434C47, 1);
            fn_8007ABA4(&cursor, 0x574E5247, 0);
        } while (fn_8007A510(&cursor));
    }
    fn_8007DE20(&cursor);
}

}
