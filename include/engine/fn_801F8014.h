#ifndef ENGINE_FN_801F8014_H
#define ENGINE_FN_801F8014_H

/* 32-byte lock passed to fn_801F7FA8, fn_801F8014, fn_801F809C and
   fn_801F80D0; fn_801F8014 takes it and fn_801F809C releases it. */
typedef struct Lock_801F8014 {
    int mUnknown0[8];
} Lock_801F8014;

#ifdef __cplusplus
extern "C" {
#endif
void fn_801F7FA8(Lock_801F8014 *pLock);
void fn_801F8014(Lock_801F8014 *pLock);
void fn_801F809C(Lock_801F8014 *pLock);
void fn_801F80D0(Lock_801F8014 *pLock);
#ifdef __cplusplus
}
#endif

#endif
