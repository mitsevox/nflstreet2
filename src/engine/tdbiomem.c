typedef struct MemFile_8020D388 {
    unsigned char *mpData;
    unsigned int mPos;
    unsigned int mSize;
} MemFile_8020D388;

int fn_8020D388(MemFile_8020D388 *pFile, void *pName, MemFile_8020D388 *pSrc)
{
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

int fn_8020D3C0(MemFile_8020D388 *pFile)
{
    int err = 0;

    if (pFile->mpData == 0) {
        err = 3;
    } else if (pFile->mPos != pFile->mSize) {
        err = 0x24;
    }
    return err;
}

int fn_8020D3F4(MemFile_8020D388 *pFile, void *pSrc, unsigned int size, unsigned int *pWritten)
{
    if (pFile->mpData != 0) {
        if (pFile->mSize >= pFile->mPos + size) {
            memcpy(pFile->mpData + pFile->mPos, pSrc, size);
            *pWritten = size;
            pFile->mPos += size;
            return 0;
        }
    }
    return 3;
}

int fn_8020D470(MemFile_8020D388 *pFile, void *pDst, unsigned int size, unsigned int *pRead)
{
    if (pFile->mpData != 0) {
        if (pFile->mSize >= pFile->mPos + size) {
            memcpy(pDst, pFile->mpData + pFile->mPos, size);
            *pRead = size;
            pFile->mPos += size;
            return 0;
        }
    }
    return 3;
}

int fn_8020D4F0(MemFile_8020D388 *pFile, int offset)
{
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

int fn_8020D52C(void)
{
    return 0;
}
