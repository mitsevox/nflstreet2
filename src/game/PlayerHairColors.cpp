/* Reads the two colour columns of a player row (hair and facial hair) for the player
   model. */

#include "game/Object_8007A334.h"
#include "game/Object_8008044C.h"

extern "C" {
int PlayerDbGetId(Object_8008044C *pObject);
}

static int _PlayerDb_aHairColorColumns[2] = { 0x31414850, 0x43484650 };

extern "C" void PlayerDbReadHairColors(Object_8008044C *pObject, unsigned char *p)
{
    ColumnValue_802D6424 columns[3];
    int i;

    PlayerDbGetId(pObject);
    for (i = 0; i < 2; ++i) {
        columns[i].Set(0x59414C50, _PlayerDb_aHairColorColumns[i], 0);
    }
    columns[2].SetEnd();
    pObject->Read(columns);
    for (i = 0; i < 2; ++i) {
        p[i] = columns[i].mValue;
    }
    p[0] += 0x80;
    p[1] += 0x80;
}
