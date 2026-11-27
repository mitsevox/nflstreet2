/* UI Studio thread actions (EA file name UISActionProcess.c): the queue of screen load,
   unload, activate, control and event requests the scripts post, run once per frame. */

#include "UIStudio/UIStudio.h"

Int32 *UISAddThreadActionAt(UISInfoT *pInfo, Int32 *p, UISThreadActionT *pAction, Int16 GroupID,
                   Int16 ScreenID, Uint32 Type, Int32 Count, Int32 *pArgs);

Int32 *UISAddThreadActionAt(UISInfoT *pInfo, Int32 *p, UISThreadActionT *pAction, Int16 GroupID,
                   Int16 ScreenID, Uint32 Type, Int32 Count, Int32 *pArgs)
{
    Int32 i;
    UISThreadActionT *pDst;

    *p = Type;
    *--p = GroupID;
    *--p = ScreenID;
    pDst = (UISThreadActionT *)(p - 5);
    *pDst = *pAction;
    p -= 5;
    *--p = Count;
    p--;
    if (pArgs != 0) {
        for (i = Count - 1; i >= 0; i--) {
            *p-- = pArgs[i];
        }
    }
    return p;
}

void UISAddThreadAction(Int16 GroupID, Int16 ScreenID, UISInfoT *pInfo, Int32 Type,
                 UISThreadActionT *pAction, Int32 Arg5, Int32 *pArg6)
{
    UISActionStackT *pStack;

    pStack = &pInfo->ActionStack;
    pStack->pTop =
        UISAddThreadActionAt(pInfo, pStack->pTop, pAction, GroupID, ScreenID, Type, Arg5, pArg6);
}

/* Returns 0 when a queued action of a type above 1 for the given screen
   lies below p in the thread-action stack. */
Int32 _UISCanDoUnloadAction(Uint16 GroupID, Uint16 ScreenID, UISInfoT *pInfo, Int32 *p)
{
    Uint32 Type;
    Uint16 Group;
    Uint16 Screen;

    while (p > pInfo->ActionStack.pTop) {
        Type = *p--;
        Group = *p--;
        Screen = *p--;
        if (Type > 1 && Group == GroupID && Screen == ScreenID) {
            return 0;
        }
        p -= 4;
        p -= *--p;
        p--;
    }
    return 1;
}

Int32 UISThreadProcessHints(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
{
    UISActionStackT *pStack;
    Int32 *p;
    Uint32 Type;
    Uint16 Group;
    Uint16 Screen;
    UISThreadActionT *pAction;
    Int32 Count;
    Int32 *pArgs;

    if (!(pInfo->Flags & 1)) {
        pStack = &pInfo->ActionStack;
        for (p = pStack->pStart; p > pStack->pTop;) {
            Type = *p;
            Group = *--p;
            Screen = *--p;
            p -= 5;
            pAction = (UISThreadActionT *)p;
            Count = *--p;
            p -= Count;
            pArgs = p;
            p--;
            if (Group == GroupID && Screen == ScreenID && Type == 9 &&
                UISFindScreen(pInfo, GroupID, ScreenID) < pInfo->NumScreens) {
                UISDoHint(pInfo, pAction->Words[0], Count, pArgs);
            }
        }
    }
    return 1;
}

Int32 *_UISDoThreadAction(UISInfoT *pInfo, Int32 *p, Int32 **ppTop)
{
    Uint32 Type;
    Uint16 GroupID;
    Uint16 ScreenID;
    UISThreadActionT *pAction;
    Int32 Count;
    Int32 *pArgs;
    Uint16 Group;
    Uint16 Screen;
    Uint16 Index;
    UISScreenT *pScreen;

    Type = *p;
    GroupID = *--p;
    ScreenID = *--p;
    p -= 5;
    pAction = (UISThreadActionT *)p;
    Count = *--p;
    p -= Count;
    pArgs = p;
    p--;
    switch (Type) {
    case 0:
        UISInternalLoadScreen(pInfo, pAction->s.GroupID, pAction->s.ScreenID, pAction->s.unk_04,
                    pAction->s.unk_06, Count, pArgs);
        break;
    case 1:
        Group = pAction->s.GroupID;
        Screen = pAction->s.ScreenID;
        Index = UISFindScreen(pInfo, Group, Screen);
        if (Index < (Uint32)pInfo->NumScreens) {
            pScreen = &pInfo->Screens[Index];
            pScreen->bWaitingToBeUnloaded = 1;
        }
        if (_UISCanDoUnloadAction(Group, Screen, pInfo, p) == 0 ||
            UISInternalUnloadScreen(pInfo, Group, Screen, pAction->s.unk_08) == 0) {
            *ppTop = UISAddThreadActionAt(pInfo, *ppTop, pAction, GroupID, ScreenID, 1, Count, pArgs);
        }
        break;
    case 9:
        UISDoHint(pInfo, pAction->Words[0], Count, pArgs);
        break;
    case 2:
        pInfo->Flags |= 2;
        fn_80219854(pInfo, &pInfo->RunState, pAction->Words[0], -8, Count, pArgs, 1);
        pInfo->Flags &= ~2;
        break;
    case 3:
        UISInternalActivateScreen(pInfo, 1, pAction->s.GroupID, pAction->s.ScreenID);
        break;
    case 4:
        UISInternalActivateScreen(pInfo, 0, pAction->s.GroupID, pAction->s.ScreenID);
        break;
    case 5:
        if (pAction->c.bDone == 0) {
            UISInternalActivateControl(pInfo, 1, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    case 6:
        if (pAction->c.bDone == 0) {
            UISInternalActivateControl(pInfo, 0, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    case 7:
        pInfo->Flags |= 2;
        fn_80219854(pInfo, &pInfo->RunState, pAction->Words[1], pAction->Words[0], Count, pArgs,
                    0);
        pInfo->Flags &= ~2;
        break;
    case 8:
        UISMoveScreenDrawPosition(pInfo, pAction->s.GroupID, pAction->s.ScreenID, pAction->Words[3]);
        break;
    }
    return p;
}

Int32 *_UISDoThreadControlAction(UISInfoT *pInfo, Int32 *p)
{
    Uint32 Type;
    UISThreadActionT *pAction;

    Type = *p;
    p -= 7;
    pAction = (UISThreadActionT *)p;
    p -= *--p;
    p--;
    switch (Type) {
    case 5:
        if (pAction->c.bDone == 0) {
            UISInternalActivateControl(pInfo, 1, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    case 6:
        if (pAction->c.bDone == 0) {
            UISInternalActivateControl(pInfo, 0, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    }
    return p;
}

void UISProcessThreadAction(UISInfoT *pInfo, Int32 bControlOnly)
{
    UISActionStackT *pStack;
    Int32 *p;
    Int32 *pTop;

    if (!(pInfo->Flags & 1)) {
        pStack = &pInfo->ActionStack;
        p = pStack->pStart;
        pInfo->Flags |= 1;
        pTop = p;
        if (bControlOnly) {
            while (p > pStack->pTop) {
                p = _UISDoThreadControlAction(pInfo, p);
            }
        } else {
            while (p > pStack->pTop) {
                p = _UISDoThreadAction(pInfo, p, &pTop);
            }
            pStack->pTop = pTop;
        }
        pInfo->Flags &= ~1;
    }
}
