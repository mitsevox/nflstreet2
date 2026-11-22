/* Empties the two formation lineup tables of the game database. */

#include "game/TDbCompilePerformOp.h"

extern "C" {

void FormationLineupClearBase(void)
{
    TDbCompilePerformOp(0, "use 'EMAG' delete from 'BLMF'\n");
}

void FormationLineupClearUser(void)
{
    TDbCompilePerformOp(0, "use 'EMAG' delete from 'ULMF'\n");
}

}
