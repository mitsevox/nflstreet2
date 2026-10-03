#include "game/Class_801CC350.h"

static Record_802CCBAC sStages[] = { { 30, "Debug Stage" }, { -1, 0 } };
static Record_803EA3A8 sRecords[] = { { -1, -1 } };
DebugGroup gDebugGroup;
static ModuleDependency sModules[] = { &gDebug, 0 };

const char *DebugGroup::GetName() { return "Debug Group"; }
Record_802CCBAC *DebugGroup::fn_800324BC() { return sStages; }
Record_803EA3A8 *DebugGroup::fn_800324C8() { return sRecords; }

ModuleDependency *DebugGroup::fn_800324D0(int id)
{
    if (id == 30) {
        return sModules;
    }
    return 0;
}

void DebugGroup::fn_800324E4() {}
int DebugGroup::fn_800324E8() { return 1; }
