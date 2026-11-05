#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "game/CameraHeader_8013F628.h"
#include "game/Object_80228224.h"

/* Common camera header; each camera type extends it. */
typedef struct Cam_t {
    CameraHeader_8013F628 mHeader;
    Object_80228224 *mpViewport;
} Cam_t;

int CamRLerp(int *pAngle, int *pSpeed, int dest, int maxSpeed, int accel);
int CamLerp(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel);
void CamConvertHdrToMatrix(void *pUnused, Cam_t *pCam);

#endif
