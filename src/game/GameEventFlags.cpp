/* Six game-state flag bytes that gameplay code swaps in and out (replay, score changes, the clock check at game start), plus their reset and a 30-tick hold counter. */
#include "game/GameEventFlags.h"

static unsigned char _GameEventFlags_bFlag0 = 0;
static unsigned char _GameEventFlags_bFlag1 = 0;
static unsigned char _GameEventFlags_bFlag2 = 0;
static unsigned char _GameEventFlags_bFlag3 = 0;
static unsigned char _GameEventFlags_bFlag4 = 0;
static unsigned char _GameEventFlags_bFlag5 = 0;
static float _GameEventFlags_fValue0 = 0.0f;
static float _GameEventFlags_fValue1 = 0.0f;
static int _GameEventFlags_iFlag2Hold = 0;

extern "C" {
void GameEventFlagsReset(void);

void GameEventFlagsInit(void)
{
    GameEventFlagsReset();
}

void GameEventFlagsShutdown(void)
{
    GameEventFlagsReset();
}

void GameEventFlagsReset(void)
{
    _GameEventFlags_bFlag0 = 0;
    _GameEventFlags_bFlag1 = 0;
    _GameEventFlags_bFlag2 = 0;
    _GameEventFlags_bFlag3 = 0;
    _GameEventFlags_bFlag4 = 0;
    _GameEventFlags_bFlag5 = 0;
    _GameEventFlags_iFlag2Hold = 0;
    _GameEventFlags_fValue0 = 0.0f;
    _GameEventFlags_fValue1 = 0.0f;
}

unsigned char GameEventFlagsSetFlag0(unsigned char value)
{
    unsigned char old = _GameEventFlags_bFlag0;

    _GameEventFlags_bFlag0 = value;
    return old;
}

unsigned char GameEventFlagsSetFlag1(unsigned char value)
{
    unsigned char old = _GameEventFlags_bFlag1;

    _GameEventFlags_bFlag1 = value;
    return old;
}

unsigned char GameEventFlagsSetFlag2(unsigned char value)
{
    unsigned char old = _GameEventFlags_bFlag2;

    _GameEventFlags_bFlag2 = value;
    if (old == 1 && value == 0) {
        _GameEventFlags_iFlag2Hold = 30;
    }
    return old;
}

unsigned char GameEventFlagsSetFlag3(unsigned char value)
{
    unsigned char old = _GameEventFlags_bFlag3;

    _GameEventFlags_bFlag3 = value;
    return old;
}

unsigned char GameEventFlagsSetFlag4(unsigned char value)
{
    unsigned char old = _GameEventFlags_bFlag4;

    _GameEventFlags_bFlag4 = value;
    if (value == 1) {
        GameEventFlagsSetFlag1(0);
        GameEventFlagsSetFlag2(0);
        GameEventFlagsSetFlag3(0);
    }
    return old;
}

unsigned char GameEventFlagsSetFlag5(unsigned char value)
{
    unsigned char old = _GameEventFlags_bFlag5;

    _GameEventFlags_bFlag5 = value;
    return old;
}

unsigned char GameEventFlagsPollFlag2Hold(void)
{
    if (_GameEventFlags_bFlag2 == 0 && _GameEventFlags_iFlag2Hold != 0) {
        _GameEventFlags_iFlag2Hold--;
        return 1;
    }
    return _GameEventFlags_bFlag2;
}
}
