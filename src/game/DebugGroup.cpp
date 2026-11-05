/* The debug flow group: a single debug stage that runs the debug module. */
#include "game/FlowGroupC.h"

static FlowStageEntry sStages[] = { { 30, "Debug Stage" }, { -1, 0 } };
static FlowTransitionEntry sRecords[] = { { -1, -1 } };
DebugGroup gDebugGroup;
static ModuleDependency sModules[] = { &gDebug, 0 };

const char *DebugGroup::GetName() { return "Debug Group"; }
FlowStageEntry *DebugGroup::GSGetStageList() { return sStages; }
FlowTransitionEntry *DebugGroup::GSGetTransitionList() { return sRecords; }

ModuleDependency *DebugGroup::GSGetStageModuleList(int id)
{
    if (id == 30) {
        return sModules;
    }
    return 0;
}

void DebugGroup::GSProcess() {}
int DebugGroup::GSTransition(int a, int id) { return 1; }
