#ifndef ENGINE_FN_801EFD2C_H
#define ENGINE_FN_801EFD2C_H

#ifdef __cplusplus
extern "C" {
#endif
/* Starts an asynchronous read of entry index of an archive into pDest; the
   callback receives pContext as its fifth argument. */
int fn_801EFD2C(void *pArchive, int index, int heap, void *pDest, int priority, void (*pCallback)(), void *pContext);
#ifdef __cplusplus
}
#endif

#endif
