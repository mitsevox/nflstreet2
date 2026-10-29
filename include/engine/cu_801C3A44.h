#ifndef ENGINE_CU_801C3A44_H
#define ENGINE_CU_801C3A44_H

#ifdef __cplusplus
extern "C" {
#endif

void fn_801C3AD8(void *camera, int unused);
void fn_801C3B74(void *camera);
void fn_801C3B78(void *camera);
void fn_801C3C4C(void *viewport, void *camera);
void fn_801C3C6C(void *camera, void *target);
void fn_801C3C74(void *camera, int angleX, int angleZ);
void SnapFocusCameraToTarget(void *camera);

#ifdef __cplusplus
}
#endif

#endif
