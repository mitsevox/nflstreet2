/* Matrix stacks: indexed stacks of 4x4 float matrices. */

#include "engine/cu_801D0110.h"
#include "engine/fn_801F7BD4.h"
#include "game/fn_801D2B7C.h"

extern unsigned char lbl_803EBCB4;
extern MatStack_801D0110 *lbl_803EBCB8;
extern unsigned int lbl_803EBCBC;

void fn_802277DC(float *pDst, float *pA, float *pB);
void fn_802271F0(float *pDst, float *pSrc);
int fn_80227040(float *pA, float *pB);

int fn_801D0310(unsigned int index);
void fn_801D03D0(float *pMatrix);
void fn_801D070C(void);
void fn_801D0710(float *pAxis, int angle);

MatStack_801D0110 *fn_801D0110(unsigned int index)
{
    return index < lbl_803EBCBC ? &lbl_803EBCB8[index] : 0;
}

int fn_801D0134(int numStacks)
{
    int result = 0;
    int count;
    int i;

    if (!lbl_803EBCB4) {
        count = numStacks + 8;
        lbl_803EBCB8 = fn_801D2BB0(1, count * sizeof(MatStack_801D0110), 0, 0);
        if (lbl_803EBCB8) {
            for (i = 0; i < count; i++) {
                lbl_803EBCB8[i].mDepth = 0;
                lbl_803EBCB8[i].mTop = 0;
                lbl_803EBCB8[i].mpMatrices = 0;
            }
            lbl_803EBCBC = count;
            fn_801D070C();
            lbl_803EBCB4 = 1;
        } else {
            result = fn_801F7C88();
        }
    } else {
        result = 0x50001;
    }
    fn_801F7BD4(result);
    return result;
}

int fn_801D01EC(void)
{
    int result = 0;
    unsigned int i;

    if (lbl_803EBCB4) {
        for (i = 0; i < lbl_803EBCBC; i++) {
            if (lbl_803EBCB8[i].mDepth) {
                fn_801D0310(i);
            }
        }
        result = fn_801D2BD0(lbl_803EBCB8);
        lbl_803EBCB8 = 0;
        lbl_803EBCBC = 0;
        lbl_803EBCB4 = 0;
    } else {
        result = 0x50002;
    }
    fn_801F7BD4(result);
    return result;
}

int fn_801D0290(unsigned int index, unsigned int depth)
{
    MatStack_801D0110 *pStack = fn_801D0110(index);
    Mtx_801D0110 *pMatrices = fn_801D2BB0(1, depth * sizeof(Mtx_801D0110), 0, 0);
    int result;

    if (pMatrices) {
        pStack->mDepth = depth;
        pStack->mTop = 0;
        pStack->mpMatrices = pMatrices;
        result = 0;
        fn_801D03D0(*pMatrices);
    } else {
        result = fn_801F7C88();
    }
    fn_801F7BD4(result);
    return result;
}

int fn_801D0310(unsigned int index)
{
    MatStack_801D0110 *pStack = fn_801D0110(index);
    int result = fn_801D2BD0(pStack->mpMatrices);

    if (!result) {
        pStack->mDepth = 0;
        pStack->mTop = 0;
        pStack->mpMatrices = 0;
    } else {
        result = fn_801F7C88();
    }
    fn_801F7BD4(result);
    return result;
}

void fn_801D0370(float *pFrom, float *pTo)
{
    float axis[4];

    fn_802277DC(axis, pFrom, pTo);
    fn_802271F0(axis, axis);
    fn_801D0710(axis, fn_80227040(pFrom, pTo));
}
