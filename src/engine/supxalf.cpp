/* Sound filter (supxalf.cpp): the unpack filter for looped EA-XA compressed sample blocks. Its init
   either decodes the whole block in memory or, for streamed voices, records the packet loop points. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackgetframexalf(Node_80279D90 *node)
{
    return ((Decoder_8027B7B0 *)node)->m20;
}

void SFILTER_unpackxalfrestore(Node_80279D90 *node)
{
    Decoder_8027B7B0 *decoder;

    decoder = (Decoder_8027B7B0 *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void SFILTER_unpackxalfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027B7B0 *decoder;

    decoder = (Decoder_8027B7B0 *)node;
    node->m0 = fn_8027B4F4;
    node->m4 = SFILTER_unpackxalfrestore;
    decoder->m20 = 0;
    decoder->m2C = params->m4;
    decoder->m30 = params->m24;
    decoder->m24 = params->m10;
    decoder->m28 = params->m14;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
    params->m28 = SFILTER_unpackgetframexalf;
    if (decoder->m30 <= 2) {
        decoder->m34 = params->m0;
        decoder->m40 = 0;
        decoder->m38 = params->mC;
        decoder->m3C = 0;
        decoder->m44 = params->m10;
        decoder->m48 = params->m14;
    } else {
        fn_8027BDE8(decoder->m1C, (char *)params->m0, decoder->m24 * 4, decoder->m24);
    }
}

}
