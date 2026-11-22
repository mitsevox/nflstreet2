/* The game database's mode state ('NIOM' table): starts and ends a game mode,
   keeps the active mode's handler and function tables and calls them, and
   reads through the 'NIOM' cursor; also starts and stops the database
   random stream with the game database. */

#include "engine/dbutil.h"
#include "engine/DbNiomHandlers.h"
#include "engine/DbNiomModeFuncs.h"
#include "game/TDbCompilePerformOp.h"

int fn_8022A59C(int a, void **ppOut);
int fn_8022AB6C(void *p, int a, int b);
int fn_8022AC80(void *p);
int DbNiomCloseCursor(void);

static int (*_DbNiom_pEndFunc)(void) = 0;
static void *_DbNiom_pLoadFunc = 0;
static void *_DbNiom_pResetFunc = 0;
static void (*_DbNiom_pCallback)(int) = 0;
static int _DbNiom_iCallbackArg = -1;
static unsigned char _DbNiom_bModeActive = 0;
static unsigned char _DbNiom_bEnding = 0;
static void *_DbNiom_pCursor = 0;
static int _DbNiom_iUnused = 0;
static int (*_DbNiom_pModeEnd)(void) = 0;
static int (*_DbNiom_pModeLoad)(void **ppData, void *p) = 0;
static int (*_DbNiom_pModeReset)(int a, int b) = 0;
static int (*_DbNiom_pModeResume)(void) = 0;
static int (*_DbNiom_pModeFn16)(void) = 0;

int DbNiomInit(void)
{
    DbUtilRandomInit();
    return 0;
}

void DbNiomShutdown(void)
{
    DbUtilRandomShutdown();
    DbNiomCloseCursor();
    _DbNiom_pEndFunc = 0;
    _DbNiom_pLoadFunc = 0;
    _DbNiom_pResetFunc = 0;
    _DbNiom_pCallback = 0;
    _DbNiom_iCallbackArg = -1;
    _DbNiom_bModeActive = 0;
}

void DbNiomSetHandlers(DbNiomHandlers_t *p)
{
    _DbNiom_pEndFunc = p->mpUnknown0;
    _DbNiom_pLoadFunc = p->mpUnknown4;
    _DbNiom_pResetFunc = p->mpUnknown8;
}

int DbNiomIsModeActive(void)
{
    return _DbNiom_bModeActive;
}

int DbNiomBeginMode(int *p)
{
    int err = 0;

    if (_DbNiom_bModeActive == 0) {
        err = TDbCompilePerformOp(0, "update 'NIOM' set 'PYTM' = \x82\n", *p);
        if (err == 0) {
            _DbNiom_bModeActive = 1;
        }
    }
    return err;
}

int DbNiomEndMode(void)
{
    int err = 0;

    if (_DbNiom_bModeActive == 1) {
        _DbNiom_bEnding = 1;
        err = _DbNiom_pEndFunc();
        if (err == 0) {
            err = DbNiomCloseCursor();
        } else {
            DbNiomCloseCursor();
        }
        _DbNiom_bModeActive = 0;
        _DbNiom_bEnding = 0;
    }
    return err;
}

int DbNiomRunCallback(void)
{
    if (_DbNiom_pCallback != 0) {
        _DbNiom_pCallback(_DbNiom_iCallbackArg);
    }
    return 0;
}

int DbNiomOpenCursor(int a)
{
    int err = 0;

    if (_DbNiom_pCursor == 0) {
        err = fn_8022A59C(a, &_DbNiom_pCursor);
        if (err != 0) {
            DbNiomCloseCursor();
        }
    }
    return err;
}

int DbNiomReadCursor(int a, int b)
{
    return fn_8022AB6C(_DbNiom_pCursor, a, b);
}

int DbNiomCloseCursor(void)
{
    int err = 0;

    if (_DbNiom_pCursor != 0) {
        err = fn_8022AC80(_DbNiom_pCursor);
        _DbNiom_pCursor = 0;
    }
    return err;
}

int DbNiomReadOnce(int a, int b)
{
    int err = DbNiomOpenCursor(0);

    if (err == 0) {
        err = DbNiomReadCursor(a, b);
    }
    if (err == 0) {
        err = DbNiomCloseCursor();
    } else {
        DbNiomCloseCursor();
    }
    return err;
}

void DbNiomSetModeFuncs(DbNiomModeFuncs_t *pFuncs)
{
    _DbNiom_pModeEnd = pFuncs->mpUnknown0;
    _DbNiom_pModeLoad = pFuncs->mpUnknown4;
    _DbNiom_pModeReset = pFuncs->mpUnknown8;
    _DbNiom_pModeResume = pFuncs->mpUnknown12;
    _DbNiom_pModeFn16 = pFuncs->mpUnknown16;
}

void DbNiomClearModeFuncs(void)
{
    _DbNiom_pModeEnd = 0;
    _DbNiom_pModeLoad = 0;
    _DbNiom_pModeReset = 0;
    _DbNiom_pModeResume = 0;
    _DbNiom_pModeFn16 = 0;
}

int DbNiomModeLoad(void **ppData, void *p)
{
    return _DbNiom_pModeLoad(ppData, p);
}

int DbNiomModeReset(int a, int b)
{
    return _DbNiom_pModeReset(a, b);
}

int DbNiomModeResume(void)
{
    return _DbNiom_pModeResume();
}
