/* Sound stream effect level (sstfxlev.c): sets one effect bus send of a stream channel and
   copies it to every voice of the stream. */

#include "engine/sndstrm.h"

extern "C" {

int SNDSTRM_fxlevel(int stream, int bus, int level)
{
    SndStreamChannel_t *channel;
    int voice;
    int i;
    Record_803A6DF0 *dst;

    channel = fn_8026D610(stream);
    if (channel == 0) {
        return -8;
    }
    channel->mpFxLevels[bus] = (float)level * (1.0f / 127.0f);
    voice = fn_8026A288(channel->mVoice);
    if (voice >= 0) {
        for (i = 0; i < channel->mChannels; i++) {
            dst = lbl_803A6C24.m1CC + lbl_803A6C24.m1CC[voice].m4[i];
            dst->m64[bus] = channel->mpFxLevels[bus];
        }
        fn_80278070(channel->mVoice, bus, level);
    }
    return 0;
}

}
