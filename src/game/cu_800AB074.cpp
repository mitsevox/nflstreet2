#include "game/Class_80297B90.h"
#include "game/PauseMenu.h"
#include "game/fn_80195EFC.h"

extern "C" {
int fn_80196278(void);
void fn_800AD910(int a, float b);
void SndgAmbPostCue(int type);
void fn_80072F04(void);
int SndgCrowdTriggerEvent(int index, int unknown);
}

extern "C" void fn_800AB074(Class_80297B90 *p, float dt)
{
    if (fn_80196278() == 0) {
        fn_80195EFC(5, 20, 0, 0);
        fn_800AD910(1, 0.0f);
        PauseClearBlocks();
        SndgAmbPostCue(3);
        fn_80072F04();
        SndgCrowdTriggerEvent(3, 0);
    }
}
