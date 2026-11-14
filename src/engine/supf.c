/* Sample unpacker (supf.c): plays a one-shot 16-bit PCM sample from memory through the mixer's
   conversion callback, padding with silence after its end. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackfgetframe(Node_80279D90 *node)
{
    return ((SndPcmUnpackFilter_t *)node)->m20;
}

int SFILTER_unpackf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndPcmUnpackFilter_t *decoder;
    unsigned int pos;
    int n;

    decoder = (SndPcmUnpackFilter_t *)node;
    pos = decoder->m20;
    if (pos >= decoder->m24) {
        return -1;
    }
    decoder->m20 = pos + count;
    if (decoder->m20 < decoder->m24) {
        if (decoder->m28 != 0) {
            lbl_803B4E34.m1E4(count, (short *)(decoder->m1C + (pos << 1)), b);
        }
    } else {
        n = decoder->m24 - pos;
        if (decoder->m28 != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->m1C + (pos << 1)), b);
        }
        memset(b + n, 0, (count - n) * 4);
    }
    return 1;
}

void SFILTER_unpackfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndPcmUnpackFilter_t *decoder;

    decoder = (SndPcmUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackf;
    decoder->m1C = params->m0;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = params->m18;
    params->m28 = SFILTER_unpackfgetframe;
    node->m4 = 0;
}

}
