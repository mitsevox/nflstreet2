/* The main front-end flow group: its stages (loading, first start, main
   menu, online, exit to the game or exit the program), the stage changes
   it allows, the modules each stage needs, and the per-frame step that
   moves the front end from one stage to the next. */
#include "game/FlowGroupC.h"
#include "game/MainFEGroup.h"
#include "game/FlowManagerC.h"
#include "game/FELoop.h"
#include "game/FMCAPPORT.h"
#include "game/GameState.h"
#include "game/GameModules.h"


extern "C" {
void BootInstallResetCallback(void);
void BootRemoveResetCallback(void);
void fn_80072C90(unsigned int delay, int wait);
void fn_80072D98(unsigned int delay);
void GameTextSetBootFinished(unsigned char a);
extern const char _MainFEGroup_szName[];
extern FlowStageEntry_t _MainFEGroup_aStages[];
extern FlowTransitionEntry_t _MainFEGroup_aTransitions[];
extern ModuleDependency _MainFEGroup_aFirstStartModules[];
extern ModuleDependency _MainFEGroup_aFirstStartCompleteModules[];
extern ModuleDependency _MainFEGroup_aLoadingModules[];
extern ModuleDependency _MainFEGroup_aMainMenuModules[];
extern ModuleDependency _MainFEGroup_aOnlineModules[];
extern ModuleDependency _MainFEGroup_aExitModules[];
}

FlowStageEntry_t _MainFEGroup_aStages[] = {
    { 9, "FE Loading" },
    { 7, "FE FirstStart" },
    { 8, "FE FirstStartComplete" },
    { 10, "FE MainMenu" },
    { 11, "FE Online" },
    { 12, "FE ExitToInGame" },
    { 14, "FE ExitProgram" },
    { -1, 0 },
};

FlowTransitionEntry_t _MainFEGroup_aTransitions[] = {
    { 7, 8 },
    { 8, 9 },
    { 9, 10 },
    { 9, 11 },
    { 10, 12 },
    { 10, 14 },
    { 10, 11 },
    { 11, 9 },
    { 11, 12 },
    { -1, -1 },
};

const char _MainFEGroup_szName[] = "MainFE Group";

void MainLoopQuit();

extern LoadingFE gLoadingFE;
extern FEDLL gFEDLL;
extern UIListener gUIListener;
extern DbColPal gDbColPal;
extern FMMainFEInit gFMMainFEInit;
extern Timg gTimg;
extern FESnd gFESnd;
extern StatGen gStatGen;
extern FEPlyr gFEPlyr;

MainFEGroup gMainFEGroup;

ModuleDependency _MainFEGroup_aFirstStartModules[] = {
    &gQkl,
    &gGRender,
    &gFEDLL,
    &gUIListener,
    &gGameState,
    &gTimg,
    &gGRand,
    &gGameStateActivate,
    &gFESnd,
    &gUIS,
    0,
};

ModuleDependency _MainFEGroup_aFirstStartCompleteModules[] = {
    &gQkl,
    &gGRender,
    &gFEDLL,
    &gUIListener,
    0,
};

ModuleDependency _MainFEGroup_aLoadingModules[] = {
    &gGRender,
    &gLoadingFE,
    &gFEDLL,
    &gQkl,
    &gUIListener,
    &gDbColPal,
    &gFMMainFEInit,
    &gMemAudit,
    &gGameState,
    &gTimg,
    &gGRand,
    &gScrmRule,
    &gFEPlyBk,
    &gAnmsCelebration,
    &gAudmon,
    &gGameStateActivate,
    &gFESnd,
    &gStatGen,
    &gFEPlyr,
    &gRumble,
    &gUIS,
    &gFMCAPPORT,
    0,
};

ModuleDependency _MainFEGroup_aMainMenuModules[] = {
    &gGRender,
    &gFEDLL,
    &gFELoop,
    &gUIListener,
    &gDbColPal,
    &gFMMainFEInit,
    &gMemAudit,
    &gGameState,
    &gTimg,
    &gGRand,
    &gScrmRule,
    &gFEPlyBk,
    &gAnmsCelebration,
    &gAudmon,
    &gGameStateActivate,
    &gFESnd,
    &gStatGen,
    &gFEPlyr,
    &gRumble,
    &gUIS,
    &gFMCAPPORT,
    0,
};

ModuleDependency _MainFEGroup_aOnlineModules[] = {
    &gMemAudit,
    &gFEDLL,
    0,
};

ModuleDependency _MainFEGroup_aExitModules[] = {
    &gFEDLL,
    &gMemAudit,
    0,
};

const char *MainFEGroup::GSGetGroupName() { return _MainFEGroup_szName; }
FlowStageEntry_t *MainFEGroup::GSGetStageList() { return _MainFEGroup_aStages; }
FlowTransitionEntry_t *MainFEGroup::GSGetTransitionList() { return _MainFEGroup_aTransitions; }

ModuleDependency *MainFEGroup::GSGetStageModuleList(int id)
{
    switch (id) {
    case 7:
        return _MainFEGroup_aFirstStartModules;
    case 8:
        return _MainFEGroup_aFirstStartCompleteModules;
    case 9:
        return _MainFEGroup_aLoadingModules;
    case 10:
        return _MainFEGroup_aMainMenuModules;
    case 12:
    case 14:
        return _MainFEGroup_aExitModules;
    case 11:
        return _MainFEGroup_aOnlineModules;
    default:
        return 0;
    }
}

void MainFEGroup::GSProcess()
{
    GSFlowManagerC *p = &gGSFlowManager;

    if (p->fn_801CBE9C(3) == 0) {
        switch (p->fn_801CBEC8(2)) {
        case 7:
            gFELoop.Boot();
            p->fn_801CBEF4(2, 8);
            break;
        case 8:
            GameTextSetBootFinished(1);
            p->fn_801CBEF4(2, 9);
            break;
        case 9:
            BootInstallResetCallback();
            p->fn_801CBEF4(2, 10);
            break;
        case 10:
            if (!gFELoop.Update()) {
                BootRemoveResetCallback();
                if (!fn_801CBFA0(p)) {
                    p->fn_801CBEF4(2, 14);
                }
            }
            break;
        case 12:
            p->fn_801CBE24(2);
            p->fn_801CBD80(1, -1);
            break;
        case 14:
            MainLoopQuit();
            break;
        }
    }
}

int MainFEGroup::GSTransition(int a, int b)
{
    switch (b) {
    case 12:
        fn_80072C90(250, 1);
        break;
    case 10:
        fn_80072D98(250);
        break;
    }
    return 1;
}

extern "C" int MainFEGroupIsStarted(FlowGroupC *pGroup) { return fn_801CC4F4(pGroup); }

extern "C" int MainFEGroupIsFirstStart(FlowGroupC *pGroup)
{
    int result = 0;
    int stage = fn_801CC4FC(pGroup);

    if (MainFEGroupIsStarted(pGroup) && (stage == 7 || stage == 8)) {
        result = 1;
    }
    return result;
}
