/* TM renderer shader libraries: named collections of shaders, registered by library name and
   looked up by "library/shader" path, plus the null shader used when none is given. */

#include "engine/tmlib.h"

/* The node pool the shaders are allocated from. */
static Pool_801C750C *_TMShaderLib_pNodes = 0;

/* The registered shader libraries. */
static TMRegistry_t _TMShaderLib_Registry;

/* The shader used when a lookup names none. */
static TMShader_t *_TMShaderLib_pNullShader;

static TMShader_t *_TMShaderLibAddShader(TMRegistry_t *pLib, TMShaderDef_t *pDef)
{
    TMShader_t *pShader;

    pShader = DSNewNode(_TMShaderLib_pNodes);
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
        DSDelNode(_TMShaderLib_pNodes, pShader);
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
    TMRegistryAlloc(&_TMShaderLib_Registry, maxLibs, 1, 1);
    _TMShaderLib_pNodes = DSNewNodeHandler(1, maxShaders, sizeof(TMShader_t), 0);
}

void TMShaderLibRegistryShutdown(void)
{
    TMRegistryFree(&_TMShaderLib_Registry);
    DSDelNodeHandler(_TMShaderLib_pNodes);
    _TMShaderLib_pNodes = 0;
}

void TMShaderLibRegister(const char *pName, TMRegistry_t *pLib)
{
    TMRegistryAddEntry(&_TMShaderLib_Registry, pName, pLib);
}

void TMShaderLibUnregister(const char *pName)
{
    TMRegistryRemoveEntryByName(&_TMShaderLib_Registry, pName);
}

TMShader_t *TMShaderLibGetShader(const char *pPath)
{
    if (pPath == 0) {
        return _TMShaderLib_pNullShader;
    }
    return TMRegistrySearchPath(&_TMShaderLib_Registry, pPath);
}

void TMShaderLibSetNullShader(TMShader_t *pShader)
{
    _TMShaderLib_pNullShader = pShader;
}
