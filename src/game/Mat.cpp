#include "game/Module.h"

extern "C" {
int MatInit(int);
int MatShutdown(void);
int MatNewStack(int, int);
int MatDelStack(int);
}

static void *sDependencies[] = { 0 };
Mat gMat;

ModuleDependency *Mat::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Mat::GetLinks() { return 0; }
const char *Mat::GetName() { return "Mat"; }

int Mat::Init()
{
    MatInit(4);
    MatNewStack(3, 12);
    MatNewStack(1, 12);
    MatNewStack(2, 12);
    return 1;
}

int Mat::Shutdown()
{
    MatDelStack(2);
    MatDelStack(1);
    MatDelStack(3);
    MatShutdown();
    return 1;
}
