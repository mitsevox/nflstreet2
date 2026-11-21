/* Matrix stacks: indexed stacks of 4x4 float matrices. */

#include "engine/matrix.h"
#include "engine/SysSetLastErrorFunc.h"
#include "game/fn_801D2B7C.h"
#include "engine/llmatrix.h"

static unsigned char _Mat_ModuleActive = 0;

/* The matrix stacks MatInit allocates, and their number. */
static MatStack_t *_Mat_pStacks = 0;
static unsigned int _Mat_NumStacks = 0;

void Vec3CrossProduct(float *pOut, float *pA, float *pB);
void Vec3Normalize(float *pOut, float *p);
int Vec3GetAngle(float *pA, float *pB);

int MatDelStack(unsigned int index);

MatStack_t *MatGetStackPtrFromIndex(unsigned int index)
{
    return index < _Mat_NumStacks ? &_Mat_pStacks[index] : 0;
}

int MatInit(int numStacks)
{
    int result = 0;
    int count;
    int i;

    if (!_Mat_ModuleActive) {
        count = numStacks + 8;
        _Mat_pStacks = fn_801D2BB0(1, count * sizeof(MatStack_t), 0, 0);
        if (_Mat_pStacks) {
            for (i = 0; i < count; i++) {
                _Mat_pStacks[i].mDepth = 0;
                _Mat_pStacks[i].mTop = 0;
                _Mat_pStacks[i].mpMatrices = 0;
            }
            _Mat_NumStacks = count;
            MatLLInit();
            _Mat_ModuleActive = 1;
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

    if (_Mat_ModuleActive) {
        for (i = 0; i < _Mat_NumStacks; i++) {
            if (_Mat_pStacks[i].mDepth) {
                MatDelStack(i);
            }
        }
        result = fn_801D2BD0(_Mat_pStacks);
        _Mat_pStacks = 0;
        _Mat_NumStacks = 0;
        _Mat_ModuleActive = 0;
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

    Vec3CrossProduct(axis, pFrom, pTo);
    Vec3Normalize(axis, axis);
    MatRotAxis(axis, Vec3GetAngle(pFrom, pTo));
}
