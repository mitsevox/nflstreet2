/* The player gear database: opens, seeks and reads the gear table of the game database (each piece's
   type, id, name and look), maps the 14 gear slots of a player to gear types, reads a piece's rating
   boosts, and upgrades a gear item to its next level for the current profile, carrying the unlocks and
   every created player's equipped pieces over to the new level. */

#include <string.h>

#include "game/TDbCompilePerformOp.h"
#include "game/DbTableCursorInline.h"
#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/GearDb.h"
#include "game/DbSortKey.h"

extern "C" {
int DbUserFindIndex(int a);
int DbUserGetDb(int a);
int DbUserGetCurrent(void);
void GearLockOpen(DbCursor *pCursor, int index);
void GearLockClose(DbCursor *pCursor);
int GearLockIsLocked(DbCursor *pCursor, int key);
int GearIsLocked(int key);
void GearUnlock(int key);
void GearLock(int key);
void CreateTeamPlayerCursorOpen(DbCursor *pCursor, int index);
void CreateTeamPlayerCursorClose(DbCursor *pCursor);
}

static int _GearDb_aColumnTags[33] = {
    0x48545247, 0x54485447, 0x4C475447, 0x52545447, 0x50535447, 0x43425447, 0x424C5447,
    0x42455447, 0x41465447, 0x52575447, 0x44485447, 0x48545447, 0x4E4B5447, 0x53555447,
    0x534C5447, 0x48535447, 0x594B5047, 0x44494547, 0x4D4E5247, 0x54534247, 0x49545247,
    0x49545347, 0x49535247, 0x49434447, 0x46435347, 0x4C474C54, 0x42485247, 0x46485247,
    0x44425547, 0x53485247, 0x41485247, 0x54485247, 0x44544847
};

static int _GearDb_aBoostTags[10] = {
    0x4C474147, 0x504D4A47, 0x4B544247, 0x43544347, 0x44505347,
    0x4B435447, 0x53535047, 0x4B4C4247, 0x564F4347, 0x43544447
};

static int _GearDb_aSlotType[14] = { 0, 1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10, 11, 12 };
static int _GearDb_aTypeSlot[13] = { 0, 1, 2, 3, 4, 5, 14, 8, 9, 10, 11, 12, 13 };

static DbSortKey _GearDb_aIdSortKeys[2] = {
    { 0x52414547, 0x44494547, 0, 0 },
    { -1, -1, 3, 0 },
};

extern "C" {

void GearDbOpen(DbCursor *pCursor)
{
    DbCursorOpen(pCursor, 0x52414547, 0x594B5047, 0, 0, 0x54415453);
}

void GearDbOpenType(DbCursor *pCursor, int value)
{
    DbFilter arg;

    arg.Set(6, 0x5241454749545247LL, 3, value);
    DbCursorOpen(pCursor, 0x52414547, 0x594B5047, _GearDb_aIdSortKeys, &arg, 0x54415453);
}

void GearDbClose(DbCursor *pCursor)
{
    DbCursorClose(pCursor);
}

int GearDbGetKey(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x594B5047);
}

int GearDbSeekKey(DbCursor *pCursor, int key, int *pResult)
{
    return DbCursorFindInt(pCursor, 0x594B5047, key, 0, pResult);
}

int GearDbSeekTypeId(DbCursor *pCursor, int a, int b, int *pResult)
{
    DbColumnValue list[3];

    list[0].Set(0x52414547, 0x44494547);
    list[0].mValue = b;
    list[1].Set(0x52414547, 0x49545247);
    list[1].mValue = a;
    list[2].Set(-1, -1);
    list[2].mValue = 0;
    return DbCursorFindRow(pCursor, list, 0, pResult);
}

int GearDbSeekId(DbCursor *pCursor, int key, int *pResult)
{
    return DbCursorFindInt(pCursor, 0x44494547, key, 0, pResult);
}

void GearDbReadRow(DbCursor *pCursor, GearRow_t *pOut)
{
    DbColumnValue list[34];
    char *pSpace;
    int i;

    for (i = 0; i < 33; i++) {
        list[i].Set(0x52414547, _GearDb_aColumnTags[i]);
        list[i].mValue = 0;
    }
    list[33].Set(-1, -1);
    list[33].mValue = 0;
    list[18].mValue = (int)pOut->mUnknown10;
    list[19].mValue = (int)pOut->mName;
    pCursor->Read(list);

    pOut->mUnknown00 = list[16].mValue;
    pOut->mUnknown0C = list[17].mValue;
    pOut->mUnknown04 = list[20].mValue;
    pOut->mUnknown08 = list[21].mValue;
    pOut->mUnknown64 = list[22].mValue;
    pOut->mUnknown68 = list[23].mValue;
    pOut->mUnknown78 = list[25].mValue;
    pOut->mUnknown70 = list[26].mValue != 0;
    pOut->mUnknown71 = list[27].mValue != 0;
    pOut->mUnknown72 = list[28].mValue != 0;
    pOut->mUnknown73 = list[29].mValue != 0;
    pOut->mUnknown74 = list[30].mValue != 0;
    pOut->mUnknown75 = list[31].mValue != 0;
    pOut->mUnknown76 = list[32].mValue != 0;
    pOut->mUnknown6C = 0;

    pSpace = strchr(pOut->mName, ' ');
    if (pSpace) {
        *pSpace = 0;
    }
    for (i = 0; i < 16; i++) {
        pOut->mUnknown52[i] = list[i].mValue;
    }
}

unsigned int GearDbGetGrsi(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49535247);
}

void GearDbGetName(DbCursor *pCursor, char *pBuffer, int size)
{
    DbCursorGetString(pCursor, 0x4D4E5247, (int)pBuffer, size);
}

int GearDbGetId(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x44494547);
}

int GearDbGetType(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49545247);
}

int GearDbGetGsti(DbCursor *pCursor)
{
    return DbCursorGetInt(pCursor, 0x49545347);
}

int GearDbFindIdByGbst(int a, int b)
{
    int value = 0;

    TDbCompilePerformOp(0, "use 'TATS' select 'DIEG' into \x85 from 'RAEG' where 'ITRG' = \x85 and 'TSBG' = \x88\n",
                &value, a, b);
    return value;
}

int GearDbGetSlotType(int index)
{
    return _GearDb_aSlotType[index];
}

int GearDbGetTypeSlot(int index)
{
    return _GearDb_aTypeSlot[index];
}

int GearDbReadBoosts(DbCursor *pCursor, short *pOut);

int GearDbHasBoosts(DbCursor *pCursor)
{
    return GearDbReadBoosts(pCursor, 0);
}

void GearDbUpgradeItem(int id)
{
    int index = DbUserFindIndex(DbUserGetCurrent());
    int handle = DbUserGetDb(DbUserGetCurrent());
    DbTableCursor cursor(0x4C504947, 0x49544947, 0, 0, handle);

    if (cursor.FindColumnValue(0x49544947, id, 0, 0)) {
        int count = cursor.GetColumnValue(0x4C504947);
        int next = count + 1;
        DbSortKey keys[2];
        DbFilter both;
        DbFilter first;
        DbFilter second;
        int oldKeys[2];
        unsigned char fresh[2];
        int newKeys[2];
        int types[2];
        int oldIds[2];
        int newIds[2];
        int i;
        int j;

        cursor.SetColumnValue(0x4C504947, next);
        keys[0].Set(0x50495247, 0x47504947, 0);
        keys[1].Set(-1, -1, 3);
        both.Set(11, &first, &second);
        first.Set(6, 0x5049524749544947LL, 2);
        first.mUnknown16.mValue.mInt = id;
        second.Set(6, 0x504952474C504947LL, 2);
        second.mUnknown16.mValue.mInt = count;
        {
            DbTableCursor rows(0x50495247, 0x594B5047, keys, &both, 0x54415453);

            for (i = 0; i < 2; i++) {
                oldKeys[i] = rows.GetColumnValue(0x594B5047);
                fresh[i] = !GearIsLocked(oldKeys[i]);
                if (fresh[i]) {
                    GearLock(oldKeys[i]);
                }
                rows.MoveNext();
            }
        }
        second.Set(6, 0x504952474C504947LL, 2);
        second.mUnknown16.mValue.mInt = next;
        {
            DbTableCursor rows(0x50495247, 0x594B5047, keys, &both, 0x54415453);

            for (i = 0; i < 2; i++) {
                newKeys[i] = rows.GetColumnValue(0x594B5047);
                if (fresh[i]) {
                    GearUnlock(newKeys[i]);
                }
                rows.MoveNext();
            }
        }
        for (i = 0; i < 2; i++) {
            DbTableCursor rows(0x52414547, 0x594B5047, 0, 0, 0x54415453);

            rows.FindColumnValue(0x594B5047, oldKeys[i], 0, 0);
            types[i] = rows.GetColumnValue(0x49545247);
            oldIds[i] = rows.GetColumnValue(0x44494547);
            rows.FindColumnValue(0x594B5047, newKeys[i], 0, 0);
            newIds[i] = rows.GetColumnValue(0x44494547);
        }
        {
            DbCursor teams;
            PlayerGear_t record;

            CreateTeamPlayerCursorOpen(&teams, index);
            if (DbCursorFirst(&teams)) {
                do {
                    PlayerDbReadGear((Object_8008044C *)&teams, &record);
                    for (i = 0; i < 14; i++) {
                        int type = GearDbGetSlotType(i);

                        for (j = 0; j < 2; j++) {
                            if (type == types[j] && record.mValues[i] == oldIds[j]) {
                                record.mValues[i] = newIds[j];
                            }
                        }
                    }
                    PlayerDbWriteGear((Object_8008044C *)&teams, &record);
                } while (DbCursorNext(&teams));
            }
            CreateTeamPlayerCursorClose(&teams);
        }
    }
}

int GearDbGetCurrentKey(int key)
{
    int a;
    int b;
    int last;
    int max;
    int handle = DbUserGetDb(DbUserGetCurrent());

    TDbCompilePerformOp(0, "use 'TATS' select 'ITIG' into \x82 and 'GPIG' into \x82 and 'LPIG' into \x82 from 'PIRG' where 'YKPG' = \x85\n",
                &a, &b, &last, key);
    TDbCompilePerformOp(0, "use \x8c select 'LPIG' into \x82 from 'LPIG' where 'ITIG' = \x82\n", handle, &max, a);
    if (last != max) {
        int found;

        do {
            found = TDbCompilePerformOp(0, "use 'TATS' select 'YKPG' into \x85 from 'PIRG' where 'ITIG' = \x82 and 'GPIG' = \x82 and 'LPIG' = \x82\n",
                                &key, a, b, max);
            max--;
        } while (found != 0 && max >= 0);
    }
    return key;
}

int GearDbIsItemUnlocked(int id)
{
    int result = 0;
    DbFilter arg;
    DbCursor keys;

    GearLockOpen(&keys, DbUserFindIndex(DbUserGetCurrent()));
    arg.Set(6, 0x5049524749544947LL, 2, id);
    {
        DbTableCursor rows(0x50495247, 0x594B5047, 0, &arg, 0x54415453);
        int more;

        for (more = rows.MoveFirst(); more; more = rows.MoveNext()) {
            if (!GearLockIsLocked(&keys, rows.GetColumnInt(0x594B5047))) {
                result = 1;
                break;
            }
        }
        GearLockClose(&keys);
    }
    return result;
}

int GearDbIsNumberItem(GearRow_t *pRow)
{
    return pRow->mUnknown64 == 5;
}

int GearDbReadBoosts(DbCursor *pCursor, short *pOut)
{
    int result = 0;
    DbFilter arg;
    int i;

    arg.Set(6, 0x50495247594B5047LL, 2, GearDbGetKey(pCursor));
    {
        DbTableCursor rows(0x50495247, 0x594B5047, 0, &arg, 0x54415453);

        if (rows.GetRowCount() > 0 && rows.GetColumnValue(0x49544947) > 0) {
            if (pOut) {
                for (i = 0; i < 10; i++) {
                    pOut[i] = rows.GetColumnValue(_GearDb_aBoostTags[i]);
                }
            }
            result = 1;
        }
        if (pOut && !result) {
            memset(pOut, 0, 20);
        }
    }
    return result;
}
}
