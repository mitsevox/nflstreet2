#include "engine/tmlib.h"

extern void fn_801D0424(void *pDst, void *pSrc);
extern void fn_801D04C4(void);
extern void fn_801D0544(void);
extern void fn_801D0664(void *pMtx);
extern void fn_801D06D4(void *pMtx);
extern void fn_801D1288(int mode, void *pMtx);
extern unsigned int fn_80213F18(void *pPoints, int numPoints, f32 (*pMtx)[4], Extent_802144AC *pExtent, void *pArg);
extern unsigned int fn_80213DB0(void *pPoints, int numPoints, f32 (*pMtx)[4], void *pArg);

extern f32 lbl_8039B580[4][4];
extern f32 lbl_8039B5C0[3][4];
extern f32 lbl_802F9D8C[3];

static inline void fn_80213BCC_Row(Extent_802144AC *pBox, f32 (*pMtx)[4], f32 (*pOut)[3], int r)
{
    f32 y0 = pMtx[r][1] * pBox->mMin[1];
    f32 z0 = pMtx[r][2] * pBox->mMin[2];
    f32 x0 = pMtx[r][0] * pBox->mMin[0];
    f32 w = pMtx[r][3];
    f32 x1 = pMtx[r][0] * pBox->mMax[0];
    f32 y1 = pMtx[r][1] * pBox->mMax[1];
    f32 z1 = pMtx[r][2] * pBox->mMax[2];
    f32 t;

    t = y0 + z0 + w;
    pOut[0][r] = x0 + t;
    pOut[1][r] = x1 + t;
    t = y1 + z0 + w;
    pOut[2][r] = x0 + t;
    pOut[3][r] = x1 + t;
    t = y0 + z1 + w;
    pOut[4][r] = x0 + t;
    pOut[5][r] = x1 + t;
    t = y1 + z1 + w;
    pOut[6][r] = x0 + t;
    pOut[7][r] = x1 + t;
}

static void fn_80213BCC(Extent_802144AC *pBox, f32 (*pMtx)[4], f32 (*pOut)[3])
{
    fn_80213BCC_Row(pBox, pMtx, pOut, 0);
    fn_80213BCC_Row(pBox, pMtx, pOut, 1);
    fn_80213BCC_Row(pBox, pMtx, pOut, 2);
}

void fn_80214140(void *pMtx)
{
    if (pMtx != 0) {
        fn_801D0424(lbl_8039B580, pMtx);
    } else {
        fn_801D1288(2, lbl_8039B580);
    }
}

void fn_80214184(void *pMtx)
{
    if (pMtx != 0) {
        fn_801D0424(lbl_8039B5C0, pMtx);
    } else {
        fn_801D0F80(lbl_8039B5C0);
    }
}

void fn_802141C4(void *pMtxA, void *pMtxB, void *pMtxC)
{
    fn_801D04C4();
    if (pMtxA != 0) {
        fn_801D06D4(pMtxA);
    }
    if (pMtxB != 0) {
        fn_801D0664(pMtxB);
    }
    if (pMtxC != 0) {
        fn_801D0664(pMtxC);
    }
    fn_801D0F80(lbl_8039B5C0);
    fn_801D0544();
}

unsigned int fn_80214238(void *pPoints, int numPoints, Extent_802144AC *pExtent, void *pArg)
{
    unsigned int result;

    if (pExtent != 0) {
        fn_802144AC(pExtent);
        result = fn_80213F18(pPoints, numPoints, lbl_8039B580, pExtent, pArg);
    } else {
        result = fn_80213DB0(pPoints, numPoints, lbl_8039B580, pArg);
    }
    return result;
}

int fn_802142B0(f32 *pNdc, f32 *pClip, f32 *pPos)
{
    f32 aClip[4];
    f32 x;
    f32 y;
    f32 z;
    int code;

    if (pPos == 0) {
        pPos = lbl_802F9D8C;
    }
    if (pClip == 0) {
        pClip = aClip;
    }
    x = lbl_8039B5C0[0][0] * pPos[0] + lbl_8039B5C0[0][1] * pPos[1] + lbl_8039B5C0[0][2] * pPos[2] + lbl_8039B5C0[0][3];
    y = lbl_8039B5C0[1][0] * pPos[0] + lbl_8039B5C0[1][1] * pPos[1] + lbl_8039B5C0[1][2] * pPos[2] + lbl_8039B5C0[1][3];
    z = lbl_8039B5C0[2][0] * pPos[0] + lbl_8039B5C0[2][1] * pPos[1] + lbl_8039B5C0[2][2] * pPos[2] + lbl_8039B5C0[2][3];
    pClip[0] = lbl_8039B580[0][0] * x + lbl_8039B580[0][2] * z;
    pClip[1] = lbl_8039B580[1][1] * y + lbl_8039B580[1][2] * z;
    pClip[2] = lbl_8039B580[2][2] * z + lbl_8039B580[2][3];
    pClip[3] = lbl_8039B580[3][2] * z;
    if (pNdc != 0) {
        f32 inv = 1.0f / pClip[3];

        pNdc[0] = pClip[0] * inv;
        pNdc[1] = pClip[1] * inv;
        pNdc[2] = pClip[2] * inv;
    }
    code = 0;
    if (!(pClip[0] >= -pClip[3])) {
        code = 2;
    } else if (!(pClip[0] <= pClip[3])) {
        code = 1;
    }
    if (!(pClip[1] >= -pClip[3])) {
        code |= 8;
    } else if (!(pClip[1] <= pClip[3])) {
        code |= 4;
    }
    if (!(pClip[2] >= -pClip[3])) {
        code |= 0x20;
    } else if (!(pClip[2] <= pClip[3])) {
        code |= 0x10;
    }
    return code;
}

unsigned int fn_8021445C(Extent_802144AC *pBox, Extent_802144AC *pExtent, void *pArg)
{
    u8 aPoints[0x60];

    fn_80213BCC(pBox, lbl_8039B5C0, (f32 (*)[3])aPoints);
    return fn_80214238(aPoints, 8, pExtent, pArg);
}

void fn_802144AC(Extent_802144AC *pExtent)
{
    pExtent->mMin[2] = 3.4028235e38f;
    pExtent->mMin[1] = 3.4028235e38f;
    pExtent->mMin[0] = 3.4028235e38f;
    pExtent->mMax[2] = -3.4028235e38f;
    pExtent->mMax[1] = -3.4028235e38f;
    pExtent->mMax[0] = -3.4028235e38f;
}

void fn_802144D8(Extent_802144AC *pExtent, float x, float y, float z)
{
    if (!(x >= pExtent->mMin[0])) {
        pExtent->mMin[0] = x;
    }
    if (!(x <= pExtent->mMax[0])) {
        pExtent->mMax[0] = x;
    }
    if (!(y >= pExtent->mMin[1])) {
        pExtent->mMin[1] = y;
    }
    if (!(y <= pExtent->mMax[1])) {
        pExtent->mMax[1] = y;
    }
    if (!(z >= pExtent->mMin[2])) {
        pExtent->mMin[2] = z;
    }
    if (!(z <= pExtent->mMax[2])) {
        pExtent->mMax[2] = z;
    }
}
