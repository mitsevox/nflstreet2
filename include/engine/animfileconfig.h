#ifndef ENGINE_ANIMFILECONFIG_H
#define ENGINE_ANIMFILECONFIG_H

#include "game/AnimFileFormat.h"

/* Buffer definition (stride 0xC) and init configuration read by AnimFileStart. */
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

#ifdef __cplusplus
extern "C" {
#endif
int AnimFileStart(AnimFileConfig_t *pConfig);
#ifdef __cplusplus
}
#endif

#endif
