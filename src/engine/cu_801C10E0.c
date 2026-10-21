#include "game/fn_801D2B7C.h"
#include "engine/fn_801EFD2C.h"
#include "engine/fn_801F8014.h"

typedef struct Request_801C10E0 {
    void *mArchive;
    int mId;
    void *mContext;
    int mSlot;
    unsigned char mState;
} Request_801C10E0;

typedef void (*Callback_801C1260)(int loader, int a, void *context);

typedef struct Loader_801C1260 {
    Callback_801C1260 mCallback;
    unsigned char *mSlotStates;
    void **mBuffers;
    Request_801C10E0 *mRequests;
    int mId;
    int mHeap;
    int mBufferCount;
    int mSize;
    int mRequestCount;
    int mUnknown24;
    volatile unsigned char mState;
} Loader_801C1260;

extern Lock_801F8014 lbl_803D4F98;
extern int lbl_803EBBC0;
extern Loader_801C1260 *lbl_803EBBC4;
extern unsigned char lbl_803EBBC8;
extern volatile int lbl_803EBBCC;


void fn_801C1448(int a, int b, int c, int d, Loader_801C1260 *loader);
void fn_801C1564(Loader_801C1260 *loader);

void fn_801C10E0(Loader_801C1260 *loader, int index)
{
    fn_801F8014(&lbl_803D4F98);
    for (index++; index < loader->mRequestCount; index++)
        loader->mRequests[index - 1] = loader->mRequests[index];
    loader->mRequests[loader->mRequestCount - 1].mState = 0;
    fn_801F809C(&lbl_803D4F98);
}

int fn_801C1198(Loader_801C1260 *loader, void *buffer)
{
    int i;

    fn_801F8014(&lbl_803D4F98);
    for (i = 0; i < loader->mBufferCount && loader->mBuffers[i] != buffer; i++)
        ;
    fn_801F809C(&lbl_803D4F98);
    return i;
}

int fn_801C1218(Loader_801C1260 *loader)
{
    int i;

    for (i = 0; i < loader->mBufferCount && (loader->mSlotStates[i] & 6); i++)
        ;
    return i;
}

int fn_801C1260(Loader_801C1260 *loader, int heap, int count, int size, int a,
                Callback_801C1260 callback)
{
    int result = 0;
    int i;

    fn_801F8014(&lbl_803D4F98);
    memset(loader, 0, sizeof(Loader_801C1260));
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
    loader->mRequests = fn_801D2B7C(i * 2 * sizeof(Request_801C10E0), 0, 0);
    if (loader->mRequests == 0)
        goto fail;
    memset(loader->mRequests, 0, i * 2 * sizeof(Request_801C10E0));
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
    fn_801F809C(&lbl_803D4F98);
    return result;
}

void fn_801C1448(int a, int b, int c, int d, Loader_801C1260 *loader)
{
    Request_801C10E0 request;

    fn_801F8014(&lbl_803D4F98);
    request = loader->mRequests[0];
    fn_801C10E0(loader, 0);
    if (!(request.mState & 4)) {
        loader->mSlotStates[request.mSlot] |= 1;
        if (loader->mCallback != 0) {
            fn_801F809C(&lbl_803D4F98);
            loader->mCallback(loader->mId, c, request.mContext);
            fn_801F8014(&lbl_803D4F98);
        }
    }
    loader->mState &= ~2;
    loader->mSlotStates[request.mSlot] &= ~2;
    fn_801F809C(&lbl_803D4F98);
    fn_801C1564(loader);
    fn_801F8014(&lbl_803D4F98);
    lbl_803EBBCC--;
    fn_801F809C(&lbl_803D4F98);
}

void fn_801C1564(Loader_801C1260 *loader)
{
    Request_801C10E0 *request = 0;
    int slot = 0;
    int issue = 0;

    fn_801F8014(&lbl_803D4F98);
    if ((loader->mState & 1) && !(loader->mState & 2)) {
        request = loader->mRequests;
        if (request->mState == 1) {
            slot = fn_801C1218(loader);
            if (slot < loader->mBufferCount) {
                issue = 1;
                loader->mState |= 2;
                request->mState |= 2;
                loader->mSlotStates[slot] |= 2;
                request->mSlot = slot;
            }
        }
    }
    fn_801F809C(&lbl_803D4F98);
    if (issue)
        fn_801EFD2C(request->mArchive, request->mId, loader->mHeap, loader->mBuffers[slot],
                    loader->mUnknown24, fn_801C1448, loader);
}

void fn_801C1654(Loader_801C1260 *loader)
{
    int i;

    fn_801F8014(&lbl_803D4F98);
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
    fn_801F809C(&lbl_803D4F98);
}

void fn_801C1710(int count)
{
    int i;

    fn_801F7FA8(&lbl_803D4F98);
    fn_801F8014(&lbl_803D4F98);
    lbl_803EBBC8 = 0;
    lbl_803EBBCC = 0;
    lbl_803EBBC0 = count;
    lbl_803EBBC4 = fn_801D2B7C(count * sizeof(Loader_801C1260), 0, 0);
    memset(lbl_803EBBC4, 0, count * sizeof(Loader_801C1260));
    for (i = 0; i < count; i++)
        lbl_803EBBC4[i].mState = 0;
    fn_801F809C(&lbl_803D4F98);
}

void fn_801C17BC(void)
{
    int i;

    lbl_803EBBC8 = 1;
    for (;;) {
        if (lbl_803EBBCC == 0) {
            fn_801F8014(&lbl_803D4F98);
            for (i = 0; i < lbl_803EBBC0; i++) {
                if (lbl_803EBBC4[i].mState)
                    fn_801C1654(&lbl_803EBBC4[i]);
            }
            fn_801D2BD0(lbl_803EBBC4);
            lbl_803EBBC8 = 0;
            lbl_803EBBC0 = 0;
            lbl_803EBBC4 = 0;
            fn_801F809C(&lbl_803D4F98);
            fn_801F80D0(&lbl_803D4F98);
            return;
        }
    }
}

int fn_801C1870(int heap, int count, int size, int a, Callback_801C1260 callback)
{
    int i;

    fn_801F8014(&lbl_803D4F98);
    for (i = 0; i < lbl_803EBBC0 && lbl_803EBBC4[i].mState != 0; i++)
        ;
    if (i < lbl_803EBBC0 && fn_801C1260(&lbl_803EBBC4[i], heap, count, size, a, callback))
        lbl_803EBBC4[i].mId = i;
    else
        i = -1;
    fn_801F809C(&lbl_803D4F98);
    return i;
}

void fn_801C1950(int id, void *archive, int index, void *context)
{
    Loader_801C1260 *loader = 0;
    int queued = 0;

    fn_801F8014(&lbl_803D4F98);
    if (!lbl_803EBBC8) {
        int i;

        loader = &lbl_803EBBC4[id];
        for (i = 0; i < loader->mRequestCount && loader->mRequests[i].mState != 0; i++)
            ;
        if (i < loader->mRequestCount) {
            lbl_803EBBCC++;
            queued = 1;
            loader->mRequests[i].mArchive = archive;
            loader->mRequests[i].mId = index;
            loader->mRequests[i].mContext = context;
            loader->mRequests[i].mState |= 1;
        }
    }
    fn_801F809C(&lbl_803D4F98);
    if (queued)
        fn_801C1564(loader);
}

void fn_801C1A60(int id)
{
    Loader_801C1260 *loader;
    int i;

    fn_801F8014(&lbl_803D4F98);
    loader = &lbl_803EBBC4[id];
    for (i = 0; i < loader->mRequestCount; i++) {
        if (loader->mRequests[i].mState) {
            if (loader->mRequests[i].mState & 2) {
                loader->mRequests[i].mState |= 4;
            } else {
                fn_801C10E0(loader, i);
                i--;
                lbl_803EBBCC--;
            }
        }
    }
    fn_801F809C(&lbl_803D4F98);
}

void fn_801C1B1C(int id, void *buffer)
{
    Loader_801C1260 *loader;
    int slot;

    fn_801F8014(&lbl_803D4F98);
    loader = &lbl_803EBBC4[id];
    slot = fn_801C1198(loader, buffer);
    if (slot < loader->mBufferCount)
        loader->mSlotStates[slot] |= 4;
    fn_801F809C(&lbl_803D4F98);
}

void fn_801C1B90(int id, void *buffer)
{
    Loader_801C1260 *loader;
    int released = 0;
    int slot;

    fn_801F8014(&lbl_803D4F98);
    loader = &lbl_803EBBC4[id];
    slot = fn_801C1198(loader, buffer);
    if (slot < loader->mBufferCount) {
        released = 1;
        loader->mSlotStates[slot] &= ~4;
    }
    fn_801F809C(&lbl_803D4F98);
    if (released)
        fn_801C1564(loader);
}

void fn_801C1C1C(int id)
{
    Loader_801C1260 *loader;
    int i;

    fn_801F8014(&lbl_803D4F98);
    loader = &lbl_803EBBC4[id];
    for (i = 0; i < loader->mBufferCount; i++)
        loader->mSlotStates[i] &= ~4;
    fn_801F809C(&lbl_803D4F98);
    fn_801C1564(loader);
}
