/* The game database's option tables: sets one column of 'TPOM', 'TPOS' or
   'TPOG'; start/stop stubs of its module. */

#include "game/TDbCompilePerformOp.h"

int DbOptionsModuleInit(void)
{
    return 0;
}

void DbOptionsModuleShutdown(void)
{
}

int DbOptionsSetTpom(int column, int value)
{
    return TDbCompilePerformOp(0, "update 'TPOM' set \x8c = \x82\n", column, value);
}

int DbOptionsSetTpos(int column, int value)
{
    return TDbCompilePerformOp(0, "update 'TPOS' set \x8c = \x82\n", column, value);
}

int DbOptionsSetTposString(int column, const char *value)
{
    return TDbCompilePerformOp(0, "update 'TPOS' set \x8c = \x88\n", column, value);
}

int DbOptionsSetTpog(int column, int value)
{
    return TDbCompilePerformOp(0, "update 'TPOG' set \x8c = \x82\n", column, value);
}
