#include "game/Module.h"
#include "game/StatGen.h"
#include "game/SysModules.h"
#include "game/GameState.h"
#include "game/GameModules.h"
#include "game/InGameModules.h"

extern "C" {
void FEPlyrInit(int);
void FEPlyrShutdown(void);
void FESndInit(void);
void FESndShutdown(void);
void PlaDynClutLoad(void);
void fn_8008FBA0(void);
void PlaModelSetLodMode(int);
void PlaModelInitPlayerModels(void);
void PlaModelResetPlayerModels(void);
void PlaModelInitMorphHead(int, int);
void PlaModelFreeMorphHead(void);
void PlaModelBeginFaceCache(void);
void PlaModelEndFaceCache(void);
void PlaTexCacheInit(int);
void PlaTexCacheLoadDefaults(void);
void PlaTexCacheShutdown(void);
void PlayBookAlloc(void);
void PlayBookClear(void);
void PlayBookCloseDatabases(int);
void GameModeTypeInvalidate(void);
void LevelLightsSelectFrontEnd(void);
void ResTrackLabel(const char *);
}

static ModuleDependency sFEPlyBkDependencies[] = { &gGameState, 0 };
static ModuleDependency sFEPlyBkLinks[] = { &gPlayBook, 0 };
FEPlyBk gFEPlyBk;

ModuleDependency *FEPlyBk::GetDependencies() { return sFEPlyBkDependencies; }
ModuleDependency *FEPlyBk::GetLinks() { return sFEPlyBkLinks; }
const char *FEPlyBk::GetName() { return "FEPlyBk"; }

int FEPlyBk::Init()
{
    PlayBookAlloc();
    PlayBookClear();
    return 1;
}

int FEPlyBk::Shutdown()
{
    PlayBookCloseDatabases(0);
    return 1;
}

static ModuleDependency sFEPlyrDependencies[] = { &gGRender, &gAnimData, &gStaData, 0 };
FEPlyr gFEPlyr;

ModuleDependency *FEPlyr::GetDependencies() { return sFEPlyrDependencies; }
ModuleDependency *FEPlyr::GetLinks() { return 0; }
const char *FEPlyr::GetName() { return "FEPlyr"; }

int FEPlyr::Init()
{
    static unsigned char sFirstInit = 1;

    ResTrackLabel("PlyrModel-FEStart");
    PlaModelSetLodMode(0);
    PlaModelInitPlayerModels();
    PlaModelInitMorphHead(1, 0);
    ResTrackLabel("PlyrModel-FEFinish");
    ResTrackLabel("PlyrTex-FEStart");
    PlaTexCacheInit(2);
    PlaTexCacheLoadDefaults();
    ResTrackLabel("PlyrTex-FEFinish");
    if (sFirstInit) {
        sFirstInit = 0;
        PlaModelBeginFaceCache();
        FEPlyrInit(2);
        PlaModelEndFaceCache();
    } else {
        FEPlyrInit(2);
    }
    return 1;
}

int FEPlyr::Shutdown()
{
    FEPlyrShutdown();
    PlaModelFreeMorphHead();
    PlaModelResetPlayerModels();
    PlaTexCacheShutdown();
    return 1;
}

static ModuleDependency sFESndDependencies[] = { &gSnd, 0 };
FESnd gFESnd;

ModuleDependency *FESnd::GetDependencies() { return sFESndDependencies; }
ModuleDependency *FESnd::GetLinks() { return 0; }
const char *FESnd::GetName() { return "FESnd"; }

int FESnd::Init()
{
    FESndInit();
    return 1;
}

int FESnd::Shutdown()
{
    FESndShutdown();
    return 1;
}

static void *sFMMainFEInitDependencies[] = { 0 };
FMMainFEInit gFMMainFEInit;

ModuleDependency *FMMainFEInit::GetDependencies() { return (ModuleDependency *)sFMMainFEInitDependencies; }
ModuleDependency *FMMainFEInit::GetLinks() { return 0; }
const char *FMMainFEInit::GetName() { return "FMMainFEInit"; }

int FMMainFEInit::Init()
{
    static unsigned char sFirstInit = 1;

    GameModeTypeInvalidate();
    if (sFirstInit) {
        sFirstInit = 0;
        gSysPreLoad.LoadSystems();
        ResTrackLabel("DynClutInitStart");
        PlaDynClutLoad();
        ResTrackLabel("DynClutInitFinish");
        fn_8008FBA0();
    }
    LevelLightsSelectFrontEnd();
    return 1;
}

int FMMainFEInit::Shutdown()
{
    return 1;
}

static void *sStatGenDependencies[] = { 0 };
StatGen gStatGen;

ModuleDependency *StatGen::GetDependencies() { return (ModuleDependency *)sStatGenDependencies; }
ModuleDependency *StatGen::GetLinks() { return 0; }
const char *StatGen::GetName() { return "StatGen"; }

int StatGen::Init()
{
    StatGenCreateRandomStream();
    return 1;
}

int StatGen::Shutdown()
{
    StatGenDestroyRandomStream();
    return 1;
}

static void *sUIListenerDependencies[] = { 0 };
UIListener gUIListener;

ModuleDependency *UIListener::GetDependencies() { return (ModuleDependency *)sUIListenerDependencies; }
ModuleDependency *UIListener::GetLinks() { return 0; }
const char *UIListener::GetName() { return "UIListener"; }

int UIListener::Init()
{
    return 1;
}

int UIListener::Shutdown()
{
    return 1;
}
