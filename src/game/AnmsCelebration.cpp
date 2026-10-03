#include "game/GameState.h"
#include "game/ModuleGroup_80033A5C.h"

extern "C" {

void fn_800925F0(void);
void fn_80093684(void *);
void fn_800937CC(void);
void fn_800926A8(void);
}

static ModuleDependency sDependencies[] = { &gGameState, &gAnimData, 0 };
static ModuleDependency sLinks[] = { &gCelebration, 0 };
AnmsCelebration gAnmsCelebration;

ModuleDependency *AnmsCelebration::GetDependencies() { return sDependencies; }
ModuleDependency *AnmsCelebration::GetLinks() { return sLinks; }
const char *AnmsCelebration::GetName() { return "AnmsCelebration"; }

int AnmsCelebration::Init()
{
    fn_800925F0();
    fn_80093684(gAnimData.fn_80033AF8());
    return 1;
}

int AnmsCelebration::Shutdown()
{
    fn_800937CC();
    fn_800926A8();
    return 1;
}
