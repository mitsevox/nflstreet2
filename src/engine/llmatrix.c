/* Matrix operations on the current stack: load, multiply, push/pop and the
 * rotation/translation/scale builders the game uses to place players, the ball,
 * cameras and effects, plus sixteen saved matrix slots. */

#include "engine/matrix.h"
#include "engine/llmatrix.h"

MatStack_t *_Mat_pCurStack = 0;
static MatMatrix_t _LLMatrix_SlotArray[16];

void PSMTXConcat(float *pA, float *pB, float *pDst);
void QuatToMatrix(float *pMatrix, float *pQuat);
float fn_80260B1C(float x);
void fn_801CFC14(int angle, float *pSin, float *pCos);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
float MathInverse(float x);

void MatMakeUnitMatrix(float *pMatrix)
{
    float zero = 0.0f;
    float one = 1.0f;

    pMatrix[0] = one;
    pMatrix[4] = zero;
    pMatrix[8] = zero;
    pMatrix[12] = zero;
    pMatrix[1] = zero;
    pMatrix[5] = one;
    pMatrix[9] = zero;
    pMatrix[13] = zero;
    pMatrix[2] = zero;
    pMatrix[6] = zero;
    pMatrix[10] = one;
    pMatrix[14] = zero;
    pMatrix[3] = zero;
    pMatrix[7] = zero;
    pMatrix[11] = zero;
    pMatrix[15] = one;
}

void MatCopyMatrix(float *pDst, float *pSrc)
{
    int i;

    for (i = 0; i < 16; i++) {
        pDst[i] = pSrc[i];
    }
}

float *MatGetCurMatrixPtr(void)
{
    MatStack_t *pStack = _Mat_pCurStack;

    return pStack->mDepth ? pStack->mpMatrices[pStack->mTop] : 0;
}

void MatSetStack(unsigned int index)
{
    _Mat_pCurStack = MatGetStackPtrFromIndex(index);
}

void MatResetStack(void)
{
    _Mat_pCurStack->mTop = 0;
    MatMakeUnitMatrix(*_Mat_pCurStack->mpMatrices);
}

void MatPush(void)
{
    MatStack_t *pStack = _Mat_pCurStack;

    pStack->mTop++;
    MatCopyMatrix(pStack->mpMatrices[pStack->mTop], pStack->mpMatrices[pStack->mTop - 1]);
}

void MatPushUnit(void)
{
    MatStack_t *pStack = _Mat_pCurStack;

    pStack->mTop++;
    MatMakeUnitMatrix(pStack->mpMatrices[pStack->mTop]);
}

void MatPop(void)
{
    _Mat_pCurStack->mTop--;
}

void MatMakeUnit(void)
{
    MatMakeUnitMatrix(_Mat_pCurStack->mpMatrices[_Mat_pCurStack->mTop]);
}

void MatMulMatrices(float *pDst, float *pA, float *pB)
{
    PSMTXConcat(pA, pB, pDst);
}

void MatMulMatrices4x4(float *pDst, float *pA, float *pB)
{
    float result[16];
    int i;
    int j;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j < 4; j++) {
            // FAKEMATCH: B's elements are read through byte offsets ((i + 4n) << 2) so each offset stays a
            // register of its own and the loads keep the base register first, as in the target.
            result[j * 4 + i] = *(float *)((char *)pB + (i << 2)) * pA[j * 4 + 0] +
                                *(float *)((char *)pB + ((i + 4) << 2)) * pA[j * 4 + 1] +
                                *(float *)((char *)pB + ((i + 8) << 2)) * pA[j * 4 + 2] +
                                *(float *)((char *)pB + ((i + 12) << 2)) * pA[j * 4 + 3];
        }
    }
    MatCopyMatrix(pDst, result);
}

void MatCat(float *pMatrix)
{
    float *pCurrent = MatGetCurMatrixPtr();

    MatMulMatrices(pCurrent, pCurrent, pMatrix);
}

void MatCat4x4(float *pMatrix)
{
    float *pCurrent = MatGetCurMatrixPtr();

    MatMulMatrices4x4(pCurrent, pCurrent, pMatrix);
}

void MatLoad(float *pMatrix)
{
    MatCopyMatrix(_Mat_pCurStack->mpMatrices[_Mat_pCurStack->mTop], pMatrix);
}

void MatLLInit(void)
{
}

void MatRotAxis(float *pAxis, int angle)
{
    float m[16];
    float s = fn_801CFB18(angle);
    float c = fn_801CFB94(angle);
    float x = pAxis[0];
    float y = pAxis[1];
    float z = pAxis[2];
    float t = 1.0f - c;
    float *pCurrent;

    m[0] = t * x * x + c;
    m[4] = t * x * y + s * z;
    m[8] = t * x * z - s * y;
    m[1] = t * x * y - s * z;
    m[5] = t * y * y + c;
    m[9] = t * y * z + s * x;
    m[2] = t * x * z + s * y;
    m[6] = t * y * z - s * x;
    m[10] = t * z * z + c;
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[12] = m[13] = m[14] = 0.0f;
    m[15] = 1.0f;
    pCurrent = MatGetCurMatrixPtr();
    MatMulMatrices(m, pCurrent, m);
    pCurrent[0] = m[0];
    pCurrent[4] = m[4];
    pCurrent[8] = m[8];
    pCurrent[1] = m[1];
    pCurrent[5] = m[5];
    pCurrent[9] = m[9];
    pCurrent[2] = m[2];
    pCurrent[6] = m[6];
    pCurrent[10] = m[10];
}

void MatRotQuat(float *pQuat)
{
    float m[16];
    float *pCurrent;

    MatMakeUnitMatrix(m);
    QuatToMatrix(m, pQuat);
    pCurrent = MatGetCurMatrixPtr();
    MatMulMatrices(m, pCurrent, m);
    pCurrent[0] = m[0];
    pCurrent[4] = m[4];
    pCurrent[8] = m[8];
    pCurrent[1] = m[1];
    pCurrent[5] = m[5];
    pCurrent[9] = m[9];
    pCurrent[2] = m[2];
    pCurrent[6] = m[6];
    pCurrent[10] = m[10];
}

void MatRotX(int angle)
{
    float *p = MatGetCurMatrixPtr();
    float m[16];
    float s;
    float c;

    fn_801CFC14(angle, &s, &c);
    m[1] = p[1] * c + p[2] * s;
    m[2] = p[1] * -s + p[2] * c;
    m[5] = p[5] * c + p[6] * s;
    m[6] = p[5] * -s + p[6] * c;
    m[9] = p[9] * c + p[10] * s;
    m[10] = p[9] * -s + p[10] * c;
    p[1] = m[1];
    p[5] = m[5];
    p[9] = m[9];
    p[2] = m[2];
    p[6] = m[6];
    p[10] = m[10];
}

void MatRotY(int angle)
{
    float *p = MatGetCurMatrixPtr();
    float m[16];
    float s;
    float c;

    fn_801CFC14(angle, &s, &c);
    m[0] = p[0] * c + p[2] * -s;
    m[2] = p[0] * s + p[2] * c;
    m[4] = p[4] * c + p[6] * -s;
    m[6] = p[4] * s + p[6] * c;
    m[8] = p[8] * c + p[10] * -s;
    m[10] = p[8] * s + p[10] * c;
    p[0] = m[0];
    p[4] = m[4];
    p[8] = m[8];
    p[2] = m[2];
    p[6] = m[6];
    p[10] = m[10];
}

void MatRotZ(int angle)
{
    float *p = MatGetCurMatrixPtr();
    float m[16];
    float s;
    float c;

    fn_801CFC14(angle, &s, &c);
    m[0] = p[0] * c + p[1] * s;
    m[1] = p[0] * -s + p[1] * c;
    m[4] = p[4] * c + p[5] * s;
    m[5] = p[4] * -s + p[5] * c;
    m[8] = p[8] * c + p[9] * s;
    m[9] = p[8] * -s + p[9] * c;
    p[0] = m[0];
    p[4] = m[4];
    p[8] = m[8];
    p[1] = m[1];
    p[5] = m[5];
    p[9] = m[9];
}

void MatRotZYX(int z, int y, int x)
{
    MatRotZ(z);
    MatRotY(y);
    MatRotX(x);
}

void MatSetAxes(float *pMatrix, float *pX, float *pY, float *pZ)
{
    pMatrix[0] = pX[0];
    pMatrix[4] = pX[1];
    pMatrix[8] = pX[2];
    pMatrix[1] = pY[0];
    pMatrix[5] = pY[1];
    pMatrix[9] = pY[2];
    pMatrix[2] = pZ[0];
    pMatrix[6] = pZ[1];
    pMatrix[10] = pZ[2];
}

void MatTranslate(float *pPos)
{
    float *p = MatGetCurMatrixPtr();
    float x = pPos[0] * p[0] + pPos[1] * p[1] + pPos[2] * p[2];
    float y = pPos[0] * p[4] + pPos[1] * p[5] + pPos[2] * p[6];
    float z = pPos[0] * p[8] + pPos[1] * p[9] + pPos[2] * p[10];

    p[3] = p[3] + x;
    p[7] = p[7] + y;
    p[11] = p[11] + z;
}

void MatScale(float scale)
{
    float *p = MatGetCurMatrixPtr();

    p[0] *= scale;
    p[4] *= scale;
    p[8] *= scale;
    p[1] *= scale;
    p[5] *= scale;
    p[9] *= scale;
    p[2] *= scale;
    p[6] *= scale;
    p[10] *= scale;
}

void MatScaleCol(float x, float y, float z)
{
    float *p = MatGetCurMatrixPtr();

    p[0] *= x;
    p[4] *= x;
    p[8] *= x;
    p[1] *= y;
    p[5] *= y;
    p[9] *= y;
    p[2] *= z;
    p[6] *= z;
    p[10] *= z;
}

void MatScalePos(float scale)
{
    float *p = MatGetCurMatrixPtr();

    p[3] *= scale;
    p[7] *= scale;
    p[11] *= scale;
}

void MatTranspose(void)
{
    float *p = MatGetCurMatrixPtr();
    float t;

    t = p[4];
    p[4] = p[1];
    p[1] = t;
    t = p[8];
    p[8] = p[2];
    p[2] = t;
    t = p[9];
    p[9] = p[6];
    p[6] = t;
}

void MatInvertRigid(void)
{
    float m[16];
    float pos[3];
    float t;

    MatStore(m);
    t = m[4];
    m[4] = m[1];
    m[1] = t;
    t = m[8];
    m[8] = m[2];
    m[2] = t;
    t = m[9];
    m[9] = m[6];
    m[6] = t;
    pos[0] = -m[3];
    pos[1] = -m[7];
    pos[2] = -m[11];
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    MatLoad(m);
    MatTranslate(pos);
}

void MatStore(float *pMatrix)
{
    MatCopyMatrix(pMatrix, MatGetCurMatrixPtr());
}

void MatGetPos(float *pPos)
{
    float *p = MatGetCurMatrixPtr();

    pPos[0] = p[3];
    pPos[1] = p[7];
    pPos[2] = p[11];
}

void MatGetRotFromMatrixZYX(int *pAngles, float *pMatrix)
{
    float sy = -pMatrix[8];
    float t = sy * sy;
    float cy;
    float inv;
    float sx;
    float cx;
    float sz;
    float cz;

    if (!(t <= 1.0f)) {
        t = 1.0f;
    }
    cy = fn_80260B1C(1.0f - t);
    if (!(cy <= 1e-07f)) {
        inv = MathInverse(cy);
        sx = pMatrix[9] * inv;
        cx = pMatrix[10] * inv;
        sz = pMatrix[4] * inv;
        cz = pMatrix[0] * inv;
    } else {
        sx = -pMatrix[6];
        cx = pMatrix[5];
        cz = 1.0f;
        sz = 0.0f;
    }
    pAngles[0] = fn_801CFE40(sx, cx);
    pAngles[1] = fn_801CFE40(sy, cy);
    pAngles[2] = fn_801CFE40(sz, cz);
}

void MatGetRotFromMatrixYZX(int *pAngles, float *pMatrix)
{
    float sz = pMatrix[4];
    float t = sz * sz;
    float cz;
    float inv;
    float sx;
    float cx;
    float sy;
    float cy;

    if (!(t <= 1.0f)) {
        t = 1.0f;
    }
    cz = fn_80260B1C(1.0f - t);
    if (!(cz <= 1e-06f)) {
        inv = 1.0f / cz;
        sx = -pMatrix[6] * inv;
        cx = pMatrix[5] * inv;
        sy = -pMatrix[8] * inv;
        cy = pMatrix[0] * inv;
    } else {
        cy = 1.0f;
        sx = -pMatrix[6];
        cx = pMatrix[5];
        sy = 0.0f;
    }
    pAngles[0] = fn_801CFE40(sx, cx);
    pAngles[1] = fn_801CFE40(sy, cy);
    pAngles[2] = fn_801CFE40(sz, cz);
}

void MatGetRotByOrder(int *pAngles, unsigned int order)
{
    float *p = MatGetCurMatrixPtr();

    switch (order) {
    case 0:
        MatGetRotFromMatrixZYX(pAngles, p);
        break;
    case 1:
        break;
    case 2:
        MatGetRotFromMatrixYZX(pAngles, p);
        break;
    }
}

void MatSetSlot(int slot, float *pMatrix)
{
    MatCopyMatrix(_LLMatrix_SlotArray[slot], pMatrix);
}

void MatGetSlot(int slot, float *pMatrix)
{
    MatCopyMatrix(pMatrix, _LLMatrix_SlotArray[slot]);
}

void MatLoadSlot(int slot)
{
    MatLoad(_LLMatrix_SlotArray[slot]);
}

void MatStoreSlot(int slot)
{
    MatStore(_LLMatrix_SlotArray[slot]);
}

void MatCatSlot(int slot)
{
    MatCat4x4(_LLMatrix_SlotArray[slot]);
}
