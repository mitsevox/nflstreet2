#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/Object_8007A334.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8018C48C(int tag);
int fn_8018BA4C(void);
void fn_8018BB24(int index, int a);
void fn_80086BA4(int index);
void fn_80086A64(void);
void fn_80086994(void);
void fn_80086B50(void);

void fn_8018E55C(int index);
void fn_8018E7A0(int index, int value);
void fn_8018E828(int index, int value);

static void fn_8018DF98(int index, int *pFlags)
{
    fn_801FCE10(0, "use \x8c select 'GLFS' into \x85 from 'TADS'\n",
                fn_8022F3D4(fn_8022F358(index)), pFlags);
}

int fn_8018DFE4(int index, int mask)
{
    int flags;
    int result = 0;

    fn_8018DF98(index, &flags);
    if (flags & mask) {
        result = 1;
    }
    return result;
}

void fn_8018E02C(int index, int mask, int set)
{
    int db = fn_8022F3D4(fn_8022F358(index));
    int flags;

    fn_8018DF98(index, &flags);
    if (set) {
        flags |= mask;
    } else {
        flags &= ~mask;
    }
    fn_801FCE10(0, "use \x8c update 'TADS' set 'GLFS' = \x85\n", db, flags);
}

static int fn_8018E0B0(Object_8007A334 *pCursor)
{
    return fn_8007A410(pCursor) == 0;
}

int fn_8018E0D8(int n)
{
    switch (n) {
    case 0:
        return 0x20;
    case 1:
        return 0x40;
    case 2:
        return 0x80;
    }
    return 0;
}

void fn_8018E11C(Object_8007A334 *pCursor, int index)
{
    fn_8007A334(pCursor, 0x59505453, 0x44494750, 0, 0, fn_8022F3D4(fn_8022F358(index)));
}

void fn_8018E174(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int fn_8018E194(Object_8007A334 *pCursor, int row, char *pBuffer, int size)
{
    int ok;

    if (fn_8018E0B0(pCursor)) {
        *pBuffer = 0;
        ok = 0;
    } else {
        fn_8007A600(pCursor, row);
        fn_8007AA3C(pCursor, 0x414E4650, (int)pBuffer, size);
        ok = 1;
    }
    return ok;
}

int fn_8018E20C(Object_8007A334 *pCursor, int row, char *pBuffer, int size)
{
    int ok;

    if (fn_8018E0B0(pCursor)) {
        *pBuffer = 0;
        ok = 0;
    } else {
        fn_8007A600(pCursor, row);
        fn_8007AA3C(pCursor, 0x414E4C50, (int)pBuffer, size);
        ok = 1;
    }
    return ok;
}

/* Writes the 'ANLP' text of the row, preceded by the first character of its
   'ANFP' text and ". " when that text is not empty. */
int fn_8018E284(Object_8007A334 *pCursor, int row, char *pName)
{
    char first[12];
    char last[15];
    int ok;
    int length;

    if (fn_8018E0B0(pCursor)) {
        ok = 0;
    } else {
        ok = fn_8018E194(pCursor, row, first, sizeof(first));
        length = 0;
        if (ok) {
            ok = fn_8018E20C(pCursor, row, last, sizeof(last));
            if (ok) {
                if (strlen(first)) {
                    pName[0] = first[0];
                    pName[1] = '.';
                    pName[2] = ' ';
                    length = 3;
                }
                strcpy(pName + length, last);
            }
        }
    }
    return ok;
}

int fn_8018E344(int index)
{
    int value = -1;

    fn_801FCE10(0, "use \x8c select 'PPXE' into \x82 from 'TADS'\n",
                fn_8022F3D4(fn_8022F358(index)), &value);
    return value;
}

void fn_8018E390(int index, int value)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'PPXE' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), value);
}

int fn_8018E3DC(int index)
{
    int value = -1;

    fn_801FCE10(0, "use \x8c select 'PVED' into \x82 from 'TADS'\n",
                fn_8022F3D4(fn_8022F358(index)), &value);
    return value;
}

void fn_8018E428(int index, int value)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'PVED' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), value);
}

void fn_8018E474(int index)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'GLFS' = \x85\n",
                fn_8022F3D4(fn_8022F358(index)), 0);
}

static void DeleteYptsRows(int index)
{
    fn_801FCE10(0, "use \x8c delete from 'YPTS' where 'DIGP' > 0\n",
                fn_8022F3D4(fn_8022F358(index)));
}

int fn_8018E4B4(void)
{
    int index = fn_8022F384(fn_8022F4BC());
    int result;

    fn_8018C48C(0x54415453);
    result = fn_8018BA4C();
    fn_8018BB24(index, result);
    fn_8018E55C(index);
    fn_8018E428(index, 250);
    fn_8018E390(index, 0);
    fn_8018E474(index);
    fn_8018E7A0(index, 1);
    fn_8018E828(index, -1);
    fn_80086BA4(index);
    fn_80086A64();
    fn_80086994();
    fn_80086B50();
    return result;
}

void fn_8018E55C(int index)
{
    fn_801FCE10(0, "use \x8c delete from 'CETS'\n", fn_8022F3D4(fn_8022F358(index)));
}

int fn_8018E598(int index)
{
    int count;
    int result = -1;

    if (fn_801FCE10(0, "use \x8c select count(*) into \x82 from 'CETS'\n",
                    fn_8022F3D4(fn_8022F358(index)), &count) == 0) {
        result = count;
    }
    return result;
}
}
