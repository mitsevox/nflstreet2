/* Sound packet players (spktplay.c): the streamed players that queue decoded audio packets per channel
   for the voices that play them: overhead, submit space, frames outstanding, purge, destroy and frame
   release. Create, start, submit, stop, packet fetch and the callback flush are not reconstructed yet. */

#include "engine/sndsys.h"

extern "C" {

int SNDPKTPLAYI_gethighchannel(int index, int count)
{
    int i;
    int value = -1;
    int result = -1;
    for (i = 0; i < count; i++) {
        if (lbl_803A6C24.m1CC[index].m4[i] > value) {
            value = lbl_803A6C24.m1CC[index].m4[i];
            result = i;
        }
    }
    return result;
}

int SNDPKTPLAYI_overhead(int count)
{
    return count * 32 + 156;
}

int SNDPKTPLAY_overhead(int count)
{
    return SNDPKTPLAYI_overhead(count) + fn_80274398();
}

int SNDPKTPLAY_submitspace(int index)
{
    SndPacketPlayer_t *stream = sndpps.m304[index];
    int value = 0;
    int i;
    for (i = 0; i < stream->m62; i++) {
        if (stream->m34[i] >= value) {
            value = stream->m34[i];
        }
    }
    return stream->m40 - value - 1;
}

int SNDPKTPLAY_framesoutstanding(int index)
{
    SndPacketPlayer_t *stream;

    stream = sndpps.m304[index];
    return stream->m4C + stream->m48;
}

int SNDPKTPLAY_purge(int index, int a, int b)
{
    return -15;
}

int SNDPKTPLAY_destroy(int index)
{
    SNDSYS_entercritical();
    fn_8027474C(index);
    sndpps.m304[index] = 0;
    SNDSYS_leavecritical();
    return 0;
}

void SNDPKTPLAYI_freeframes(int index, int channel, int value)
{
    SndPacketPlayer_t *stream;
    SndPacketEvent_t *event;

    stream = sndpps.m304[index];
    if (channel == stream->m42) {
        stream->m4C -= value;
        if (stream->m58 != 0) {
            event = &sndpps.m4[sndpps.m0];
            event->m0 = 0;
            event->m2 = index;
            event->m4 = value;
            sndpps.m0++;
        }
    }
}

}
