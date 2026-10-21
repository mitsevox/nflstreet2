/* Partial source for the engine range 0x80226F9C-0x80227F14 (neutral file name). */

extern void fn_801F7BD4(int err);
extern float fn_80260B1C(float x);
extern float fn_801CFF54(float x);
extern int fn_801CFD78(float x);
extern void fn_801CFC14(int angle, float *pFirst, float *pSecond);
extern void fn_801CFCD0(int *pAngles, float *pFirst, float *pSecond);
extern void fn_801D0F80(float m[4][4]);
extern double fabs(double x);

float fn_8022716C(float *p);
float fn_80227704(float *pA, float *pB);

static unsigned char lbl_803EBF88 = 0;

int fn_80226F9C(void)
{
    int err = 0;

    if (lbl_803EBF88 == 0) {
        lbl_803EBF88 = 1;
    } else {
        err = 0x60001;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_80226FF0(void)
{
    int err = 0;

    if (lbl_803EBF88) {
        lbl_803EBF88 = 0;
    } else {
        err = 0x60002;
    }
    fn_801F7BD4(err);
    return err;
}

int fn_80227040(float *pA, float *pB)
{
    return fn_801CFD78(fn_80227704(pA, pB) * fn_8022716C(pA) * fn_8022716C(pB));
}

float fn_802270A4(float *p)
{
    return fn_80260B1C(p[0] * p[0] + p[1] * p[1]);
}

float fn_802270D4(float *p)
{
    return fn_80260B1C(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

float fn_8022710C(float *p)
{
    return p[0] * p[0] + p[1] * p[1];
}

float fn_80227120(float *p)
{
    return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
}

float fn_8022713C(float *p)
{
    return fn_801CFF54(p[0] * p[0] + p[1] * p[1]);
}

float fn_8022716C(float *p)
{
    return fn_801CFF54(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

void fn_802271A4(float *pOut, float *p)
{
    float scale = fn_8022713C(p);

    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
}

void fn_802271F0(float *pOut, float *p)
{
    float scale = fn_8022716C(p);

    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
    pOut[2] = p[2] * scale;
}

void fn_80227248(float *pOut, float *p, float scale)
{
    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
}

void fn_80227264(float *pOut, float *p, float scale)
{
    pOut[0] = p[0] * scale;
    pOut[1] = p[1] * scale;
    pOut[2] = p[2] * scale;
}

void fn_8022728C(float *pOut, float *p, float length)
{
    fn_80227248(pOut, p, length / fn_802270A4(p));
}

void fn_802272DC(float *pOut, float *p, float length)
{
    fn_80227264(pOut, p, length / fn_802270D4(p));
}

void fn_8022732C(float *pOut, float *p, float scale)
{
    pOut[0] += p[0] * scale;
    pOut[1] += p[1] * scale;
}

void fn_80227350(float *pOut, float *p, float scale)
{
    pOut[0] += p[0] * scale;
    pOut[1] += p[1] * scale;
    pOut[2] += p[2] * scale;
}

void fn_80227384(float *pOut, float *p, int angle)
{
    float s;
    float c;

    float x;
    float y;

    fn_801CFC14(angle, &s, &c);
    x = p[0];
    y = p[1];
    pOut[0] = c * x - s * y;
    pOut[1] = c * y + s * x;
}

void fn_802273E8(float *pOut, float *p, int a, int b, int c)
{
    float first[3];
    float second[3];
    int angles[3];
    float x0;
    float y0;
    float x1;
    float z1;

    angles[0] = a;
    angles[1] = b;
    angles[2] = c;
    fn_801CFCD0(angles, first, second);
    x0 = second[2] * p[0] - first[2] * p[1];
    y0 = first[2] * p[0] + second[2] * p[1];
    x1 = second[1] * x0 + first[1] * p[2];
    z1 = second[1] * p[2] - first[1] * x0;
    pOut[0] = x1;
    pOut[1] = second[0] * y0 - first[0] * z1;
    pOut[2] = first[0] * y0 + second[0] * z1;
}

void fn_80227490(float *pOut, float *p, int a, int b, int c)
{
    float first[3];
    float second[3];
    int angles[3];
    float y0;
    float z0;
    float x1;
    float z1;

    angles[0] = c;
    angles[1] = b;
    angles[2] = a;
    fn_801CFCD0(angles, first, second);
    y0 = second[0] * p[1] - first[0] * p[2];
    z0 = first[0] * p[1] + second[0] * p[2];
    x1 = second[1] * p[0] + first[1] * z0;
    z1 = second[1] * z0 - first[1] * p[0];
    pOut[0] = second[2] * x1 - first[2] * y0;
    pOut[1] = first[2] * x1 + second[2] * y0;
    pOut[2] = z1;
}

void fn_80227538(float *pOut, int angle, float length)
{
    float first;
    float second;

    fn_801CFC14(angle, &first, &second);
    pOut[0] = second * length;
    pOut[1] = first * length;
}

int fn_80227594(float *pA, float *pB, float eps)
{
    float dx = fabs(pA[0] - pB[0]);
    float dy = fabs(pA[1] - pB[1]);

    return dx < eps && dy < eps;
}

int fn_802275D8(float *pA, float *pB, float eps)
{
    float dx = fabs(pA[0] - pB[0]);
    float dy = fabs(pA[1] - pB[1]);
    float dz = fabs(pA[2] - pB[2]);

    return dx < eps && dy < eps && dz < eps;
}

void fn_80227638(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] + pB[0];
    pOut[1] = pA[1] + pB[1];
}

void fn_8022765C(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] + pB[0];
    pOut[1] = pA[1] + pB[1];
    pOut[2] = pA[2] + pB[2];
}

void fn_80227690(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] - pB[0];
    pOut[1] = pA[1] - pB[1];
}

void fn_802276B4(float *pOut, float *pA, float *pB)
{
    pOut[0] = pA[0] - pB[0];
    pOut[1] = pA[1] - pB[1];
    pOut[2] = pA[2] - pB[2];
}

float fn_802276E8(float *pA, float *pB)
{
    return pA[0] * pB[0] + pA[1] * pB[1];
}

float fn_80227704(float *pA, float *pB)
{
    return pA[0] * pB[0] + pA[1] * pB[1] + pA[2] * pB[2];
}

void fn_802277DC(float *pOut, float *pA, float *pB)
{
    float x = pA[1] * pB[2] - pA[2] * pB[1];
    float y = pA[2] * pB[0] - pA[0] * pB[2];
    float z = pA[0] * pB[1] - pA[1] * pB[0];

    pOut[0] = x;
    pOut[1] = y;
    pOut[2] = z;
}

float fn_8022781C(float *pA, float *pB)
{
    float d[2];

    fn_80227690(d, pA, pB);
    return fn_802270A4(d);
}

float fn_8022785C(float *pA, float *pB)
{
    float d[3];

    fn_802276B4(d, pA, pB);
    return fn_802270D4(d);
}

float fn_80227890(float *pA, float *pB)
{
    float d[2];

    fn_80227690(d, pA, pB);
    return fn_8022710C(d);
}

float fn_802278D0(float *pA, float *pB)
{
    float d[3];

    fn_802276B4(d, pA, pB);
    return fn_80227120(d);
}

void fn_80227904(float *pOut, float *pA, float *pB, float t)
{
    float x = pB[0];
    float y = pB[1];

    pOut[0] = (pA[0] - x) * t + x;
    pOut[1] = (pA[1] - y) * t + y;
}

void fn_80227930(float *pOut, float *pA, float *pB, float t)
{
    float x = pB[0];
    float y = pB[1];
    float z = pB[2];

    pOut[0] = (pA[0] - x) * t + x;
    pOut[1] = (pA[1] - y) * t + y;
    pOut[2] = (pA[2] - z) * t + z;
}

void fn_80227C2C(float *pOut, float *p)
{
    float m[4][4];
    float x;
    float y;
    float z;

    fn_801D0F80(m);
    x = p[0];
    y = p[1];
    z = p[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z;
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z;
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z;
}

void fn_80227CC0(float *pOut, float *p)
{
    float m[4][4];
    float x;
    float y;
    float z;

    fn_801D0F80(m);
    x = p[0];
    y = p[1];
    z = p[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
}

void fn_80227E40(float *pOut, float *p)
{
    float m[4][4];
    float x;
    float y;
    float z;
    float w;

    fn_801D0F80(m);
    x = p[0];
    y = p[1];
    z = p[2];
    w = p[3];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3] * w;
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3] * w;
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3] * w;
    pOut[3] = m[3][0] * x + m[3][1] * y + m[3][2] * z + m[3][3] * w;
}
