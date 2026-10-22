#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include "engine/tmlib.h"

extern int fn_801D2BD0(void *p);
extern void fn_8024EB28(GXCullMode mode);
extern void fn_8025221C(GXBool dither);
extern void fn_802520E0(GXBool compareEnable, GXCompare func, GXBool updateEnable);
extern void fn_80252114(GXBool beforeTex);
extern void fn_80252034(GXBlendMode type, GXBlendFactor srcFactor, GXBlendFactor dstFactor, GXLogicOp op);
extern void fn_802527D4(RenderViewport_80210298 *pViewport);
extern void fn_80250654(GXTlutObj *pTlut, u32 tlutName);
extern void fn_802503D8(GXTexObj *pObj, u32 tlutName);
extern void fn_802505A8(GXTexObj *pObj, GXTexMapID id);
extern GXTexFmt fn_8025040C(const GXTexObj *pObj);
extern void fn_802517E8(GXTevRegID id, GXColor color);
extern void fn_80251864(GXTevKColorID id, GXColor color);

extern RenderState_80210298 lbl_803E96E8;
extern Texture_80212234 lbl_8039B4B0;
extern GXTlutObj lbl_8039B4E0;
extern GXTlutObj lbl_8039B508;
extern int lbl_802F9C08[4];
extern unsigned char lbl_803EBEF0;
extern Texture_80212234 *lbl_803EBEF4;
extern void *lbl_803EBEF8;
extern void *lbl_803EBEFC;
extern unsigned char lbl_803EBF00;


void fn_80210298(void)
{
    if (lbl_803EBF00) {
        fn_801D2BD0(lbl_803EBEF8);
        lbl_803EBEF8 = 0;
        fn_801D2BD0(lbl_803EBEFC);
        lbl_803EBEFC = 0;
        lbl_803EBF00 = 0;
    }
}

void fn_802102E8(void)
{
    fn_80212658(&lbl_8039B4B0);
    fn_80210368(&lbl_8039B4B0);
    fn_80210388();
    lbl_803EBEF0 = 1;
}

void fn_8021032C(void)
{
    fn_80212530(&lbl_8039B4B0);
    lbl_803EBEF0 = 0;
    lbl_803EBEF4 = 0;
    fn_80210298();
}

void fn_80210368(Texture_80212234 *pTexture)
{
    if (pTexture != 0) {
        lbl_803EBEF4 = pTexture;
    } else {
        lbl_803EBEF4 = &lbl_8039B4B0;
    }
}

void fn_80210388(void)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    fn_80210654(0);
    fn_80210BA4(0);
    pState->mpMaterial = 0;
    pState->mpShader = 0;
    pState->mNumHooks = 0;
    pState->mBlendMode = 0;
    pState->mBindFunc = 0;
}

void fn_802103DC(void)
{
    GXColor ambColor = {0xC0, 0xC0, 0xC0, 0xFF};
    GXColor matColor = {0xFF, 0xFF, 0xFF, 0xFF};

    fn_80210388();
    fn_80210BD8(1);
    fn_8024EB28(GX_CULL_NONE);
    fn_8025221C(GX_FALSE);
    fn_802520E0(GX_TRUE, GX_LEQUAL, GX_TRUE);
    fn_80252114(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, ambColor);
    GXSetChanMatColor(GX_COLOR0A0, matColor);
    GXSetChanAmbColor(GX_COLOR1A1, ambColor);
    GXSetChanMatColor(GX_COLOR1A1, matColor);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetCurrentMtx(GX_PNMTX0);
    fn_802134E8();
    fn_8021077C(0);
    fn_80215B74();
}

void fn_80210608(void)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    fn_802527D4(&pState->mViewport);
}

void fn_80210634(void)
{
    fn_80215B78();
}

void fn_80210654(Model_8020F28C *pModel)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    if (pModel != 0) {
        if (lbl_803E96E8.mpGeom != pModel->mpGeom) {
            pState->mUnknown60 = -1;
            lbl_803E96E8.mpGeom = pModel->mpGeom;
        }
        pState->mpSwap = pModel->mpSwap;
        pState->mpChannels = pModel->mpChannels;
        pState->mpInst = pModel->mpInst;
        pState->mpRint = pModel->mpRint;
        pState->mpFade = pModel->mpFade;
        pState->mpExtn = pModel->mpExtn;
        pState->mpSkel = pModel->mpSkel;
        fn_80210BB0(pModel->mpTxfm);
    } else {
        lbl_803E96E8.mpGeom = 0;
        pState->mpSwap = 0;
        pState->mpChannels = 0;
        pState->mpInst = 0;
        pState->mpRint = 0;
        pState->mpFade = 0;
        pState->mpExtn = 0;
        pState->mpSkel = 0;
        fn_80210BB0(0);
        pState->mUnknown60 = -1;
    }
    pState->mLod = 0;
}

void fn_80210724(ClusterObj_80210724 *pClusterObj)
{
    lbl_803E96E8.mpClusterObj = pClusterObj;
    if (pClusterObj != 0) {
        GXSetArray(GX_POS_MTX_ARRAY, pClusterObj->mpMatrices, 0x30);
        GXSetArray(GX_NRM_MTX_ARRAY, pClusterObj->mpMatrices, 0x10);
    }
}

void fn_8021077C(Shader_80211638 *pShader)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    if (pShader == 0) {
        pShader = fn_80211984(0);
    }
    if (pShader != pState->mpShader) {
        Shader_80211638 *pOld = pState->mpShader;

        pState->mBindFunc = 0;
        if (pOld != 0 && pOld->mUnbindFunc != 0) {
            pOld->mUnbindFunc(pOld);
        }
        fn_80213224(pShader->mpDef->mUnknown14);
        if (pShader->mBindFunc != 0) {
            pShader->mBindFunc(pShader);
        }
        pState->mpShader = pShader;
    }
}

void fn_80210814(GXTexMapID id, Texture_80212234 *pTexture, Clut_80212534 *pClut)
{
    if (pTexture != 0) {
        if (pClut != 0) {
            if (pClut->mType == 0) {
                fn_80250654(&pClut->u.maTlut[0], id);
                fn_802503D8(&pTexture->mObj, id);
            } else if (pClut->mType == 1) {
                GXTexMapID indirectId = id + 4;

                if (fn_8025040C(&pTexture->mObj) == GX_TF_C4) {
                    fn_80250654(&lbl_8039B4E0, id);
                    fn_802503D8(&pTexture->mObj, id);
                } else {
                    fn_80250654(&lbl_8039B508, id);
                    fn_802503D8(&pTexture->mObj, id);
                }
                fn_802505A8(&pClut->u.mObj, indirectId);
            } else {
                u32 secondId = id + 8;

                fn_80250654(&pClut->u.maTlut[0], id);
                fn_80250654(&pClut->u.maTlut[1], secondId);
                fn_802503D8(&pTexture->mObj, id);
            }
        }
        fn_802505A8(&pTexture->mObj, id);
        if (pClut != 0 && pClut->mType == 2) {
            fn_802503D8(&pTexture->mObj, id + 8);
            fn_802505A8(&pTexture->mObj, id + 4);
            fn_802503D8(&pTexture->mObj, id);
        }
    } else if (lbl_803EBEF4 != 0) {
        fn_80210814(id, lbl_803EBEF4, 0);
    }
}

void fn_80210970(Material_8020FAAC *pMaterial)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    if (pMaterial == pState->mpMaterial) {
        return;
    }
    if (pMaterial != 0) {
        Shader_80211638 *pShader = pMaterial->mpShader;

        fn_8021077C(pShader);
        if (pState->mBindFunc == 0) {
            int i;
            int j;

            for (i = 0; i < pShader->mNumTextures; i++) {
                fn_80210814(i, pMaterial->mpParms[i].mpTexture, pMaterial->mpParms[i].mpClut);
            }
            for (j = 0; j < pShader->mNumConsts; j++) {
                ShaderParmDef_80211638 *pParm = &pShader->mpFirstConst[j];
                void **pValue = &pMaterial->maUnknown14[pParm->mUnknown11];

                switch (pParm->mType) {
                case 2:
                    fn_802517E8(pParm->mIndex + 1, *(GXColor *)pValue);
                    break;
                case 3:
                    fn_80251864(pParm->mIndex, *(GXColor *)pValue);
                    break;
                case 4:
                    GXSetChanMatColor(pParm->mIndex, *(GXColor *)pValue);
                    break;
                case 5:
                    GXSetChanAmbColor(pParm->mIndex, *(GXColor *)pValue);
                    break;
                case 6: {
                    float *pScale = (float *)pValue;
                    f32 mtx[4][4];

                    mtx[0][0] = pScale[0];
                    mtx[0][1] = 0.0f;
                    mtx[0][2] = 0.0f;
                    mtx[0][3] = pScale[2];
                    mtx[1][0] = 0.0f;
                    mtx[1][1] = pScale[1];
                    mtx[1][2] = 0.0f;
                    mtx[1][3] = pScale[3];
                    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetTexCoordGen(pParm->mIndex, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
                    break;
                }
                }
            }
        } else {
            pState->mBindFunc(pMaterial);
        }
    } else {
        fn_8021077C(0);
    }
    pState->mpMaterial = pMaterial;
}

void fn_80210B6C(int index)
{
    if (lbl_803E96E8.mpMaterialList != 0) {
        fn_80210970(fn_80210184(lbl_803E96E8.mpMaterialList, index));
    }
}

void fn_80210BA4(MaterialList_8020FF34 *pList)
{
    lbl_803E96E8.mpMaterialList = pList;
}

void fn_80210BB0(void *pTexXForm)
{
    lbl_803E96E8.mpTexXForm = pTexXForm;
    lbl_802F9C08[0] = -2;
    lbl_802F9C08[1] = -2;
    lbl_802F9C08[2] = -2;
    lbl_802F9C08[3] = -2;
}

void fn_80210BD8(unsigned int mode)
{
    RenderState_80210298 *pState = &lbl_803E96E8;

    if (mode != pState->mBlendMode) {
        switch (mode) {
        case 1:
            fn_80252034(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            break;
        case 2:
            fn_80252034(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            break;
        case 3:
            fn_80252034(GX_BM_BLEND, GX_BL_ZERO, GX_BL_SRCCLR, GX_LO_NOOP);
            break;
        case 4:
            fn_80252034(GX_BM_BLEND, GX_BL_ZERO, GX_BL_SRCALPHA, GX_LO_NOOP);
            break;
        case 5:
            fn_80252034(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
            break;
        case 6:
            fn_80252034(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
            break;
        }
        pState->mBlendMode = mode;
    }
}

void fn_80210CC4(float nearZ, float farZ)
{
    RenderState_80210298 *pState = &lbl_803E96E8;
    RenderViewport_80210298 *pViewport;

    pState->mViewport.mNear = nearZ;
    pState->mViewport.mFar = farZ;
    pViewport = &pState->mViewport;
    GXSetViewport(pViewport->mLeft, pViewport->mTop, pViewport->mWidth, pViewport->mHeight, pViewport->mNear,
                  pViewport->mFar);
}

void fn_80210D10(GXBool compareEnable, GXCompare func, GXBool updateEnable)
{
    fn_802520E0(compareEnable, func, updateEnable);
}
