/* Mirrored animation frames: copies a pose's rotations and vectors through
   the left/right bone mirror table, negating the mirrored axes. */
#include "game/AnimQuantContext.h"

static int _AnimMirror_aiBoneMap[30] = {
    0, 5, 6, 7, 8, 1, 2, 3, 4, 9, 10, 11, 12, 13, 20,
    21, 22, 23, 24, 25, 14, 15, 16, 17, 18, 19, 0, 0, 0, 0,
};

extern "C" {

void AnimMirrorRotations(short *pOut, short *pIn, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i) {
        pOut[0] = pIn[_AnimMirror_aiBoneMap[i] * 3];
        pOut[1] = -pIn[_AnimMirror_aiBoneMap[i] * 3 + 1];
        pOut[2] = -pIn[_AnimMirror_aiBoneMap[i] * 3 + 2];
        pOut += 3;
    }
}

void AnimMirrorVector(int *pOut, short *pIn, int index, AnimQuantContext *pContext)
{
    int mapped = _AnimMirror_aiBoneMap[index];
    if (pContext) {
        pOut[0] = AnimDequantize(pIn[mapped * 3], mapped, 0, pContext, &pContext->mUnknownC) << 8;
        pOut[1] = AnimDequantize(pIn[mapped * 3 + 1], mapped, 1, pContext, &pContext->mUnknownC) << 8;
        pOut[2] = AnimDequantize(pIn[mapped * 3 + 2], mapped, 2, pContext, &pContext->mUnknownC) << 8;
    } else {
        pOut[0] = pIn[index * 3] << 8;
        pOut[1] = -pIn[index * 3 + 1] << 8;
        pOut[2] = -pIn[index * 3 + 2] << 8;
    }
}

}
