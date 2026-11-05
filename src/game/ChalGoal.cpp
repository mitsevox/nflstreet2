/* Goal tests for NFL Street 2's challenges: checks a challenge goal (a stat to reach or to stay
   under) against the game stats, ranks a medal goal as Gold, Silver or Bronze, and opens and reads
   the challenge database tables. */

#include "game/Class_8018FD64Inline.h"
#include "game/Challenge.h"
#include "game/DbCursor.h"

extern "C" {

int fn_800D41F8(int side);
int fn_8022B7A4(int handle, int tag, void *pValue);

/* The six functions ChalCheckNoGoal to ChalRankAtLeastGoal are the words of the .data
   table 0x802D6400-0x802D6418, three pairs indexed by a type word: ChalCheckGoal
   calls the first of a pair with a tag, a side, the record and an entry
   index, and ChalCheckMedalGoal calls the second with a tag, a side and the
   ChalMedalGoal_t block. */

int ChalCheckNoGoal(int tag, int side, Challenge_t *pRecord, int index)
{
    return 0;
}

int ChalRankNoGoal(int tag, int side, ChalMedalGoal_t *pInfo)
{
    return 0;
}

int ChalCheckAtMostGoal(int tag, int side, Challenge_t *pRecord, int index)
{
    unsigned int limit = pRecord->mUnknown1C4[index].mValue;
    unsigned int value;

    fn_8022B7A4(side, tag, &value);
    return value > limit;
}

int ChalRankAtMostGoal(int tag, int side, ChalMedalGoal_t *pInfo)
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

int ChalCheckAtLeastGoal(int tag, int side, Challenge_t *pRecord, int index)
{
    unsigned int limit = pRecord->mUnknown1C4[index].mValue;
    unsigned int value;

    fn_8022B7A4(side, tag, &value);
    return value < limit ? 2 : 0;
}

int ChalRankAtLeastGoal(int tag, int side, ChalMedalGoal_t *pInfo)
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

int ChalRankStylePoints(int side, ChalMedalGoal_t *pInfo)
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

void ChalOpenTable(DbCursor *pObject)
{
    DbCursorOpenTable(pObject, 0x4C414843, -1);
}

void ChalOpenInfo(DbCursor *pObject, int value)
{
    DbCursorOpen(pObject, 0x4E494843, 0x4B504943, 0, 0, value);
}

void ChalOpenProgress(DbCursor *pObject, int value)
{
    DbCursorOpen(pObject, 0x47504843, 0x44494843, 0, 0, value);
}

/* Reads a row for id (tags 0x444D4843 and 0x54415453 passed to
   fn_8018FDEC) into pInfo; mUnknown0 is 0 when fn_8018FF30 finds no row. */
void ChalReadMedalGoal(int id, ChalMedalGoal_t *pInfo)
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
