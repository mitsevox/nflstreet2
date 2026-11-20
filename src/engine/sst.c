/* Sound stream channel core (sst.c): creates and destroys the stream channels, queues file and
   request-id streams on them, parses the stream chunks the stream taps deliver (headers and sample
   data), starts the packet player voice of a parsed stream and services every channel at 100 Hz. */

#include "engine/sndstrm.h"

extern "C" {

extern SndStreamChannel_t *lbl_803A7648[];

void *memset(void *dest, int ch, unsigned int count);
int STREAM_queuefile(void *tap, char *name, int offset, int tag);
int STREAM_queuemem(void *tap, char *name, int offset, int tag);
void STREAM_release(void *tap, void *chunk);
void STREAM_destroy(void *tap);
void STREAM_kill(void *tap);
void fn_8027929C(int buffer);
void fn_802791FC(int buffer);
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

extern "C" {
void fn_8026D790(int stream, SndStreamChunk_t *chunk);
void fn_8026D9CC(SndStreamChannel_t *channel, SndStreamChunk_t *chunk);
void fn_8026DC38(void);
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

int SNDSTRMI_parsechunk(int stream, SndStreamChunk_t *chunk)
{
    SndStreamChannel_t *channel = lbl_803A7648[stream];

    if (chunk->mId == 0x5343446C) {
        fn_8026D9CC(channel, chunk);
    } else if (chunk->mId == 0x5343486C) {
        fn_8026D790(stream, chunk);
        return 0;
    } else {
        STREAM_release(channel->mpTap, chunk);
    }
    return 1;
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
        iSNDserverremoveclient(fn_8026DC38);
        lbl_803A6C24.m1C8 = 0;
    }
    fn_8027929C(channel->mBuffer);
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
        fn_802791FC(channel->mBuffer);
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
    channel->mState = 0;
    channel->mpCurrent = 0;
    memset(&channel->mFormat, 0, sizeof(SndSampleFormat_t));
    memset(&channel->mQueueFormat, 0, sizeof(SndSampleFormat_t));
    memset(&channel->mAttr, 0, sizeof(SndSampleAttr_t));
    memset(&channel->mQueueAttr, 0, sizeof(SndSampleAttr_t));
    SNDSYS_leavecritical();
    return 0;
}

}
