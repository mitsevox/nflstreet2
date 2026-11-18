/* Sound filter (supmutpf.c): the unpack filter for MT-compressed samples, with its restore and
   init. */

#include "engine/sndsys.h"

extern "C" {

int SFILTER_unpackmtpf(Node_80279D90 *node, int count, float *a, float *b, int flag)
{
    SndMtUnpackFilter_t *decoder;
    Format_8027D284 format;
    int last;
    int total;
    int n;

    decoder = (SndMtUnpackFilter_t *)node;
    total = 0;
    if (decoder->mPendingCount != 0) {
        SNDPKTPLAYI_freeframes(decoder->mStream, decoder->mChannel, decoder->mPendingCount);
        decoder->mPendingCount = 0;
    }
    while (count > 0) {
        n = CodecReadSamples(decoder->mpCodec, &b, count);
        decoder->mPacketPosition += n;
        b += n;
        decoder->mPendingCount += n;
        total += n;
        if (n < count) {
            count -= n;
            decoder->mpPacket = fn_802792F0(decoder->mStream, decoder->mChannel, &decoder->mPacketCount, &last);
            if (decoder->mpPacket != 0) {
                decoder->mPacketPosition = 0;
                if (decoder->mMode <= 2) {
                    if (last == 0) {
                        format = fn_8027D284(decoder->mpCodec);
                        format.m8 = 1;
                        fn_8027D2C4(decoder->mpCodec, &format, 0);
                    } else {
                        format = fn_8027D284(decoder->mpCodec);
                        format.m8 = 0;
                        fn_8027D2C4(decoder->mpCodec, &format, 0);
                    }
                    fn_8027D2E0(decoder->mpCodec, 0);
                } else {
                    if (last == 0) {
                        format = fn_8027D284(decoder->mpCodec);
                        format.m4 = 0;
                        format.m8 = 1;
                    } else {
                        format = fn_8027D284(decoder->mpCodec);
                        format.m8 = 0;
                    }
                    fn_8027D2C4(decoder->mpCodec, &format, 0);
                    fn_8027D2E0(decoder->mpCodec, 1);
                }
                fn_8027CFCC(decoder->mpCodec, decoder->mpPacket + 1, decoder->mPacketCount * 4, decoder->mPacketCount);
            } else {
                if (count > 0 && decoder->mPendingCount != 0) {
                    memset(b, 0, count * 4);
                }
                decoder->mPacketCount = 0;
                count = 0;
            }
        } else {
            count -= n;
        }
    }
    return total;
}

void SFILTER_unpackmtpfrestore(Node_80279D90 *node)
{
    SndMtUnpackFilter_t *decoder;

    decoder = (SndMtUnpackFilter_t *)node;
    if (decoder->mpCodec != 0) {
        fn_8027C04C(decoder->mpCodec);
    }
}

void SFILTER_unpackmtpfinit(Node_80279D90 *node, Params_80275F80 *params)
{
    SndMtUnpackFilter_t *decoder;

    decoder = (SndMtUnpackFilter_t *)node;
    node->m0 = SFILTER_unpackmtpf;
    decoder->mStream = SNDPKTPLAYI_voicetopackethandle(fn_80274304(params->m1C));
    decoder->mChannel = fn_80274334(params->m1C);
    decoder->mpPacket = 0;
    decoder->mPacketPosition = 0;
    decoder->mMode = params->m24;
    decoder->mPacketCount = params->mC;
    node->m4 = SFILTER_unpackmtpfrestore;
    decoder->mpCodec = fn_8027CF9C(fn_8027C020(3432));
    decoder->mPendingCount = 0;
}

}
