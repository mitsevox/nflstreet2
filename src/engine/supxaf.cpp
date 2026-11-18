/* Sound filter (supxaf.cpp): the unpack filter for EA-XA compressed sample blocks held in memory.
   It decodes through an EA-XA block decoder, reports the frame position, and releases the decoder. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackxaf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndXaUnpackFilter_t *decoder;
    int n;

    decoder = (SndXaUnpackFilter_t *)node;
    if (decoder->mFramePosition >= decoder->mFrameCount) {
        return -1;
    }
    n = fn_8027BE24(decoder->mpDecoder, &b, count);
    decoder->mFramePosition += n;
    b += n;
    if (n < count) {
        count -= n;
        memset(b, 0, count * 4);
        n += count;
    }
    return n;
}

int SFILTER_unpackgetframexaf(Node_80279D90 *node)
{
    return ((SndXaUnpackFilter_t *)node)->mFramePosition;
}

void SFILTER_unpackxafrestore(Node_80279D90 *node)
{
    SndXaUnpackFilter_t *decoder;

    decoder = (SndXaUnpackFilter_t *)node;
    if (decoder->mpDecoder != 0) {
        fn_8027BD94(decoder->mpDecoder);
    }
}

void SFILTER_unpackxafinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndXaUnpackFilter_t *decoder;

    decoder = (SndXaUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackxaf;
    node->m4 = SFILTER_unpackxafrestore;
    decoder->mpData = (char *)params->m0;
    decoder->mFrameCount = params->mC;
    decoder->mFramePosition = 0;
    decoder->mpDecoder = fn_8027BDC0(fn_8027BD68(168));
    params->m28 = SFILTER_unpackgetframexaf;
    fn_8027BDE8(decoder->mpDecoder, decoder->mpData, decoder->mFrameCount * 4, decoder->mFrameCount);
}

}
