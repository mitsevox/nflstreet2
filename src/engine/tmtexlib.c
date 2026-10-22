#include "engine/tmlib.h"

extern Registry_8021283C lbl_8039B53C;

static void fn_802119C4(TexLib_802119C4 *pLib, TexHeader_8020E2B0 *pTex, int count, int bInit)
{
    Object_8020E52C *pMaterial;
    TexNode_802119C4 *pNode;
    const char *pName;
    int i;

    for (i = 0; i < count; i++) {
        pNode = &pLib->mpTexNodes[i];
        pMaterial = fn_8020E52C(pTex, i);
        pName = fn_8020E53C(pTex, i);
        pNode->mpName = pName;
        pNode->mTextureIndex = i;
        pNode->mpLib = pLib;
        pNode->mFirstClut = pMaterial->mUnknown8;
        pNode->mNumCluts = pMaterial->mUnknown0;
        pNode->mUnknownE = -1;
        fn_80212940(&pLib->mRegistry, i, pName, pNode);
    }
}

static void fn_80211A74(TexLib_802119C4 *pLib, TexHeader_8020E2B0 *pTex, int count, int bInit)
{
    Object_8020E5F8 *pPalette;
    int numEntries;
    int i;

    for (i = 0; i < count; i++) {
        pPalette = fn_8020E5F8(pTex, i);
        numEntries = 16;
        if (pPalette->mUnknown4 > 0x7F) {
            numEntries = 256;
        }
        fn_80212534(&pLib->mpCluts[i], pPalette->mpUnknown8, pPalette->mUnknown2, numEntries, pPalette->mUnknown4);
    }
}

static void fn_80211AFC(TexLib_802119C4 *pLib, Object_8020E5F8 *pPalette, int clutIndex, Clut_80212534 *pClut)
{
    int numEntries;

    numEntries = 16;
    if (pPalette->mUnknown4 > 0x7F) {
        numEntries = 256;
    }
    if (pClut == 0) {
        fn_80212534(&pLib->mpCluts[clutIndex], pPalette->mpUnknown8, pPalette->mUnknown2, numEntries, pPalette->mUnknown4);
    } else {
        fn_80212534(pClut, pPalette->mpUnknown8, pPalette->mUnknown2, numEntries, pPalette->mUnknown4);
    }
}

static void fn_80211B64(TexHeader_8020E2B0 *pTex, TexLib_802119C4 *pLib, int materialIndex, Object_8020E560 *pTexture, int textureIndex, int clutIndex)
{
    Object_8020E52C *pMaterial;
    Clut_80212534 *pClut;
    const char *pName;

    pMaterial = &pTex->mpMaterials[materialIndex];
    pName = fn_8020E53C(pTex, materialIndex);
    if (pMaterial->mUnknown0 != 0) {
        pClut = &pLib->mpCluts[clutIndex];
    } else {
        pClut = 0;
    }
    fn_8021242C(&pLib->mpTextures[textureIndex], pTexture->mpUnknownC, pTexture->mWidth, pTexture->mHeight, pTexture->mFormat, pMaterial->mUnknown2, (void *)pTexture->mUnknown8, pClut);
    fn_802126BC(&pLib->mpTextures[textureIndex], pName);
}

static void fn_80211C08(TexLib_802119C4 *pLib, TexHeader_8020E2B0 *pTex, int count, int bInit)
{
    Object_8020E52C *pMaterial;
    Object_8020E560 *pTexture;
    Clut_80212534 *pClut;
    const char *pName;
    int i;

    for (i = 0; i < count; i++) {
        pMaterial = fn_8020E52C(pTex, i);
        pName = fn_8020E53C(pTex, i);
        pTexture = fn_8020E560(pTex, pMaterial->mUnknown4);
        if (pMaterial->mUnknown0 != 0) {
            pClut = &pLib->mpCluts[pMaterial->mUnknown8];
        } else {
            pClut = 0;
        }
        if (bInit) {
            fn_8021239C(&pLib->mpTextures[i], pTexture->mpUnknownC, pTexture->mWidth, pTexture->mHeight, pTexture->mFormat, pMaterial->mUnknown2, (void *)pTexture->mUnknown8, pClut);
        } else {
            fn_8021242C(&pLib->mpTextures[i], pTexture->mpUnknownC, pTexture->mWidth, pTexture->mHeight, pTexture->mFormat, pMaterial->mUnknown2, (void *)pTexture->mUnknown8, pClut);
        }
        fn_802126BC(&pLib->mpTextures[i], pName);
    }
}

void fn_80211D24(TexLib_802119C4 *pLib, int numTexNodes, int numTextures, int numCluts)
{
    pLib->mNumTexNodes = numTexNodes;
    pLib->mpTexNodes = fn_802127D0(numTexNodes, sizeof(TexNode_802119C4));
    pLib->mNumTextures = numTextures;
    pLib->mpTextures = fn_802127D0(numTextures, sizeof(Texture_80212234));
    pLib->mNumCluts = numCluts;
    pLib->mpCluts = fn_802127D0(numCluts, sizeof(Clut_80212534));
    fn_80212850(&pLib->mRegistry, numTexNodes, 0, 0);
}

void fn_80211DA8(TexLib_802119C4 *pLib)
{
    fn_802128A8(&pLib->mRegistry);
    fn_80212814(pLib->mpTexNodes);
    pLib->mpTexNodes = 0;
    pLib->mNumTexNodes = 0;
    fn_80212814(pLib->mpTextures);
    pLib->mpTextures = 0;
    pLib->mNumTextures = 0;
    fn_80212814(pLib->mpCluts);
    pLib->mpCluts = 0;
    pLib->mNumCluts = 0;
}

void fn_80211E08(TexLib_802119C4 *pLib, TexHeader_8020E2B0 *pTex)
{
    int numMaterials;
    int numPalettes;

    if (pTex == 0) {
        fn_80211D24(pLib, 0, 0, 0);
        return;
    }
    fn_8020E2B0(pTex);
    numMaterials = fn_8020E51C(pTex);
    numPalettes = fn_8020E524(pTex);
    fn_80211D24(pLib, numMaterials, numMaterials, numPalettes);
    fn_80211A74(pLib, pTex, numPalettes, 1);
    fn_802119C4(pLib, pTex, numMaterials, 1);
    fn_80211C08(pLib, pTex, numMaterials, 1);
}

void fn_80211EBC(TexHeader_8020E2B0 *pTex, TexLib_802119C4 *pLib, int materialIndex, Object_8020E560 *pTexture, int textureIndex, int clutIndex)
{
    fn_80211B64(pTex, pLib, materialIndex, pTexture, textureIndex, clutIndex);
}

void fn_80211EDC(TexLib_802119C4 *pLib, Object_8020E5F8 *pPalette, int clutIndex, Clut_80212534 *pClut)
{
    fn_80211AFC(pLib, pPalette, clutIndex, pClut);
}

void fn_80211EFC(TexLib_802119C4 *pLib)
{
    int i;

    for (i = 0; i < pLib->mNumTextures; i++) {
        fn_80212530(&pLib->mpTextures[i]);
    }
    for (i = 0; i < pLib->mNumCluts; i++) {
        fn_80212654(&pLib->mpCluts[i]);
    }
    fn_80211DA8(pLib);
}

void fn_80211F94(int maxLibs)
{
    fn_80212850(&lbl_8039B53C, maxLibs, 1, 1);
}

void fn_80211FC8(void)
{
    fn_802128A8(&lbl_8039B53C);
}

void fn_80211FF0(void)
{
    fn_802128DC(&lbl_8039B53C);
}

void fn_80212018(const char *pName, TexLib_802119C4 *pLib)
{
    if (pLib != 0) {
        fn_8021295C(&lbl_8039B53C, pName, pLib);
    }
}

Texture_80212234 *fn_80212050(TexNode_802119C4 *pNode)
{
    if (pNode != 0) {
        return &pNode->mpLib->mpTextures[pNode->mTextureIndex];
    }
    return 0;
}

Clut_80212534 *fn_80212074(TexNode_802119C4 *pNode, int index)
{
    TexLib_802119C4 *pLib;

    if (pNode != 0) {
        pLib = pNode->mpLib;
        if (index < pNode->mNumCluts) {
            index += pNode->mFirstClut;
            return &pLib->mpCluts[index];
        }
    }
    return 0;
}

TexNode_802119C4 *fn_802120AC(TexLib_802119C4 *pLib, const char *pName)
{
    if (pLib != 0) {
        return fn_80212C60(&pLib->mRegistry, pName);
    }
    return fn_80212BDC(&lbl_8039B53C, pName);
}

Texture_80212234 *fn_802120E4(TexLib_802119C4 *pLib, const char *pName)
{
    TexNode_802119C4 *pNode;
    Texture_80212234 *pTexture;

    pTexture = 0;
    pNode = fn_802120AC(pLib, pName);
    if (pNode != 0) {
        pTexture = fn_80212050(pNode);
    }
    return pTexture;
}

Clut_80212534 *fn_80212124(TexLib_802119C4 *pLib, const char *pName, int index)
{
    TexNode_802119C4 *pNode;
    Clut_80212534 *pClut;

    pClut = 0;
    pNode = fn_802120AC(pLib, pName);
    if (pNode != 0) {
        pClut = fn_80212074(pNode, index);
    }
    return pClut;
}

void fn_8021216C(TexLib_802119C4 *pLib, Desc_802EE9E4 *pDesc)
{
    int i;

    for (i = 0; i < pLib->mNumTextures; i++) {
        fn_80212310(&pLib->mpTextures[i], pDesc);
    }
}

void fn_802121D0(TexLib_802119C4 *pLib, TexWrapDesc_80212374 *pDesc)
{
    int i;

    for (i = 0; i < pLib->mNumTextures; i++) {
        fn_80212374(&pLib->mpTextures[i], pDesc);
    }
}
