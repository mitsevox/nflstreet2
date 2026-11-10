#include "game/Module.h"
#include "game/MemPoolDesc.h"

extern "C" {

int ResInit(int);
void fn_801F2BAC(int);
void ResTrackInitSize(int, int);
void ResTrackSetTideCompatible(int);
void ResTrackEnable(int);
void fn_801F2BF0(void);
int ResShutdown(void);
}

static ModuleDependency sDependencies[] = { &gSys, &gFileIO, 0 };
Res gRes;

ModuleDependency *Res::GetDependencies() { return sDependencies; }
ModuleDependency *Res::GetLinks() { return 0; }
const char *Res::GetName() { return "Res"; }

int Res::Init()
{
    ResInit(0x40);
    fn_801F2BAC(1);
    if (MemPoolGetDesc(8)->mUnknown10 != 0) {
        ResTrackInitSize(8, 0x100000);
        ResTrackSetTideCompatible(0);
        ResTrackEnable(1);
    }
    return 1;
}

int Res::Shutdown()
{
    fn_801F2BF0();
    ResShutdown();
    return 1;
}
