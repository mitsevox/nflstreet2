#include "game/Key_8007A334.h"
#include "game/Object_8007A334.h"
#include "game/cu_8002ACB4.h"

/* Record filled by fn_80088CE0. */
struct Record_80088CE0 {
    signed char mIndex;
    char mName[132];
    int mUnknown136;
    int mUnknown140;
    unsigned int mUnknown144;
    int mUnknown148;
};

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

void fn_80088648(Object_8007A334 *pCursor, int db);
void fn_8008869C(Object_8007A334 *pCursor);
unsigned int fn_800886BC(int db);
int fn_8008872C(int db);
void fn_8008879C(int db, int value);
void fn_8008880C(int db, int value);
void fn_800888D0(int db, int value);
void fn_80088950(Object_8007A334 *pCursor, int index);
void fn_8008898C(Object_8007A334 *pCursor, int db);
void fn_80088A1C(Object_8007A334 *pCursor);
void fn_80088A3C(Object_8007A334 *pCursor, int set);
unsigned char fn_80088A74(Object_8007A334 *pCursor, int index);
void fn_80088AC8(Object_8007A334 *pCursor, int index, int value);
void fn_80088B24(Object_8007A334 *pCursor, int mode, unsigned char value);
void fn_80088C8C(Object_8007A334 *pCursor);
int fn_80088CAC(Object_8007A334 *pCursor, int a, int key, int *pResult);
void fn_80088CE0(Object_8007A334 *pCursor, Record_80088CE0 *pRecord);
unsigned char fn_80088D84(Object_8007A334 *pCursor);
}

extern "C" {

void fn_80088648(Object_8007A334 *pCursor, int db)
{
    fn_8007A334(pCursor, 0x464E4955, 0x41434955, 0, 0, fn_8022F3D4(db));
}

void fn_8008869C(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

unsigned int fn_800886BC(int db)
{
    Object_8007A334 cursor;
    unsigned int value;

    fn_80088648(&cursor, db);
    value = fn_8007A98C(&cursor, 0x41434955);
    fn_8008869C(&cursor);
    return value;
}

int fn_8008872C(int db)
{
    Object_8007A334 cursor;
    int value;

    fn_80088648(&cursor, db);
    value = fn_8007A98C(&cursor, 0x54434955);
    fn_8008869C(&cursor);
    return value;
}

void fn_8008879C(int db, int value)
{
    Object_8007A334 cursor;

    fn_80088648(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, value);
    fn_8008869C(&cursor);
}

/* Adds value to both the 'ACIU' and 'TCIU' columns, clamping it so that
   'TCIU' does not exceed 9999999. */
void fn_8008880C(int db, int value)
{
    Object_8007A334 cursor;
    unsigned int current;
    unsigned int total;

    fn_80088648(&cursor, db);
    current = fn_8007A98C(&cursor, 0x41434955);
    total = fn_8007A98C(&cursor, 0x54434955);
    if (total + value > 9999999) {
        value = 9999999 - total;
    }
    fn_8007ABA4(&cursor, 0x41434955, current + value);
    fn_8007ABA4(&cursor, 0x54434955, total + value);
    fn_8008869C(&cursor);
}

void fn_800888D0(int db, int value)
{
    Object_8007A334 cursor;

    fn_80088648(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, fn_8007A98C(&cursor, 0x41434955) - value);
    fn_8008869C(&cursor);
}

void fn_80088950(Object_8007A334 *pCursor, int index)
{
    fn_8008898C(pCursor, fn_8022F358(index));
}

void fn_8008898C(Object_8007A334 *pCursor, int db)
{
    Key_8007A334 keys[2];

    keys[0].Set(0x53544653, 0x49434655, 0);
    keys[1].Set(-1, -1, 3);
    fn_8007A334(pCursor, 0x43465355, 0x49434655, keys, 0, fn_8022F3D4(db));
}

void fn_80088A1C(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

void fn_80088A3C(Object_8007A334 *pCursor, int set)
{
    fn_8007AA90(pCursor, 0x43434655, set != 0);
}

unsigned char fn_80088A74(Object_8007A334 *pCursor, int index)
{
    fn_8007A7F4(pCursor, 0x49434655, index, 0, 0);
    return fn_8007A934(pCursor, 0x43434655);
}

void fn_80088AC8(Object_8007A334 *pCursor, int index, int value)
{
    fn_8007A7F4(pCursor, 0x49434655, index, 0, 0);
    fn_8007AA90(pCursor, 0x43434655, value);
}

void fn_80088B24(Object_8007A334 *pCursor, int mode, unsigned char value)
{
    Key_8007A334 keys[2];
    Object_80023BBC root;
    Object_80023BBC left;
    Object_80023BBC right;
    int column = 0x54464653;

    keys[0].Set(0x53544653, 0x49464653, 0);
    keys[1].Set(-1, -1, 3);
    if (mode == 0) {
        fn_8007A334(pCursor, 0x53544653, 0x49464653, keys, 0, 0x54415453);
    } else if (mode == 1 || mode == 2) {
        if (mode == 2) {
            column = 0x51464653;
        }
        root.Set(11, &left, &right);
        left.Set(6, ((long long)0x53544653 << 32) | (unsigned int)column, 3, value);
        right.Set(6, 0x535446534E464653LL, 3, 1);
        fn_8007A334(pCursor, 0x53544653, 0x49464653, keys, &root, 0x54415453);
    }
}

void fn_80088C8C(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int fn_80088CAC(Object_8007A334 *pCursor, int a, int key, int *pResult)
{
    return fn_8007A7F4(pCursor, 0x51464653, key, a, pResult);
}

void fn_80088CE0(Object_8007A334 *pCursor, Record_80088CE0 *pRecord)
{
    pRecord->mIndex = fn_8007A98C(pCursor, 0x49464653);
    fn_8007AA3C(pCursor, 0x44464653, (int)pRecord->mName, sizeof(pRecord->mName));
    pRecord->mUnknown136 = fn_8007A98C(pCursor, 0x54464653);
    pRecord->mUnknown140 = fn_8007A98C(pCursor, 0x51464653);
    pRecord->mUnknown144 = fn_8007A98C(pCursor, 0x50464653);
    pRecord->mUnknown148 = fn_8007A98C(pCursor, 0x57464653);
}

unsigned char fn_80088D84(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x49464653);
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
