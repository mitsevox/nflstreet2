/* Comparison fragment of src/engine/llvector.c: Vec3Mat44Mul and its literal pool. */

extern void MatStore(float m[4][4]);

void Vec3Mat44Mul(float *pOut, float *pV)
{
    float m[4][4];
    float x;
    float y;
    float z;

    MatStore(m);
    x = pV[0];
    y = pV[1];
    z = pV[2];
    pOut[0] = m[0][0] * x + m[0][1] * y + m[0][2] * z + m[0][3];
    pOut[1] = m[1][0] * x + m[1][1] * y + m[1][2] * z + m[1][3];
    pOut[2] = m[2][0] * x + m[2][1] * y + m[2][2] * z + m[2][3];
    pOut[3] = m[3][0] * x + m[3][1] * y + m[3][2] * z + 1.0f;
}
