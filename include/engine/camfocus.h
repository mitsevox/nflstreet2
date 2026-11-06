#ifndef ENGINE_CAMFOCUS_H
#define ENGINE_CAMFOCUS_H

#ifdef __cplusplus
extern "C" {
#endif

void CamFocusAdd(void *camera, int unused);
void CamFocusDelete(void *camera);
void CamFocusProcess(void *camera);
void CamFocusUpdate(void *viewport, void *camera);
void CamFocusSetTarget(void *camera, void *target);
void CamFocusMoveAngle(void *camera, int angleX, int angleZ);
void CamFocusWarpToDest(void *camera);

#ifdef __cplusplus
}
#endif

#endif
