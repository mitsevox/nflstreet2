/* UIStudio.c (EA's name, from its __FILE__ string): the core of EA's UI Studio library, the
   runtime behind every front-end and in-game menu screen. It loads, activates and unloads the
   screens of the UIStudio group files, runs the scripts and events sent to them, ticks their
   rate functions and draws their objects.

   Partial source (0x802176E8-0x8021A068). Functions of this file without a body here are
   declared only; their original bytes are not replaced. */

#include "UIStudio/UIStudio.h"

Int32 fn_802178E4(UISScreenT *pScreen, void **ppTarget, Int32 Type, void *pContext);
void fn_80217A7C(UISInfoT *pInfo, UISScreenT *pScreen, Int32 Value, Int32 Type, void *pChange,
                 Int32 bFirstPass);
Int32 fn_802180A0(UISInfoT *pInfo, UISScreenT *pScreen, UISRunStateT *pStackInfo, Uint32 Control,
                  Int32 Channel, Int32 EventID, Int32 nParam, Int32 *pParam, Uint8 *pbActive);
Int32 fn_8021C654(UISControlT *pControl, Uint32 ID);
Int32 fn_8021C6A8(UISControlT *pControl, Int32 Flags, Uint32 ID);
Int32 fn_8021C760(UISInfoT *pInfo, UISScreenT *pScreen, UISControlStateT *pControlState,
                  UISRunStateT *pState, Int32 Value, Uint32 NumArgs, Int32 *pArgs,
                  Uint32 NumExtra, Int32 *pExtra, Uint8 bPushArg, Int32 Arg, Int32 *pResult);
Int32 fn_8021861C(UISScreenDataT *pNewBase);
Int32 fn_80218DDC(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bModal, Uint8 Count,
                  Int32 *pArgs);
void fn_8021956C(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bProcess);
Int32 fn_80218D20(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Arg3, Int32 Arg4,
                  Int32 Count, Int32 *pArgs);
void fn_80217D30(UISInfoT *pInfo, UISScreenT *pScreen, Uint32 Control, Int32 FncID);
void fn_80218364(UISInfoT *pInfo, Uint32 MS);
UISColorVectorT *fn_8021CA3C(void);
UISColorVectorT *fn_8021CA48(void);
void fn_8021CA54(Float32 a, Float32 b, Float32 c, Float32 d);
void fn_8021CA70(Float32 a, Float32 b, Float32 c, Float32 d);

/* Draw-pass word cleared before each screen; its address is passed to the draw functions. */
static UISParamT lbl_803ECFE8;
/* Hook UISProcessEvent calls around a float event; only UISInit writes it (0). */
static void (*_UIStudio_pEventHook)(void);
/* Tested before the next screen is activated after an unload. */
static Uint8 _UIS_ShuttingDown = 0;

Int32 fn_8021A45C(UISInfoT *pInfo, Int32 *pFrame, UISRunStateT *pState, UISScreenT *pScreen,
                  UISControlStateT *pControlState);
Int32 fn_8021D9D4(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID);
void *memmove(void *dst, const void *src, Uint32 n);

/* Runs the screen's static objects that have not run yet, then every action
   function under control Control and the controls it links to. */
void fn_802176E8(UISInfoT *pInfo, UISScreenT *pScreen, Uint32 Control, Int32 FncID)
{
    UISControlT *pControl;
    UISObjectRefT *pRef;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    void *pObject;
    Uint32 Object;
    Uint32 Node;
    Int16 bInit;

    if (pScreen->pData != 0) {
        pControl = &pScreen->pData->pControls[Control];
        bInit = FncID == -1;
        for (Object = 0; Object < pScreen->pData->NumObjects; Object++) {
            pRef = &pScreen->pData->pObjects[Object];
            if (pRef->State == 0) {
                if (pRef->ID < pInfo->NumActionFncs && pInfo->ActionFncs[pRef->ID].pFnc != 0) {
                    pObject = pRef->pOffset != 0 ? (Uint8 *)pScreen->pData + *pRef->pOffset : 0;
                    pInfo->ActionFncs[pRef->ID].pFnc(pObject, FncID, 0, 0, 0);
                }
                pRef->State = 1;
            }
        }
        for (Node = 0; Node < pControl->NumNodes; Node++) {
            pNode = pControl->ppNodes[Node];
            for (Object = 0; Object < pNode->NumEntries; Object++) {
                pEntry = &pNode->pEntries[Object];
                if (pEntry->ID == 0xFFFF) {
                    fn_802176E8(pInfo, pScreen, pEntry->Value, FncID);
                } else if (pEntry->ID < pInfo->NumActionFncs &&
                           pInfo->ActionFncs[pEntry->ID].pFnc != 0) {
                    pObject = pEntry->Value != 0
                                  ? (Uint8 *)pScreen->pData + *(Int32 *)pEntry->Value
                                  : 0;
                    pInfo->ActionFncs[pEntry->ID].pFnc(pObject, FncID, 0, 0, 0);
                    pEntry->State = bInit;
                }
            }
        }
    }
}

/* Looks under a control (Type 8) or node (Type 7) for the owner of the state
   block *ppTarget names, stores the owner in *ppTarget and returns whether it is
   shown; returns -1 when it is not found. */
Int32 fn_802178E4(UISScreenT *pScreen, void **ppTarget, Int32 Type, void *pContext)
{
    UISControlT *pControl;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    Uint32 Item;
    Uint32 NumItems;
    Int32 Result;

    if (ppTarget != 0 && pContext != 0 && pScreen != 0) {
        switch (Type) {
        case 8:
            pControl = pContext;
            if (pControl->pState == *ppTarget) {
                *ppTarget = pControl;
                return pControl->pState->pOwner != 0;
            }
            if (pControl->pState != 0 && pControl->pState->pOwner != 0) {
                NumItems = pControl->NumNodes;
                for (Item = 0; Item < NumItems; Item++) {
                    Result = fn_802178E4(pScreen, ppTarget, 7,
                                         ((UISControlT *)pContext)->ppNodes[Item]);
                    if (Result != -1) {
                        return Result;
                    }
                }
            }
            break;
        case 7:
            pNode = pContext;
            if (pNode->pFlag == *ppTarget) {
                *ppTarget = pNode;
                return *pNode->pFlag != 0;
            }
            if (pNode->pFlag != 0 && *pNode->pFlag != 0) {
                NumItems = pNode->NumEntries;
                for (Item = 0; Item < NumItems; Item++) {
                    pEntry = &pNode->pEntries[Item];
                    if (pEntry->ID == 0xFFFF) {
                        Result = fn_802178E4(pScreen, ppTarget, 8,
                                             &pScreen->pData->pControls[pEntry->Value]);
                        if (Result != -1) {
                            return Result;
                        }
                    }
                }
            }
            break;
        }
    }
    return -1;
}

/* Sends message -4 with the new visibility Value to every action function
   under a control (Type 8) or node (Type 7); without bFirstPass, hidden
   controls and nodes are skipped. */
void fn_80217A7C(UISInfoT *pInfo, UISScreenT *pScreen, Int32 Value, Int32 Type, void *pChange,
                 Int32 bFirstPass)
{
    UISControlT *pControl;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    void *pObject;
    Uint32 Item;
    Uint32 NumItems;

    if (pInfo != 0 && pScreen != 0 && pChange != 0) {
        switch (Type) {
        case 8:
            pControl = pChange;
            if (pControl->pState != 0 && (bFirstPass || pControl->pState->pOwner != 0)) {
                NumItems = pControl->NumNodes;
                for (Item = 0; Item < NumItems; Item++) {
                    fn_80217A7C(pInfo, pScreen, Value, 7, ((UISControlT *)pChange)->ppNodes[Item],
                                0);
                }
            }
            break;
        case 7:
            pNode = pChange;
            if (pNode->pFlag != 0 && (bFirstPass || *pNode->pFlag != 0)) {
                NumItems = pNode->NumEntries;
                for (Item = 0; Item < NumItems; Item++) {
                    pEntry = &pNode->pEntries[Item];
                    if (pEntry->ID == 0xFFFF) {
                        fn_80217A7C(pInfo, pScreen, Value, 8,
                                    &pScreen->pData->pControls[pEntry->Value], 0);
                    } else if (pEntry->ID < pInfo->NumActionFncs &&
                               pInfo->ActionFncs[pEntry->ID].pFnc != 0) {
                        pObject = pEntry->Value != 0
                                      ? (Uint8 *)pScreen->pData + *(Int32 *)pEntry->Value
                                      : 0;
                        pInfo->ActionFncs[pEntry->ID].pFnc(pObject, -4, 1, &Value, 0);
                    }
                }
            }
            break;
        }
    }
}

/* Calls the control callback for control Control of pScreen and recurses
   into every control linked from its live nodes. */
void fn_80217C38(UISInfoT *pInfo, Int32 Action, UISScreenT *pScreen, Int32 Control)
{
    UISControlT *pControl;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    Uint32 Node;
    Uint32 Entry;

    if (pScreen->pData != 0) {
        pControl = &pScreen->pData->pControls[Control];
        pInfo->pControlFnc(Action, (Uint8 *)pControl->pState + 8);
        for (Node = 0; Node < pControl->NumNodes; Node++) {
            pNode = pControl->ppNodes[Node];
            if (*pNode->pFlag != 0) {
                for (Entry = 0; Entry < pNode->NumEntries; Entry++) {
                    pEntry = &pNode->pEntries[Entry];
                    if (pEntry->ID == 0xFFFF) {
                        fn_80217C38(pInfo, Action, pScreen, pEntry->Value);
                    }
                }
            }
        }
    }
}

/* Draws control Control of pScreen: runs the screen's static objects, then, when
   the control is shown, the draw functions of its live nodes and the controls
   they link to, with its colour factors folded into the current ones. */
void fn_80217D30(UISInfoT *pInfo, UISScreenT *pScreen, Uint32 Control, Int32 FncID)
{
    UISColorVectorT OldMultipler = {1.0f, 1.0f, 1.0f, 1.0f};
    UISColorVectorT OldAdditive = {0.0f};
    UISColorVectorT *pCurMultipler;
    UISColorVectorT *pCurAdditive;
    UISControlT *pControl;
    UISObjectRefT *pRef;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    void *pObject;
    Uint32 Node;

    if (pScreen->pData != 0 && pScreen->bWaitingToBeUnloaded == 0) {
        pControl = &pScreen->pData->pControls[Control];
        for (Control = 0; Control < pScreen->pData->NumObjects; Control++) {
            pRef = &pScreen->pData->pObjects[Control];
            if (pRef->ID < pInfo->NumActionFncs && pInfo->ActionFncs[pRef->ID].pFnc != 0) {
                pObject = pRef->pOffset != 0 ? (Uint8 *)pScreen->pData + *pRef->pOffset : 0;
                pInfo->ActionFncs[pRef->ID].pFnc(pObject, FncID, 0, 0, 0);
            }
        }
        if (pControl->pState->pOwner != 0) {
            OldMultipler = *fn_8021CA3C();
            OldAdditive = *fn_8021CA48();
            pCurMultipler = &pControl->pState->MultiplerFactor;
            pCurAdditive = &pControl->pState->AdditiveFactor;
            fn_8021CA54(OldMultipler.r * pCurMultipler->r, OldMultipler.g * pCurMultipler->g,
                        OldMultipler.b * pCurMultipler->b, OldMultipler.a * pCurMultipler->a);
            fn_8021CA70(OldAdditive.r + pCurAdditive->r, OldAdditive.g + pCurAdditive->g,
                        OldAdditive.b + pCurAdditive->b, OldAdditive.a + pCurAdditive->a);
            pInfo->pControlFnc(1, (Uint8 *)pControl->pState + 8);
            for (Node = 0; Node < pControl->NumNodes; Node++) {
                pNode = pControl->ppNodes[Node];
                if (*pNode->pFlag != 0) {
                    for (Control = 0; Control < pNode->NumEntries; Control++) {
                        pEntry = &pNode->pEntries[Control];
                        if (pEntry->ID == 0xFFFF) {
                            fn_80217D30(pInfo, pScreen, pEntry->Value, FncID);
                        } else if (pEntry->State != 0 && pEntry->ID < pInfo->NumActionFncs &&
                                   pInfo->ActionFncs[pEntry->ID].pFnc != 0) {
                            pObject = pEntry->Value != 0
                                          ? (Uint8 *)pScreen->pData + *(Int32 *)pEntry->Value
                                          : 0;
                            pInfo->ActionFncs[pEntry->ID].pFnc(pObject, FncID, 0, &lbl_803ECFE8,
                                                               0);
                        }
                    }
                }
            }
            fn_8021CA54(OldMultipler.r, OldMultipler.g, OldMultipler.b, OldMultipler.a);
            fn_8021CA70(OldAdditive.r, OldAdditive.g, OldAdditive.b, OldAdditive.a);
            pInfo->pControlFnc(2, (Uint8 *)pControl->pState + 8);
        }
    }
}

/* Sends event EventID to control Control of pScreen, first through the controls
   it links to. A control takes events only while it is enabled and can handle
   messages, except the studio's own events (-2 to -5, -8 to -11). Returns 2 as
   soon as a linked handler returns 2; *pbActive gets the control's enable byte. */
Int32 fn_802180A0(UISInfoT *pInfo, UISScreenT *pScreen, UISRunStateT *pStackInfo, Uint32 Control,
                  Int32 Channel, Int32 EventID, Int32 nParam, Int32 *pParam, Uint8 *pbActive)
{
    UISControlT *pControl;
    UISControlItemT *pMap;
    Int32 rVal;
    Uint32 Map;
    Int32 pcEvent;
    signed char bLocalProcess;

    rVal = 0;
    if (pScreen->pData == 0 || Control >= pScreen->pData->NumControls) {
        return 0;
    }
    pControl = &pScreen->pData->pControls[Control];
    if ((pControl->pState->bEnabled != 0 && pControl->pState->bCanHandleMessages != 0) ||
        EventID == -10 || EventID == -9 || EventID == -2 || EventID == -3 || EventID == -8 ||
        EventID == -4 || EventID == -5 || EventID == -11) {
        for (Map = 0; Map < pControl->NumItems; Map++) {
            pMap = &pControl->pItems[Map];
            if (pMap->ID == 0xFFFF) {
                bLocalProcess = 0;
                rVal = fn_802180A0(pInfo, pScreen, pStackInfo, pMap->Value, Channel, EventID, nParam,
                                   pParam, (Uint8 *)&bLocalProcess);
                if (bLocalProcess == 1) {
                    pcEvent = fn_8021C6A8(pControl, (Uint16)pMap->Value, EventID);
                    if (pcEvent != 0 &&
                        fn_8021C760(pInfo, pScreen, pControl->pState, pStackInfo, pcEvent, nParam,
                                    pParam, 0, 0, 1, Channel, 0) == 2) {
                        return 2;
                    }
                }
            }
        }
        fn_8021DDF4(pInfo, 1);
        pcEvent = fn_8021C654(pControl, EventID);
        if ((EventID == -6 || EventID == -7) && (Int32)pControl->pState != pParam[2]) {
            pcEvent = 0;
        }
        if (pcEvent != 0) {
            rVal = fn_8021C760(pInfo, pScreen, pControl->pState, pStackInfo, pcEvent, nParam, pParam,
                               0, 0, 1, Channel, 0);
        }
    }
    *pbActive = pControl->pState->bEnabled;
    return rVal;
}

/* Marks every rate function of pScreen for unloading and removes them. */
void fn_802182E4(UISInfoT *pInfo, UISScreenT *pScreen)
{
    Uint32 RateFnc;
    Uint32 NumRateFncs;
    UISRateFncT *pRateFnc;

    pInfo->Flags |= 4;
    NumRateFncs = pInfo->NumRateFncs;
    for (RateFnc = 0; RateFnc < NumRateFncs; RateFnc++) {
        pRateFnc = &pInfo->RateFncs[RateFnc];
        if (pRateFnc->pScreen == pScreen) {
            pRateFnc->State = UISRATE_UNLOAD;
        }
    }
    pInfo->Flags &= ~4;
    UISRemoveUnNessaryRateFncs(pInfo);
}

/* Runs the rate functions for MS elapsed milliseconds. Each running one steps once
   per MSRate: its step script (if any) gives the step's scale, the driven value
   moves by fStepValue times it, and once it reaches fEndValue the rate function
   finishes and its end script (or the first control's event -14 script) runs. */
void fn_80218364(UISInfoT *pInfo, Uint32 MS)
{
    UISRateFncT *pRateFnc;
    Uint32 RateFnc;
    Uint32 NumRateFncs;
    UISScreenT *pScreen;
    UISRunStateT *pStackInfo;
    Float32 fAcel;
    Int32 iElapse;
    Float32 ReturnParam;
    Int32 RateParams[3];
    Uint32 nParam;
    Float32 *pfModVal;
    Float32 newVal;
    Int32 pEndRateFncPC;

    fAcel = 0.0f;
    pStackInfo = &pInfo->RateStack;
    UISRemoveUnNessaryRateFncs(pInfo);
    pInfo->Flags |= 4;
    NumRateFncs = pInfo->NumRateFncs;
    for (RateFnc = 0; RateFnc < NumRateFncs; RateFnc++) {
        pRateFnc = &pInfo->RateFncs[RateFnc];
        if (pRateFnc->State != UISRATE_ACTIVE) {
            continue;
        }
        pScreen = pRateFnc->pScreen;
        if (pRateFnc->MSRate == 0) {
            continue;
        }
        pRateFnc->MSCount += MS;
        iElapse = pRateFnc->MSCount - pRateFnc->MSLastCount;
        while (iElapse >= (Int32)pRateFnc->MSRate) {
            iElapse -= pRateFnc->MSRate;
            pRateFnc->MSLastCount += pRateFnc->MSRate;
            if (pRateFnc->pFnc != 0) {
                if (pRateFnc->State != UISRATE_ACTIVE) {
                    break;
                }
                ReturnParam = 1.0f;
                RateParams[0] = pRateFnc->RateFncID;
                RateParams[1] = pRateFnc->MSLastCount;
                if (pRateFnc->AnimationData.iType == 0) {
                    RateParams[2] = pRateFnc->MSRate;
                    nParam = 3;
                } else {
                    nParam = 2;
                }
                fn_8021C760(pInfo, pScreen, (UISControlStateT *)pRateFnc->pControlInfo, pStackInfo,
                            (Int32)pRateFnc->pFnc, nParam, RateParams, 0, 0, 0, -1,
                            (Int32 *)&ReturnParam);
                fAcel = ReturnParam;
            } else {
                fAcel = 1.0f;
            }
            if (pRateFnc->AnimationData.iType != 0) {
                pfModVal = UISGetActionPtrValue(pRateFnc->AnimationData.iType,
                                                pRateFnc->AnimationData.pSubControlInfo);
                if (fAcel < 0.0f) {
                    fAcel = 1.0f;
                }
                newVal = pRateFnc->AnimationData.fStepValue * fAcel + *pfModVal;
                if ((pRateFnc->AnimationData.fStepValue > 0.0f &&
                     newVal < pRateFnc->AnimationData.fEndValue) ||
                    (pRateFnc->AnimationData.fStepValue < 0.0f &&
                     newVal > pRateFnc->AnimationData.fEndValue)) {
                    *pfModVal = newVal;
                } else {
                    *pfModVal = pRateFnc->AnimationData.fEndValue;
                    pRateFnc->State = UISRATE_UNLOAD;
                    if (pRateFnc->AnimationData.pEndFnc != 0) {
                        RateParams[0] = pRateFnc->RateFncID;
                        fn_8021C760(pInfo, pScreen, (UISControlStateT *)pRateFnc->pControlInfo,
                                    pStackInfo, (Int32)pRateFnc->AnimationData.pEndFnc, 1,
                                    RateParams, 0, 0, 0, -1, 0);
                    } else {
                        pEndRateFncPC = fn_8021C654(pScreen->pData->pControls, -14);
                        if (pEndRateFncPC != 0) {
                            RateParams[0] = pRateFnc->RateFncID;
                            fn_8021C760(pInfo, pScreen, (UISControlStateT *)pRateFnc->pControlInfo,
                                        pStackInfo, pEndRateFncPC, 1, RateParams, 0, 0, 0, -1, 0);
                        }
                    }
                }
            }
        }
    }
    pInfo->Flags &= ~4;
    UISRemoveUnNessaryRateFncs(pInfo);
}

/* Turns the file offsets of a loaded screen file into pointers, the first time
   the file is seen; string links become string record pointers (0 when out of
   range). Returns 1, or -1 when the file was already patched. */
Int32 fn_8021861C(UISScreenDataT *pNewBase)
{
    Uint32 Control;
    UISControlT *pControl;
    Uint32 Node;
    UISNodeT *pNode;
    Uint32 Obj;
    UISNodeEntryT *pObj;
    Uint32 Map;
    UISControlItemT *pMap;
    Uint32 Str;
    Uint32 Patch;
    Uint32 *pPatch;
    UISObjectRefT *pRef;

    if ((Uint32)pNewBase->pControls < (Uint32)pNewBase) {
        pNewBase->pControls = (UISControlT *)((Uint32)pNewBase + (Uint32)pNewBase->pControls);
        for (Control = 0; Control < pNewBase->NumControls; Control++) {
            pControl = &pNewBase->pControls[Control];
            pControl->pState =
                (UISControlStateT *)((Uint32)pNewBase + (Uint32)pControl->pState);
            pControl->ppNodes = (UISNodeT **)((Uint32)pNewBase + (Uint32)pControl->ppNodes);
            Node = pControl->NumNodes;
            while (Node-- != 0) {
                pControl->ppNodes[Node] =
                    (UISNodeT *)((Uint32)pNewBase + (Uint32)pControl->ppNodes[Node]);
                pNode = pControl->ppNodes[Node];
                pNode->pFlag = (Int32 *)((Uint32)pNewBase + (Uint32)pNode->pFlag);
                pNode->pEntries = (UISNodeEntryT *)((Uint32)pNewBase + (Uint32)pNode->pEntries);
                Obj = pNode->NumEntries;
                while (Obj-- != 0) {
                    pObj = &pNode->pEntries[Obj];
                    if (pObj->ID != 0xFFFF) {
                        pObj->State = 0;
                        pObj->Value = (Uint32)pNewBase + pObj->Value;
                    }
                }
            }
            pControl->pItems = (UISControlItemT *)((Uint32)pNewBase + (Uint32)pControl->pItems);
            Map = pControl->NumItems;
            while (Map-- != 0) {
                pMap = &pControl->pItems[Map];
                if (pMap->ID != 0xFFFF) {
                    pMap->Value = (Uint32)pNewBase + pMap->Value;
                }
            }
        }
        pNewBase->pStrings = (UISStringT *)((Uint32)pNewBase + (Uint32)pNewBase->pStrings);
        Str = pNewBase->NumStrings;
        while (Str-- != 0) {
            pNewBase->pStrings[Str].pText =
                (char *)((Uint32)pNewBase + (Uint32)pNewBase->pStrings[Str].pText);
        }
        pNewBase->pStringPatchTable =
            (Uint32 *)((Uint32)pNewBase + (Uint32)pNewBase->pStringPatchTable);
        Patch = pNewBase->NumPatchStrings;
        while (Patch-- != 0) {
            pPatch = (Uint32 *)((Uint32)pNewBase + pNewBase->pStringPatchTable[Patch]);
            if (*pPatch < pNewBase->NumStrings) {
                *pPatch = (Uint32)&pNewBase->pStrings[*pPatch];
            } else {
                *pPatch = 0;
            }
        }
        pNewBase->pObjects = (UISObjectRefT *)((Uint32)pNewBase + (Uint32)pNewBase->pObjects);
        Control = pNewBase->NumObjects;
        while (Control-- != 0) {
            pRef = &pNewBase->pObjects[Control];
            if (pRef->pOffset != 0) {
                pRef->pOffset = *(Int32 *)((Uint32)pNewBase + (Uint32)pRef->pOffset) != 0
                                    ? (Int32 *)((Uint32)pNewBase + (Uint32)pRef->pOffset)
                                    : 0;
            }
        }
        return 1;
    }
    return -1;
}

/* Returns the byte size of a UISInfoT with the given table capacities. */
Uint32 fn_802188A0(Uint32 NumScreens, Uint32 NumActionFncs, Uint32 NumRateFncs, Uint32 Num40,
                   Uint32 NumA, Uint32 NumB)
{
    return (NumScreens + 1) * 20 + (NumActionFncs * 4 + sizeof(UISInfoT)) +
           NumRateFncs * sizeof(UISRateFncT) + Num40 * 40 + (NumA + NumB) * 4;
}

/* Sets the studio up in the block at pInfo (fn_802188A0 bytes): the header, then
   the screen, action function, rate function and modal tables, the global
   script's screen record and the two word stacks. */
void fn_802188D4(UISInfoT *pInfo, Uint32 MaxScreens, Uint32 MaxActionFncs, Uint32 MaxRateFncs,
                 Uint32 MaxModals, Uint32 StackSize, Uint32 RateStackSize, Uint32 MSPerTick)
{
    Uint32 Offset;

    Offset = sizeof(UISInfoT) + MaxScreens * sizeof(UISScreenT);
    pInfo->unk_00 = UIS_MAGIC;
    pInfo->Flags = 0;
    pInfo->bShuttingDown = 0;
    pInfo->MaxScreens = MaxScreens;
    pInfo->NumScreens = 0;
    pInfo->Screens = (UISScreenT *)(pInfo + 1);
    pInfo->MaxActionFncs = MaxActionFncs;
    pInfo->NumActionFncs = 0;
    pInfo->ActionFncs = (UISPluginT *)((Uint8 *)pInfo + Offset);
    Offset += MaxActionFncs * sizeof(UISPluginT);
    pInfo->MaxRateFncs = MaxRateFncs;
    pInfo->NumRateFncs = 0;
    pInfo->RateFncs = (UISRateFncT *)((Uint8 *)pInfo + Offset);
    Offset += MaxRateFncs * sizeof(UISRateFncT);
    pInfo->MaxScreenRefs = MaxModals;
    pInfo->NumScreenRefs = 0;
    pInfo->ScreenRefs = (UISScreenRefT *)((Uint8 *)pInfo + Offset);
    Offset += MaxModals * sizeof(UISScreenRefT);
    pInfo->pCursor = (UISCursorT *)((Uint8 *)pInfo + Offset);
    Offset += sizeof(UISScreenT);
    pInfo->pCursor->bWaitingToBeUnloaded = 0;
    pInfo->pCursor->unk_00 = -1;
    pInfo->pCursor->GroupID = 0xFFFF;
    pInfo->pCursor->ScreenID = 0xFFFF;
    pInfo->pCursor->ParentGroupID = 0xFFFF;
    pInfo->pCursor->ParentScreenID = 0xFFFF;
    pInfo->pCursor->pTarget = 0;
    pInfo->RunState.pStackStart = pInfo->RunState.pStackCurrent = pInfo->RunState.pTop =
        (Int32 *)((Uint8 *)pInfo + Offset);
    pInfo->RunState.pStackEnd = pInfo->RunState.pStackCurrent + StackSize;
    pInfo->ActionStack.pStart = pInfo->RunState.pStackEnd - 1;
    pInfo->ActionStack.pTop = pInfo->RunState.pStackEnd - 1;
    pInfo->ppStackCurrent = &pInfo->RunState.pStackCurrent;
    Offset += StackSize * sizeof(Int32);
    pInfo->RateStack.pStackStart = pInfo->RateStack.pStackCurrent = pInfo->RateStack.pTop =
        (Int32 *)((Uint8 *)pInfo + Offset);
    pInfo->RateStack.pStackEnd = pInfo->RateStack.pStackCurrent + RateStackSize;
    pInfo->MSPerTick = MSPerTick;
    pInfo->ActiveScreen = -1;
    pInfo->pMessageFnc = 0;
    pInfo->pControlFnc = 0;
    pInfo->pCallback20 = 0;
    pInfo->pLoadFnc = 0;
    pInfo->pUnloadFnc = 0;
    pInfo->pShutdownScreenFnc = 0;
    pInfo->pScreenActivatedFnc = 0;
    pInfo->pCallback28 = 0;
    pInfo->pCallback2C = 0;
    pInfo->pCallback30 = 0;
    pInfo->pCallback34 = 0;
    pInfo->pCallback38 = 0;
    _UIStudio_pEventHook = 0;
}

/* Unloads every loaded screen, last first. */
void fn_80218A34(UISInfoT *pInfo)
{
    Int32 Screen;
    UISScreenT *pScreen;

    pInfo->bShuttingDown = 1;
    for (Screen = pInfo->NumScreens - 1; Screen >= 0; Screen--) {
        pScreen = &pInfo->Screens[Screen];
        fn_8021956C(pInfo, pScreen->GroupID, pScreen->ScreenID, 1);
    }
    pInfo->unk_00 = 0;
    pInfo->bShuttingDown = 0;
}

void fn_80218AA8(UISInfoT *pInfo, void *pMessageFnc)
{
    pInfo->pMessageFnc = pMessageFnc;
}

void fn_80218AB0(UISInfoT *pInfo, UISResLoadFncT *pLoadFnc, UISResUnloadFncT *pUnloadFnc)
{
    pInfo->pLoadFnc = pLoadFnc;
    pInfo->pUnloadFnc = pUnloadFnc;
}

void fn_80218ABC(UISInfoT *pInfo, UISResUnloadFncT *pShutdownScreenFnc)
{
    pInfo->pShutdownScreenFnc = pShutdownScreenFnc;
}

void fn_80218AC4(UISInfoT *pInfo, UISControlFncT *pFnc)
{
    pInfo->pControlFnc = pFnc;
}

void fn_80218ACC(UISInfoT *pInfo, UISScreenActivatedFncT *pScreenActivatedFnc)
{
    pInfo->pScreenActivatedFnc = pScreenActivatedFnc;
}

/* Installs action function pFnc at index Fnc. */
void fn_80218AD4(UISInfoT *pInfo, Int32 Fnc, UISActionFncT *pFnc)
{
    pInfo->ActionFncs[Fnc].pFnc = pFnc;
    pInfo->NumActionFncs++;
}

/* Loads a screen as the newest in the table, with ParentGroupID/ParentScreenID
   as the screen to go back to: patches its data (event -9 the first time), runs
   its initializers and transforms and sends it event -2 with the arguments. A
   loaded screen is set up again instead. Returns 0 when it was already loaded or
   the load callback gave nothing. */
Int32 fn_80218AF0(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Uint16 ParentGroupID,
                  Uint16 ParentScreenID, Uint8 Count, Int32 *pArgs)
{
    Uint32 Screen;
    void *pData;
    UISScreenT *pScreen;
    Int32 bNotLoaded;
    Uint8 Done;

    Screen = fn_8021C5EC(pInfo, GroupID, ScreenID);
    if (Screen < pInfo->NumScreens) {
        fn_80218D20(pInfo, GroupID, ScreenID, ParentGroupID, ParentScreenID, Count, pArgs);
        return 0;
    }
    pData = pInfo->pLoadFnc(GroupID, ScreenID);
    if (pData == 0) {
        return 0;
    }
    pInfo->NumScreens++;
    pScreen = &pInfo->Screens[Screen];
    pScreen->unk_00 = 0;
    pScreen->GroupID = GroupID;
    pScreen->ScreenID = ScreenID;
    pScreen->ParentGroupID = ParentGroupID;
    pScreen->ParentScreenID = ParentScreenID;
    pScreen->bWaitingToBeUnloaded = 0;
    pScreen->pData = pData;
    bNotLoaded = fn_8021861C(pData);
    fn_802176E8(pInfo, pScreen, 0, -1);
    pScreen->pData->pControls[0].pState->bEnabled = 1;
    if (bNotLoaded) {
        Done = 0;
        pInfo->Flags |= 2;
        fn_802180A0(pInfo, pScreen, &pInfo->RunState, 0, -1, -9, 0, 0, &Done);
        pInfo->Flags &= ~2;
    }
    fn_80217C38(pInfo, 0, pScreen, 0);
    Done = 0;
    if (Count == 255) {
        Count = pArgs[10];
    }
    pInfo->Flags |= 2;
    fn_802180A0(pInfo, pScreen, &pInfo->RunState, 0, -1, -2, Count, pArgs, &Done);
    pInfo->Flags &= ~2;
    return 1;
}

/* Sets the cursor target; a target that fails the 0x8021861C test is cleared.
   Returns 1 when pTarget was nonzero. */
Int32 fn_80218CB8(UISInfoT *pInfo, void *pTarget)
{
    Int32 Result;

    Result = 0;
    if (pTarget != 0) {
        if (pTarget != pInfo->pCursor->pTarget && !(Uint8)fn_8021861C(pTarget)) {
            pTarget = 0;
        }
        Result = 1;
    }
    pInfo->pCursor->pTarget = pTarget;
    return Result;
}

Int32 fn_80218D20(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Arg3, Int32 Arg4,
                  Int32 Count, Int32 *pArgs)
{
    UISScreenT *pScreen;
    Uint8 Done;

    pScreen = &pInfo->Screens[fn_8021C5EC(pInfo, GroupID, ScreenID)];
    fn_802182E4(pInfo, pScreen);
    pScreen->pData->pControls[0].pState->bEnabled = 1;
    Done = 0;
    if (Count == 255) {
        Count = (Uint8)pArgs[10];
    }
    pInfo->Flags |= 2;
    fn_802180A0(pInfo, pScreen, &pInfo->RunState, 0, -1, -2, Count, pArgs, &Done);
    pInfo->Flags &= ~2;
    return 1;
}

/* Goes to a screen: loaded (or set up again) unless it is already loaded; a
   modal record is pushed for it while modal screens are up. Returns what
   fn_80218AF0 returned. */
Int32 fn_80218DDC(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bModal, Uint8 Count,
                  Int32 *pArgs)
{
    Int16 iActiveGroup;
    Int16 iActiveScreen;
    UISScreenRefT *pModal;
    UISScreenT *pScreen;
    Int32 rVal;
    Uint32 bScreenLoaded;
    Uint32 Modal;
    Int32 Screen;

    Modal = 0;
    if (pInfo->NumScreens == 0 || pInfo->ActiveScreen == -1) {
        iActiveGroup = -1;
        iActiveScreen = -1;
    } else {
        pScreen = &pInfo->Screens[pInfo->ActiveScreen];
        iActiveGroup = pScreen->GroupID;
        iActiveScreen = pScreen->ScreenID;
    }
    bScreenLoaded = fn_8021C5EC(pInfo, GroupID, ScreenID) < pInfo->NumScreens;
    if (bScreenLoaded == 1) {
        fn_80218D20(pInfo, GroupID, ScreenID, (Uint16)iActiveGroup, (Uint16)iActiveScreen, Count,
                    pArgs);
        return 0;
    }
    if (pInfo->NumScreenRefs != 0 && !bScreenLoaded) {
        bModal = 1;
    }
    if (bModal) {
        Modal = pInfo->NumScreenRefs;
        pModal = &pInfo->ScreenRefs[Modal];
        memset(pModal, 0, sizeof(UISScreenRefT));
        pModal->GroupID = GroupID;
        pModal->ScreenID = ScreenID;
        pInfo->NumScreenRefs++;
    }
    rVal = fn_80218AF0(pInfo, GroupID, ScreenID, iActiveGroup, iActiveScreen, Count, pArgs);
    if (bModal) {
        Screen = fn_8021C5EC(pInfo, GroupID, ScreenID);
        if (Screen < pInfo->NumScreens) {
            pModal = &pInfo->ScreenRefs[Modal];
            pScreen = &pInfo->Screens[Screen];
            pModal->pControlState = pScreen->pData->pControls[0].pState;
            Screen = fn_8021C5EC(pInfo, iActiveGroup, iActiveScreen);
            if (Screen < pInfo->NumScreens) {
                pModal->pScreen = &pInfo->Screens[Screen];
            }
        } else {
            pInfo->NumScreenRefs--;
        }
    }
    return rVal;
}

Int32 fn_80218FC4(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Uint8 Arg3, Int32 *pArg4)
{
    UISThreadActionT Action;

    if (pInfo->Flags & 2) {
        Action.s.GroupID = GroupID;
        Action.s.ScreenID = ScreenID;
        Action.s.unk_04 = -1;
        Action.s.unk_06 = -1;
        fn_8021D904(GroupID, ScreenID, pInfo, 0, &Action, Arg3, pArg4);
        return 1;
    }
    return fn_80218DDC(pInfo, GroupID, ScreenID, 0, Arg3, pArg4);
}

Int32 fn_80219044(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Uint8 Arg3, Int32 *pArg4)
{
    return fn_80218DDC(pInfo, GroupID, ScreenID, 1, Arg3, pArg4);
}

/* Called before a screen is unloaded. If the last modal record names the screen,
   it is dropped: the screen it was loaded over becomes current, and its paused
   script runs on with iRetVal on the top of its stack. Returns 0 when an older
   record names or holds the screen, which cannot go yet. */
Uint8 fn_80219070(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 iRetVal)
{
    Int32 nModals;
    UISScreenRefT *pModal;
    UISScreenT *pScreen;
    UISRunStateT *pStackInfo;
    Int32 *pStackBase;

    nModals = pInfo->NumScreenRefs;
    if (nModals > 0) {
        pModal = &pInfo->ScreenRefs[nModals - 1];
        if (pModal->ScreenID == ScreenID && pModal->GroupID == GroupID) {
            pInfo->NumScreenRefs = nModals - 1;
            if (pModal->pScreen == 0) {
                pInfo->ActiveScreen = -1;
                return 1;
            }
            pInfo->ActiveScreen =
                fn_8021C5EC(pInfo, pModal->pScreen->GroupID, pModal->pScreen->ScreenID);
            if (pInfo->ActiveScreen < pInfo->NumScreens) {
                pStackBase = pModal->pRestoreStack;
                if (pStackBase != 0) {
                    pStackInfo = pModal->pRestoreState;
                    *pStackInfo = pModal->StackState;
                    pStackInfo->pTop[-1] = iRetVal;
                    if (fn_8021A45C(pInfo, pModal->pRestoreStack, pStackInfo, pModal->pScreen,
                                    pModal->pControlState) != 3) {
                        pStackInfo->pTop = pStackBase;
                    }
                }
            }
        } else {
            while (nModals-- != 0) {
                pModal = &pInfo->ScreenRefs[nModals];
                if (pModal->ScreenID == ScreenID && pModal->GroupID == GroupID) {
                    return 0;
                }
                pScreen = pModal->pScreen;
                if (pScreen != 0 && pScreen->ScreenID == ScreenID && pScreen->GroupID == GroupID) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

/* Unloads a screen. Screens that had it as their parent take its parent; it gets
   the shutdown callback, event -3 and its queued hints, its initializers and
   transforms are shut down, its rate functions are dropped, the unload callback
   frees its data and the table closes up. With no current screen left, its
   parent (or the last screen) is activated. Returns 0 when fn_80219070 says the
   screen cannot go yet. */
Int32 fn_802191F0(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 iRetVal)
{
    UISScreenT *pScreen;
    UISScreenT *pOther;
    Uint32 Screen;
    Uint16 ParentScreenID;
    Uint16 ParentGroupID;
    Uint8 Done;
    Uint32 nRateFnc;
    Uint32 Idx;

    Screen = fn_8021C5EC(pInfo, GroupID, ScreenID);
    if (Screen < pInfo->NumScreens) {
        pScreen = &pInfo->Screens[Screen];
        ParentGroupID = pScreen->ParentGroupID;
        ParentScreenID = pScreen->ParentScreenID;
        if (!fn_80219070(pInfo, GroupID, ScreenID, iRetVal)) {
            return 0;
        }
        if (Screen == pInfo->ActiveScreen) {
            pInfo->ActiveScreen = -1;
        }
        for (Idx = 0; Idx < pInfo->NumScreens; Idx++) {
            pOther = &pInfo->Screens[Idx];
            if (pOther->ParentGroupID == GroupID && pOther->ParentScreenID == ScreenID) {
                pOther->ParentGroupID = ParentGroupID;
                pOther->ParentScreenID = ParentScreenID;
            }
        }
        Done = 0;
        if (pInfo->pShutdownScreenFnc != 0) {
            pInfo->pShutdownScreenFnc(pScreen->GroupID, pScreen->ScreenID, pScreen->pData);
        }
        pInfo->Flags |= 2;
        fn_802180A0(pInfo, pScreen, &pInfo->RunState, 0, -1, -3, 0, 0, &Done);
        pInfo->Flags &= ~2;
        fn_8021D9D4(pInfo, GroupID, ScreenID);
        fn_802176E8(pInfo, pScreen, 0, -3);
        fn_80217C38(pInfo, 3, pScreen, 0);
        nRateFnc = pInfo->NumRateFncs;
        while (nRateFnc-- != 0) {
            if (pInfo->RateFncs[nRateFnc].pScreen == pScreen) {
                pInfo->RateFncs[nRateFnc].State = UISRATE_UNLOAD;
            }
        }
        UISRemoveUnNessaryRateFncs(pInfo);
        pInfo->pUnloadFnc(pScreen->GroupID, pScreen->ScreenID, pScreen->pData);
        pScreen->pData = 0;
        pInfo->NumScreens--;
        for (; Screen < pInfo->NumScreens; Screen++) {
            pOther = &pInfo->Screens[Screen];
            pScreen = &pInfo->Screens[Screen + 1];
            memmove(pOther, pScreen, sizeof(UISScreenT));
            nRateFnc = pInfo->NumScreenRefs;
            while (nRateFnc-- != 0) {
                if (pInfo->ScreenRefs[nRateFnc].pScreen == pScreen) {
                    pInfo->ScreenRefs[nRateFnc].pScreen = pOther;
                }
            }
            nRateFnc = pInfo->MaxRateFncs;
            while (nRateFnc-- != 0) {
                if (pInfo->RateFncs[nRateFnc].pScreen == pScreen) {
                    pInfo->RateFncs[nRateFnc].pScreen = pOther;
                }
            }
            if (Screen + 1 == pInfo->ActiveScreen) {
                pInfo->ActiveScreen = Screen;
            }
        }
        if (pInfo->ActiveScreen == -1) {
            if (pInfo->NumScreens != 0) {
                pInfo->ActiveScreen = fn_8021C5EC(pInfo, ParentGroupID, ParentScreenID);
                if (pInfo->ActiveScreen < pInfo->NumScreens) {
                    pScreen = &pInfo->Screens[pInfo->ActiveScreen];
                } else {
                    pInfo->ActiveScreen = pInfo->NumScreens - 1;
                    pScreen = pInfo->ActiveScreen < pInfo->NumScreens
                                  ? &pInfo->Screens[pInfo->ActiveScreen]
                                  : 0;
                }
                if (pScreen != 0) {
                    UISThreadActionT Action;

                    Action.s.GroupID = pScreen->GroupID;
                    Action.s.ScreenID = pScreen->ScreenID;
                    if (!_UIS_ShuttingDown) {
                        fn_8021D904(pScreen->GroupID, pScreen->ScreenID, pInfo, 3, &Action, 0, 0);
                    }
                }
            } else {
                pInfo->ActiveScreen = -1;
            }
        }
    }
    return 1;
}

void fn_8021956C(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bProcess)
{
    UISThreadActionT Action;
    Int32 Arg;

    Action.s.GroupID = GroupID;
    Action.s.ScreenID = ScreenID;
    Arg = 0;
    fn_8021D904(GroupID, ScreenID, pInfo, 1, &Action, 1, &Arg);
    if (bProcess) {
        fn_8021DDF4(pInfo, 0);
    }
}

void fn_802195E4(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
{
    UISThreadActionT Action;

    Action.s.GroupID = GroupID;
    Action.s.ScreenID = ScreenID;
    fn_8021D904(GroupID, ScreenID, pInfo, 3, &Action, 0, 0);
    if (!(pInfo->Flags & 2)) {
        fn_8021DDF4(pInfo, 0);
    }
}

/* Returns the group and screen IDs of the active screen (-1 when none). */
void fn_80219650(UISInfoT *pInfo, Uint16 *pGroupID, Uint16 *pScreenID)
{
    if (pGroupID != 0) {
        *pGroupID = -1;
        if (pInfo->ActiveScreen != -1) {
            *pGroupID = pInfo->Screens[pInfo->ActiveScreen].GroupID;
        }
    }
    if (pScreenID != 0) {
        *pScreenID = -1;
        if (pInfo->ActiveScreen != -1) {
            *pScreenID = pInfo->Screens[pInfo->ActiveScreen].ScreenID;
        }
    }
}

/* Runs the queued thread actions, makes the screen of the last modal record
   current, then sends event Channel to it (or to every screen when AllScreens)
   unless the screen has taken it already; a negative Message is sent again. */
void fn_802196B4(UISInfoT *pInfo, Uint32 Channel, Int32 Message, Int32 nParam, Int32 *pParam,
                 Int32 AllScreens)
{
    Int32 Modal;
    Uint32 Screen;
    Uint32 NumScreens;
    UISScreenT *pScreen;
    Int32 bDontProcessEvent;
    Uint8 bProcess;

    fn_8021DDF4(pInfo, 0);
    Modal = pInfo->NumScreenRefs - 1;
    if (Modal >= 0) {
        pInfo->ActiveScreen = fn_8021C5EC(pInfo, pInfo->ScreenRefs[Modal].GroupID,
                                          pInfo->ScreenRefs[Modal].ScreenID);
    }
    if (AllScreens) {
        Screen = 0;
        NumScreens = pInfo->NumScreens;
    } else {
        Screen = pInfo->ActiveScreen;
        NumScreens = Screen + 1;
        if (Screen == -1) {
            return;
        }
    }
    if (pParam != 0 && *(Float32 *)pParam == 0.0f && _UIStudio_pEventHook != 0) {
        _UIStudio_pEventHook();
    }
    for (; Screen < NumScreens; Screen++) {
        pScreen = &pInfo->Screens[Screen];
        bDontProcessEvent = pScreen->unk_00 & (1 << Channel);
        if ((bDontProcessEvent == 1 && Message < 0) || bDontProcessEvent == 0) {
            bProcess = 0;
            if (pParam != 0 && *(Float32 *)pParam != 0.0f && _UIStudio_pEventHook != 0) {
                _UIStudio_pEventHook();
            }
            pInfo->Flags |= 2;
            fn_802180A0(pInfo, pScreen, &pInfo->RunState, 0, Channel, Message, nParam, pParam,
                        &bProcess);
            pInfo->Flags &= ~2;
        }
    }
}

void fn_80219854(UISInfoT *pInfo, UISRunStateT *pState, Int32 Arg2, Int32 Arg3, Int32 Count,
                 Int32 *pArgs, Int32 bAll)
{
    Uint32 Screen;
    Uint32 End;
    UISScreenT *pScreen;
    Uint8 Done;

    if (bAll) {
        Screen = 0;
        End = pInfo->NumScreens;
    } else {
        Screen = pInfo->ActiveScreen;
        End = Screen + 1;
        if (Screen == -1) {
            return;
        }
    }
    for (; Screen < End; Screen++) {
        pScreen = &pInfo->Screens[Screen];
        if (Arg3 == -8 && pScreen->bWaitingToBeUnloaded == 1) {
            continue;
        }
        Done = 0;
        fn_802180A0(pInfo, pScreen, pState, 0, Arg2, Arg3, Count, pArgs, &Done);
    }
}

/* Runs Ticks timer ticks, then draws every loaded screen between the draw callbacks. */
void fn_8021992C(UISInfoT *pInfo, Uint32 Ticks)
{
    Uint32 Tick;
    Uint32 Screen;
    Uint32 NumScreens;
    UISScreenT *pScreen;

    Tick = 0;
    fn_8021CA54(1.0f, 1.0f, 1.0f, 1.0f);
    fn_8021CA70(0.0f, 0.0f, 0.0f, 0.0f);
    for (; Tick < Ticks; Tick++) {
        fn_80218364(pInfo, pInfo->MSPerTick);
    }
    if (pInfo->pCallback2C != 0) {
        pInfo->pCallback2C();
    }
    NumScreens = pInfo->NumScreens;
    for (Screen = 0; Screen < NumScreens; Screen++) {
        lbl_803ECFE8.iValue = 0;
        pScreen = &pInfo->Screens[Screen];
        if (pInfo->pCallback34 != 0) {
            pInfo->pCallback34(pScreen->GroupID, pScreen->ScreenID);
        }
        fn_80217D30(pInfo, pScreen, 0, -2);
        if (pInfo->pCallback38 != 0) {
            pInfo->pCallback38(pScreen->GroupID, pScreen->ScreenID);
        }
    }
    if (pInfo->pCallback30 != 0) {
        pInfo->pCallback30();
    }
}

void fn_80219A54(UISInfoT *pInfo, Int32 Arg1)
{
    Int32 Screen;
    Int32 NumScreens;
    Uint8 Done;

    fn_8021DDF4(pInfo, 0);
    NumScreens = pInfo->NumScreens;
    for (Screen = 0; Screen < NumScreens; Screen++) {
        pInfo->Flags |= 2;
        Done = 0;
        fn_802180A0(pInfo, &pInfo->Screens[Screen], &pInfo->RunState, 0, Arg1, -10, 0, 0, &Done);
        pInfo->Flags &= ~2;
    }
}

/* Returns the object with ID ObjectID of the given screen, or 0. */
void *fn_80219AF8(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Uint16 ObjectID)
{
    void *pObject;
    Int32 Screen;
    UISScreenT *pScreen;
    UISScreenDataT *pData;
    UISObjectRefT *pRef;
    Uint32 Object;

    pObject = 0;
    Screen = fn_8021C5EC(pInfo, GroupID, ScreenID);
    if (Screen < pInfo->NumScreens) {
        pScreen = &pInfo->Screens[Screen];
        pData = pScreen->pData;
        for (Object = 0; Object < pData->NumObjects; Object++) {
            pRef = &pData->pObjects[Object];
            if (pRef->ID == ObjectID) {
                pObject = pRef->pOffset != 0 ? (Uint8 *)pData + *pRef->pOffset : 0;
                break;
            }
        }
    }
    return pObject;
}

void fn_80219F84(UISInfoT *pInfo, UISScreenT *pScreen, Int32 Type, void *pNode, Int32 bValue)
{
    Int32 Current;
    Int32 Value;

    if (pScreen != 0 && pScreen->pData != 0 && pNode != 0) {
        Current = fn_802178E4(pScreen, &pNode, 8, pScreen->pData->pControls);
        Value = bValue ? 1 : 0;
        if (Current != -1 && Current != Value) {
            fn_80217A7C(pInfo, pScreen, Value, Type, pNode, 1);
        }
    }
}

/* Returns the enable state of the active screen's first control. */
Uint8 fn_8021A020(UISInfoT *pInfo)
{
    UISScreenT *pScreen;

    if (pInfo->ActiveScreen < pInfo->NumScreens) {
        pScreen = &pInfo->Screens[pInfo->ActiveScreen];
        if (pScreen->pData != 0) {
            return pScreen->pData->pControls[0].pState->bEnabled;
        }
    }
    return 0;
}

Uint8 fn_8021A060(UISInfoT *pInfo)
{
    return pInfo->bShuttingDown;
}
