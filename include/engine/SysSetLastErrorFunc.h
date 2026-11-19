#ifndef ENGINE_SYSSETLASTERRORFUNC_H
#define ENGINE_SYSSETLASTERRORFUNC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Records an error code (0 for success) and returns it (mr r3,r31 at 0x801F7C70). */
int SysSetLastErrorFunc(int err);
/* Returns the current error code. */
int SysGetLastError(void);
#ifdef __cplusplus
}
#endif

#endif
