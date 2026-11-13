#ifndef ENGINE_ANIMEMOT_H
#define ENGINE_ANIMEMOT_H

#include "game/AnimFileFormat.h"
#include "engine/AnimStateAnimList.h"

/* State transition list filled by fn_801BBDCC. */
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

/* Buffer definition (stride 0xC) and init configuration read by fn_801BB2D8. */
typedef struct AnimFileBufferDef_t {
    int mSize;
    unsigned short mFlags;
    unsigned char mUnknown6[2];
    AnimFileFormat_t *mpData;
} AnimFileBufferDef_t;

typedef struct AnimFileConfig_t {
    void *mpArchive;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    unsigned short mUnknownC;
    unsigned char mUnknownE[2];
    int mUnknown10;
    AnimFileBufferDef_t *mpBuffers;
} AnimFileConfig_t;

struct AnimFrameCache_t;
struct Info_801BC0E8;

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
int fn_801BB2D8(AnimFileConfig_t *pConfig);
void fn_801BBB54(int objectType);
void fn_801BBC3C(int objectType, int state, AnimStateAnimList_t *pList);
void fn_801BBDCC(int objectType, int state, AnimStateTransList_t *pList);
int fn_801BBE5C(int objectType, int fileNum);
unsigned short fn_801BBF44(int objectType);
AnimFileFormat_t *fn_801BC084(unsigned int slot);
struct AnimFrameCache_t *fn_801BC0C0(unsigned int slot);
void fn_801BC0E8(int slot, struct Info_801BC0E8 *pInfo);
void fn_801BC57C(int slot, struct Info_801BC0E8 *pInfo);
void fn_801BC64C(void (*pFunc)(int, struct Info_801BC0E8 *));
void AnimCacheInvalidate(unsigned int objectType);
AnimCacheStateInfo_t *AnimCacheGetStateInfo(unsigned int objectType, unsigned int state);
void *AnimFrameCacheGetFrame(AnimFileFormat_t *pFile, int a, int slot, unsigned int motion, char *pSource, int group);
#ifdef __cplusplus
}
#endif

#endif
