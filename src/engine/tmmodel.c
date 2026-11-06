/* TM renderer models: binds the chunks of a loaded model resource to a model, registers the chunk
   types at start-up, remaps a model's materials and skeleton clusters, manages its vertex channel
   array and computes its bounding extent. */

#include "engine/tmlib.h"

void TMModelReset(TMModel_t *pModel)
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

void TMModelClone(TMModel_t *pDst, TMModel_t *pSrc)
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

int TMModelBindModelChunk(TMModel_t *pModel, TMModelRes_t *pRes, unsigned int tag)
{
    void *pData = TMModelResGetChunk(pRes, tag, 0);

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

void TMModelBindModelRes(TMModel_t *pModel, TMModelRes_t *pRes)
{
    pModel->mpDInf = 0;
    pModel->mpFade = 0;
    TMModelBindModelChunk(pModel, pRes, 'Info');
    TMModelBindModelChunk(pModel, pRes, 'Extn');
    TMModelBindModelChunk(pModel, pRes, 'Geom');
    TMModelBindModelChunk(pModel, pRes, 'Clst');
    TMModelBindModelChunk(pModel, pRes, 'Swap');
    TMModelBindModelChunk(pModel, pRes, 'Skel');
    TMModelBindModelChunk(pModel, pRes, 'Matl');
    TMModelBindModelChunk(pModel, pRes, 'Txfm');
    TMModelBindModelChunk(pModel, pRes, 'Inst');
    TMModelBindModelChunk(pModel, pRes, 'Rint');
    TMModelBindModelChunk(pModel, pRes, 'Fade');
    TMModelBindModelChunk(pModel, pRes, 'DInf');
}

void TMModelInit(int maxChunkTypes)
{
    TMModelResInit(maxChunkTypes);
    TMModelResAddChunkType('Info', 0, 1);
    TMModelResAddChunkType('Lite', (TMChunkRelocFunc_t)TMLightDefRelocateChunk, 0);
    TMModelResAddChunkType('Matl', (TMChunkRelocFunc_t)TMMaterialDefRelocateChunk, 1);
    TMModelResAddChunkType('Text', 0, 0);
    TMModelResAddChunkType('Skel', (TMChunkRelocFunc_t)TMSkelRelocateChunk, 1);
    TMModelResAddChunkType('Geom', (TMChunkRelocFunc_t)TMGeomRelocateChunk, 2);
    TMModelResAddChunkType('Extn', (TMChunkRelocFunc_t)TMExtentsDefRelocateChunk, 0);
    TMModelResAddChunkType('Swap', (TMChunkRelocFunc_t)TMSwapRelocateChunk, 0);
    TMModelResAddChunkType('Clst', (TMChunkRelocFunc_t)TMClusterDefRelocateChunk, 0);
    TMModelResAddChunkType('Txfm', (TMChunkRelocFunc_t)TMTexXformRelocateChunk, 1);
    TMModelResAddChunkType('Inst', (TMChunkRelocFunc_t)TMInstanceDefRelocateChunk, 1);
    TMModelResAddChunkType('Rint', (TMChunkRelocFunc_t)TMInstanceRegionDefRelocateChunk, 1);
    TMModelResAddChunkType('Fade', 0, 0);
    TMModelResAddChunkType('DInf', (TMChunkRelocFunc_t)TMDebugInfoRelocateChunk, 1);
    TMModelResAddChunkType('MAnm', (TMChunkRelocFunc_t)TMMorphAnimRelocate, 1);
}

void TMModelShutdown(void)
{
    TMModelResShutdown();
}

void TMModelRemapMaterials(TMModel_t *pModel, TMMaterialDefList_t *pMatLib)
{
    TMMaterialDefList_t *pOld = pModel->mpMatl;
    int numMaterials = pOld->mNumMaterials;
    unsigned short *pRemap = TMMemAllocArray(numMaterials, 2);
    int i;

    for (i = 0; i < numMaterials; i++) {
        pRemap[i] = TMMaterialDefGetIndexByName(pMatLib, pOld->mpMaterials[i].mpName);
    }
    TMGeometryRemapMaterials(pModel->mpGeom, pRemap, numMaterials);
    TMMemFreeArray(pRemap);
    pModel->mpMatl = pMatLib;
}

void TMModelRemapClusters(TMModel_t *pModel, void *pOther)
{
    if (pModel->mpSkel != 0 && pModel->mpClst != 0) {
        short *pRemap = TMSkelBuildRemapTable(pModel->mpSkel, pOther);

        if (pRemap != 0) {
            TMClusterDefRemap(pModel->mpClst, pRemap);
            TMSkelRemapNodes(pModel->mpSkel, pRemap);
            TMMemFreeArray(pRemap);
        }
        pModel->mpSkel->mpNames = 0;
    }
}

void TMModelResetChannels(TMModel_t *pModel)
{
    TMGeom_t *pGeom = pModel->mpGeom;
    int i;

    if (pGeom != 0) {
        for (i = 0; i < pGeom->mNumAttrs; i++) {
            pModel->mpChannels[i] = 0;
        }
    }
}

void TMModelAllocChannels(TMModel_t *pModel)
{
    if (pModel->mpGeom != 0) {
        pModel->mpChannels = TMMemAllocArray(pModel->mpGeom->mNumAttrs, 4);
        TMModelResetChannels(pModel);
    }
}

void TMModelFreeChannels(TMModel_t *pModel)
{
    if (pModel->mpChannels != 0) {
        TMMemFreeArray(pModel->mpChannels);
        pModel->mpChannels = 0;
    }
}

void TMModelAddExtent(TMModel_t *pModel, Extent_802144AC *pExtent, int state, int arg)
{
    TMGeom_t *pGeom = pModel->mpGeom;
    TMSwapDef_t *pSwap = pModel->mpSwap;

    if (state == -1 || pSwap == 0) {
        unsigned int i;

        for (i = 0; i < pGeom->mNumNodes; i++) {
            TMGeomAddNodeExtent(pGeom, i, pExtent);
        }
    } else {
        TMSwapState_t *pState = TMSwapGetState(pSwap, state, arg);

        if (pState != 0) {
            int i;

            for (i = 0; i < pState->mNumNodes; i++) {
                TMGeomAddNodeExtent(pGeom, pSwap->mpNodeIndices[pState->mFirstNode + i], pExtent);
            }
        }
    }
}
