/* Memory-buffer I/O device for the T3DB game database: open, close, read, write and seek callbacks
   that let a database be loaded from, or written into, a caller-owned memory buffer. */
#include <string.h>
#include "engine/tdbiomem.h"

typedef struct TDbIOMemFile_t {
    unsigned char *mpData;
    unsigned int mPos;
    unsigned int mSize;
} TDbIOMemFile_t;

/* Start a buffer view at the supplied descriptor's current position. */
static int _TDbIOMemOpen(void *pHandle, unsigned int size, void *pName, int mode)
{
    TDbIOMemFile_t *pFile = pHandle;
    TDbIOMemFile_t *pSrc = pName;
    int err = 0;

    if (pSrc == 0) {
        err = 0x24;
    } else {
        pFile->mSize = pSrc->mSize;
        pFile->mpData = pSrc->mpData + pSrc->mPos;
        pFile->mPos = 0;
    }
    return err;
}

/* Check that the buffer is present and its full declared size was consumed. */
static int _TDbIOMemClose(void *pHandle)
{
    TDbIOMemFile_t *pFile = pHandle;
    int err = 0;

    if (pFile->mpData == 0) {
        err = 3;
    } else if (pFile->mPos != pFile->mSize) {
        err = 0x24;
    }
    return err;
}

/* Copy bytes into the buffer and advance the position on success. */
static int _TDbIOMemWrite(void *pHandle, void *pSrc, unsigned int size, unsigned int *pWritten)
{
    TDbIOMemFile_t *pFile = pHandle;
    if (pFile->mpData == 0) {
        return 3;
    }
    if (pFile->mSize < pFile->mPos + size) {
        return 3;
    }
    memcpy(pFile->mpData + pFile->mPos, pSrc, size);
    *pWritten = size;
    pFile->mPos += size;
    return 0;
}

/* Copy bytes out of the buffer and advance the position on success. */
static int _TDbIOMemRead(void *pHandle, void *pDst, unsigned int size, unsigned int *pRead)
{
    TDbIOMemFile_t *pFile = pHandle;
    if (pFile->mpData == 0) {
        return 3;
    }
    if (pFile->mSize < pFile->mPos + size) {
        return 3;
    }
    memcpy(pDst, pFile->mpData + pFile->mPos, size);
    *pRead = size;
    pFile->mPos += size;
    return 0;
}

/* Move relative to the current position, rejecting a negative or past-end result. */
static int _TDbIOMemSeek(void *pHandle, int offset)
{
    TDbIOMemFile_t *pFile = pHandle;
    int pos;

    if (pFile->mpData == 0) {
        return 3;
    }
    pos = pFile->mPos + offset;
    if (pFile->mSize < (unsigned int)pos || pos < 0) {
        return 3;
    }
    pFile->mPos = pos;
    return 0;
}

/* Report no extra storage beyond the serialized database bytes. */
static unsigned int _TDbIOMemCalcExtraSize(unsigned int size)
{
    return 0;
}

TDbIODevice_t gTDbIOMemCallback = {
    _TDbIOMemOpen,
    _TDbIOMemClose,
    _TDbIOMemRead,
    _TDbIOMemWrite,
    _TDbIOMemSeek,
    _TDbIOMemCalcExtraSize,
    12
};
