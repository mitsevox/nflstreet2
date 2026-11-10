/*
 * The team database file (db_teams.dat, named by the DbGame module at start-up). Opens the file as
 * a resource, creates a T3DB database under a free id and loads it from the open file on request,
 * so the database code can read team records from it; then destroys the database and closes the
 * file again.
 */
#include "engine/fn_801F8D60.h"
#include "game/ResOpenDevice.h"
#include "engine/cu_801C2EB4.h"
#include "engine/dbteams.h"
#include "engine/fn_8022C938.h"
#include "engine/fn_801F9134.h"
#include "engine/tdbiores.h"

extern int fn_801F8CE8(int *pHandle);

static char *_DbTeams_pFileName = 0;
static void *_DbTeams_pResource = 0;
static int _DbTeams_iMode = -1;
static int _DbTeams_iDbId = -1;

int DbTeamsInit(const char *pName)
{
    _DbTeams_pFileName = fn_8022C938(fn_801C3180(pName) + 1, 1);
    fn_801C2EB4(_DbTeams_pFileName, pName);
    return 0;
}

void DbTeamsShutdown(void)
{
    fn_8022C988(_DbTeams_pFileName);
    _DbTeams_pFileName = 0;
}

int DbTeamsOpen(void)
{
    int err = 0;

    _DbTeams_pResource = ResOpenDevice(_DbTeams_pFileName, 44);
    if (_DbTeams_pResource == 0) {
        err = 38;
    }
    if (err == 0) {
        err = fn_801F8CE8(&_DbTeams_iDbId);
        if (err == 0) {
            err = fn_801F8D60(_DbTeams_iDbId, -1);
            if (err != 0) {
                _DbTeams_iDbId = -1;
            }
        }
    }
    return err;
}

int DbTeamsIsOpen(void)
{
    if (_DbTeams_pResource) {
        return 1;
    }
    return 0;
}

int DbTeamsClose(void)
{
    int err = fn_801F8EEC(_DbTeams_iDbId);

    if (err == 0) {
        _DbTeams_iDbId = -1;
        if (ResClose(_DbTeams_pResource) != 0) {
            err = 39;
        }
    } else {
        ResClose(_DbTeams_pResource);
    }
    _DbTeams_pResource = 0;
    _DbTeams_iMode = -1;
    return err;
}

int DbTeamsLoad(int a, int *pOut)
{
    int err;
    int *pState = &_DbTeams_iMode;

    *pState = a;
    err = fn_801F9134(_DbTeams_iDbId, (int)&_DbTeams_pResource, 0, (int)&tdbioresCallback);
    *pState = -1;
    *pOut = err != 0 ? -1 : _DbTeams_iDbId;
    return err;
}
