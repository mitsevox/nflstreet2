extern "C" {
void *memset(void *pDest, int value, unsigned int size);
void fn_8023DB7C(void);
void fn_80089668(void);
void fn_800896A8(void *pData, unsigned int size);
void fn_800896EC(unsigned int *pResult);
void fn_801D6E04(int error);
void fn_801D6E10(void *pData, unsigned int size);
void fn_801D6E54(void *pData, unsigned int size);
int fn_801D6EA0(unsigned char *pFailed);
void fn_801D6F58(void);
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

static unsigned int sPollCount = 0;

extern "C" {
static void fn_80023E08(void)
{
    if (++sPollCount > 2) {
        fn_8023DB7C();
        sPollCount = 0;
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
        fn_80089668();
    }
    return result;
}

/* Transfers the bytes left before the end: zeros when writing, discarded when reading. */
extern "C" {
static int fn_80023EAC(CardStream *pStream)
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
            fn_801D6E54(buffer, count);
        } else {
            fn_801D6E10(buffer, count);
        }
        sPollCount = 0;
        while (!fn_801D6EA0(&failed)) {
            if (failed) {
                result = 0x24;
                break;
            }
            fn_801D6F58();
            fn_80023E08();
        }
        if (failed) {
            break;
        }
        *pStream->mpPosition += count;
    }
    if (*pStream->mpPosition != pStream->mSize) {
        if (!failed) {
            fn_801D6E04(-99);
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

    fn_801D6EA0(&failed);
    if (failed) {
        fn_800896EC(&pStream->mpTarget->mChecksum);
    } else {
        fn_800896EC(&pStream->mpTarget->mChecksum);
        if (pStream->mFillToEnd) {
            result = fn_80023EAC(pStream);
        }
    }
    return result;
}

static int CardStreamWrite(CardStream *pStream, void *pData, unsigned int size, unsigned int *pDone)
{
    int result = 0;
    unsigned char failed;

    if (pStream->mSize < *pStream->mpPosition + size) {
        fn_801D6E04(-99);
        return 3;
    }
    fn_801D6E10(pData, size);
    sPollCount = 0;
    while (!fn_801D6EA0(&failed)) {
        if (failed) {
            result = 0x24;
            break;
        }
        fn_801D6F58();
        fn_80023E08();
    }
    if (!failed) {
        fn_800896A8(pData, size);
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
        fn_801D6E04(-99);
        return 3;
    }
    fn_801D6E54(pData, size);
    sPollCount = 0;
    while (!fn_801D6EA0(&failed)) {
        if (failed) {
            result = 0x24;
            break;
        }
        fn_801D6F58();
        fn_80023E08();
    }
    if (!failed) {
        fn_800896A8(pData, size);
    }
    *pDone = size;
    *pStream->mpPosition += size;
    return result;
}

extern "C" {
static int fn_800241D8(unsigned int size)
{
    return 0;
}
}

CardStreamOps gCardStreamOps = {
    CardStreamOpen, CardStreamClose, CardStreamRead, CardStreamWrite, 0, fn_800241D8, 16,
};
