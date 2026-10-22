#include "engine/tmlib.h"

void fn_8020F28C(Model_8020F28C *pModel)
{
    pModel->mpGeom = 0;
    pModel->mpExtn = 0;
    pModel->mpClst = 0;
    pModel->mpSkel = 0;
    pModel->mpSwap = 0;
    pModel->mpMatl = 0;
    pModel->mpChannels = 0;
    pModel->mpTxfm = 0;
    pModel->mpInst = 0;
    pModel->mpRint = 0;
    pModel->mpDInf = 0;
    pModel->mpFade = 0;
}

void fn_8020F2C4(Model_8020F28C *pDst, Model_8020F28C *pSrc)
{
    pDst->mpInfo = pSrc->mpInfo;
    pDst->mpGeom = pSrc->mpGeom;
    pDst->mpExtn = pSrc->mpExtn;
    pDst->mpClst = pSrc->mpClst;
    pDst->mpSkel = pSrc->mpSkel;
    pDst->mpSwap = pSrc->mpSwap;
    pDst->mpMatl = pSrc->mpMatl;
    pDst->mpChannels = 0;
    pDst->mpTxfm = pSrc->mpTxfm;
    pDst->mpInst = pSrc->mpInst;
    pDst->mpRint = pSrc->mpRint;
    pDst->mpDInf = pSrc->mpDInf;
    pDst->mpFade = pSrc->mpFade;
}

int fn_8020F330(Model_8020F28C *pModel, ModelRes_8020EA18 *pRes, unsigned int tag)
{
    void *pData = fn_8020EC50(pRes, tag, 0);

    if (pData != 0) {
        switch (tag) {
        case 'Info':
            pModel->mpInfo = pData;
            break;
        case 'Extn':
            pModel->mpExtn = pData;
            break;
        case 'Geom':
            pModel->mpGeom = pData;
            break;
        case 'Clst':
            pModel->mpClst = pData;
            break;
        case 'Swap':
            pModel->mpSwap = pData;
            break;
        case 'Skel':
            pModel->mpSkel = pData;
            break;
        case 'Matl':
            pModel->mpMatl = pData;
            break;
        case 'Txfm':
            pModel->mpTxfm = pData;
            break;
        case 'Inst':
            pModel->mpInst = pData;
            break;
        case 'Rint':
            pModel->mpRint = pData;
            break;
        case 'DInf':
            pModel->mpDInf = pData;
            break;
        case 'Fade':
            pModel->mpFade = pData;
            break;
        }
        return 1;
    }
    return 0;
}

void fn_8020F4D0(Model_8020F28C *pModel, ModelRes_8020EA18 *pRes)
{
    pModel->mpDInf = 0;
    pModel->mpFade = 0;
    fn_8020F330(pModel, pRes, 'Info');
    fn_8020F330(pModel, pRes, 'Extn');
    fn_8020F330(pModel, pRes, 'Geom');
    fn_8020F330(pModel, pRes, 'Clst');
    fn_8020F330(pModel, pRes, 'Swap');
    fn_8020F330(pModel, pRes, 'Skel');
    fn_8020F330(pModel, pRes, 'Matl');
    fn_8020F330(pModel, pRes, 'Txfm');
    fn_8020F330(pModel, pRes, 'Inst');
    fn_8020F330(pModel, pRes, 'Rint');
    fn_8020F330(pModel, pRes, 'Fade');
    fn_8020F330(pModel, pRes, 'DInf');
}

void fn_8020F5F0(int maxChunkTypes)
{
    fn_8020EB08(maxChunkTypes);
    fn_8020EB48('Info', 0, 1);
    fn_8020EB48('Lite', (ChunkRelocFunc_8020EA18)fn_802146C8, 0);
    fn_8020EB48('Matl', (ChunkRelocFunc_8020EA18)fn_80213228, 1);
    fn_8020EB48('Text', 0, 0);
    fn_8020EB48('Skel', (ChunkRelocFunc_8020EA18)fn_80215E5C, 1);
    fn_8020EB48('Geom', (ChunkRelocFunc_8020EA18)fn_8020F08C, 2);
    fn_8020EB48('Extn', (ChunkRelocFunc_8020EA18)fn_80215804, 0);
    fn_8020EB48('Swap', (ChunkRelocFunc_8020EA18)fn_802160A0, 0);
    fn_8020EB48('Clst', (ChunkRelocFunc_8020EA18)fn_80213384, 0);
    fn_8020EB48('Txfm', (ChunkRelocFunc_8020EA18)fn_80215838, 1);
    fn_8020EB48('Inst', (ChunkRelocFunc_8020EA18)fn_80215C14, 1);
    fn_8020EB48('Rint', (ChunkRelocFunc_8020EA18)fn_80215CB0, 1);
    fn_8020EB48('Fade', 0, 0);
    fn_8020EB48('DInf', (ChunkRelocFunc_8020EA18)fn_80215B7C, 1);
    fn_8020EB48('MAnm', (ChunkRelocFunc_8020EA18)fn_80215DC0, 1);
}

void fn_8020F76C(void)
{
    fn_8020EB70();
}

void fn_8020F78C(Model_8020F28C *pModel, MaterialLib_80213228 *pMatLib)
{
    MaterialLib_80213228 *pOld = pModel->mpMatl;
    int numMaterials = pOld->mNumMaterials;
    unsigned short *pRemap = fn_802127D0(numMaterials, 2);
    int i;

    for (i = 0; i < numMaterials; i++) {
        pRemap[i] = fn_8021330C(pMatLib, pOld->mpMaterials[i].mpName);
    }
    fn_8020F178(pModel->mpGeom, pRemap, numMaterials);
    fn_80212814(pRemap);
    pModel->mpMatl = pMatLib;
}

void fn_8020F824(Model_8020F28C *pModel, void *pOther)
{
    if (pModel->mpSkel != 0 && pModel->mpClst != 0) {
        short *pRemap = fn_80215EE0(pModel->mpSkel, pOther);

        if (pRemap != 0) {
            fn_802133B8(pModel->mpClst, pRemap);
            fn_80215F78(pModel->mpSkel, pRemap);
            fn_80212814(pRemap);
        }
        pModel->mpSkel->mpNames = 0;
    }
}

void fn_8020F89C(Model_8020F28C *pModel)
{
    Geom_8020ED10 *pGeom = pModel->mpGeom;
    int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumAttrs; i++) {
            pModel->mpChannels[i] = 0;
        }
    }
}

void fn_8020F8E0(Model_8020F28C *pModel)
{
    if (pModel->mpGeom != 0) {
        pModel->mpChannels = fn_802127D0(pModel->mpGeom->mNumAttrs, 4);
        fn_8020F89C(pModel);
    }
}

void fn_8020F92C(Model_8020F28C *pModel)
{
    if (pModel->mpChannels != 0) {
        fn_80212814(pModel->mpChannels);
        pModel->mpChannels = 0;
    }
}

void fn_8020F96C(Model_8020F28C *pModel, Extent_802144AC *pExtent, int state, int arg)
{
    Geom_8020ED10 *pGeom = pModel->mpGeom;
    Swap_802160A0 *pSwap = pModel->mpSwap;

    if (state == -1 || pSwap == 0) {
        unsigned int i;

        for (i = 0; i < pGeom->mNumNodes; i++) {
            fn_8020F1D8(pGeom, i, pExtent);
        }
    } else {
        SwapState_802160A0 *pState = fn_80216190(pSwap, state, arg);

        if (pState != 0) {
            int i;

            for (i = 0; i < pState->mNumNodes; i++) {
                fn_8020F1D8(pGeom, pSwap->mpNodeIndices[pState->mFirstNode + i], pExtent);
            }
        }
    }
}
