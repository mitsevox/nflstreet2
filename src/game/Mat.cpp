#include "game/Module.h"

extern "C" {
int fn_801D0134(int);
int fn_801D01EC(void);
int fn_801D0290(int, int);
int fn_801D0310(int);
}

static void *sDependencies[] = { 0 };
Mat gMat;

ModuleDependency *Mat::GetDependencies() { return (ModuleDependency *)sDependencies; }
ModuleDependency *Mat::GetLinks() { return 0; }
const char *Mat::GetName() { return "Mat"; }

int Mat::Init()
{
    fn_801D0134(4);
    fn_801D0290(3, 12);
    fn_801D0290(1, 12);
    fn_801D0290(2, 12);
    return 1;
}

int Mat::Shutdown()
{
    fn_801D0310(2);
    fn_801D0310(1);
    fn_801D0310(3);
    fn_801D01EC();
    return 1;
}
