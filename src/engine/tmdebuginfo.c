/* Debug-info chunks of loaded models: pointer relocation of their name and string tables. */

#include "engine/tmlib.h"

void TMDebugInfoRelocateChunk(TMDebugInfo_t *pInfo, void *pOldBase, void *pNewBase)
{
    if (pInfo->mNumNames != 0 && pInfo->mpNames != 0) {
        pInfo->mpNames = fn_8020EB94(pInfo, 0, pInfo->mpNames);
    } else {
        pInfo->mNumNames = 0;
        pInfo->mpNames = 0;
    }
    if (pInfo->mNumStrings != 0 && pInfo->mpStrings != 0) {
        pInfo->mpStrings = fn_8020EB94(pInfo, pOldBase, pInfo->mpStrings);
    } else {
        pInfo->mNumStrings = 0;
        pInfo->mpStrings = 0;
    }
}
