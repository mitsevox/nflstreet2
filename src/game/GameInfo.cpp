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

static int sColumnTags[3] = { 0x47544847, 0x47544147, 0x47545047 };
static DbCursor sCursor;
static DbColumnValue sRecord[4];
static unsigned char sInitialized = 0;

extern "C" {

void GameInfoInit(void)
{
    DbCursorOpen(&sCursor, 0x464E4947, 0x554E5547, 0, 0, 0x454D4147);
    GameInfoRead();
    sInitialized = 1;
}

/* Reads the current values of all columns into sRecord. */
void GameInfoRead(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        sRecord[i].mTableTag = 0x464E4947;
        sRecord[i].mColumnTag = sColumnTags[i];
    }
    DbColumnValue *pEnd = &sRecord[3];
    pEnd->mValue = 0;
    pEnd->mColumnTag = -1;
    pEnd->mTableTag = -1;
    sCursor.Read(sRecord);
}

void GameInfoShutdown(void)
{
    DbCursorClose(&sCursor);
    sInitialized = 0;
}

unsigned char GameInfoIsInitialized(void)
{
    return sInitialized;
}

void GameInfoSet(int index, int value)
{
    if (index == 0) {
        fn_8022DBF4(value);
    } else if (index == 1) {
        fn_8022DC38(value);
    } else {
        fn_8007AA90(&sCursor, sColumnTags[index], value);
        sRecord[index].mValue = value;
    }
}

int GameInfoGet(int index)
{
    if (index == 0) {
        return fn_8022E558();
    } else if (index == 1) {
        return fn_8022E560();
    }
    return sRecord[index].mValue;
}
}
