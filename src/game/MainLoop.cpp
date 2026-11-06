/* The main loop: starts the system modules and runs the module groups frame by frame until the game quits. */

#include "game/Class_801CBC50.h"
#include "game/Module.h"

extern "C" {

void FESndShutdown(void);
int fn_801CC7FC(ModuleNode *pNode);
int fn_801CC820(ModuleNode *pNode, unsigned char flags);
int fn_801CC8AC(ModuleNode *pNode, unsigned char flags);
void fn_801D64EC(void);
int fn_801F3D2C(void);
}

/* Set by MainLoopQuit; ends the loop in MainLoopRun. */
static unsigned char _MainLoop_bDone = 0;
float gFrameTimeScale = 1.0f;

void MainLoopUpdate(void)
{
    fn_801CBFA8(&lbl_803067B0);
}

void MainLoopRun(void)
{
    Sys *pModule = &gSys;
    fn_801CC7FC(pModule);
    fn_801CC820(pModule, 0);

    Class_803067B0 *pObject = &lbl_803067B0;
    fn_801CBCD0(pObject);
    fn_801CC054(pObject, 0);
    pObject->fn_801CBD80(0, -1);
    pObject->fn_801CBD80(2, 7);

    while (!_MainLoop_bDone) {
        MainLoopUpdate();
    }

    FESndShutdown();
    fn_801F3D2C();
    fn_801D64EC();
    fn_801CC8AC(&gSys, 0);
}

void MainLoopQuit(void)
{
    _MainLoop_bDone = 1;
}
