/* The user-profile databases: up to two per-user databases with their
   'FNIU' user-info table - create, delete and reset a user, find users by id
   or database, pick the current user, and load and save a user's database
   for the memory card. */

#include "engine/dbutil.h"
#include "engine/tdbext.h"
#include "engine/TDbCreate.h"
#include "engine/TDbLoad.h"
#include "engine/DbUserEntry.h"
#include "game/DbUserSetCurrent.h"
#include "game/TDbCompilePerformOp.h"
#include <string.h>

typedef struct DbUserSaveRequest_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mTarget;
    unsigned char mbAsync;
} DbUserSaveRequest_t;

typedef struct DbUserAsync_t {
    int mDb;
    int mUnknown4;
    int mUnknown8;
    int mTarget;
    void *mpOps;
    void (*mpDone)(void);
    int mUnknown18;
} DbUserAsync_t;

extern int TDbSave(int handle, int a, int b);
extern void TDbLoadAsync(DbUserAsync_t *pReq, void (*pStart)(void *pJob), int a, int b);
extern void TDbSaveAsync(DbUserAsync_t *pReq, void (*pStart)(void *pJob), int a, int b);
extern void DbSaveThreadStart(void *pJob);
extern void DbSaveThreadOnComplete(void);

signed char DbUserFindIndex(int key);
int DbUserFindIdByDb(int key);
int DbUserGetDb(int key);
int DbUserGetCurrent(void);

static DbUserEntry_t _DbUser_aEntries[2] = { { -1, -1 }, { -1, -1 } };
static int _DbUser_iSize = 0;
static char *_DbUser_pFileName = 0;
static int _DbUser_iMode = -1;
static int _DbUser_iCurrent = -1;
static unsigned char _DbUser_iCount = 0;
static const int _DbUser_aDbIds[2] = { 0x30525355, 0x31525355 };
static DbUserAsync_t _DbUser_LoadJob;
static DbUserAsync_t _DbUser_SaveJob;


int DbUserNewId(void)
{
    int key;
    do {
        key = DbUtilRandomRange(0, 0x7FFFFFFA) & 0x7FFFFFFF;
    } while (DbUserFindIndex(key) != -1);
    return key;
}

int DbUserInit(int a, const char *pName, int b)
{
    int result = 0;

    _DbUser_iSize = a;
    _DbUser_pFileName = DbUtilAlloc(strlen(pName) + 1, 1);
    strcpy(_DbUser_pFileName, pName);
    _DbUser_iMode = b;
    _DbUser_iCurrent = -1;
    _DbUser_iCount = result;
    return result;
}

void DbUserShutdown(void)
{
    DbUtilFree(_DbUser_pFileName);
    _DbUser_iSize = 0;
    _DbUser_pFileName = 0;
    _DbUser_iMode = -1;
    _DbUser_iCurrent = -1;
    _DbUser_iCount = 0;
}

int DbUserCreate(void)
{
    unsigned char i;
    int id;
    int key;
    int old;

    id = -1;
    if ((signed char)_DbUser_iCount <= 1) {
        for (i = 0; DbUserFindIdByDb(key = _DbUser_aDbIds[i]) != -1; i++) {
        }
        id = DbUserNewId();
        _DbUser_aEntries[(signed char)_DbUser_iCount].mId = id;
        _DbUser_aEntries[(signed char)_DbUser_iCount].mDb = key;
        TDbExtLoadFromResource(key, _DbUser_pFileName, _DbUser_iMode, 0);
        _DbUser_iCount++;
        old = DbUserSetCurrent(id);
        TDbCompilePerformOp(0, "use \x8c update 'FNIU' set 'DIGU' = \x82\n", DbUserGetDb(DbUserGetCurrent()), id);
        DbUserSetCurrent(old);
    }
    return id;
}

void DbUserDelete(int key)
{
    signed char index;

    if (key != -1) {
        index = DbUserFindIndex(key);
        if (index != -1) {
            _DbUser_iCount--;
            TDbExtLoadFromResource(_DbUser_aEntries[index].mDb, _DbUser_pFileName, _DbUser_iMode, 0);
            for (; index < (signed char)_DbUser_iCount; index++) {
                memcpy(&_DbUser_aEntries[index], &_DbUser_aEntries[index + 1], sizeof(_DbUser_aEntries[0]));
            }
            _DbUser_aEntries[(signed char)_DbUser_iCount].mId = -1;
            _DbUser_aEntries[(signed char)_DbUser_iCount].mDb = -1;
        }
    }
}

void DbUserReset(int key)
{
    int index;
    int id;
    int old;

    if (key != -1) {
        index = DbUserFindIndex(key);
        if (index != -1) {
            TDbExtLoadFromResource(_DbUser_aEntries[index].mDb, _DbUser_pFileName, _DbUser_iMode, 0);
            id = DbUserNewId();
            old = DbUserSetCurrent(key);
            TDbCompilePerformOp(0, "use \x8c update 'FNIU' set 'DIGU' = \x82\n", DbUserGetDb(DbUserGetCurrent()), id);
            _DbUser_aEntries[index].mId = id;
            if (old == key) {
                DbUserSetCurrent(id);
            } else {
                DbUserSetCurrent(old);
            }
        }
    }
}

int DbUserGetCount(void)
{
    return (signed char)_DbUser_iCount;
}

int DbUserGetId(int index)
{
    int value = -1;
    if (index < (signed char)_DbUser_iCount) {
        value = _DbUser_aEntries[index].mId;
    }
    return value;
}

signed char DbUserFindIndex(int key)
{
    signed char i;
    for (i = 0; i < (signed char)_DbUser_iCount; i++) {
        if (key == _DbUser_aEntries[i].mId) {
            return i;
        }
    }
    return -1;
}

int DbUserGetDb(int key)
{
    int value = -1;
    if (key != -1) {
        int index = DbUserFindIndex(key);
        if (index != -1) {
            value = _DbUser_aEntries[index].mDb;
        }
    }
    return value;
}

int DbUserFindIdByDb(int key)
{
    unsigned char i = _DbUser_iCount;

    while (--i != 255) {
        if (_DbUser_aEntries[i].mDb == key) {
            return _DbUser_aEntries[i].mId;
        }
    }
    return -1;
}

int DbUserSetCurrent(int value)
{
    int old = _DbUser_iCurrent;

    _DbUser_iCurrent = value;
    return old;
}

int DbUserSelect(int value)
{
    DbUserSetCurrent(value);
    return DbUserGetDb(value);
}

int DbUserGetCurrent(void)
{
    return _DbUser_iCurrent;
}

int DbUserOpenDatabases(void)
{
    int err = 0;
    unsigned int i;

    for (i = 0; i <= 1 && (err = TDbCreate(_DbUser_aDbIds[i], _DbUser_iSize)) == 0; i++) {
        err = TDbExtLoadFromResource(_DbUser_aDbIds[i], _DbUser_pFileName, _DbUser_iMode, 0);
        if (err != 0) {
            break;
        }
    }
    return err;
}

int DbUserPostLoad(int a)
{
    int key;
    int err;

    if (a == 0) {
        err = TDbCompilePerformOp(0, "use \x8c select 'DIGU' into \x82 from 'FNIU'\n", DbUserGetDb(DbUserGetCurrent()), &key);
        if (key != DbUserGetCurrent()) {
            if (DbUserFindIndex(key) == -1) {
                (_DbUser_aEntries + DbUserFindIndex(DbUserGetCurrent()))->mId = key;
                _DbUser_iCurrent = key;
            } else {
                err = 1;
            }
        }
    } else {
        err = 36;
    }
    return err;
}

int DbUserLoad(DbUserSaveRequest_t *pRequest, void *pOps)
{
    int result = 0;

    if (pRequest->mbAsync != 0) {
        _DbUser_LoadJob.mDb = DbUserGetDb(DbUserGetCurrent());
        _DbUser_LoadJob.mUnknown4 = result;
        _DbUser_LoadJob.mUnknown8 = pRequest->mUnknown0;
        _DbUser_LoadJob.mTarget = pRequest->mTarget;
        _DbUser_LoadJob.mpOps = pOps;
        _DbUser_LoadJob.mpDone = DbSaveThreadOnComplete;
        TDbLoadAsync(&_DbUser_LoadJob, DbSaveThreadStart, pRequest->mUnknown4, pRequest->mUnknown8);
    } else {
        result = DbUserPostLoad(TDbLoad(DbUserGetDb(DbUserGetCurrent()), pRequest->mTarget, 0, (int)pOps));
    }
    return result;
}

int DbUserSave(DbUserSaveRequest_t *pRequest, void *pOps)
{
    int result = 0;

    if (pRequest->mbAsync != 0) {
        _DbUser_SaveJob.mDb = DbUserGetDb(DbUserGetCurrent());
        _DbUser_SaveJob.mUnknown4 = result;
        _DbUser_SaveJob.mUnknown8 = pRequest->mUnknown0;
        _DbUser_SaveJob.mTarget = pRequest->mTarget;
        _DbUser_SaveJob.mpOps = pOps;
        _DbUser_SaveJob.mpDone = DbSaveThreadOnComplete;
        TDbSaveAsync(&_DbUser_SaveJob, DbSaveThreadStart, pRequest->mUnknown4, pRequest->mUnknown8);
    } else {
        result = TDbSave(DbUserGetDb(DbUserGetCurrent()), pRequest->mTarget, (int)pOps);
    }
    return result;
}

int DbUserCloseDatabases(void)
{
    int err = 0;
    unsigned int i;

    for (i = 0; i <= 1; i++) {
        err = TDbDestroy(_DbUser_aDbIds[i]);
        if (err != 0) {
            break;
        }
    }
    return err;
}

int DbUserSetName(int value, char *pName)
{
    int err = 0;
    int old = DbUserSetCurrent(value);

    if (DbUserGetDb(DbUserGetCurrent()) != -1) {
        err = TDbCompilePerformOp(0, "use \x8c update 'FNIU' set 'nuSP' = \x88\n", DbUserGetDb(DbUserGetCurrent()), pName);
    }
    DbUserSetCurrent(old);
    return err;
}
