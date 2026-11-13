#include "game/SysModules.h"

extern "C" {
void LoadingBegin(int);
}

static ModuleDependency sDependencies[] = { &gLoading, &gGRender, 0 };
LoadingFEToInGame gLoadingFEToInGame;

ModuleDependency *LoadingFEToInGame::GetDependencies() { return sDependencies; }
ModuleDependency *LoadingFEToInGame::GetLinks() { return 0; }
const char *LoadingFEToInGame::GetName() { return "LoadingFEToInGame"; }

int LoadingFEToInGame::Init()
{
    LoadingBegin(2);
    return 1;
}

int LoadingFEToInGame::Shutdown()
{
    return 1;
}
