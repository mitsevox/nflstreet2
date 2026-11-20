#ifndef ENGINE_SYNCSTATEGROUP_H
#define ENGINE_SYNCSTATEGROUP_H
#include "engine/list.h"
typedef struct SyncStateGroup_t {
    int mKey;
    int mState;
    int mNumHandles;
    int mHeapSize;
    int mHeap;
    DSList_t *mpHandles;
    void *mpCopy;
} SyncStateGroup_t;
#ifdef __cplusplus
extern "C" {
#endif
int SyncStateShutdown(void);
void SyncStateOpenGroup(SyncStateGroup_t *p);
void SyncStateSaveGroup(SyncStateGroup_t *p);
SyncStateGroup_t *SyncStateActivateGroup(SyncStateGroup_t *p);
#ifdef __cplusplus
}
#endif
#endif
