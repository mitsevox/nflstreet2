/* Player gear rating bonuses. Looks up the rating bonuses of each piece of
   gear a player wears in the gear database tables, sums them, and gives
   them on their own, rescaled to 0..255, or added to the player's ratings
   and clamped to the 1..99 rating range. */
#include "game/fn_801C1F94.h"

#include "game/DbCursor.h"
#include "game/Object_8008044C.h"
#include "game/DbQueryTable.h"

extern "C" {
int fn_8007BF14(int index);
int fn_801FA290(int handle, DbQueryTable *pTables, DbFilter *pFilter,
                DbColumnValue *pColumns);
void PlayerDbReadRatings(Object_8008044C *pObject, int *pValues);
void PlayerGearSumBonuses(PlayerGear_t *pInfo, short *pValues);

#if defined(DECOMP_COMPARE)
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

void PlayerGearGetScaledBonuses(Object_8008044C *pObject, short *pValues)
{
    PlayerGear_t info;
    int i;

    fn_800817CC(pObject, &info);
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

    fn_801C1F94(pValues, 0, 10 * sizeof(short));
    tables[0].Set(0x52414547, 0, &filter);
    tables[1].Set(0x50495247, 0, &join);
    tables[2].Set(-1);
    join.Set(6, ((unsigned long long)0x50495247 << 32) | 0x594B5047, 6);
    join.mUnknown16.mValue.mLong = ((unsigned long long)0x52414547 << 32) | 0x594B5047;
    filter.Set(11, &left, &right);
    for (i = 0; i < 14; i++) {
        if (i != 7) {
            int result = fn_8007BF14(i);

            if (i == 6 && pInfo->mValues[6] == 0) {
                i = 7;
            }
            left.Set(6, ((unsigned long long)0x52414547 << 32) | 0x44494547, 3, pInfo->mValues[i]);
            right.Set(6, ((unsigned long long)0x52414547 << 32) | 0x49545247, 2, result);
            if (fn_801FA290(0x54415453, tables, 0, _PlayerGearRatings_aBonusColumns) != 0x17) {
                for (j = 0; j < 10; j++) {
                    pValues[j] += _PlayerGearRatings_aBonusColumns[j].mValue;
                }
            }
        }
    }
}

#endif

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

    fn_800817CC(pObject, &info);
    PlayerGearSumBonuses(&info, pValues);
}

void PlayerGetGearRatings(Object_8008044C *pObject, int *pValues)
{
    PlayerGear_t info;

    fn_800817CC(pObject, &info);
    PlayerAddGearRatings(pObject, &info, pValues);
}

}
