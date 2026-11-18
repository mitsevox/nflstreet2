#include "game/Module.h"
#include "game/MemPoolDesc.h"

extern "C" {

int ResInit(int);
void ResQuickloadInit(int);
void ResTrackInitSize(int, int);
void ResTrackSetTideCompatible(int);
void ResTrackEnable(int);
void ResQuickloadShutdown(void);
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
    ResQuickloadInit(1);
    if (MemPoolGetDesc(8)->mUnknown10 != 0) {
        ResTrackInitSize(8, 0x100000);
        ResTrackSetTideCompatible(0);
        ResTrackEnable(1);
    }
    return 1;
}

int Res::Shutdown()
{
    ResQuickloadShutdown();
    ResShutdown();
    return 1;
}
