/* The system flow group: a single system stage that starts the core
   engine and game modules (system, files, resources, fonts, rendering,
   sound, database, memory card, input and the rest) the other groups
   rely on. */
#include "game/FlowGroupC.h"
#include "game/ModuleGroup_8008CC74.h"
#include "game/SndgPathfinder.h"

static FlowStageEntry sStages[] = { { 0, "System Stage" }, { -1, 0 } };
static FlowTransitionEntry sRecords[] = { { -1, -1 } };
SystemGroup gSystemGroup;
static ModuleDependency sModules[] = {
    &gSys,
    &gFileIO,
    &gRes,
    &gFont,
    &gGLIB,
    &gRender,
    &gSnd,
    &gSndgPathfinder,
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
FlowStageEntry *SystemGroup::GSGetStageList() { return sStages; }
FlowTransitionEntry *SystemGroup::GSGetTransitionList() { return sRecords; }

ModuleDependency *SystemGroup::GSGetStageModuleList(int id)
{
    if (id == 0) {
        return sModules;
    }
    return 0;
}

void SystemGroup::GSProcess() {}
int SystemGroup::GSTransition(int a, int id) { return 1; }
