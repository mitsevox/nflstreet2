#ifndef ENGINE_CU_801C33E8_H
#define ENGINE_CU_801C33E8_H

#include "game/CameraHeader_8013F628.h"
#include "game/Object_80228224.h"

/* Common camera header; each camera type extends it. */
typedef struct Cam_801C33E8 {
    CameraHeader_8013F628 mHeader;
    Object_80228224 *mpViewport;
} Cam_801C33E8;

int fn_801C370C(int *pAngle, int *pSpeed, int dest, int maxSpeed, int accel);
int fn_801C384C(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel);
void fn_801C3918(void *pUnused, Cam_801C33E8 *pCam);

#endif
