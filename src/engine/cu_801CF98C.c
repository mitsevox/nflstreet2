/* Low-level angle code: Taylor coefficients for the sine approximation and
 * 24-bit-angle sine/cosine entry points. */

extern float lbl_803847A0[7];
extern float lbl_803E9288[9];

float fn_801CF944(float *pTable, float angle, float scale);
float fn_80260428(float x, float y);
float fn_802610B0(float x);
float fn_80260EE8(float x);

float fn_801CFB18(int angle);
float fn_801CFB94(int angle);

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
    lbl_803E9288[0] = fn_80260428(3.1415927f, 1.0f);
    lbl_803E9288[1] = -lbl_803847A0[0] * fn_80260428(3.1415927f, 3.0f);
    lbl_803E9288[2] = lbl_803847A0[1] * fn_80260428(3.1415927f, 5.0f);
    lbl_803E9288[3] = -lbl_803847A0[2] * fn_80260428(3.1415927f, 7.0f);
    lbl_803E9288[4] = lbl_803847A0[3] * fn_80260428(3.1415927f, 9.0f);
    lbl_803E9288[5] = -lbl_803847A0[4] * fn_80260428(3.1415927f, 11.0f);
    lbl_803E9288[6] = lbl_803847A0[5] * fn_80260428(3.1415927f, 13.0f);
    lbl_803E9288[7] = -lbl_803847A0[6] * fn_80260428(3.1415927f, 15.0f);
    lbl_803E9288[8] = 0.00390625f;
}

float fn_801CFB18(int angle)
{
    return fn_801CF944(lbl_803E9288, (angle << 8) >> 8, 1.1920929e-07f);
}

float fn_801CFB74(float x)
{
    return fn_802610B0(x);
}

float fn_801CFB94(int angle)
{
    return fn_801CF944(lbl_803E9288, ((angle + 0x400000) << 8) >> 8, 1.1920929e-07f);
}

float fn_801CFBF4(float x)
{
    return fn_80260EE8(x);
}

void fn_801CFC14(int angle, float *pSin, float *pCos)
{
    *pSin = fn_801CFB18(angle);
    *pCos = fn_801CFB94(angle);
}
