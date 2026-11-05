/* Mirrored animation frames: copies a pose's rotations and vectors through
   the left/right bone mirror table, negating the mirrored axes. */
#include "game/AnimQuantContext.h"

extern "C" {

extern int lbl_802F2684[];

void AnimMirrorRotations(short *pOut, short *pIn, unsigned int count)
{
    for (unsigned int i = 0; i < count; ++i) {
        pOut[0] = pIn[lbl_802F2684[i] * 3];
        pOut[1] = -pIn[lbl_802F2684[i] * 3 + 1];
        pOut[2] = -pIn[lbl_802F2684[i] * 3 + 2];
        pOut += 3;
    }
}

void AnimMirrorVector(int *pOut, short *pIn, int index, AnimQuantContext *pContext)
{
    int mapped = lbl_802F2684[index];
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
