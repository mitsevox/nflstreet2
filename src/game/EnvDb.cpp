/* Game-database access for the playing environments (the venues a game is played in): whether an
   environment is locked in a profile, locking and unlocking the two bonus environments, and reading
   the selected environment's row (pictures, UI name and other values). */

#include <string.h>

#include "game/fn_801FCE10.h"
#include "game/DbCursor.h"
#include "game/QueryStatus.h"

extern "C" {
int fn_8022F358(int index);
int fn_8022F3D4(int a);
}

static DbCursor _Env_sCursor;

extern "C" {
static void _EnvDbOpen(DbCursor *pObject)
{
    DbCursorOpenTable(pObject, 0x52564E45, 0x44495645);
}

static void _EnvDbClose(DbCursor *pObject)
{
    DbCursorClose(pObject);
}

int EnvIsLocked(int index, int id)
{
    int value;
    int result = fn_801FCE10(0, "use \x8c select 'KLNE' into \x82 from 'NEKL' where 'DIVE' = \x85\n",
                             fn_8022F3D4(fn_8022F358(index)), &value, id);

    if (QUERY_STATUS_ACCEPTED(result) && result != 0x17) {
        return value == 1;
    }
    return 0;
}

void EnvSetLocked(int index, int id, int value)
{
    fn_801FCE10(0, "use \x8c update 'NEKL' set 'KLNE' = \x82 where 'DIVE' = \x85\n",
                fn_8022F3D4(fn_8022F358(index)), value, id);
}

void EnvUnlockBonus(int index)
{
    EnvSetLocked(index, 10, 0);
    EnvSetLocked(index, 11, 0);
}

void EnvLockBonus(int index)
{
    EnvSetLocked(index, 10, 1);
    EnvSetLocked(index, 11, 1);
}

/* Selects the row whose 'DIVE' column equals id; the accessors below read
   that row until EnvRelease releases it. */
void EnvSelect(int id)
{
    _EnvDbOpen(&_Env_sCursor);
    DbCursorFindInt(&_Env_sCursor, 0x44495645, id, 0, 0);
}

void EnvRelease(void)
{
    _EnvDbClose(&_Env_sCursor);
}

void EnvGetPictures(int *pA, int *pB)
{
    *pA = DbCursorGetInt(&_Env_sCursor, 0x43495045);
    *pB = DbCursorGetInt(&_Env_sCursor, 0x32435045);
}

int EnvGetEVTL(void)
{
    return DbCursorGetInt(&_Env_sCursor, 0x4C545645);
}

float EnvGetEVPL(void)
{
    return fn_8007A9E4(&_Env_sCursor, 0x4C505645);
}

float EnvGetEVPF(void)
{
    return fn_8007A9E4(&_Env_sCursor, 0x46505645);
}

float EnvGetEVWD(void)
{
    return fn_8007A9E4(&_Env_sCursor, 0x44575645);
}

float EnvGetEVWL(void)
{
    return fn_8007A9E4(&_Env_sCursor, 0x4C575645);
}

int EnvGetEVDS(void)
{
    return DbCursorGetInt(&_Env_sCursor, 0x53445645);
}

float EnvGetEVED(void)
{
    return fn_8007A9E4(&_Env_sCursor, 0x44455645);
}

void EnvGetUIName(char *pDest, int count)
{
    char buffer[33];

    buffer[0] = 0;
    fn_8007AA3C(&_Env_sCursor, 0x49554E45, (int)buffer, sizeof(buffer));
    strncpy(pDest, buffer, count);
}

void EnvGetEVLO(int a, int b)
{
    fn_8007AA3C(&_Env_sCursor, 0x4F4C5645, a, b);
}

void EnvGetEVDE(int a, int b)
{
    fn_8007AA3C(&_Env_sCursor, 0x45445645, a, b);
}

int EnvIsENVFSet(void)
{
    return DbCursorGetInt(&_Env_sCursor, 0x46564E45) == 1;
}
}
