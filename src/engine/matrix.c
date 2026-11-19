/* Matrix stacks: indexed stacks of 4x4 float matrices. */

#include "engine/matrix.h"
#include "engine/SysSetLastErrorFunc.h"
#include "game/fn_801D2B7C.h"
#include "engine/llmatrix.h"

extern unsigned char lbl_803EBCB4;
extern MatStack_t *lbl_803EBCB8;
extern unsigned int lbl_803EBCBC;

void fn_802277DC(float *pOut, float *pA, float *pB);
void fn_802271F0(float *pOut, float *p);
int Vec3GetAngle(float *pA, float *pB);

int MatDelStack(unsigned int index);

MatStack_t *MatGetStackPtrFromIndex(unsigned int index)
{
    return index < lbl_803EBCBC ? &lbl_803EBCB8[index] : 0;
}

int MatInit(int numStacks)
{
    int result = 0;
    int count;
    int i;

    if (!lbl_803EBCB4) {
        count = numStacks + 8;
        lbl_803EBCB8 = fn_801D2BB0(1, count * sizeof(MatStack_t), 0, 0);
        if (lbl_803EBCB8) {
            for (i = 0; i < count; i++) {
                lbl_803EBCB8[i].mDepth = 0;
                lbl_803EBCB8[i].mTop = 0;
                lbl_803EBCB8[i].mpMatrices = 0;
            }
            lbl_803EBCBC = count;
            MatLLInit();
            lbl_803EBCB4 = 1;
        } else {
            result = SysGetLastError();
        }
    } else {
        result = 0x50001;
    }
    SysSetLastErrorFunc(result);
    return result;
}

int MatShutdown(void)
{
    int result = 0;
    unsigned int i;

    if (lbl_803EBCB4) {
        for (i = 0; i < lbl_803EBCBC; i++) {
            if (lbl_803EBCB8[i].mDepth) {
                MatDelStack(i);
            }
        }
        result = fn_801D2BD0(lbl_803EBCB8);
        lbl_803EBCB8 = 0;
        lbl_803EBCBC = 0;
        lbl_803EBCB4 = 0;
    } else {
        result = 0x50002;
    }
    SysSetLastErrorFunc(result);
    return result;
}

int MatNewStack(unsigned int index, unsigned int depth)
{
    MatStack_t *pStack = MatGetStackPtrFromIndex(index);
    MatMatrix_t *pMatrices = fn_801D2BB0(1, depth * sizeof(MatMatrix_t), 0, 0);
    int result;

    if (pMatrices) {
        pStack->mDepth = depth;
        pStack->mTop = 0;
        pStack->mpMatrices = pMatrices;
        result = 0;
        MatMakeUnitMatrix(*pMatrices);
    } else {
        result = SysGetLastError();
    }
    SysSetLastErrorFunc(result);
    return result;
}

int MatDelStack(unsigned int index)
{
    MatStack_t *pStack = MatGetStackPtrFromIndex(index);
    int result = fn_801D2BD0(pStack->mpMatrices);

    if (!result) {
        pStack->mDepth = 0;
        pStack->mTop = 0;
        pStack->mpMatrices = 0;
    } else {
        result = SysGetLastError();
    }
    SysSetLastErrorFunc(result);
    return result;
}

void MatRotVecToVec(float *pFrom, float *pTo)
{
    float axis[4];

    fn_802277DC(axis, pFrom, pTo);
    fn_802271F0(axis, axis);
    MatRotAxis(axis, Vec3GetAngle(pFrom, pTo));
}
