/* The main loop: starts the system modules and runs the module groups frame by frame until the game quits. */

#include "game/FlowManagerC.h"
#include "game/Module.h"

extern "C" {

void FESndShutdown(void);
int FlowModulePreStart(FlowModuleC *pNode);
int FlowModuleStart(FlowModuleC *pNode, unsigned char flags);
int FlowModuleStop(FlowModuleC *pNode, unsigned char flags);
void fn_801D64EC(void);
int fn_801F3D2C(void);
}

/* Set by MainLoopQuit; ends the loop in MainLoopRun. */
static unsigned char _MainLoop_bDone = 0;
float gFrameTimeScale = 1.0f;

void MainLoopUpdate(void)
{
    gGSFlowManager.Process();
}

void MainLoopRun(void)
{
    Sys *pModule = &gSys;
    FlowModulePreStart(pModule);
    FlowModuleStart(pModule, 0);

    GSFlowManagerC *pObject = &gGSFlowManager;
    pObject->Init();
    pObject->SetVerboseFlags(0);
    pObject->StartGroup(0, -1);
    pObject->StartGroup(2, 7);

    while (!_MainLoop_bDone) {
        MainLoopUpdate();
    }

    FESndShutdown();
    fn_801F3D2C();
    fn_801D64EC();
    FlowModuleStop(&gSys, 0);
}

void MainLoopQuit(void)
{
    _MainLoop_bDone = 1;
}
