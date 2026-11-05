/* TM renderer texture libraries: turns a loaded texture file into GX textures and palettes looked
   up by name, keeps a registry of libraries, and lets the game replace a library's textures. */

#include "engine/tmlib.h"

extern TMRegistry_t lbl_8039B53C;

static void _TMTexLibInitTexNodes(TMTexLib_t *pLib, TexFileHeader_t *pTex, int count, int bInit)
{
    TexFileMaterial_t *pMaterial;
    TMTexNode_t *pNode;
    const char *pName;
    int i;

    for (i = 0; i < count; i++) {
        pNode = &pLib->mpTexNodes[i];
        pMaterial = TexGetMaterialByIndex(pTex, i);
        pName = TexGetMaterialNameByIndex(pTex, i);
        pNode->mpName = pName;
        pNode->mTextureIndex = i;
        pNode->mpLib = pLib;
        pNode->mFirstClut = pMaterial->mUnknown8;
        pNode->mNumCluts = pMaterial->mUnknown0;
        pNode->mUnknownE = -1;
        TMRegistrySetEntry(&pLib->mRegistry, i, pName, pNode);
    }
}

static void _TMTexLibInitCluts(TMTexLib_t *pLib, TexFileHeader_t *pTex, int count, int bInit)
{
    TexFilePalette_t *pPalette;
    int numEntries;
    int i;

    for (i = 0; i < count; i++) {
        pPalette = TexGetPaletteByIndex(pTex, i);
        numEntries = 16;
        if (pPalette->mUnknown4 > 0x7F) {
            numEntries = 256;
        }
        TMTextureClutNew(&pLib->mpCluts[i], pPalette->mpUnknown8, pPalette->mUnknown2, numEntries, pPalette->mUnknown4);
    }
}

void TMTexLibSetClutData(TMTexLib_t *pLib, TexFilePalette_t *pPalette, int clutIndex, TMClut_t *pClut)
{
    int numEntries;

    numEntries = 16;
    if (pPalette->mUnknown4 > 0x7F) {
        numEntries = 256;
    }
    if (pClut == 0) {
        TMTextureClutNew(&pLib->mpCluts[clutIndex], pPalette->mpUnknown8, pPalette->mUnknown2, numEntries, pPalette->mUnknown4);
    } else {
        TMTextureClutNew(pClut, pPalette->mpUnknown8, pPalette->mUnknown2, numEntries, pPalette->mUnknown4);
    }
}

void TMTexLibSetTextureData(TexFileHeader_t *pTex, TMTexLib_t *pLib, int materialIndex, TexFileImage_t *pTexture, int textureIndex, int clutIndex)
{
    TexFileMaterial_t *pMaterial;
    TMClut_t *pClut;
    const char *pName;

    pMaterial = &pTex->mpMaterials[materialIndex];
    pName = TexGetMaterialNameByIndex(pTex, materialIndex);
    if (pMaterial->mUnknown0 != 0) {
        pClut = &pLib->mpCluts[clutIndex];
    } else {
        pClut = 0;
    }
    TMTextureSetTexData(&pLib->mpTextures[textureIndex], pTexture->mpUnknownC, pTexture->mWidth, pTexture->mHeight, pTexture->mFormat, pMaterial->mUnknown2, pTexture->mUnknown8, pClut);
    TMTextureSetTexName(&pLib->mpTextures[textureIndex], pName);
}

static void _TMTexLibInitTextures(TMTexLib_t *pLib, TexFileHeader_t *pTex, int count, int bInit)
{
    TexFileMaterial_t *pMaterial;
    TexFileImage_t *pTexture;
    TMClut_t *pClut;
    const char *pName;
    int i;

    for (i = 0; i < count; i++) {
        pMaterial = TexGetMaterialByIndex(pTex, i);
        pName = TexGetMaterialNameByIndex(pTex, i);
        pTexture = TexGetTextureByIndex(pTex, pMaterial->mUnknown4);
        if (pMaterial->mUnknown0 != 0) {
            pClut = &pLib->mpCluts[pMaterial->mUnknown8];
        } else {
            pClut = 0;
        }
        if (bInit) {
            TMTextureTexNew(&pLib->mpTextures[i], pTexture->mpUnknownC, pTexture->mWidth, pTexture->mHeight, pTexture->mFormat, pMaterial->mUnknown2, pTexture->mUnknown8, pClut);
        } else {
            TMTextureSetTexData(&pLib->mpTextures[i], pTexture->mpUnknownC, pTexture->mWidth, pTexture->mHeight, pTexture->mFormat, pMaterial->mUnknown2, pTexture->mUnknown8, pClut);
        }
        TMTextureSetTexName(&pLib->mpTextures[i], pName);
    }
}

void TMTexLibAlloc(TMTexLib_t *pLib, int numTexNodes, int numTextures, int numCluts)
{
    pLib->mNumTexNodes = numTexNodes;
    pLib->mpTexNodes = TMMemAllocArray(numTexNodes, sizeof(TMTexNode_t));
    pLib->mNumTextures = numTextures;
    pLib->mpTextures = TMMemAllocArray(numTextures, sizeof(TMTexture_t));
    pLib->mNumCluts = numCluts;
    pLib->mpCluts = TMMemAllocArray(numCluts, sizeof(TMClut_t));
    TMRegistryAlloc(&pLib->mRegistry, numTexNodes, 0, 0);
}

void TMTexLibFree(TMTexLib_t *pLib)
{
    TMRegistryFree(&pLib->mRegistry);
    TMMemFreeArray(pLib->mpTexNodes);
    pLib->mpTexNodes = 0;
    pLib->mNumTexNodes = 0;
    TMMemFreeArray(pLib->mpTextures);
    pLib->mpTextures = 0;
    pLib->mNumTextures = 0;
    TMMemFreeArray(pLib->mpCluts);
    pLib->mpCluts = 0;
    pLib->mNumCluts = 0;
}

void TMTexLibLoad(TMTexLib_t *pLib, TexFileHeader_t *pTex)
{
    int numMaterials;
    int numPalettes;

    if (pTex == 0) {
        TMTexLibAlloc(pLib, 0, 0, 0);
        return;
    }
    TexMipmapRelocate(pTex);
    numMaterials = TexGetNumMaterials(pTex);
    numPalettes = TexGetNumPalettes(pTex);
    TMTexLibAlloc(pLib, numMaterials, numMaterials, numPalettes);
    _TMTexLibInitCluts(pLib, pTex, numPalettes, 1);
    _TMTexLibInitTexNodes(pLib, pTex, numMaterials, 1);
    _TMTexLibInitTextures(pLib, pTex, numMaterials, 1);
}

void TMTexLibReplaceTexture(TexFileHeader_t *pTex, TMTexLib_t *pLib, int materialIndex, TexFileImage_t *pTexture, int textureIndex, int clutIndex)
{
    TMTexLibSetTextureData(pTex, pLib, materialIndex, pTexture, textureIndex, clutIndex);
}

void TMTexLibReplaceClut(TMTexLib_t *pLib, TexFilePalette_t *pPalette, int clutIndex, TMClut_t *pClut)
{
    TMTexLibSetClutData(pLib, pPalette, clutIndex, pClut);
}

void TMTexLibUnload(TMTexLib_t *pLib)
{
    int i;

    for (i = 0; i < pLib->mNumTextures; i++) {
        TMTextureTexDelete(&pLib->mpTextures[i]);
    }
    for (i = 0; i < pLib->mNumCluts; i++) {
        TMTextureClutDelete(&pLib->mpCluts[i]);
    }
    TMTexLibFree(pLib);
}

void TMTexLibRegistryInit(int maxLibs)
{
    TMRegistryAlloc(&lbl_8039B53C, maxLibs, 1, 1);
}

void TMTexLibRegistryShutdown(void)
{
    TMRegistryFree(&lbl_8039B53C);
}

void TMTexLibRegistryReset(void)
{
    TMRegistryReset(&lbl_8039B53C);
}

void TMTexLibRegister(const char *pName, TMTexLib_t *pLib)
{
    if (pLib != 0) {
        TMRegistryAddEntry(&lbl_8039B53C, pName, pLib);
    }
}

TMTexture_t *TMTexLibGetTextureByTexNode(TMTexNode_t *pNode)
{
    if (pNode != 0) {
        return &pNode->mpLib->mpTextures[pNode->mTextureIndex];
    }
    return 0;
}

TMClut_t *TMTexLibGetClutByTexNode(TMTexNode_t *pNode, int index)
{
    TMTexLib_t *pLib;

    if (pNode != 0) {
        pLib = pNode->mpLib;
        if (index < pNode->mNumCluts) {
            index += pNode->mFirstClut;
            return &pLib->mpCluts[index];
        }
    }
    return 0;
}

TMTexNode_t *TMTexLibGetTexNode(TMTexLib_t *pLib, const char *pName)
{
    if (pLib != 0) {
        return TMRegistryGetDataByName(&pLib->mRegistry, pName);
    }
    return TMRegistrySearchPath(&lbl_8039B53C, pName);
}

TMTexture_t *TMTexLibGetTexture(TMTexLib_t *pLib, const char *pName)
{
    TMTexNode_t *pNode;
    TMTexture_t *pTexture;

    pTexture = 0;
    pNode = TMTexLibGetTexNode(pLib, pName);
    if (pNode != 0) {
        pTexture = TMTexLibGetTextureByTexNode(pNode);
    }
    return pTexture;
}

TMClut_t *TMTexLibGetClut(TMTexLib_t *pLib, const char *pName, int index)
{
    TMTexNode_t *pNode;
    TMClut_t *pClut;

    pClut = 0;
    pNode = TMTexLibGetTexNode(pLib, pName);
    if (pNode != 0) {
        pClut = TMTexLibGetClutByTexNode(pNode, index);
    }
    return pClut;
}

void TMTexLibSetFilterParm(TMTexLib_t *pLib, TMTexFilterDesc_t *pDesc)
{
    int i;

    for (i = 0; i < pLib->mNumTextures; i++) {
        TMTextureSetFilterParm(&pLib->mpTextures[i], pDesc);
    }
}

void TMTexLibSetWrapParm(TMTexLib_t *pLib, TMTexWrapDesc_t *pDesc)
{
    int i;

    for (i = 0; i < pLib->mNumTextures; i++) {
        TMTextureSetWrapParm(&pLib->mpTextures[i], pDesc);
    }
}
