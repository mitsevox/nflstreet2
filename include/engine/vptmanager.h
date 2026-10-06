#ifndef ENGINE_VPTMANAGER_H
#define ENGINE_VPTMANAGER_H

#include "game/Object_80228224.h"

#ifdef __cplusplus
extern "C" {
#endif

int fn_8002AE90(void *p, int a);
int fn_8002AEE4(void *p, int a);
void fn_8002B1E4(void);
void fn_8002B270(void);
void fn_8002B2D0(void);
int fn_8002B2D4(Object_80228224 *p, void *obj, int (*a)(Object_80228224 *, void *), int (*b)(Object_80228224 *, void *));
int fn_8002B3DC(Object_80228224 *p, void *obj);
int fn_8002B494(Object_80228224 *p, void *obj, void *other);
void *fn_8002B550(Object_80228224 *p);
void fn_8002B598(void);
int fn_8002B59C(void);
void fn_8002B5A4(int value);
int fn_8002B5A8(void);

#ifdef __cplusplus
}
#endif

#endif
