/* The debug flow group: a single debug stage that runs the debug module. */
#include "game/FlowGroupC.h"

static FlowStageEntry_t _DebugGroup_aStages[] = { { 30, "Debug Stage" }, { -1, 0 } };
static FlowTransitionEntry_t _DebugGroup_aTransitions[] = { { -1, -1 } };
DebugGroup gDebugGroup;
static ModuleDependency _DebugGroup_aModules[] = { &gDebug, 0 };

const char *DebugGroup::GSGetGroupName() { return "Debug Group"; }
FlowStageEntry_t *DebugGroup::GSGetStageList() { return _DebugGroup_aStages; }
FlowTransitionEntry_t *DebugGroup::GSGetTransitionList() { return _DebugGroup_aTransitions; }

ModuleDependency *DebugGroup::GSGetStageModuleList(int id)
{
    if (id == 30) {
        return _DebugGroup_aModules;
    }
    return 0;
}

void DebugGroup::GSProcess() {}
int DebugGroup::GSTransition(int a, int id) { return 1; }
