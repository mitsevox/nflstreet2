/* Sample unpacker (supmutf.c): plays a one-shot MT-compressed sample through an MT decoder, padding
   with silence after its end. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackgetframemtf(Node_80279D90 *node)
{
    return ((SndMtSampleUnpackFilter_t *)node)->m20;
}

int SFILTER_unpackmtf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndMtSampleUnpackFilter_t *decoder;
    int n;

    decoder = (SndMtSampleUnpackFilter_t *)node;
    if (decoder->m20 >= decoder->m1C) {
        return -1;
    }
    n = decoder->m28->Decode(&b, count);
    decoder->m20 += n;
    b += n;
    if (n < count) {
        count -= n;
        memset(b, 0, count * 4);
    }
    return 1;
}

void SFILTER_unpackmtfrestore(Node_80279D90 *node)
{
    SndMtSampleUnpackFilter_t *decoder;

    decoder = (SndMtSampleUnpackFilter_t *)node;
    if (decoder->m28 != 0) {
        delete decoder->m28;
    }
}

void SFILTER_unpackmtfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndMtSampleUnpackFilter_t *decoder;
    Snd::MTFSTATE format;

    decoder = (SndMtSampleUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackmtf;
    decoder->m1C = params->mC;
    decoder->m20 = 0;
    decoder->m24 = params->m24;
    params->m28 = SFILTER_unpackgetframemtf;
    node->m4 = SFILTER_unpackmtfrestore;
    decoder->m28 = new Snd::CMTBLKDecf;
    format = decoder->m28->GetState();
    format.m8 = 1;
    decoder->m28->SetState(&format, 0);
    if (decoder->m24 <= 2) {
        decoder->m28->SetCodecVersion(0);
    } else {
        decoder->m28->SetCodecVersion(1);
    }
    decoder->m28->Feed((unsigned char *)params->m0, decoder->m1C * 4, decoder->m1C);
}

}
