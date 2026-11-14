#include "game/Module.h"

extern "C" {
int VecInit(void);
int VecShutdown(void);
}

static void *sDependencies[] = { 0 };
Vec gVec;

ModuleDependency *Vec::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Vec::GetLinks() { return 0; }
const char *Vec::GetName() { return "Vec"; }

int Vec::Init()
{
    VecInit();
    return 1;
}

int Vec::Shutdown()
{
    VecShutdown();
    return 1;
}
