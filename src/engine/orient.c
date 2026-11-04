/* Orientation helpers: 24-bit angle triples, shortest-path angle interpolation. */

static int fn_801CF7CC(int a, int b, float t)
{
    long long r = ((long long)(a - b) * (int)(t * 16777216.0f)) >> 24;

    r += b;
    return r;
}

void fn_801CF810(int *pDst, int *pA, int *pB, float t)
{
    unsigned int i;
    int a;
    int b;
    int diff;

    for (i = 0; i <= 2; i++) {
        b = pB[i] & 0xFFFFFF;
        a = pA[i] & 0xFFFFFF;
        diff = a - b;
        if (diff > 0x800000) {
            b += 0x1000000;
        } else if (diff < -0x800000) {
            a += 0x1000000;
        }
        pDst[i] = fn_801CF7CC(a, b, t);
    }
}

void fn_801CF8A8(int *pDst, int a, int b, float t)
{
    int diff;

    b &= 0xFFFFFF;
    a &= 0xFFFFFF;
    diff = a - b;
    if (diff > 0x800000) {
        b += 0x1000000;
    } else if (diff < -0x800000) {
        a += 0x1000000;
    }
    *pDst = fn_801CF7CC(a, b, t);
}

void fn_801CF910(int *pDst, int *pA, int *pB)
{
    pDst[0] = pA[0] + pB[0];
    pDst[1] = pA[1] + pB[1];
    pDst[2] = pA[2] + pB[2];
}
