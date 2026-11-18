/* Sound filter (suppf.c): the unpack filter for streamed 16-bit sample packets. It pulls packets from
   the sound stream, converts their samples to floats and acknowledges what it consumed. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackpf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndPcmPacketUnpackFilter_t *decoder;
    int length;
    int last;
    int n;

    decoder = (SndPcmPacketUnpackFilter_t *)node;
    if (decoder->mPendingCount != 0) {
        SNDPKTPLAYI_freeframes(decoder->mStream, decoder->mChannel, decoder->mPendingCount);
        decoder->mPendingCount = 0;
    }
    while (count > 0) {
        if (decoder->mPosition >= decoder->mPacketLength) {
            decoder->mpPacket = fn_802792F0(decoder->mStream, decoder->mChannel, &length, &last);
            if (decoder->mpPacket == 0) {
                if (decoder->mPendingCount != 0) {
                    memset(b, 0, count * 4);
                }
                return decoder->mPendingCount;
            }
            decoder->mPosition = 0;
            decoder->mPacketLength = length;
        }
        n = decoder->mPacketLength - decoder->mPosition;
        if (count < n) {
            n = count;
        }
        if (decoder->mConvert != 0) {
            lbl_803B4E34.m1E4(n, (short *)(decoder->mpPacket + (decoder->mPosition << 1)), b);
        }
        b += n;
        decoder->mPosition += n;
        decoder->mPendingCount += n;
        count -= n;
    }
    return decoder->mPendingCount;
}

void SFILTER_unpackpfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndPcmPacketUnpackFilter_t *decoder;

    decoder = (SndPcmPacketUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackpf;
    decoder->mStream = SNDPKTPLAYI_voicetopackethandle(fn_80274304(params->m1C));
    decoder->mChannel = fn_80274334(params->m1C);
    decoder->mPacketLength = -1;
    decoder->mpPacket = 0;
    decoder->mPosition = 0;
    decoder->mConvert = params->m18;
    decoder->mPendingCount = 0;
}

}
