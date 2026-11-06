#include "game/DbSortKey.h"
#include "game/DbCursor.h"
#include "game/Record_80088CE0.h"
#include "game/cu_8002ACB4.h"

/* State of the stream table lbl_802D6C24: the result word passed to the
   open operation. */
struct Stream_80088DB0 {
    unsigned int *mpResult;
};

extern "C" {
void fn_80089668(void);
void fn_800896A8(void *pData, unsigned int size);
void fn_800896EC(unsigned int *pResult);
int fn_8022F358(int index);
int fn_8022F3D4(int a);

void fn_80088648(DbCursor *pCursor, int db);
void fn_8008869C(DbCursor *pCursor);
unsigned int fn_800886BC(int db);
int fn_8008872C(int db);
void fn_8008879C(int db, int value);
void fn_8008880C(int db, int value);
void fn_800888D0(int db, int value);
void fn_80088950(DbCursor *pCursor, int index);
void fn_8008898C(DbCursor *pCursor, int db);
void fn_80088A1C(DbCursor *pCursor);
void fn_80088A3C(DbCursor *pCursor, int set);
unsigned char fn_80088A74(DbCursor *pCursor, int index);
void fn_80088AC8(DbCursor *pCursor, int index, int value);
void fn_80088B24(DbCursor *pCursor, int mode, unsigned char value);
void fn_80088C8C(DbCursor *pCursor);
int fn_80088CAC(DbCursor *pCursor, int a, int key, int *pResult);
void fn_80088CE0(DbCursor *pCursor, Record_80088CE0 *pRecord);
unsigned char fn_80088D84(DbCursor *pCursor);
}

extern "C" {

void fn_80088648(DbCursor *pCursor, int db)
{
    DbCursorOpen(pCursor, 0x464E4955, 0x41434955, 0, 0, fn_8022F3D4(db));
}

void fn_8008869C(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

unsigned int fn_800886BC(int db)
{
    DbCursor cursor;
    unsigned int value;

    fn_80088648(&cursor, db);
    value = DbCursorGetInt(&cursor, 0x41434955);
    fn_8008869C(&cursor);
    return value;
}

int fn_8008872C(int db)
{
    DbCursor cursor;
    int value;

    fn_80088648(&cursor, db);
    value = DbCursorGetInt(&cursor, 0x54434955);
    fn_8008869C(&cursor);
    return value;
}

void fn_8008879C(int db, int value)
{
    DbCursor cursor;

    fn_80088648(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, value);
    fn_8008869C(&cursor);
}

/* Adds value to both the 'ACIU' and 'TCIU' columns, clamping it so that
   'TCIU' does not exceed 9999999. */
void fn_8008880C(int db, int value)
{
    DbCursor cursor;
    unsigned int current;
    unsigned int total;

    fn_80088648(&cursor, db);
    current = DbCursorGetInt(&cursor, 0x41434955);
    total = DbCursorGetInt(&cursor, 0x54434955);
    if (total + value > 9999999) {
        value = 9999999 - total;
    }
    fn_8007ABA4(&cursor, 0x41434955, current + value);
    fn_8007ABA4(&cursor, 0x54434955, total + value);
    fn_8008869C(&cursor);
}

void fn_800888D0(int db, int value)
{
    DbCursor cursor;

    fn_80088648(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, DbCursorGetInt(&cursor, 0x41434955) - value);
    fn_8008869C(&cursor);
}

void fn_80088950(DbCursor *pCursor, int index)
{
    fn_8008898C(pCursor, fn_8022F358(index));
}

void fn_8008898C(DbCursor *pCursor, int db)
{
    DbSortKey keys[2];

    keys[0].Set(0x53544653, 0x49434655, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pCursor, 0x43465355, 0x49434655, keys, 0, fn_8022F3D4(db));
}

void fn_80088A1C(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

void fn_80088A3C(DbCursor *pCursor, int set)
{
    fn_8007AA90(pCursor, 0x43434655, set != 0);
}

unsigned char fn_80088A74(DbCursor *pCursor, int index)
{
    DbCursorFindInt(pCursor, 0x49434655, index, 0, 0);
    return DbCursorGetValue(pCursor, 0x43434655);
}

void fn_80088AC8(DbCursor *pCursor, int index, int value)
{
    DbCursorFindInt(pCursor, 0x49434655, index, 0, 0);
    fn_8007AA90(pCursor, 0x43434655, value);
}

void fn_80088B24(DbCursor *pCursor, int mode, unsigned char value)
{
    DbSortKey keys[2];
    DbFilter root;
    DbFilter left;
    DbFilter right;
    unsigned int column = 0x54464653;

    keys[0].Set(0x53544653, 0x49464653, 0);
    keys[1].Set(-1, -1, 3);
    if (mode == 0) {
        DbCursorOpen(pCursor, 0x53544653, 0x49464653, keys, 0, 0x54415453);
    } else {
        switch (mode) {
        case 2:
            column = 0x51464653;
            /* fall through */
        case 1: {
            unsigned int table = 0x53544653;

            root.Set(11, &left, &right);
            left.Set(6, ((unsigned long long)table << 32) | column, 3);
            left.mUnknown16.mValue.mInt = value;
            right.Set(6, 0x535446534E464653LL, 3);
            right.mUnknown16.mValue.mInt = 1;
            DbCursorOpen(pCursor, 0x53544653, 0x49464653, keys, &root, 0x54415453);
            break;
        }
        }
    }
}

void fn_80088C8C(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int fn_80088CAC(DbCursor *pCursor, int a, int key, int *pResult)
{
    return DbCursorFindInt(pCursor, 0x51464653, key, a, pResult);
}

void fn_80088CE0(DbCursor *pCursor, Record_80088CE0 *pRecord)
{
    pRecord->mIndex = DbCursorGetInt(pCursor, 0x49464653);
    fn_8007AA3C(pCursor, 0x44464653, (int)pRecord->mName, sizeof(pRecord->mName));
    pRecord->mUnknown136 = DbCursorGetInt(pCursor, 0x54464653);
    pRecord->mUnknown140 = DbCursorGetInt(pCursor, 0x51464653);
    pRecord->mUnknown144 = DbCursorGetInt(pCursor, 0x50464653);
    pRecord->mUnknown148 = DbCursorGetInt(pCursor, 0x57464653);
}

unsigned char fn_80088D84(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49464653);
}

static int fn_80088DB0(void *pStream, int a, int target, unsigned char reading)
{
    Stream_80088DB0 *pState = (Stream_80088DB0 *)pStream;
    int result = 0;

    pState->mpResult = (unsigned int *)target;
    if (target == 0) {
        result = 0x24;
    } else {
        fn_80089668();
    }
    return result;
}

static int fn_80088DF4(void *pStream)
{
    Stream_80088DB0 *pState = (Stream_80088DB0 *)pStream;

    if (pState->mpResult == 0) {
        return 3;
    }
    fn_800896EC(pState->mpResult);
    return 0;
}

static int fn_80088E2C(void *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    Stream_80088DB0 *pState = (Stream_80088DB0 *)pStream;
    int result = 3;

    if (pState->mpResult != 0) {
        fn_800896A8(pData, size);
        *pDone = size;
        result = 0;
    }
    return result;
}

static int fn_80088E7C(void *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    return 3;
}

static int fn_80088E84(unsigned int size)
{
    return 0;
}

StreamOps_8002ACB4 lbl_802D6C24 = {
    fn_80088DB0, fn_80088DF4, fn_80088E7C, fn_80088E2C, 0, fn_80088E84, 4,
};

}
