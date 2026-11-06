#ifndef GAME_ANIMQUANTCONTEXT_H
#define GAME_ANIMQUANTCONTEXT_H
#include "game/AnimDequantize.h"
typedef struct AnimQuantContext {
    int mUnknown0;
    struct AnimQuantTables mUnknown4;
    struct AnimQuantTables mUnknownC;
    unsigned char *mpUnknown14;
} AnimQuantContext;
#ifdef __cplusplus
extern "C" {
#endif
void AnimMirrorRotations(short *pOut, short *pIn, unsigned int count);
void AnimMirrorVector(int *pOut, short *pIn, int index, AnimQuantContext *pContext);
#ifdef __cplusplus
}
#endif
#endif
