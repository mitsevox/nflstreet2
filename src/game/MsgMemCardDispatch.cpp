/* Passes the front end's memory card messages on to the memory card save handler. */

#include "game/EditMenu.h"

extern "C" {
int MemCardScreenMsg(unsigned int id, int *p, int c, int *pResult);

int MsgMemCardDispatch(int group, unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 4:
        return MemCardScreenMsg(id, (int *)pArgs, unused, pResult);
    }
    return 0;
}
}
