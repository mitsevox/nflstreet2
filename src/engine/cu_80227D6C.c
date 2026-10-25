/* Comparison fragment of src/engine/cu_80226F9C.c: fn_80227D6C and its literal pool. */

extern void fn_801D0F80(float m[4][4]);

void fn_80227D6C(float *pOut, float *pV)
{
    float m[4][4];
    float x;
    float y;
    float z;

    fn_801D0F80(m);
    x = pV[0];
    y = pV[1];
    z = pV[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    pOut[3] = m[3][0] * x + m[3][1] * y + m[3][2] * z + 1.0f;
}
