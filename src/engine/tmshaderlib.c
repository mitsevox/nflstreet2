/* TM renderer shader libraries: named collections of shaders, registered by library name and
   looked up by "library/shader" path, plus the null shader used when none is given. */

#include "engine/tmlib.h"

extern Pool_801C750C *lbl_803EBF10;
extern TMRegistry_t lbl_8039B52C;
extern TMShader_t *lbl_803ECFD0;

static TMShader_t *_TMShaderLibAddShader(TMRegistry_t *pLib, TMShaderDef_t *pDef)
{
    TMShader_t *pShader;

    pShader = DSNewNode(lbl_803EBF10);
    TMShaderNew(pShader, pDef);
    TMRegistryAddEntry(pLib, pDef->mName, pShader);
    return pShader;
}

void TMShaderLibAlloc(TMRegistry_t *pLib, int maxShaders)
{
    TMRegistryAlloc(pLib, maxShaders, 1, 0);
}

void TMShaderLibFree(TMRegistry_t *pLib)
{
    TMShader_t *pShader;
    int count;
    int i;

    count = TMRegistryGetNumEntries(pLib);
    for (i = 0; i < count; i++) {
        pShader = TMRegistryGetDataByIndex(pLib, i);
        TMShaderDelete(pShader);
        DSDelNode(lbl_803EBF10, pShader);
    }
    TMRegistryFree(pLib);
}

TMShader_t *TMShaderLibAddShader(TMRegistry_t *pLib, TMShaderDef_t *pDef, TMShaderFunc_t bindFunc)
{
    TMShader_t *pShader;

    pShader = _TMShaderLibAddShader(pLib, pDef);
    TMShaderSetBindFunc(pShader, bindFunc);
    return pShader;
}

void TMShaderLibRegistryInit(int maxShaders, int maxLibs)
{
    TMRegistryAlloc(&lbl_8039B52C, maxLibs, 1, 1);
    lbl_803EBF10 = DSNewNodeHandler(1, maxShaders, sizeof(TMShader_t), 0);
}

void TMShaderLibRegistryShutdown(void)
{
    TMRegistryFree(&lbl_8039B52C);
    DSDelNodeHandler(lbl_803EBF10);
    lbl_803EBF10 = 0;
}

void TMShaderLibRegister(const char *pName, TMRegistry_t *pLib)
{
    TMRegistryAddEntry(&lbl_8039B52C, pName, pLib);
}

void TMShaderLibUnregister(const char *pName)
{
    TMRegistryRemoveEntryByName(&lbl_8039B52C, pName);
}

TMShader_t *TMShaderLibGetShader(const char *pPath)
{
    if (pPath == 0) {
        return lbl_803ECFD0;
    }
    return TMRegistrySearchPath(&lbl_8039B52C, pPath);
}

void TMShaderLibSetNullShader(TMShader_t *pShader)
{
    lbl_803ECFD0 = pShader;
}
