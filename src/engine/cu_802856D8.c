/* Partial source for the range 0x802856D8-0x80285A90 (neutral file name). */

#include <dolphin/os.h>
#include <dolphin/gba.h>

extern int FileOpenFileDevice(const char *pName, int device);
extern int FileClose(int handle);
extern int FileSeek(int handle, int offset, unsigned int whence);
extern int FileReadCallback(int handle, void *pBuffer, int size, void (*pCallback)(int, int, int));
extern int FilePerformWrite(int handle, int pos, void *pBuffer, int size);
void *fn_801C1F94();

typedef struct Struct_803E990C
{
    OSTick mUnknown00;
    char mUnknown04[4];
    int mUnknown08;
    char mUnknown0C[0x260 - 0xC];
} Struct_803E990C;

typedef struct File_80285808
{
    int mHandle;
    int mPosition;
    const void *mUnknown08;
} File_80285808;

typedef struct Struct_80285A24
{
    char mUnknown00[4];
    unsigned int mUnknown04;
    void *mUnknown08;
    char mUnknown0C[4];
    void *(*mUnknown10)(void *);
    char *mUnknown14;
} Struct_80285A24;

extern OSThread lbl_803BA580;
extern Struct_803E990C lbl_803E990C[];
extern int lbl_803EC590;
extern OSCond lbl_803ED4BC;

void fn_802856D8(void)
{
    int i;

    GBAInit();
    for (i = 0; i < 4; i++)
        fn_801C1F94(&lbl_803E990C[i], 0, sizeof(Struct_803E990C));
}

int fn_8028572C(int channel)
{
    OSTick tick;
    u8 status;

    if (lbl_803E990C[channel].mUnknown08 < 2 || lbl_803E990C[channel].mUnknown08 > 4)
    {
        tick = OSGetTick();
        if (GBAGetStatus(channel, &status) == 0)
        {
            lbl_803E990C[channel].mUnknown00 = tick;
            lbl_803E990C[channel].mUnknown08 = 1;
        }
        else if (OSTicksToSeconds(tick - lbl_803E990C[channel].mUnknown00) != 0)
        {
            lbl_803E990C[channel].mUnknown08 = 0;
        }
    }
    return lbl_803E990C[channel].mUnknown08;
}

void fn_802857D8(void)
{
    if (lbl_803EC590 != 0)
        OSSignalCond(&lbl_803ED4BC);
}

int fn_80285808(File_80285808 *pFile, const void *pValue, const char *pName, int write)
{
    int handle;

    if (write)
        handle = FileOpenFileDevice(pName, 44);
    else
        handle = FileOpenFileDevice(pName, 36);
    if (handle < 0)
        return 36;
    pFile->mHandle = handle;
    pFile->mPosition = 0;
    pFile->mUnknown08 = pValue;
    return 0;
}

int fn_80285878(File_80285808 *pFile)
{
    if (pFile->mHandle < 0)
        return 3;
    if (FileClose(pFile->mHandle) != 0)
        return 36;
    return 0;
}

int fn_802858BC(File_80285808 *pFile, void *pBuffer, int size, int *pCount)
{
    int count;

    if (pFile->mHandle < 0)
        return 3;
    count = FilePerformWrite(pFile->mHandle, pFile->mPosition, pBuffer, size);
    if (count < 0)
    {
        *pCount = 0;
        return 36;
    }
    *pCount = count;
    pFile->mPosition += count;
    return 0;
}

int fn_80285940(File_80285808 *pFile, void *pBuffer, int size, int *pCount)
{
    int count;

    if (pFile->mHandle < 0)
        return 3;
    count = FileReadCallback(pFile->mHandle, pBuffer, size, 0);
    if (count < 0)
    {
        *pCount = 0;
        return 36;
    }
    *pCount = count;
    pFile->mPosition += count;
    return 0;
}

int fn_802859B4(File_80285808 *pFile, int offset)
{
    if (pFile->mHandle < 0)
        return 3;
    if (FileSeek(pFile->mHandle, offset, 1) != 0)
        return 36;
    pFile->mPosition += offset;
    return 0;
}

int fn_80285A1C(void)
{
    return 0;
}

void fn_80285A24(Struct_80285A24 *p)
{
    if ((unsigned char)OSCreateThread(&lbl_803BA580, p->mUnknown10, p->mUnknown08, p->mUnknown14 + p->mUnknown04, p->mUnknown04, 22, 1))
        OSResumeThread(&lbl_803BA580);
}

void fn_80285A8C(void)
{
}
