#include "engine/cu_801BA03C.ba03c-1.h"

typedef struct Object_801BE594 {
    unsigned char mUnknown0[6];
    unsigned short mUnknown6;
    unsigned char mUnknown8[68];
    float mUnknown4C;
} Object_801BE594;

typedef struct Quat_801BC67C {
    float mValues[4];
} Quat_801BC67C;

int abs(int x);

void fn_801EBFA0(Quat_801BC67C *pOut, int x, int y, int z);
void fn_801EC048(Quat_801BC67C *pOut, Quat_801BC67C *pA, Quat_801BC67C *pB, float t);
void fn_801EBD8C(int *pOut, Quat_801BC67C *pQuat);
void fn_801CF810(int *pOut, int *pA, int *pB, float t);

unsigned short fn_801BC65C(int state, Object_801BC084 *pFile, Object_801BE594 *pInfo)
{
    if (pFile->mFlags & 4)
        return pInfo->mUnknown6;
    return 0xFFFF;
}

void fn_801BC67C(int *pOut, int *pA, int *pB, float t)
{
    Quat_801BC67C b;
    Quat_801BC67C a;
    int dx = (pA[0] - pB[0]) << 8 >> 8;
    int dy = (pA[1] - pB[1]) << 8 >> 8;
    int dz = (pA[2] - pB[2]) << 8 >> 8;

    if (abs(dx) + abs(dy) + abs(dz) > 0x400000) {
        fn_801EBFA0(&a, pA[1], pA[2], pA[0]);
        fn_801EBFA0(&b, pB[1], pB[2], pB[0]);
        fn_801EC048(&a, &a, &b, t);
        fn_801EBD8C(pOut, &a);
    } else {
        fn_801CF810(pOut, pA, pB, t);
    }
}

void *fn_801BC780(Object_801BC084 *pFile, int group)
{
    if ((pFile->mFlags & 1) && !(pFile->mFlags & 0x200)) {
        if (pFile->mFlags & 4)
            return pFile->mpGroupMotion[group].mpCompress;
        return pFile->mpCompress;
    }
    return 0;
}
