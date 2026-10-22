#include "engine/cu_801DA52C.h"

extern "C" {
void fn_801DB21C(int *pIn, int *pOut);
void fn_801DB490(int *pIn, int *pOut);
}

extern int lbl_8039AB10[64];
extern int lbl_8039AC10[64];

void fn_801DB670(int *pOut, int stride)
{
    fn_801DB21C(&lbl_8039AB10[0], &lbl_8039AC10[0]);
    fn_801DB21C(&lbl_8039AB10[8], &lbl_8039AC10[1]);
    fn_801DB21C(&lbl_8039AB10[16], &lbl_8039AC10[2]);
    fn_801DB21C(&lbl_8039AB10[24], &lbl_8039AC10[3]);
    fn_801DB21C(&lbl_8039AB10[32], &lbl_8039AC10[4]);
    fn_801DB21C(&lbl_8039AB10[40], &lbl_8039AC10[5]);
    fn_801DB21C(&lbl_8039AB10[48], &lbl_8039AC10[6]);
    fn_801DB21C(&lbl_8039AB10[56], &lbl_8039AC10[7]);
    fn_801DB490(&lbl_8039AC10[0], pOut);
    fn_801DB490(&lbl_8039AC10[8], pOut + stride);
    fn_801DB490(&lbl_8039AC10[16], pOut + stride * 2);
    fn_801DB490(&lbl_8039AC10[24], pOut + stride * 3);
    fn_801DB490(&lbl_8039AC10[32], pOut + stride * 4);
    fn_801DB490(&lbl_8039AC10[40], pOut + stride * 5);
    fn_801DB490(&lbl_8039AC10[48], pOut + stride * 6);
    fn_801DB490(&lbl_8039AC10[56], pOut + stride * 7);
}
