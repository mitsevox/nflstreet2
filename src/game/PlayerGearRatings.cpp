/* Reads and sums the rating bonuses of the gear a player wears. Returns
   them raw or scaled by 255/99, or adds them to the player's ratings
   before clamping to 1..99. */
#include <string.h>

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/DbQueryTable.h"

extern "C" {
int GearDbGetSlotType(int index);
int TDbQryGetSingleRow(int handle, DbQueryTable *pTables, DbFilter *pFilter,
                       DbColumnValue *pColumns);
void PlayerDbReadRatings(Object_8008044C *pObject, int *pValues);
void PlayerGearSumBonuses(PlayerGear_t *pInfo, short *pValues);

static DbColumnValue _PlayerGearRatings_aBonusColumns[11] = {
    { 0, 0x50495247, 0x4C474147, 0 },
    { 0, 0x50495247, 0x504D4A47, 0 },
    { 0, 0x50495247, 0x4B544247, 0 },
    { 0, 0x50495247, 0x43544347, 0 },
    { 0, 0x50495247, 0x44505347, 0 },
    { 0, 0x50495247, 0x4B435447, 0 },
    { 0, 0x50495247, 0x53535047, 0 },
    { 0, 0x50495247, 0x4B4C4247, 0 },
    { 0, 0x50495247, 0x564F4347, 0 },
    { 0, 0x50495247, 0x43544447, 0 },
    { 0, -1, -1, 0 },
};

static inline void _PlayerGearRatingsSetFilter(DbFilter &filter, int operation,
                                              long long column, int valueKind, int value)
{
    filter.SetUnknown32(6, column, valueKind, operation);
    filter.mUnknown16.mValue.mInt = value;
}

void PlayerGearGetScaledBonuses(Object_8008044C *pObject, short *pValues)
{
    PlayerGear_t info;
    int i;

    PlayerDbReadGear(pObject, &info);
    PlayerGearSumBonuses(&info, pValues);
    for (i = 0; i < 10; i++) {
        pValues[i] = pValues[i] * 255 / 99;
    }
}

void PlayerGearSumBonuses(PlayerGear_t *pInfo, short *pValues)
{
    DbQueryTable tables[3];
    DbFilter filter;
    DbFilter left;
    DbFilter right;
    DbFilter join;
    int i;
    int j;

    memset(pValues, 0, 10 * sizeof(short));
    tables[0].Set(0x52414547, 0, &filter);
    tables[1].Set(0x50495247, 0, &join);
    tables[2].Set(-1);
    join.Set(6, ((unsigned long long)0x50495247 << 32) | 0x594B5047, 6);
    join.mUnknown16.mValue.mLong = ((unsigned long long)0x52414547 << 32) | 0x594B5047;
    filter.Set(11, &left, &right);
    const long long gearIdColumn = ((unsigned long long)0x52414547 << 32) | 0x44494547;
    const long long gearTypeColumn = ((unsigned long long)0x52414547 << 32) | 0x49545247;
    for (i = 0; i < 14; i++) {
        if (i != 7) {
            int gearType = GearDbGetSlotType(i);

            // Slot 7 supplies the fallback gear ID when slot 6 is empty.
            if (i == 6 && pInfo->mValues[6] == 0) {
                i = 7;
            }
            _PlayerGearRatingsSetFilter(left, 0x10003, gearIdColumn, 3, pInfo->mValues[i]);
            _PlayerGearRatingsSetFilter(right, 0x10003, gearTypeColumn, 2, gearType);
            if (TDbQryGetSingleRow(0x54415453, tables, 0, _PlayerGearRatings_aBonusColumns) != 0x17) {
                for (j = 0; j < 10; j++) {
                    pValues[j] += _PlayerGearRatings_aBonusColumns[j].mValue;
                }
            }
        }
    }
}

void PlayerAddGearRatings(Object_8008044C *pObject, PlayerGear_t *pInfo, int *pValues)
{
    short sums[10];
    int i;

    PlayerDbReadRatings(pObject, pValues);
    PlayerGearSumBonuses(pInfo, sums);
    for (i = 0; i < 10; i++) {
        pValues[i] = sums[i] + pValues[i];
        pValues[i] = pValues[i] <= 0 ? 1 : (pValues[i] > 99 ? 99 : pValues[i]);
    }
}

void PlayerGetGearBonuses(Object_8008044C *pObject, short *pValues)
{
    PlayerGear_t info;

    PlayerDbReadGear(pObject, &info);
    PlayerGearSumBonuses(&info, pValues);
}

void PlayerGetGearRatings(Object_8008044C *pObject, int *pValues)
{
    PlayerGear_t info;

    PlayerDbReadGear(pObject, &info);
    PlayerAddGearRatings(pObject, &info, pValues);
}

}
