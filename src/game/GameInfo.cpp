/* Keeps the current game's information row (the GINF table: home team, away team and a third value)
   open in the game database and lets the front end and game code read and change it by index. */

#include "game/DbCursor.h"
#include "game/GameInfo.h"

extern "C" {
int fn_8022DBF4(int value);
int fn_8022DC38(int value);
int fn_8022E558(void);
int fn_8022E560(void);
}

static int _GameInfo_aColumnTags[3] = { 0x47544847, 0x47544147, 0x47545047 };
static DbCursor _GameInfo_sCursor;
static DbColumnValue _GameInfo_aRecord[4];
static unsigned char _GameInfo_bInitialized = 0;

extern "C" {

void GameInfoInit(void)
{
    DbCursorOpen(&_GameInfo_sCursor, 0x464E4947, 0x554E5547, 0, 0, 0x454D4147);
    GameInfoRead();
    _GameInfo_bInitialized = 1;
}

/* Reads the current values of all columns into _GameInfo_aRecord. */
void GameInfoRead(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        _GameInfo_aRecord[i].mTableTag = 0x464E4947;
        _GameInfo_aRecord[i].mColumnTag = _GameInfo_aColumnTags[i];
    }
    DbColumnValue *pEnd = &_GameInfo_aRecord[3];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;
    _GameInfo_sCursor.Read(_GameInfo_aRecord);
}

void GameInfoShutdown(void)
{
    DbCursorClose(&_GameInfo_sCursor);
    _GameInfo_bInitialized = 0;
}

unsigned char GameInfoIsInitialized(void)
{
    return _GameInfo_bInitialized;
}

void GameInfoSet(int index, int value)
{
    if (index == 0) {
        fn_8022DBF4(value);
    } else if (index == 1) {
        fn_8022DC38(value);
    } else {
        fn_8007AA90(&_GameInfo_sCursor, _GameInfo_aColumnTags[index], value);
        _GameInfo_aRecord[index].mValue = value;
    }
}

int GameInfoGet(int index)
{
    if (index == 0) {
        return fn_8022E558();
    } else if (index == 1) {
        return fn_8022E560();
    }
    return _GameInfo_aRecord[index].mValue;
}
}
