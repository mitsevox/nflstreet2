#ifndef ENGINE_SYNCSTATEGROUP_H
#define ENGINE_SYNCSTATEGROUP_H
#include "engine/list.h"
typedef struct SyncStateGroup_t {
    int mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    int mUnknown16;
    DSList_t *mpUnknown20;
    void *mpUnknown24;
} SyncStateGroup_t;
#ifdef __cplusplus
extern "C" {
#endif
int SyncStateShutdown(void);
void SyncStateOpenGroup(SyncStateGroup_t *p);
void SyncStateSaveGroup(SyncStateGroup_t *p);
SyncStateGroup_t *SyncStateEndGroup(SyncStateGroup_t *p);
#ifdef __cplusplus
}
#endif
#endif
