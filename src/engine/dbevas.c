/* The save-game database ('EVAS'): keeps its file name, creates and fills it
   when the game database starts, and loads, saves and destroys it for the
   memory card load and save. */

#include "engine/dbutil.h"
#include "engine/tdbext.h"
#include "engine/TDbCreate.h"
#include "engine/TDbLoad.h"
#include "game/TDbCompilePerformOp.h"
#include <string.h>

struct CardStreamTarget;
struct SaveStreamOps_t;

extern int TDbSave(int handle, int a, int b);

static int _DbEvas_iSize = 0;
static char *_DbEvas_pFileName = 0;
static int _DbEvas_iMode = -1;

int DbEvasModuleInit(void)
{
    return 0;
}

void DbEvasModuleShutdown(void)
{
}

int DbEvasInit(int a, const char *pName, int b)
{
    _DbEvas_pFileName = DbUtilAlloc(strlen(pName) + 1, 1);
    strcpy(_DbEvas_pFileName, pName);
    _DbEvas_iMode = b;
    return 0;
}

void DbEvasShutdown(void)
{
    DbUtilFree(_DbEvas_pFileName);
    _DbEvas_iSize = 0;
    _DbEvas_pFileName = 0;
    _DbEvas_iMode = -1;
}

int DbEvasLoad(void)
{
    int result = TDbCreate(0x45564153, _DbEvas_iSize);
    if (result == 0) {
        result = TDbExtLoadFromResource(0x45564153, _DbEvas_pFileName, _DbEvas_iMode, 0);
    }
    return result;
}

int DbEvasLoadStream(struct CardStreamTarget *pTarget, struct SaveStreamOps_t *pOps)
{
    return TDbLoad(0x45564153, (int)pTarget, 0, (int)pOps);
}

int DbEvasSaveStream(void *pTarget, struct SaveStreamOps_t *pOps)
{
    return TDbSave(0x45564153, (int)pTarget, (int)pOps);
}

int DbEvasUnload(void)
{
    return TDbDestroy(0x45564153);
}

// FAKEMATCH: discarded stand-in (static inline, so ProDG emits its literals without its code);
// its literals are the unreferenced 0x802B5C1C-0x802B5C8C queries of the target .rodata
static inline int _DbEvasCopyStats(const char *pDbName)
{
    int status = TDbCompilePerformOp(0, "use 'EVAS' insert into \x8c.'TPOS' * select * from 'TPOS'\n", pDbName);

    if (status == 0) {
        status = TDbCompilePerformOp(0, "use 'EVAS' insert into \x8c.'TPOG' * select * from 'TPOG'\n", pDbName);
    }
    return status;
}
