/* Comparison fragment of src/engine/cu_8021A438.c: fn_80220D3C and its literal pool. */
#include "engine/cu_8021A438.h"

extern Color_80223C4C *lbl_803EBF50;
extern Int32 lbl_803ED00C;
extern Color_80223C4C lbl_8039F878[];

void fn_80220CFC(Int32 a);

void fn_80220D3C(void)
{
    lbl_803ED00C = 0;
    lbl_8039F878[0].unk_00[0] = 1.0f;
    lbl_8039F878[0].unk_00[1] = 1.0f;
    lbl_8039F878[0].unk_00[2] = 1.0f;
    lbl_8039F878[0].unk_00[3] = 1.0f;
    lbl_8039F878[0].unk_00[4] = 0.0f;
    lbl_8039F878[0].unk_00[5] = 0.0f;
    lbl_8039F878[0].unk_00[6] = 0.0f;
    lbl_8039F878[0].unk_00[7] = 0.0f;
    lbl_803EBF50 = lbl_8039F878;
    fn_80220CFC(0);
}


static inline unsigned char fn_80220DA4_ToByte(Float32 v)
{
    Float32 f;

    if (!(v < 0.0f)) {
        f = v;
        if (!(f <= 255.0f)) {
            f = 255.0f;
        }
        return (int)f;
    }
    return 0;
}


void fn_80220DA4(Float32 *pMul, Float32 *pScale)
{
    Color_80223C4C *pCur;
    Color_80223C4C *pNext;

    pCur = &lbl_8039F878[lbl_803ED00C];
    pNext = pCur + 1;
    pNext->unk_00[0] = pCur->unk_00[0] * pMul[0];
    pNext->unk_00[1] = pCur->unk_00[1] * pMul[1];
    pNext->unk_00[2] = pCur->unk_00[2] * pMul[2];
    pNext->unk_00[3] = pCur->unk_00[3] * pMul[3];
    pNext->unk_00[4] = pCur->unk_00[4] * pScale[0];
    pNext->unk_00[5] = pCur->unk_00[5] * pScale[1];
    pNext->unk_00[6] = pCur->unk_00[6] * pScale[2];
    pNext->unk_00[7] = pCur->unk_00[7] * pScale[3];
    if (!(pNext->unk_00[3] < 1.0f)) {
        pNext->unk_00[3] = 1.0f;
    }
    if (!(pNext->unk_00[3] > 0.0f)) {
        pNext->unk_00[3] = 0.0f;
    }
    pNext->unk_20.r = fn_80220DA4_ToByte(pNext->unk_00[0] * 255.0f);
    pNext->unk_20.g = fn_80220DA4_ToByte(pNext->unk_00[1] * 255.0f);
    pNext->unk_20.b = fn_80220DA4_ToByte(pNext->unk_00[2] * 255.0f);
    pNext->unk_20.a = fn_80220DA4_ToByte(pNext->unk_00[3] * 255.0f);
    pNext->unk_24.r = fn_80220DA4_ToByte(pNext->unk_00[4] * 255.0f);
    pNext->unk_24.g = fn_80220DA4_ToByte(pNext->unk_00[5] * 255.0f);
    pNext->unk_24.b = fn_80220DA4_ToByte(pNext->unk_00[6] * 255.0f);
    pNext->unk_24.a = fn_80220DA4_ToByte(pNext->unk_00[7] * 255.0f);
    lbl_803ED00C++;
    lbl_803EBF50++;
    fn_80220CFC(0);
}

