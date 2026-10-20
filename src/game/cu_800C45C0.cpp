#include "game/Step_800C4460.h"

extern "C" {
void fn_800C4460(Sequence_800C4460 *p);
void fn_800C44E0(Sequence_800C4460 *p);
void fn_800C4568(Sequence_800C4460 *p);
}

extern "C" void fn_800C45C0(Sequence_800C4460 *p, float dt)
{
    if (p->mUnknown100 != 0) {
        Step_800C4460 *pStep = &p->mSteps[p->mUnknown101];

        if (pStep->mUnknownC <= 0.0f) {
            fn_800C44E0(p);
        } else {
            pStep->mUnknownC -= dt;
            if (pStep->mUnknownC > 0.0f) {
                fn_800C44E0(p);
            } else {
                fn_800C4568(p);
                p->mUnknown101++;
                fn_800C4460(p);
            }
        }
    }
}

