#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/Object_8007A334.h"
#include "game/cu_8018EC68.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F384(int a);
int fn_8022F4BC(void);
void fn_8018C48C(int tag);
int fn_8018BA4C(void);
void fn_8018BB24(int index, int a);
int fn_80086BA4(int index);
int fn_80086A64(void);
int fn_80086994(void);
int fn_80086B50(void);
void fn_8018B8B0(Object_8007A334 *pCursor);

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
int fn_8018E284(Object_8007A334 *pCursor, int row, char *pName, int size)
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

/* Deletes the 'YPTS' rows whose 'DIGP' is greater than 0, clears this file's 'TADS'
   and 'CETS' state and rewrites the defaults of the 'DIGP' 0 row. */
static void ResetYptsTadsCetsTables(void)
{
    Object_8007A334 cursor;
    int index = fn_8022F384(fn_8022F4BC());

    fn_801FCE10(0, "use \x8c delete from 'YPTS' where 'DIGP' > 0\n", fn_8022F3D4(fn_8022F4BC()));
    fn_8018E55C(index);
    fn_8018E428(index, 250);
    fn_8018E390(index, 0);
    fn_8018E474(index);
    fn_8018E7A0(index, 1);
    fn_8018E828(index, -1);
    fn_8018E11C(&cursor, index);
    if (fn_8007A7F4(&cursor, 0x44494750, 0, 0, 0)) {
        fn_8018B8B0(&cursor);
    }
    fn_8018E174(&cursor);
    fn_80086BA4(index);
    fn_80086A64();
    fn_80086994();
    fn_80086B50();
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

#if defined(DECOMP_COMPARE)
int fn_8018E5F4(int index, int id)
{
    int value;
    int found = 0;

    if (fn_801FCE10(0, "use \x8c select 'NETS' into \x82 from 'CETS' where 'NETS' = \x82\n",
                    fn_8022F3D4(fn_8022F358(index)), &value, id) == 0) {
        found = 1;
    }
    return found;
}

void fn_8018E658(int index, int id)
{
    fn_801FCE10(0, "use \x8c insert into 'CETS' set 'NETS' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), id);
}

int fn_8018E6A4(int index)
{
    return fn_8018EE78() - fn_8018E598(index);
}

int fn_8018E6E0(int index, int a)
{
    VetsRow_8018EC68 row;
    int result = 1;
    unsigned int count = fn_8018EE44(a);

    if (count) {
        unsigned int i;

        for (i = 0; i < count; i++) {
            if (fn_8018EDF0(a, i, &row) && !fn_8018E5F4(index, row.mNets)) {
                result = 0;
                break;
            }
        }
    } else if (a == 11) {
        result = 0;
    }
    return result;
}

int fn_8018E774(int index)
{
    return !fn_8018DFE4(index, 1);
}

void fn_8018E7A0(int index, int value)
{
    fn_8018E02C(index, 1, !value);
}

int fn_8018E7CC(int index)
{
    int value;
    int result = -1;

    if (fn_801FCE10(0, "use \x8c select 'LKSS' into \x82 from 'TADS'\n",
                    fn_8022F3D4(fn_8022F358(index)), &value) == 0) {
        result = value;
    }
    return result;
}

void fn_8018E828(int index, int value)
{
    fn_801FCE10(0, "use \x8c update 'TADS' set 'LKSS' = \x82\n",
                fn_8022F3D4(fn_8022F358(index)), value);
}

int fn_8018E874(int index, int n)
{
    return fn_8018DFE4(index, fn_8018E0D8(n));
}

void fn_8018E8B0(int index, int n, int set)
{
    fn_8018E02C(index, fn_8018E0D8(n), set);
}

int fn_8018E8F4(int index)
{
    return !fn_8018DFE4(index, 0x100);
}

void fn_8018E920(int index, int value)
{
    fn_8018E02C(index, 0x100, !value);
}

int fn_8018E94C(int index)
{
    return !fn_8018DFE4(index, 0x200);
}

void fn_8018E978(int index, int value)
{
    fn_8018E02C(index, 0x200, !value);
}
#endif
}
