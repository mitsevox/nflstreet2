/* Low-level angle math for the whole game: sine and cosine of 24-bit angles (a full turn is
 * 0x1000000) from a Taylor polynomial evaluated on the Gekko's paired-single unit, their float
 * wrappers, tangent, and the inverse functions that turn a cosine, sine, tangent or a y/x pair back
 * into a 24-bit angle. The polynomial tables are filled once at start-up. */

#include "cmath.h"

static float _Math_TaylorConst[8];
float _Math_Taylor[9];
float _Math_ArcTanTable[9] = {
    0.99999934f, -0.33329856f, 0.19946536f, -0.13908534f,
    0.09642004f, -0.055909887f, 0.02186123f, -0.004054058f,
    0.7853982f,
};

static float _MathSin(float *pTable, float angle, float scale)
{
    asm volatile(
        "    fmuls    2,1,2\n"
        "    psq_l    3,0(3),0,0\n"
        "    psq_l    4,8(3),0,0\n"
        "    fmuls    7,2,2\n"
        "    psq_l    5,16(3),0,0\n"
        "    psq_l    6,24(3),0,0\n"
        "    fmuls    9,2,7\n"
        "    fmuls    7,7,7\n"
        "    ps_merge01 8,2,9\n"
        "    ps_mul   10,8,7\n"
        "    ps_mul   1,3,8\n"
        "    ps_mul   11,10,7\n"
        "    ps_madd  1,4,10,1\n"
        "    ps_mul   12,11,7\n"
        "    ps_madd  1,5,11,1\n"
        "    ps_madd  1,6,12,1\n"
        "    ps_sum0  1,1,1,1\n"
        "    blr\n");
    return 0.0f;
}

void MathLLAngleInit(void)
{
    _Math_TaylorConst[0] = 0.16666667f;
    _Math_TaylorConst[1] = 0.008333334f;
    _Math_TaylorConst[2] = 0.0001984127f;
    _Math_TaylorConst[3] = 2.7557319e-06f;
    _Math_TaylorConst[4] = 2.5052108e-08f;
    _Math_TaylorConst[5] = 1.6059044e-10f;
    _Math_TaylorConst[6] = 7.647164e-13f;
    _Math_Taylor[0] = powf(3.1415927f, 1.0f);
    _Math_Taylor[1] = -_Math_TaylorConst[0] * powf(3.1415927f, 3.0f);
    _Math_Taylor[2] = _Math_TaylorConst[1] * powf(3.1415927f, 5.0f);
    _Math_Taylor[3] = -_Math_TaylorConst[2] * powf(3.1415927f, 7.0f);
    _Math_Taylor[4] = _Math_TaylorConst[3] * powf(3.1415927f, 9.0f);
    _Math_Taylor[5] = -_Math_TaylorConst[4] * powf(3.1415927f, 11.0f);
    _Math_Taylor[6] = _Math_TaylorConst[5] * powf(3.1415927f, 13.0f);
    _Math_Taylor[7] = -_Math_TaylorConst[6] * powf(3.1415927f, 15.0f);
    _Math_Taylor[8] = 0.00390625f;
}

float MathSin(int angle)
{
    return _MathSin(_Math_Taylor, (angle << 8) >> 8, 1.1920929e-07f);
}

float MathSinf(float x)
{
    return sinf(x);
}

float MathCos(int angle)
{
    return _MathSin(_Math_Taylor, ((angle + 0x400000) << 8) >> 8, 1.1920929e-07f);
}

float MathCosf(float x)
{
    return cosf(x);
}

void MathSinCos(int angle, float *pSin, float *pCos)
{
    *pSin = MathSin(angle);
    *pCos = MathCos(angle);
}

void _MathSinCos16(int angle, float *pTable, float *pSin, float *pCos)
{
    asm volatile(
        "    stwu     1,-16(1)\n"
        "    addi     7,3,16384\n"
        "    sth      3,0(1)\n"
        "    sth      7,2(1)\n"
        "    psq_l    1,0(1),0,6\n"
        "    ps_mul   5,1,1\n"
        "    psq_l    2,0(4),0,0\n"
        "    psq_l    3,8(4),0,0\n"
        "    ps_mul   6,1,5\n"
        "    ps_mul   5,5,5\n"
        "    ps_merge00 7,1,6\n"
        "    ps_merge11 11,1,6\n"
        "    psq_l    4,16(4),0,0\n"
        "    ps_muls0 8,7,5\n"
        "    ps_muls1 12,11,5\n"
        "    ps_mul   1,2,7\n"
        "    ps_mul   0,2,11\n"
        "    ps_muls0 9,8,5\n"
        "    ps_muls1 13,12,5\n"
        "    ps_madd  1,3,8,1\n"
        "    ps_madd  0,3,12,0\n"
        "    ps_madd  1,4,9,1\n"
        "    ps_madd  0,4,13,0\n"
        "    ps_sum0  1,1,1,1\n"
        "    ps_sum0  0,0,0,0\n"
        "    addi     1,1,16\n"
        "    stfs     1,0(5)\n"
        "    stfs     0,0(6)\n"
        "    blr\n");
}

void MathSinCosVec4(int *pAngles, float *pSin, float *pCos)
{
    MathSinCos(pAngles[0], &pSin[0], &pCos[0]);
    MathSinCos(pAngles[1], &pSin[1], &pCos[1]);
    MathSinCos(pAngles[2], &pSin[2], &pCos[2]);
}

float MathTan(int angle)
{
    return tanf((float)angle * 3.7450703e-07f);
}

int MathArcCos(float x)
{
    return acosf(x) * 2670176.8f;
}

float MathArcCosf(float x)
{
    return acosf(x);
}

int MathArcSin(float x)
{
    return asinf(x) * 2670176.8f;
}

int MathArcTan(float x)
{
    return atanf(x) * 2670176.8f;
}

int MathArcTan2(float y, float x)
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
    sum = r * _Math_ArcTanTable[0] + r3 * _Math_ArcTanTable[1];
    sum += p * _Math_ArcTanTable[2];
    p *= r2;
    sum += p * _Math_ArcTanTable[3];
    p *= r2;
    sum += p * _Math_ArcTanTable[4];
    p *= r2;
    sum += p * _Math_ArcTanTable[5];
    p *= r2;
    sum += p * _Math_ArcTanTable[6];
    p *= r2;
    sum += p * _Math_ArcTanTable[7];
    return (((int)((sum + _Math_ArcTanTable[8]) * 2670176.8f) + base) << 8) >> 8;
}
