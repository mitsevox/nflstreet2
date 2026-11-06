#ifndef ENGINE_CAMERA_H
#define ENGINE_CAMERA_H

#include "game/CamHdr.h"
#include "engine/viewporttypes.h"

/* Common camera header; each camera type extends it. */
typedef struct Cam_t {
    CamHdr_t mHeader;
    Viewport_t *mpViewport;
} Cam_t;

int CamRLerp(int *pAngle, int *pSpeed, int dest, int maxSpeed, int accel);
int CamLerp(float *pValue, float *pSpeed, float dest, float maxSpeed, float accel);
void CamConvertHdrToMatrix(void *pUnused, Cam_t *pCam);

#endif
