/* Animation file extension: after an animation file loads, fixes up its compression tables and moves
   its motion data out to auxiliary RAM; when a player animation needs a motion it is read back from
   auxiliary RAM (and decompressed) through a small staging buffer, and the copy is freed on unload. */
#include <dolphin/types.h>
#include "game/AnimFileFormat.h"
#include "game/AnimFrameHeader.h"

extern "C" {
void *fn_801D2BB0(int a, int size, int c, int d);
void fn_801C1D98(void *destination, char *source, int size);
int fn_801D3148(int a, void *allocation);
void *fn_801D310C(void *allocation, int size, int c, int d);
void fn_801D2BD0(void *allocation);
void fn_801C1E78(char *pDst, void *pSrc, int size);
void fn_801C1FBC(void *destination, void *source, unsigned int size);
}

/* Two 0xC0-byte staging buffers for reads from ARAM, used alternately. */
static unsigned char AnimExtn_iCurrBuffer;
static char AnimExtn_ARamTransferBuffer[2][0xC0] ATTRIBUTE_ALIGN(32);

void _AnimExtnRelocateMotion(AnimFileFormat_t *file)
{
    unsigned int i;
    unsigned int j;
    int size = fn_801D3148(1, file);
    unsigned int start = (unsigned int)file;
    if (file->flags & 4) {
        for (i = 0; i < file->groups->count; ++i) {
            start = (unsigned int)file->groupMotion[i].motion[0];
            for (j = 0; j < file->groupMotion[i].count; ++j) {
                if ((unsigned int)file->groupMotion[i].motion[j] < start)
                    file->groupMotion[i].motion[j] = (char *)start;
            }
        }
    } else {
        start = (unsigned int)file->motion[0];
        for (j = 0; j < file->motionCount; ++j) {
            if ((unsigned int)file->motion[j] < start)
                file->motion[j] = (char *)start;
        }
    }
    int headerSize = start - (unsigned int)file;
    int motionSize = size - headerSize;
    unsigned int copy = (unsigned int)fn_801D2BB0(16, motionSize, 0, 0);
    fn_801C1D98((void *)copy, (char *)start, (motionSize + 31) & ~31);
    fn_801D310C(file, headerSize, 0, 0);
    if (file->flags & 4) {
        for (i = 0; i < file->groups->count; ++i) {
            for (j = 0; j < file->groupMotion[i].count; ++j)
                file->groupMotion[i].motion[j] = (char *)((unsigned int)file->groupMotion[i].motion[j] - start + copy);
        }
    } else {
        for (j = 0; j < file->motionCount; ++j)
            file->motion[j] = (char *)((unsigned int)file->motion[j] - start + copy);
    }
}

void _AnimExtnRelocateCompressTable(AnimFileFormat_t *file)
{
    AnimQuantContext *table;
    if (file->flags & 1) {
        if (file->flags & 4) {
            file->compress = 0;
            for (int i = 0; i < (int)file->groups->count; ++i) {
                if (file->groupMotion[i].compress) {
                    table = (AnimQuantContext *)((char *)file + (unsigned int)file->groupMotion[i].compress);
                    file->groupMotion[i].compress = table;
                    table->mUnknown4.mUnknown0 = (short *)((char *)file + (unsigned int)table->mUnknown4.mUnknown0);
                    table->mUnknown4.mUnknown4 = (short *)((char *)file + (unsigned int)table->mUnknown4.mUnknown4);
                    table->mUnknownC.mUnknown0 = (short *)((char *)file + (unsigned int)table->mUnknownC.mUnknown0);
                    table->mUnknownC.mUnknown4 = (short *)((char *)file + (unsigned int)table->mUnknownC.mUnknown4);
                    table->mpUnknown14 = (unsigned char *)((char *)file + (unsigned int)table->mpUnknown14);
                }
            }
        } else {
            table = (AnimQuantContext *)((char *)file + (unsigned int)file->compress);
            file->compress = table;
            table->mUnknown4.mUnknown0 = (short *)((char *)file + (unsigned int)table->mUnknown4.mUnknown0);
            table->mUnknown4.mUnknown4 = (short *)((char *)file + (unsigned int)table->mUnknown4.mUnknown4);
            table->mUnknownC.mUnknown0 = (short *)((char *)file + (unsigned int)table->mUnknownC.mUnknown0);
            table->mUnknownC.mUnknown4 = (short *)((char *)file + (unsigned int)table->mUnknownC.mUnknown4);
            table->mpUnknown14 = (unsigned char *)((char *)file + (unsigned int)table->mpUnknown14);
        }
    }
}

void AnimExtnRelocateFile(AnimFileFormat_t *file)
{
    _AnimExtnRelocateCompressTable(file);
    if (file->flags & 0x200)
        _AnimExtnRelocateMotion(file);
}

extern "C" void AnimExtnFreeFile(AnimFileFormat_t *file)
{
    if ((file->flags & 0x200) && file->motion[0])
        fn_801D2BD0(file->motion[0]);
}

extern "C" void AnimExtnReadMotion(AnimFileFormat_t *file, int a, unsigned char *destination, unsigned int source, unsigned int size, int group)
{
    char *buffer = AnimExtn_ARamTransferBuffer[AnimExtn_iCurrBuffer];
    AnimExtn_iCurrBuffer = AnimExtn_iCurrBuffer == 0;
    unsigned int offset = source & 31;
    fn_801C1E78(buffer, (void *)(source & ~31), 0xC0);
    if (file->flags & 1) {
        if (file->flags & 4)
            AnimDecompressFrame(destination, (unsigned char *)source, file->groupMotion[group].compress, 0);
        else
            AnimDecompressFrame(destination, (unsigned char *)buffer + offset, file->compress, 0);
    } else {
        fn_801C1FBC(destination, buffer + offset, size);
    }
}
