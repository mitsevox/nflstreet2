#include "UIStudio/UIStudio.h"

/* Partial source for the UI Studio core file (0x802176E8-0x8021A068).
   Functions of this file without a body here are declared only; their
   original bytes are not replaced. */

Int32 fn_802178E4(void *pNodeArg, void **ppNode, Int32 Type, void *pNode);
void fn_80217A7C(UISInfoT *pInfo, UISScreenT *pScreen, Int32 Value, Int32 Type, void *pNode,
                 Int32 bAll);
void fn_802180A0(UISInfoT *pInfo, UISScreenT *pScreen, void *pArg2, Int32 Arg3, Int32 Arg4,
                 Int32 Arg5, Int32 Arg6, Uint8 *pArg7, Uint8 *pArg8);
Uint8 fn_8021861C(void *pTarget);
Int32 fn_80218DDC(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bArg3, Int32 Arg4,
                  Int32 *pArg5);
void fn_8021956C(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bProcess);

/* Calls the control callback for control Control of pScreen and recurses
   into every control linked from its live nodes. */
void fn_80217C38(UISInfoT *pInfo, void *pArg, UISScreenT *pScreen, Int32 Control)
{
    UISControlT *pControl;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    Uint32 Node;
    Uint32 Entry;

    if (pScreen->pData != 0) {
        pControl = &pScreen->pData->pControls[Control];
        pInfo->pControlFnc(pArg, (Uint8 *)pControl->pState + 8);
        for (Node = 0; Node < pControl->NumNodes; Node++) {
            pNode = pControl->ppNodes[Node];
            if (*pNode->pFlag != 0) {
                for (Entry = 0; Entry < pNode->NumEntries; Entry++) {
                    pEntry = &pNode->pEntries[Entry];
                    if (pEntry->ID == 0xFFFF) {
                        fn_80217C38(pInfo, pArg, pScreen, pEntry->Value);
                    }
                }
            }
        }
    }
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

/* Returns the byte size of a UISInfoT with the given table capacities. */
Uint32 fn_802188A0(Uint32 NumScreens, Uint32 NumActionFncs, Uint32 NumRateFncs, Uint32 Num40,
                   Uint32 NumA, Uint32 NumB)
{
    return (NumScreens + 1) * 20 + (NumActionFncs * 4 + sizeof(UISInfoT)) +
           NumRateFncs * sizeof(UISRateFncT) + Num40 * 40 + (NumA + NumB) * 4;
}

/* Unloads every loaded screen, last first. */
void fn_80218A34(UISInfoT *pInfo)
{
    Int32 Screen;

    pInfo->bShuttingDown = 1;
    for (Screen = pInfo->NumScreens - 1; Screen >= 0; Screen--) {
        fn_8021956C(pInfo, pInfo->Screens[Screen].GroupID, pInfo->Screens[Screen].ScreenID, 1);
    }
    pInfo->unk_00 = 0;
    pInfo->bShuttingDown = 0;
}

void fn_80218AA8(UISInfoT *pInfo, void *pCallback)
{
    pInfo->pCallback0C = pCallback;
}

void fn_80218AB0(UISInfoT *pInfo, void *pCallback14, void *pCallback18)
{
    pInfo->pCallback14 = pCallback14;
    pInfo->pCallback18 = pCallback18;
}

void fn_80218ABC(UISInfoT *pInfo, void *pCallback)
{
    pInfo->pCallback10 = pCallback;
}

void fn_80218AC4(UISInfoT *pInfo, UISControlFncT *pFnc)
{
    pInfo->pControlFnc = pFnc;
}

void fn_80218ACC(UISInfoT *pInfo, void *pCallback)
{
    pInfo->pCallback24 = pCallback;
}

/* Installs action function pFnc at index Fnc. */
void fn_80218AD4(UISInfoT *pInfo, Int32 Fnc, UISActionFncT *pFnc)
{
    pInfo->ActionFncs[Fnc] = pFnc;
    pInfo->NumActionFncs++;
}

/* Sets the cursor target; a target that fails the 0x8021861C test is cleared.
   Returns 1 when pTarget was nonzero. */
Int32 fn_80218CB8(UISInfoT *pInfo, void *pTarget)
{
    Int32 Result;

    Result = 0;
    if (pTarget != 0) {
        if (pTarget != pInfo->pCursor->pTarget && !fn_8021861C(pTarget)) {
            pTarget = 0;
        }
        Result = 1;
    }
    pInfo->pCursor->pTarget = pTarget;
    return Result;
}

Int32 fn_80218D20(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Arg3, Int32 Arg4,
                  Int32 Arg5, Uint8 *pArg6)
{
    UISScreenT *pScreen;
    Uint8 Done;

    pScreen = &pInfo->Screens[fn_8021C5EC(pInfo, GroupID, ScreenID)];
    fn_802182E4(pInfo, pScreen);
    pScreen->pData->pControls[0].pState->bEnabled = 1;
    Done = 0;
    if (Arg5 == 255) {
        Arg5 = pArg6[43];
    }
    pInfo->Flags |= 2;
    fn_802180A0(pInfo, pScreen, pInfo->unk_74, 0, -1, -2, Arg5, pArg6, &Done);
    pInfo->Flags &= ~2;
    return 1;
}

Int32 fn_80218FC4(UISInfoT *pInfo, Int16 GroupID, Int16 ScreenID, Int32 Arg3, Int32 *pArg4)
{
    UISThreadActionT Action;

    if (!(pInfo->Flags & 2)) {
        return fn_80218DDC(pInfo, GroupID, ScreenID, 0, Arg3, pArg4);
    }
    Action.GroupID = GroupID;
    Action.ScreenID = ScreenID;
    Action.unk_04 = -1;
    Action.unk_06 = -1;
    fn_8021D904(GroupID, ScreenID, pInfo, 0, &Action, Arg3, pArg4);
    return 1;
}

Int32 fn_80219044(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Arg3, Int32 *pArg4)
{
    return fn_80218DDC(pInfo, GroupID, ScreenID, 1, Arg3, pArg4);
}

void fn_8021956C(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 bProcess)
{
    UISThreadActionT Action;
    Int32 Arg;

    Action.GroupID = GroupID;
    Action.ScreenID = ScreenID;
    Arg = 0;
    fn_8021D904(GroupID, ScreenID, pInfo, 1, &Action, 1, &Arg);
    if (bProcess) {
        fn_8021DDF4(pInfo, 0);
    }
}

void fn_802195E4(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
{
    UISThreadActionT Action;

    Action.GroupID = GroupID;
    Action.ScreenID = ScreenID;
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

void fn_80219854(UISInfoT *pInfo, void *pArg1, Int32 Arg2, Int32 Arg3, Int32 Arg4, Uint8 *pArg5,
                 Int32 bAll)
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
        fn_802180A0(pInfo, pScreen, pArg1, 0, Arg2, Arg3, Arg4, pArg5, &Done);
    }
}

void fn_80219A54(UISInfoT *pInfo, Int32 Arg1)
{
    Int32 Screen;
    Uint8 Done;

    fn_8021DDF4(pInfo, 0);
    for (Screen = 0; Screen < pInfo->NumScreens; Screen++) {
        pInfo->Flags |= 2;
        Done = 0;
        fn_802180A0(pInfo, &pInfo->Screens[Screen], pInfo->unk_74, 0, Arg1, -10, 0, 0, &Done);
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

    if (pScreen != 0 && pScreen->pData != 0 && pNode != 0) {
        Current = fn_802178E4(pScreen, &pNode, 8, pScreen->pData->pControls);
        if (Current != -1 && Current != (bValue ? 1 : 0)) {
            fn_80217A7C(pInfo, pScreen, bValue ? 1 : 0, Type, pNode, 1);
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
