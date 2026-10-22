typedef struct ResCacheFile_801F2E54 {
    int mDevice;
    char *pName;
    char mUnknown8[12];
    unsigned short mNumFiles;
    char mUnknown16[110];
    int mCacheHandle;
    int *pCache;
} ResCacheFile_801F2E54;

typedef struct ResCacheWrite_801F2E54 {
    ResCacheFile_801F2E54 *pFile;
    int mIndex;
    void *pBuffer;
    int mSize;
} ResCacheWrite_801F2E54;

extern int sprintf(char *buffer, const char *format, ...);
extern void *memset(void *dest, int value, unsigned int count);
extern int fn_801C96E4(char *name, int mode);
extern int fn_801C97F0(int handle);
extern int fn_801C9844(int handle, int offset, int mode);
extern int fn_801C9960(int handle, void *pBuffer, int size, int a);
extern int fn_801C9A3C(int handle, void *pBuffer, int size, int a);
extern int fn_801C9C0C(int handle, void *pBuffer, int size, int priority,
                       void (*pCallback)(int, int, void *), void *pContext);
extern void fn_801CA834(int handle);
extern int fn_801CB148(char device);
extern int fn_801CB1AC(int device);
extern int fn_801CB1B4(int handle, int value);
extern void *fn_801D2BB0(int heap, int size, int a, int b);
extern int fn_801D2BD0(void *p);

extern char lbl_802B19A4[];
extern unsigned char lbl_803EBDE0;
extern int lbl_803EBDE4;

static void fn_801F2E54(int result, int error, void *pContext)
{
    ResCacheWrite_801F2E54 *pWrite = pContext;

    fn_801D2BD0(pWrite->pBuffer);
    if (error == 0 && result == pWrite->mSize) {
        pWrite->pFile->pCache[pWrite->mIndex] = result;
    } else {
        pWrite->pFile->pCache[pWrite->mIndex] = 0;
    }
    fn_801D2BD0(pWrite);
}

void fn_801F2ED8(int mode)
{
    lbl_803EBDE4 = mode;
}

void fn_801F2EE0(ResCacheFile_801F2E54 *pFile, char *pName)
{
    char name[128];
    int invalid = 0;
    int handle;
    int size;
    int file;

    if (fn_801CB148(pFile->mDevice) > 0x10B07600) {
        pFile->mCacheHandle = -1;
        return;
    }
    handle = fn_801C96E4(pName, lbl_803EBDE4);
    pFile->mCacheHandle = handle;
    if (handle < 0) {
        invalid = 1;
    } else if (fn_801CB1AC(pFile->mDevice) == 1) {
        invalid = 1;
        fn_801C97F0(pFile->mCacheHandle);
        pFile->mCacheHandle = -1;
    } else if (fn_801CB148(pFile->mDevice) != fn_801CB148(pFile->mCacheHandle)) {
        invalid = 1;
    }
    if (invalid) {
        handle = fn_801C96E4(pName, lbl_803EBDE4 | 0x20);
        pFile->mCacheHandle = handle;
        if (handle < 0) {
            return;
        }
        if (fn_801CB1B4(handle, fn_801CB148(pFile->mDevice)) == 0) {
            pFile->pCache = fn_801D2BB0(1, pFile->mNumFiles * 4, 0, 0);
            if (pFile->pCache != 0) {
                memset(pFile->pCache, 0, pFile->mNumFiles * 4);
                return;
            }
        }
    } else {
        size = pFile->mNumFiles * 4;
        pFile->pCache = fn_801D2BB0(1, size, 0, 0);
        if (pFile->pCache != 0) {
            sprintf(name, lbl_802B19A4, pName);
            name[127] = 0;
            file = fn_801C96E4(name, lbl_803EBDE4);
            if (file < 0) {
                memset(pFile->pCache, 0, size);
            } else {
                if (fn_801C9960(file, pFile->pCache, size, 0) != size) {
                    memset(pFile->pCache, 0, size);
                }
                fn_801C97F0(file);
            }
            return;
        }
    }
    fn_801C97F0(pFile->mCacheHandle);
    pFile->mCacheHandle = -1;
}

void fn_801F30CC(ResCacheFile_801F2E54 *pFile)
{
    fn_801D2BD0(pFile->pCache);
    fn_801C97F0(pFile->mCacheHandle);
}

void fn_801F3104(ResCacheFile_801F2E54 *pFile)
{
    char name[128];
    int handle = 0;

    fn_801CA834(pFile->mCacheHandle);
    sprintf(name, lbl_802B19A4, pFile->pName);
    name[127] = 0;
    handle = fn_801C96E4(name, lbl_803EBDE4 | 0x20);
    if (handle >= 0) {
        fn_801C9A3C(handle, pFile->pCache, pFile->mNumFiles * 4, 0);
        fn_801C97F0(handle);
    }
}

void fn_801F318C(ResCacheFile_801F2E54 *pFile, int index, int offset, void *pData, int size)
{
    ResCacheWrite_801F2E54 *pWrite;
    void *pBuffer;
    int error;

    if (lbl_803EBDE0) {
        error = fn_801C9844(pFile->mCacheHandle, offset, 0);
        if (error == 0 && fn_801C9A3C(pFile->mCacheHandle, pData, size, 0) == size) {
            pFile->pCache[index] = size;
        } else {
            pFile->pCache[index] = 0;
        }
    } else {
        pBuffer = fn_801D2BB0(1, size, 0, 0);
        if (pBuffer != 0) {
            pWrite = fn_801D2BB0(1, sizeof(ResCacheWrite_801F2E54), 0, 0);
            if (pWrite != 0) {
                memcpy(pBuffer, pData, size);
                pWrite->pFile = pFile;
                pWrite->mIndex = index;
                pWrite->pBuffer = pBuffer;
                pWrite->mSize = size;
                if (fn_801C9844(pFile->mCacheHandle, offset, 0) != 0 ||
                    fn_801C9C0C(pFile->mCacheHandle, pBuffer, size, 100, fn_801F2E54, pWrite) == 0) {
                    fn_801D2BD0(pWrite);
                    fn_801D2BD0(pBuffer);
                    pFile->pCache[index] = 0;
                }
            } else {
                fn_801D2BD0(pBuffer);
                pFile->pCache[index] = 0;
            }
        } else {
            pFile->pCache[index] = 0;
        }
    }
}
