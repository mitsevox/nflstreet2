#ifndef ENGINE_ANIMEMOT_H
#define ENGINE_ANIMEMOT_H

#include "game/AnimFileFormat.h"
#include "engine/AnimStateAnimList.h"
#include "engine/animfileconfig.h"

/* State transition list filled by AnimFileGetTransList. */
typedef struct AnimStateTransList_t {
    unsigned short mCount;
    unsigned short mMax;
    unsigned short mState;
    unsigned char mUnknown6[2];
    AnimListEntry_t mEntries[8];
} AnimStateTransList_t;

/* Cached (slot, state index) pair of an object type and state. */
typedef struct AnimCacheStateInfo_t {
    short mUnknown0;
    short mUnknown2;
} AnimCacheStateInfo_t;


struct AnimFrameCache_t;
struct AnimFileBigInfo_t;

#ifdef __cplusplus
extern "C" {
#endif
void AnimFileSetCustomRelocateFunc(void (*pFunc)(AnimFileFormat_t *));
void AnimFileRelocate(AnimFileFormat_t *pFile);
unsigned short AnimFileGetObjectType(AnimFileFormat_t *pFile);
unsigned short AnimFileGetFileNum(AnimFileFormat_t *pFile);
AnimScript_t *AnimFileGetAnimation(AnimFileFormat_t *pFile, int anim);
int AnimFileGetStateRef(AnimFileFormat_t *pFile, int state);
void AnimFileGetStateAnimListByStateRef(AnimFileFormat_t *pFile, int slot, int stateRef, AnimStateAnimList_t *pList);
void AnimFileGetStateTransListByStateRef(AnimFileFormat_t *pFile, int slot, int stateRef, AnimStateTransList_t *pList);
void *AnimFileGetStateDataByStateRef(AnimFileFormat_t *pFile, int stateRef);
unsigned int AnimFileGetNumStates(AnimFileFormat_t *pFile);
unsigned short AnimFileGetStateIdByStateRef(AnimFileFormat_t *pFile, int stateRef);
void *AnimFileGetFrame(AnimFileFormat_t *pFile, int a, int b, unsigned int index);
int AnimFileStart(AnimFileConfig_t *pConfig);
void AnimFileBuildStateCache(int objectType);
void AnimFileGetStateAnimList(int objectType, int state, AnimStateAnimList_t *pList);
void AnimFileGetTransList(int objectType, int state, AnimStateTransList_t *pList);
int AnimFileGetSlotFromFileNum(int objectType, int fileNum);
unsigned short AnimFileGetTransitionStateFromObjType(int objectType);
AnimFileFormat_t *AnimFileGetPtrFromSlot(unsigned int slot);
struct AnimFrameCache_t *AnimFileGetFrameCacheFromSlot(unsigned int slot);
void AnimFileNewProcessBigFile(int slot, struct AnimFileBigInfo_t *pInfo);
void AnimFileProcessBigFile(int slot, struct AnimFileBigInfo_t *pInfo);
void AnimFileSetRelocateBigFileFunc(void (*pFunc)(int, struct AnimFileBigInfo_t *));
void AnimCacheInvalidate(unsigned int objectType);
AnimCacheStateInfo_t *AnimCacheGetStateInfo(unsigned int objectType, unsigned int state);
void *AnimFrameCacheGetFrame(AnimFileFormat_t *pFile, int a, int slot, unsigned int motion, char *pSource, int group);
#ifdef __cplusplus
}
#endif

#endif
