#include "game/fn_8007F828.h"
#include "game/SysModules.h"

extern "C" {
void fn_8013CF98(void);
void LoadingBegin(int);
void LoadingEnd(int);
void CamSetDefaultAspect(float);
int fn_801CEB4C(void);
}

static ModuleDependency sDependencies[] = { &gLoading, &gGRender, 0 };
LoadingFE gLoadingFE;
static unsigned char sFirstInit = 1;

ModuleDependency *LoadingFE::GetDependencies() { return sDependencies; }
ModuleDependency *LoadingFE::GetLinks() { return 0; }
const char *LoadingFE::GetName() { return "LoadingFE"; }

int LoadingFE::Init()
{
    if (sFirstInit) {
        sFirstInit = 0;
        LoadingBegin(1);
    } else {
        if (fn_8007F828(6) == 1 || fn_801CEB4C() == 1) {
            CamSetDefaultAspect(4.0f / 3.0f);
        } else {
            fn_8013CF98();
        }
        LoadingBegin(4);
    }
    return 1;
}

int LoadingFE::Shutdown()
{
    LoadingEnd(1);
    return 1;
}
