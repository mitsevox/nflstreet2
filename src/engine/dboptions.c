/* The game database's 'TPOM' option table: sets one of its columns;
   start/stop stubs of its module. */

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
