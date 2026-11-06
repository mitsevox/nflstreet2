#include "engine/cu_801BDA30.h"

typedef struct Quat_801BC67C {
    float mValues[4];
} Quat_801BC67C;

int abs(int x);

void QuatFromEulerYZX(Quat_801BC67C *pOut, int x, int y, int z);
void QuatSlerp(Quat_801BC67C *pOut, Quat_801BC67C *pA, Quat_801BC67C *pB, float t);
void QuatToEulerYZX(Triple_801BCA74 *pOut, Quat_801BC67C *pQuat);
void Orient3Lerp(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t);

unsigned short fn_801BC65C(int state, AnimFileFormat_t *pFile, Slot_801BE594 *pSlot)
{
    if (pFile->flags & 4)
        return pSlot->mUnknown6;
    return 0xFFFF;
}

void fn_801BC67C(Triple_801BCA74 *pOut, Triple_801BCA74 *pA, Triple_801BCA74 *pB, float t)
{
    Quat_801BC67C b;
    Quat_801BC67C a;
    int dx = (pA->mUnknown0 - pB->mUnknown0) << 8 >> 8;
    int dy = (pA->mUnknown4 - pB->mUnknown4) << 8 >> 8;
    int dz = (pA->mUnknown8 - pB->mUnknown8) << 8 >> 8;

    if (abs(dx) + abs(dy) + abs(dz) > 0x400000) {
        QuatFromEulerYZX(&a, pA->mUnknown4, pA->mUnknown8, pA->mUnknown0);
        QuatFromEulerYZX(&b, pB->mUnknown4, pB->mUnknown8, pB->mUnknown0);
        QuatSlerp(&a, &a, &b, t);
        QuatToEulerYZX(pOut, &a);
    } else {
        Orient3Lerp(pOut, pA, pB, t);
    }
}

AnimQuantContext *fn_801BC780(AnimFileFormat_t *pFile, int group)
{
    if ((pFile->flags & 1) && !(pFile->flags & 0x200)) {
        if (pFile->flags & 4)
            return pFile->groupMotion[group].compress;
        return pFile->compress;
    }
    return 0;
}
