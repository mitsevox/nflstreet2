#include "game/Module.h"
#include "game/cu_80003C94.h"
#include "game/ModuleGroup_8008CC74.h"
#include "game/GameState.h"
#include "game/ModuleGroup_80033A5C.h"

extern "C" {
extern char lbl_803071E8[];

void fn_800221CC(int);
void fn_80022328(void);
void fn_80022FF0(void);
void fn_80023048(void);
void fn_8004613C(void);
void fn_8008FBA0(void);
void fn_8015E654(int);
void fn_8015E6C4(void);
void fn_8015E6C8(void);
void fn_8015E950(int, int);
void fn_8015E994(void);
void fn_8015F35C(void);
void fn_8015F388(void);
void fn_80160874(int);
void fn_80160A80(void);
void fn_80160B6C(void);
void fn_801681A8(void);
void fn_80168210(void);
void fn_801684B8(int);
void fn_8017F664(void);
void fn_8019B5D4(void);
void fn_801F2798(const char *);
}

static ModuleDependency sFEPlyBkDependencies[] = { &gGameState, 0 };
static ModuleDependency sFEPlyBkLinks[] = { lbl_803071E8, 0 };
FEPlyBk gFEPlyBk;

ModuleDependency *FEPlyBk::GetDependencies() { return sFEPlyBkDependencies; }
ModuleDependency *FEPlyBk::GetLinks() { return sFEPlyBkLinks; }
const char *FEPlyBk::GetName() { return "FEPlyBk"; }

int FEPlyBk::Init()
{
    fn_801681A8();
    fn_80168210();
    return 1;
}

int FEPlyBk::Shutdown()
{
    fn_801684B8(0);
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

    fn_801F2798("PlyrModel-FEStart");
    fn_8015E654(0);
    fn_8015E6C4();
    fn_8015E950(1, 0);
    fn_801F2798("PlyrModel-FEFinish");
    fn_801F2798("PlyrTex-FEStart");
    fn_80160874(2);
    fn_80160A80();
    fn_801F2798("PlyrTex-FEFinish");
    if (sFirstInit) {
        sFirstInit = 0;
        fn_8015F35C();
        fn_800221CC(2);
        fn_8015F388();
    } else {
        fn_800221CC(2);
    }
    return 1;
}

int FEPlyr::Shutdown()
{
    fn_80022328();
    fn_8015E994();
    fn_8015E6C8();
    fn_80160B6C();
    return 1;
}

static ModuleDependency sFESndDependencies[] = { &gSnd, 0 };
FESnd gFESnd;

ModuleDependency *FESnd::GetDependencies() { return sFESndDependencies; }
ModuleDependency *FESnd::GetLinks() { return 0; }
const char *FESnd::GetName() { return "FESnd"; }

int FESnd::Init()
{
    fn_80022FF0();
    return 1;
}

int FESnd::Shutdown()
{
    fn_80023048();
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

    fn_8017F664();
    if (sFirstInit) {
        sFirstInit = 0;
        gSysPreLoad.fn_8008D4A8();
        fn_801F2798("DynClutInitStart");
        fn_8004613C();
        fn_801F2798("DynClutInitFinish");
        fn_8008FBA0();
    }
    fn_8019B5D4();
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
    fn_80003C94();
    return 1;
}

int StatGen::Shutdown()
{
    fn_80003CC4();
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
