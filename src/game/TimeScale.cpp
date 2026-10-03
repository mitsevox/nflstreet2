#include "game/TimeScale.h"

extern "C" {
extern float lbl_803EA2C4;

void fn_8006CCA8(float value);
}

static float sCurrent = 1.0f;
static float sTarget = 1.0f;
static float sStep = 0.0f;

void TimeScaleReset()
{
    lbl_803EA2C4 = 1.0f;
    fn_8006CCA8(1.0f);
    sCurrent = 1.0f;
    sTarget = 1.0f;
    sStep = 0.0f;
}

/* Moves the current scale one step towards the target and publishes it. */
void TimeScaleUpdate()
{
    if (sStep != 0.0f) {
        sCurrent += sStep;
        if ((sStep > 0.0f && sCurrent >= sTarget) || (sStep < 0.0f && sCurrent <= sTarget)) {
            sCurrent = sTarget;
            sStep = 0.0f;
        }
        lbl_803EA2C4 = sCurrent;
        fn_8006CCA8(sCurrent);
    }
}

void TimeScaleSet(float target)
{
    TimeScaleRamp(target, 0.0f);
}

void TimeScaleRamp(float target, float divisor)
{
    if (divisor == 0.0f || sCurrent == target) {
        /* A non-zero step makes the next update publish the new value. */
        sCurrent = target;
        sTarget = target;
        sStep = 1.0f;
        return;
    }
    sStep = target / divisor;
    sTarget = target;
    if ((target < sCurrent && sStep > 0.0f) || (target > sCurrent && sStep < 0.0f)) {
        sStep = -sStep;
    }
}
