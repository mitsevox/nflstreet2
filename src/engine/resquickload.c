typedef struct ResQuickloadChunk_801F284C {
    unsigned int mID;
    int mSize;
    int mCount;
} ResQuickloadChunk_801F284C;

typedef struct ResQuickloadKey_801F29F0 {
    unsigned short mFile;
    unsigned short mType;
    unsigned int mID;
    unsigned int mOffset;
} ResQuickloadKey_801F29F0;

typedef struct ResQuickloadEntry_801F2A4C {
    int mKey;
    int mID;
    unsigned int mOffset;
} ResQuickloadEntry_801F2A4C;

typedef struct ResQuickloadDetails_801F2A4C {
    unsigned int mID;
    int mSize;
    int mCount;
    ResQuickloadEntry_801F2A4C mEntries[1];
} ResQuickloadDetails_801F2A4C;

typedef struct ResQuickloadFiles_801F2954 {
    unsigned int mID;
    int mSize;
    int mCount;
    char mEntries[1][0x30];
} ResQuickloadFiles_801F2954;

typedef struct ResQuickload_801F284C {
    int mHandle;
    char *pName;
    char *pData;
    ResQuickloadFiles_801F2954 *pFiles;
    ResQuickloadDetails_801F2A4C *pDetails;
    int mDataOffset;
    int mPosition;
} ResQuickload_801F284C;

typedef struct ResQuickloadAlias_801F2D60 {
    char *pFrom;
    char *pTo;
} ResQuickloadAlias_801F2D60;

extern int strcmp(const char *a, const char *b);
extern void *fn_801C68FC(int a, int b, int count, int size, int c, int d);
extern void fn_801C69E4(void *pPool);
extern void *fn_801C6A20(void *pPool);
extern void fn_801C6AA4(void *pPool, void *pItem, int mode);
extern void *fn_801C6B4C(void *pPool, int mode);
extern void fn_801C6C0C(void *pPool, void *pItem);
extern void *fn_801C6C84(void *pPool, void *pItem);
extern int fn_801C96E4(char *name, int mode);
extern int fn_801C97F0(int handle);
extern int fn_801C9844(int handle, int offset, int mode);
extern int fn_801C9960(int handle, void *pBuffer, int size, int a);
extern int fn_801C9D2C(int handle);
extern int fn_801D2BD0(void *p);
extern void *fn_801D2BB0(int heap, int size, int label, int b);
extern int fn_801F1530(void);
extern void *fn_802623A8(const void *pKey, const void *pBase, int count, int size,
                         int (*pCompare)(const void *, const void *));

extern void *lbl_803EBDD8;
extern ResQuickloadAlias_801F2D60 *lbl_803EBDDC;

int fn_801F2CD4(char *pName);

static void fn_801F284C(int handle, ResQuickload_801F284C *pQuickload)
{
    int header[3];
    int size;
    ResQuickloadChunk_801F284C *pChunk;

    fn_801C9960(handle, header, sizeof(header), 0);
    size = header[2];
    pQuickload->mDataOffset = size;
    pQuickload->mPosition = size;
    pQuickload->pData = fn_801D2BB0(1, size, fn_801F1530(), 0);
    fn_801C9844(handle, 0, 0);
    fn_801C9960(handle, pQuickload->pData, size, 0);
    for (pChunk = (ResQuickloadChunk_801F284C *)pQuickload->pData; (char *)pChunk < pQuickload->pData + size;
         pChunk = (ResQuickloadChunk_801F284C *)((char *)pChunk + pChunk->mSize)) {
        switch (pChunk->mID) {
        case 0x46494C53:
            pQuickload->pFiles = (ResQuickloadFiles_801F2954 *)pChunk;
            break;
        case 0x44544C53:
            pQuickload->pDetails = (ResQuickloadDetails_801F2A4C *)pChunk;
            break;
        }
    }
}

static int fn_801F2934(const void *pKey, const void *pEntry)
{
    return strcmp(pKey, pEntry);
}

static ResQuickload_801F284C *fn_801F2954(char *pName, int *pIndex)
{
    ResQuickload_801F284C *pQuickload;
    ResQuickloadFiles_801F2954 *pFiles;
    char *pFound;

    for (pQuickload = fn_801C6B4C(lbl_803EBDD8, 0); pQuickload != 0; pQuickload = fn_801C6C84(lbl_803EBDD8, pQuickload)) {
        pFiles = pQuickload->pFiles;
        pFound = fn_802623A8(pName, pFiles->mEntries, pFiles->mCount, sizeof(pFiles->mEntries[0]), fn_801F2934);
        if (pFound != 0) {
            *pIndex = (pFound - (char *)pFiles->mEntries) / sizeof(pFiles->mEntries[0]);
            break;
        }
    }
    return pQuickload;
}

static int fn_801F29F0(const void *pKey, const void *pEntry)
{
    const ResQuickloadKey_801F29F0 *a = pKey;
    const ResQuickloadKey_801F29F0 *b = pEntry;
    int result;

    if (a->mFile > b->mFile) {
        result = 1;
    } else if (a->mFile < b->mFile) {
        result = -1;
    } else if (a->mType > b->mType) {
        result = 1;
    } else if (a->mType < b->mType) {
        result = -1;
    } else if (a->mID > b->mID) {
        result = 1;
    } else if (a->mID < b->mID) {
        result = -1;
    } else {
        result = 0;
    }
    return result;
}

#define DISTANCE(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))

static ResQuickloadEntry_801F2A4C *fn_801F2A4C(ResQuickloadDetails_801F2A4C *pDetails, int file, int type,
                                               unsigned int id, unsigned int offset)
{
    ResQuickloadKey_801F29F0 key;
    ResQuickloadEntry_801F2A4C *pEntry;
    ResQuickloadEntry_801F2A4C *pNext;

    key.mFile = file;
    key.mType = type;
    key.mID = id;
    key.mOffset = offset;
    pEntry = fn_802623A8(&key, pDetails->mEntries, pDetails->mCount, sizeof(ResQuickloadEntry_801F2A4C), fn_801F29F0);
    if (pEntry != 0) {
        while (pEntry > pDetails->mEntries) {
            pNext = pEntry - 1;
            if (pEntry->mKey != pNext->mKey || pEntry->mID != pNext->mID ||
                DISTANCE(offset, pNext->mOffset) >= DISTANCE(offset, pEntry->mOffset)) {
                break;
            }
            pEntry = pNext;
        }
        while (pEntry < &pDetails->mEntries[pDetails->mCount - 1]) {
            pNext = pEntry + 1;
            if (pEntry->mKey != pNext->mKey || pEntry->mID != pNext->mID ||
                DISTANCE(offset, pNext->mOffset) >= DISTANCE(offset, pEntry->mOffset)) {
                break;
            }
            pEntry = pNext;
        }
    }
    return pEntry;
}

int fn_801F2B94(void)
{
    if (lbl_803EBDD8 == 0) {
        return 0;
    }
    return 1;
}

void fn_801F2BAC(int count)
{
    lbl_803EBDD8 = fn_801C68FC(1, 0, count, sizeof(ResQuickload_801F284C), 0, 0);
    lbl_803EBDDC = 0;
}

void fn_801F2BF0(void)
{
    ResQuickload_801F284C *pQuickload;

    for (pQuickload = fn_801C6B4C(lbl_803EBDD8, 0); pQuickload != 0; pQuickload = fn_801C6C84(lbl_803EBDD8, pQuickload)) {
        fn_801F2CD4(pQuickload->pName);
    }
    fn_801C69E4(lbl_803EBDD8);
    lbl_803EBDD8 = 0;
}

int fn_801F2C54(char *pName, int mode)
{
    int result = 0;
    int handle;
    ResQuickload_801F284C *pQuickload;

    handle = fn_801C96E4(pName, mode);
    if (handle >= 0) {
        pQuickload = fn_801C6A20(lbl_803EBDD8);
        if (pQuickload != 0) {
            pQuickload->pName = pName;
            pQuickload->mHandle = handle;
            result = 1;
            fn_801F284C(handle, pQuickload);
            fn_801C6AA4(lbl_803EBDD8, pQuickload, 0);
        } else {
            fn_801C97F0(handle);
        }
    }
    return result;
}

int fn_801F2CD4(char *pName)
{
    int result = 0;
    ResQuickload_801F284C *pQuickload;

    for (pQuickload = fn_801C6B4C(lbl_803EBDD8, 0); pQuickload != 0; pQuickload = fn_801C6C84(lbl_803EBDD8, pQuickload)) {
        if (strcmp(pQuickload->pName, pName) == 0) {
            result = 1;
            fn_801D2BD0(pQuickload->pData);
            fn_801C97F0(pQuickload->mHandle);
            fn_801C6C0C(lbl_803EBDD8, pQuickload);
            break;
        }
    }
    return result;
}

int fn_801F2D60(int file, char *pName, unsigned int id, int *pHandle, int *pOffset)
{
    int result = 0;
    int index = 0;
    ResQuickloadAlias_801F2D60 *pAlias;
    ResQuickload_801F284C *pQuickload;
    ResQuickloadEntry_801F2A4C *pEntry;

    if (fn_801F2B94()) {
        if (lbl_803EBDDC != 0) {
            for (pAlias = lbl_803EBDDC; pAlias->pFrom != 0; pAlias++) {
                if (strcmp(pName, pAlias->pFrom) == 0) {
                    pName = pAlias->pTo;
                    break;
                }
            }
        }
        pQuickload = fn_801F2954(pName, &index);
        if (pQuickload != 0) {
            pEntry = fn_801F2A4C(pQuickload->pDetails, file, index, id,
                                 fn_801C9D2C(pQuickload->mHandle) - pQuickload->mDataOffset);
            if (pEntry != 0) {
                result = 1;
                *pHandle = pQuickload->mHandle;
                pQuickload->mPosition = *pOffset = pQuickload->mDataOffset + pEntry->mOffset;
            }
        }
    }
    return result;
}
