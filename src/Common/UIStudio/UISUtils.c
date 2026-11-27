/* UI Studio helpers (EA file name UISUtils.c): screen and event-code lookup, running a
   script function, the transform and colour accessors, the script text formatter,
   control focus helpers, screen ordering and hints. */

#include <string.h>

#include "UIStudio/UIStudio.h"
#include "engine/cu_8021A438.h"

static Float32 _UISUtils_afColorMultiplier[4];
static Float32 _UISUtils_afColorAdditive[4];

Uint32 UISFindScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
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

Int32 UISFindEventPC(UISControlT *pControl, Uint32 ID)
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

Int32 UISFindSubControlEventPC(UISControlT *pControl, Int32 Flags, Uint32 ID)
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

Int32 _UISFindHintPC(UISControlT *pControl, Uint32 ID)
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

Int32 UISExecuteFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlStateT *pControlState,
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
    pState->pCode = (Uint8 *)Value;
    pState->pTop++;
    Result = UISStackProcess(pInfo, pFrame, pState, pScreen, pControlState);
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

Float32 *UISGetColorMultipler(void)
{
    return _UISUtils_afColorMultiplier;
}

Float32 *UISGetColorAdditive(void)
{
    return _UISUtils_afColorAdditive;
}

void UISSetColorMultipler(Float32 a, Float32 b, Float32 c, Float32 d)
{
    _UISUtils_afColorMultiplier[0] = a;
    _UISUtils_afColorMultiplier[3] = d;
    _UISUtils_afColorMultiplier[1] = b;
    _UISUtils_afColorMultiplier[2] = c;
}

void UISSetColorAdditive(Float32 a, Float32 b, Float32 c, Float32 d)
{
    _UISUtils_afColorAdditive[0] = a;
    _UISUtils_afColorAdditive[3] = d;
    _UISUtils_afColorAdditive[1] = b;
    _UISUtils_afColorAdditive[2] = c;
}

/* Writes Value in decimal to pDst, stopping at pEnd; returns the end of the
   written text. */
char *_WriteInt(Uint32 Value, char *pDst, char *pEnd, char Pad, Int32 Width, Int32 bSigned)
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

char *_WriteFloat(char *pDst, char *pEnd, Int32 Width, Int32 Precision, Float32 Value)
{
    char Buffer[64];
    Int32 Length;
    Int32 bNegative;
    Int32 Count;
    Int32 Digit;
    Float32 Round;
    Float32 Fraction;
    Float32 Tenth;

    Length = 0;
    if (Precision < 0) {
        Precision = 6;
    }
    bNegative = Value < 0.0f;
    if (bNegative) {
        Value = -Value;
    }
    Round = 0.5f;
    for (Count = 0; Count < Precision; Count++) {
        Round *= 0.1f;
    }
    Value += Round;
    Fraction = Value - (Int32)Value;
    do {
        Tenth = Value * 0.1f;
        Buffer[Length++] = (Int32)(Value - (Int32)Tenth * 10) + '0';
        Value = Tenth;
    } while (Value >= 1.0f);
    if (bNegative) {
        Buffer[Length++] = '-';
    }
    if (Width != 0) {
        Count = (Precision != 0 ? Width - 1 : Width) - (Precision + Length);
        for (; Count > 0; Count--) {
            Buffer[Length++] = ' ';
        }
    }
    for (Length--; Length >= 0 && pDst < pEnd; Length--) {
        *pDst++ = Buffer[Length];
    }
    if (Precision != 0 && pDst < pEnd) {
        *pDst++ = '.';
        do {
            Fraction *= 10.0f;
            Digit = (Int32)Fraction;
            *pDst++ = Digit + '0';
            Fraction -= Digit;
        } while (--Precision != 0 && pDst < pEnd);
    }
    return pDst;
}

/* Writes Value in hexadecimal; Case selects the letter case of the digits. */
char *_WriteHex(Uint32 Value, char *pDst, char *pEnd, Int32 Width, char Pad, Int32 Case)
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
char *_WriteString(const char *pString, char *pDst, char *pEnd, Int32 Width, Int32 Precision,
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
    while (*pString != 0) {
        if (pDst == pEnd) {
            break;
        }
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

Int32 UISSprintf(char *pDst, Uint32 Size, const char *pFormat, Int32 a, Int32 *pArgs)
{
    Int32 *pParam;
    char *pOut;
    char *pStart;
    char *pEnd;
    char *pString;
    Int32 bLeft;
    Int32 bUnsigned;
    Int32 Width;
    Int32 Precision;
    Int32 Case;
    char Pad;
    char c;

    pOut = pDst;
    pStart = pOut;
    bLeft = 0;
    pEnd = pStart + Size;
    if (pStart == NULL || Size == 0 || pFormat == NULL) {
        return -1;
    }
    if ((c = *pFormat++) != 0 && pOut < pEnd) {
        pParam = pArgs;
        do {
        if (c == '%') {
            bUnsigned = 0;
            Width = 0;
            Precision = -1;
            Pad = ' ';
            c = *pFormat++;
            if (c == '-') {
                bLeft = 1;
                c = *pFormat++;
            }
            if (c == '0') {
                Pad = '0';
                c = *pFormat++;
            }
            while (c >= '0' && c <= '9') {
                Width = Width * 10 + c - '0';
                c = *pFormat++;
            }
            if (c == '.') {
                c = *pFormat++;
            }
            if (c >= '0' && c <= '9') {
                Precision = c - '0';
                c = *pFormat++;
                while (c >= '0' && c <= '9') {
                    Precision = Precision * 10 + c - '0';
                    c = *pFormat++;
                }
            }
            Case = 0;
            if (c >= 'A' && c <= 'Z') {
                Case = -32;
            }
            switch (c) {
            case 'c':
                *pOut++ = *pParam++;
                break;
            case 's':
                pString = ((UIGTextBuffer_t *)*pParam++)->pText;
                if (pString != NULL) {
                    pOut = _WriteString(pString, pOut, pEnd, Width, Precision, bLeft);
                } else {
                    pOut = _WriteString("(null)", pOut, pEnd, Width, Precision, bLeft);
                }
                break;
            case 'u':
                bUnsigned = 1;
            case 'd':
            case 'i':
                pOut = _WriteInt(*pParam++, pOut, pEnd, Pad, Width, bUnsigned ^ 1);
                break;
            case 'f':
                pOut = _WriteFloat(pOut, pEnd, Width, Precision, *(Float32 *)pParam++);
                break;
            case 'X':
            case 'p':
            case 'x':
                pOut = _WriteHex(*pParam++, pOut, pEnd, Width, Pad, Case);
                break;
            default:
                if (c != 0) {
                    *pOut++ = c;
                }
                break;
            }
        } else if (c != 0) {
            *pOut++ = c;
        }
        } while ((c = *pFormat++) != 0 && pOut < pEnd);
    }
    *pOut = 0;
    return pOut - pStart;
}

void UISStringFormat(void *p, UIGTextBuffer_t *pDst, UIGTextBuffer_t *pFormat, Int32 a, Int32 *pArgs)
{
    if (pFormat != NULL && pDst != NULL) {
        UISSprintf(pDst->pText, pDst->Size, pFormat->pText, a, pArgs);
    }
}

Int32 _IsChildOfControl(UISScreenDataT *pData, UISControlT *pControl, UISControlStateT *pState)
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

UISControlStateT *_GetFirstEnableControl(UISScreenDataT *pData, UISControlT *pControl)
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

UISControlStateT *UISFindSiblingEnableControl(UISScreenT *pScreen, UISControlStateT *pState)
{
    UISScreenDataT *pData;
    Uint32 Control;
    UISControlT *pControl;

    pData = pScreen->pData;
    for (Control = 0; Control < pData->NumControls; Control++) {
        pControl = &pData->pControls[Control];
        if (_IsChildOfControl(pData, pControl, pState)) {
            return _GetFirstEnableControl(pData, pControl);
        }
    }
    return 0;
}

/* Moves the given screen Delta places through the screen table, keeping
   the active index and screen pointers pointing at the same screens. */
void UISMoveScreenDrawPosition(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Delta)
{
    UISScreenT Temp;
    Int32 Screen;
    Int32 Previous;
    Int32 NumScreens;
    Int32 Count;
    Int32 Step;
    Uint32 Rate;
    Uint32 Ref;

    Screen = UISFindScreen(pInfo, GroupID, ScreenID);
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

void _ParseHints(UISInfoT *pInfo, UISScreenT *pScreen, UISRunStateT *pState, Int32 Control,
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
            _ParseHints(pInfo, pScreen, pState, pItem->Value, ID, Count, pArgs);
        }
    }
    Value = _UISFindHintPC(pControl, ID);
    if (Value != 0) {
        UISExecuteFnc(pInfo, pScreen, pControl->pState, pState, Value, Count, pArgs, 0, 0, 0, 0,
                    0);
    }
}

void UISDoHint(UISInfoT *pInfo, Int32 Value, Int32 Count, Int32 *pArgs)
{
    Uint32 Screen;
    Uint32 NumScreens;
    UISScreenT *pScreen;

    NumScreens = pInfo->NumScreens;
    for (Screen = 0; Screen < NumScreens; Screen++) {
        pScreen = &pInfo->Screens[Screen];
        if (pScreen->bWaitingToBeUnloaded == 0) {
            pInfo->Flags |= 2;
            _ParseHints(pInfo, pScreen, &pInfo->RunState, 0, Value, Count, pArgs);
            pInfo->Flags &= ~2;
        }
    }
}

void UISProcessHint(UISInfoT *pInfo, Int32 Value, Int32 Count, Int32 *pArgs)
{
    UISThreadActionT Action;
    Int16 GroupID;
    Int16 ScreenID;

    if (pInfo->Flags & 6) {
        GroupID = pInfo->Screens[pInfo->ActiveScreen].GroupID;
        ScreenID = pInfo->Screens[pInfo->ActiveScreen].ScreenID;
        Action.Words[0] = Value;
        UISAddThreadAction(GroupID, ScreenID, pInfo, 9, &Action, Count, pArgs);
    } else {
        UISDoHint(pInfo, Value, Count, pArgs);
    }
}

Int32 UISAreEventsEnabled(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID)
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
