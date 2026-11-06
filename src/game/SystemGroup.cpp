/* The system flow group: a single system stage that starts the core
   engine and game modules (system, files, resources, fonts, rendering,
   sound, database, memory card, input and the rest) the other groups
   rely on. */
#include "game/FlowGroupC.h"
#include "game/SysModules.h"
#include "game/SndgPathfinder.h"

static FlowStageEntry_t _SystemGroup_aStages[] = { { 0, "System Stage" }, { -1, 0 } };
static FlowTransitionEntry_t _SystemGroup_aTransitions[] = { { -1, -1 } };
SystemGroup gSystemGroup;
static ModuleDependency _SystemGroup_aModules[] = {
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

const char *SystemGroup::GSGetGroupName() { return "System Group"; }
FlowStageEntry_t *SystemGroup::GSGetStageList() { return _SystemGroup_aStages; }
FlowTransitionEntry_t *SystemGroup::GSGetTransitionList() { return _SystemGroup_aTransitions; }

ModuleDependency *SystemGroup::GSGetStageModuleList(int id)
{
    if (id == 0) {
        return _SystemGroup_aModules;
    }
    return 0;
}

void SystemGroup::GSProcess() {}
int SystemGroup::GSTransition(int a, int id) { return 1; }
