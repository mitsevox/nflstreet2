typedef struct ResWriteEntry_801F201C {
    unsigned int mOffset;
    unsigned int mSize;
} ResWriteEntry_801F201C;

typedef struct ResWrite_801F1B6C {
    int mHandle;
    char mUnknown4[4];
    unsigned int mEndPad;
    unsigned int mPosition;
    unsigned short mNumWritten;
    char mUnknown12;
    unsigned char mBigEndian;
    unsigned short mNumResources;
    char mUnknown16[2];
    unsigned int mDirType;
    char mUnknown1C[8];
    unsigned int mDirSize;
    unsigned int mCompSize;
    char mUnknown2C[4];
    int mDirOffset;
    int mCompOffset;
    char mUnknown38[4];
    int mDataOffset;
    ResWriteEntry_801F201C *pDirEntries;
    char mUnknown44[16];
    ResWriteEntry_801F201C *pCompEntries;
} ResWrite_801F1B6C;

extern int fn_801C9844(int handle, int offset, int mode);
extern int fn_801C9A3C(int handle, void *pBuffer, int size, int a);
extern int fn_801C9D2C(int handle);
extern int fn_801F1838(int a, int b, int c, int d, int e, int f, int g);
extern int fn_801F1D20(ResWrite_801F1B6C *pWrite);
extern void fn_801F1F30(ResWrite_801F1B6C *pWrite);

void fn_801F21B4(int handle, unsigned char value);
unsigned int fn_801F21E4(int handle, unsigned char value, unsigned int count);
void fn_801F2244(int handle, unsigned short value, int bigEndian);
void fn_801F2294(int handle, unsigned int value, int bigEndian);

int fn_801F17E0(unsigned int id)
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

int fn_801F1B6C(ResWrite_801F1B6C *pWrite)
{
    int size;

    if (pWrite->mNumResources != pWrite->mNumWritten) {
        return 0xF0011;
    }
    size = fn_801C9D2C(pWrite->mHandle);
    if (pWrite->mPosition < pWrite->mEndPad && pWrite->mEndPad != -1) {
        fn_801F21E4(pWrite->mHandle, 0, pWrite->mEndPad - pWrite->mPosition);
    }
    size -= pWrite->mDataOffset;
    fn_801C9844(pWrite->mHandle, pWrite->mDataOffset, 0);
    fn_801F2294(pWrite->mHandle, 0x44415441, 0);
    fn_801F2294(pWrite->mHandle, size, pWrite->mBigEndian);
    if (fn_801F1D20(pWrite) == 0) {
        return 0xF0012;
    }
    fn_801F1F30(pWrite);
    fn_801F201C(pWrite);
    return 0;
}

unsigned int fn_801F1C48(unsigned int type, unsigned int count)
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

unsigned int fn_801F1CD4(unsigned int type, unsigned int count)
{
    return fn_801F1C48(type, count) + 8;
}

unsigned int fn_801F1CF8(unsigned int size, unsigned int alignment)
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

int fn_801F201C(ResWrite_801F1B6C *pWrite)
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
    position = fn_801C9D2C(pWrite->mHandle);
    fn_801C9844(pWrite->mHandle, pWrite->mCompOffset, 0);
    fn_801F2294(pWrite->mHandle, 0x434F4D50, 0);
    fn_801F2294(pWrite->mHandle, size, pWrite->mBigEndian);
    for (; i < pWrite->mNumResources; i++) {
        fn_801F2294(pWrite->mHandle, pWrite->pCompEntries[i].mOffset, pWrite->mBigEndian);
        fn_801F2294(pWrite->mHandle, pWrite->pCompEntries[i].mSize, pWrite->mBigEndian);
    }
    written = fn_801C9D2C(pWrite->mHandle) - pWrite->mCompOffset;
    fn_801F21E4(pWrite->mHandle, 0, pWrite->mCompSize - written);
    fn_801C9844(pWrite->mHandle, position, 0);
    return 1;
}

int fn_801F2120(ResWrite_801F1B6C *pWrite, int index, unsigned int offset, unsigned int size)
{
    fn_801C9844(pWrite->mHandle, pWrite->mDirOffset + 8, 0);
    if (pWrite->mDirType != 0x44495231) {
        return 0;
    }
    fn_801C9844(pWrite->mHandle, index * 8, 1);
    fn_801F2294(pWrite->mHandle, offset, pWrite->mBigEndian);
    fn_801F2294(pWrite->mHandle, size, pWrite->mBigEndian);
    return 1;
}

void fn_801F21B4(int handle, unsigned char value)
{
    fn_801C9A3C(handle, &value, 1, 0);
}

unsigned int fn_801F21E4(int handle, unsigned char value, unsigned int count)
{
    unsigned int i;

    for (i = 0; i < count; i++) {
        fn_801C9A3C(handle, &value, 1, 0);
    }
    return count;
}

void fn_801F2244(int handle, unsigned short value, int bigEndian)
{
    unsigned short out;

    if (bigEndian == 1) {
        out = value;
    } else {
        out = ((unsigned char)value << 8) | (value >> 8);
    }
    fn_801C9A3C(handle, &out, 2, 0);
}

void fn_801F2294(int handle, unsigned int value, int bigEndian)
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
