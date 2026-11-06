#ifndef ENGINE_VPTMANAGER_H
#define ENGINE_VPTMANAGER_H

#include "engine/viewporttypes.h"

#ifdef __cplusplus
extern "C" {
#endif

int _VptManagerCreateStack(void *p, int a);
int _VptManagerDestroyStack(void *p, int a);
void VptManagerInit(void);
void VptManagerRestoreCamera(void);
void VptManagerShutdown(void);
int VptManagerPushCamera(Viewport_t *p, void *obj, int (*a)(Viewport_t *, void *), int (*b)(Viewport_t *, void *));
int VptManagerPopCamera(Viewport_t *p, void *obj);
int VptManagerReplaceCamera(Viewport_t *p, void *obj, void *other);
void *VptManagerGetCurrentCamera(Viewport_t *p);
void VptManagerMarketCamInit(void);
int VptManagerIsMarketCamOn(void);
void VptManagerSetPassIcons(int value);
int VptManagerGetPassIcons(void);

#ifdef __cplusplus
}
#endif

#endif
