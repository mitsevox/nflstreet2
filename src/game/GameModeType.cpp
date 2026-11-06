/* Reads and caches the current game mode type from the game database and tests it against a fixed set of modes. */
#include "game/GameModeType.h"
#include "game/fn_801FCE10.h"
#include "game/InGame.h"

extern "C" {
int fn_802294F4(void);
}

static int _GameModeType_iCached = 99;

extern "C" {
unsigned int GameModeTypeGet(void)
{
    int value = 99;

    if (fn_802294F4() != 0) {
        int cached = _GameModeType_iCached;

        if (cached == 99) {
            if (fn_801FCE10(0, "select 'PYTM' into \x82 from 'NIOM'\n", &value) != 0) {
                value = cached;
            }
            if (InGameIsPlaying() != 0) {
                _GameModeType_iCached = value;
            }
        } else {
            value = cached;
        }
    }
    return value;
}

int GameModeTypeIsSpecial(void)
{
    switch (GameModeTypeGet()) {
    case 3:
        return 1;
    case 4:
        return 1;
    case 5:
        return 1;
    case 13:
        return 1;
    default:
        return 0;
    }
}

void GameModeTypeInvalidate(void)
{
    _GameModeType_iCached = 99;
}
}
