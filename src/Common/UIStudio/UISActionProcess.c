#include "UIStudio/UIStudio.h"

/* A queued thread action occupies, from its first (highest) word down: the action,
   the group and screen IDs, a spare word, the UISThreadGroupInfoT, the parameter
   count and the parameters (stored so that they read upward in order). */

static UISParamT *UISAddThreadActionAt(UISInfoT *pInfo, UISParamT *pLocalThreadInfo,
                                       UISThreadGroupInfoT *pInputThreadInfo, Int16 GroupID,
                                       Int16 ScreenID, UISThreadActionT Action, Int32 nParms,
                                       UISParamT *pParms)
{
    UISThreadGroupInfoT *pLoadInfo;
    Int32 idxParams;

    (pLocalThreadInfo--)->iValue = Action;
    (pLocalThreadInfo--)->iValue = GroupID;
    (pLocalThreadInfo--)->iValue = ScreenID;
    pLocalThreadInfo -= sizeof(UISThreadGroupInfoT) / sizeof(UISParamT);
    pLoadInfo = (UISThreadGroupInfoT *)pLocalThreadInfo--;
    *pLoadInfo = *pInputThreadInfo;
    (pLocalThreadInfo--)->iValue = nParms;
    if (pParms != NULL) {
        for (idxParams = nParms - 1; idxParams >= 0; idxParams--) {
            *pLocalThreadInfo-- = pParms[idxParams];
        }
    }
    return pLocalThreadInfo;
}

void UISAddThreadAction(Int16 GroupID, Int16 ScreenID, UISInfoT *pInfo, UISThreadActionT Action,
                        UISThreadGroupInfoT *pInputThreadInfo, Int32 nParms, UISParamT *pParms)
{
    UISLocalThreadInfoT *pThreadInfo;

    pThreadInfo = &pInfo->ThreadInfo;
    pThreadInfo->pCurrentParams =
        UISAddThreadActionAt(pInfo, pThreadInfo->pCurrentParams, pInputThreadInfo, GroupID,
                             ScreenID, Action, nParms, pParms);
}

/* A screen may be unloaded only when no later queued action other than a load or
   unload refers to it. */
static Bool _UISCanDoUnloadAction(Uint16 GroupID, Uint16 ScreenID, UISInfoT *pInfo,
                                  UISParamT *pLocalThreadInfo)
{
    UISThreadActionT Action;
    Uint16 ActionGroupID;
    Uint16 ActionScreenID;
    Int32 nParms;

    while (pLocalThreadInfo > pInfo->ThreadInfo.pCurrentParams) {
        Action = (pLocalThreadInfo--)->iValue;
        ActionGroupID = (pLocalThreadInfo--)->iValue;
        ActionScreenID = (pLocalThreadInfo--)->iValue;
        if (Action != UISThreadAction_Load && Action != UISThreadAction_Unload
            && ActionGroupID == GroupID
            && ActionScreenID == ScreenID) {
            return FALSE;
        }
        pLocalThreadInfo -= sizeof(UISThreadGroupInfoT) / sizeof(UISParamT);
        nParms = (--pLocalThreadInfo)->iValue;
        pLocalThreadInfo -= nParms;
        pLocalThreadInfo--;
    }
    return TRUE;
}

/* Runs the queued hints for one screen, unless the queue is being processed. */
Bool UISThreadProcessHints(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
{
    UISLocalThreadInfoT *pThreadInfo;
    UISThreadActionT Action;
    Uint16 ActionGroupID;
    Uint16 ActionScreenID;
    UISThreadGroupInfoT *pLoadInfo;
    Int32 nParms;
    UISParamT *pParms;
    UISParamT *pLocalThreadInfo;

    if (!(pInfo->CriticalRegions & UISCRITICAL_THREADACTIONS)) {
        pThreadInfo = &pInfo->ThreadInfo;
        pLocalThreadInfo = pThreadInfo->pBeginParams;
        while (pLocalThreadInfo > pThreadInfo->pCurrentParams) {
            Action = (pLocalThreadInfo--)->iValue;
            ActionGroupID = (pLocalThreadInfo--)->iValue;
            ActionScreenID = (pLocalThreadInfo--)->iValue;
            pLocalThreadInfo -= sizeof(UISThreadGroupInfoT) / sizeof(UISParamT);
            pLoadInfo = (UISThreadGroupInfoT *)pLocalThreadInfo;
            nParms = (--pLocalThreadInfo)->iValue;
            pLocalThreadInfo -= nParms;
            pParms = pLocalThreadInfo;
            pLocalThreadInfo--;
            if (ActionGroupID == GroupID && ActionScreenID == ScreenID
                && Action == UISThreadAction_HINT
                && UISFindScreen(pInfo, GroupID, ScreenID) < pInfo->NumScreens) {
                UISDoHint(pInfo, pLoadInfo->MessageInfo.Message, nParms, pParms);
            }
        }
    }
    return TRUE;
}

static UISParamT *_UISDoThreadAction(UISInfoT *pInfo, UISParamT *pLocalThreadInfo,
                                     UISParamT **pNextFrameThreadInfo)
{
    UISThreadActionT Action;
    UISThreadGroupInfoT *pLoadInfo;
    Int32 nParms;
    UISParamT *pParms;
    Uint16 GroupID;
    Uint16 ScreenID;
    Uint16 idxScreen;
    UISScreenT *pScreen;

    Action = (pLocalThreadInfo--)->iValue;
    GroupID = (pLocalThreadInfo--)->iValue;
    ScreenID = (pLocalThreadInfo--)->iValue;
    pLocalThreadInfo -= sizeof(UISThreadGroupInfoT) / sizeof(UISParamT);
    pLoadInfo = (UISThreadGroupInfoT *)pLocalThreadInfo;
    nParms = (--pLocalThreadInfo)->iValue;
    pLocalThreadInfo -= nParms;
    pParms = pLocalThreadInfo;
    pLocalThreadInfo--;

    switch (Action) {
    case UISThreadAction_Load:
        UISInternalLoadScreen(pInfo, pLoadInfo->ScreenInfo.GroupID, pLoadInfo->ScreenInfo.ScreenID,
                              pLoadInfo->ScreenInfo.ParentGroupID,
                              pLoadInfo->ScreenInfo.ParentScreenID, nParms, pParms);
        break;
    case UISThreadAction_Unload: {
        Uint16 UnloadGroupID = pLoadInfo->ScreenInfo.GroupID;
        Uint16 UnloadScreenID = pLoadInfo->ScreenInfo.ScreenID;

        idxScreen = UISFindScreen(pInfo, UnloadGroupID, UnloadScreenID);
        if (idxScreen < pInfo->NumScreens) {
            pScreen = &pInfo->Screens[idxScreen];
            pScreen->bWaitingToBeUnloaded = TRUE;
        }
        if (!_UISCanDoUnloadAction(UnloadGroupID, UnloadScreenID, pInfo, pLocalThreadInfo)
            || !UISInternalUnloadScreen(pInfo, UnloadGroupID, UnloadScreenID,
                                        pLoadInfo->ScreenInfo.iRetVal)) {
            /* Try again next frame. */
            *pNextFrameThreadInfo =
                UISAddThreadActionAt(pInfo, *pNextFrameThreadInfo, pLoadInfo, GroupID, ScreenID,
                                     UISThreadAction_Unload, nParms, pParms);
        }
        break;
    }
    case UISThreadAction_HINT:
        UISDoHint(pInfo, pLoadInfo->MessageInfo.Message, nParms, pParms);
        break;
    case UISThreadAction_Update:
        pInfo->CriticalRegions |= UISCRITICAL_INTERNALEVENTS;
        UISProcessInternalEvents(pInfo, &pInfo->EventStack, pLoadInfo->GenericInfo.Data[0], -8,
                                 nParms, pParms, TRUE);
        pInfo->CriticalRegions &= ~UISCRITICAL_INTERNALEVENTS;
        break;
    case UISThreadAction_ScreenActivate:
        UISInternalActivateScreen(pInfo, TRUE, pLoadInfo->ScreenInfo.GroupID,
                                  pLoadInfo->ScreenInfo.ScreenID);
        break;
    case UISThreadAction_ScreenDeactivate:
        UISInternalActivateScreen(pInfo, FALSE, pLoadInfo->ScreenInfo.GroupID,
                                  pLoadInfo->ScreenInfo.ScreenID);
        break;
    case UISThreadAction_ControlActivate:
        if (!pLoadInfo->ActivateInfo.iProcessed) {
            UISInternalActivateControl(pInfo, TRUE, pLoadInfo->ActivateInfo.iDir,
                                       pLoadInfo->ActivateInfo.pControlInfo,
                                       pLoadInfo->ActivateInfo.pTableEntry,
                                       pLoadInfo->ActivateInfo.GroupID,
                                       pLoadInfo->ActivateInfo.ScreenID);
            pLoadInfo->ActivateInfo.iProcessed = TRUE;
        }
        break;
    case UISThreadAction_ControlDeactivate:
        if (!pLoadInfo->ActivateInfo.iProcessed) {
            UISInternalActivateControl(pInfo, FALSE, pLoadInfo->ActivateInfo.iDir,
                                       pLoadInfo->ActivateInfo.pControlInfo,
                                       pLoadInfo->ActivateInfo.pTableEntry,
                                       pLoadInfo->ActivateInfo.GroupID,
                                       pLoadInfo->ActivateInfo.ScreenID);
            pLoadInfo->ActivateInfo.iProcessed = TRUE;
        }
        break;
    case UISThreadAction_ProcessEvent:
        pInfo->CriticalRegions |= UISCRITICAL_INTERNALEVENTS;
        UISProcessInternalEvents(pInfo, &pInfo->EventStack, pLoadInfo->MessageInfo.Controller,
                                 pLoadInfo->MessageInfo.Message, nParms, pParms, FALSE);
        pInfo->CriticalRegions &= ~UISCRITICAL_INTERNALEVENTS;
        break;
    case UISThreadAction_MoveScreen:
        UISMoveScreenDrawPosition(pInfo, pLoadInfo->ScreenInfo.GroupID,
                                  pLoadInfo->ScreenInfo.ScreenID, pLoadInfo->ScreenInfo.iDir);
        break;
    }
    return pLocalThreadInfo;
}

/* Runs a queued control activation or deactivation; other actions are skipped. */
static UISParamT *_UISDoThreadControlAction(UISInfoT *pInfo, UISParamT *pLocalThreadInfo)
{
    UISThreadActionT Action;
    UISThreadGroupInfoT *pLoadInfo;
    Int32 nParms;

    Action = pLocalThreadInfo->iValue;
    pLocalThreadInfo -= 3 + sizeof(UISThreadGroupInfoT) / sizeof(UISParamT);
    pLoadInfo = (UISThreadGroupInfoT *)pLocalThreadInfo;
    nParms = (--pLocalThreadInfo)->iValue;
    pLocalThreadInfo -= nParms;
    pLocalThreadInfo--;

    switch (Action) {
    case UISThreadAction_ControlActivate:
        if (!pLoadInfo->ActivateInfo.iProcessed) {
            UISInternalActivateControl(pInfo, TRUE, pLoadInfo->ActivateInfo.iDir,
                                       pLoadInfo->ActivateInfo.pControlInfo,
                                       pLoadInfo->ActivateInfo.pTableEntry,
                                       pLoadInfo->ActivateInfo.GroupID,
                                       pLoadInfo->ActivateInfo.ScreenID);
            pLoadInfo->ActivateInfo.iProcessed = TRUE;
        }
        break;
    case UISThreadAction_ControlDeactivate:
        if (!pLoadInfo->ActivateInfo.iProcessed) {
            UISInternalActivateControl(pInfo, FALSE, pLoadInfo->ActivateInfo.iDir,
                                       pLoadInfo->ActivateInfo.pControlInfo,
                                       pLoadInfo->ActivateInfo.pTableEntry,
                                       pLoadInfo->ActivateInfo.GroupID,
                                       pLoadInfo->ActivateInfo.ScreenID);
            pLoadInfo->ActivateInfo.iProcessed = TRUE;
        }
        break;
    }
    return pLocalThreadInfo;
}

/* Runs the queued thread actions. Actions that cannot complete yet are queued again
   for the next call; with bControlEventsOnly only control activations run and the
   queue is left in place. */
void UISProcessThreadAction(UISInfoT *pInfo, Bool bControlEventsOnly)
{
    UISParamT *pLocalThreadInfo;
    UISLocalThreadInfoT *pThreadInfo;
    UISParamT *pNextFrameInfo;

    if (pInfo->CriticalRegions & UISCRITICAL_THREADACTIONS) {
        return;
    }
    pThreadInfo = &pInfo->ThreadInfo;
    pLocalThreadInfo = pThreadInfo->pBeginParams;
    pInfo->CriticalRegions |= UISCRITICAL_THREADACTIONS;
    pNextFrameInfo = pLocalThreadInfo;
    if (bControlEventsOnly) {
        while (pLocalThreadInfo > pThreadInfo->pCurrentParams) {
            pLocalThreadInfo = _UISDoThreadControlAction(pInfo, pLocalThreadInfo);
        }
    } else {
        while (pLocalThreadInfo > pThreadInfo->pCurrentParams) {
            pLocalThreadInfo = _UISDoThreadAction(pInfo, pLocalThreadInfo, &pNextFrameInfo);
        }
        pThreadInfo->pCurrentParams = pNextFrameInfo;
    }
    pInfo->CriticalRegions &= ~UISCRITICAL_THREADACTIONS;
}
