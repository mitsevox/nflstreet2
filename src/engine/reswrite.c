#include "engine/Resource.h"
#include "engine/GCmp.h"
#include "engine/system.h"
#include "game/fn_801D2B7C.h"

extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileWriteCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int FileGetPosition(int handle);
extern void *memset();
extern unsigned int strlen(const char *s);
extern char *strcpy(char *pDst, const char *pSrc);
extern void GCmpCompress(int codec, GCmpBuffer_t *pSrc, GCmpBuffer_t *pDst);
extern Lock_801F8014 _Res_sResourceLock;
extern unsigned char _Res_bModuleActive;
int fn_801F1838(ResFile_t *pWrite, char *pName, void *pData, unsigned int size, int codec, int precompressed,
                unsigned int compressedSize);
extern int fn_801F1D20(ResFile_t *pWrite);
extern int ProcBuildHashTable(int type, unsigned int count, char **ppStrings, int *pHashes, unsigned int **ppParams,
                       int *pParamSize);
extern int fn_801F1F30(ResFile_t *pWrite);

static int fn_801F21B4(int handle, unsigned char value);
static unsigned int fn_801F21E4(int handle, unsigned char value, unsigned int count);
static unsigned int fn_801F1CF8(unsigned int size, unsigned int alignment);
static int fn_801F2244(int handle, unsigned short value, int bigEndian);
static int fn_801F2294(int handle, unsigned int value, int bigEndian);
static int fn_801F201C(ResFile_t *pWrite);
static int fn_801F2120(ResFile_t *pWrite, int index, unsigned int offset, unsigned int size);

static int fn_801F17E0(unsigned int id)
{
    switch (id) {
    case 0x48534831:
        return 1;
    case 0x48534832:
        return 2;
    case 0:
        return 0;
    default:
        return 0;
    }
}

int fn_801F1838(ResFile_t *pWrite, char *pName, void *pData, unsigned int size, int codec, int precompressed,
                unsigned int compressedSize)
{
    GCmpBuffer_t src;
    GCmpBuffer_t dst;
    int err = 0;
    int position;
    unsigned int pad;
    unsigned short index;

    dst.mpData = 0;
    fn_801F8014(&_Res_sResourceLock);
    if (_Res_bModuleActive == 0) {
        err = 0xF0002;
        goto done;
    }
    if (pWrite->mNumRes <= pWrite->mNumWritten || (pWrite->mCompressed == 0 && codec != 0)) {
        size = 0;
        goto done;
    }
    index = pWrite->mNumWritten;
    position = FileGetPosition(pWrite->mFile);
    if (pWrite->mCompressed != 0) {
        pWrite->pBlocks[index].mSize = size;
        pWrite->pBlocks[index].mOffsetOrCodec = 0;
    }
    if (codec != 0) {
        if (precompressed == 0) {
            memset(&src, 0, 0x1C);
            memset(&dst, 0, 0x1C);
            src.mpData = pData;
            src.mSize = size;
            src.mPos = 0;
            GCmpCompress(codec, &src, &dst);
            if (dst.mSize < size) {
                pWrite->pBlocks[index].mOffsetOrCodec = codec;
                size = dst.mSize;
            } else {
                pWrite->pBlocks[index].mOffsetOrCodec = 0;
                fn_801D2BD0(dst.mpData);
                dst.mpData = 0;
            }
        } else if (compressedSize < size) {
            pWrite->pBlocks[index].mOffsetOrCodec = codec;
            size = compressedSize;
        } else {
            pWrite->pBlocks[index].mOffsetOrCodec = 0;
        }
    }
    if (size != 0) {
        pad = fn_801F1CF8(size, pWrite->mAlignment);
        if (pWrite->mPosition + size + pad > pWrite->mEndPad) {
            size = 0;
            goto done;
        }
        if (dst.mpData != 0) {
            FileWriteCallback(pWrite->mFile, dst.mpData, size, 0);
        } else {
            FileWriteCallback(pWrite->mFile, pData, size, 0);
        }
        fn_801F21E4(pWrite->mFile, 0, pad);
        pWrite->mPosition += size + pad;
    } else {
        pad = pWrite->mAlignment;
        if (pWrite->mPosition + pad > pWrite->mEndPad) {
            goto done;
        }
        fn_801F21E4(pWrite->mFile, 0, pad);
        pWrite->mPosition += pad;
    }
    if (pWrite->mDirTag == 0x44495231) {
        pWrite->pDir[index].mOffsetOrCodec = position - pWrite->mBaseOffset;
        pWrite->pDir[index].mSize = size;
    }
    pWrite->mNumWritten++;
    if (pName != 0 && pWrite->pSlots != 0) {
        pWrite->pSlots[index] = fn_801D2BB0(1, strlen(pName) + 1, 0, 0);
        strcpy(pWrite->pSlots[index], pName);
    }
done:
    if (dst.mpData != 0) {
        fn_801D2BD0(dst.mpData);
    }
    fn_801F809C(&_Res_sResourceLock);
    fn_801F7BD4(err);
    return size;
}

int fn_801F1B44(ResFile_t *pWrite, char *pName, void *pData, unsigned int size, int codec)
{
    return fn_801F1838(pWrite, pName, pData, size, codec, 0, 0);
}

int fn_801F1B6C(ResFile_t *pWrite)
{
    int end;
    int size;

    if (pWrite->mNumRes != pWrite->mNumWritten) {
        return 0xF0011;
    }
    end = FileGetPosition(pWrite->mFile);
    if (pWrite->mPosition < pWrite->mEndPad && pWrite->mEndPad != -1) {
        fn_801F21E4(pWrite->mFile, 0, pWrite->mEndPad - pWrite->mPosition);
    }
    size = end - pWrite->mBaseOffset;
    FileSeek(pWrite->mFile, pWrite->mBaseOffset, 0);
    fn_801F2294(pWrite->mFile, 0x44415441, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    if (fn_801F1D20(pWrite) == 0) {
        return 0xF0012;
    }
    fn_801F1F30(pWrite);
    fn_801F201C(pWrite);
    return 0;
}

static unsigned int fn_801F1C48(unsigned int type, unsigned int count)
{
    unsigned int size;

    switch (type) {
    case 0x54455246:
        size = 8;
        break;
    case 0x434F4D50:
    case 0x44495231:
        size = count * 8;
        break;
    case 0x48534831:
        size = count * 4 + 16;
        break;
    case 0x48534832:
        size = count * 2 + 12;
        break;
    default:
        size = 0;
        break;
    }
    return size;
}

static unsigned int fn_801F1CD4(unsigned int type, unsigned int count)
{
    return fn_801F1C48(type, count) + 8;
}

static unsigned int fn_801F1CF8(unsigned int size, unsigned int alignment)
{
    unsigned int pad;

    if (alignment == 0) {
        return 0;
    }
    pad = size % alignment;
    if (pad != 0) {
        pad = alignment - pad;
    }
    return pad;
}

int fn_801F1D20(ResFile_t *pWrite)
{
    ResHashHeader_t *pHash;
    unsigned int count;
    unsigned int size;
    unsigned int pad;
    int type;
    int position;
    unsigned int i;
    unsigned int j;

    if (pWrite->mHashTag == 0) {
        return 1;
    }
    pHash = pWrite->pHash;
    count = pWrite->mNumRes;
    if (ProcBuildHashTable(fn_801F17E0(pWrite->mHashTag), count, (char **)pWrite->pSlots, pWrite->pHashTable,
                    &pWrite->pHashParams, &pHash->mParamSize) != 1) {
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
            }
        }
        return 0;
    }
    size = fn_801F1CD4(pWrite->mHashTag, pWrite->mNumRes);
    pad = fn_801F1CF8(size, pWrite->mAlignment);
    type = pWrite->mHashTag;
    size += pad;
    position = FileGetPosition(pWrite->mFile);
    FileSeek(pWrite->mFile, pWrite->mHashOffset, 0);
    fn_801F2294(pWrite->mFile, type, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, pHash->mType, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, pHash->mParamSize, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, pHash->mWidth, pWrite->mBigEndian);
    if (pWrite->mHashTag == 0x48534831) {
        fn_801F2294(pWrite->mFile, pWrite->pHashParams[0], pWrite->mBigEndian);
    }
    for (i = 0; i < count; i++) {
        switch (pHash->mWidth) {
        case 1:
            fn_801F21B4(pWrite->mFile, ((unsigned char *)pWrite->pHashTable)[i]);
            break;
        case 2:
            fn_801F2244(pWrite->mFile, ((unsigned short *)pWrite->pHashTable)[i], pWrite->mBigEndian);
            break;
        case 4:
            fn_801F2294(pWrite->mFile, ((unsigned int *)pWrite->pHashTable)[i], pWrite->mBigEndian);
            break;
        }
    }
    fn_801F21E4(pWrite->mFile, 0, pad);
    FileSeek(pWrite->mFile, position, 0);
    return 1;
}

int fn_801F1F30(ResFile_t *pWrite)
{
    int position;
    unsigned int size;
    unsigned int i;

    position = FileGetPosition(pWrite->mFile);
    FileSeek(pWrite->mFile, pWrite->mDirOffset, 0);
    size = pWrite->mDirSize;
    fn_801F2294(pWrite->mFile, 0x44495231, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    for (i = 0; i < pWrite->mNumRes; i++) {
        if (pWrite->mDirTag == 0x44495231) {
            fn_801F2120(pWrite, i, pWrite->pDir[i].mOffsetOrCodec, pWrite->pDir[i].mSize);
        }
    }
    FileSeek(pWrite->mFile, position, 0);
    return 1;
}

static int fn_801F201C(ResFile_t *pWrite)
{
    unsigned int size;
    unsigned int i;
    int position;
    int written;

    size = pWrite->mCompSize;
    if (size == 0) {
        return 1;
    }
    i = 0;
    position = FileGetPosition(pWrite->mFile);
    FileSeek(pWrite->mFile, pWrite->mCompOffset, 0);
    fn_801F2294(pWrite->mFile, 0x434F4D50, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    for (; i < pWrite->mNumRes; i++) {
        fn_801F2294(pWrite->mFile, pWrite->pBlocks[i].mOffsetOrCodec, pWrite->mBigEndian);
        fn_801F2294(pWrite->mFile, pWrite->pBlocks[i].mSize, pWrite->mBigEndian);
    }
    written = FileGetPosition(pWrite->mFile) - pWrite->mCompOffset;
    fn_801F21E4(pWrite->mFile, 0, pWrite->mCompSize - written);
    FileSeek(pWrite->mFile, position, 0);
    return 1;
}

static int fn_801F2120(ResFile_t *pWrite, int index, unsigned int offset, unsigned int size)
{
    FileSeek(pWrite->mFile, pWrite->mDirOffset + 8, 0);
    if (pWrite->mDirTag == 0x44495231) {
        FileSeek(pWrite->mFile, index * 8, 1);
        fn_801F2294(pWrite->mFile, offset, pWrite->mBigEndian);
        fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
        return 1;
    }
    return 0;
}

static int fn_801F21B4(int handle, unsigned char value)
{
    return FileWriteCallback(handle, &value, 1, 0);
}

static unsigned int fn_801F21E4(int handle, unsigned char value, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        FileWriteCallback(handle, &value, 1, 0);
    }
    return count;
}

static int fn_801F2244(int handle, unsigned short value, int bigEndian)
{
    unsigned short out;

    if (bigEndian == 1) {
        out = value;
    } else {
        out = ((unsigned char)value << 8) | (value >> 8);
    }
    return FileWriteCallback(handle, &out, 2, 0);
}

static int fn_801F2294(int handle, unsigned int value, int bigEndian)
{
    unsigned char out[4];

    if (bigEndian == 1) {
        out[3] = value & 0xFF;
        out[2] = (value & 0xFF00) >> 8;
        out[1] = (value & 0xFF0000) >> 16;
        out[0] = (value & 0xFF000000) >> 24;
    } else {
        out[0] = value & 0xFF;
        out[1] = (value & 0xFF00) >> 8;
        out[2] = (value & 0xFF0000) >> 16;
        out[3] = (value & 0xFF000000) >> 24;
    }
    return FileWriteCallback(handle, out, 4, 0);
}
