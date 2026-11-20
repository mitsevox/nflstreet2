/* Vector library front end: the module init/shutdown guard and the angle between two 3D vectors. */

#include "engine/SysSetLastErrorFunc.h"

extern int fn_801CFD78(float x);
float Vec3InvMagnitude(float *p);
float Vec3DotProduct(float *pA, float *pB);

static unsigned char _Vec_ModuleActive = 0;

int VecInit(void)
{
    int err = 0;

    if (_Vec_ModuleActive == 0) {
        _Vec_ModuleActive = 1;
    } else {
        err = 0x60001;
    }
    SysSetLastErrorFunc(err);
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
    SysSetLastErrorFunc(err);
    return err;
}

int Vec3GetAngle(float *pA, float *pB)
{
    return fn_801CFD78(Vec3DotProduct(pA, pB) * Vec3InvMagnitude(pA) * Vec3InvMagnitude(pB));
}
