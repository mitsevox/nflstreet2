/* Memory-card streams: the open, close, read and write operations the save code uses to move save data to and from the card, keeping a CRC-32 of the bytes transferred. */

#include <dolphin/os.h>
extern "C" {
void *memset(void *pDest, int value, unsigned int size);
void ChecksumCRC32Begin(void);
void ChecksumCRC32Update(void *pData, unsigned int size);
void ChecksumCRC32End(unsigned int *pResult);
void MemCardMgrSetStreamError(int error);
void MemCardMgrStreamWrite(void *pData, unsigned int size);
void MemCardMgrStreamRead(void *pData, unsigned int size);
int MemCardMgrIsStreamReady(unsigned char *pFailed);
void MemCardMgrUpdate(void);
}

/*
 * Stream operations over memory-card transfers. Each transfer is bounded by
 * the target record's size and advances its position. Successful reads and
 * writes update a running CRC-32, which Close stores in the record.
 */

struct CardStreamTarget {
    unsigned int mChecksum;
    unsigned int mSize;
    unsigned int mPosition;
    unsigned char mFillToEnd;
};

struct CardStream {
    unsigned int mSize;
    unsigned int *mpPosition;
    CardStreamTarget *mpTarget;
    unsigned char mReading;
    unsigned char mFillToEnd;
};

struct CardStreamOps {
    int (*mpOpen)(CardStream *pStream, int unused, CardStreamTarget *pTarget, unsigned char reading);
    int (*mpClose)(CardStream *pStream);
    int (*mpRead)(CardStream *pStream, void *pData, unsigned int size, unsigned int *pDone);
    int (*mpWrite)(CardStream *pStream, void *pData, unsigned int size, unsigned int *pDone);
    void (*mpUnknown10)(CardStream *pStream, unsigned int count);
    int (*mpUnknown14)(unsigned int size);
    unsigned int mUnknown18;
};

static unsigned int _CardStream_uPollCount = 0;

extern "C" {
static void _CardStreamYield(void)
{
    if (++_CardStream_uPollCount > 2) {
        OSYieldThread();
        _CardStream_uPollCount = 0;
    }
}
}

static int CardStreamOpen(CardStream *pStream, int unused, CardStreamTarget *pTarget, unsigned char reading)
{
    int result = 0;

    if (pTarget == 0) {
        result = 0x24;
    } else {
        pStream->mSize = pTarget->mSize;
        pStream->mpPosition = &pTarget->mPosition;
        pStream->mReading = reading;
        pStream->mFillToEnd = pTarget->mFillToEnd;
        pStream->mpTarget = pTarget;
        pTarget->mChecksum = 0xFFFFFFFF;
        ChecksumCRC32Begin();
    }
    return result;
}

/* Transfers the bytes left before the end: zeros when writing, discarded when reading. */
extern "C" {
static int _CardStreamFillToEnd(CardStream *pStream)
{
    int result = 0;
    unsigned int size = pStream->mSize;
    unsigned char buffer[0x400];
    unsigned char failed = 0;
    unsigned int count;

    memset(buffer, 0, sizeof(buffer));
    while (*pStream->mpPosition < size) {
        count = size - *pStream->mpPosition;
        if (count > sizeof(buffer)) {
            count = sizeof(buffer);
        }
        if (pStream->mReading) {
            MemCardMgrStreamRead(buffer, count);
        } else {
            MemCardMgrStreamWrite(buffer, count);
        }
        _CardStream_uPollCount = 0;
        while (!MemCardMgrIsStreamReady(&failed)) {
            if (failed) {
                result = 0x24;
                break;
            }
            MemCardMgrUpdate();
            _CardStreamYield();
        }
        if (failed) {
            break;
        }
        *pStream->mpPosition += count;
    }
    if (*pStream->mpPosition != pStream->mSize) {
        if (!failed) {
            MemCardMgrSetStreamError(-99);
        }
        result = 0x24;
    }
    return result;
}
}

static int CardStreamClose(CardStream *pStream)
{
    int result = 0;
    unsigned char failed;

    MemCardMgrIsStreamReady(&failed);
    if (failed) {
        ChecksumCRC32End(&pStream->mpTarget->mChecksum);
    } else {
        ChecksumCRC32End(&pStream->mpTarget->mChecksum);
        if (pStream->mFillToEnd) {
            result = _CardStreamFillToEnd(pStream);
        }
    }
    return result;
}

static int CardStreamWrite(CardStream *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    int result = 0;
    unsigned char failed;

    if (pStream->mSize < *pStream->mpPosition + size) {
        MemCardMgrSetStreamError(-99);
        return 3;
    }
    MemCardMgrStreamWrite(pData, size);
    _CardStream_uPollCount = 0;
    while (!MemCardMgrIsStreamReady(&failed)) {
        if (failed) {
            result = 0x24;
            break;
        }
        MemCardMgrUpdate();
        _CardStreamYield();
    }
    if (!failed) {
        ChecksumCRC32Update(pData, size);
    }
    *pDone = size;
    *pStream->mpPosition += size;
    return result;
}

static int CardStreamRead(CardStream *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    int result = 0;
    unsigned char failed;

    if (pStream->mSize < *pStream->mpPosition + size) {
        MemCardMgrSetStreamError(-99);
        return 3;
    }
    MemCardMgrStreamRead(pData, size);
    _CardStream_uPollCount = 0;
    while (!MemCardMgrIsStreamReady(&failed)) {
        if (failed) {
            result = 0x24;
            break;
        }
        MemCardMgrUpdate();
        _CardStreamYield();
    }
    if (!failed) {
        ChecksumCRC32Update(pData, size);
    }
    *pDone = size;
    *pStream->mpPosition += size;
    return result;
}

extern "C" {
static int _CardStreamPrepare(unsigned int size)
{
    return 0;
}
}

CardStreamOps gCardStreamOps = {
    CardStreamOpen, CardStreamClose, CardStreamRead, CardStreamWrite, 0, _CardStreamPrepare, 16,
};
