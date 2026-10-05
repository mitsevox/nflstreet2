#include "game/cu_80190208.h"
#include "game/Object_8007A334.h"
#include "game/fn_801FCE10.h"
#include "game/QueryStatus.h"
#include <string.h>

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int handle);
int fn_8007A934(Object_8007A334 *pObject, int key);
char *fn_801C2F88(char *pDest, const char *pSource, unsigned int count);
}

static signed char sIndex = -1;

extern "C" {
void fn_80190208(Object_8007A334 *pObject, int index)
{
    fn_8007A334(pObject, 0x53544843, 0x58494843, 0, 0,
                fn_8022F3D4(fn_8022F358(index)));
}

int fn_80190260(Object_8007A334 *pObject)
{
    return fn_8007A3C4(pObject);
}

void fn_80190280(int index)
{
    sIndex = index;
}

void fn_80190288(void)
{
    sIndex = -1;
}

int fn_80190294(void)
{
    int count;
    int status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'STHC' where 'LUHC' = 1\n",
                             fn_8022F3D4(fn_8022F358(sIndex)), &count);
    if (QUERY_STATUS_ACCEPTED(status) && status != 0x17) return count;
    return 0;
}

int fn_80190310(void)
{
    int count;
    int status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'STHC' where 'LUHC' = 0\n",
                             fn_8022F3D4(fn_8022F358(sIndex)), &count);
    if (QUERY_STATUS_ACCEPTED(status) && status != 0x17) {
        if (count) return 0;
    }
    return 1;
}

int fn_80190394(void)
{
    int count;
    int status = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'STHC' where 'NEHC' = 1 and ( 'XIHC' < \x82 or 'XIHC' > \x82 )\n",
                             fn_8022F3D4(fn_8022F358(sIndex)), &count, 9, 21);
    if (QUERY_STATUS_ACCEPTED(status) && status != 0x17) {
        if (count) return 0;
    }
    return 1;
}

int fn_80190420(const char *pCode, int unused, char *pName)
{
    int id;
    if (!pName) {
        int status = fn_801FCE10(0, "use 'TATS' select 'XIHC' into \x82 from 'DCHC' where 'DCHC' = \x88 and 'UTHC' = 1\n", &id, 0);
        if (QUERY_STATUS_ACCEPTED(status) && status != 0x17) return id;
        return 56;
    } else {
        int status = fn_801FCE10(0, "use 'TATS' select 'XIHC' into \x82 and 'ANHC' into \x88 from 'DCHC' where 'DCHC' = \x88 and 'UTHC' = 1\n", &id, pName, pCode);
        if (QUERY_STATUS_ACCEPTED(status) && status != 0x17) return id;
    }
    return 56;
}

int fn_801904E0(int index)
{
    int found = 0;
    int handle = fn_8022F3D4(fn_8022F358(sIndex));
    QueryCursor cursor;
    int id;
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "use \x8c declare \x8a fastcursor for select 'XIHC' into \x82 from 'STHC' where 'LUHC' = 1\n", handle, &cursor, &id) == 0) {
        cursor.mUnknown4 = index;
        if (cursor.mUnknown0) {
            int status = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            if (QUERY_STATUS_ACCEPTED(status) == 1 && status != 0x15) found = 1;
        }
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    if (found) return id;
    return 56;
}

int fn_801905E0(int index, int *pId, char *pName, int count, int *pEnabled)
{
    char name[32];
    QueryCursor cursor;
    int id;
    int enabled;
    int marked;
    int found = 0;
    int handle = fn_8022F3D4(fn_8022F358(sIndex));
    cursor.mUnknown0 = 0;
    cursor.mUnknown4 = 0;
    cursor.mUnknown8 = -1;
    cursor.mUnknown12 = 0;
    if (fn_801FCE10(0, "use \x8c declare \x8a fastcursor for select 'XIHC' into \x85 and 'NEHC' into \x85 from 'STHC' where 'LUHC' = 1\n", handle, &cursor, &id, &enabled) == 0) {
        cursor.mUnknown4 = index;
        if (cursor.mUnknown0) {
            int status = fn_801FCE10(0, "fetch from \x8a\n", &cursor);
            if (QUERY_STATUS_ACCEPTED(status) == 1 && status != 0x15) {
                found = 1;
                *pId = id;
                *pEnabled = enabled;
            }
        }
    }
    if (cursor.mUnknown0) fn_801FCFA0(&cursor);
    if (found) {
        if (fn_801FCE10(0, "use 'TATS' select 'ANHC' into \x88 and 'GQHC' into \x82 from 'DCHC' where 'XIHC' = \x82\n", name, &marked, id) == 0) {
            strncpy(pName, name, count);
            if (marked) fn_801C2F88(pName, " *", 2);
        } else {
            found = 0;
        }
    }
    return found;
}

unsigned char fn_80190768(int id)
{
    Object_8007A334 cursor;
    int value = 0;
    fn_80190208(&cursor, sIndex);
    if (fn_8007A894(&cursor, 0x58494843, id, 0, 0)) {
        value = fn_8007A934(&cursor, 0x4C554843);
    }
    fn_80190260(&cursor);
    return value;
}

int fn_80190808(int id)
{
    Object_8007A334 cursor;
    fn_80190208(&cursor, sIndex);
    if (fn_8007A894(&cursor, 0x58494843, id, 0, 0)) {
        fn_8007AA90(&cursor, 0x4C554843, 1);
    }
    return fn_80190260(&cursor);
}

int fn_801908A0(int id)
{
    Object_8007A334 cursor;
    int value = 0;
    fn_80190208(&cursor, sIndex);
    if (fn_8007A894(&cursor, 0x58494843, id, 0, 0)) {
        value = fn_8007A934(&cursor, 0x4E454843);
    }
    fn_80190260(&cursor);
    if (value) return 1;
    return 0;
}

int fn_8019094C(int id)
{
    Object_8007A334 cursor;
    fn_80190208(&cursor, sIndex);
    if (fn_8007A894(&cursor, 0x58494843, id, 0, 0)) {
        fn_8007AA90(&cursor, 0x4E454843, 1);
    }
    return fn_80190260(&cursor);
}

int fn_801909E4(int id)
{
    Object_8007A334 cursor;
    fn_80190208(&cursor, sIndex);
    if (fn_8007A894(&cursor, 0x58494843, id, 0, 0)) {
        fn_8007AA90(&cursor, 0x4E454843, 0);
    }
    return fn_80190260(&cursor);
}
}
