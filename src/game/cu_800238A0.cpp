#include "game/fn_801FCE10.h"
#include "game/DbCursor.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int a);
}

static int lbl_802F4684[8] = { 0x4C43444C, 0x494C4344, 0, 0, -1, -1, 3, 0 };
static int lbl_802F46A4[8] = { 0x4C43444C, 0x494C4344, 0, 0, -1, -1, 3, 0 };

extern "C" {
int fn_800238A0(int index)
{
    int count;
    int result = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LCDL' where 'LLCD' = 0\n",
                             fn_8022F3D4(fn_8022F358(index)), &count);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        return count;
    }
    return 0;
}

int fn_80023914(int index)
{
    int count;
    int result = fn_801FCE10(0, "use \x8c select count(*) into \x85 from 'LCDL' where 'WNRG' != 0\n",
                             fn_8022F3D4(fn_8022F358(index)), &count);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        return count;
    }
    return 0;
}

void fn_80023988(int a, char *pBuffer, int size)
{
    DbCursor cursor;

    DbCursorOpen(&cursor, 0x4C414344, 0x494C4344, 0, 0, 0x54415453);
    DbCursorFindValue(&cursor, 0x494C4344, a, 0, 0);
    fn_8007AA3C(&cursor, 0x4E4C4344, (int)pBuffer, size);
    DbCursorClose(&cursor);
}

unsigned char fn_80023A3C(int index, int a)
{
    DbCursor cursor;
    unsigned char result = 0;

    DbCursorOpen(&cursor, 0x4C43444C, 0x494C4344, 0, 0, fn_8022F3D4(fn_8022F358(index)));
    if (DbCursorFindValue(&cursor, 0x494C4344, a, 0, 0)) {
        result = DbCursorGetInt(&cursor, 0x574E5247) != 0;
    }
    DbCursorClose(&cursor);
    return result;
}

void fn_80023B08(int index, int a)
{
    DbCursor cursor;

    DbCursorOpen(&cursor, 0x4C43444C, 0x494C4344, 0, 0, fn_8022F3D4(fn_8022F358(index)));
    if (DbCursorFindValue(&cursor, 0x494C4344, a, 0, 0)) {
        fn_8007ABA4(&cursor, 0x574E5247, 0);
    }
    DbCursorClose(&cursor);
}

int fn_80023BBC(int index, int a)
{
    DbCursor cursor;
    int value;
    int found;
    int handle = fn_8022F3D4(fn_8022F358(index));
    DbFilter arg;

    arg.Set(6, 0x4C43444C4C4C4344LL, 3);
    arg.mUnknown16.mValue.mInt = 0;
    DbCursorOpen(&cursor, 0x4C43444C, 0x494C4344, lbl_802F4684, &arg, handle);
    found = DbCursorFindInt(&cursor, 0x494C4344, a, 0, &value);
    DbCursorClose(&cursor);
    if (found) {
        return value;
    }
    return -1;
}

int fn_80023CA4(int index, int a)
{
    int result = 0x1F;
    DbCursor cursor;
    int handle = fn_8022F3D4(fn_8022F358(index));
    DbFilter arg;

    arg.Set(6, 0x4C43444C4C4C4344LL, 3);
    arg.mUnknown16.mValue.mInt = 0;
    DbCursorOpen(&cursor, 0x4C43444C, 0x494C4344, lbl_802F46A4, &arg, handle);
    if (DbCursorSeek(&cursor, a)) {
        result = DbCursorGetInt(&cursor, 0x494C4344);
    }
    DbCursorClose(&cursor);
    return result;
}
}
