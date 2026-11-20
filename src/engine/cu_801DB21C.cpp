#include "engine/maddec.h"

extern "C" {
void fn_801DB21C(int *pIn, int *pOut);
void fn_801DB490(int *pIn, int *pOut);
}

extern int idctinput[64];
extern int lbl_8039AC10[64];

#define IDCT_MUL(a, c) ((int)(((long long)(a) * (c) + 0x8000) >> 16))

void fn_801DB21C(int *pIn, int *pOut)
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
        pOut[56] = a0 - b0;
        pOut[8] = a1 + b1;
        pOut[48] = a1 - b1;
        pOut[16] = a2 + b2;
        pOut[40] = a2 - b2;
        pOut[24] = a3 + b3;
        pOut[32] = a3 - b3;
    }
}

void fn_801DB490(int *pIn, int *pOut)
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

void fn_801DB670(int *pOut, int stride)
{
    fn_801DB21C(&idctinput[0], &lbl_8039AC10[0]);
    fn_801DB21C(&idctinput[8], &lbl_8039AC10[1]);
    fn_801DB21C(&idctinput[16], &lbl_8039AC10[2]);
    fn_801DB21C(&idctinput[24], &lbl_8039AC10[3]);
    fn_801DB21C(&idctinput[32], &lbl_8039AC10[4]);
    fn_801DB21C(&idctinput[40], &lbl_8039AC10[5]);
    fn_801DB21C(&idctinput[48], &lbl_8039AC10[6]);
    fn_801DB21C(&idctinput[56], &lbl_8039AC10[7]);
    fn_801DB490(&lbl_8039AC10[0], pOut);
    fn_801DB490(&lbl_8039AC10[8], pOut + stride);
    fn_801DB490(&lbl_8039AC10[16], pOut + stride * 2);
    fn_801DB490(&lbl_8039AC10[24], pOut + stride * 3);
    fn_801DB490(&lbl_8039AC10[32], pOut + stride * 4);
    fn_801DB490(&lbl_8039AC10[40], pOut + stride * 5);
    fn_801DB490(&lbl_8039AC10[48], pOut + stride * 6);
    fn_801DB490(&lbl_8039AC10[56], pOut + stride * 7);
}
