/* Comparison fragment of src/engine/cu_80226F9C.c: fn_80227970 and its literal pool. */


void fn_80227970(float *pA, float *pB, float *pP, float *pOut, float *pDistSq, float *pT)
{
    float dx;
    float dy;
    float dz;
    float ex;
    float ey;
    float ez;

    if (pA[0] == pB[0] && pA[1] == pB[1] && pA[2] == pB[2]) {
        *pT = 0.0f;
        pOut[0] = pA[0];
        pOut[1] = pA[1];
        pOut[2] = pA[2];
    } else {
        ex = pA[0] - pB[0];
        ey = pA[1] - pB[1];
        ez = pA[2] - pB[2];
        *pT = ((pA[0] - pP[0]) * ex + (pA[1] - pP[1]) * ey + (pA[2] - pP[2]) * ez) / (ex * ex + ey * ey + ez * ez);
        if (*pT < 0.0f) {
            *pT = 0.0f;
            pOut[0] = pA[0];
            pOut[1] = pA[1];
            pOut[2] = pA[2];
        } else if (*pT > 1.0f) {
            *pT = 1.0f;
            pOut[0] = pB[0];
            pOut[1] = pB[1];
            pOut[2] = pB[2];
        } else {
            pOut[0] = pA[0] + *pT * (pB[0] - pA[0]);
            pOut[1] = pA[1] + *pT * (pB[1] - pA[1]);
            pOut[2] = pA[2] + *pT * (pB[2] - pA[2]);
        }
    }
    dx = pOut[0] - pP[0];
    dy = pOut[1] - pP[1];
    dz = pOut[2] - pP[2];
    *pDistSq = dx * dx + dy * dy + dz * dz;
}
