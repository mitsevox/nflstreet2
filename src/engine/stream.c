/* Streaming file reader: queues file and memory requests into ring buffers, splits the data into chunks
   for each tap, and serves the sound streams and movies that read through it. */
#include "engine/sound.h"
#include "engine/system.h"

#define STREAM_MAGIC 0x5354524D

#define CHUNK_WRAP -1
#define CHUNK_SKIP -2

typedef struct StreamChunk_801F5D84 {
    unsigned int mID;
    unsigned int mSize;
} StreamChunk_801F5D84;

typedef struct StreamRequest_801F5EA4 {
    int mID;
    int mState;
    struct StreamRequest_801F5EA4 *pPrev;
    struct StreamRequest_801F5EA4 *pNext;
    int mType;
    SndFileDesc_t mFile;
    unsigned int mFileSize;
    unsigned int mFileOffset;
    int mFileHandle;
    char *pMem;
    /* Byte count of a memory request; start offset in the file for a file request. */
    int mUnk2C;
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
    SndFileDesc_t mFile;
    unsigned int mFileSize;
    int mFileOffset;
    int mFileHandle;
    int mFilePos;
    int mReadHandle;
    int mReadSize;
    int mBlockSize;
} Stream_801F5DA4;

extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileReadAsync(int handle, char *pBuffer, int size, int priority,
                       void (*pCallback)(int, int, void *), void *pContext);
extern int FileRePrioritizeAsync(int readHandle, int priority);
extern void FileLockAsyncRequestList(void);
extern void FileUnlockAsyncRequestList(void);
extern void FileDebugProcess(void);
extern int FileHostCheckActive(void);

/* Held around each async read submission so the reads of all streams queue in order. */
static Lock_801F8014 _Stream_SeekReadCS;

/* The id of the last request handed out, counted in steps of 0x100 and never 0. */
static unsigned int requestidcounter;

static void startnextrequest(Stream_801F5DA4 *s, int priority);
static void restartstream(Stream_801F5DA4 *s, int priority);
void STREAM_kill(StreamTap_801F5DA4 *h);
StreamChunk_801F5D84 *STREAM_get(StreamTap_801F5DA4 *h);
void STREAM_release(StreamTap_801F5DA4 *h, StreamChunk_801F5D84 *c);
void STREAM_setgreedystate(StreamTap_801F5DA4 *h, int state);

static unsigned int getint(unsigned int value)
{
    return (value >> 24) | ((value >> 8) & 0xFF00) | ((value << 8) & 0xFF0000) | (value << 24);
}

static int validatehandle(StreamTap_801F5DA4 *h, Stream_801F5DA4 **ps, StreamTap_801F5DA4 **pt)
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

static int inbetween(char *pStart, char *pEnd, char *p)
{
    if (pStart <= pEnd) {
        return p >= pStart && p < pEnd;
    }
    return p >= pStart || p < pEnd;
}

static void decbufferusage(Stream_801F5DA4 *s, int size)
{
    int used;
    int newUsed;

    _StreamMUTEX_lock(s->pMutex);
    used = s->mUsed;
    newUsed = used - size;
    s->mUsed = newUsed;
    _StreamMUTEX_unlock(s->pMutex);
    if (used >= s->mGreedyLevel && newUsed < s->mGreedyLevel) {
        s->mGreedyState = 1;
        if (s->mState == 1) {
            s->mReadHandle = FileRePrioritizeAsync(s->mReadHandle, s->mGreedyPriority);
        }
    }
}

static StreamRequest_801F5EA4 *getfreerequest(Stream_801F5DA4 *s)
{
    StreamRequest_801F5EA4 *req = 0;

    _StreamMUTEX_lock(s->pMutex);
    if (s->pFree) {
        req = s->pFree;
        s->pFree = req->pNext;
        requestidcounter += 0x100;
        if (requestidcounter == 0) {
            requestidcounter = 0x100;
        }
        req->mID = (req->mID & 0xFF) | requestidcounter;
    }
    _StreamMUTEX_unlock(s->pMutex);
    return req;
}

static void queuerequest(Stream_801F5DA4 *s, StreamRequest_801F5EA4 *req)
{
    req->mState = 1;
    req->pNext = 0;
    _StreamMUTEX_lock(s->pMutex);
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
    _StreamMUTEX_unlock(s->pMutex);
}

static StreamRequest_801F5EA4 *locaterequest(Stream_801F5DA4 *s, int id)
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

static void freerequest(Stream_801F5DA4 *s, StreamRequest_801F5EA4 *req)
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

static int filterchunk(Stream_801F5DA4 *s, StreamChunk_801F5D84 *c)
{
    unsigned int id = getint(c->mID);
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

static int parsechunks(Stream_801F5DA4 *s)
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
        size = getint(c->mSize);
        if (size & 0xFF000000) {
            size = 8;
            c->mID = getint(req->mEndMarker);
            c->mSize = getint(8);
        }
        if ((unsigned int)(s->pHead + size) > (unsigned int)s->pWrite) {
            break;
        }
        if (getint(c->mID) == req->mEndMarker) {
            pad = (int)s->pHead & 31;
            size = ((size + pad + 31) & ~31) - pad;
        }
        tap = filterchunk(s, c);
        if (tap < 0) {
            _StreamMUTEX_lock(s->pMutex);
            cancelled = req->mState == 4;
            if (!cancelled) {
                c->mID = getint(CHUNK_SKIP);
                s->pHead += size;
            }
            _StreamMUTEX_unlock(s->pMutex);
        } else {
            /* FAKEMATCH: the greedy-state reset value is a local set at the top of this arm
               (the target holds the 0 in r25 from 0x801F6190 to the store at 0x801F6210). */
            int greedyState = 0;

            c->mSize = getint(size | (tap << 24));
            _StreamMUTEX_lock(s->pMutex);
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
                    s->mGreedyState = greedyState;
                }
            }
            _StreamMUTEX_unlock(s->pMutex);
        }
        if (cancelled) {
            if (getint(c->mID) != req->mEndMarker) {
                pad = (int)s->pHead & 31;
                size = ((size + pad + 31) & ~31) - pad;
                c->mSize = getint(size | (tap << 24));
            }
            return 0;
        }
        if (getint(c->mID) == req->mEndMarker) {
            return 1;
        }
    }
    return 0;
}

static void readcallback(Stream_801F5DA4 *s)
{
    StreamRequest_801F5EA4 *req = s->pCurrent;
    int end;
    int found;

    if (req->mType == 1) {
        end = s->mReadSize + s->mFilePos >= req->mUnk2C;
    } else {
        end = (unsigned int)(s->mReadSize + s->mFilePos) >= s->mFileSize;
    }
    s->mFilePos += s->mReadSize;
    s->pWrite += s->mReadSize;
    found = parsechunks(s);
    if (req->mState == 4) {
        startnextrequest(s, s->mGreedyPriority);
    } else if (end || found) {
        _StreamMUTEX_lock(s->pMutex);
        if (req->mState != 4) {
            req->mState = 3;
        }
        _StreamMUTEX_unlock(s->pMutex);
        startnextrequest(s, s->mGreedyPriority);
    } else {
        restartstream(s, s->mGreedyPriority - 1);
    }
}

static void _StreamReadCallback(int a, int b, void *pContext)
{
    readcallback(pContext);
}

static void startnextrequest(Stream_801F5DA4 *s, int priority)
{
    int idle;
    StreamRequest_801F5EA4 *req;

    _StreamMUTEX_lock(s->pMutex);
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
    _StreamMUTEX_unlock(s->pMutex);
    if (!idle) {
        s->pWrite = s->pHead;
        if (req->mType == 1) {
            s->mFilePos = 0;
        } else {
            s->mFilePos = req->mUnk2C;
            if (req->mFile.pRes != s->mFile.pRes || req->mFile.mIndex != s->mFile.mIndex) {
                s->mFile.pRes = req->mFile.pRes;
                s->mFile.mIndex = req->mFile.mIndex;
                s->mFileSize = req->mFileSize;
                s->mFileOffset = req->mFileOffset;
                s->mFileHandle = req->mFileHandle;
                restartstream(s, s->mGreedyPriority);
                return;
            }
        }
        restartstream(s, priority);
    }
}

static void restartstream(Stream_801F5DA4 *s, int priority)
{
    StreamChunk_801F5D84 *c;
    StreamRequest_801F5EA4 *req;
    int avail;
    int len;

    while (s->pTail != s->pHead) {
        c = (StreamChunk_801F5D84 *)s->pTail;
        if (getint(c->mID) == CHUNK_WRAP) {
            s->pTail = s->pWrap;
        } else if (getint(c->mID) == CHUNK_SKIP) {
            s->pTail += getint(c->mSize);
        } else {
            break;
        }
    }
    _StreamMUTEX_lock(s->pMutex);
    for (;;) {
        req = s->pFirst;
        if (req->pNext == 0 || req->pNext->mState == 1) {
            break;
        }
        if (inbetween(s->pTail, s->pWrite, req->pNext->pStart - 1)) {
            break;
        }
        freerequest(s, req);
    }
    _StreamMUTEX_unlock(s->pMutex);
    if ((unsigned int)s->pTail > (unsigned int)s->pWrite) {
        avail = s->pTail - s->pWrite - 33;
    } else {
        avail = s->pBufferEnd - s->pWrite - 32;
        if (avail < s->mBlockSize) {
            len = s->pWrite - s->pHead;
            if (s->pCurrent->mType == 1) {
                if (s->pTail - s->pWrap < len + 1) {
                    s->mState = 2;
                    return;
                }
            } else if (s->pTail - s->pWrap - 32 < len + 1) {
                s->mState = 2;
                return;
            }
            if ((len & 31) == 0 || s->pCurrent->mType == 1) {
                s->pWrap = s->pBuffer;
            } else {
                s->pWrap = s->pBuffer - (len % 32 - 32);
            }
            memcpy(s->pWrap, s->pHead, len);
            c = (StreamChunk_801F5D84 *)s->pHead;
            c->mID = getint(CHUNK_WRAP);
            c->mSize = getint(8);
            s->pHead = s->pWrap;
            s->pWrite = s->pWrap + len;
            if (getint(((StreamChunk_801F5D84 *)s->pTail)->mID) == CHUNK_WRAP) {
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
        if (s->mFilePos + avail > req->mUnk2C) {
            s->mReadSize = req->mUnk2C - s->mFilePos;
        } else {
            s->mReadSize = avail;
        }
        memcpy(s->pWrite, req->pMem, s->mReadSize);
        req->pMem += s->mReadSize;
        readcallback(s);
    } else {
        s->mReadSize = s->mBlockSize;
        if ((unsigned int)(s->mFilePos + s->mBlockSize) > s->mFileSize) {
            s->mReadSize = s->mFileSize - s->mFilePos;
        }
        FileLockAsyncRequestList();
        fn_801F8014(&_Stream_SeekReadCS);
        FileSeek(s->mFileHandle, s->mFileOffset + s->mFilePos, 0);
        s->mReadHandle = FileReadAsync(s->mFileHandle, s->pWrite, s->mReadSize, priority, _StreamReadCallback, s);
        fn_801F809C(&_Stream_SeekReadCS);
        FileUnlockAsyncRequestList();
    }
}

int STREAM_overhead(int numRequests, int numFilters, int numTaps)
{
    return sizeof(Stream_801F5DA4) + numRequests * sizeof(StreamRequest_801F5EA4) + numFilters * sizeof(StreamFilter_801F6074) +
           numTaps * sizeof(StreamTap_801F5DA4) + 32;
}

StreamTap_801F5DA4 *STREAM_create(int numRequests, int numFilters, int numTaps, void *pMem, int memSize)
{
    Stream_801F5DA4 *s = pMem;
    int bufferSize = memSize - STREAM_overhead(numRequests, numFilters, numTaps);
    char *pBuffer;
    int i;

    if (bufferSize < 0x1800 || numRequests < 2 || numRequests > 256 || (numFilters < 1 || numFilters > 16) ||
        numTaps <= 0 || numTaps > numFilters) {
        return 0;
    }
    s->mMagic = STREAM_MAGIC;
    s->pMutex = _StreamMUTEX_alloc();
    s->pRequests = (StreamRequest_801F5EA4 *)(s + 1);
    s->mNumRequests = numRequests;
    s->pFilters = (StreamFilter_801F6074 *)(s->pRequests + numRequests);
    s->mNumFilters = numFilters;
    s->pTaps = (StreamTap_801F5DA4 *)(s->pFilters + numFilters);
    s->mNumTaps = numTaps;
    pBuffer = (char *)(((unsigned int)(s->pTaps + numTaps) & ~31) + 32);
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
    s->pFree = s->pRequests;
    s->mFile.pRes = (ResFile_t *)-1;
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
        StreamRequest_801F5EA4 *pReq = &s->pRequests[i];
        pReq->mID = i;
        pReq->mState = 0;
        pReq->pNext = &s->pRequests[i + 1];
    }
    s->pRequests[numRequests - 1].pNext = 0;
    for (i = 0; i < numFilters; i++) {
        StreamFilter_801F6074 *pFilter = &s->pFilters[i];
        // FAKEMATCH: value written before tap; this source order gives the target schedule (+0x8 at 0x801F6A64, +0x4 at 0x801F6A6C)
        pFilter->mMask = 0;
        pFilter->mValue = 0;
        pFilter->mTap = 1;
    }
    for (i = 0; i < numTaps; i++) {
        StreamTap_801F5DA4 *pTap = &s->pTaps[i];
        // FAKEMATCH: index written before byte count; this source order gives the target schedule (+0x8 at 0x801F6AA0, +0x4 at 0x801F6AA8)
        pTap->pStream = s;
        pTap->mIndex = i + 1;
        pTap->mBytes = 0;
    }
    return s->pTaps;
}

void STREAM_setfilter(StreamTap_801F5DA4 *h, int index, unsigned int mask, unsigned int value, int tap)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamFilter_801F6074 *f;

    if (validatehandle(h, &s, &t) == 0 && index > 0 && index <= s->mNumFilters &&
        (index != s->mNumFilters || (mask | value) == 0) && (tap > 0 || tap == -1 || tap == -2) &&
        tap <= s->mNumTaps && s->mState == 0) {
        f = &s->pFilters[index - 1];
        f->mMask = mask;
        f->mValue = value;
        f->mTap = tap;
    }
}

void STREAM_destroy(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) == 0) {
        STREAM_kill(h);
        while (s->mState == 1) {
            if (FileHostCheckActive()) {
                FileDebugProcess();
            }
        }
        s->mMagic = 0;
        _StreamMUTEX_free(s->pMutex);
    }
}

void STREAM_setgreedylevel(StreamTap_801F5DA4 *h, int level)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    int old;

    if (validatehandle(h, &s, &t) == 0) {
        old = s->mGreedyLevel;
        s->mGreedyLevel = level;
        if ((s->mUsed < old) != (s->mUsed < level)) {
            STREAM_setgreedystate(h, s->mUsed < level);
        }
    }
}

void STREAM_setgreedystate(StreamTap_801F5DA4 *h, int state)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) == 0) {
        s->mGreedyState = state;
        if (state && s->mState == 1) {
            s->mReadHandle = FileRePrioritizeAsync(s->mReadHandle, s->mGreedyPriority);
        }
    }
}

StreamTap_801F5DA4 *STREAM_taphandle(StreamTap_801F5DA4 *h, int tap)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) != 0 || tap <= 0 || tap > s->mNumTaps) {
        return 0;
    }
    return &s->pTaps[tap - 1];
}

int STREAM_queuefile(StreamTap_801F5DA4 *h, SndFileDesc_t *pFile, int offset, unsigned int endMarker)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamRequest_801F5EA4 *req;
    int state;

    /* The sound code passes an "AEMSnn" descriptor name here in place of a file entry. */
    if (((char *)pFile)[0] == 'A' && ((char *)pFile)[1] == 'E' && ((char *)pFile)[2] == 'M' && ((char *)pFile)[3] == 'S') {
        pFile = SndAemsDerefrenceFileDesc((const char *)pFile);
    }
    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    req = getfreerequest(s);
    if (req == 0) {
        return 0;
    }
    req->mType = 0;
    req->mFile.pRes = pFile->pRes;
    req->mFile.mIndex = pFile->mIndex;
    ResGetStreamInfo(pFile->pRes, pFile->mIndex, &req->mFileSize, &req->mFileOffset, &req->mFileHandle);
    req->mUnk2C = offset;
    req->mEndMarker = endMarker;
    queuerequest(s, req);
    _StreamMUTEX_lock(s->pMutex);
    state = s->mState;
    if (state == 0) {
        s->mState = 1;
    }
    _StreamMUTEX_unlock(s->pMutex);
    if (state == 0) {
        if (s->mGreedyState) {
            startnextrequest(s, s->mGreedyPriority);
        } else {
            startnextrequest(s, s->mPriority);
        }
    }
    return req->mID;
}

int STREAM_queuemem(StreamTap_801F5DA4 *h, char *pMem, int size, unsigned int endMarker)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamRequest_801F5EA4 *req;
    StreamChunk_801F5D84 *c;
    int state;

    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    req = getfreerequest(s);
    if (req == 0) {
        return 0;
    }
    if (size == 0) {
        for (c = (StreamChunk_801F5D84 *)pMem; getint(c->mID) != endMarker;) {
            int chunkSize = getint(c->mSize);

            size += chunkSize;
            c = (StreamChunk_801F5D84 *)((char *)c + chunkSize);
        }
        size += getint(c->mSize);
    }
    req->pMem = pMem;
    req->mUnk2C = size;
    req->mEndMarker = endMarker;
    req->mType = 1;
    queuerequest(s, req);
    _StreamMUTEX_lock(s->pMutex);
    state = s->mState;
    if (state == 0) {
        s->mState = 1;
    }
    _StreamMUTEX_unlock(s->pMutex);
    if (state == 0) {
        startnextrequest(s, 0);
    }
    return req->mID;
}

void STREAM_cancelrequest(StreamTap_801F5DA4 *h, int id)
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

    if (validatehandle(h, &s, &t) != 0) {
        return;
    }
    _StreamMUTEX_lock(s->pMutex);
    req = locaterequest(s, id);
    if (req == 0 || req->mState == 4) {
        skip = 1;
    } else if (req->mState == 1) {
        skip = 1;
        freerequest(s, req);
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
    _StreamMUTEX_unlock(s->pMutex);
    if (!skip) {
        for (i = 0; i < s->mNumTaps; i++) {
            t = &s->pTaps[i];
            if (t->mBytes > 0) {
                if (inbetween(pTail, pFrom, t->pRead)) {
                    tap = t->mIndex << 24;
                    c = (StreamChunk_801F5D84 *)pFrom;
                    while ((char *)c != pTo) {
                        if (getint(c->mID) == CHUNK_WRAP) {
                            c = (StreamChunk_801F5D84 *)s->pWrap;
                        } else {
                            size = getint(c->mSize) & 0xFFFFFF;
                            if ((getint(c->mSize) & 0xFF000000) == tap) {
                                _StreamMUTEX_lock(s->pMutex);
                                t->mBytes -= size;
                                _StreamMUTEX_unlock(s->pMutex);
                                decbufferusage(s, size);
                                c->mID = getint(CHUNK_SKIP);
                                c->mSize = getint(size);
                            }
                            c = (StreamChunk_801F5D84 *)((char *)c + size);
                        }
                    }
                } else {
                    if (inbetween(pFrom, pTo, t->pRead)) {
                        do {
                            c = STREAM_get(t);
                            STREAM_release(t, c);
                        } while (t->mBytes > 0 && inbetween(pFrom, pTo, t->pRead));
                    }
                }
            }
        }
    }
}

void STREAM_kill(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamChunk_801F5D84 *c;
    unsigned int size = 0;
    int pad;
    int i;
    StreamRequest_801F5EA4 *req;

    if (validatehandle(h, &s, &t) != 0 || (req = s->pLast) == 0) {
        return;
    }
    while (req->mState == 1 || req->mState == 2) {
        STREAM_cancelrequest(h, req->mID);
        req = s->pLast;
    }
    while (s->pFirst != s->pCurrent) {
        freerequest(s, s->pFirst);
    }
    s->pCurrent->mState = 4;
    for (i = 0; i < s->mNumTaps; i++) {
        s->pTaps[i].mBytes = 0;
    }
    decbufferusage(s, s->mUsed);
    for (c = (StreamChunk_801F5D84 *)s->pTail; (char *)c != s->pHead;) {
        if (getint(c->mID) == CHUNK_WRAP) {
            c = (StreamChunk_801F5D84 *)s->pWrap;
        } else {
            size = getint(c->mSize) & 0xFFFFFF;
            c->mID = getint(CHUNK_SKIP);
            c->mSize = getint(size);
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
            c->mSize = getint(size + pad);
            s->pHead += pad;
        }
        s->mState = 0;
    }
}

StreamChunk_801F5D84 *STREAM_get(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    StreamChunk_801F5D84 *c;
    StreamChunk_801F5D84 *pNext;
    unsigned int size;
    int left;
    unsigned int tap;

    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    if (t->mBytes == 0) {
        return 0;
    }
    c = (StreamChunk_801F5D84 *)t->pRead;
    size = getint(c->mSize) & 0xFFFFFF;
    c->mSize = getint(size);
    _StreamMUTEX_lock(s->pMutex);
    left = t->mBytes -= size;
    _StreamMUTEX_unlock(s->pMutex);
    if (left > 0) {
        tap = t->mIndex << 24;
        pNext = (StreamChunk_801F5D84 *)((char *)c + size);
        while ((getint(pNext->mSize) & 0xFF000000) != tap) {
            if (getint(pNext->mID) == CHUNK_WRAP) {
                pNext = (StreamChunk_801F5D84 *)s->pWrap;
            } else {
                size = getint(pNext->mSize) & 0xFFFFFF;
                pNext = (StreamChunk_801F5D84 *)((char *)pNext + size);
            }
        }
        t->pRead = (char *)pNext;
    }
    return c;
}

void STREAM_release(StreamTap_801F5DA4 *h, StreamChunk_801F5D84 *c)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;
    int state;

    if (validatehandle(h, &s, &t) != 0 || (char *)c < s->pWrap || (char *)c > s->pBufferEnd - 8 ||
        getint(c->mID) == CHUNK_SKIP) {
        return;
    }
    c->mID = getint(CHUNK_SKIP);
    decbufferusage(s, getint(c->mSize));
    _StreamMUTEX_lock(s->pMutex);
    state = s->mState;
    if (state == 2) {
        s->mState = 1;
    }
    _StreamMUTEX_unlock(s->pMutex);
    if (state == 2) {
        if (s->mGreedyState) {
            restartstream(s, s->mGreedyPriority);
        } else {
            restartstream(s, s->mPriority);
        }
    }
}

int STREAM_gettable(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    return t->mBytes;
}

int STREAM_state(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    return s->mState;
}

int STREAM_isendofstream(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    return s->mState == 0 && t->mBytes == 0;
}

int STREAM_buffersize(StreamTap_801F5DA4 *h)
{
    Stream_801F5DA4 *s;
    StreamTap_801F5DA4 *t;

    if (validatehandle(h, &s, &t) != 0) {
        return 0;
    }
    return s->pBufferEnd - s->pBuffer;
}

void StreamInit(void)
{
    fn_801F7FA8(&_Stream_SeekReadCS);
}

void StreamShutdown(void)
{
    fn_801F80D0(&_Stream_SeekReadCS);
}
