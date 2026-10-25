#include <string.h>

#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXTransform.h>
#include "UIStudio/UIStudio.h"
#include "engine/Resource.h"
#include "engine/cu_801D03D0.h"
#include "engine/cu_8021A438.h"
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"

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

/* 12-byte argument of fn_8021DEFC. */
typedef struct Desc_8021DEFC {
    Int32 NumA;     /* 0x00 */
    Int32 NumB;     /* 0x04 */
    Int32 unk_08;   /* 0x08 */
} Desc_8021DEFC;

/* A colour that is also compared as one word. */
typedef union ColorWord_80220988 {
    GXColor Color;
    Uint32 Value;
} ColorWord_80220988;

extern GXLightObj lbl_803E9880;
extern unsigned short *lbl_803EBF48;
extern Color_80223C4C *lbl_803EBF50;
extern Int32 lbl_803EBF54;
extern Int32 lbl_803EBF58;
extern Uint8 lbl_803EBF5C;
extern Float32 lbl_802F9FA0[4][4];
extern Uint32 lbl_803ECFF0;
extern Uint32 lbl_803ECFF4;
extern Int32 lbl_803ECFF8;
extern Int32 lbl_803ECFFC;
extern Int32 lbl_803ED000;
extern Object_8021E688 *lbl_803ED004;
extern Int32 lbl_803ED008;
extern Int32 lbl_803ED00C;

int fn_801F0DB8(void *pData, int index);
int fn_801F0E68(void *pData, int index);
Res_801EDC2C *fn_801EECD0(Res_801EDC2C *pParent, unsigned int index, int heap, int mode);
unsigned int fn_801EF548(Res_801EDC2C *pRes, unsigned int index, int heap, int a, ResDone_801EFAD8 pDone,
                         void *pUser);
int fn_801F02AC(Res_801EDC2C *pRes, int heap, int a);
int fn_801F08FC(Res_801EDC2C *pRes);
int fn_801F0D34(Res_801EDC2C *pRes);
int fn_801F149C(Res_801EDC2C *pRes);
Int32 fn_8021CF38(char *pDst, Uint32 Size, const char *pFormat, Int32 a, Int32 *pArgs);
void fn_8021E160(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry);
Int32 fn_8021E504(Object_8021E688 *pObject, Int32 Index, Int32 Item);
void fn_8021E9AC(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry);
void fn_8021EB54(Object_8021E688 *pObject, Uint32 Flags, Int32 a, Int32 b);
void fn_8021EBB4(Object_8021E688 *pObject, Uint32 Flags, Int32 Index, Int32 Item, Int32 Value);
void fn_8021ECB0(Object_8021E688 *pObject, Uint32 Flags, Int32 a);
void fn_8021ECFC(Object_8021E688 *pObject, Uint32 Flags, Int32 a);
void fn_8021E950(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);
void fn_8021EE54(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser);
void fn_8021EF74(Int32 a);
void fn_8021EFA4(void);
void fn_8021F8DC(Node_80223874 *pNode);
void fn_8021F954(Node_80223874 *pNode);
void fn_8021F984(Node_80223874 *pNode, Int32 Item);
void fn_8021FB30(Node_80223874 *pNode);
void fn_80220310(Node_80223874 *pNode);
void fn_80220988(void);
void fn_80220A08(void);
void fn_80220AD0(Node_80223874 *pNode, Int32 a, Int32 Item);
Int32 fn_80220BFC(Int32 a, Int32 b);
void fn_80220D3C(void);
void fn_8024F9EC(GXLightObj *pLight, GXLightID Light);
void fn_80210388(void);

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

void fn_8021D1FC(void *p, Buffer_80222E54 *pDst, Buffer_80222E54 *pFormat, Int32 a, Int32 *pArgs)
{
    if (pFormat != NULL && pDst != NULL) {
        fn_8021CF38(pDst->pText, pDst->Size, pFormat->pText, a, pArgs);
    }
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

Object_8021E688 *fn_8021DEFC(Desc_8021DEFC *pDesc)
{
    Int32 Size;
    Object_8021E688 *pObject;

    fn_80220BE0();
    Size = pDesc->NumA * sizeof(Entry_8021E688) + sizeof(Object_8021E688) +
           pDesc->NumB * sizeof(Entry_8021E688);
    pObject = fn_801D2B7C(Size, pDesc->unk_08, 0);
    memset(pObject, 0, Size);
    if (pDesc->NumB != 0) {
        pObject->pB = (Entry_8021E688 *)(pObject + 1);
    }
    pObject->pA = (Entry_8021E688 *)(pObject + 1) + pDesc->NumB;
    pObject->NumA = pDesc->NumA;
    pObject->NumB = pDesc->NumB;
    return pObject;
}

void fn_8021DF9C(Object_8021E688 *pObject)
{
    Int32 i;
    Int32 Count;

    fn_80220BE0();
    if (pObject != NULL) {
        Count = pObject->NumA;
        for (i = 0; i < Count; i++) {
            fn_8021E72C(pObject, i, -2);
        }
        Count = pObject->NumB;
        for (i = 0; i < Count; i++) {
            fn_8021E9AC(pObject, i, &pObject->pB[i]);
        }
        memset(pObject, 0, sizeof(Object_8021E688));
        fn_801D2BD0(pObject);
    }
}

void fn_8021E050(Object_8021E688 *pObject, Int32 Index, const char *pName, Int32 a, Int32 b)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pB[Index];
    pEntry->Flags = 0x80000000;
    pEntry->pData = fn_801EEB44(pName, 44);
    pEntry->u.unk_0C = (Int32)pName;
    pEntry->unk_00 = a;
    pEntry->unk_04 = b;
}

void fn_8021E0B0(Object_8021E688 *pObject, Int32 Index, Int32 Name, Int32 a, Int32 b,
                 Uint32 Flags)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    pEntry->Flags = Flags;
    pEntry->unk_00 = a;
    pEntry->unk_08 = b;
    pEntry->unk_04 = 0;
    pEntry->pData = NULL;
    if (Name & 0x42000000) {
        pEntry->u.Ref.Index = (Name >> 16) & 0xFF;
        pEntry->Flags |= 0x80000000;
        pEntry->u.Ref.Item = Name;
    } else {
        pEntry->u.unk_0C = Name;
    }
    if (pEntry->Flags & 0x20) {
        fn_8021E160(pObject, Index, pEntry);
    }
    if (pEntry->Flags & 0x40) {
        fn_8021E504(pObject, Index, -1);
    }
}

void fn_8021E160(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry)
{
    Entry_8021E688 *pParent;
    Int32 Size;

    fn_8021EF04(Index, -1);
    if (!(pEntry->Flags & 10)) {
        if (pEntry->Flags & 0x80000000) {
            pParent = &pObject->pB[pEntry->u.Ref.Index];
            pEntry->pData = fn_801EECD0(pParent->pData, pEntry->u.Ref.Item, pParent->unk_00,
                                        pParent->unk_04);
        } else {
            pEntry->pData = fn_801EEB44((const char *)pEntry->u.unk_0C, 44);
        }
        pEntry->NumItems = fn_801F0D34(pEntry->pData);
        Size = pEntry->NumItems * sizeof(Item_8021E688);
        pEntry->pItems = fn_801D2B7C(Size, pObject->unk_00, 0);
        memset(pEntry->pItems, 0, Size);
        pEntry->bItems = 1;
    }
    fn_8021ECB0(pObject, pEntry->Flags, Index);
    fn_80220BE0();
    fn_8021EF34();
}

void fn_8021E244(Object_8021E688 *pObject, Int32 Index, Int32 Count)
{
    Entry_8021E688 *pEntry;
    Int32 Size;

    pEntry = &pObject->pA[Index];
    pEntry->NumItems = Count;
    Size = pEntry->NumItems * sizeof(Item_8021E688);
    pEntry->pItems = fn_801D2B7C(Size, pObject->unk_00, 0);
    memset(pEntry->pItems, 0, Size);
    pEntry->bItems = 1;
}

Int32 fn_8021E2B4(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;
    Int32 Result;
    Int32 First;
    Int32 End;
    Int32 i;

    pEntry = &pObject->pA[Index];
    Result = 0;
    if (pEntry->Flags == 0) {
        return 0;
    }
    if (pEntry->bItems == 0) {
        fn_8021E160(pObject, Index, pEntry);
    }
    if (Item == -1) {
        First = 0;
        End = pEntry->NumItems;
    } else {
        First = Item;
        End = First + 1;
    }
    if (pEntry->Flags & 0x10) {
        pItem = &pEntry->pItems[Item];
        if ((pItem->unk_04 != 0 || pItem->unk_02 == 1) && (pEntry->Flags & 0x80)) {
            pItem->unk_00++;
        } else {
            if (!(pEntry->Flags & 10)) {
                pItem->unk_00++;
                if (pItem->unk_00 == 1 && pItem->unk_03 == 0) {
                    pItem->unk_02 = 1;
                }
                if (fn_801F0E68(pEntry->pData, Item) == 0) {
                    fn_8021EF04(Index, Item);
                    fn_8021EF74(pEntry->Flags);
                    Result = fn_801EF548(pEntry->pData, Item, pEntry->unk_00, 100, fn_8021E950, pItem);
                    fn_8021EFA4();
                    fn_8021EF34();
                }
            }
            if (pItem->unk_02 == 1) {
                Result = 0;
            } else {
                fn_8021EBB4(pObject, pEntry->Flags, Index, Item, Result);
            }
        }
    } else {
        for (i = First; i < End; i++) {
            pItem = &pEntry->pItems[i];
            if (pItem->unk_04 != 0 && (pEntry->Flags & 0x80)) {
                pItem->unk_00++;
            } else {
                if (!(pEntry->Flags & 10) && fn_801F0C50(pEntry->pData, i) != 0) {
                    fn_8021EF04(Index, i);
                    fn_8021EF74(pEntry->Flags);
                    Result = fn_801EF390(pEntry->pData, i, pEntry->unk_00);
                    fn_8021EFA4();
                    fn_8021EF34();
                }
                pItem->unk_00++;
                fn_8021EBB4(pObject, pEntry->Flags, Index, i, Result);
            }
        }
    }
    return Result;
}

Int32 fn_8021E504(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Int32 Result;
    Int32 bAll;
    Int32 First;
    Int32 End;

    pEntry = &pObject->pA[Index];
    Result = 0;
    bAll = 0;
    if (pEntry->bItems == 0) {
        fn_8021E160(pObject, Index, pEntry);
    }
    if (Item == -1) {
        First = 0;
        End = pEntry->NumItems;
    } else {
        First = Item;
        End = Item + 1;
    }
    if (Item == -1) {
        if (pEntry->Flags & 10) {
            bAll = 0;
        } else if (pEntry->Flags & 4) {
            bAll = fn_801F149C(pEntry->pData) == 128;
        } else {
            bAll = 1;
        }
    }
    if (bAll) {
        fn_8021EF04(Index, 0);
        fn_8021EF74(pEntry->Flags);
        fn_801F02AC(pEntry->pData, pEntry->unk_00, 1);
        fn_8021EFA4();
        fn_8021EF34();
    } else if (!(pEntry->Flags & 10)) {
        for (Item = First; Item < End; Item++) {
            if (fn_801F0C50(pEntry->pData, Item) != 0) {
                fn_8021EF04(Index, Item);
                fn_8021EF74(pEntry->Flags);
                Result = fn_801EF390(pEntry->pData, Item, pEntry->unk_00);
                fn_8021EFA4();
                fn_8021EF34();
            }
        }
    }
    for (Item = First; Item < End; Item++) {
        pEntry->pItems[Item].unk_03++;
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

void fn_8021E72C(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;
    Int32 bInUse;
    Int32 i;

    pEntry = &pObject->pA[Index];
    bInUse = 0;
    if (pEntry->pItems == NULL) {
        return;
    }
    if (Item == -1 || Item == -2) {
        for (i = 0; i < pEntry->NumItems; i++) {
            pItem = &pEntry->pItems[i];
            if (pItem->unk_00 != 0) {
                if (Item == -2) {
                    pItem->unk_00 = 0;
                } else {
                    pItem->unk_00--;
                }
                if (pItem->unk_00 == 0) {
                    fn_8021EB54(pObject, pEntry->Flags, Index, i);
                } else {
                    bInUse = 1;
                }
            }
        }
        if (bInUse == 0) {
            if (!(pEntry->Flags & 10)) {
                fn_801F08FC(pEntry->pData);
            }
            fn_8021E9AC(pObject, Index, pEntry);
            if (Item == -2) {
                pEntry->Flags = 0;
            }
        }
    } else {
        pItem = &pEntry->pItems[Item];
        pItem->unk_00--;
        if ((pEntry->Flags & 0x10) && pItem->unk_00 < 0) {
            pItem->unk_00 = 0;
            if (!(pEntry->Flags & 10) && pItem->unk_03 == 0 && fn_8021DE9C(pEntry, Item) != 0) {
                fn_801F010C(pEntry->pData, Item);
                pItem->unk_02 = 0;
            }
        } else if (pItem->unk_00 <= 0) {
            fn_8021EB54(pObject, pEntry->Flags, Index, Item);
            if (!(pEntry->Flags & 10) && pItem->unk_03 == 0 && fn_8021DE9C(pEntry, Item) != 0) {
                fn_801F010C(pEntry->pData, Item);
                pItem->unk_02 = 0;
            }
        }
    }
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

void fn_8021E950(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
    fn_8021EE54(pRes, index, pBuffer, err, pUser);
}

Int32 fn_8021E970(Object_8021E688 *pObject, Int32 Index)
{
    Entry_8021E688 *pEntry;

    pEntry = &pObject->pA[Index];
    return pEntry->u.unk_0C;
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

void fn_8021E9AC(Object_8021E688 *pObject, Int32 Index, Entry_8021E688 *pEntry)
{
    if (pEntry->Flags != 0) {
        fn_8021ECFC(pObject, pEntry->Flags, Index);
        if (!(pEntry->Flags & 10) && pEntry->pData != NULL) {
            fn_801EEFAC(pEntry->pData);
            pEntry->pData = NULL;
        }
        if (pEntry->pItems != NULL) {
            fn_801D2BD0(pEntry->pItems);
        }
        pEntry->bItems = 0;
        pEntry->unk_18 = 0;
        pEntry->NumItems = 0;
        pEntry->pItems = NULL;
    }
}

void fn_8021EA34(Int32 Index, Object_8021E688 *pObject)
{
    lbl_803EBF38[Index] = pObject;
}

Object_8021E688 *fn_8021EA44(Int32 Index)
{
    return lbl_803EBF38[Index];
}

Int32 fn_8021EA54(Object_8021E688 *pObject, Int32 Index, Int32 Item)
{
    Entry_8021E688 *pEntry;
    Item_8021E688 *pItem;
    Int32 Result;

    pEntry = &pObject->pA[Index];
    pItem = &pEntry->pItems[Item];
    Result = 0;
    if ((pEntry->Flags & 0x10) && pItem->unk_04 == 0 && !(pEntry->Flags & 10) &&
        fn_801F0DB8(pEntry->pData, Item) != 0) {
        fn_8021EF04(Index, Item);
        fn_8021EF74(pEntry->Flags);
        Result = fn_801EF390(pEntry->pData, Item, pEntry->unk_00);
        fn_8021EFA4();
        fn_8021EF34();
    }
    if (pItem->unk_00 != 0) {
        fn_8021EBB4(pObject, pEntry->Flags, Index, Item, Result);
    }
    return pItem->unk_04;
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

void fn_8021EBB4(Object_8021E688 *pObject, Uint32 Flags, Int32 Index, Int32 Item, Int32 Value)
{
    fn_8021EF04(Index, Item);
    if (Flags & 4) {
        fn_80221374(pObject, Index, Item, Value);
    } else if (Flags & 8) {
        fn_80225E64(pObject, Index, Item, Value);
    } else if (Flags & 2) {
        fn_802261D4(pObject, Index, Item);
    }
    if ((Flags & 0x8A) == 0x80 && Value != 0 && pObject->pA[Index].pItems[Item].unk_03 == 0) {
        fn_801F010C(pObject->pA[Index].pData, Item);
        pObject->pA[Index].pItems[Item].unk_02 = 0;
    }
    fn_8021EF34();
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

void fn_8021EE54(void *pRes, unsigned int index, void *pBuffer, unsigned int err, void *pUser)
{
}

void fn_8021EE58(Object_8021E688 *pObject, Int32 a, Int32 b, Int32 c, Int32 d)
{
    Entry_8021E688 *pDst;
    Entry_8021E688 *pSrc;
    Item_8021E688 *pDstItem;
    Item_8021E688 *pSrcItem;
    Int32 Value;

    pDst = &pObject->pA[a];
    pSrc = &pObject->pA[c];
    Value = fn_8021E688(pObject, c, d);
    fn_8021E6A8(pObject, c, d, 0);
    fn_8021E6A8(pObject, a, b, Value);
    pSrcItem = &pSrc->pItems[d];
    pDstItem = &pDst->pItems[b];
    pSrcItem->unk_00--;
    pDstItem->unk_00++;
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

void fn_8021F550(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 2) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E2B4(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    pNode->unk_0C = pNode->unk_04;
    pNode->unk_0E = pNode->unk_06;
    fn_8021F8DC(pNode);
}

void fn_8021F5C0(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;
    Int32 Item = 0;

    if ((pNode->Flags & 2) && pNode->unk_06 != -1 && pNode->unk_04 != -1) {
        pObject = fn_8021EA44(1);
        if (fn_8021E924(pObject, pNode->unk_06) & 2) {
            fn_80226320(pObject, pNode->unk_06, pNode->unk_04);
        }
        if (pNode->unk_0C != -1 && pNode->unk_0E != -1 &&
            fn_8021EE10(pObject, pNode->unk_06, pNode->unk_04) == 0) {
            fn_802213F8(pObject, &pNode->unk_06, &pNode->unk_04, pNode->unk_0E, pNode->unk_0C);
            pNode->unk_0C = -1;
            pNode->unk_0E = -1;
        }
        Item = fn_8021EA54(pObject, pNode->unk_06, pNode->unk_04);
    }
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220C4C(pNode->unk_0A, pNode->unk_08, Item);
    }
    fn_8021F984(pNode, Item);
    if (Item != 0 && (pNode->Flags & 0x10) && pNode->unk_08 != -1 && pNode->unk_0A != -1) {
        fn_80220CA4(pNode->unk_0A, pNode->unk_08, Item);
    }
}

void fn_8021F71C(Node_80223874 *pNode)
{
    Object_8021E688 *pObject;

    if (pNode->Flags & 2) {
        pObject = fn_8021EA44(1);
        if (pNode->unk_06 != -1 && pNode->unk_04 != -1) {
            fn_8021E72C(pObject, pNode->unk_06, pNode->unk_04);
        }
    }
    fn_8021F954(pNode);
}

void fn_8021F8DC(Node_80223874 *pNode)
{
    Int32 i;

    if (pNode->Flags & 0x8000) {
        fn_802260B0(&pNode->u.List);
    } else if ((pNode->Flags & 3) == 2) {
        pNode->Flags |= 1;
        for (i = 0; i < 4; i++) {
            pNode->u.v.Colors[i].r = 255;
            pNode->u.v.Colors[i].g = 255;
            pNode->u.v.Colors[i].b = 255;
        }
    }
}

void fn_8021F954(Node_80223874 *pNode)
{
    if (pNode->Flags & 0x8000) {
        fn_802260C0(&pNode->u.List);
    }
}

void fn_8021F984(Node_80223874 *pNode, Int32 Item)
{
    Uint16 Flags;
    Int32 Mode;
    Int32 bTex = 0;
    Int32 bTexture;

    if ((pNode->Flags & 2) && Item == 0) {
        return;
    }
    Flags = pNode->Flags;
    fn_80210388();
    Mode = Flags & 3;
    fn_80220A08();
    lbl_803ECFF8 = -1;
    fn_80220988();
    if (Mode != lbl_803ECFF8) {
        bTexture = Flags & 2;
        fn_802218D4(Mode == 2 ? 0 : 1);
        fn_80221924(bTexture);
        lbl_803ECFF8 = Mode;
    }
    GXSetCullMode((Flags & 4) ? GX_CULL_BACK : GX_CULL_NONE);
    GXLoadPosMtxImm((f32 (*)[4])fn_801D0444(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    if (pNode->Flags & 2) {
        lbl_802F9FA0[0][0] = ((Node_802215F0 *)Item)->unk_30;
        lbl_802F9FA0[1][1] = ((Node_802215F0 *)Item)->unk_34;
        GXLoadTexMtxImm(lbl_802F9FA0, GX_TEXMTX0, GX_MTX2x4);
        if (!(pNode->Flags & 0x8000)) {
            fn_80220AD0(pNode, 0, Item);
        }
        bTex = fn_8022179C(Item);
    }
    if (pNode->Flags & 0x8000) {
        fn_802260D0(&pNode->u.List);
    } else {
        if (pNode->Flags & 8) {
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 10);
        } else {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        }
        if (pNode->Flags & 2) {
            fn_8021FB30(pNode);
        } else {
            fn_80220310(pNode);
        }
    }
    GXSetCullMode(GX_CULL_NONE);
    if (bTex) {
        GXSetNumIndStages(0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    }
}

void fn_80220988(void)
{
    Color_80223C4C *pColor;
    ColorWord_80220988 Mat;
    ColorWord_80220988 Light;

    pColor = fn_80220D34();
    Mat.Color = pColor->unk_20;
    Light.Color = pColor->unk_24;
    if (Mat.Value != lbl_803ECFF0 || Light.Value != lbl_803ECFF4) {
        GXSetChanMatColor(GX_COLOR0A0, Mat.Color);
        GXInitLightColor(&lbl_803E9880, Light.Color);
        fn_8024F9EC(&lbl_803E9880, GX_LIGHT7);
        lbl_803ECFF0 = Mat.Value;
        lbl_803ECFF4 = Light.Value;
    }
}

void fn_80220A08(void)
{
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 4);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 8);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_FALSE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    lbl_803ECFF4 = lbl_803ECFF0 = 0x12345678;
}

void fn_80220AD0(Node_80223874 *pNode, Int32 a, Int32 Item)
{
    Int32 First = 0;
    Int32 Second = 0;
    Int32 i;

    if (a != 0) {
        First = 1;
        Second = 1;
    } else {
        for (i = 0; i < 4; i++) {
            if (pNode->u.v.Coords[i][0] > 256) {
                First = 1;
            }
            if (pNode->u.v.Coords[i][1] > 256) {
                Second = 1;
            }
        }
    }
    fn_802219F0(First, Second);
}

Int32 fn_80220B4C(Int32 a, Int32 b)
{
    Object_8021E688 *pObject;

    Int32 Result;

    pObject = fn_8021EA44(1);
    Result = 0;
    if (pObject != NULL) {
        if (lbl_803ED008 == 0 || lbl_803ED004 != pObject || lbl_803ECFFC != a || lbl_803ED000 != b) {
            lbl_803ED008 = fn_8021E2B4(pObject, a, b);
            lbl_803ED004 = pObject;
            lbl_803ECFFC = a;
            lbl_803ED000 = b;
        }
        Result = lbl_803ED008;
    }
    return Result;
}

void fn_80220BE0(void)
{
    lbl_803ED008 = 0;
    lbl_803ECFFC = -1;
    lbl_803ED004 = NULL;
    lbl_803ED000 = -1;
}

Int32 fn_80220BFC(Int32 a, Int32 b)
{
    Object_8021E688 *pObject;

    pObject = fn_8021EA44(1);
    if (pObject == NULL) {
        return 0;
    }
    return fn_8021E2B4(pObject, a, b);
}

void fn_80220C4C(Int32 a, Int32 b, Int32 c)
{
    Int32 p;

    lbl_803EBF48 = fn_80221570((struct Node_802215F0 *)c);
    p = fn_80220BFC(a, b);
    if (p != 0) {
        fn_80221590((struct Node_802215F0 *)c, (unsigned short *)p);
    }
}

void fn_80220CA4(Int32 a, Int32 b, Int32 c)
{
    if (lbl_803EBF48 != NULL) {
        fn_80221590((struct Node_802215F0 *)c, lbl_803EBF48);
    }
    lbl_803EBF48 = NULL;
}

void fn_80220CDC(Int32 a)
{
    lbl_803EBF54 = a;
}

Int32 fn_80220CE4(void)
{
    if (lbl_803EBF5C == 0) {
        return 0;
    }
    return lbl_803EBF54;
}

void fn_80220CFC(Int32 a)
{
    lbl_803EBF58 = a;
}

void fn_80220D04(void)
{
    fn_80220D3C();
    fn_80220CDC(0);
    fn_80220CFC(0);
}

void *fn_80220D34(void)
{
    return lbl_803EBF50;
}

void fn_80221118(void)
{
    lbl_803ED00C--;
    lbl_803EBF50--;
    fn_80220CFC(0);
}
