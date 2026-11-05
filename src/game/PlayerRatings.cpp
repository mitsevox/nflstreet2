/* Player ratings: read and write the ten rating columns of a player row (agility, jump,
   break tackle, catch, speed, tackle, pass, block, coverage and one more), and a rating
   with the player's bonus added, kept within 1-99. */

#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"

extern "C" {
void fn_800814BC(Info_80307908 *pInfo, short *pValues);

static int _PlayerDb_aRatingColumns[10] = {
    0x49474150, 0x4D554A50, 0x4B544250, 0x48544350, 0x44505350,
    0x4B415450, 0x53535050, 0x4B4C4250, 0x564F4350, 0x54464450,
};

int PlayerDbGetRating(Object_8008044C *pObject, int index)
{
    return fn_8007A98C(pObject, _PlayerDb_aRatingColumns[index]);
}

int PlayerDbGetBoostedRating(Object_8008044C *pObject, int index)
{
    unsigned int value = PlayerDbGetRating(pObject, index);
    short values[10];
    Info_80307908 info;

    fn_800817CC(pObject, &info);
    fn_800814BC(&info, values);
    value += values[index];
    return value == 0 ? 1 : (value > 99 ? 99 : value);
}

void PlayerDbSetRating(Object_8008044C *pObject, int index, int value)
{
    fn_8007ABA4(pObject, _PlayerDb_aRatingColumns[index], value);
}

void PlayerDbReadRatings(Object_8008044C *pObject, int *pValues)
{
    ColumnValue_802D6424 columns[11];
    ColumnValue_802D6424 *pColumns = columns;
    int i;

    for (i = 0; i < 10; i++) {
        pColumns[i].Set(pObject->mUnknown8, _PlayerDb_aRatingColumns[i], 0);
    }
    columns[10].SetEnd();
    fn_801FA228(pObject->mUnknown0, 0, 0, pColumns);
    for (i = 0; i < 10; i++) {
        pValues[i] = pColumns[i].mValue;
    }
}

}
