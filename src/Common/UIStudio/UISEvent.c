#include "UIStudio/UIStudio.h"
#include "unresolved.h"

/* Returns the index of the rate function RateFncID owned by pControlInfo,
   or NumRateFncs when there is none. */
Uint32 UISFindRateFnc(UISInfoT *pInfo, UISControlInfoT *pControlInfo, Uint32 RateFncID)
{
    Uint32 RateFnc;
    UISRateFncT *pRateFnc;

    for (RateFnc = 0; RateFnc < pInfo->NumRateFncs; RateFnc++) {
        pRateFnc = &pInfo->RateFncs[RateFnc];
        if (pRateFnc->RateFncID == RateFncID && pRateFnc->pControlInfo == pControlInfo) {
            break;
        }
    }
    return RateFnc;
}

/* Loads (or replaces) a rate function that moves the value selected by animType
   to targValue over MSDur (in the time unit of pInfo->MSPerTick). */
void UISLoadAdvRateFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlInfoT *pControlInfo,
                       UISControlInfoT *pSubControlInfo, Uint32 RateFncID, Uint8 *pEndFnc,
                       Uint8 *pAcelFnc, Uint32 MSDur, Float32 targValue, Uint32 animType)
{
    Uint32 RateFnc;
    UISRateFncT *pRateFnc;

    if (pScreen->bWaitingToBeUnloaded) {
        RuntimeErrorFnc(0, __FILE__, 97,
                        "Attempting to load a rate function while it's screen is being unloaded.");
        return;
    }
    RateFnc = UISFindRateFnc(pInfo, pControlInfo, RateFncID);
    if (RateFnc == pInfo->NumRateFncs) {
        pInfo->NumRateFncs++;
    }
    pRateFnc = &pInfo->RateFncs[RateFnc];
    pRateFnc->AnimationData.pSubControlInfo = pSubControlInfo;
    pRateFnc->pControlInfo = pControlInfo;
    pRateFnc->pScreen = pScreen;
    pRateFnc->RateFncID = RateFncID;
    pRateFnc->pFnc = pAcelFnc;
    pRateFnc->MSRate = pInfo->MSPerTick;
    pRateFnc->MSCount = 0;
    pRateFnc->MSLastCount = 0;
    pRateFnc->State = UISRATE_LOAD;
    pRateFnc->AnimationData.iType = animType;
    pRateFnc->AnimationData.fEndValue = targValue;
    pRateFnc->AnimationData.pEndFnc = pEndFnc;
    pRateFnc->AnimationData.fStepValue =
        (targValue - *UISGetActionPtrValue(pRateFnc->AnimationData.iType,
                                           pRateFnc->AnimationData.pSubControlInfo)) /
        ((Float32)MSDur / (Float32)pInfo->MSPerTick);
}

/* Loads (or replaces) a rate function that runs pFnc at a period derived from MSRate. */
void UISLoadRateFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlInfoT *pControlInfo,
                    Uint32 RateFncID, Uint8 *pFnc, Uint32 MSRate)
{
    Uint32 RateFnc;
    UISRateFncT *pRateFnc;

    if (pScreen->bWaitingToBeUnloaded) {
        RuntimeErrorFnc(0, __FILE__, 138,
                        "Attempting to load a rate function while it's screen is being unloaded.");
        return;
    }
    RateFnc = UISFindRateFnc(pInfo, pControlInfo, RateFncID);
    if (RateFnc == pInfo->NumRateFncs) {
        pInfo->NumRateFncs++;
    }
    pRateFnc = &pInfo->RateFncs[RateFnc];
    pRateFnc->pControlInfo = pControlInfo;
    pRateFnc->RateFncID = RateFncID;
    pRateFnc->pFnc = pFnc;
    switch (fn_801CE1E8()) {
    case 1:
        pRateFnc->MSRate = MSRate * 60 / 50;
        break;
    case 0:
    default:
        pRateFnc->MSRate = MSRate;
        break;
    }
    pRateFnc->MSCount = 0;
    pRateFnc->MSLastCount = 0;
    pRateFnc->pScreen = pScreen;
    pRateFnc->State = UISRATE_LOAD;
    pRateFnc->AnimationData.iType = 0;
    pRateFnc->AnimationData.fEndValue = 0.0f;
    pRateFnc->AnimationData.pEndFnc = NULL;
}

/* Marks a rate function to be removed by UISRemoveUnNessaryRateFncs. */
void UISUnloadRateFnc(UISInfoT *pInfo, UISControlInfoT *pControlInfo, Uint32 RateFncID)
{
    Uint32 RateFnc;

    RateFnc = UISFindRateFnc(pInfo, pControlInfo, RateFncID);
    if (RateFnc < pInfo->NumRateFncs) {
        pInfo->RateFncs[RateFnc].State = UISRATE_UNLOAD;
    }
}

/* Removes unloaded rate functions, closing up the table, and activates newly loaded ones. */
void UISRemoveUnNessaryRateFncs(UISInfoT *pInfo)
{
    Int32 nRateFnc;
    Int32 nSlideFnc;

    nRateFnc = pInfo->NumRateFncs;
    while (nRateFnc-- != 0) {
        if (pInfo->RateFncs[nRateFnc].State == UISRATE_UNLOAD) {
            pInfo->NumRateFncs--;
            for (nSlideFnc = nRateFnc; nSlideFnc < pInfo->NumRateFncs; nSlideFnc++) {
                fn_801C2030(&pInfo->RateFncs[nSlideFnc], &pInfo->RateFncs[nSlideFnc + 1],
                            sizeof(UISRateFncT));
            }
        } else if (pInfo->RateFncs[nRateFnc].State == UISRATE_LOAD) {
            pInfo->RateFncs[nRateFnc].State = UISRATE_ACTIVE;
        }
    }
}
