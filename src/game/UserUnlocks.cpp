/* A profile's points and unlockables: the points balance and lifetime total, which items
   are unlocked, and the list of items that can be unlocked. Also the stream type that
   computes a CRC-32 checksum of data written to it. */

#include "game/Key_8007A334.h"
#include "game/Object_8007A334.h"
#include "game/UnlockItem.h"
#include "game/cu_8002ACB4.h"

/* State of the stream table _ChecksumCRC32_Type: the result word passed to the
   open operation. */
struct ChecksumCRC32Stream {
    unsigned int *mpResult;
};

extern "C" {
void ChecksumCRC32Begin(void);
void ChecksumCRC32Update(void *pData, unsigned int size);
void ChecksumCRC32End(unsigned int *pResult);
int fn_8022F358(int index);
int fn_8022F3D4(int a);

void UserInfoOpen(Object_8007A334 *pCursor, int db);
void UserInfoClose(Object_8007A334 *pCursor);
unsigned int UserInfoGetPoints(int db);
int UserInfoGetTotalPoints(int db);
void UserInfoSetPoints(int db, int value);
void UserInfoAddPoints(int db, int value);
void UserInfoSpendPoints(int db, int value);
void UnlockStatusOpen(Object_8007A334 *pCursor, int index);
void UnlockStatusOpenDb(Object_8007A334 *pCursor, int db);
void UnlockStatusClose(Object_8007A334 *pCursor);
void UnlockStatusSetCurrent(Object_8007A334 *pCursor, int set);
unsigned char UnlockStatusGet(Object_8007A334 *pCursor, int index);
void UnlockStatusSet(Object_8007A334 *pCursor, int index, int value);
void UnlockListOpen(Object_8007A334 *pCursor, int mode, unsigned char value);
void UnlockListClose(Object_8007A334 *pCursor);
int UnlockListSeek(Object_8007A334 *pCursor, int a, int key, int *pResult);
void UnlockListReadItem(Object_8007A334 *pCursor, UnlockItem *pRecord);
unsigned char UnlockListGetIndex(Object_8007A334 *pCursor);
}

extern "C" {

void UserInfoOpen(Object_8007A334 *pCursor, int db)
{
    fn_8007A334(pCursor, 0x464E4955, 0x41434955, 0, 0, fn_8022F3D4(db));
}

void UserInfoClose(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

unsigned int UserInfoGetPoints(int db)
{
    Object_8007A334 cursor;
    unsigned int value;

    UserInfoOpen(&cursor, db);
    value = fn_8007A98C(&cursor, 0x41434955);
    UserInfoClose(&cursor);
    return value;
}

int UserInfoGetTotalPoints(int db)
{
    Object_8007A334 cursor;
    int value;

    UserInfoOpen(&cursor, db);
    value = fn_8007A98C(&cursor, 0x54434955);
    UserInfoClose(&cursor);
    return value;
}

void UserInfoSetPoints(int db, int value)
{
    Object_8007A334 cursor;

    UserInfoOpen(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, value);
    UserInfoClose(&cursor);
}

/* Adds value to both the 'ACIU' and 'TCIU' columns, clamping it so that
   'TCIU' does not exceed 9999999. */
void UserInfoAddPoints(int db, int value)
{
    Object_8007A334 cursor;
    unsigned int current;
    unsigned int total;

    UserInfoOpen(&cursor, db);
    current = fn_8007A98C(&cursor, 0x41434955);
    total = fn_8007A98C(&cursor, 0x54434955);
    if (total + value > 9999999) {
        value = 9999999 - total;
    }
    fn_8007ABA4(&cursor, 0x41434955, current + value);
    fn_8007ABA4(&cursor, 0x54434955, total + value);
    UserInfoClose(&cursor);
}

void UserInfoSpendPoints(int db, int value)
{
    Object_8007A334 cursor;

    UserInfoOpen(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, fn_8007A98C(&cursor, 0x41434955) - value);
    UserInfoClose(&cursor);
}

void UnlockStatusOpen(Object_8007A334 *pCursor, int index)
{
    UnlockStatusOpenDb(pCursor, fn_8022F358(index));
}

void UnlockStatusOpenDb(Object_8007A334 *pCursor, int db)
{
    Key_8007A334 keys[2];

    keys[0].Set(0x53544653, 0x49434655, 0);
    keys[1].Set(-1, -1, 3);
    fn_8007A334(pCursor, 0x43465355, 0x49434655, keys, 0, fn_8022F3D4(db));
}

void UnlockStatusClose(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

void UnlockStatusSetCurrent(Object_8007A334 *pCursor, int set)
{
    fn_8007AA90(pCursor, 0x43434655, set != 0);
}

unsigned char UnlockStatusGet(Object_8007A334 *pCursor, int index)
{
    fn_8007A7F4(pCursor, 0x49434655, index, 0, 0);
    return fn_8007A934(pCursor, 0x43434655);
}

void UnlockStatusSet(Object_8007A334 *pCursor, int index, int value)
{
    fn_8007A7F4(pCursor, 0x49434655, index, 0, 0);
    fn_8007AA90(pCursor, 0x43434655, value);
}

void UnlockListOpen(Object_8007A334 *pCursor, int mode, unsigned char value)
{
    Key_8007A334 keys[2];
    Object_80023BBC root;
    Object_80023BBC left;
    Object_80023BBC right;
    unsigned int column = 0x54464653;

    keys[0].Set(0x53544653, 0x49464653, 0);
    keys[1].Set(-1, -1, 3);
    if (mode == 0) {
        fn_8007A334(pCursor, 0x53544653, 0x49464653, keys, 0, 0x54415453);
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
            fn_8007A334(pCursor, 0x53544653, 0x49464653, keys, &root, 0x54415453);
            break;
        }
        }
    }
}

void UnlockListClose(Object_8007A334 *pCursor)
{
    fn_8007A3C4(pCursor);
}

int UnlockListSeek(Object_8007A334 *pCursor, int a, int key, int *pResult)
{
    return fn_8007A7F4(pCursor, 0x51464653, key, a, pResult);
}

void UnlockListReadItem(Object_8007A334 *pCursor, UnlockItem *pRecord)
{
    pRecord->mIndex = fn_8007A98C(pCursor, 0x49464653);
    fn_8007AA3C(pCursor, 0x44464653, (int)pRecord->mName, sizeof(pRecord->mName));
    pRecord->mUnknown136 = fn_8007A98C(pCursor, 0x54464653);
    pRecord->mUnknown140 = fn_8007A98C(pCursor, 0x51464653);
    pRecord->mUnknown144 = fn_8007A98C(pCursor, 0x50464653);
    pRecord->mUnknown148 = fn_8007A98C(pCursor, 0x57464653);
}

unsigned char UnlockListGetIndex(Object_8007A334 *pCursor)
{
    return fn_8007A98C(pCursor, 0x49464653);
}

static int _ChecksumCRC32_Start(void *pStream, int a, int target, unsigned char reading)
{
    ChecksumCRC32Stream *pState = (ChecksumCRC32Stream *)pStream;
    int result = 0;

    pState->mpResult = (unsigned int *)target;
    if (target == 0) {
        result = 0x24;
    } else {
        ChecksumCRC32Begin();
    }
    return result;
}

static int _ChecksumCRC32_Stop(void *pStream)
{
    ChecksumCRC32Stream *pState = (ChecksumCRC32Stream *)pStream;

    if (pState->mpResult == 0) {
        return 3;
    }
    ChecksumCRC32End(pState->mpResult);
    return 0;
}

static int _ChecksumCRC32_CalculateBuffer(void *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    ChecksumCRC32Stream *pState = (ChecksumCRC32Stream *)pStream;
    int result = 3;

    if (pState->mpResult != 0) {
        ChecksumCRC32Update(pData, size);
        *pDone = size;
        result = 0;
    }
    return result;
}

static int _ChecksumCRC32_Read(void *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    return 3;
}

static int _ChecksumCRC32_GetSize(unsigned int size)
{
    return 0;
}

StreamOps_8002ACB4 _ChecksumCRC32_Type = {
    _ChecksumCRC32_Start, _ChecksumCRC32_Stop, _ChecksumCRC32_Read, _ChecksumCRC32_CalculateBuffer, 0, _ChecksumCRC32_GetSize, 4,
};

}
