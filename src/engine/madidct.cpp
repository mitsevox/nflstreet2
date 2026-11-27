/* MAD video decoder inverse DCT: turns one 8x8 block of decoded picture coefficients back
   into pixel values, a column pass then a row pass in 16.16 fixed point. */

#include "engine/maddec.h"

extern "C" {
void IdctColumn(int *pIn, int *pOut);
void IdctRow(int *pIn, int *pOut);
}

extern int idctinput[64];
static int work[64];

#define IDCT_MUL(a, c) ((int)(((long long)(a) * (c) + 0x8000) >> 16))

void IdctColumn(int *pIn, int *pOut)
{
    int x1 = pIn[1];
    int x2 = pIn[2];
    int x3 = pIn[3];
    int x4 = pIn[4];
    int x5 = pIn[5];
    int x6 = pIn[6];
    int x7 = pIn[7];

    if ((x1 | x2 | x3 | x4 | x5 | x6 | x7) == 0) {
        pOut[0] = pIn[0];
        pOut[8] = pIn[0];
        pOut[16] = pIn[0];
        pOut[24] = pIn[0];
        pOut[32] = pIn[0];
        pOut[40] = pIn[0];
        pOut[48] = pIn[0];
        pOut[56] = pIn[0];
    } else {
        int d17 = x1 - x7;
        int d53 = x5 - x3;
        int s17 = x1 + x7;
        int s53 = x5 + x3;
        int m26 = IDCT_MUL(x2 - x6, 46341);
        int mz = IDCT_MUL(d53 + d17, 25080);
        int m17 = IDCT_MUL(d17, 85627);
        int ms = IDCT_MUL(s17 - s53, 46341);
        int m53 = IDCT_MUL(d53, 35468);
        int e2 = x2 + x6 + m26;
        int e0 = pIn[0] + x4;
        int e1 = pIn[0] - x4;
        int a0 = e0 + e2;
        int a3 = e0 - e2;
        int a1 = e1 + m26;
        int a2 = e1 - m26;
        int s = s53 + s17;
        int t = m17 - mz;
        int u = m53 + mz;
        int b0 = s + t;
        int b1 = t + ms;
        int b2 = ms + u;
        int b3 = u;

        pOut[0] = a0 + b0;
        pOut[8] = a1 + b1;
        pOut[16] = a2 + b2;
        pOut[24] = a3 + b3;
        pOut[32] = a3 - b3;
        pOut[40] = a2 - b2;
        pOut[48] = a1 - b1;
        pOut[56] = a0 - b0;
    }
}

void IdctRow(int *pIn, int *pOut)
{
    int d17 = pIn[1] - pIn[7];
    int d53 = pIn[5] - pIn[3];
    int s17 = pIn[1] + pIn[7];
    int s53 = pIn[5] + pIn[3];
    int m26 = IDCT_MUL(pIn[2] - pIn[6], 46341);
    int mz = IDCT_MUL(d53 + d17, 25080);
    int m17 = IDCT_MUL(d17, 85627);
    int ms = IDCT_MUL(s17 - s53, 46341);
    int m53 = IDCT_MUL(d53, 35468);
    int e2 = pIn[2] + pIn[6] + m26;
    int e0 = pIn[0] + pIn[4];
    int e1 = pIn[0] - pIn[4];
    int a0 = e0 + e2;
    int a3 = e0 - e2;
    int a1 = e1 + m26;
    int a2 = e1 - m26;
    int s = s53 + s17;
    int t = m17 - mz;
    int u = m53 + mz;
    int b0 = s + t;
    int b1 = t + ms;
    int b2 = ms + u;
    int b3 = u;

    pOut[0] = a0 + b0;
    pOut[7] = a0 - b0;
    pOut[1] = a1 + b1;
    pOut[6] = a1 - b1;
    pOut[2] = a2 + b2;
    pOut[5] = a2 - b2;
    pOut[3] = a3 + b3;
    pOut[4] = a3 - b3;
}

void idctcompute(int *pOut, int stride)
{
    IdctColumn(&idctinput[0], &work[0]);
    IdctColumn(&idctinput[8], &work[1]);
    IdctColumn(&idctinput[16], &work[2]);
    IdctColumn(&idctinput[24], &work[3]);
    IdctColumn(&idctinput[32], &work[4]);
    IdctColumn(&idctinput[40], &work[5]);
    IdctColumn(&idctinput[48], &work[6]);
    IdctColumn(&idctinput[56], &work[7]);
    IdctRow(&work[0], pOut);
    IdctRow(&work[8], pOut + stride);
    IdctRow(&work[16], pOut + stride * 2);
    IdctRow(&work[24], pOut + stride * 3);
    IdctRow(&work[32], pOut + stride * 4);
    IdctRow(&work[40], pOut + stride * 5);
    IdctRow(&work[48], pOut + stride * 6);
    IdctRow(&work[56], pOut + stride * 7);
}
