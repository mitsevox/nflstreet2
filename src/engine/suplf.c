/* Sample unpacker (suplf.c): plays a looped 16-bit PCM sample from memory, wrapping from the loop end
   to the loop start. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpacklfgetframe(Node_80279D90 *node)
{
    return ((SndPcmLoopUnpackFilter_t *)node)->m20;
}

int SFILTER_unpacklf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndPcmLoopUnpackFilter_t *decoder;
    int n;

    decoder = (SndPcmLoopUnpackFilter_t *)node;
    while (count > 0) {
        n = decoder->m28 - decoder->m20 + 1;
        if (count < n) {
            n = count;
        }
        if (decoder->m2C != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->m1C + (decoder->m20 << 1)), b);
        }
        b += n;
        decoder->m20 += n;
        count -= n;
        if (decoder->m20 > decoder->m28) {
            decoder->m20 = decoder->m24;
        }
    }
    return 1;
}

void SFILTER_unpacklfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndPcmLoopUnpackFilter_t *decoder;

    decoder = (SndPcmLoopUnpackFilter_t *)node;
    node->m0 = SFILTER_unpacklf;
    decoder->m1C = params->m0;
    decoder->m20 = 0;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m2C = params->m18;
    params->m28 = SFILTER_unpacklfgetframe;
}

}
