/*
 * Loads the T3DB database that the game's queries address as 'TATS'. At start-up the
 * DbGame module gives it the database size, the file to load it from (template.dat) and a load
 * mode; it then creates the database and fills it from that file, and destroys it at shutdown.
 */
#include "engine/fn_8022C938.h"
#include <string.h>
#include "engine/dbtats.h"
#include "engine/fn_801F8D60.h"
#include "engine/tdbext.h"


static int _DbTats_iSize = 0;
static char *_DbTats_pFileName = 0;
static int _DbTats_iMode = -1;

int DbTatsInit(int a, const char *pName, int b)
{
    _DbTats_pFileName = fn_8022C938(strlen(pName) + 1, 1);
    strcpy(_DbTats_pFileName, pName);
    _DbTats_iSize = a;
    _DbTats_iMode = b;
    return 0;
}

void DbTatsShutdown(void)
{
    fn_8022C988(_DbTats_pFileName);
    _DbTats_iSize = 0;
    _DbTats_pFileName = 0;
    _DbTats_iMode = -1;
}

int DbTatsLoad(void)
{
    int err = fn_801F8D60(0x54415453, _DbTats_iSize);

    if (err == 0) {
        err = TDbExtLoadFromResource(0x54415453, _DbTats_pFileName, _DbTats_iMode, 0);
    }
    return err;
}

int DbTatsUnload(void)
{
    return fn_801F8EEC(0x54415453);
}
