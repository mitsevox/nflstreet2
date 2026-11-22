/* Low-level angle code: Taylor coefficients for the sine approximation, 24-bit-angle
 * sine/cosine entry points, tangent and inverse trigonometry in 24-bit angles. */

#include "cmath.h"

extern float lbl_803847A0[7];
extern float lbl_803E9288[9];
extern float lbl_802F7B0C[9];

float fn_801CF944(float *pTable, float angle, float scale);

float fn_801CF98C(void)
{
    return 0.0f;
}

void fn_801CF998(void)
{
    lbl_803847A0[0] = 0.16666667f;
    lbl_803847A0[1] = 0.008333334f;
    lbl_803847A0[2] = 0.0001984127f;
    lbl_803847A0[3] = 2.7557319e-06f;
    lbl_803847A0[4] = 2.5052108e-08f;
    lbl_803847A0[5] = 1.6059044e-10f;
    lbl_803847A0[6] = 7.647164e-13f;
    lbl_803E9288[0] = powf(3.1415927f, 1.0f);
    lbl_803E9288[1] = -lbl_803847A0[0] * powf(3.1415927f, 3.0f);
    lbl_803E9288[2] = lbl_803847A0[1] * powf(3.1415927f, 5.0f);
    lbl_803E9288[3] = -lbl_803847A0[2] * powf(3.1415927f, 7.0f);
    lbl_803E9288[4] = lbl_803847A0[3] * powf(3.1415927f, 9.0f);
    lbl_803E9288[5] = -lbl_803847A0[4] * powf(3.1415927f, 11.0f);
    lbl_803E9288[6] = lbl_803847A0[5] * powf(3.1415927f, 13.0f);
    lbl_803E9288[7] = -lbl_803847A0[6] * powf(3.1415927f, 15.0f);
    lbl_803E9288[8] = 0.00390625f;
}

float fn_801CFB18(int angle)
{
    return fn_801CF944(lbl_803E9288, (angle << 8) >> 8, 1.1920929e-07f);
}

float fn_801CFB74(float x)
{
    return sinf(x);
}

float fn_801CFB94(int angle)
{
    return fn_801CF944(lbl_803E9288, ((angle + 0x400000) << 8) >> 8, 1.1920929e-07f);
}

float fn_801CFBF4(float x)
{
    return cosf(x);
}

void fn_801CFC14(int angle, float *pSin, float *pCos)
{
    *pSin = fn_801CFB18(angle);
    *pCos = fn_801CFB94(angle);
}

void fn_801CFCCC(void)
{
}

void fn_801CFCD0(int *pAngles, float *pSin, float *pCos)
{
    fn_801CFC14(pAngles[0], &pSin[0], &pCos[0]);
    fn_801CFC14(pAngles[1], &pSin[1], &pCos[1]);
    fn_801CFC14(pAngles[2], &pSin[2], &pCos[2]);
}

float fn_801CFD28(int angle)
{
    return tanf((float)angle * 3.7450703e-07f);
}

int fn_801CFD78(float x)
{
    return acosf(x) * 2670176.8f;
}

float fn_801CFDB0(float x)
{
    return acosf(x);
}

int fn_801CFDD0(float x)
{
    return asinf(x) * 2670176.8f;
}

int fn_801CFE08(float x)
{
    return atanf(x) * 2670176.8f;
}

int fn_801CFE40(float y, float x)
{
    float ax = (float)__builtin_fabs(x);
    float ay = (float)__builtin_fabs(y);
    float r = (ay - ax) / (ay + ax);
    int base = 0;
    float r2;
    float r3;
    float p;
    float sum;

    if (!(y >= 0.0f)) {
        base = 0x800000;
        if (!(x < 0.0f)) {
            base = -0x400000;
            r = -r;
        }
    } else if (!(x >= 0.0f)) {
        base = 0x400000;
        r = -r;
    }
    r2 = r * r;
    r3 = r * r2;
    p = r3 * r2;
    sum = r * lbl_802F7B0C[0] + r3 * lbl_802F7B0C[1];
    sum += p * lbl_802F7B0C[2];
    p *= r2;
    sum += p * lbl_802F7B0C[3];
    p *= r2;
    sum += p * lbl_802F7B0C[4];
    p *= r2;
    sum += p * lbl_802F7B0C[5];
    p *= r2;
    sum += p * lbl_802F7B0C[6];
    p *= r2;
    sum += p * lbl_802F7B0C[7];
    return (((int)((sum + lbl_802F7B0C[8]) * 2670176.8f) + base) << 8) >> 8;
}
