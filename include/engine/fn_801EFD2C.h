#ifndef ENGINE_FN_801EFD2C_H
#define ENGINE_FN_801EFD2C_H

#ifdef __cplusplus
extern "C" {
#endif
/* Starts an asynchronous read of entry index of an archive into pDest; arg
   is passed through (callers pass 100 or the loader +0x24); the
   callback receives pContext as its fifth argument. */
int fn_801EFD2C(void *pArchive, int index, int heap, void *pDest, int arg, void (*pCallback)(), void *pContext);
#ifdef __cplusplus
}
#endif

#endif
