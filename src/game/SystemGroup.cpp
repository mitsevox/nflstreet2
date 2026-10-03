#include "game/Class_801CC350.h"
#include "game/ModuleGroup_8008CC74.h"

extern "C" {
extern char lbl_8030A60C[];
}

static Record_802CCBAC sStages[] = { { 0, "System Stage" }, { -1, 0 } };
static Record_803EA3A8 sRecords[] = { { -1, -1 } };
SystemGroup gSystemGroup;
static ModuleDependency sModules[] = {
    &gSys,
    &gFileIO,
    &gRes,
    &gFont,
    &gGLIB,
    &gRender,
    &gSnd,
    lbl_8030A60C,
    &gFMSndgMusic,
    &gARes,
    &gCam,
    &gContext,
    &gCurve,
    &gMat,
    &gDb,
    &gDbGame,
    &gDbgPrint,
    &gEvent,
    &gLoading,
    &gMath,
    &gMemCard,
    &gObj,
    &gPeriph,
    &gRemap,
    &gSort,
    &gTex,
    &gVec,
    &gVpt,
    &gVRAM,
    &gTask,
    &gSysPreLoad,
    0
};

const char *SystemGroup::GetName() { return "System Group"; }
Record_802CCBAC *SystemGroup::vfn_04() { return sStages; }
Record_803EA3A8 *SystemGroup::vfn_05() { return sRecords; }

ModuleDependency *SystemGroup::vfn_06(int id)
{
    if (id == 0) {
        return sModules;
    }
    return 0;
}

void SystemGroup::vfn_02() {}
int SystemGroup::vfn_03() { return 1; }
