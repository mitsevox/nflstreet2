/* Sound filter (supxapf.cpp): the unpack filter for streamed EA-XA compressed sample packets, with its
   restore and init. */

#include "engine/sndsys.h"

extern "C" {

void fn_8027BA40(Node_80279D90 *node)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    if (decoder->m1C != 0) {
        fn_8027BD94(decoder->m1C);
    }
}

void fn_8027BA6C(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    node->m0 = fn_8027B888;
    node->m4 = fn_8027BA40;
    decoder->m30 = SNDPKTPLAYI_voicetopackethandle(fn_80274304(params->m1C));
    decoder->m38 = fn_80274334(params->m1C);
    decoder->m2C = params->m24;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = 0;
    decoder->m34 = 0;
    decoder->m1C = fn_8027BDC0(fn_8027BD68(168));
}

}
