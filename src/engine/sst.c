/* Sound stream channel core (sst.c): creates and destroys the stream channels, queues file and
   request-id streams on them, parses the stream chunks the stream taps deliver (headers and sample
   data), starts the packet player voice of a parsed stream and services every channel at 100 Hz. */

#include "engine/sndstrm.h"
#include "engine/sndsys.h"
#include "engine/sndbank.h"

extern "C" {

extern SndStreamChannel_t *lbl_803A7648[];

void *memset(void *dest, int ch, unsigned int count);
int memcmp(const void *a, const void *b, unsigned int count);
int STREAM_queuefile(void *tap, char *name, int offset, int tag);
int STREAM_queuemem(void *tap, char *name, int offset, int tag);
void STREAM_release(void *tap, void *chunk);
void STREAM_destroy(void *tap);
void STREAM_kill(void *tap);
int SNDPKTPLAY_destroy(int buffer);
int SNDPKTPLAY_stop(int buffer);
void SNDMEMI_free(void *p);

}

void iSNDserverremoveclient(void (*client)(void));

/* A stream chunk as the tap delivers it: its four-character id and size. */
typedef struct SndStreamChunk_t {
    int mId;
    unsigned int mSize;
} SndStreamChunk_t;

/* The tag word in front of a delivered sample buffer; byte +0x3 is the stream index. */
typedef struct SndStreamBufferTag_t {
    unsigned char unk_0x0[3];
    unsigned char mStream;
} SndStreamBufferTag_t;

SndStreamChannel_t *SNDSTRMI_getstreamptr(int index);
void SNDSTRMI_removerequest(int id);
int SNDSTRMI_numcreated(void);

/* A sample-data chunk: the frame count, then one offset per channel from the end of the offset
   table to that channel's data. */
typedef struct SndStreamDataChunk_t {
    SndStreamChunk_t mHeader;
    unsigned int mFrames;
    unsigned int mOffsets[1];
} SndStreamDataChunk_t;

void SNDSTRMI_startstream(SndStreamChannel_t *channel);
int SNDSTRMI_parseheader(int stream, SndStreamChunk_t *chunk);
void SNDSTRMI_parsedata(SndStreamChannel_t *channel, SndStreamChunk_t *chunk);
int SNDSTRMI_parsechunk(int stream, SndStreamChunk_t *chunk);
int SNDSTRMI_isheld(SndStreamChannel_t *channel);
void SNDSTRMI_service(void);

void iSNDserveraddclient(void (*client)(void));

extern "C" {
void *STREAM_create(int numRequests, int a, int b, void *memory, int size);
int STREAM_buffersize(void *tap);
int SNDSTRM_setgreedylevel(int stream, int level);
extern const unsigned char lbl_802C1F68[][6][6];
extern unsigned char lbl_802C1FF8[][6];
int SNDPKTPLAY_start(int index, void *format, void *attr, void *opts);
int SNDCTRL_filteradd(int handle, void *desc);
int STREAM_state(void *tap);
SndStreamChunk_t *STREAM_get(void *tap);
int SNDPKTPLAY_submit(int index, SndPacket_t *packet);
int SNDPKTPLAY_submitspace(int index);
}

extern "C" {
int SNDSTRM_purge(int stream);
int SNDSTRM_destroy(int stream);
}

namespace Snd {

void StreamRemoveFaders(SndStreamChannel_t *channel)
{
    int i;

    for (i = 0; i < 6; i++) {
        SndStreamSpeaker_t *speaker = &channel->mSpeakers[i];

        if (speaker->mStep != 0.0f) {
            gVariableTimerList.Remove(&speaker->mFader);
        }
    }
}

}

/* Rounds to the nearest integer, halves away from zero. */
static inline int SNDSTRMI_round(float t)
{
    if (!(t < 0.0f)) {
        return (int)(t + 0.5f);
    }
    return (int)(t - 0.5f);
}

/* For a voice of n channels (row n-1), the stream speaker slot each voice channel plays, or -128. */
signed char SNDSTRMIchannelspeaker[6][6] = {
    {0, -128, -128, -128, -128, -128},
    {1, 2, -128, -128, -128, -128},
    {-128, -128, -128, -128, -128, -128},
    {1, 2, 3, 4, -128, -128},
    {-128, -128, -128, -128, -128, -128},
    {1, 0, 2, 3, 4, 5},
};

void SNDSTRMI_startstream(SndStreamChannel_t *channel)
{
    unsigned int i;
    int voice;

    channel->mVoice = SNDPKTPLAY_start(channel->mBuffer, &channel->mFormat, &channel->mAttr,
                                       channel->unk_0xEC);
    voice = SNDVOICEI_get(channel->mVoice);
    for (i = 0; i < channel->mFormat.mChannels; i++) {
        int j = 0;
        int index = lbl_803A6C24.m1CC[voice].m4[i];
        SndStreamSpeaker_t *speaker =
            &channel->mSpeakers[SNDSTRMIchannelspeaker[channel->mFormat.mChannels - 1][i]];
        Record_803A6DF0 *dst = &lbl_803A6C24.m1CC[index];
        float vol;

        for (; j < lbl_8030002C; j++) {
            dst->m64[j] = channel->mpFxLevels[j];
            SNDfxlevel(channel->mVoice, j, (int)(dst->m64[j] * 127.0f));
        }
        vol = speaker->mVolume;
        dst->m38 = vol;
        dst->m48 = vol * lbl_80300028;
        SndHalSetVol(index);
    }
    if (channel->mPanned == 0) {
        const unsigned char *pans = lbl_802C1F68[lbl_803A772C][channel->mFormat.mChannels - 1];
        const unsigned char *offsets = lbl_802C1FF8[channel->mFormat.mChannels - 1];

        for (i = 0; i < channel->mFormat.mChannels; i++) {
            int index = lbl_803A6C24.m1CC[voice].m4[i];
            Record_803A6DF0 *dst = &lbl_803A6C24.m1CC[index];
            SndStreamSpeaker_t *speaker =
                &channel->mSpeakers[SNDSTRMIchannelspeaker[channel->mFormat.mChannels - 1][i]];
            int pan;

            if (speaker->mAzimuth == -1000000.0f) {
                dst->m1C = pans[i] << 8;
            } else {
                pan = SNDSTRMI_round(speaker->mAzimuth * (65536.0f / 360.0f));
                dst->m1C = pan;
                if (speaker->mAzimuthOn == 0) {
                    dst->m1C = pan + (offsets[i] << 8);
                }
            }
            SndHalSetPan(index);
        }
    }
    for (i = 0; i < 1; i++) {
        if (channel->mSends[i].m10 != 0) {
            SNDCTRL_filteradd(channel->mVoice, &channel->mSends[i]);
        }
    }
    channel->mState = 1;
}

int SNDSTRMI_calcdatarate(SndSampleFormat_t *format)
{
    int bits = 0;
    int rate = format->mRate * format->mChannels;

    if (format->mCodec == 10) {
        bits = 136;
    } else if (format->mCodec == 4) {
        bits = 51;
    } else if (format->mCodec == 22) {
        bits = 102;
    } else if (format->mCodec == 7) {
        bits = 512;
    } else if (format->mCodec == 16) {
        return format->mChannels * 8;
    } else if (format->mCodec == 23) {
        return format->mChannels * 8;
    }
    return rate * bits >> 8;
}

int SNDSTRMI_destroyall(void)
{
    int i;

    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        SNDSTRM_destroy(i);
    }
    return 0;
}

SndStreamChannel_t *SNDSTRMI_getstreamptr(int index)
{
    if (index >= lbl_803A6C24.m1C.m22 || index < 0) {
        return 0;
    }
    return lbl_803A7648[index];
}

void SNDSTRMI_removerequest(int id)
{
    SndStreamChannel_t *channel = lbl_803A7648[(unsigned char)id];
    SndStreamRequest_t *request = SNDSTRMI_getrequestptr(id);

    SNDLINKI_remove(&channel->mRequests, &request->mLink);
    SNDLINKI_push(&channel->mFreeRequests, &request->mLink);
    if (channel->mpCurrent == request) {
        channel->mpCurrent = 0;
    }
}

void SNDSTRMI_releasecallback(void *buffer, void *unused)
{
    SndStreamBufferTag_t *tag = ((SndStreamBufferTag_t **)buffer)[-1];

    STREAM_release(lbl_803A7648[tag->mStream]->mpTap, tag);
}

void SNDSTRMI_framescallback(int unused, unsigned int frames, void *context)
{
    SndStreamChannel_t *channel = (SndStreamChannel_t *)context;
    unsigned int extra = 0;
    int passes = 0;

    for (;;) {
        SndStreamRequest_t *request = (SndStreamRequest_t *)channel->mRequests.mpFirst;

        if (++passes > 200) {
            SNDSTRMI_removerequest(request->mId);
            return;
        }
        if (frames > request->unk_0x1C) {
            extra = frames - request->unk_0x1C;
            frames -= extra;
        }
        request->unk_0x14 += frames;
        request->unk_0x1C -= frames;
        if (request->unk_0x14 >= request->unk_0x18) {
            SNDSTRMI_removerequest(request->mId);
        }
        if (extra == 0) {
            return;
        }
        frames = extra;
        extra = 0;
    }
}

/* The message a stream header passes to the bank user-data callbacks for each of its data blocks. */
typedef struct SndStreamUserDataMessage_t {
    int mEvent;
    unsigned char *mPayload;
    unsigned int mPayloadSize;
    int unk_0xC;
    int mRequestId;
} SndStreamUserDataMessage_t;

int SNDSTRMI_parseheader(int stream, SndStreamChunk_t *chunk)
{
    SndStreamChannel_t *channel = lbl_803A7648[stream];
    SndStreamRequest_t *request;
    SndSampleDesc_t desc;
    SndStreamUserDataMessage_t message;
    int i = 0;
    int j;

    if (channel->mpCurrent == 0) {
        channel->mpCurrent = (SndStreamRequest_t *)channel->mRequests.mpFirst;
    } else {
        channel->mpCurrent = (SndStreamRequest_t *)channel->mpCurrent->mLink.mpNext;
    }
    request = channel->mpCurrent;
    SNDI_patchtohdr(0, (unsigned char *)(chunk + 1), &channel->mQueueFormat, &channel->mQueueAttr, &desc,
                    &request->unk_0x25[0]);
    request->unk_0x18 = desc.mFrames;
    request->mActive = 0;
    while (channel->mQueueAttr.mDataBlocks[i] != 0) {
        message.mEvent = 3;
        message.mPayload = channel->mQueueAttr.mDataBlocks[i];
        message.mPayloadSize = channel->mQueueAttr.mDataBlockSizes[i];
        message.mRequestId = request->mId;
        channel->mQueueAttr.mDataBlocks[i] = 0;
        channel->mQueueAttr.mDataBlockSizes[i] = 0;
        i++;
        for (j = 0; j < lbl_803A6C24.mBankUserDataCallbackCount; j++) {
            lbl_803A6C24.mBankUserDataCallbacks[j](&message);
        }
    }
    STREAM_release(channel->mpTap, chunk);
    request->mDataRate = SNDSTRMI_calcdatarate(&channel->mQueueFormat);
    if (memcmp(&channel->mFormat, &channel->mQueueFormat, sizeof(SndSampleFormat_t)) != 0
        || memcmp(&channel->mAttr, &channel->mQueueAttr, sizeof(SndSampleAttr_t)) != 0
        || channel->mQueueAttr.m18[0] != 0) {
        if (channel->mFormat.mRate != 0) {
            channel->mState = 2;
            return 0;
        }
        channel->mFormat = channel->mQueueFormat;
        channel->mAttr = channel->mQueueAttr;
        channel->mQueueAttr.m18[0] = 0;
    }
    if (channel->mState != 1) {
        SNDSTRMI_startstream(channel);
        channel->mState = 1;
    }
    return 0;
}

void SNDSTRMI_parsedata(SndStreamChannel_t *channel, SndStreamChunk_t *chunk)
{
    SndStreamRequest_t *request = channel->mpCurrent;
    SndStreamDataChunk_t *data = (SndStreamDataChunk_t *)chunk;
    SndPacket_t packet;
    unsigned char *samples;
    int i;

    if (request->unk_0x25[0]) {
        packet.mFrames = data->mFrames;
    } else {
        packet.mFrames = data->mFrames;
    }
    samples = (unsigned char *)&data->mOffsets[channel->mFormat.mChannels];
    for (i = 0; i < channel->mFormat.mChannels; i++) {
        if (request->unk_0x25[0]) {
            packet.mChannelData[i] = samples + data->mOffsets[i];
        } else {
            packet.mChannelData[i] = samples + data->mOffsets[i];
        }
    }
    if (packet.mFrames == 0) {
        STREAM_release(channel->mpTap, chunk);
        return;
    }
    ((SndStreamChunk_t **)packet.mChannelData[0])[-1] = chunk;
    chunk->mId = request->mId;
    request->unk_0x1C += packet.mFrames;
    packet.mLast = request->mActive;
    SNDPKTPLAY_submit(channel->mBuffer, &packet);
    request->mActive = 1;
}

int SNDSTRMI_parsechunk(int stream, SndStreamChunk_t *chunk)
{
    SndStreamChannel_t *channel = lbl_803A7648[stream];

    if (chunk->mId == 0x5343446C) {
        SNDSTRMI_parsedata(channel, chunk);
    } else if (chunk->mId == 0x5343486C) {
        SNDSTRMI_parseheader(stream, chunk);
        return 0;
    } else {
        STREAM_release(channel->mpTap, chunk);
    }
    return 1;
}

int SNDSTRMI_isheld(SndStreamChannel_t *channel)
{
    SndStreamRequest_t *request = channel->mpCurrent;
    unsigned int buffered;

    if (request != 0 && request->mDataRate != 0) {
        if (request->mHold < 0) {
            return 1;
        }
        if (request->mHold != 0) {
            buffered = STREAM_gettable(channel->mpTap);
            if (buffered > 4000000) {
                buffered = 4000000;
            }
            if (buffered * 1000 / request->mDataRate >= (unsigned int)request->mHold
                || STREAM_state(channel->mpTap) == 2) {
                request->mHold = 0;
                return 0;
            }
            if (channel->mFreeRequests.mCount > 0 || STREAM_state(channel->mpTap) != 0) {
                return 1;
            }
            request->mHold = 0;
        }
    }
    return 0;
}

void SNDSTRMI_service(void)
{
    SndStreamChannel_t *channel;
    SndStreamChunk_t *chunk;
    int stream;
    int count;
    int more;

    SNDSYS_entercritical();
    for (stream = 0; stream < lbl_803A6C24.m1C.m22; stream++) {
        channel = lbl_803A7648[stream];
        if (channel == 0 || channel->mRequests.mCount == 0) {
            continue;
        }
        if (channel->mState == 2) {
            if (SNDPKTPLAY_framesoutstanding(channel->mBuffer) > 0) {
                continue;
            }
            channel->mFormat = channel->mQueueFormat;
            channel->mAttr = channel->mQueueAttr;
            channel->mQueueAttr.m18[0] = 0;
            SNDPKTPLAY_stop(channel->mBuffer);
            SNDSTRMI_startstream(channel);
        }
        if (SNDSTRMI_isheld(channel) != 0) {
            continue;
        }
        if (channel->mState == 1) {
            count = SNDPKTPLAY_submitspace(channel->mBuffer);
            if (count <= 0) {
                continue;
            }
        } else {
            count = 8;
        }
        more = 0;
        do {
            count--;
            chunk = STREAM_get(channel->mpTap);
            if (chunk != 0) {
                more = SNDSTRMI_parsechunk(stream, chunk);
            }
        } while (more != 0 && count > 0);
    }
    SNDSYS_leavecritical();
}

int SNDSTRMI_numcreated(void)
{
    int count = 0;
    int i;

    for (i = 0; i < lbl_803A6C24.m1C.m22; i++) {
        if (lbl_803A7648[i] != 0) {
            count++;
        }
    }
    return count;
}

extern "C" int SNDPKTPLAY_create(SndPacketReleaseFn_t release, SndPacketFramesDoneFn_t callback,
                                 void *context, void *memory, unsigned int size);

int fn_8026DE00(void *opts, int numRequests, int numPackets, void *memory, int size, int tap, int shared)
{
    SndStreamChannel_t *channel;
    SndStreamRequest_t *requests;
    unsigned char *player;
    unsigned char *p;
    float *fxlevels;
    void *stap;
    int stream = 0;
    int id;
    int n;
    int i;
    float vol;

    SNDSYS_entercritical();
    for (; stream < lbl_803A6C24.m1C.m22; stream++) {
        if (lbl_803A7648[stream] == 0) {
            goto found;
        }
    }
    SNDSYS_leavecritical();
    return -9;

found:
    channel = (SndStreamChannel_t *)memory;
    fxlevels = (float *)(channel + 1);
    p = (unsigned char *)memory + sizeof(SndStreamChannel_t) + lbl_8030002C * sizeof(float);
    size = size - sizeof(SndStreamChannel_t) - lbl_8030002C * sizeof(float);
    id = stream;
    memset(channel, 0, sizeof(SndStreamChannel_t));
    requests = (SndStreamRequest_t *)p;
    p += numRequests * sizeof(SndStreamRequest_t);
    size -= numRequests * sizeof(SndStreamRequest_t);
    player = p;
    n = SNDPKTPLAY_overhead(numPackets);
    size -= n;
    p += n;
    SNDLINKI_init(&channel->mRequests);
    SNDLINKI_init(&channel->mFreeRequests);
    for (i = 0; i < numRequests; i++) {
        SNDLINKI_push(&channel->mFreeRequests, &requests[i].mLink);
    }
    channel->mBuffer =
        SNDPKTPLAY_create(SNDSTRMI_releasecallback, SNDSTRMI_framescallback, channel, player,
                          SNDPKTPLAY_overhead(numPackets));
    if (channel->mBuffer < 0) {
        SNDSYS_leavecritical();
        return channel->mBuffer;
    }
    if (shared != 0) {
        channel->mpTap = (void *)tap;
        channel->mSharedTap = 1;
    } else {
        stap = STREAM_create(numRequests + 2, 1, 1, p, size);
        if (stap == 0) {
            SNDPKTPLAY_destroy(channel->mBuffer);
            SNDSYS_leavecritical();
            return -9;
        }
        channel->mpTap = stap;
        channel->mSharedTap = shared;
    }
    channel->mNextId = 0;
    channel->mVoice = -1;
    *(SndPlayOpts_t *)channel->unk_0xEC = *(SndPlayOpts_t *)opts;
    channel->mpFxLevels = fxlevels;
    for (i = 0; i < lbl_8030002C; i++) {
        channel->mpFxLevels[i] = (signed char)((SndPlayOpts_t *)channel->unk_0xEC)->m5 * (1.0f / 127.0f);
    }
    vol = (signed char)((SndPlayOpts_t *)opts)->m0 * (1.0f / 127.0f);
    for (i = 0; i <= 5; i++) {
        SndStreamSpeaker_t *speaker = &channel->mSpeakers[i];

        speaker->mIndex = i;
        speaker->mAzimuthOn = 0;
        speaker->mVolume = vol;
        speaker->mAzimuth = -1000000.0f;
    }
    channel->mPanned = 1;
    if (SNDSTRMI_numcreated() == 0) {
        iSNDserveraddclient(SNDSTRMI_service);
        lbl_803A6C24.m1C8 = (void (*)(void))SNDSTRMI_destroyall;
    }
    lbl_803A7648[id] = channel;
    if (shared == 0) {
        SNDSTRM_setgreedylevel(id, STREAM_buffersize(channel->mpTap) / 3);
    }
    channel->mQueueAttr.m18[0] = 0;
    SNDSTRM_purge(id);
    SNDSYS_leavecritical();
    return id;
}

int SNDSTRMI_queue(int stream, int hold, char *name, int offset, int type)
{
    SndStreamChannel_t *channel;
    SndStreamRequest_t *request;
    int id;

    channel = SNDSTRMI_getstreamptr(stream);
    if (channel == 0) {
        return -8;
    }
    if (channel->mFreeRequests.mCount == 0) {
        return -13;
    }
    if (type == 0) {
        offset = STREAM_queuefile(channel->mpTap, name, offset, 0x6C454353);
    } else if (type == 1) {
        offset = STREAM_queuemem(channel->mpTap, name, 0, 0x6C454353);
    }
    if (offset == 0) {
        return -1;
    }
    SNDSYS_entercritical();
    request = (SndStreamRequest_t *)SNDLINKI_pop(&channel->mFreeRequests);
    memset(request, 0, sizeof(SndStreamRequest_t));
    SNDLINKI_pushtail(&channel->mRequests, &request->mLink);
    request->mData = offset;
    channel->mNextId += 256;
    if (channel->mNextId < 0) {
        channel->mNextId = 0;
    }
    request->mId = channel->mNextId | stream;
    request->mHold = hold;
    id = request->mId;
    SNDSYS_leavecritical();
    return id;
}

extern "C" {

int SNDSTRM_create(SndPlayOpts_t *opts, int a, int b, void *memory, int size)
{
    return fn_8026DE00(opts, a, b, memory, size, 0, 0);
}

int SNDSTRM_destroy(int stream)
{
    SndStreamChannel_t *channel;
    void *tap;
    int shared;

    SNDSYS_entercritical();
    channel = SNDSTRMI_getstreamptr(stream);
    if (channel == 0) {
        SNDSYS_leavecritical();
        return -8;
    }
    SNDSTRM_purge(stream);
    Snd::StreamRemoveFaders(channel);
    if (SNDSTRMI_numcreated() == 1) {
        iSNDserverremoveclient(SNDSTRMI_service);
        lbl_803A6C24.m1C8 = 0;
    }
    SNDPKTPLAY_destroy(channel->mBuffer);
    tap = channel->mpTap;
    shared = channel->mSharedTap;
    lbl_803A7648[stream] = 0;
    SNDSYS_leavecritical();
    if (shared == 0) {
        STREAM_destroy(tap);
    }
    return 0;
}

int SNDSTRM_queuefile(int stream, int hold, char *name, int offset)
{
    return SNDSTRMI_queue(stream, hold, name, offset, 0);
}

int SNDSTRM_purge(int stream)
{
    SndStreamChannel_t *channel;
    SndLinkNode_t *link;
    int i;

    SNDSYS_entercritical();
    channel = SNDSTRMI_getstreamptr(stream);
    if (channel == 0) {
        SNDSYS_leavecritical();
        return -8;
    }
    if (channel->mVoice >= 0) {
        SNDPKTPLAY_stop(channel->mBuffer);
    }
    channel->mVoice = -1;
    if (channel->mSharedTap == 0) {
        STREAM_kill(channel->mpTap);
    }
    if (channel->mQueueAttr.m18[0] != 0) {
        for (i = 0; i < channel->mQueueFormat.mChannels; i++) {
            SNDMEMI_free(channel->mQueueAttr.m18[i]);
        }
    }
    do {
        link = SNDLINKI_pop(&channel->mRequests);
        if (link != 0) {
            SNDLINKI_push(&channel->mFreeRequests, link);
        }
    } while (link != 0);
    channel->mpCurrent = 0;
    channel->mState = 0;
    memset(&channel->mFormat, 0, sizeof(SndSampleFormat_t));
    memset(&channel->mQueueFormat, 0, sizeof(SndSampleFormat_t));
    memset(&channel->mAttr, 0, sizeof(SndSampleAttr_t));
    memset(&channel->mQueueAttr, 0, sizeof(SndSampleAttr_t));
    SNDSYS_leavecritical();
    return 0;
}

}
