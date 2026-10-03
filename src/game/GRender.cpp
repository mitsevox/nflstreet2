#include "game/Module.h"

extern "C" {
void fn_801CE910(void);
void fn_802348CC(int);
void fn_80234908(void);
}

static void *sDependencies[] = { 0 };
GRender gGRender;

ModuleDependency *GRender::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *GRender::GetLinks() { return 0; }
const char *GRender::GetName() { return "GRender"; }

int GRender::Init()
{
    fn_802348CC(0);
    return 1;
}

int GRender::Shutdown()
{
    fn_801CE910();
    fn_80234908();
    return 1;
}
