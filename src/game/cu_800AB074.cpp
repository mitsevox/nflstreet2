#include "game/Class_80297B90.h"
#include "game/PauseMenu.h"
#include "game/ScreenTransition.h"

extern "C" {
int ScreenTransIsActive(void);
void fn_800AD910(int a, float b);
void SndgAmbPostCue(int type);
void SndgMusicResume(void);
int SndgCrowdTriggerEvent(int index, int unknown);
}

extern "C" void fn_800AB074(Class_80297B90 *p, float dt)
{
    if (ScreenTransIsActive() == 0) {
        ScreenTransStart(5, 20, 0, 0);
        fn_800AD910(1, 0.0f);
        PauseClearBlocks();
        SndgAmbPostCue(3);
        SndgMusicResume();
        SndgCrowdTriggerEvent(3, 0);
    }
}
