/* Matrix stacks: indexed stacks of 4x4 float matrices with a current stack,
 * plus rotation/translation/scale builders. */

typedef float Mtx_801D0110[16];

typedef struct MatStack_801D0110 {
    unsigned int mDepth;
    int mTop;
    Mtx_801D0110 *mpMatrices;
} MatStack_801D0110;

extern unsigned char lbl_803EBCB4;
extern MatStack_801D0110 *lbl_803EBCB8;
extern unsigned int lbl_803EBCBC;
extern MatStack_801D0110 *lbl_803EBCC0;

void *fn_801D2BB0(int heap, int size, int a, int b);
int fn_801D2BD0(void *p);
int fn_801F7C88(void);
void fn_801F7BD4(int error);
void fn_8024AA18(float *pA, float *pB, float *pDst);
void fn_802277DC(float *pDst, float *pA, float *pB);
void fn_802271F0(float *pDst, float *pSrc);
int fn_80227040(float *pA, float *pB);
void fn_801EB814(float *pMatrix, float *pQuat);
float fn_80260B1C(float x);
void fn_801CFC14(int angle, float *pSin, float *pCos);
float fn_801CFB18(int angle);
float fn_801CFB94(int angle);
int fn_801CFE40(float y, float x);
float fn_801CFFA0(float x);

extern Mtx_801D0110 lbl_803847C0[];

int fn_801D0310(unsigned int index);
void fn_801D03D0(float *pMatrix);
void fn_801D070C(void);
void fn_801D0710(float *pAxis, int angle);
float *fn_801D0444(void);
void fn_801D06D4(float *pMatrix);
void fn_801D069C(float *pMatrix);
void fn_801D0C58(float *pPos);
void fn_801D0F80(float *pMatrix);

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

void fn_801D03D0(float *pMatrix)
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

void fn_801D0424(float *pDst, float *pSrc)
{
    int i;

    for (i = 0; i < 16; i++) {
        pDst[i] = pSrc[i];
    }
}

float *fn_801D0444(void)
{
    MatStack_801D0110 *pStack = lbl_803EBCC0;

    return pStack->mDepth ? pStack->mpMatrices[pStack->mTop] : 0;
}

void fn_801D0470(unsigned int index)
{
    lbl_803EBCC0 = fn_801D0110(index);
}

void fn_801D0494(void)
{
    lbl_803EBCC0->mTop = 0;
    fn_801D03D0(*lbl_803EBCC0->mpMatrices);
}

void fn_801D04C4(void)
{
    MatStack_801D0110 *pStack = lbl_803EBCC0;

    pStack->mTop++;
    fn_801D0424(pStack->mpMatrices[pStack->mTop], pStack->mpMatrices[pStack->mTop - 1]);
}

void fn_801D0508(void)
{
    MatStack_801D0110 *pStack = lbl_803EBCC0;

    pStack->mTop++;
    fn_801D03D0(pStack->mpMatrices[pStack->mTop]);
}

void fn_801D0544(void)
{
    lbl_803EBCC0->mTop--;
}

void fn_801D0558(void)
{
    fn_801D03D0(lbl_803EBCC0->mpMatrices[lbl_803EBCC0->mTop]);
}

void fn_801D058C(float *pDst, float *pA, float *pB)
{
    fn_8024AA18(pA, pB, pDst);
}

void fn_801D05BC(float *pDst, float *pA, float *pB)
{
    float result[16];
    int i;
    int j;

    for (i = 0; i <= 3; i++) {
        for (j = 0; j < 4; j++) {
            result[j * 4 + i] = pA[j * 4 + 0] * pB[i] + pA[j * 4 + 1] * pB[4 + i] + pA[j * 4 + 2] * pB[8 + i] +
                                pA[j * 4 + 3] * pB[12 + i];
        }
    }
    fn_801D0424(pDst, result);
}

void fn_801D0664(float *pMatrix)
{
    float *pCurrent = fn_801D0444();

    fn_801D058C(pCurrent, pCurrent, pMatrix);
}

void fn_801D069C(float *pMatrix)
{
    float *pCurrent = fn_801D0444();

    fn_801D05BC(pCurrent, pCurrent, pMatrix);
}

void fn_801D06D4(float *pMatrix)
{
    fn_801D0424(lbl_803EBCC0->mpMatrices[lbl_803EBCC0->mTop], pMatrix);
}

void fn_801D070C(void)
{
}

void fn_801D0710(float *pAxis, int angle)
{
    float m[16];
    float s = fn_801CFB18(angle);
    float c = fn_801CFB94(angle);
    float x = pAxis[0];
    float y = pAxis[1];
    float z = pAxis[2];
    float t = 1.0f - c;
    float *pCurrent;

    m[3] = 0.0f;
    m[0] = t * x * x + c;
    m[4] = t * x * y + s * z;
    m[8] = t * x * z - s * y;
    m[7] = 0.0f;
    m[5] = t * y * y + c;
    m[9] = t * y * z + s * x;
    m[11] = 0.0f;
    m[1] = t * x * y - s * z;
    m[10] = t * z * z + c;
    m[2] = t * x * z + s * y;
    m[14] = 0.0f;
    m[13] = 0.0f;
    m[6] = t * y * z - s * x;
    m[12] = 0.0f;
    m[15] = 1.0f;
    pCurrent = fn_801D0444();
    fn_801D058C(m, pCurrent, m);
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

void fn_801D0860(float *pQuat)
{
    float m[16];
    float *pCurrent;

    fn_801D03D0(m);
    fn_801EB814(m, pQuat);
    pCurrent = fn_801D0444();
    fn_801D058C(m, pCurrent, m);
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

void fn_801D08FC(int angle)
{
    float *p = fn_801D0444();
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

void fn_801D09EC(int angle)
{
    float *p = fn_801D0444();
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

void fn_801D0ADC(int angle)
{
    float *p = fn_801D0444();
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

void fn_801D0BCC(int z, int y, int x)
{
    fn_801D0ADC(z);
    fn_801D09EC(y);
    fn_801D08FC(x);
}

void fn_801D0C0C(float *pMatrix, float *pX, float *pY, float *pZ)
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

void fn_801D0C58(float *pPos)
{
    float *p = fn_801D0444();
    float x = pPos[0] * p[0] + pPos[1] * p[1] + pPos[2] * p[2];
    float y = pPos[0] * p[4] + pPos[1] * p[5] + pPos[2] * p[6];
    float z = pPos[0] * p[8] + pPos[1] * p[9] + pPos[2] * p[10];

    p[3] = p[3] + x;
    p[7] = p[7] + y;
    p[11] = p[11] + z;
}

void fn_801D0CFC(float scale)
{
    float *p = fn_801D0444();

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

void fn_801D0D94(float x, float y, float z)
{
    float *p = fn_801D0444();

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

void fn_801D0E44(float scale)
{
    float *p = fn_801D0444();

    p[3] *= scale;
    p[7] *= scale;
    p[11] *= scale;
}

void fn_801D0E94(void)
{
    float *p = fn_801D0444();
    float t1 = p[1];
    float t2;
    float t6;

    p[1] = p[4];
    t2 = p[2];
    p[2] = p[8];
    t6 = p[6];
    p[6] = p[9];
    p[4] = t1;
    p[8] = t2;
    p[9] = t6;
}

void fn_801D0EE4(void)
{
    float m[16];
    float pos[3];
    float t;

    fn_801D0F80(m);
    t = m[1];
    m[1] = m[4];
    m[4] = t;
    t = m[2];
    m[2] = m[8];
    m[8] = t;
    t = m[6];
    m[6] = m[9];
    m[9] = t;
    pos[0] = -m[3];
    pos[1] = -m[7];
    pos[2] = -m[11];
    m[11] = 0.0f;
    m[3] = 0.0f;
    m[7] = 0.0f;
    fn_801D06D4(m);
    fn_801D0C58(pos);
}

void fn_801D0F80(float *pMatrix)
{
    fn_801D0424(pMatrix, fn_801D0444());
}

void fn_801D0FB8(float *pPos)
{
    float *p = fn_801D0444();

    pPos[0] = p[3];
    pPos[1] = p[7];
    pPos[2] = p[11];
}

void fn_801D0FFC(int *pAngles, float *pMatrix)
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
        inv = fn_801CFFA0(cy);
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

void fn_801D10F8(int *pAngles, float *pMatrix)
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

void fn_801D11F4(int *pAngles, unsigned int order)
{
    float *p = fn_801D0444();

    switch (order) {
    case 0:
        fn_801D0FFC(pAngles, p);
        break;
    case 1:
        break;
    case 2:
        fn_801D10F8(pAngles, p);
        break;
    }
}

void fn_801D1258(int slot, float *pMatrix)
{
    fn_801D0424(lbl_803847C0[slot], pMatrix);
}

void fn_801D1288(int slot, float *pMatrix)
{
    fn_801D0424(pMatrix, lbl_803847C0[slot]);
}

void fn_801D12BC(int slot)
{
    fn_801D06D4(lbl_803847C0[slot]);
}

void fn_801D12EC(int slot)
{
    fn_801D0F80(lbl_803847C0[slot]);
}

void fn_801D131C(int slot)
{
    fn_801D069C(lbl_803847C0[slot]);
}
