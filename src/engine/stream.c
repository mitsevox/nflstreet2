#include "engine/Resource.h"
#include "engine/system.h"

#define STREAM_MAGIC 0x5354524D

#define CHUNK_WRAP -1
#define CHUNK_SKIP -2

typedef struct StreamChunk_801F5D84 {
    unsigned int mID;
    unsigned int mSize;
} StreamChunk_801F5D84;

typedef struct StreamFile_801F6D54 {
    Res_801EDC2C *pRes;
    unsigned int mIndex;
} StreamFile_801F6D54;

typedef struct StreamRequest_801F5EA4 {
    int mID;
    int mState;
    struct StreamRequest_801F5EA4 *pPrev;
    struct StreamRequest_801F5EA4 *pNext;
    int mType;
    StreamFile_801F6D54 mFile;
    unsigned int mFileSize;
    unsigned int mFileOffset;
    int mFileHandle;
    char *pMem;
    int mSize;
    unsigned int mEndMarker;
    char *pStart;
} StreamRequest_801F5EA4;

typedef struct StreamFilter_801F6074 {
    unsigned int mMask;
    unsigned int mValue;
    int mTap;
} StreamFilter_801F6074;

typedef struct StreamTap_801F5DA4 {
    struct Stream_801F5DA4 *pStream;
    int mIndex;
    int mBytes;
    char *pRead;
} StreamTap_801F5DA4;

typedef struct Stream_801F5DA4 {
    int mMagic;
    struct OSMutex *pMutex;
    StreamRequest_801F5EA4 *pRequests;
    int mNumRequests;
    StreamFilter_801F6074 *pFilters;
    int mNumFilters;
    StreamTap_801F5DA4 *pTaps;
    int mNumTaps;
    char *pBuffer;
    char *pWrap;
    char *pBufferEnd;
    int mState;
    int mPriority;
    int mGreedyPriority;
    int mGreedyLevel;
    int mGreedyState;
    int mUsed;
    char *pTail;
    char *pHead;
    char *pWrite;
    StreamRequest_801F5EA4 *pFirst;
    StreamRequest_801F5EA4 *pCurrent;
    StreamRequest_801F5EA4 *pLast;
    StreamRequest_801F5EA4 *pFree;
    StreamFile_801F6D54 mFile;
    unsigned int mFileSize;
    int mFileOffset;
    int mFileHandle;
    int mFilePos;
    int mReadHandle;
    int mReadSize;
    int mBlockSize;
} Stream_801F5DA4;

extern int fn_801C9844(int handle, int offset, unsigned int whence);
extern int fn_801C9B18(int handle, char *pBuffer, int size, int priority,
                       void (*pCallback)(int, int, void *), void *pContext);
extern int fn_801C9C88(int readHandle, int priority);
extern void fn_801C9D78(void);
extern void fn_801C9DA0(void);
extern void fn_801CAF24(void);
extern int fn_801CB120(void);
extern StreamFile_801F6D54 *fn_801F5000(StreamFile_801F6D54 *pFile);
extern struct OSMutex *fn_801F773C(void);
extern void fn_801F7764(struct OSMutex *pMutex);
extern void fn_801F778C(struct OSMutex *pMutex);
extern void fn_801F77B4(struct OSMutex *pMutex);

extern Lock_801F8014 lbl_8039B3D8;

extern unsigned int lbl_803ECFA0;

static void fn_801F6410(Stream_801F5DA4 *s, int priority);
static void fn_801F6540(Stream_801F5DA4 *s, int priority);
void fn_801F7208(StreamTap_801F5DA4 *h);
StreamChunk_801F5D84 *fn_801F73D4(StreamTap_801F5DA4 *h);
void fn_801F74D4(StreamTap_801F5DA4 *h, StreamChunk_801F5D84 *c);
void fn_801F6C78(StreamTap_801F5DA4 *h, int state);

static unsigned int fn_801F5D84(unsigned int value)
{
    return (value >> 24) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | (value << 24);
}

static int fn_801F5DA4(StreamTap_801F5DA4 *h, Stream_801F5DA4 **ps, StreamTap_801F5DA4 **pt)
{
    Stream_801F5DA4 *s;

    if (h == 0) {
        return 1;
    }
    s = h->pStream;
    if (s->mMagic != STREAM_MAGIC) {
        return 1;
    }
    *pt = h;
    *ps = s;
    return 0;
}

static int fn_801F5DE4(char *pStart, char *pEnd, char *p)
{
    if (pStart <= pEnd) {
        return p >= pStart && p < pEnd;
    }
    return p >= pStart || p < pEnd;
}

static void fn_801F5E24(Stream_801F5DA4 *s, int size)
{
    int used;
    int newUsed;

    fn_801F778C(s->pMutex);
    used = s->mUsed;
    newUsed = used - size;
    s->mUsed = newUsed;
    fn_801F77B4(s->pMutex);
    if (used >= s->mGreedyLevel && newUsed < s->mGreedyLevel) {
        s->mGreedyState = 1;
        if (s->mState == 1) {
            s->mReadHandle = fn_801C9C88(s->mReadHandle, s->mGreedyPriority);
        }
    }
}

static StreamRequest_801F5EA4 *fn_801F5EA4(Stream_801F5DA4 *s)
{
    StreamRequest_801F5EA4 *req = 0;

    fn_801F778C(s->pMutex);
    if (s->pFree) {
        req = s->pFree;
        s->pFree = req->pNext;
        lbl_803ECFA0 += 0x100;
        if (lbl_803ECFA0 == 0) {
            lbl_803ECFA0 = 0x100;
        }
        req->mID = (req->mID & 0xFF) | lbl_803ECFA0;
    }
    fn_801F77B4(s->pMutex);
    return req;
}

static void fn_801F5F28(Stream_801F5DA4 *s, StreamRequest_801F5EA4 *req)
{
    req->mState = 1;
    req->pNext = 0;
    fn_801F778C(s->pMutex);
    if (s->pLast == 0) {
        req->pPrev = 0;
        s->pFirst = req;
        s->pCurrent = req;
        s->pLast = req;
    } else {
        req->pPrev = s->pLast;
        s->pLast->pNext = req;
        s->pLast = req;
    }
    fn_801F77B4(s->pMutex);
}

static StreamRequest_801F5EA4 *fn_801F5FA4(Stream_801F5DA4 *s, int id)
{
    int index = id & 0xFF;
    StreamRequest_801F5EA4 *req;

    if (index >= s->mNumRequests) {
        return 0;
    }
    req = &s->pRequests[index];
    if (id != req->mID) {
        return 0;
    }
    if (req->mState == 0) {
        return 0;
    }
    return req;
}

static void fn_801F5FF4(Stream_801F5DA4 *s, StreamRequest_801F5EA4 *req)
{
    if (req == s->pFirst) {
        s->pFirst = req->pNext;
    } else {
        req->pPrev->pNext = req->pNext;
    }
    if (req == s->pLast) {
        s->pLast = req->pPrev;
    } else {
        req->pNext->pPrev = req->pPrev;
    }
    if (req == s->pCurrent) {
        s->pCurrent = req->pNext ? req->pNext : req->pPrev;
    }
    req->mState = 0;
    req->pNext = s->pFree;
    s->pFree = req;
}

static int fn_801F6074(Stream_801F5DA4 *s, StreamChunk_801F5D84 *c)
{
    unsigned int id = fn_801F5D84(c->mID);
    StreamFilter_801F6074 *f;
    int i;

    for (i = 0; i < s->mNumFilters; i++) {
        f = &s->pFilters[i];
        if ((id & f->mMask) == f->mValue) {
            return f->mTap;
        }
    }
    return -2;
}

static int fn_801F60F0(Stream_801F5DA4 *s)
{
    StreamRequest_801F5EA4 *req = s->pCurrent;
    StreamChunk_801F5D84 *c;
    unsigned int size;
    int tap;
    int cancelled;
    int pad;
    int used;
    StreamTap_801F5DA4 *t;

    while (s->pWrite - s->pHead > 7) {
        c = (StreamChunk_801F5D84 *)s->pHead;
        size = fn_801F5D84(c->mSize);
        if (size & 0xFF000000) {
            size = 8;
            c->mID = fn_801F5D84(req->mEndMarker);
            c->mSize = fn_801F5D84(8);
        }
        if ((unsigned int)(s->pHead + size) > (unsigned int)s->pWrite) {
            break;
        }
        if (fn_801F5D84(c->mID) == req->mEndMarker) {
            pad = (int)s->pHead & 31;
            size = ((size + pad + 31) & ~31) - pad;
        }
        tap = fn_801F6074(s, c);
        if (tap < 0) {
            fn_801F778C(s->pMutex);
            cancelled = req->mState == 4;
            if (!cancelled) {
                c->mID = fn_801F5D84(CHUNK_SKIP);
                s->pHead += size;
            }
            fn_801F77B4(s->pMutex);
        } else {
            c->mSize = fn_801F5D84(size | (tap << 24));
            fn_801F778C(s->pMutex);
            cancelled = req->mState == 4;
            if (!cancelled) {
                t = &s->pTaps[tap - 1];
                t->mBytes += size;
                if (t->mBytes == size) {
                    t->pRead = (char *)c;
                }
                used = s->mUsed;
                s->mUsed = used + size;
                s->pHead += size;
                if (used < s->mGreedyLevel && s->mUsed >= s->mGreedyLevel) {
                    s->mGreedyState = 0;
                }
            }
            fn_801F77B4(s->pMutex);
        }
        if (cancelled) {
            if (fn_801F5D84(c->mID) != req->mEndMarker) {
                pad = (int)s->pHead & 31;
                size = ((size + pad + 31) & ~31) - pad;
                c->mSize = fn_801F5D84(size | (tap << 24));
            }
            return 0;
        }
        if (fn_801F5D84(c->mID) == req->mEndMarker) {
            return 1;
        }
    }
    return 0;
}

static void fn_801F62F0(Stream_801F5DA4 *s)
{
    StreamRequest_801F5EA4 *req = s->pCurrent;
    int end;
    int found;

    if (req->mType == 1) {
        end = s->mReadSize + s->mFilePos >= req->mSize;
    } else {
        end = (unsigned int)(s->mReadSize + s->mFilePos) >= s->mFileSize;
    }
    s->mFilePos += s->mReadSize;
    s->pWrite += s->mReadSize;
    found = fn_801F60F0(s);
    if (req->mState == 4) {
        fn_801F6410(s, s->mGreedyPriority);
    } else if (end || found) {
        fn_801F778C(s->pMutex);
        if (req->mState != 4) {
            req->mState = 3;
        }
        fn_801F77B4(s->pMutex);
        fn_801F6410(s, s->mGreedyPriority);
    } else {
        fn_801F6540(s, s->mGreedyPriority - 1);
    }
}

static void fn_801F63EC(int a, int b, void *pContext)
{
    fn_801F62F0(pContext);
}

static void fn_801F6410(Stream_801F5DA4 *s, int priority)
{
    int idle;
    StreamRequest_801F5EA4 *req;

    fn_801F778C(s->pMutex);
    if (s->pCurrent == 0) {
        idle = 1;
    } else if (s->pCurrent->mState == 1) {
        idle = 0;
    } else if (s->pCurrent->pNext == 0) {
        idle = 1;
    } else {
        s->pCurrent = s->pCurrent->pNext;
        idle = 0;
    }
    if (idle) {
        req = 0;
        s->mState = 0;
    } else {
        req = s->pCurrent;
        req->pStart = s->pHead;
        req->mState = 2;
    }
    fn_801F77B4(s->pMutex);
    if (!idle) {
        s->pWrite = s->pHead;
        if (req->mType == 1) {
            s->mFilePos = 0;
        } else {
            s->mFilePos = req->mSize;
            if (req->mFile.pRes != s->mFile.pRes || req->mFile.mIndex != s->mFile.mIndex) {
                s->mFile.pRes = req->mFile.pRes;
                s->mFile.mIndex = req->mFile.mIndex;
                s->mFileSize = req->mFileSize;
                s->mFileOffset = req->mFileOffset;
                s->mFileHandle = req->mFileHandle;
                fn_801F6540(s, s->mGreedyPriority);
                return;
            }
        }
        fn_801F6540(s, priority);
    }
}

static void fn_801F6540(Stream_801F5DA4 *s, int priority)
{
    StreamChunk_801F5D84 *c;
    StreamRequest_801F5EA4 *req;
    int avail;
    int len;

    while (s->pTail != s->pHead) {
        c = (StreamChunk_801F5D84 *)s->pTail;
        if (fn_801F5D84(c->mID) == CHUNK_WRAP) {
            s->pTail = s->pWrap;
        } else if (fn_801F5D84(c->mID) == CHUNK_SKIP) {
            s->pTail += fn_801F5D84(c->mSize);
        } else {
            break;
        }
    }
    fn_801F778C(s->pMutex);
    for (;;) {
        req = s->pFirst;
        if (req->pNext == 0 || req->pNext->mState == 1) {
            break;
        }
        if (fn_801F5DE4(s->pTail, s->pWrite, req->pNext->pStart - 1)) {
            break;
        }
        fn_801F5FF4(s, req);
    }
    fn_801F77B4(s->pMutex);
    if ((unsigned int)s->pTail > (unsigned int)s->pWrite) {
        avail = s->pTail - s->pWrite - 33;
    } else {
        avail = s->pBufferEnd - s->pWrite - 32;
        if (avail < s->mBlockSize) {
            req = s->pCurrent;
            len = s->pWrite - s->pHead;
            if (req->mType == 1) {
                if (s->pTail - s->pWrap < len + 1) {
                    goto stall;
                }
            } else if (s->pTail - s->pWrap - 32 < len + 1) {
                goto stall;
            }
            if ((len & 31) == 0 || req->mType == 1) {
                s->pWrap = s->pBuffer;
            } else {
                s->pWrap = s->pBuffer - (len % 32 - 32);
            }
            memcpy(s->pWrap, s->pHead, len);
            c = (StreamChunk_801F5D84 *)s->pHead;
            c->mID = fn_801F5D84(CHUNK_WRAP);
            c->mSize = fn_801F5D84(8);
            s->pHead = s->pWrap;
            s->pWrite = s->pWrap + len;
            if (fn_801F5D84(((StreamChunk_801F5D84 *)s->pTail)->mID) == CHUNK_WRAP) {
                s->pTail = s->pWrap;
                avail = s->pBufferEnd - s->pWrite - 32;
            } else {
                avail = s->pTail - s->pWrite - 1;
            }
        }
    }
    if (avail < s->mBlockSize) {
    stall:
        s->mState = 2;
        return;
    }
    req = s->pCurrent;
    if (req->mType == 1) {
        if (s->mFilePos + avail > req->mSize) {
            s->mReadSize = req->mSize - s->mFilePos;
        } else {
            s->mReadSize = avail;
        }
        memcpy(s->pWrite, req->pMem, s->mReadSize);
        req->pMem += s->mReadSize;
        fn_801F62F0(s);
    } else {
        s->mReadSize = s->mBlockSize;
        if ((unsigned int)(s->mFilePos + s->mBlockSize) > s->mFileSize) {
            s->mReadSize = s->mFileSize - s->mFilePos;
        }
        fn_801C9D78();
        fn_801F8014(&lbl_8039B3D8);
        fn_801C9844(s->mFileHandle, s->mFileOffset + s->mFilePos, 0);
        s->mReadHandle = fn_801C9B18(s->mFileHandle, s->pWrite, s->mReadSize, priority, fn_801F63EC, s);
        fn_801F809C(&lbl_8039B3D8);
        fn_801C9DA0();
    }
}

int fn_801F685C(int numRequests, int numFilters, int numTaps)
{
    return sizeof(Stream_801F5DA4) + numRequests * sizeof(StreamRequest_801F5EA4) + numFilters * sizeof(StreamFilter_801F6074) +
           numTaps * sizeof(StreamTap_801F5DA4) + 32;
}

StreamTap_801F5DA4 *fn_801F687C(int numRequests, int numFilters, int numTaps, void *pMem, int memSize)
{
    Stream_801F5DA4 *s = pMem;
    int bufferSize = memSize - fn_801F685C(numRequests, numFilters, numTaps);
    StreamRequest_801F5EA4 *pRequests;
    StreamFilter_801F6074 *pFilters;
    StreamTap_801F5DA4 *pTaps;
    char *pBuffer;
    int i;

    if (bufferSize < 0x1800 || numRequests < 2 || numRequests > 256 || numFilters < 1 || numFilters > 16 ||
        numTaps <= 0 || numTaps > numFilters) {
        return 0;
    }
    s->mMagic = STREAM_MAGIC;
    s->pMutex = fn_801F773C();
    pRequests = (StreamRequest_801F5EA4 *)(s + 1);
    pFilters = (StreamFilter_801F6074 *)(pRequests + numRequests);
    pTaps = (StreamTap_801F5DA4 *)(pFilters + numFilters);
    pBuffer = (char *)(((unsigned int)(pTaps + numTaps) & ~31) + 32);
    s->pRequests = pRequests;
    s->mNumRequests = numRequests;
    s->pFilters = pFilters;
    s->mNumFilters = numFilters;
    s->pTaps = pTaps;
    s->mNumTaps = numTaps;
    s->pBuffer = pBuffer;
    s->pWrap = pBuffer;
    s->pBufferEnd = (char *)pMem + memSize;
    s->mState = 0;
    s->mPriority = 150;
    s->mGreedyPriority = 50;
    s->mGreedyLevel = 0;
    s->mGreedyState = 0;
    s->mUsed = 0;
    s->pTail = pBuffer;
    s->pHead = pBuffer;
    s->pWrite = pBuffer;
    s->pFirst = 0;
    s->pCurrent = 0;
    s->pLast = 0;
    s->pFree = pRequests;
    s->mFile.pRes = (Res_801EDC2C *)-1;
    s->mFile.mIndex = -1;
    s->mFileSize = 0;
    if (bufferSize <= 0x3FFF) {
        s->mBlockSize = 0x800;
    } else if (bufferSize <= 0x7FFF) {
        s->mBlockSize = 0x1000;
    } else if (bufferSize <= 0xFFFF) {
        s->mBlockSize = 0x2000;
    } else if (bufferSize <= 0x1FFFF) {
        s->mBlockSize = 0x4000;
    } else {
        s->mBlockSize = 0x8000;
    }
    for (i = 0; i < numRequests; i++) {
        s->pRequests[i].mID = i;
        s->pRequests[i].mState = 0;
        s->pRequests[i].pNext = &s->pRequests[i + 1];
    }
    s->pRequests[numRequests - 1].pNext = 0;
    for (i = 0; i < numFilters; i++) {
        s->pFilters[i].mMask = 0;
        s->pFilters[i].mTap = 1;
        s->pFilters[i].mValue = 0;
    }
    for (i = 0; i < numTaps; i++) {
        s->pTaps[i].pStream = s;
        s->pTaps[i].mBytes = 0;
        s->pTaps[i].mIndex = i + 1;
    }
    return s->pTaps;
}

void fn_801F6AC8(StreamTap_801F5DA4 *h, int index, unsigned int mask, unsigned int value, int tap)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamFilter_801F6074 *f;

    if (fn_801F5DA4(h, &s, &t) == 0 && index > 0 && index <= s->mNumFilters &&
        (index != s->mNumFilters || (mask | value) == 0) && (tap > 0 || tap == -1 || tap == -2) &&
        tap <= s->mNumTaps && s->mState == 0) {
        f = &s->pFilters[index - 1];
        f->mMask = mask;
        f->mValue = value;
        f->mTap = tap;
    }
}

void fn_801F6B84(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) == 0) {
        fn_801F7208(h);
        while (s->mState == 1) {
            if (fn_801CB120()) {
                fn_801CAF24();
            }
        }
        s->mMagic = 0;
        fn_801F7764(s->pMutex);
    }
}

void fn_801F6C04(StreamTap_801F5DA4 *h, int level)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    int old;

    if (fn_801F5DA4(h, &s, &t) == 0) {
        old = s->mGreedyLevel;
        s->mGreedyLevel = level;
        if ((s->mUsed < old) != (s->mUsed < level)) {
            fn_801F6C78(h, s->mUsed < level);
        }
    }
}

void fn_801F6C78(StreamTap_801F5DA4 *h, int state)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) == 0) {
        s->mGreedyState = state;
        if (state && s->mState == 1) {
            s->mReadHandle = fn_801C9C88(s->mReadHandle, s->mGreedyPriority);
        }
    }
}

StreamTap_801F5DA4 *fn_801F6CE8(StreamTap_801F5DA4 *h, int tap)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) != 0 || tap <= 0 || tap > s->mNumTaps) {
        return 0;
    }
    return &s->pTaps[tap - 1];
}

int fn_801F6D54(StreamTap_801F5DA4 *h, StreamFile_801F6D54 *pFile, int offset, unsigned int endMarker)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamRequest_801F5EA4 *req;
    int state;

    if (((char *)pFile)[0] == 'A' && ((char *)pFile)[1] == 'E' && ((char *)pFile)[2] == 'M' && ((char *)pFile)[3] == 'S') {
        pFile = fn_801F5000(pFile);
    }
    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    req = fn_801F5EA4(s);
    if (req == 0) {
        return 0;
    }
    req->mType = 0;
    req->mFile.pRes = pFile->pRes;
    req->mFile.mIndex = pFile->mIndex;
    fn_801F10B0(pFile->pRes, pFile->mIndex, &req->mFileSize, &req->mFileOffset, &req->mFileHandle);
    req->mSize = offset;
    req->mEndMarker = endMarker;
    fn_801F5F28(s, req);
    fn_801F778C(s->pMutex);
    state = s->mState;
    if (state == 0) {
        s->mState = 1;
    }
    fn_801F77B4(s->pMutex);
    if (state == 0) {
        if (s->mGreedyState) {
            fn_801F6410(s, s->mGreedyPriority);
        } else {
            fn_801F6410(s, s->mPriority);
        }
    }
    return req->mID;
}

int fn_801F6E9C(StreamTap_801F5DA4 *h, char *pMem, int size, unsigned int endMarker)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamRequest_801F5EA4 *req;
    StreamChunk_801F5D84 *c;
    int state;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    req = fn_801F5EA4(s);
    if (req == 0) {
        return 0;
    }
    if (size == 0) {
        for (c = (StreamChunk_801F5D84 *)pMem; fn_801F5D84(c->mID) != endMarker;) {
            int chunkSize = fn_801F5D84(c->mSize);

            size += chunkSize;
            c = (StreamChunk_801F5D84 *)((char *)c + chunkSize);
        }
        size += fn_801F5D84(c->mSize);
    }
    req->pMem = pMem;
    req->mSize = size;
    req->mEndMarker = endMarker;
    req->mType = 1;
    fn_801F5F28(s, req);
    fn_801F778C(s->pMutex);
    state = s->mState;
    if (state == 0) {
        s->mState = 1;
    }
    fn_801F77B4(s->pMutex);
    if (state == 0) {
        fn_801F6410(s, 0);
    }
    return req->mID;
}

void fn_801F6FA0(StreamTap_801F5DA4 *h, int id)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamRequest_801F5EA4 *req;
    StreamChunk_801F5D84 *c;
    char *pTail = 0;
    char *pFrom = 0;
    char *pTo = 0;
    int skip;
    int i;
    unsigned int size;
    unsigned int tap;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return;
    }
    fn_801F778C(s->pMutex);
    req = fn_801F5FA4(s, id);
    if (req == 0 || req->mState == 4) {
        skip = 1;
    } else if (req->mState == 1) {
        skip = 1;
        fn_801F5FF4(s, req);
    } else {
        req->mState = 4;
        pTail = s->pTail;
        if (req == s->pFirst) {
            pFrom = pTail;
        } else {
            pFrom = req->pStart;
        }
        if (req->pNext == 0 || req->pNext->mState == 1) {
            pTo = s->pHead;
        } else {
            pTo = req->pNext->pStart;
        }
        skip = 0;
    }
    fn_801F77B4(s->pMutex);
    if (!skip) {
        for (i = 0; i < s->mNumTaps; i++) {
            t = &s->pTaps[i];
            if (t->mBytes > 0) {
                if (fn_801F5DE4(pTail, pFrom, t->pRead)) {
                    tap = t->mIndex << 24;
                    c = (StreamChunk_801F5D84 *)pFrom;
                    while ((char *)c != pTo) {
                        if (fn_801F5D84(c->mID) == CHUNK_WRAP) {
                            c = (StreamChunk_801F5D84 *)s->pWrap;
                        } else {
                            size = fn_801F5D84(c->mSize) & 0xFFFFFF;
                            if ((fn_801F5D84(c->mSize) & 0xFF000000) == tap) {
                                fn_801F778C(s->pMutex);
                                t->mBytes -= size;
                                fn_801F77B4(s->pMutex);
                                fn_801F5E24(s, size);
                                c->mID = fn_801F5D84(CHUNK_SKIP);
                                c->mSize = fn_801F5D84(size);
                            }
                            c = (StreamChunk_801F5D84 *)((char *)c + size);
                        }
                    }
                } else {
                    if (fn_801F5DE4(pFrom, pTo, t->pRead)) {
                        do {
                            c = fn_801F73D4(t);
                            fn_801F74D4(t, c);
                        } while (t->mBytes > 0 && fn_801F5DE4(pFrom, pTo, t->pRead));
                    }
                }
            }
        }
    }
}

void fn_801F7208(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamChunk_801F5D84 *c;
    unsigned int size = 0;
    int pad;
    int i;

    if (fn_801F5DA4(h, &s, &t) != 0 || s->pLast == 0) {
        return;
    }
    while (s->pLast->mState == 1 || s->pLast->mState == 2) {
        fn_801F6FA0(h, s->pLast->mID);
    }
    while (s->pFirst != s->pCurrent) {
        fn_801F5FF4(s, s->pFirst);
    }
    s->pCurrent->mState = 4;
    for (i = 0; i < s->mNumTaps; i++) {
        s->pTaps[i].mBytes = 0;
    }
    fn_801F5E24(s, s->mUsed);
    for (c = (StreamChunk_801F5D84 *)s->pTail; (char *)c != s->pHead;) {
        if (fn_801F5D84(c->mID) == CHUNK_WRAP) {
            c = (StreamChunk_801F5D84 *)s->pWrap;
        } else {
            size = fn_801F5D84(c->mSize) & 0xFFFFFF;
            c->mID = fn_801F5D84(CHUNK_SKIP);
            c->mSize = fn_801F5D84(size);
            c = (StreamChunk_801F5D84 *)((char *)c + size);
        }
    }
    if (s->mState == 2) {
        if ((char *)c == s->pWrap) {
            s->pHead = s->pBuffer;
            s->pWrap = s->pHead;
        } else {
            pad = 32 - ((int)s->pHead & 31);
            if (pad == 32) {
                pad = 0;
            }
            c = (StreamChunk_801F5D84 *)(s->pHead - size);
            c->mSize = fn_801F5D84(size + pad);
            s->pHead += pad;
        }
        s->mState = 0;
    }
}

StreamChunk_801F5D84 *fn_801F73D4(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamChunk_801F5D84 *c;
    StreamChunk_801F5D84 *pNext;
    unsigned int size;
    int left;
    unsigned int tap;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    if (t->mBytes == 0) {
        return 0;
    }
    c = (StreamChunk_801F5D84 *)t->pRead;
    size = fn_801F5D84(c->mSize) & 0xFFFFFF;
    c->mSize = fn_801F5D84(size);
    fn_801F778C(s->pMutex);
    left = t->mBytes -= size;
    fn_801F77B4(s->pMutex);
    if (left > 0) {
        tap = t->mIndex << 24;
        pNext = (StreamChunk_801F5D84 *)((char *)c + size);
        while ((fn_801F5D84(pNext->mSize) & 0xFF000000) != tap) {
            if (fn_801F5D84(pNext->mID) == CHUNK_WRAP) {
                pNext = (StreamChunk_801F5D84 *)s->pWrap;
            } else {
                size = fn_801F5D84(pNext->mSize) & 0xFFFFFF;
                pNext = (StreamChunk_801F5D84 *)((char *)pNext + size);
            }
        }
        t->pRead = (char *)pNext;
    }
    return c;
}

void fn_801F74D4(StreamTap_801F5DA4 *h, StreamChunk_801F5D84 *c)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    int state;

    if (fn_801F5DA4(h, &s, &t) != 0 || (char *)c < s->pWrap || (char *)c > s->pBufferEnd - 8 ||
        fn_801F5D84(c->mID) == CHUNK_SKIP) {
        return;
    }
    c->mID = fn_801F5D84(CHUNK_SKIP);
    fn_801F5E24(s, fn_801F5D84(c->mSize));
    fn_801F778C(s->pMutex);
    state = s->mState;
    if (state == 2) {
        s->mState = 1;
    }
    fn_801F77B4(s->pMutex);
    if (state == 2) {
        if (s->mGreedyState) {
            fn_801F6540(s, s->mGreedyPriority);
        } else {
            fn_801F6540(s, s->mPriority);
        }
    }
}

int fn_801F75C4(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    return t->mBytes;
}

int fn_801F7604(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    return s->mState;
}

int fn_801F7644(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    return s->mState == 0 && t->mBytes == 0;
}

int fn_801F76A0(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (fn_801F5DA4(h, &s, &t) != 0) {
        return 0;
    }
    return s->pBufferEnd - s->pBuffer;
}

void fn_801F76E8(void)
{
    fn_801F7FA8(&lbl_8039B3D8);
}

void fn_801F7710(void)
{
    fn_801F80D0(&lbl_8039B3D8);
}
