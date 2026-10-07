#include "game/AnimFileFormat.h"

extern "C" {
void *fn_801D2BB0(int a, int size, int c, int d);
void fn_801C1D98(void *destination, char *source, int size);
int fn_801D3148(int a, void *allocation);
void *fn_801D310C(void *allocation, int size, int c, int d);

}

void _AnimExtnRelocateMotion(AnimFileFormat_t *file)
{
    int size = fn_801D3148(1, file);
    char *start = (char *)file;
    if (file->flags & 4) {
        for (unsigned int i = 0; i < file->groups->count; ++i) {
            start = file->groupMotion[i].motion[0];
            for (unsigned int j = 0; j < file->groupMotion[i].count; ++j) {
                if ((unsigned int)file->groupMotion[i].motion[j] < (unsigned int)start)
                    file->groupMotion[i].motion[j] = start;
            }
        }
    } else {
        start = file->motion[0];
        for (unsigned int i = 0; i < file->motionCount; ++i) {
            if ((unsigned int)file->motion[i] < (unsigned int)start)
                file->motion[i] = start;
        }
    }
    int headerSize = start - (char *)file;
    int motionSize = size - headerSize;
    char *copy = (char *)fn_801D2BB0(16, motionSize, 0, 0);
    fn_801C1D98(copy, start, (motionSize + 31) & ~31);
    fn_801D310C(file, headerSize, 0, 0);
    if (file->flags & 4) {
        for (unsigned int i = 0; i < file->groups->count; ++i) {
            for (unsigned int j = 0; j < file->groupMotion[i].count; ++j)
                file->groupMotion[i].motion[j] = file->groupMotion[i].motion[j] - start + copy;
        }
    } else {
        for (unsigned int i = 0; i < file->motionCount; ++i)
            file->motion[i] = file->motion[i] - start + copy;
    }
}

void _AnimExtnRelocateCompressTable(AnimFileFormat_t *file)
{
    if (file->flags & 1) {
        if (file->flags & 4) {
            file->compress = 0;
            for (int i = 0; i < (int)file->groups->count; ++i) {
                if (file->groupMotion[i].compress) {
                    AnimCompressTableView *table = (AnimCompressTableView *)((char *)file + (unsigned int)file->groupMotion[i].compress);
                    file->groupMotion[i].compress = table;
                    table->array4 = (char *)file + (unsigned int)table->array4;
                    table->array8 = (char *)file + (unsigned int)table->array8;
                    table->arrayC = (char *)file + (unsigned int)table->arrayC;
                    table->array10 = (char *)file + (unsigned int)table->array10;
                    table->array14 = (char *)file + (unsigned int)table->array14;
                }
            }
        } else {
            AnimCompressTableView *table = (AnimCompressTableView *)((char *)file + (unsigned int)file->compress);
            file->compress = table;
            table->array4 = (char *)file + (unsigned int)table->array4;
            table->array8 = (char *)file + (unsigned int)table->array8;
            table->arrayC = (char *)file + (unsigned int)table->arrayC;
            table->array10 = (char *)file + (unsigned int)table->array10;
            table->array14 = (char *)file + (unsigned int)table->array14;
        }
    }
}

void AnimExtnRelocateFile(AnimFileFormat_t *file)
{
    _AnimExtnRelocateCompressTable(file);
    if (file->flags & 0x200)
        _AnimExtnRelocateMotion(file);
}
