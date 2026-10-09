#include <dolphin/os.h>
#include <dolphin/dvd.h>
#include <dolphin/vi.h>
#include <dolphin/__vm.h>
#include <math.h>

/* Defined with C++ linkage in src/game/MainLoop.cpp. */
void fn_80026AF8(void);

extern "C" {

void fn_801CE1F0(int value);
void fn_802451F8(int value);

void fn_80088F2C(void)
{
    asm volatile("li 3,4\n\toris 3,3,4\n\tmtspr 914,3\n\t"
                 "li 3,5\n\toris 3,3,5\n\tmtspr 915,3\n\t"
                 "li 3,6\n\toris 3,3,6\n\tmtspr 916,3\n\t"
                 "li 3,7\n\toris 3,3,7\n\tmtspr 917,3\n\t"
                 "li 3,7\n\toris 3,3,3847\n\tmtspr 918,3\n\t"
                 "li 3,7\n\toris 3,3,7\n\tmtspr 919,3"
                 : : : "r3");
}

void fn_80088F78(void)
{
    OSInit();
    fn_80088F2C();
    DVDInit();
    VIInit();
    VMInit(0x41000, 0xAFC000, 0x104000);
    fn_802451F8(0);
}

}

int main(void)
{
    fn_80088F78();
    fn_801CE1F0(0);
    fn_80026AF8();
    return 0;
}

#if defined(DECOMP_COMPARE)
/* Draft. Clamps a parameter s on pA0-pA1 and t on pB0-pB1 to 0..1 (s from
   the two-segment solve, then t from s, then s again from t), stores the
   midpoint of the two points to pOut and returns their squared distance.
   Control flow and stack layout match; register allocation and scheduling
   of the opening products do not. */
extern "C" float fn_80088FFC(float *pA0, float *pA1, float *pB0, float *pB1, float *pOut)
{
    float r[3];
    float d2[3];
    float d1[3];
    float p[3];
    float q[3];
    float a, b, c, e, f, denom, s, t;

    d1[0] = pA1[0] - pA0[0];
    d1[1] = pA1[1] - pA0[1];
    d1[2] = pA1[2] - pA0[2];
    d2[0] = pB1[0] - pB0[0];
    d2[1] = pB1[1] - pB0[1];
    d2[2] = pB1[2] - pB0[2];
    r[0] = pA0[0] - pB0[0];
    r[1] = pA0[1] - pB0[1];
    r[2] = pA0[2] - pB0[2];
    a = d1[0] * d1[0] + d1[1] * d1[1] + d1[2] * d1[2];
    e = d2[0] * d2[0] + d2[1] * d2[1] + d2[2] * d2[2];
    b = d2[0] * d1[0] + d2[1] * d1[1] + d2[2] * d1[2];
    c = r[0] * d1[0] + r[1] * d1[1] + r[2] * d1[2];
    f = r[0] * d2[0] + r[1] * d2[1] + r[2] * d2[2];
    denom = a * e - b * b;
    if (fabsf(denom) < 1e-07f) {
        s = 0.0f;
    } else {
        s = (f * b - c * e) / denom;
    }
    s = s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s);
    p[0] = pA0[0] + s * d1[0];
    p[1] = pA0[1] + s * d1[1];
    p[2] = pA0[2] + s * d1[2];
    if (e > 1e-07f) {
        t = ((p[0] - pB0[0]) * d2[0] + (p[1] - pB0[1]) * d2[1] + (p[2] - pB0[2]) * d2[2]) / e;
        t = t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
    } else {
        t = 0.0f;
    }
    q[0] = pB0[0] + t * d2[0];
    q[1] = pB0[1] + t * d2[1];
    q[2] = pB0[2] + t * d2[2];
    if (a > 1e-07f) {
        s = ((q[0] - pA0[0]) * d1[0] + (q[1] - pA0[1]) * d1[1] + (q[2] - pA0[2]) * d1[2]) / a;
        s = s < 0.0f ? 0.0f : (s > 1.0f ? 1.0f : s);
    } else {
        s = 0.0f;
    }
    p[0] = pA0[0] + s * d1[0];
    p[1] = pA0[1] + s * d1[1];
    p[2] = pA0[2] + s * d1[2];
    pOut[0] = (p[0] + q[0]) * 0.5f;
    pOut[1] = (p[1] + q[1]) * 0.5f;
    pOut[2] = (p[2] + q[2]) * 0.5f;
    return (p[0] - q[0]) * (p[0] - q[0]) + (p[1] - q[1]) * (p[1] - q[1]) + (p[2] - q[2]) * (p[2] - q[2]);
}
#endif
