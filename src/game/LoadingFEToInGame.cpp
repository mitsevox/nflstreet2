#include "game/Module.h"

extern "C" {
extern char lbl_8030BFB4[];

void fn_80194858(int);
}

static ModuleDependency sDependencies[] = { lbl_8030BFB4, &gGRender, 0 };
LoadingFEToInGame gLoadingFEToInGame;

ModuleDependency *LoadingFEToInGame::GetDependencies() { return sDependencies; }
ModuleDependency *LoadingFEToInGame::GetLinks() { return 0; }
const char *LoadingFEToInGame::GetName() { return "LoadingFEToInGame"; }

int LoadingFEToInGame::Init()
{
    fn_80194858(2);
    return 1;
}

int LoadingFEToInGame::Shutdown()
{
    return 1;
}
