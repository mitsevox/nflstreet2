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
    n = CodecReadSamples(decoder->m28, &b, count);
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
        fn_8027C04C(decoder->m28);
    }
}

void SFILTER_unpackmtfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndMtSampleUnpackFilter_t *decoder;
    Format_8027D284 format;

    decoder = (SndMtSampleUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackmtf;
    decoder->m1C = params->mC;
    decoder->m20 = 0;
    decoder->m24 = params->m24;
    params->m28 = SFILTER_unpackgetframemtf;
    node->m4 = SFILTER_unpackmtfrestore;
    decoder->m28 = fn_8027CF9C(fn_8027C020(3432));
    format = fn_8027D284(decoder->m28);
    format.m8 = 1;
    fn_8027D2C4(decoder->m28, &format, 0);
    if (decoder->m24 <= 2) {
        fn_8027D2E0(decoder->m28, 0);
    } else {
        fn_8027D2E0(decoder->m28, 1);
    }
    fn_8027CFCC(decoder->m28, (unsigned char *)params->m0, decoder->m1C * 4, decoder->m1C);
}

}
