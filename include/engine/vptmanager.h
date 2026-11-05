#ifndef ENGINE_VPTMANAGER_H
#define ENGINE_VPTMANAGER_H

#include "engine/viewporttypes.h"

#ifdef __cplusplus
extern "C" {
#endif

int fn_8002AE90(void *p, int a);
int fn_8002AEE4(void *p, int a);
void fn_8002B1E4(void);
void fn_8002B270(void);
void fn_8002B2D0(void);
int fn_8002B2D4(Viewport_t *p, void *obj, int (*a)(Viewport_t *, void *), int (*b)(Viewport_t *, void *));
int fn_8002B3DC(Viewport_t *p, void *obj);
int fn_8002B494(Viewport_t *p, void *obj, void *other);
void *fn_8002B550(Viewport_t *p);
void fn_8002B598(void);
int fn_8002B59C(void);
void fn_8002B5A4(int value);
int fn_8002B5A8(void);

#ifdef __cplusplus
}
#endif

#endif
