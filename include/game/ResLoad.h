#ifndef GAME_RESLOAD_H
#define GAME_RESLOAD_H

/* Resource entry accessors using the game's opaque handle and address-word API. */
#ifdef __cplusplus
extern "C" {
#endif
int ResLoad(void *pData, int index, int a);
int ResUnLoad(void *pData, int index);
int ResIsLoaded(void *pData, int index);
int ResIsLoading(void *pData, int index);
#ifdef __cplusplus
}
#endif

#endif
