/* The game flow manager: tells the engine flow manager that the game has
   four flow groups (system, in-game, main front end, debug) and hands
   out each group object by index. */
#include "game/FlowManagerC.h"
#include "game/FlowGroupC.h"
#include "game/Class_800325E8.h"

extern "C" {
extern char gMainFEGroup[];
}

GSFlowManagerC gGSFlowManager;

int GSFlowManagerC::GSGetNumGroups() { return 4; }

void *GSFlowManagerC::GSCreateGroup(int index)
{
    switch (index) {
    case 0:
        return &gSystemGroup;
    case 1:
        return &lbl_803068B4;
    case 2:
        return gMainFEGroup;
    case 3:
        return &gDebugGroup;
    }
    return 0;
}

void GSFlowManagerC::GSDestroyGroup() {}
