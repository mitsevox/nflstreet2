#include "game/Class_801CC350.h"

static Record_802CCBAC sStages[] = { { 30, "Debug Stage" }, { -1, 0 } };
static Record_803EA3A8 sRecords[] = { { -1, -1 } };
DebugGroup gDebugGroup;
static ModuleDependency sModules[] = { &gDebug, 0 };

const char *DebugGroup::GetName() { return "Debug Group"; }
Record_802CCBAC *DebugGroup::vfn_04() { return sStages; }
Record_803EA3A8 *DebugGroup::vfn_05() { return sRecords; }

ModuleDependency *DebugGroup::vfn_06(int id)
{
    if (id == 30) {
        return sModules;
    }
    return 0;
}

void DebugGroup::vfn_02() {}
int DebugGroup::vfn_03() { return 1; }
