/* Queues streamed audio for each voice channel and delivers its release and playback callbacks. */

#include "engine/sndbank.h"
#include "engine/sndsys.h"

/* Release-style assertion form for the vacant-slot branch. */
#define SND_ASSERT(e) do { } while (0)

extern "C" {

SndPacketPlayers_t sndpps;

int SNDstop(int handle);
void SNDPKTPLAYI_flushcallbackdata(void);
int SNDPKTPLAY_purge(int index, int a, int b);
void SNDI_checkplayopts(SndPlayOpts_t *opts);
void iSNDcalcpitch(int index);
int SNDPLATFORM_packetplay(int stream, int index, int a, int b, int c, Info_80274464 *info, Struct_80274464 *p);
void SNDVOICEI_free(int value);
extern float lbl_80300028;
int SNDVOICEI_alloc(int count, int priority, int *handle, int rate, int format);
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
    return SNDPKTPLAYI_overhead(count) + SNDPLATFORM_packetoverhead();
}

int SNDPKTPLAY_create(SndPacketReleaseFn_t release, SndPacketFramesDoneFn_t callback, void *context,
                      void *memory, unsigned int size)
{
    SndPacketPlayer_t *stream;
    void *voice;
    int i = 0;

    SNDSYS_entercritical();
    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        if (sndpps.mPlayers[i] == 0) {
            goto found;
        }
    }
    SNDSYS_leavecritical();
    return -9;
found:
    // FAKEMATCH: compiled-out assert; its empty do-while keeps the slot search apart from the voice setup
    SND_ASSERT(size >= (unsigned int)SNDPKTPLAY_overhead(8));
    if (SNDPLATFORM_packetplaycreate(i, (Stream_802743A0 *)memory) < 0) {
        SNDSYS_leavecritical();
        return -6;
    }
    voice = memory;
    memory = (char *)memory + SNDPLATFORM_packetoverhead();
    size -= SNDPLATFORM_packetoverhead();
    stream = (SndPacketPlayer_t *)memory;
    stream->mQueueCapacity = (size - 156) / 32;
    stream->mVoiceMemory = voice;
    stream->mReleaseCallback = release;
    stream->mFramesDoneCallback = callback;
    stream->mCallbackContext = context;
    stream->mVoiceHandle = -1;
    sndpps.mPlayers[i] = stream;
    SNDSYS_leavecritical();
    return i;
}

int SNDPKTPLAY_start(int index, Info_80274464 *info, Struct_80274464 *params, SndPlayOpts_t *opts)
{
    SndPacketPlayer_t *stream;
    Record_803A6DF0 *record;
    Record_803A6DF0 *channel;
    SNDIPATCHHEADER header;
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
    stream = sndpps.mPlayers[index];
    count = info->m2;
    header.m3 = info->m2;
    header.m18 = params->m8;
    // FAKEMATCH: duplicate store of the initialized cursor, kept for the scheduler (without it 99.26%, 1108 vs 1112 bytes)
    cursor = 0;
    // FAKEMATCH: format copy before the queue resets and the channel-record store order below were found
    // by search (the scheduler then gives the target load and store order)
    stream->mFormat = *info;
    stream->mNextPacketId = 0;
    stream->mQueuedFrames = 0;
    stream->mActiveFrames = 0;
    stream->mConsumedPackets = 0;
    stream->mRetiredPackets = 0;
    stream->mWriteIndex = 0;
    stream->mRetireIndex = 0;
    for (i = 0; i < stream->mFormat.m2; i++) {
        stream->mChannelConsumedPackets[i] = 0;
        stream->mChannelQueuedPackets[i] = 0;
        stream->mChannelReadIndex[i] = 0;
        stream->mChannelBuffers[i] = params->m18[i];
    }
    // FAKEMATCH: found is never set (success leaves by break); without the test 80.87%
    while (!found && (render = SNDI_validrendermode(&cursor, &header)) != 0) {
        SNDPLATFORM_getvoicerange(render, &rate, &format);
        voice = SNDVOICEI_alloc(count, 101, &handle, rate, format);
        if (voice < 0) {
            stream->mVoiceHandle = -9;
            continue;
        }
        stream->mVoiceHandle = handle;
        stream->mHighChannel = SNDPKTPLAYI_gethighchannel(voice, info->m2);
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
        for (i = 0; i < info->m2; ++i) {
            unsigned short *outputAzimuth = &lbl_803A6C24.m1CC[record->m4[i]].m1C;
            *outputAzimuth += record->m50[i];
        }
        record->m8A = 0;
        iSNDcalcpitch(voice);
        result = SNDPLATFORM_packetplay(index, voice, opts->mE, opts->m14, opts->m16, info, params);
        if (result >= 0) {
            break;
        }
        for (i = 0; i < count; i++) {
            SNDVOICEI_free(lbl_803A6C24.m1CC[voice].m4[i]);
        }
        stream->mVoiceHandle = result;
    }
    return stream->mVoiceHandle;
}

int SNDPKTPLAY_submit(int index, SndPacket_t *packet)
{
    SndPacketPlayer_t *stream = sndpps.mPlayers[index];
    SndPacketEntry_t *entry;
    int id;
    int i;

    for (i = 0; i < stream->mFormat.m2; i++) {
        if (stream->mChannelQueuedPackets[i] >= stream->mQueueCapacity - 1) {
            return -13;
        }
    }
    entry = &stream->mEntries[stream->mWriteIndex];
    entry->mFrames = packet->mFrames;
    entry->mLast = packet->mLast;
    entry->mPacketId = stream->mNextPacketId;
    for (i = 0; i < stream->mFormat.m2; i++) {
        entry->mChannelData[i] = packet->mChannelData[i];
        stream->mChannelQueuedPackets[i]++;
    }
    stream->mQueuedFrames += packet->mFrames;
    id = stream->mNextPacketId;
    stream->mNextPacketId++;
    if (++stream->mWriteIndex >= stream->mQueueCapacity) {
        stream->mWriteIndex = 0;
    }
    return id;
}

int SNDPKTPLAY_submitspace(int index)
{
    SndPacketPlayer_t *stream = sndpps.mPlayers[index];
    int value = 0;
    int i;
    for (i = 0; i < stream->mFormat.m2; i++) {
        if (stream->mChannelQueuedPackets[i] >= value) {
            value = stream->mChannelQueuedPackets[i];
        }
    }
    return stream->mQueueCapacity - value - 1;
}

int SNDPKTPLAY_framesoutstanding(int index)
{
    SndPacketPlayer_t *stream;

    stream = sndpps.mPlayers[index];
    return stream->mQueuedFrames + stream->mActiveFrames;
}

int SNDPKTPLAY_purge(int index, int a, int b)
{
    return -15;
}

int SNDPKTPLAY_stop(int index)
{
    SndPacketPlayer_t *stream = sndpps.mPlayers[index];
    int i = 0;

    SNDstop(stream->mVoiceHandle);
    SNDPKTPLAYI_flushcallbackdata();
    SNDPKTPLAY_purge(index, 0, 0x7FFFFFFF);
    stream->mVoiceHandle = -1;
    for (i = 0; i < stream->mFormat.m2; i++) {
        if (stream->mChannelBuffers[i] != 0) {
            SNDMEMI_free(stream->mChannelBuffers[i]);
        }
    }
    return 0;
}

int SNDPKTPLAY_destroy(int index)
{
    SNDSYS_entercritical();
    SNDPLATFORM_packetplaydestroy(index);
    sndpps.mPlayers[index] = 0;
    SNDSYS_leavecritical();
    return 0;
}

unsigned char *SNDPKTPLAYI_get(int index, int channel, int *count, int *last)
{
    SndPacketPlayer_t *stream = sndpps.mPlayers[index];
    SndPacketEntry_t *oldest;
    SndPacketEntry_t *entry;
    SndPacketEvent_t *event;
    unsigned char *data;
    unsigned char *result;
    int i;
    int all = 1;
    int done = 1;

    for (i = 0; i < stream->mFormat.m2; i++) {
        if (stream->mChannelConsumedPackets[i] <= stream->mRetiredPackets) {
            all = 0;
        }
    }
    if (all) {
        oldest = &stream->mEntries[stream->mRetireIndex];
        if (stream->mReleaseCallback != 0) {
            event = &sndpps.mEvents[sndpps.mEventCount];
            event->mKind = 1;
            event->mPlayerIndex = index;
            event->mPayload.mpBuffer = oldest->mChannelData[0];
            sndpps.mEventCount++;
        }
        stream->mRetireIndex++;
        stream->mRetiredPackets++;
        if (stream->mRetireIndex >= stream->mQueueCapacity) {
            stream->mRetireIndex = 0;
        }
    }
    if (stream->mChannelQueuedPackets[channel] == 0) {
        return 0;
    }
    entry = &stream->mEntries[stream->mChannelReadIndex[channel]];
    *count = entry->mFrames;
    *last = entry->mLast;
    stream->mChannelReadIndex[channel]++;
    stream->mChannelConsumedPackets[channel]++;
    i = 0;
    do {
        if (stream->mChannelConsumedPackets[i] <= stream->mConsumedPackets) {
            done = 0;
        }
        i++;
    } while (done == 1 && i < stream->mFormat.m2);
    if (done) {
        stream->mConsumedPackets++;
        stream->mQueuedFrames -= entry->mFrames;
        stream->mActiveFrames += entry->mFrames;
    }
    if (stream->mChannelReadIndex[channel] >= stream->mQueueCapacity) {
        stream->mChannelReadIndex[channel] = 0;
    }
    stream->mChannelQueuedPackets[channel]--;
    result = (unsigned char *)-1;
    data = (unsigned char *)entry->mChannelData[channel];
    if (data != 0) {
        result = data;
    }
    return result;
}

void SNDPKTPLAYI_freeframes(int index, int channel, int value)
{
    SndPacketPlayer_t *stream;
    SndPacketEvent_t *event;

    stream = sndpps.mPlayers[index];
    if (channel == stream->mHighChannel) {
        stream->mActiveFrames -= value;
        if (stream->mFramesDoneCallback != 0) {
            event = &sndpps.mEvents[sndpps.mEventCount];
            event->mKind = 0;
            event->mPlayerIndex = index;
            event->mPayload.mFrames = value;
            sndpps.mEventCount++;
        }
    }
}

void SNDPKTPLAYI_flushcallbackdata(void)
{
    SndPacketEvent_t *event;
    SndPacketPlayer_t *stream;
    int i;

    for (i = 0; i < sndpps.mEventCount; i++) {
        event = &sndpps.mEvents[i];
        stream = sndpps.mPlayers[event->mPlayerIndex];
        if (event->mKind == 0) {
            stream->mFramesDoneCallback(event->mPlayerIndex, event->mPayload.mFrames, stream->mCallbackContext);
        } else {
            stream->mReleaseCallback(event->mPayload.mpBuffer, stream->mCallbackContext);
        }
    }
    sndpps.mEventCount = 0;
}

}
