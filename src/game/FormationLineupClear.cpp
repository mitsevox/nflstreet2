/* Empties the two formation lineup tables of the game database. */

#include "game/fn_801FCE10.h"

extern "C" {

void FormationLineupClearBase(void)
{
    fn_801FCE10(0, "use 'EMAG' delete from 'BLMF'\n");
}

void FormationLineupClearUser(void)
{
    fn_801FCE10(0, "use 'EMAG' delete from 'ULMF'\n");
}

}
