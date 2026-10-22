#ifndef ENGINE_FN_801F7BD4_H
#define ENGINE_FN_801F7BD4_H

#ifdef __cplusplus
extern "C" {
#endif
/* Records an error code (0 for success) and returns it (mr r3,r31 at 0x801F7C70). */
int fn_801F7BD4(int err);
/* Returns the current error code. */
int fn_801F7C88(void);
#ifdef __cplusplus
}
#endif

#endif
