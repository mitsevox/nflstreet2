#ifndef ENGINE_CU_801BA818_H
#define ENGINE_CU_801BA818_H

#include "game/AnimFileFormat.h"

typedef struct Entry_801BAB88 {
    unsigned short mUnknown0;
    unsigned short mUnknown2;
    void *mpUnknown4;
} Entry_801BAB88;

/* State animation list filled by fn_801BBC3C. */
typedef struct List_801BAB88 {
    unsigned short mCount;
    unsigned short mMax;
    Entry_801BAB88 mEntries[380];
} List_801BAB88;

/* State transition list filled by fn_801BBDCC. */
typedef struct List_801BAC1C {
    unsigned short mCount;
    unsigned short mMax;
    unsigned short mState;
    unsigned char mUnknown6[2];
    Entry_801BAB88 mEntries[8];
} List_801BAC1C;

/* Cached (slot, state index) pair of an object type and state. */
typedef struct Pair_801BF7BC {
    short mUnknown0;
    short mUnknown2;
} Pair_801BF7BC;

/* Buffer definition (stride 0xC) and init configuration read by fn_801BB2D8. */
typedef struct Def_801BB2D8 {
    int mSize;
    unsigned short mFlags;
    unsigned char mUnknown6[2];
    AnimFileFormat_t *mpData;
} Def_801BB2D8;

typedef struct Config_801BB2D8 {
    void *mpArchive;
    int mUnknown4;
    unsigned short mUnknown8;
    unsigned short mUnknownA;
    unsigned short mUnknownC;
    unsigned char mUnknownE[2];
    int mUnknown10;
    Def_801BB2D8 *mpBuffers;
} Config_801BB2D8;

struct Cache_801BFCC4;
struct Info_801BC0E8;

#ifdef __cplusplus
extern "C" {
#endif
void fn_801BA848(void (*pFunc)(AnimFileFormat_t *));
void fn_801BA850(AnimFileFormat_t *pFile);
unsigned short fn_801BAB24(AnimFileFormat_t *pFile);
unsigned short fn_801BAB2C(AnimFileFormat_t *pFile);
Anim_801BAB34 *fn_801BAB34(AnimFileFormat_t *pFile, int anim);
int fn_801BAB48(AnimFileFormat_t *pFile, int state);
void fn_801BAB88(AnimFileFormat_t *pFile, int slot, int stateRef, List_801BAB88 *pList);
void fn_801BAC1C(AnimFileFormat_t *pFile, int slot, int stateRef, List_801BAC1C *pList);
void *fn_801BAC9C(AnimFileFormat_t *pFile, int stateRef);
unsigned int fn_801BACB0(AnimFileFormat_t *pFile);
unsigned short fn_801BACBC(AnimFileFormat_t *pFile, int stateRef);
void *fn_801BAD70(AnimFileFormat_t *pFile, int a, int b, unsigned int index);
int fn_801BB2D8(Config_801BB2D8 *pConfig);
void fn_801BBB54(int objectType);
void fn_801BBC3C(int objectType, int state, List_801BAB88 *pList);
void fn_801BBDCC(int objectType, int state, List_801BAC1C *pList);
int fn_801BBE5C(int objectType, int fileNum);
unsigned short fn_801BBF44(int objectType);
AnimFileFormat_t *fn_801BC084(unsigned int slot);
struct Cache_801BFCC4 *fn_801BC0C0(unsigned int slot);
void fn_801BC0E8(int slot, struct Info_801BC0E8 *pInfo);
void fn_801BC57C(int slot, struct Info_801BC0E8 *pInfo);
void fn_801BC64C(void (*pFunc)(int, struct Info_801BC0E8 *));
void fn_801BF7BC(unsigned int objectType);
Pair_801BF7BC *fn_801BF870(unsigned int objectType, unsigned int state);
void *fn_801BFD8C(AnimFileFormat_t *pFile, int a, int slot, unsigned int motion, char *pSource, int group);
#ifdef __cplusplus
}
#endif

#endif
