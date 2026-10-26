#include "engine/Resource.h"

extern int fn_801C9844(int handle, int offset, unsigned int whence);
extern int fn_801C9A3C(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int fn_801C9D2C(int handle);
extern int fn_801F1838(int a, int b, int c, int d, int e, int f, int g);
extern int fn_801F1D20(Res_801EDC2C *pWrite);
extern int fn_801F15B0(int type, unsigned int count, char **ppStrings, int *pHashes, unsigned int **ppParams,
                       int *pParamSize);
extern int fn_801F1F30(Res_801EDC2C *pWrite);

static void fn_801F21B4(int handle, unsigned char value);
static unsigned int fn_801F21E4(int handle, unsigned char value, unsigned int count);
static void fn_801F2244(int handle, unsigned short value, int bigEndian);
static void fn_801F2294(int handle, unsigned int value, int bigEndian);
static int fn_801F201C(Res_801EDC2C *pWrite);
static int fn_801F2120(Res_801EDC2C *pWrite, int index, unsigned int offset, unsigned int size);

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

int fn_801F1B44(int a, int b, int c, int d, int e)
{
    return fn_801F1838(a, b, c, d, e, 0, 0);
}

int fn_801F1B6C(Res_801EDC2C *pWrite)
{
    int size;

    if (pWrite->mNumRes != pWrite->mNumWritten) {
        return 0xF0011;
    }
    size = fn_801C9D2C(pWrite->mFile);
    if (pWrite->mPosition < pWrite->mEndPad && pWrite->mEndPad != -1) {
        fn_801F21E4(pWrite->mFile, 0, pWrite->mEndPad - pWrite->mPosition);
    }
    size -= pWrite->mBaseOffset;
    fn_801C9844(pWrite->mFile, pWrite->mBaseOffset, 0);
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

int fn_801F1D20(Res_801EDC2C *pWrite)
{
    ResHash_801F0A8C *pHash;
    unsigned int count;
    unsigned int size;
    unsigned int pad;
    int type;
    int position;
    unsigned int i;
    unsigned int j;

    if (pWrite->mHashCount == 0) {
        return 1;
    }
    pHash = pWrite->pHash;
    count = pWrite->mNumRes;
    if (fn_801F15B0(fn_801F17E0(pWrite->mHashCount), count, (char **)pWrite->pSlots, pWrite->pHashTable,
                    &pWrite->pHashParams, &pHash->mUnk4) != 1) {
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
            }
        }
        return 0;
    }
    size = fn_801F1CD4(pWrite->mHashCount, pWrite->mNumRes);
    pad = fn_801F1CF8(size, pWrite->mAlignment);
    type = pWrite->mHashCount;
    size += pad;
    position = fn_801C9D2C(pWrite->mFile);
    fn_801C9844(pWrite->mFile, pWrite->mHashOffset, 0);
    fn_801F2294(pWrite->mFile, type, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, pHash->mType, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, pHash->mUnk4, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, pHash->mWidth, pWrite->mBigEndian);
    if (pWrite->mHashCount == 0x48534831) {
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
    fn_801C9844(pWrite->mFile, position, 0);
    return 1;
}

int fn_801F1F30(Res_801EDC2C *pWrite)
{
    int position;
    unsigned int size;
    unsigned int i;

    position = fn_801C9D2C(pWrite->mFile);
    fn_801C9844(pWrite->mFile, pWrite->mDirOffset, 0);
    size = pWrite->mDirSize;
    fn_801F2294(pWrite->mFile, 0x44495231, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    for (i = 0; i < pWrite->mNumRes; i++) {
        if (pWrite->mDirTag == 0x44495231) {
            fn_801F2120(pWrite, i, pWrite->pDir[i].mUnk0, pWrite->pDir[i].mUnk4);
        }
    }
    fn_801C9844(pWrite->mFile, position, 0);
    return 1;
}

static int fn_801F201C(Res_801EDC2C *pWrite)
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
    position = fn_801C9D2C(pWrite->mFile);
    fn_801C9844(pWrite->mFile, pWrite->mCompOffset, 0);
    fn_801F2294(pWrite->mFile, 0x434F4D50, 0);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    for (; i < pWrite->mNumRes; i++) {
        fn_801F2294(pWrite->mFile, pWrite->pBlocks[i].mUnk0, pWrite->mBigEndian);
        fn_801F2294(pWrite->mFile, pWrite->pBlocks[i].mUnk4, pWrite->mBigEndian);
    }
    written = fn_801C9D2C(pWrite->mFile) - pWrite->mCompOffset;
    fn_801F21E4(pWrite->mFile, 0, pWrite->mCompSize - written);
    fn_801C9844(pWrite->mFile, position, 0);
    return 1;
}

static int fn_801F2120(Res_801EDC2C *pWrite, int index, unsigned int offset, unsigned int size)
{
    fn_801C9844(pWrite->mFile, pWrite->mDirOffset + 8, 0);
    if (pWrite->mDirTag != 0x44495231) {
        return 0;
    }
    fn_801C9844(pWrite->mFile, index * 8, 1);
    fn_801F2294(pWrite->mFile, offset, pWrite->mBigEndian);
    fn_801F2294(pWrite->mFile, size, pWrite->mBigEndian);
    return 1;
}

static void fn_801F21B4(int handle, unsigned char value)
{
    fn_801C9A3C(handle, &value, 1, 0);
}

static unsigned int fn_801F21E4(int handle, unsigned char value, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        fn_801C9A3C(handle, &value, 1, 0);
    }
    return count;
}

static void fn_801F2244(int handle, unsigned short value, int bigEndian)
{
    unsigned short out;

    if (bigEndian == 1) {
        out = value;
    } else {
        out = ((unsigned char)value << 8) | (value >> 8);
    }
    fn_801C9A3C(handle, &out, 2, 0);
}

static void fn_801F2294(int handle, unsigned int value, int bigEndian)
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
    fn_801C9A3C(handle, out, 4, 0);
}
