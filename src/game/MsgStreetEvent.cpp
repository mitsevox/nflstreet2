/* Street Event menus: passes the front end's messages for the Street Event screens
   to the event list (MsgStreetEventSelect.cpp) or the event setup screen
   (MsgStreetEventSetup.cpp). */

#include "game/EditMenu.h"

extern "C" {
int MsgStreetEventSelectHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);
int MsgStreetEventSetupHandleMessage(unsigned int id, MenuArg_t *pArgs, int unused, int *pResult);

int MsgStreetEventDispatch(int group, unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 1:
        return MsgStreetEventSelectHandleMessage(id, pArgs, unused, pResult);
    case 2:
        return MsgStreetEventSetupHandleMessage(id, pArgs, unused, pResult);
    }
    return 0;
}
}
