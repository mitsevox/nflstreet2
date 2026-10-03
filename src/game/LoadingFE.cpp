#include "game/ModuleGroup_8008CC74.h"

extern "C" {
int fn_8007F828(int);
void fn_8013CF98(void);
void fn_80194858(int);
void fn_80194AEC(int);
void fn_801C3A3C(float);
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
        fn_80194858(1);
    } else {
        if (fn_8007F828(6) == 1 || fn_801CEB4C() == 1) {
            fn_801C3A3C(4.0f / 3.0f);
        } else {
            fn_8013CF98();
        }
        fn_80194858(4);
    }
    return 1;
}

int LoadingFE::Shutdown()
{
    fn_80194AEC(1);
    return 1;
}
