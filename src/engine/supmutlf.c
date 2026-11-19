/* Sample unpacker (supmutlf.c): plays a looped MT-compressed sample, restarting the MT decoder at
   the loop start. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackgetframemtlf(Node_80279D90 *node)
{
    return ((SndMtLoopUnpackFilter_t *)node)->m20;
}

int SFILTER_unpackmtlf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndMtLoopUnpackFilter_t *decoder;
    Snd::MTFSTATE format;
    int n;

    decoder = (SndMtLoopUnpackFilter_t *)node;
    while (count > 0) {
        n = decoder->m1C->Decode(&b, count);
        b += n;
        decoder->m20 += n;
        count -= n;
        if (n < count) {
            decoder->m20 = decoder->m24;
            format.m4 = 0;
            format.m0 = 0;
            format.m8 = 1;
            decoder->m1C->SetState(&format, 0);
            decoder->m1C->Feed(decoder->m2C, (decoder->m28 - decoder->m24 + 1) * 4,
                        decoder->m28 - decoder->m24 + 1);
        }
    }
    return 1;
}

void SFILTER_unpackmtlfrestore(Node_80279D90 *node)
{
    SndMtLoopUnpackFilter_t *decoder;

    decoder = (SndMtLoopUnpackFilter_t *)node;
    if (decoder->m1C != 0) {
        delete decoder->m1C;
    }
}

void SFILTER_unpackmtlfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndMtLoopUnpackFilter_t *decoder;
    Snd::MTFSTATE format;

    decoder = (SndMtLoopUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackmtlf;
    node->m4 = SFILTER_unpackmtlfrestore;
    decoder->m2C = (unsigned char *)params->m4;
    decoder->m20 = 0;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m1C = new Snd::CMTBLKDecf;
    format = decoder->m1C->GetState();
    format.m8 = 1;
    decoder->m1C->SetState(&format, 0);
    decoder->m1C->Feed((unsigned char *)params->m0, decoder->m24 * 4, decoder->m24);
    params->m28 = SFILTER_unpackgetframemtlf;
}

}
