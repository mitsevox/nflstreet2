#include "game/GameState.h"

extern "C" {
void SyncTimeInit(int);
void SyncTimeShutdown(void);
}

static ModuleDependency sDependencies[] = { &gGameState, 0 };
Timg gTimg;

ModuleDependency *Timg::GetDependencies() { return sDependencies; }
ModuleDependency *Timg::GetLinks() { return 0; }
const char *Timg::GetName() { return "Timg"; }

int Timg::Init()
{
    SyncTimeInit(1);
    return 1;
}

int Timg::Shutdown()
{
    SyncTimeShutdown();
    return 1;
}
