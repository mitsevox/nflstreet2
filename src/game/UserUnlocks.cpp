/* A profile's points and unlockables: the points balance and lifetime total, which items
   are unlocked, and the list of items that can be unlocked. Also the stream type that
   computes a CRC-32 checksum of data written to it. */

#include "game/DbSortKey.h"
#include "game/DbCursor.h"
#include "game/UnlockItem.h"
#include "game/PlayerSave.h"

/* State of the stream table gChecksumCRC32StreamType: the result word passed to the
   open operation. */
struct ChecksumCRC32Stream_t {
    unsigned int *mpResult;
};

extern "C" {
void ChecksumCRC32Begin(void);
void ChecksumCRC32Update(void *pData, unsigned int size);
void ChecksumCRC32End(unsigned int *pResult);
int fn_8022F358(int index);
int fn_8022F3D4(int a);

void UserInfoOpen(DbCursor *pCursor, int db);
void UserInfoClose(DbCursor *pCursor);
unsigned int UserInfoGetPoints(int db);
int UserInfoGetTotalPoints(int db);
void UserInfoSetPoints(int db, int value);
void UserInfoAddPoints(int db, int value);
void UserInfoSpendPoints(int db, int value);
void UnlockStatusOpen(DbCursor *pCursor, int index);
void UnlockStatusOpenDb(DbCursor *pCursor, int db);
void UnlockStatusClose(DbCursor *pCursor);
void UnlockStatusSetCurrent(DbCursor *pCursor, int set);
unsigned char UnlockStatusGet(DbCursor *pCursor, int index);
void UnlockStatusSet(DbCursor *pCursor, int index, int value);
void UnlockListOpen(DbCursor *pCursor, int mode, unsigned char value);
void UnlockListClose(DbCursor *pCursor);
int UnlockListSeek(DbCursor *pCursor, int a, int key, int *pResult);
void UnlockListReadItem(DbCursor *pCursor, UnlockItem_t *pRecord);
unsigned char UnlockListGetIndex(DbCursor *pCursor);
}

extern "C" {

void UserInfoOpen(DbCursor *pCursor, int db)
{
    DbCursorOpen(pCursor, 0x464E4955, 0x41434955, 0, 0, fn_8022F3D4(db));
}

void UserInfoClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

unsigned int UserInfoGetPoints(int db)
{
    DbCursor cursor;
    unsigned int value;

    UserInfoOpen(&cursor, db);
    value = DbCursorGetInt(&cursor, 0x41434955);
    UserInfoClose(&cursor);
    return value;
}

int UserInfoGetTotalPoints(int db)
{
    DbCursor cursor;
    int value;

    UserInfoOpen(&cursor, db);
    value = DbCursorGetInt(&cursor, 0x54434955);
    UserInfoClose(&cursor);
    return value;
}

void UserInfoSetPoints(int db, int value)
{
    DbCursor cursor;

    UserInfoOpen(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, value);
    UserInfoClose(&cursor);
}

/* Adds value to both the 'ACIU' and 'TCIU' columns, clamping it so that
   'TCIU' does not exceed 9999999. */
void UserInfoAddPoints(int db, int value)
{
    DbCursor cursor;
    unsigned int current;
    unsigned int total;

    UserInfoOpen(&cursor, db);
    current = DbCursorGetInt(&cursor, 0x41434955);
    total = DbCursorGetInt(&cursor, 0x54434955);
    if (total + value > 9999999) {
        value = 9999999 - total;
    }
    fn_8007ABA4(&cursor, 0x41434955, current + value);
    fn_8007ABA4(&cursor, 0x54434955, total + value);
    UserInfoClose(&cursor);
}

void UserInfoSpendPoints(int db, int value)
{
    DbCursor cursor;

    UserInfoOpen(&cursor, db);
    fn_8007ABA4(&cursor, 0x41434955, DbCursorGetInt(&cursor, 0x41434955) - value);
    UserInfoClose(&cursor);
}

void UnlockStatusOpen(DbCursor *pCursor, int index)
{
    UnlockStatusOpenDb(pCursor, fn_8022F358(index));
}

void UnlockStatusOpenDb(DbCursor *pCursor, int db)
{
    DbSortKey keys[2];

    keys[0].Set(0x53544653, 0x49434655, 0);
    keys[1].Set(-1, -1, 3);
    DbCursorOpen(pCursor, 0x43465355, 0x49434655, keys, 0, fn_8022F3D4(db));
}

void UnlockStatusClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

void UnlockStatusSetCurrent(DbCursor *pCursor, int set)
{
    fn_8007AA90(pCursor, 0x43434655, set != 0);
}

unsigned char UnlockStatusGet(DbCursor *pCursor, int index)
{
    DbCursorFindInt(pCursor, 0x49434655, index, 0, 0);
    return DbCursorGetValue(pCursor, 0x43434655);
}

void UnlockStatusSet(DbCursor *pCursor, int index, int value)
{
    DbCursorFindInt(pCursor, 0x49434655, index, 0, 0);
    fn_8007AA90(pCursor, 0x43434655, value);
}

void UnlockListOpen(DbCursor *pCursor, int mode, unsigned char value)
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

void UnlockListClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int UnlockListSeek(DbCursor *pCursor, int a, int key, int *pResult)
{
    return DbCursorFindInt(pCursor, 0x51464653, key, a, pResult);
}

void UnlockListReadItem(DbCursor *pCursor, UnlockItem_t *pRecord)
{
    pRecord->mIndex = DbCursorGetInt(pCursor, 0x49464653);
    fn_8007AA3C(pCursor, 0x44464653, (int)pRecord->mName, sizeof(pRecord->mName));
    pRecord->mUnknown136 = DbCursorGetInt(pCursor, 0x54464653);
    pRecord->mUnknown140 = DbCursorGetInt(pCursor, 0x51464653);
    pRecord->mUnknown144 = DbCursorGetInt(pCursor, 0x50464653);
    pRecord->mUnknown148 = DbCursorGetInt(pCursor, 0x57464653);
}

unsigned char UnlockListGetIndex(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49464653);
}

static int _ChecksumCRC32StreamStart(void *pStream, int a, int target, unsigned char reading)
{
    ChecksumCRC32Stream_t *pState = (ChecksumCRC32Stream_t *)pStream;
    int result = 0;

    pState->mpResult = (unsigned int *)target;
    if (target == 0) {
        result = 0x24;
    } else {
        ChecksumCRC32Begin();
    }
    return result;
}

static int _ChecksumCRC32StreamStop(void *pStream)
{
    ChecksumCRC32Stream_t *pState = (ChecksumCRC32Stream_t *)pStream;

    if (pState->mpResult == 0) {
        return 3;
    }
    ChecksumCRC32End(pState->mpResult);
    return 0;
}

static int _ChecksumCRC32StreamWrite(void *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    ChecksumCRC32Stream_t *pState = (ChecksumCRC32Stream_t *)pStream;
    int result = 3;

    if (pState->mpResult != 0) {
        ChecksumCRC32Update(pData, size);
        *pDone = size;
        result = 0;
    }
    return result;
}

static int _ChecksumCRC32StreamRead(void *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    return 3;
}

static int _ChecksumCRC32StreamNoOp(unsigned int size)
{
    return 0;
}

SaveStreamOps_t gChecksumCRC32StreamType = {
    _ChecksumCRC32StreamStart, _ChecksumCRC32StreamStop, _ChecksumCRC32StreamRead, _ChecksumCRC32StreamWrite, 0, _ChecksumCRC32StreamNoOp, 4,
};

}
