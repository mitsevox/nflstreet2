/* UIStudio message routing for screen group 2: the replay menu and the debug window. */
#include "game/EditMenu.h"

struct ReplayScreenArgs_t;
struct DebugWindowMsg_t;

extern "C" {
int ReplayScreenHandleMessage(unsigned int id, ReplayScreenArgs_t *pBlock, int unused, int *pResult);
int DebugWindowHandleMsg(unsigned int id, DebugWindowMsg_t *pBlock, int unused, int *pResult);

int UISGroup2HandleMsg(int group, unsigned int id, MenuArg_t *pArgs, int unused, int *pResult)
{
    switch (group) {
    case 3:
        return DebugWindowHandleMsg(id, (DebugWindowMsg_t *)pArgs, unused, pResult);
    case 2:
        return ReplayScreenHandleMessage(id, (ReplayScreenArgs_t *)pArgs, unused, pResult);
    case 5:
        return 0;
    }
    return 0;
}
}
