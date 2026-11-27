#include "game/GameState.h"
#include "game/GameModules.h"

extern "C" {

void AnmsInit(void);
void AnmsLoad(void *);
void AnmsUnload(void);
void AnmsReset(void);
}

static ModuleDependency sDependencies[] = { &gGameState, &gAnimData, 0 };
static ModuleDependency sLinks[] = { &gCelebration, 0 };
AnmsCelebration gAnmsCelebration;

ModuleDependency *AnmsCelebration::GetDependencies() { return sDependencies; }
ModuleDependency *AnmsCelebration::GetLinks() { return sLinks; }
const char *AnmsCelebration::GetName() { return "AnmsCelebration"; }

int AnmsCelebration::Init()
{
    AnmsInit();
    AnmsLoad(gAnimData.GetArchive());
    return 1;
}

int AnmsCelebration::Shutdown()
{
    AnmsUnload();
    AnmsReset();
    return 1;
}
