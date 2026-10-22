/* Low-level angle code: tangent, inverse trigonometry in 24-bit angles,
 * reciprocal helpers and angle interpolation. */

extern float lbl_802F7B0C[9];

void fn_801CFC14(int angle, float *pSin, float *pCos);
void fn_801CF998(void);
void fn_801F7BD4(int error);
float fn_8025FDE8(float x);
float fn_80260034(float x);
float fn_80260B1C(float x);
float fn_80260C14(float x);
float fn_8026118C(float x);

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
    return fn_8026118C((float)angle * 3.7450703e-07f);
}

int fn_801CFD78(float x)
{
    return fn_8025FDE8(x) * 2670176.8f;
}

float fn_801CFDB0(float x)
{
    return fn_8025FDE8(x);
}

int fn_801CFDD0(float x)
{
    return fn_80260034(x) * 2670176.8f;
}

int fn_801CFE08(float x)
{
    return fn_80260C14(x) * 2670176.8f;
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

void fn_801CFF34(void)
{
    fn_801CF998();
}

float fn_801CFF54(float x)
{
    float s = fn_80260B1C(x);
    float result;

    if (!(s <= 1e-07f)) {
        result = 1.0f / s;
    } else {
        result = 0.0f;
    }
    return result;
}

float fn_801CFFA0(float x)
{
    float result = 0.0f;

    if (!(x <= 1e-07f)) {
        result = 1.0f / x;
    }
    return result;
}

int fn_801CFFD0(int a, int b)
{
    int diff = (a - b) & 0xFFFFFF;
    int other = 0x1000000 - diff;

    if (other < diff) {
        diff = other;
    }
    return diff;
}

int fn_801CFFF0(int a, int b, float t)
{
    int error = 0;
    int result;
    int diff;
    int other;

    if (!(t >= 0.0f)) {
        error = 0x40003;
        result = a;
    } else if (!(t <= 1.0f)) {
        error = 0x40003;
        result = b;
    } else {
        diff = (b - a) & 0xFFFFFF;
        other = 0x1000000 - diff;
        if (other < diff) {
            t = 1.0f - t;
            result = (b + (int)((float)other * t)) & 0xFFFFFF;
        } else {
            result = (a + (int)((float)diff * t)) & 0xFFFFFF;
        }
    }
    fn_801F7BD4(error);
    return result;
}
