/* Sound filter (supxapf.cpp): the unpack filter for streamed EA-XA compressed sample packets, with its
   restore and init. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackxapf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    Decoder_8027BA6C *decoder;
    Snd::XAFSTATE state;
    int last;
    int total;
    int seed;
    int n;

    decoder = (Decoder_8027BA6C *)node;
    total = 0;
    seed = 0;
    if (decoder->m34 != 0) {
        SNDPKTPLAYI_freeframes(decoder->m30, decoder->m38, decoder->m34);
        decoder->m34 = 0;
    }
    while (count > 0) {
        n = decoder->m1C->Decode(&b, count);
        decoder->m28 += n;
        b += n;
        decoder->m34 += n;
        total += n;
        if (n < count) {
            count -= n;
            decoder->m20 = (int)SNDPKTPLAYI_get(decoder->m30, decoder->m38, &decoder->m24, &last);
            if (decoder->m20 != 0) {
                if (decoder->m2C <= 2) {
                    seed = 1;
                }
                if (seed != 0) {
                    state.mPrev1 = ((short *)decoder->m20)[0];
                    state.mPrev2 = ((short *)decoder->m20)[1];
                    decoder->m1C->SetState(&state);
                    decoder->m20 += 4;
                }
                decoder->m28 = 0;
                decoder->m1C->Feed((char *)decoder->m20, decoder->m24 * 4, decoder->m24);
            } else {
                if (count > 0 && decoder->m34 != 0) {
                    memset(b, 0, count * 4);
                }
                count = 0;
            }
        } else {
            count -= n;
        }
    }
    return total;
}

void SFILTER_unpackxapfrestore(Node_80279D90 *node)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    if (decoder->m1C != 0) {
        delete decoder->m1C;
    }
}

void SFILTER_unpackxapfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    Decoder_8027BA6C *decoder;

    decoder = (Decoder_8027BA6C *)node;
    node->m0 = SFILTER_unpackxapf;
    node->m4 = SFILTER_unpackxapfrestore;
    decoder->m30 = SNDPKTPLAYI_voicetopackethandle(fn_80274304(params->m1C));
    decoder->m38 = fn_80274334(params->m1C);
    decoder->m2C = params->m24;
    decoder->m20 = 0;
    decoder->m24 = params->mC;
    decoder->m28 = 0;
    decoder->m34 = 0;
    decoder->m1C = new Snd::CEAXABLKDecf;
}

}
