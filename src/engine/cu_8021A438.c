#include <string.h>

#include "UIStudio/UIStudio.h"
#include "engine/cu_8021A438.h"

/* Partial source for the engine range 0x8021A438-0x80221198 (neutral file
   name). Functions without a body here keep their original bytes. */

Int32 fn_8021A45C(UISInfoT *pInfo, Int32 *pFrame, UISRunStateT *pState, UISScreenT *pScreen,
                  UISControlStateT *pControlState);
Int32 fn_8021C760(UISInfoT *pInfo, UISScreenT *pScreen, UISControlStateT *pControlState,
                  UISRunStateT *pState, Int32 Value, Uint32 NumArgs, Int32 *pArgs,
                  Uint32 NumExtra, Int32 *pExtra, Uint8 bPushArg, Int32 Arg, Int32 *pResult);
Int32 *fn_8021D888(UISInfoT *pInfo, Int32 *p, UISThreadActionT *pAction, Int16 GroupID,
                   Int16 ScreenID, Uint32 Type, Int32 Count, Int32 *pArgs);
void fn_8021D404(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Delta);
void fn_8021D718(UISInfoT *pInfo, Int32 Value, Int32 Count, Int32 *pArgs);

typedef void Callback_803EBF40(Int32, Int32);
typedef void Callback_803EBF44(Int32);

extern Object_8021E688 *lbl_803EBF38[2];
extern Callback_803EBF40 *lbl_803EBF40;
extern Callback_803EBF44 *lbl_803EBF44;

int fn_801F0DB8(void *pData, int index);
int fn_801F0E68(void *pData, int index);
void fn_80220BE0(void);
void fn_8021E160(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry);
void fn_8021EE54(void *pData, Int32 a, Int32 b, Int32 c, void *pArg);

extern Float32 lbl_8039F858[4];
extern Float32 lbl_8039F868[4];

void *fn_8021A438(UISInfoT *pInfo, Uint8 *pBase, Int32 Offset)
{
    void *p;

    if (Offset < 0) {
        Offset &= 0x7FFFFFFF;
        p = (Uint8 *)pInfo->pCursor->pTarget + Offset;
    } else {
        p = pBase + Offset;
    }
    return p;
}

Uint32 fn_8021C5EC(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
{
    Uint32 Screen;
    UISScreenT *pScreen;

    for (Screen = 0; Screen < pInfo->NumScreens; Screen++) {
        pScreen = &pInfo->Screens[Screen];
        if (pScreen->GroupID == GroupID && pScreen->ScreenID == ScreenID) {
            break;
        }
    }
    return Screen;
}

Int32 fn_8021C654(UISControlT *pControl, Uint32 ID)
{
    Uint32 Item;
    UISControlItemT *pItem;

    for (Item = 0; Item < pControl->NumItems; Item++) {
        pItem = &pControl->pItems[Item];
        if ((pItem->Flags & 0x8000) && pItem->ID == (Uint16)ID) {
            return pItem->Value;
        }
    }
    return 0;
}

Int32 fn_8021C6A8(UISControlT *pControl, Int32 Flags, Uint32 ID)
{
    Uint32 Item;
    UISControlItemT *pItem;

    for (Item = 0; Item < pControl->NumItems; Item++) {
        pItem = &pControl->pItems[Item];
        if (!(pItem->Flags & 0xC000) && pItem->ID == (Uint16)ID &&
            (pItem->Flags & 0x2FFF) == Flags) {
            return pItem->Value;
        }
    }
    return 0;
}

Int32 fn_8021C70C(UISControlT *pControl, Uint32 ID)
{
    Uint32 Item;
    UISControlItemT *pItem;

    for (Item = 0; Item < pControl->NumItems; Item++) {
        pItem = &pControl->pItems[Item];
        if ((pItem->Flags & 0x4000) && pItem->ID == (Uint16)ID) {
            return pItem->Value;
        }
    }
    return 0;
}

Int32 fn_8021C760(UISInfoT *pInfo, UISScreenT *pScreen, UISControlStateT *pControlState,
                  UISRunStateT *pState, Int32 Value, Uint32 NumArgs, Int32 *pArgs,
                  Uint32 NumExtra, Int32 *pExtra, Uint8 bPushArg, Int32 Arg, Int32 *pResult)
{
    Int32 *pFrame;
    Uint32 i;
    Int32 Result;

    pFrame = pState->pTop;
    if (pResult == 0) {
        *pFrame = 0;
    } else {
        *pFrame = *pResult;
    }
    pState->pTop++;
    if (bPushArg) {
        *pState->pTop = Arg;
        pState->pTop++;
    }
    for (i = 0; i < NumArgs; i++) {
        *pState->pTop = pArgs[i];
        pState->pTop++;
    }
    for (i = 0; i < NumExtra; i++) {
        *pState->pTop = pExtra[i];
        pState->pTop++;
    }
    *pState->pTop = (Int32)pControlState;
    pState->pTop++;
    *pState->pTop = 0;
    pState->unk_10 = Value;
    pState->pTop++;
    Result = fn_8021A45C(pInfo, pFrame, pState, pScreen, pControlState);
    if (pResult != 0) {
        *pResult = *pFrame;
    }
    if (Result != 3) {
        pState->pTop = pFrame;
    }
    return Result;
}

Float32 *UISGetActionPtrValue(Uint32 Action, UISControlInfoT *pControlInfo)
{
    switch (Action) {
    case 16:
        return &pControlInfo->f20;
    case 17:
        return &pControlInfo->f24;
    case 18:
        return &pControlInfo->f28;
    case 19:
        return &pControlInfo->f08;
    case 20:
        return &pControlInfo->f0C;
    case 21:
        return &pControlInfo->f10;
    case 22:
        return &pControlInfo->f2C;
    case 23:
        return &pControlInfo->f30;
    case 24:
        return &pControlInfo->f34;
    case 25:
        return &pControlInfo->f14;
    case 26:
        return &pControlInfo->f18;
    case 27:
        return &pControlInfo->f1C;
    case 32:
        return &pControlInfo->f58;
    case 33:
        return &pControlInfo->f4C;
    case 34:
        return &pControlInfo->f50;
    case 35:
        return &pControlInfo->f54;
    case 36:
        return &pControlInfo->f48;
    case 37:
        return &pControlInfo->f3C;
    case 38:
        return &pControlInfo->f40;
    case 39:
        return &pControlInfo->f44;
    }
    return &pControlInfo->f48;
}

Float32 *fn_8021CA3C(void)
{
    return lbl_8039F858;
}

Float32 *fn_8021CA48(void)
{
    return lbl_8039F868;
}

void fn_8021CA54(Float32 a, Float32 b, Float32 c, Float32 d)
{
    lbl_8039F858[0] = a;
    lbl_8039F858[3] = d;
    lbl_8039F858[1] = b;
    lbl_8039F858[2] = c;
}

void fn_8021CA70(Float32 a, Float32 b, Float32 c, Float32 d)
{
    lbl_8039F868[0] = a;
    lbl_8039F868[3] = d;
    lbl_8039F868[1] = b;
    lbl_8039F868[2] = c;
}

/* Writes Value in decimal to pDst, stopping at pEnd; returns the end of the
   written text. */
char *fn_8021CA8C(Uint32 Value, char *pDst, char *pEnd, char Pad, Int32 Width, Int32 bSigned)
{
    char Buffer[16];
    Int32 Length;
    Int32 bNegative;
    Int32 Count;
    Uint32 Quotient;

    Length = 0;
    bNegative = 0;
    if (bSigned) {
        bNegative = (Int32)Value < 0;
        if (bNegative) {
            Value = -Value;
        }
    }
    do {
        Quotient = Value / 10;
        Buffer[Length++] = Value + '0' - Quotient * 10;
        Value = Quotient;
    } while (Value != 0);
    if (Width != 0) {
        for (Count = Width - bNegative - Length; Count > 0; Count--) {
            Buffer[Length++] = Pad;
        }
    }
    if (bNegative) {
        Buffer[Length++] = '-';
    }
    for (Length--; Length >= 0 && pDst < pEnd; Length--) {
        *pDst++ = Buffer[Length];
    }
    return pDst;
}

/* Writes Value in hexadecimal; Case selects the letter case of the digits. */
char *fn_8021CDAC(Uint32 Value, char *pDst, char *pEnd, Int32 Width, char Pad, Int32 Case)
{
    char Buffer[16];
    Int32 Length;
    Int32 Count;
    char Digit;

    Length = 0;
    do {
        Digit = (Value & 0xF) + '0';
        if (Digit > '9') {
            Digit += Case + 39;
        }
        Buffer[Length++] = Digit;
        Value >>= 4;
    } while (Value != 0);
    if (Width != 0) {
        for (Count = Width - Length; Count > 0; Count--) {
            Buffer[Length++] = Pad;
        }
    }
    for (Length--; Length >= 0 && pDst < pEnd; Length--) {
        *pDst++ = Buffer[Length];
    }
    return pDst;
}

/* Copies pString to pDst padded with spaces to Width (left-aligned when
   bLeft is 1), stopping at pEnd. */
char *fn_8021CE48(const char *pString, char *pDst, char *pEnd, Int32 Width, Int32 Precision,
                  Int32 bLeft)
{
    Int32 Count;
    Int32 Length;

    Count = 0;
    if (Width < 0) {
        Width = -Width;
    }
    Length = strlen(pString);
    if (bLeft == 0) {
        while (Count < Width - Length && pDst != pEnd) {
            *pDst++ = ' ';
            Count++;
        }
    }
    while (*pString != 0 && pDst != pEnd) {
        *pDst++ = *pString++;
        Count++;
    }
    if (bLeft == 1) {
        while (Count < Width && pDst != pEnd) {
            *pDst++ = ' ';
            Count++;
        }
    }
    return pDst;
}

Int32 fn_8021D23C(UISScreenDataT *pData, UISControlT *pControl, UISControlStateT *pState)
{
    Uint32 Node;
    Uint32 Entry;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;

    for (Node = 0; Node < pControl->NumNodes; Node++) {
        pNode = pControl->ppNodes[Node];
        for (Entry = 0; Entry < pNode->NumEntries; Entry++) {
            pEntry = &pNode->pEntries[Entry];
            if (pEntry->ID == 0xFFFF && pData->pControls[pEntry->Value].pState == pState) {
                return 1;
            }
        }
    }
    return 0;
}

UISControlStateT *fn_8021D2DC(UISScreenDataT *pData, UISControlT *pControl)
{
    Uint32 Node;
    Uint32 Entry;
    UISNodeT *pNode;
    UISNodeEntryT *pEntry;
    UISControlStateT *pState;

    for (Node = 0; Node < pControl->NumNodes; Node++) {
        pNode = pControl->ppNodes[Node];
        for (Entry = 0; Entry < pNode->NumEntries; Entry++) {
            pEntry = &pNode->pEntries[Entry];
            if (pEntry->ID == 0xFFFF) {
                pState = pData->pControls[pEntry->Value].pState;
                if (pState->bEnabled != 0) {
                    return pState;
                }
            }
        }
    }
    return 0;
}

UISControlStateT *fn_8021D37C(UISScreenT *pScreen, UISControlStateT *pState)
{
    UISScreenDataT *pData;
    Uint32 Control;
    UISControlT *pControl;

    pData = pScreen->pData;
    for (Control = 0; Control < pData->NumControls; Control++) {
        pControl = &pData->pControls[Control];
        if (fn_8021D23C(pData, pControl, pState)) {
            return fn_8021D2DC(pData, pControl);
        }
    }
    return 0;
}

/* Moves the given screen Delta places through the screen table, keeping
   the active index and screen pointers pointing at the same screens. */
void fn_8021D404(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Delta)
{
    UISScreenT Temp;
    Int32 Screen;
    Int32 Previous;
    Int32 NumScreens;
    Int32 Count;
    Int32 Step;
    Uint32 Rate;
    Uint32 Ref;

    Screen = fn_8021C5EC(pInfo, GroupID, ScreenID);
    NumScreens = pInfo->NumScreens;
    if (Screen < NumScreens) {
        if (Delta >= 0) {
            Count = Delta;
            Step = 1;
        } else {
            Count = -Delta;
            Step = -1;
        }
        while (Count-- != 0) {
            Previous = Screen;
            Screen += Step;
            if (Screen >= NumScreens || Screen < 0) {
                break;
            }
            if (pInfo->ActiveScreen == Screen) {
                pInfo->ActiveScreen = Previous;
            } else if (pInfo->ActiveScreen == Previous) {
                pInfo->ActiveScreen = Screen;
            }
            for (Rate = 0; Rate < pInfo->NumRateFncs; Rate++) {
                if (pInfo->RateFncs[Rate].pScreen == &pInfo->Screens[Screen]) {
                    pInfo->RateFncs[Rate].pScreen = &pInfo->Screens[Previous];
                } else if (pInfo->RateFncs[Rate].pScreen == &pInfo->Screens[Previous]) {
                    pInfo->RateFncs[Rate].pScreen = &pInfo->Screens[Screen];
                }
            }
            for (Ref = 0; Ref < pInfo->NumScreenRefs; Ref++) {
                if (pInfo->ScreenRefs[Ref].pScreen == &pInfo->Screens[Screen]) {
                    pInfo->ScreenRefs[Ref].pScreen = &pInfo->Screens[Previous];
                } else if (pInfo->ScreenRefs[Ref].pScreen == &pInfo->Screens[Previous]) {
                    pInfo->ScreenRefs[Ref].pScreen = &pInfo->Screens[Screen];
                }
            }
            Temp = pInfo->Screens[Screen];
            pInfo->Screens[Screen] = pInfo->Screens[Previous];
            pInfo->Screens[Previous] = Temp;
        }
    }
}

void fn_8021D620(UISInfoT *pInfo, UISScreenT *pScreen, UISRunStateT *pState, Int32 Control,
                 Uint32 ID, Int32 Count, Int32 *pArgs)
{
    UISControlT *pControl;
    UISControlItemT *pItem;
    Uint32 Item;
    Int32 Value;

    pControl = &pScreen->pData->pControls[Control];
    for (Item = 0; Item < pControl->NumItems; Item++) {
        pItem = &pControl->pItems[Item];
        if (pItem->ID == 0xFFFF) {
            fn_8021D620(pInfo, pScreen, pState, pItem->Value, ID, Count, pArgs);
        }
    }
    Value = fn_8021C70C(pControl, ID);
    if (Value != 0) {
        fn_8021C760(pInfo, pScreen, pControl->pState, pState, Value, Count, pArgs, 0, 0, 0, 0,
                    0);
    }
}

void fn_8021D718(UISInfoT *pInfo, Int32 Value, Int32 Count, Int32 *pArgs)
{
    Uint32 Screen;
    Uint32 NumScreens;
    UISScreenT *pScreen;

    NumScreens = pInfo->NumScreens;
    for (Screen = 0; Screen < NumScreens; Screen++) {
        pScreen = &pInfo->Screens[Screen];
        if (pScreen->bWaitingToBeUnloaded == 0) {
            pInfo->Flags |= 2;
            fn_8021D620(pInfo, pScreen, &pInfo->RunState, 0, Value, Count, pArgs);
            pInfo->Flags &= ~2;
        }
    }
}

void fn_8021D7B8(UISInfoT *pInfo, Int32 Value, Int32 Count, Int32 *pArgs)
{
    UISThreadActionT Action;
    Int16 GroupID;
    Int16 ScreenID;

    if (pInfo->Flags & 6) {
        GroupID = pInfo->Screens[pInfo->ActiveScreen].GroupID;
        ScreenID = pInfo->Screens[pInfo->ActiveScreen].ScreenID;
        Action.Words[0] = Value;
        fn_8021D904(GroupID, ScreenID, pInfo, 9, &Action, Count, pArgs);
    } else {
        fn_8021D718(pInfo, Value, Count, pArgs);
    }
}

Int32 fn_8021D828(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
{
    Uint32 Screen;
    UISScreenT *pScreen;

    for (Screen = 0; Screen < pInfo->NumScreens; Screen++) {
        pScreen = &pInfo->Screens[Screen];
        if (pScreen->GroupID == GroupID && pScreen->ScreenID == ScreenID) {
            return pScreen->unk_00 == 0;
        }
    }
    return 1;
}

void fn_8021D880(UISRuntimeErrorFncT *pFnc)
{
    RuntimeErrorFnc = pFnc;
}

Int32 *fn_8021D888(UISInfoT *pInfo, Int32 *p, UISThreadActionT *pAction, Int16 GroupID,
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

void fn_8021D904(Int16 GroupID, Int16 ScreenID, UISInfoT *pInfo, Int32 Type,
                 UISThreadActionT *pAction, Int32 Arg5, Int32 *pArg6)
{
    UISActionStackT *pStack;

    pStack = &pInfo->ActionStack;
    pStack->pTop =
        fn_8021D888(pInfo, pStack->pTop, pAction, GroupID, ScreenID, Type, Arg5, pArg6);
}

/* Returns 0 when a queued action of a type above 1 for the given screen
   lies below p in the thread-action stack. */
Int32 fn_8021D968(Uint16 GroupID, Uint16 ScreenID, UISInfoT *pInfo, Int32 *p)
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

Int32 fn_8021D9D4(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
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
                fn_8021C5EC(pInfo, GroupID, ScreenID) < pInfo->NumScreens) {
                fn_8021D718(pInfo, pAction->Words[0], Count, pArgs);
            }
        }
    }
    return 1;
}

Int32 *fn_8021DAA4(UISInfoT *pInfo, Int32 *p, Int32 **ppTop)
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
        fn_80218AF0(pInfo, pAction->s.GroupID, pAction->s.ScreenID, pAction->s.unk_04,
                    pAction->s.unk_06, Count, pArgs);
        break;
    case 1:
        Group = pAction->s.GroupID;
        Screen = pAction->s.ScreenID;
        Index = fn_8021C5EC(pInfo, Group, Screen);
        if (Index < (Uint32)pInfo->NumScreens) {
            pScreen = &pInfo->Screens[Index];
            pScreen->bWaitingToBeUnloaded = 1;
        }
        if (fn_8021D968(Group, Screen, pInfo, p) == 0 ||
            fn_802191F0(pInfo, Group, Screen, pAction->s.unk_08) == 0) {
            *ppTop = fn_8021D888(pInfo, *ppTop, pAction, GroupID, ScreenID, 1, Count, pArgs);
        }
        break;
    case 9:
        fn_8021D718(pInfo, pAction->Words[0], Count, pArgs);
        break;
    case 2:
        pInfo->Flags |= 2;
        fn_80219854(pInfo, &pInfo->RunState, pAction->Words[0], -8, Count, pArgs, 1);
        pInfo->Flags &= ~2;
        break;
    case 3:
        fn_80219E18(pInfo, 1, pAction->s.GroupID, pAction->s.ScreenID);
        break;
    case 4:
        fn_80219E18(pInfo, 0, pAction->s.GroupID, pAction->s.ScreenID);
        break;
    case 5:
        if (pAction->c.bDone == 0) {
            fn_80219BA0(pInfo, 1, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    case 6:
        if (pAction->c.bDone == 0) {
            fn_80219BA0(pInfo, 0, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
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
        fn_8021D404(pInfo, pAction->s.GroupID, pAction->s.ScreenID, pAction->Words[3]);
        break;
    }
    return p;
}

Int32 *fn_8021DD50(UISInfoT *pInfo, Int32 *p)
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
            fn_80219BA0(pInfo, 1, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    case 6:
        if (pAction->c.bDone == 0) {
            fn_80219BA0(pInfo, 0, pAction->c.unk_00, pAction->Words[2], pAction->Words[1],
                        pAction->s.unk_0C, pAction->s.unk_0E);
            pAction->c.bDone = 1;
        }
        break;
    }
    return p;
}

void fn_8021DDF4(UISInfoT *pInfo, Int32 bControlOnly)
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
                p = fn_8021DD50(pInfo, p);
            }
        } else {
            while (p > pStack->pTop) {
                p = fn_8021DAA4(pInfo, p, &pTop);
            }
            pStack->pTop = pTop;
        }
        pInfo->Flags &= ~1;
    }
}

Int32 fn_8021DE9C(Entry_8021E688 *pEntry, Int32 Item)
{
    Int32 Result;
    Item_8021E688 *pItem;

    Result = 0;
    if (fn_801F0DB8(pEntry->pData, Item) != 0) {
        Result = 1;
    } else {
        pItem = &pEntry->pItems[Item];
        if (pItem->unk_02 != 0) {
            Result = 1;
        }
    }
    return Result;
}

Int32 fn_8021E688(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    return pItem->unk_04;
}

void fn_8021E6A8(Object_8021E688 *pObject, Int32 Index, Int32 Item, Int32 Value)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    pItem->unk_04 = Value;
    if (Value != 0) {
        pItem->unk_02 = 0;
    }
}

Int16 fn_8021E6D8(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;

    pEntry = &pObject->pA[Index];
    if (pEntry->bItems == 0) {
        fn_8021E160(pObject, Index, pEntry);
    }
    pItem = &pEntry->pItems[Item];
    return pItem->unk_00;
}

Uint32 fn_8021E924(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->Flags & 0x7FFFFFFF;
}

Int32 fn_8021E93C(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_08;
}

void fn_8021E950(void *pData, Int32 a, Int32 b, Int32 c, void *pArg)
{
    fn_8021EE54(pData, a, b, c, pArg);
}

Int32 fn_8021E970(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_0C;
}

void *fn_8021E984(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->pData;
}

void fn_8021E998(Object_8021E688 *pObject, Int32 Index, void *pData)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->pData = pData;
}

void fn_8021EA34(Int32 Index, Object_8021E688 *pObject)
{
    lbl_803EBF38[Index] = pObject;
}

Object_8021E688 *fn_8021EA44(Int32 Index)
{
    return lbl_803EBF38[Index];
}

void fn_8021EB2C(Object_8021E688 *pObject, Int32 Index, Int32 Value)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->unk_18 = Value;
}

Int32 fn_8021EB40(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->unk_18;
}

void fn_8021EB54(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b)
{
    if (Flags & 4) {
        fn_80221314(pObject, a, b);
    } else if (Flags & 8) {
        fn_80225F10(pObject, a, b);
    } else if (Flags & 2) {
        fn_802262C4(pObject, a, b);
    }
}

void fn_8021ECB0(Object_8021E688 *pObject, Uint32 Flags, Int32 a)
{
    if (!(Flags & 4)) {
        if (Flags & 8) {
            fn_80225D90(pObject, a);
        } else if (Flags & 2) {
            fn_802260F8(pObject, a);
        }
    }
    fn_80220BE0();
}

void fn_8021ECFC(Object_8021E688 *pObject, Uint32 Flags, Int32 a)
{
    if (!(Flags & 4)) {
        if (Flags & 8) {
            fn_80225E10(pObject, a);
        } else if (Flags & 2) {
            fn_8022615C(pObject, a);
        }
    }
    fn_80220BE0();
}

void fn_8021ED48(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b)
{
    if (!(Flags & 4)) {
        if (!(Flags & 8)) {
            if (Flags & 2) {
                fn_8022618C(pObject, a, b);
            }
        }
    }
}

void fn_8021ED88(Object_8021E688 *pObject)
{
    Int32 Index;
    Int32 NumA;
    Int32 Item;
    Int32 NumItems;
    Entry_8021E688 *pEntry;

    if (pObject != 0) {
        NumA = pObject->NumA;
        for (Index = 0; Index < NumA; Index++) {
            pEntry = &pObject->pA[Index];
            NumItems = pEntry->NumItems;
            for (Item = 0; Item < NumItems; Item++) {
                fn_8021ED48(pObject, pEntry->Flags, Index, Item);
            }
        }
    }
}

Int32 fn_8021EE10(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    if (pEntry->Flags & 0x10) {
        return fn_801F0E68(pEntry->pData, Item);
    }
    return 0;
}

void fn_8021EE54(void *pData, Int32 a, Int32 b, Int32 c, void *pArg)
{
}

void fn_8021EF04(Int32 a, Int32 b)
{
    if (lbl_803EBF40 != 0) {
        lbl_803EBF40(a, b);
    }
}

void fn_8021EF34(void)
{
    if (lbl_803EBF40 != 0) {
        lbl_803EBF40(-1, -1);
    }
}

void fn_8021EF6C(Callback_803EBF44 *pCallback)
{
    lbl_803EBF44 = pCallback;
}

void fn_8021EF74(Int32 a)
{
    if (lbl_803EBF44 != 0) {
        lbl_803EBF44(a);
    }
}

void fn_8021EFA4(void)
{
    if (lbl_803EBF44 != 0) {
        lbl_803EBF44(0);
    }
}
