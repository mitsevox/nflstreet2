#include "game/GameState.h"
#include "game/GameModules.h"
#include "game/InGameModules.h"

extern "C" {
void CelebrationBlocksInit(void *);
void fn_8009B7E0(void);
}

static ModuleDependency sDependencies[] = { &gGameState, &gAnimData, &gAnimScriptMan, 0 };
static ModuleDependency sLinks[] = { &gAnmsCelebration, 0 };
Celebration gCelebration;

ModuleDependency *Celebration::GetDependencies() { return sDependencies; }
ModuleDependency *Celebration::GetLinks() { return sLinks; }
const char *Celebration::GetName() { return "Celebration"; }

int Celebration::Init()
{
    CelebrationBlocksInit(gAnimData.GetArchive());
    return 1;
}

int Celebration::Shutdown()
{
    fn_8009B7E0();
    return 1;
}
