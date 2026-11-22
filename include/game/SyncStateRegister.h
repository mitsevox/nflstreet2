#ifndef GAME_SYNCSTATEREGISTER_H
#define GAME_SYNCSTATEREGISTER_H

typedef int (*SyncStateFn_t)(void *p, int value);
typedef int (*SyncStateCompareFn_t)(void *p, void *q);
typedef int (*SyncStateLoadFn_t)(void *p, void *pBuffer);
typedef int (*SyncStateSizeFn_t)(void *p);
typedef int (*SyncStateSaveFn_t)(void *p, void *pBuffer);

#ifdef __cplusplus
extern "C" {
#endif
void *SyncStateRegister(int a, void **ppData, int size, int b, unsigned int id);
void SyncStateCommit(void *pHandle);
void SyncStateSetCallbacks(void *pHandle, SyncStateFn_t pCallback10, SyncStateFn_t pCallback14, SyncStateFn_t pCallback18, SyncStateCompareFn_t pCallback1C);
void SyncStateSetSaveCallbacks(void *pHandle, SyncStateSaveFn_t pCallback28, SyncStateSizeFn_t pCallback24, SyncStateLoadFn_t pCallback20);
#ifdef __cplusplus
}
#endif

#endif
