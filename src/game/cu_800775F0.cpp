#include "game/Class_8018FD64Inline.h"
#include "game/Object_800785C0.h"
#include "game/Object_8007A334.h"

extern "C" {

int fn_800D41F8(int side);
int fn_8022B7A4(int handle, int tag, void *pValue);

/* The six functions fn_800775F0 to fn_80077730 are the words of the .data
   table 0x802D6400-0x802D6418, three pairs indexed by a type word: fn_800796B8
   calls the first of a pair with a tag, a side, the record and an entry
   index, and fn_80079758 calls the second with a tag, a side and the
   Info_8007984C block. */

int fn_800775F0(int tag, int side, Object_800785C0 *pRecord, int index)
{
    return 0;
}

int fn_800775F8(int tag, int side, Info_8007984C *pInfo)
{
    return 0;
}

int fn_80077600(int tag, int side, Object_800785C0 *pRecord, int index)
{
    unsigned int limit = pRecord->mUnknown1C4[index].mValue;
    unsigned int value;

    fn_8022B7A4(side, tag, &value);
    return value > limit;
}

int fn_80077654(int tag, int side, Info_8007984C *pInfo)
{
    int result = 7;
    unsigned int value;
    int i;

    fn_8022B7A4(side, tag, &value);
    for (i = 0; i <= 2; i++) {
        if (value < pInfo->mUnknown4[i]) {
            result = i;
            break;
        }
    }
    return result;
}

int fn_800776DC(int tag, int side, Object_800785C0 *pRecord, int index)
{
    unsigned int limit = pRecord->mUnknown1C4[index].mValue;
    unsigned int value;

    fn_8022B7A4(side, tag, &value);
    return value < limit ? 2 : 0;
}

int fn_80077730(int tag, int side, Info_8007984C *pInfo)
{
    int result = 7;
    unsigned int value;
    int i;

    fn_8022B7A4(side, tag, &value);
    for (i = 0; i <= 2; i++) {
        if (value >= pInfo->mUnknown4[i]) {
            result = i;
            break;
        }
    }
    return result;
}

int fn_800777B8(int side, Info_8007984C *pInfo)
{
    int result = 7;
    unsigned int value = fn_800D41F8(side);
    int i;

    for (i = 0; i <= 2; i++) {
        if (value >= pInfo->mUnknown4[i]) {
            result = i;
            break;
        }
    }
    return result;
}

void fn_80077828(Object_8007A334 *pObject)
{
    fn_8007A308(pObject, 0x4C414843, -1);
}

void fn_80077854(Object_8007A334 *pObject, int value)
{
    fn_8007A334(pObject, 0x4E494843, 0x4B504943, 0, 0, value);
}

void fn_80077890(Object_8007A334 *pObject, int value)
{
    fn_8007A334(pObject, 0x47504843, 0x44494843, 0, 0, value);
}

/* Reads a row for id (tags 0x444D4843 and 0x54415453 passed to
   fn_8018FDEC) into pInfo; mUnknown0 is 0 when fn_8018FF30 finds no row. */
void fn_800778CC(int id, Info_8007984C *pInfo)
{
    Class_8018FD64 cursor;

    cursor.fn_8018FDEC(0x444D4843, -1, 0, 0, 0x54415453);
    if (cursor.fn_8018FF30(0x44494843, id, 0, 0)) {
        pInfo->mUnknown0 = cursor.fn_8018FF9C(0x41514843);
        pInfo->mUnknown4[0] = cursor.fn_8018FF9C(0x41505143);
        pInfo->mUnknown4[1] = cursor.fn_8018FF9C(0x42505143);
        pInfo->mUnknown4[2] = cursor.fn_8018FF9C(0x43505143);
        pInfo->mUnknown1C = cursor.fn_8018FF9C(0x54524843);
        pInfo->mUnknown20[0] = cursor.fn_8018FF9C(0x56524843);
        pInfo->mUnknown20[1] = cursor.fn_8018FF9C(0x32564843);
        pInfo->mUnknown20[2] = cursor.fn_8018FF9C(0x33564843);
    } else {
        pInfo->mUnknown0 = 0;
    }
}
}
