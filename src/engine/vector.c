/* Vector library front end: the module init/shutdown guard and the angle between two 3D vectors. */

#include "engine/fn_801F7BD4.h"

extern int fn_801CFD78(float x);
float fn_8022716C(float *p);
float fn_80227704(float *pA, float *pB);

static unsigned char _Vec_ModuleActive = 0;

int VecInit(void)
{
    int err = 0;

    if (_Vec_ModuleActive == 0) {
        _Vec_ModuleActive = 1;
    } else {
        err = 0x60001;
    }
    fn_801F7BD4(err);
    return err;
}

int VecShutdown(void)
{
    int err = 0;

    if (_Vec_ModuleActive) {
        _Vec_ModuleActive = 0;
    } else {
        err = 0x60002;
    }
    fn_801F7BD4(err);
    return err;
}

int Vec3GetAngle(float *pA, float *pB)
{
    return fn_801CFD78(fn_80227704(pA, pB) * fn_8022716C(pA) * fn_8022716C(pB));
}
