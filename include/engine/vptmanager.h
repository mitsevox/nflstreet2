#ifndef ENGINE_VPTMANAGER_H
#define ENGINE_VPTMANAGER_H

#include "game/Object_80228224.h"

#ifdef __cplusplus
extern "C" {
#endif

int _VptManagerCreateStack(void *p, int a);
int _VptManagerDestroyStack(void *p, int a);
void VptManagerInit(void);
void VptManagerRestoreCamera(void);
void VptManagerShutdown(void);
int VptManagerPushCamera(Object_80228224 *p, void *obj, int (*a)(Object_80228224 *, void *), int (*b)(Object_80228224 *, void *));
int VptManagerPopCamera(Object_80228224 *p, void *obj);
int VptManagerReplaceCamera(Object_80228224 *p, void *obj, void *other);
void *VptManagerGetCurrentCamera(Object_80228224 *p);
void VptManagerMarketCamInit(void);
int VptManagerIsMarketCamOn(void);
void VptManagerSetPassIcons(int value);
int VptManagerGetPassIcons(void);

#ifdef __cplusplus
}
#endif

#endif
