#include "game/Module.h"

extern "C" {
int fn_80226F9C(void);
int fn_80226FF0(void);
}

static void *sDependencies[] = { 0 };
Vec gVec;

ModuleDependency *Vec::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Vec::GetLinks() { return 0; }
const char *Vec::GetName() { return "Vec"; }

int Vec::Init()
{
    fn_80226F9C();
    return 1;
}

int Vec::Shutdown()
{
    fn_80226FF0();
    return 1;
}
