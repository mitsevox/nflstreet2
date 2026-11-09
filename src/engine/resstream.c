/* Buffered resource streaming: queues reads of resource file entries and loads
   them in the background into a small pool of buffers, which the caller holds
   while it uses them and then releases for the next read (used to stream
   textures in). */

#include "game/fn_801D2B7C.h"
#include "engine/ResCopyAsyncToBuffer.h"
#include "engine/fn_801F8014.h"

typedef struct ResStreamRequest_t {
    void *mArchive;
    int mId;
    void *mContext;
    int mSlot;
    unsigned char mState;
} ResStreamRequest_t;

typedef void (*ResStreamCallback_t)(int loader, int a, void *context);

typedef struct ResStream_t {
    ResStreamCallback_t mCallback;
    unsigned char *mSlotStates;
    void **mBuffers;
    ResStreamRequest_t *mRequests;
    int mId;
    int mHeap;
    int mBufferCount;
    int mSize;
    int mRequestCount;
    int mUnknown24;
    volatile unsigned char mState;
} ResStream_t;

extern Lock_801F8014 _ResStream_Lock;
extern int _ResStream_iNumStreams;
extern ResStream_t *_ResStream_pStreams;
extern unsigned char _ResStream_bShutdown;
extern volatile int _ResStream_iNumPending;


void ResStreamReadDone(int a, int b, int c, int d, ResStream_t *loader);
void ResStreamStartNextRead(ResStream_t *loader);

void ResStreamRemoveRequest(ResStream_t *loader, int index)
{
    fn_801F8014(&_ResStream_Lock);
    for (index++; index < loader->mRequestCount; index++)
        loader->mRequests[index - 1] = loader->mRequests[index];
    loader->mRequests[loader->mRequestCount - 1].mState = 0;
    fn_801F809C(&_ResStream_Lock);
}

int ResStreamFindBuffer(ResStream_t *loader, void *buffer)
{
    int i;

    fn_801F8014(&_ResStream_Lock);
    for (i = 0; i < loader->mBufferCount && loader->mBuffers[i] != buffer; i++)
        ;
    fn_801F809C(&_ResStream_Lock);
    return i;
}

int ResStreamFindFreeBuffer(ResStream_t *loader)
{
    int i;

    for (i = 0; i < loader->mBufferCount && (loader->mSlotStates[i] & 6); i++)
        ;
    return i;
}

int ResStreamCreate(ResStream_t *loader, int heap, int count, int size, int a,
                ResStreamCallback_t callback)
{
    int result = 0;
    int i;

    fn_801F8014(&_ResStream_Lock);
    memset(loader, 0, sizeof(ResStream_t));
    loader->mSlotStates = fn_801D2B7C(count, 0, 0);
    if (loader->mSlotStates == 0)
        goto fail;
    memset(loader->mSlotStates, 0, count);
    loader->mBuffers = fn_801D2B7C(count * sizeof(void *), 0, 0);
    if (loader->mBuffers == 0)
        goto fail;
    memset(loader->mBuffers, 0, count * sizeof(void *));
    for (i = 0; i < count; i++) {
        loader->mBuffers[i] = fn_801D2BB0(heap, size, 0, 0);
        if (loader->mBuffers[i] == 0)
            break;
    }
    if (i != count)
        goto fail;
    loader->mRequests = fn_801D2B7C(i * 2 * sizeof(ResStreamRequest_t), 0, 0);
    if (loader->mRequests == 0)
        goto fail;
    memset(loader->mRequests, 0, i * 2 * sizeof(ResStreamRequest_t));
    loader->mHeap = heap;
    loader->mSize = size;
    loader->mRequestCount = i * 2;
    loader->mUnknown24 = a;
    loader->mCallback = callback;
    loader->mState = 1;
    loader->mBufferCount = i;
    result = 1;
fail:
    if (!result) {
        if (loader->mSlotStates != 0)
            fn_801D2BD0(loader->mSlotStates);
        if (loader->mBuffers != 0) {
            for (i = 0; i < count; i++) {
                if (loader->mBuffers[i] != 0)
                    fn_801D2BD0(loader->mBuffers[i]);
            }
            fn_801D2BD0(loader->mBuffers);
        }
        if (loader->mRequests != 0)
            fn_801D2BD0(loader->mRequests);
    }
    fn_801F809C(&_ResStream_Lock);
    return result;
}

void ResStreamReadDone(int a, int b, int c, int d, ResStream_t *loader)
{
    ResStreamRequest_t request;

    fn_801F8014(&_ResStream_Lock);
    request = loader->mRequests[0];
    ResStreamRemoveRequest(loader, 0);
    if (!(request.mState & 4)) {
        loader->mSlotStates[request.mSlot] |= 1;
        if (loader->mCallback != 0) {
            fn_801F809C(&_ResStream_Lock);
            loader->mCallback(loader->mId, c, request.mContext);
            fn_801F8014(&_ResStream_Lock);
        }
    }
    loader->mState &= ~2;
    loader->mSlotStates[request.mSlot] &= ~2;
    fn_801F809C(&_ResStream_Lock);
    ResStreamStartNextRead(loader);
    fn_801F8014(&_ResStream_Lock);
    _ResStream_iNumPending--;
    fn_801F809C(&_ResStream_Lock);
}

void ResStreamStartNextRead(ResStream_t *loader)
{
    ResStreamRequest_t *request = 0;
    int slot = 0;
    int issue = 0;

    fn_801F8014(&_ResStream_Lock);
    if ((loader->mState & 1) && !(loader->mState & 2)) {
        request = loader->mRequests;
        if (request->mState == 1) {
            slot = ResStreamFindFreeBuffer(loader);
            if (slot < loader->mBufferCount) {
                issue = 1;
                loader->mState |= 2;
                request->mState |= 2;
                loader->mSlotStates[slot] |= 2;
                request->mSlot = slot;
            }
        }
    }
    fn_801F809C(&_ResStream_Lock);
    if (issue)
        ResCopyAsyncToBuffer(request->mArchive, request->mId, loader->mHeap, loader->mBuffers[slot],
                    loader->mUnknown24, ResStreamReadDone, loader);
}

void ResStreamDestroy(ResStream_t *loader)
{
    int i;

    fn_801F8014(&_ResStream_Lock);
    for (i = 0; i < loader->mBufferCount; i++) {
        if (!(loader->mState & 8) || !(loader->mSlotStates[i] & 4))
            fn_801D2BD0(loader->mBuffers[i]);
    }
    fn_801D2BD0(loader->mSlotStates);
    loader->mSlotStates = 0;
    fn_801D2BD0(loader->mBuffers);
    loader->mBuffers = 0;
    fn_801D2BD0(loader->mRequests);
    loader->mRequests = 0;
    loader->mState = 0;
    fn_801F809C(&_ResStream_Lock);
}

void ResStreamInit(int count)
{
    int i;

    fn_801F7FA8(&_ResStream_Lock);
    fn_801F8014(&_ResStream_Lock);
    _ResStream_bShutdown = 0;
    _ResStream_iNumPending = 0;
    _ResStream_iNumStreams = count;
    _ResStream_pStreams = fn_801D2B7C(count * sizeof(ResStream_t), 0, 0);
    memset(_ResStream_pStreams, 0, count * sizeof(ResStream_t));
    for (i = 0; i < count; i++)
        _ResStream_pStreams[i].mState = 0;
    fn_801F809C(&_ResStream_Lock);
}

void ResStreamShutdown(void)
{
    int i;

    _ResStream_bShutdown = 1;
    for (;;) {
        if (_ResStream_iNumPending == 0) {
            fn_801F8014(&_ResStream_Lock);
            for (i = 0; i < _ResStream_iNumStreams; i++) {
                if (_ResStream_pStreams[i].mState)
                    ResStreamDestroy(&_ResStream_pStreams[i]);
            }
            fn_801D2BD0(_ResStream_pStreams);
            _ResStream_bShutdown = 0;
            _ResStream_iNumStreams = 0;
            _ResStream_pStreams = 0;
            fn_801F809C(&_ResStream_Lock);
            fn_801F80D0(&_ResStream_Lock);
            return;
        }
    }
}

int ResStreamOpen(int heap, int count, int size, int a, ResStreamCallback_t callback)
{
    int i;

    fn_801F8014(&_ResStream_Lock);
    for (i = 0; i < _ResStream_iNumStreams && _ResStream_pStreams[i].mState != 0; i++)
        ;
    if (i < _ResStream_iNumStreams && ResStreamCreate(&_ResStream_pStreams[i], heap, count, size, a, callback))
        _ResStream_pStreams[i].mId = i;
    else
        i = -1;
    fn_801F809C(&_ResStream_Lock);
    return i;
}

void ResStreamQueueRead(int id, void *archive, int index, void *context)
{
    ResStream_t *loader = 0;
    int queued = 0;

    fn_801F8014(&_ResStream_Lock);
    if (!_ResStream_bShutdown) {
        int i;

        loader = &_ResStream_pStreams[id];
        for (i = 0; i < loader->mRequestCount && loader->mRequests[i].mState != 0; i++)
            ;
        if (i < loader->mRequestCount) {
            _ResStream_iNumPending++;
            queued = 1;
            loader->mRequests[i].mArchive = archive;
            loader->mRequests[i].mId = index;
            loader->mRequests[i].mContext = context;
            loader->mRequests[i].mState |= 1;
        }
    }
    fn_801F809C(&_ResStream_Lock);
    if (queued)
        ResStreamStartNextRead(loader);
}

void ResStreamCancelReads(int id)
{
    ResStream_t *loader;
    int i;

    fn_801F8014(&_ResStream_Lock);
    loader = &_ResStream_pStreams[id];
    for (i = 0; i < loader->mRequestCount; i++) {
        if (loader->mRequests[i].mState) {
            if (loader->mRequests[i].mState & 2) {
                loader->mRequests[i].mState |= 4;
            } else {
                ResStreamRemoveRequest(loader, i);
                i--;
                _ResStream_iNumPending--;
            }
        }
    }
    fn_801F809C(&_ResStream_Lock);
}

void ResStreamHoldBuffer(int id, void *buffer)
{
    ResStream_t *loader;
    int slot;

    fn_801F8014(&_ResStream_Lock);
    loader = &_ResStream_pStreams[id];
    slot = ResStreamFindBuffer(loader, buffer);
    if (slot < loader->mBufferCount)
        loader->mSlotStates[slot] |= 4;
    fn_801F809C(&_ResStream_Lock);
}

void ResStreamReleaseBuffer(int id, void *buffer)
{
    ResStream_t *loader;
    int released = 0;
    int slot;

    fn_801F8014(&_ResStream_Lock);
    loader = &_ResStream_pStreams[id];
    slot = ResStreamFindBuffer(loader, buffer);
    if (slot < loader->mBufferCount) {
        released = 1;
        loader->mSlotStates[slot] &= ~4;
    }
    fn_801F809C(&_ResStream_Lock);
    if (released)
        ResStreamStartNextRead(loader);
}

void ResStreamReleaseAllBuffers(int id)
{
    ResStream_t *loader;
    int i;

    fn_801F8014(&_ResStream_Lock);
    loader = &_ResStream_pStreams[id];
    for (i = 0; i < loader->mBufferCount; i++)
        loader->mSlotStates[i] &= ~4;
    fn_801F809C(&_ResStream_Lock);
    ResStreamStartNextRead(loader);
}

void ResStreamClose(int id)
{
    ResStream_t *loader = &_ResStream_pStreams[id];

    for (;;) {
        if ((loader->mState & 2) || (loader->mState & 4))
            continue;
        fn_801F8014(&_ResStream_Lock);
        if (loader->mRequests[0].mState == 0) {
            loader->mState &= ~1;
            ResStreamDestroy(loader);
            fn_801F809C(&_ResStream_Lock);
            break;
        }
        if (loader->mRequests[0].mState == 1 && ResStreamFindFreeBuffer(loader) >= loader->mBufferCount)
            ResStreamCancelReads(id);
        fn_801F809C(&_ResStream_Lock);
    }
}
