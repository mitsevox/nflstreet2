/* Sound packet players (spktplay.c): the streamed players that queue decoded audio packets per channel
   for the voices that play them: create, start, submit, submit space, frames outstanding, purge, stop,
   destroy, the packet fetch of the decoders, frame release and the callback flush. Names from the
   GoldenEye: Rogue Agent, Medal of Honor: European Assault and NASCAR 2005 symbol sets (spktplay.c). */

#include "engine/sndsys.h"

extern "C" {

int fn_802743A0(int index, void *stream);
int SNDstop(int handle);
void SNDPKTPLAYI_flushcallbackdata(void);
int SNDPKTPLAY_purge(int index, int a, int b);
void SNDI_checkplayopts(SndPlayOpts_t *opts);
void iSNDcalcpitch(int index);
int fn_80274464(int stream, int index, int a, int b, int c, Info_80274464 *info, Struct_80274464 *p);
void fn_8026A0E8(int value);
void fn_80273D7C(unsigned int flags, int *a, int *b);
extern float lbl_80300028;
int fn_80269D28(int count, int priority, int *handle, int rate, int format);
int SNDI_validrendermode(int *mode, SndPatchHeader_t *header);
void SetDefaultAzimuths(Record_803A6DF0 *p);
int SNDPKTPLAYI_gethighchannel(int index, int count);

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

int SNDPKTPLAY_create(void (*release)(int value, void *context), void (*callback)(int index, int value, void *context),
                      void *context, void *memory,
                      unsigned int size)
{
    SndPacketPlayer_t *stream;
    void *voice;
    int i = 0;

    SNDSYS_entercritical();
    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        if (sndpps.m304[i] == 0) {
            goto found;
        }
    }
    SNDSYS_leavecritical();
    return -9;
found:
    if (fn_802743A0(i, memory) < 0) {
        SNDSYS_leavecritical();
        return -6;
    }
    voice = memory;
    memory = (char *)memory + fn_80274398();
    size -= fn_80274398();
    stream = (SndPacketPlayer_t *)memory;
    stream->m40 = (size - 156) / 32;
    stream->m50 = voice;
    stream->m54 = release;
    stream->m58 = callback;
    stream->m5C = context;
    stream->m0 = -1;
    sndpps.m304[i] = stream;
    SNDSYS_leavecritical();
    return i;
}

int SNDPKTPLAY_start(int index, Info_80274464 *info, Struct_80274464 *params, SndPlayOpts_t *opts)
{
    SndPacketPlayer_t *stream;
    Record_803A6DF0 *record;
    Record_803A6DF0 *channel;
    SndPatchHeader_t header;
    int rate;
    int format;
    int handle;
    int cursor = 0;
    int found = 0;
    int render;
    int count;
    int voice;
    int result;
    int i;

    SNDI_checkplayopts(opts);
    stream = sndpps.m304[index];
    count = info->m2;
    header.m3 = info->m2;
    header.m18 = params->m8;
    // FAKEMATCH: duplicate store of the initialized cursor, kept for the scheduler (without it 99.26%, 1108 vs 1112 bytes)
    cursor = 0;
    // FAKEMATCH: format copy before the queue resets and the channel-record store order below were found
    // by search (the scheduler then gives the target load and store order)
    stream->m60 = *info;
    stream->m4 = 0;
    stream->m48 = 0;
    stream->m4C = 0;
    stream->mC = 0;
    stream->m8 = 0;
    stream->m46 = 0;
    stream->m44 = 0;
    for (i = 0; i < stream->m60.m2; i++) {
        stream->m10[i] = 0;
        stream->m34[i] = 0;
        stream->m28[i] = 0;
        stream->m64[i] = params->m18[i];
    }
    // FAKEMATCH: found is never set (success leaves by break); without the test 80.87%
    while (!found && (render = SNDI_validrendermode(&cursor, &header)) != 0) {
        fn_80273D7C(render, &rate, &format);
        voice = fn_80269D28(count, 101, &handle, rate, format);
        if (voice < 0) {
            stream->m0 = -9;
            continue;
        }
        stream->m0 = handle;
        stream->m42 = SNDPKTPLAYI_gethighchannel(voice, info->m2);
        record = &lbl_803A6C24.m1CC[voice];
        record->m18 = -1;
        record->m14 = 0;
        record->m20 = info->m0;
        record->m22 = info->m3;
        record->m23 = info->m2;
        if (info->m2 == 1) {
            record->m1C = opts->m8;
        } else {
            SetDefaultAzimuths(record);
        }
        record->m4[7] = -1;
        record->m4C = 0;
        record->m88 = params->m0;
        record->m8C = opts->mC;
        record->m68 = opts->m1;
        record->m60 = opts->m5;
        *record->m64 = (signed char)opts->m5 * (1.0f / 127.0f);
        record->m86 = params->m6 * 100;
        record->m26 = 0;
        record->m27 = 0;
        record->m78 = 0;
        record->m80 = 0;
        record->m38 = (signed char)opts->m0 * (1.0f / 127.0f);
        for (i = 0; i < info->m2; i++) {
            record->m50[i] = params->mC[i] - lbl_803A6C24.m1D8[info->m2 - 1][i];
            channel = &lbl_803A6C24.m1CC[record->m4[i]];
            // FAKEMATCH: search-found store order (see the comment at the format copy)
            channel->m24 = render;
            channel->m5F = opts->m4;
            channel->m2B = params->m3;
            channel->m38 = record->m38;
            channel->m74 = 0;
            channel->m5C = 1;
            channel->m30 = 0.0f;
            channel->m40 = 0x7F0000;
            channel->m44 = 0x7FFFFFFF;
            channel->m5E = 0;
            channel->m5D = 0;
            channel->m48 = channel->m38 * lbl_80300028;
            channel->m3C = 0;
            channel->m70 = 0;
            channel->m7C = 0;
            if (i == 5) {
                channel->m4E = 1;
            } else {
                channel->m4E = 0;
            }
            channel->m1E = 0;
        }
        if (info->m2 == 1) {
            record->m1E = opts->mA;
        }
        for (i = 0; i < info->m2; i++) {
            lbl_803A6C24.m1CC[record->m4[i]].m1C += record->m50[i];
        }
        record->m8A = 0;
        iSNDcalcpitch(voice);
        result = fn_80274464(index, voice, opts->mE, opts->m14, opts->m16, info, params);
        if (result >= 0) {
            break;
        }
        for (i = 0; i < count; i++) {
            fn_8026A0E8(lbl_803A6C24.m1CC[voice].m4[i]);
        }
        stream->m0 = result;
    }
    return stream->m0;
}

int SNDPKTPLAY_submit(int index, SndPacket_t *packet)
{
    SndPacketPlayer_t *stream = sndpps.m304[index];
    SndPacketEntry_t *entry;
    int id;
    int i;

    for (i = 0; i < stream->m60.m2; i++) {
        if (stream->m34[i] >= stream->m40 - 1) {
            return -13;
        }
    }
    entry = &stream->m7C[stream->m46];
    entry->m4 = packet->m4;
    entry->m4b = packet->m4b;
    entry->m0 = stream->m4;
    for (i = 0; i < stream->m60.m2; i++) {
        entry->m8[i] = packet->mC[i];
        stream->m34[i]++;
    }
    stream->m48 += packet->m4;
    id = stream->m4;
    stream->m4++;
    if (++stream->m46 >= stream->m40) {
        stream->m46 = 0;
    }
    return id;
}

int SNDPKTPLAY_submitspace(int index)
{
    SndPacketPlayer_t *stream = sndpps.m304[index];
    int value = 0;
    int i;
    for (i = 0; i < stream->m60.m2; i++) {
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
    return stream->m48 + stream->m4C;
}

int SNDPKTPLAY_purge(int index, int a, int b)
{
    return -15;
}

int SNDPKTPLAY_stop(int index)
{
    SndPacketPlayer_t *stream = sndpps.m304[index];
    int i = 0;

    SNDstop(stream->m0);
    SNDPKTPLAYI_flushcallbackdata();
    SNDPKTPLAY_purge(index, 0, 0x7FFFFFFF);
    stream->m0 = -1;
    for (i = 0; i < stream->m60.m2; i++) {
        if (stream->m64[i] != 0) {
            SNDMEMI_free(stream->m64[i]);
        }
    }
    return 0;
}

int SNDPKTPLAY_destroy(int index)
{
    SNDSYS_entercritical();
    fn_8027474C(index);
    sndpps.m304[index] = 0;
    SNDSYS_leavecritical();
    return 0;
}

unsigned char *SNDPKTPLAYI_get(int index, int channel, int *count, int *last)
{
    SndPacketPlayer_t *stream = sndpps.m304[index];
    SndPacketEntry_t *oldest;
    SndPacketEntry_t *entry;
    SndPacketEvent_t *event;
    unsigned char *data;
    unsigned char *result;
    int i;
    int all = 1;
    int done = 1;

    for (i = 0; i < stream->m60.m2; i++) {
        if (stream->m10[i] <= stream->m8) {
            all = 0;
        }
    }
    if (all) {
        oldest = &stream->m7C[stream->m44];
        if (stream->m54 != 0) {
            event = &sndpps.m4[sndpps.m0];
            event->m0 = 1;
            event->m2 = index;
            event->m4 = (int)oldest->m8[0];
            sndpps.m0++;
        }
        stream->m44++;
        stream->m8++;
        if (stream->m44 >= stream->m40) {
            stream->m44 = 0;
        }
    }
    if (stream->m34[channel] == 0) {
        return 0;
    }
    entry = &stream->m7C[stream->m28[channel]];
    *count = entry->m4;
    *last = entry->m4b;
    stream->m28[channel]++;
    stream->m10[channel]++;
    i = 0;
    do {
        if (stream->m10[i] <= stream->mC) {
            done = 0;
        }
        i++;
    } while (done == 1 && i < stream->m60.m2);
    if (done) {
        stream->mC++;
        stream->m48 -= entry->m4;
        stream->m4C += entry->m4;
    }
    if (stream->m28[channel] >= stream->m40) {
        stream->m28[channel] = 0;
    }
    stream->m34[channel]--;
    result = (unsigned char *)-1;
    data = (unsigned char *)entry->m8[channel];
    if (data != 0) {
        result = data;
    }
    return result;
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

void SNDPKTPLAYI_flushcallbackdata(void)
{
    SndPacketEvent_t *event;
    SndPacketPlayer_t *stream;
    int i;

    for (i = 0; i < sndpps.m0; i++) {
        event = &sndpps.m4[i];
        stream = sndpps.m304[event->m2];
        if (event->m0 == 0) {
            stream->m58(event->m2, event->m4, stream->m5C);
        } else {
            stream->m54(event->m4, stream->m5C);
        }
    }
    sndpps.m0 = 0;
}

}
