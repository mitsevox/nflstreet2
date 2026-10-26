/* Comparison fragment of src/engine/cu_80226F9C.c: fn_80227B04 and its literal pool. */

float fn_80227B04(float *pA, float *pB, float *pP)
{
    float aPoint[3];
    float ex;
    float ey;
    float ez;
    float t;
    float dx;
    float dy;
    float dz;

    if (pA[0] == pB[0] && pA[1] == pB[1] && pA[2] == pB[2]) {
        aPoint[0] = pA[0];
        aPoint[1] = pA[1];
        aPoint[2] = pA[2];
    } else {
        ex = pA[0] - pB[0];
        ey = pA[1] - pB[1];
        ez = pA[2] - pB[2];
        t = ((pA[0] - pP[0]) * ex + (pA[1] - pP[1]) * ey + (pA[2] - pP[2]) * ez) / (ex * ex + ey * ey + ez * ez);
        if (t > 1.0f) {
            t = 1.0f;
        }
        if (t < 0.0f) {
            t = 0.0f;
        }
        aPoint[0] = pA[0] + t * (pB[0] - pA[0]);
        aPoint[1] = pA[1] + t * (pB[1] - pA[1]);
        aPoint[2] = pA[2] + t * (pB[2] - pA[2]);
    }
    dx = aPoint[0] - pP[0];
    dy = aPoint[1] - pP[1];
    dz = aPoint[2] - pP[2];
    return dx * dx + dy * dy + dz * dz;
}
