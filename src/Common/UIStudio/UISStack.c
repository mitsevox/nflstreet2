/* UI Studio script interpreter (EA file name UISStack.c): runs a screen's byte code on
   the word stack of its run state, turning script offsets into code pointers. */

#include <string.h>

#include "UIStudio/UIStudio.h"
#include "engine/cu_8021A438.h"

void *_UISPatchFncPC(UISInfoT *pInfo, Uint8 *pBase, Int32 Offset)
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

double fabs(double);

typedef void UISMessageFncT(Int32 Message, Uint16 GroupID, Uint16 ScreenID, Int32 Count,
                            Int32 *pArgs, Int32 *pResult);

void UISStringFormat(void *p, UIGTextBuffer_t *pDst, UIGTextBuffer_t *pFormat, Int32 a, Int32 *pArgs);

extern Int32 lbl_8039F808[20];

#define UIS_FLOAT(Word) (*(Float32 *)&(Word))
#define UIS_EPSILON 1e-7f

Int32 UISStackProcess(UISInfoT *pInfo, Int32 *pFrame, UISRunStateT *pState, UISScreenT *pScreen,
                  UISControlStateT *pControlState)
{
    UISThreadActionT Action;
    Uint16 CurGroupID;
    Uint16 CurScreenID;
    Int32 Index;
    Int32 Param;
    Uint8 **ppCode;
    Int32 **ppTop;
    Int32 *pTop;
    Uint8 Op;

    while (pState->pCode != NULL) {
        ppCode = &pState->pCode;
        ppTop = &pState->pTop;
        pTop = pState->pTop;
        Op = *pState->pCode;
        pState->pCode++;
        switch (Op) {
        case 1:
        case 106:
            break;
        case 2:
        case 113: {
            Uint8 NumArgs;
            Int32 *pArgs;
            Uint32 ID;

            NumArgs = **ppCode;
            (*ppCode)++;
            pArgs = *ppTop - NumArgs;
            ID = pArgs[-1];
            Action.s.GroupID = ID;
            Action.s.ScreenID = ID >> 16;
            Action.s.unk_04 = pScreen->GroupID;
            Action.s.unk_06 = pScreen->ScreenID;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 0, &Action, NumArgs, pArgs);
            while (NumArgs-- != 0) {
                (*ppTop)--;
            }
            (*ppTop)--;
            break;
        }
        case 3: {
            Int32 Value;
            Uint32 ID;
            Uint16 Group;
            Uint16 Screen;

            Value = *--pState->pTop;
            ID = *--pState->pTop;
            Group = ID;
            Screen = ID >> 16;
            if (Group == 0xFFFF) {
                Group = pScreen->GroupID;
                Screen = pScreen->ScreenID;
            }
            Action.s.GroupID = Group;
            Action.s.ScreenID = Screen;
            Action.s.unk_08 = Value;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 1, &Action, 0, NULL);
            break;
        }
        case 8: {
            Uint32 ID;
            Uint16 Group;
            Uint16 Screen;

            ID = *--*ppTop;
            Group = ID;
            Screen = ID >> 16;
            if (Group == 0xFFFF) {
                Group = pScreen->GroupID;
                Screen = pScreen->ScreenID;
            }
            Action.s.GroupID = Group;
            Action.s.ScreenID = Screen;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 3, &Action, 0, NULL);
            break;
        }
        case 88: {
            Uint8 NumArgs;
            UISControlInfoT *pControlInfo;
            UISControlInfoT *pSubControlInfo;
            Uint8 *pEndFnc;
            Uint8 *pAcelFnc;
            Int32 Offset;
            Uint32 MSDur;
            Float32 TargValue;
            Uint32 AnimType;
            Uint32 RateFncID;

            NumArgs = **ppCode;
            (*ppCode)++;
            pEndFnc = NULL;
            pAcelFnc = NULL;
            pControlInfo = (UISControlInfoT *)*--*ppTop;
            pSubControlInfo = (UISControlInfoT *)*--*ppTop;
            if (NumArgs > 4) {
                if (NumArgs > 5) {
                    Offset = *--*ppTop;
                    if (Offset != 0) {
                        pAcelFnc = _UISPatchFncPC(pInfo, (Uint8 *)pScreen->pData, Offset);
                    } else {
                        pAcelFnc = NULL;
                    }
                }
                Offset = *--*ppTop;
                if (Offset != 0) {
                    pEndFnc = _UISPatchFncPC(pInfo, (Uint8 *)pScreen->pData, Offset);
                } else {
                    pEndFnc = NULL;
                }
            }
            MSDur = *--*ppTop;
            TargValue = UIS_FLOAT(*--*ppTop);
            AnimType = *--*ppTop;
            RateFncID = *--*ppTop;
            UISLoadAdvRateFnc(pInfo, pScreen, pControlInfo, pSubControlInfo, RateFncID, pEndFnc,
                              pAcelFnc, MSDur, TargValue, AnimType);
            break;
        }
        case 6: {
            UISControlInfoT *pControlInfo;
            Uint32 MSRate;
            Uint8 *pFnc;

            pControlInfo = (UISControlInfoT *)*--*ppTop;
            MSRate = *--*ppTop;
            pFnc = _UISPatchFncPC(pInfo, (Uint8 *)pScreen->pData, *--*ppTop);
            UISLoadRateFnc(pInfo, pScreen, pControlInfo, *--*ppTop, pFnc, MSRate);
            break;
        }
        case 7: {
            UISControlInfoT *pControlInfo;

            pControlInfo = (UISControlInfoT *)*--*ppTop;
            UISUnloadRateFnc(pInfo, pControlInfo, *--*ppTop);
            break;
        }
        case 10: {
            Int32 Count;
            Int32 Fnc;
            Int32 Value;
            Int32 *pOffset;
            void *pObject;
            Int32 *pArgs;

            Count = *--pState->pTop;
            Fnc = *--pState->pTop;
            Value = *--pState->pTop;
            pOffset = (Int32 *)*--pState->pTop;
            if (pOffset != NULL) {
                pObject = (Uint8 *)pScreen->pData + *pOffset;
            } else {
                pObject = NULL;
            }
            pArgs = *ppTop - Count;
            pInfo->ActionFncs[Fnc].pFnc(pObject, Value, Count, pArgs, (Int32)(pArgs - 1));
            break;
        }
        case 118: {
            Int32 Count;
            Int32 *pArgs;

            Count = *--*ppTop;
            (*ppTop)--;
            pArgs = *ppTop - Count;
            Action.Words[0] = *pArgs;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 9, &Action, Count, pArgs + 1);
            break;
        }
        case 11: {
            Int32 Count;
            Int32 *pArgs;
            Uint8 *pCode;

            Count = *--*ppTop;
            (*ppTop)--;
            pArgs = *ppTop - Count;
            pCode = *ppCode;
            ((UISMessageFncT *)pInfo->pMessageFnc)(*pArgs, pScreen->GroupID, pScreen->ScreenID,
                                                  Count, pArgs + 1, pArgs - 1);
            *ppCode = pCode;
            break;
        }
        case 12: {
            Int32 Count;

            Count = *--*ppTop;
            Action.Words[0] = *--*ppTop;
            Action.Words[1] = *--*ppTop;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 7, &Action, Count,
                        *ppTop - Count);
            break;
        }
        case 13:
            *pState->pTop = (Int32)pScreen->pData;
            pState->pTop++;
            break;
        case 14: {
            UISStringT *pDst;
            UISStringT *pSrc;
            Uint32 Length;

            pDst = (UISStringT *)*--*ppTop;
            pSrc = (UISStringT *)*--*ppTop;
            if (pSrc != NULL && pDst != NULL) {
                Length = pSrc->Length;
                if (pDst->Length < Length) {
                    Length = pDst->Length;
                }
                strncpy(pDst->pText, pSrc->pText, Length);
                pDst->pText[Length] = 0;
            }
            break;
        }
        case 15:
        case 16: {
            Int32 Value;

            Value = **ppCode << 24;
            (*ppCode)++;
            Value |= **ppCode << 16;
            (*ppCode)++;
            Value |= **ppCode << 8;
            (*ppCode)++;
            Value |= **ppCode;
            (*ppCode)++;
            **ppTop = Value;
            (*ppTop)++;
            break;
        }
        case 17: {
            Int32 Value;

            Value = *pState->pCode << 24;
            pState->pCode++;
            Value |= *pState->pCode << 16;
            pState->pCode++;
            Value |= *pState->pCode << 8;
            pState->pCode++;
            Value |= *pState->pCode;
            pState->pCode++;
            *pState->pTop = Value;
            pState->pTop++;
            break;
        }
        case 18:
            pTop[-1] = (Int32)UIS_FLOAT(pTop[-1]);
            break;
        case 19:
            UIS_FLOAT(pTop[-1]) = (Float32)pTop[-1];
            break;
        case 20:
            pTop[-2] = (Int32)UIS_FLOAT(pTop[-2]);
            break;
        case 21:
            UIS_FLOAT(pTop[-2]) = (Float32)pTop[-2];
            break;
        case 24:
            pTop[-1] = *(Int32 *)pTop[-1];
            break;
        case 25:
            *(Int32 *)pTop[-1] = pTop[-2];
            *ppTop -= 2;
            break;
        case 105:
            pTop[-1] = (Int32)&pTop[pTop[-1] - 1];
            break;
        case 26:
            pTop[-1] = pTop[pTop[-1] - 1];
            break;
        case 27:
            pTop[pTop[-1] - 1] = pTop[-2];
            *ppTop -= 2;
            break;
        case 28: {
            Int32 Value;
            Int32 Value2;

            Value = *--*ppTop;
            Value2 = *--*ppTop;
            **ppTop = Value & Value2;
            (*ppTop)++;
            break;
        }
        case 29: {
            Int32 Value;
            Int32 Value2;

            Value = *--*ppTop;
            Value2 = *--*ppTop;
            **ppTop = Value | Value2;
            (*ppTop)++;
            break;
        }
        case 30: {
            Int32 Value;

            Value = *--pState->pTop;
            *pState->pTop = ~Value;
            pState->pTop++;
            break;
        }
        case 31: {
            Int32 Value;
            Int32 Value2;

            Value = *--*ppTop;
            Value2 = *--*ppTop;
            **ppTop = Value && Value2;
            (*ppTop)++;
            break;
        }
        case 32: {
            Int32 Value;
            Int32 Value2;

            Value = *--*ppTop;
            Value2 = *--*ppTop;
            **ppTop = Value || Value2;
            (*ppTop)++;
            break;
        }
        case 33: {
            Int32 Value;

            Value = *--*ppTop;
            **ppTop = !Value;
            (*ppTop)++;
            break;
        }
        case 34:
            pTop[-1] = pTop[-1] < 0 ? -pTop[-1] : pTop[-1];
            break;
        case 35: {
            Float32 Value;

            Value = UIS_FLOAT(*--*ppTop);
            UIS_FLOAT(**ppTop) = fabs(Value);
            (*ppTop)++;
            break;
        }
        case 36:
            (*ppTop)[-1] = -pTop[-1];
            break;
        case 37:
            pTop[-2] = pTop[-2] + pTop[-1];
            pState->pTop--;
            break;
        case 38:
            (*ppTop)[-2] = (*ppTop)[-2] - (*ppTop)[-1];
            (*ppTop)--;
            break;
        case 39:
            pTop[-2] = pTop[-2] * pTop[-1];
            (*ppTop)--;
            break;
        case 40:
            pTop[-2] = pTop[-2] / pTop[-1];
            (*ppTop)--;
            break;
        case 90:
            pTop[-2] = pTop[-2] % pTop[-1];
            (*ppTop)--;
            break;
        case 41: {
            Float32 Value;

            Value = UIS_FLOAT(*--pState->pTop);
            UIS_FLOAT(*pState->pTop) = -Value;
            pState->pTop++;
            break;
        }
        case 42:
            UIS_FLOAT(pTop[-2]) = UIS_FLOAT(pTop[-2]) + UIS_FLOAT(pTop[-1]);
            (*ppTop)--;
            break;
        case 43:
            UIS_FLOAT(pTop[-2]) = UIS_FLOAT(pTop[-2]) - UIS_FLOAT(pTop[-1]);
            (*ppTop)--;
            break;
        case 44:
            UIS_FLOAT(pTop[-2]) = UIS_FLOAT(pTop[-2]) * UIS_FLOAT(pTop[-1]);
            (*ppTop)--;
            break;
        case 45:
            UIS_FLOAT(pTop[-2]) = UIS_FLOAT(pTop[-2]) / UIS_FLOAT(pTop[-1]);
            pState->pTop--;
            break;
        case 46:
            pTop[-1]++;
            break;
        case 47:
            pTop[-1]--;
            break;
        case 48:
            UIS_FLOAT(pTop[-1]) += 1.0f;
            break;
        case 49:
            UIS_FLOAT(pTop[-1]) -= 1.0f;
            break;
        case 50:
            pTop[-2] = pTop[-1] <= pTop[-2];
            (*ppTop)--;
            break;
        case 51:
            pTop[-2] = pTop[-1] >= pTop[-2];
            (*ppTop)--;
            break;
        case 52:
            pTop[-2] = pTop[-1] < pTop[-2];
            pState->pTop--;
            break;
        case 53:
            pTop[-2] = pTop[-1] > pTop[-2];
            (*ppTop)--;
            break;
        case 54:
            pTop[-2] = pTop[-1] == pTop[-2];
            (*ppTop)--;
            break;
        case 55:
            pTop[-2] = pTop[-1] != pTop[-2];
            (*ppTop)--;
            break;
        case 56:
            pTop[-2] = UIS_FLOAT(pTop[-1]) <= UIS_FLOAT(pTop[-2]) + UIS_EPSILON;
            pState->pTop--;
            break;
        case 57:
            pTop[-2] = UIS_FLOAT(pTop[-1]) >= UIS_FLOAT(pTop[-2]) - UIS_EPSILON;
            (*ppTop)--;
            break;
        case 58:
            pTop[-2] = UIS_FLOAT(pTop[-1]) < UIS_FLOAT(pTop[-2]) - UIS_EPSILON;
            (*ppTop)--;
            break;
        case 59:
            pTop[-2] = UIS_FLOAT(pTop[-1]) > UIS_FLOAT(pTop[-2]) + UIS_EPSILON;
            (*ppTop)--;
            break;
        case 60:
            pTop[-2] = (Float32)fabs(UIS_FLOAT(pTop[-1]) - UIS_FLOAT(pTop[-2])) <= UIS_EPSILON;
            pState->pTop--;
            break;
        case 61:
            pTop[-2] = (Float32)fabs(UIS_FLOAT(pTop[-1]) - UIS_FLOAT(pTop[-2])) > UIS_EPSILON;
            (*ppTop)--;
            break;
        case 62: {
            Int32 Offset;

            Offset = *--*ppTop;
            if (*--*ppTop != 0) {
                *ppCode += Offset;
            }
            break;
        }
        case 63: {
            Int32 Offset;

            Offset = *--*ppTop;
            if (*--*ppTop == 0) {
                *ppCode += Offset;
            }
            break;
        }
        case 64: {
            Int32 Offset;

            Offset = *--pState->pTop;
            pState->pCode += Offset;
            break;
        }
        case 65:
            *pTop = pTop[-1];
            (*ppTop)++;
            break;
        case 66:
            (*ppTop)--;
            break;
        case 67: {
            Int32 Offset;

            Offset = *pState->pCode << 24;
            pState->pCode++;
            Offset |= *pState->pCode << 16;
            pState->pCode++;
            Offset |= *pState->pCode << 8;
            pState->pCode++;
            Offset |= *pState->pCode;
            pState->pCode++;
            *pState->pTop = (Int32)pState->pCode;
            pState->pTop++;
            pState->pCode = _UISPatchFncPC(pInfo, (Uint8 *)pScreen->pData, Offset);
            break;
        }
        case 68:
            *ppCode = (Uint8 *)*--*ppTop;
            break;
        case 69: {
            Uint8 NumArgs;
            Int32 *pOffset;
            Uint32 ID;

            NumArgs = **ppCode;
            (*ppCode)++;
            pOffset = (Int32 *)*--*ppTop;
            ID = *(Int32 *)((Uint8 *)pScreen->pData + *pOffset);
            if (ID != 0xFFFFFFFF) {
                Action.s.GroupID = ID;
                Action.s.ScreenID = ID >> 16;
                Action.s.unk_04 = pScreen->GroupID;
                Action.s.unk_06 = pScreen->ScreenID;
                UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 0, &Action, NumArgs,
                            *ppTop - NumArgs);
                UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 3, &Action, 0, NULL);
                while (NumArgs-- != 0) {
                    (*ppTop)--;
                }
            }
            break;
        }
        case 70: {
            Int32 Value;

            Value = *--*ppTop;
            Action.s.GroupID = 0;
            Action.s.ScreenID = 0;
            Action.Words[1] = 0;
            Action.Words[2] = Value;
            Action.s.unk_0E = pScreen->GroupID;
            Action.s.unk_0C = pScreen->ScreenID;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 6, &Action, 0, NULL);
            break;
        }
        case 71: {
            Int32 Value;
            Int32 *pOffset;
            Int32 *pList;
            void *pObject;

            Value = *--pState->pTop;
            pOffset = (Int32 *)*--pState->pTop;
            Index = *--pState->pTop;
            pList = (Int32 *)((Uint8 *)pScreen->pData + *pOffset);
            if (Index < pList[0]) {
                pObject = (Uint8 *)pScreen->pData + pList[Index + 2];
                if (pObject != pControlState || pControlState->bEnabled == 0) {
                    Action.s.GroupID = Value;
                    Action.s.ScreenID = 0;
                    Action.Words[1] = (Int32)pList;
                    Action.Words[2] = (Int32)pObject;
                    Action.s.unk_0E = pScreen->GroupID;
                    Action.s.unk_0C = pScreen->ScreenID;
                    UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 5, &Action, 1, &Index);
                }
            }
            break;
        }
        case 72:
            Action.s.GroupID = pScreen->ParentGroupID;
            Action.s.ScreenID = pScreen->ParentScreenID;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 3, &Action, 0, NULL);
            break;
        case 73: {
            UISStringT *pString;

            pString = (UISStringT *)*--*ppTop;
            if (pString != NULL) {
                (*ppTop)[-1] = strlen(pString->pText);
            } else {
                (*ppTop)[-1] = 0;
            }
            break;
        }
        case 74: {
            Uint32 Pos;
            UISStringT *pString;
            Int32 Value;

            Pos = *--*ppTop;
            pString = (UISStringT *)*--*ppTop;
            Value = 0;
            if (pString != NULL && Pos < pString->Length) {
                Value = (signed char)pString->pText[Pos];
            }
            (*ppTop)[-1] = Value;
            break;
        }
        case 75: {
            Int32 Value;
            Uint32 Pos;
            UISStringT *pString;

            Value = *--pState->pTop;
            Pos = *--pState->pTop;
            pString = (UISStringT *)*--pState->pTop;
            if (pString != NULL && Pos < pString->Length) {
                pString->pText[Pos] = Value;
            }
            break;
        }
        case 76: {
            Uint32 Count;
            Uint32 i;
            UIGTextBuffer_t *pFormat;

            Count = *--*ppTop;
            for (i = 0; i < Count; i++) {
                if (i < 20) {
                    lbl_8039F808[Count - 1 - i] = *--*ppTop;
                } else {
                    (*ppTop)--;
                }
            }
            pFormat = (UIGTextBuffer_t *)*--*ppTop;
            UISStringFormat(pScreen->pData, (UIGTextBuffer_t *)*--*ppTop, pFormat, Count, lbl_8039F808);
            break;
        }
        case 119: {
            Int32 Value;

            Value = *--pState->pTop;
            if (Value == pScreen->GroupID) {
                pState->pTop[-1] = 1;
            } else {
                pState->pTop[-1] = 0;
            }
            break;
        }
        case 120:
            fn_80219650(pInfo, &CurGroupID, &CurScreenID);
            (*ppTop)[-1] = (CurScreenID << 16) | CurGroupID;
            break;
        case 77:
            Param = *--*ppTop;
            Action.Words[0] = *--*ppTop;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 2, &Action, 1, &Param);
            break;
        case 78:
            *ppCode += 4;
            break;
        case 82: {
            Int32 Value;

            Value = pTop[-1];
            pTop[-1] = pTop[-2];
            pState->pTop[-2] = Value;
            break;
        }
        case 79:
            pScreen->unk_00 = 0;
            break;
        case 80:
            pScreen->unk_00 = -1;
            break;
        case 81:
        case 112: {
            Uint8 NumArgs;
            Uint32 Ref;
            Int32 *pArgs;
            Uint32 ID;
            UISScreenRefT *pRef;

            NumArgs = **ppCode;
            (*ppCode)++;
            Ref = pInfo->NumScreenRefs;
            if (Ref < pInfo->MaxScreenRefs) {
                pArgs = *ppTop - NumArgs;
                ID = pArgs[-1];
                Action.s.GroupID = ID;
                Action.s.ScreenID = ID >> 16;
                Action.s.unk_04 = pScreen->GroupID;
                Action.s.unk_06 = pScreen->ScreenID;
                UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 0, &Action, NumArgs, pArgs);
                while (NumArgs-- != 0) {
                    (*ppTop)--;
                }
                (*ppTop)--;
                pRef = &pInfo->ScreenRefs[Ref];
                pRef->StackState.pCode = *ppCode;
                pRef->StackState.pTop = *ppTop;
                pRef->StackState.pStackCurrent = pState->pStackCurrent;
                pRef->StackState.pStackEnd = pState->pStackEnd;
                pRef->StackState.pStackStart = pState->pStackStart;
                pRef->pRestoreStack = pFrame;
                pRef->pRestoreState = pState;
                pState->pStackCurrent = pRef->StackState.pTop;
                pRef->GroupID = Action.s.GroupID;
                pRef->ScreenID = Action.s.ScreenID;
                pRef->pControlState = pControlState;
                pRef->pScreen = pScreen;
                pInfo->NumScreenRefs++;
                return 3;
            }
            while (NumArgs-- != 0) {
                (*ppTop)--;
            }
            break;
        }
        case 84:
        case 126: {
            Int32 Value;

            Value = *--*ppTop;
            Action.s.GroupID = 0;
            Action.s.ScreenID = 0;
            Action.Words[1] = 0;
            Action.Words[2] = Value;
            Action.s.unk_0E = pScreen->GroupID;
            Action.s.unk_0C = pScreen->ScreenID;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 5, &Action, 0, NULL);
            break;
        }
        case 85:
        case 107: {
            Int32 Value;
            Int32 Offset;

            Value = **ppCode << 24;
            (*ppCode)++;
            Value |= **ppCode << 16;
            (*ppCode)++;
            Value |= **ppCode << 8;
            (*ppCode)++;
            Value |= **ppCode;
            (*ppCode)++;
            Offset = **ppCode << 8;
            (*ppCode)++;
            Offset |= **ppCode;
            (*ppCode)++;
            Value += (*ppTop)[(Int16)Offset];
            if (Op == 107) {
                **ppTop = Value;
            } else {
                **ppTop = *(Int32 *)Value;
            }
            (*ppTop)++;
            break;
        }
        case 86: {
            Int32 Value;
            Int32 Offset;

            Value = **ppCode << 24;
            (*ppCode)++;
            Value |= **ppCode << 16;
            (*ppCode)++;
            Value |= **ppCode << 8;
            (*ppCode)++;
            Value |= **ppCode;
            (*ppCode)++;
            Offset = **ppCode << 8;
            (*ppCode)++;
            Offset |= **ppCode;
            (*ppCode)++;
            *(Int32 *)(Value + (*ppTop)[(Int16)Offset]) = pTop[-1];
            (*ppTop)--;
            break;
        }
        case 87: {
            Int32 Value;
            Int32 Offset;

            Value = *pState->pCode << 24;
            pState->pCode++;
            Value |= *pState->pCode << 16;
            pState->pCode++;
            Value |= *pState->pCode << 8;
            pState->pCode++;
            Value |= *pState->pCode;
            pState->pCode++;
            Offset = *pState->pCode << 8;
            pState->pCode++;
            Offset |= *pState->pCode;
            pState->pCode++;
            *pTop = Value + pTop[(Int16)Offset];
            pState->pTop++;
            break;
        }
        case 91:
        case 93:
        case 95:
        case 97:
        case 108:
        case 109:
        case 110: {
            Int32 *pArray;
            Int32 Element;
            Int32 Stride;
            Int32 bOnStack;
            Int32 NumDims;
            Int32 Dim;
            Int32 Size;
            Int32 Value;
            Int32 Offset;

            pArray = NULL;
            Element = 0;
            Stride = 1;
            bOnStack = 0;
            switch (Op) {
            case 97:
                bOnStack = 1;
                pArray = (Int32 *)pTop[pTop[-1] - 1];
                break;
            case 91:
            case 108:
                bOnStack = 1;
                pArray = &pTop[pTop[-1] - 1];
                break;
            case 93:
            case 109:
                pArray = (Int32 *)pTop[-1];
                bOnStack = 1;
                break;
            case 95:
            case 110:
                bOnStack = 0;
                Value = **ppCode << 24;
                (*ppCode)++;
                Value |= **ppCode << 16;
                (*ppCode)++;
                Value |= **ppCode << 8;
                (*ppCode)++;
                Value |= **ppCode;
                (*ppCode)++;
                Offset = **ppCode << 8;
                (*ppCode)++;
                Offset |= **ppCode;
                (*ppCode)++;
                pArray = (Int32 *)(Value + (*ppTop)[(Int16)Offset]);
                break;
            }
            NumDims = pArray[0];
            for (Dim = 0; Dim < NumDims; Dim++) {
                Value = pTop[-(Dim + bOnStack) - 1];
                Size = pArray[Dim + 1];
                if (Value >= Size || Value < 0) {
                    Value = Size - 1;
                }
                Element += Stride * Value;
                Stride *= Size;
            }
            if (Op >= 108 && Op <= 110) {
                pTop[-(NumDims + bOnStack)] = (Int32)&pArray[Element + 1 + NumDims];
            } else {
                pTop[-(NumDims + bOnStack)] = pArray[Element + NumDims + 1];
            }
            *ppTop -= NumDims - 1 + bOnStack;
            break;
        }
        case 92:
        case 94:
        case 96:
        case 98: {
            Int32 *pArray;
            Int32 Element;
            Int32 Stride;
            Int32 bOnStack;
            Int32 NumDims;
            Int32 Dim;
            Int32 Size;
            Int32 Value;
            Int32 Offset;

            pArray = NULL;
            Element = 0;
            Stride = 1;
            bOnStack = 0;
            switch (Op) {
            case 98:
                bOnStack = 1;
                pArray = (Int32 *)pTop[pTop[-1] - 1];
                break;
            case 92:
                bOnStack = 1;
                pArray = &pTop[pTop[-1] - 1];
                break;
            case 94:
                pArray = (Int32 *)pTop[-1];
                bOnStack = 1;
                break;
            case 96:
                Value = **ppCode << 24;
                (*ppCode)++;
                Value |= **ppCode << 16;
                (*ppCode)++;
                Value |= **ppCode << 8;
                (*ppCode)++;
                Value |= **ppCode;
                (*ppCode)++;
                Offset = **ppCode << 8;
                (*ppCode)++;
                Offset |= **ppCode;
                (*ppCode)++;
                pArray = (Int32 *)(Value + (*ppTop)[(Int16)Offset]);
                break;
            }
            NumDims = pArray[0];
            for (Dim = 0; Dim < NumDims; Dim++) {
                Value = pTop[-(Dim + bOnStack + 1) - 1];
                Size = pArray[Dim + 1];
                if (Value >= Size || Value < 0) {
                    Value = Size - 1;
                }
                Element += Stride * Value;
                Stride *= Size;
            }
            pArray[Element + NumDims + 1] = pTop[-1 - bOnStack];
            *ppTop -= NumDims + (bOnStack + 1);
            break;
        }
        case 99: {
            Int32 Count;
            Int32 i;

            Count = **ppCode << 24;
            (*ppCode)++;
            Count |= **ppCode << 16;
            (*ppCode)++;
            Count |= **ppCode << 8;
            (*ppCode)++;
            Count |= **ppCode;
            (*ppCode)++;
            for (i = 0; i < Count; i++) {
                pTop[i] = pTop[-1];
            }
            *ppTop += Count;
            break;
        }
        case 100: {
            Int32 Count;

            Count = *pState->pCode << 24;
            pState->pCode++;
            Count |= *pState->pCode << 16;
            pState->pCode++;
            Count |= *pState->pCode << 8;
            pState->pCode++;
            Count |= *pState->pCode;
            pState->pCode++;
            pState->pTop = pTop - Count;
            break;
        }
        case 101: {
            Int32 Count;
            Int32 i;

            Count = *pState->pCode << 24;
            pState->pCode++;
            Count |= *pState->pCode << 16;
            pState->pCode++;
            Count |= *pState->pCode << 8;
            pState->pCode++;
            Count |= *pState->pCode;
            pState->pCode++;
            for (i = 0; i < Count; i++) {
                pTop[i] = pTop[i - Count];
            }
            *ppTop += Count;
            break;
        }
        case 102:
        case 103:
        case 104: {
            Int32 *pArray;
            Int32 Total;
            Int32 bOnStack;
            Int32 NumDims;
            Int32 i;
            Int32 Value;
            Int32 Offset;

            pArray = NULL;
            Total = 1;
            bOnStack = 0;
            switch (Op) {
            case 102:
                bOnStack = 1;
                pArray = &pTop[pTop[-1] - 1];
                break;
            case 103:
                pArray = (Int32 *)pTop[-1];
                bOnStack = 1;
                break;
            case 104:
                Value = *pState->pCode << 24;
                pState->pCode++;
                Value |= *pState->pCode << 16;
                pState->pCode++;
                Value |= *pState->pCode << 8;
                pState->pCode++;
                Value |= *pState->pCode;
                pState->pCode++;
                Offset = *pState->pCode << 8;
                pState->pCode++;
                Offset |= *pState->pCode;
                pState->pCode++;
                pArray = (Int32 *)(Value + pTop[(Int16)Offset]);
                break;
            }
            NumDims = pArray[0];
            for (i = 0; i < NumDims; i++) {
                Total *= pArray[i + 1];
            }
            for (i = 0; i < Total; i++) {
                pArray[NumDims + 1 + i] = pTop[-1 - bOnStack];
            }
            *ppTop -= bOnStack + 1;
            break;
        }
        case 111: {
            Int32 Value;

            Value = pTop[-1];
            if (Value < pScreen->pData->NumStrings && Value >= 0) {
                pTop[-1] = (Int32)&pScreen->pData->pStrings[Value];
            } else {
                pTop[-1] = 0;
            }
            break;
        }
        case 89: {
            Int32 Value;
            Int32 Offset;
            Uint8 Type;

            Value = *pState->pCode << 24;
            pState->pCode++;
            Value |= *pState->pCode << 16;
            pState->pCode++;
            Value |= *pState->pCode << 8;
            pState->pCode++;
            Value |= *pState->pCode;
            pState->pCode++;
            Offset = *pState->pCode << 8;
            pState->pCode++;
            Offset |= *pState->pCode;
            pState->pCode++;
            Type = *pState->pCode;
            pState->pCode++;
            UISUpdateVisibility(pInfo, pScreen, Type, (void *)(Value + pTop[(Int16)Offset]), pTop[-1]);
            pState->pTop--;
            break;
        }
        case 115: {
            UISControlInfoT *pControlInfo;
            Uint32 RateFncID;

            pControlInfo = (UISControlInfoT *)*--pState->pTop;
            RateFncID = *--pState->pTop;
            *pState->pTop = UISFindRateFnc(pInfo, pControlInfo, RateFncID) < pInfo->NumRateFncs;
            pState->pTop++;
            break;
        }
        case 114: {
            Int32 Value;
            Uint32 ID;

            Value = *--pState->pTop;
            ID = *--pState->pTop;
            Action.s.GroupID = ID;
            Action.s.ScreenID = ID >> 16;
            Action.s.unk_04 = pScreen->GroupID;
            Action.s.unk_06 = pScreen->ScreenID;
            Action.Words[3] = Value;
            UISAddThreadAction(pScreen->GroupID, pScreen->ScreenID, pInfo, 8, &Action, 0, NULL);
            break;
        }
        case 116: {
            Int32 bClear;
            Int32 Bit;
            Int32 Mask;

            bClear = *--*ppTop;
            Bit = *--*ppTop;
            if (Bit < 0) {
                Mask = -1;
            } else {
                Mask = 1 << Bit;
            }
            if (bClear == 0) {
                pScreen->unk_00 |= Mask;
            } else {
                pScreen->unk_00 &= ~Mask;
            }
            break;
        }
        case 117: {
            Int32 Bit;

            Bit = *--pState->pTop;
            *pState->pTop = (pScreen->unk_00 & (1 << Bit)) == 0;
            pState->pTop++;
            break;
        }
        case 121: {
            UISStringT *pString;

            pString = (UISStringT *)*--pState->pTop;
            if (pString != NULL) {
                pState->pTop[-1] = pString->Length;
            } else {
                (*ppTop)[-1] = 0;
            }
            break;
        }
        case 122: {
            UISStringT *pString;
            Uint32 i;
            Uint8 c;

            pString = (UISStringT *)*--*ppTop;
            if (pString != NULL) {
                for (i = 0; i < pString->Length; i++) {
                    c = pString->pText[i];
                    if (c >= 'a' && c <= 'z') {
                        pString->pText[i] = c - 32;
                    }
                }
            }
            break;
        }
        case 123: {
            UISStringT *pString;
            Uint32 i;
            Uint8 c;

            pString = (UISStringT *)*--pState->pTop;
            if (pString != NULL) {
                for (i = 0; i < pString->Length; i++) {
                    c = pString->pText[i];
                    if (c >= 'A' && c <= 'Z') {
                        pString->pText[i] = c + 32;
                    }
                }
            }
            break;
        }
        case 124: {
            UISStringT *pReplace;
            UISStringT *pFind;
            UISStringT *pString;
            Uint32 Length;
            Uint32 FindLength;
            Uint32 ReplaceLength;
            Uint32 NumTries;
            Int32 Diff;
            Uint32 i;
            Uint32 j;
            Int32 bMatch;

            pReplace = (UISStringT *)*--*ppTop;
            pFind = (UISStringT *)*--*ppTop;
            pString = (UISStringT *)*--*ppTop;
            if (pString != NULL && pFind != NULL && pReplace != NULL) {
                Length = strlen(pString->pText);
                FindLength = strlen(pFind->pText);
                ReplaceLength = strlen(pReplace->pText);
                if (Length != 0 && FindLength != 0 && Length >= FindLength) {
                    NumTries = Length - FindLength + 1;
                    Diff = ReplaceLength - FindLength;
                    for (i = 0; i < NumTries; i++) {
                        bMatch = 1;
                        for (j = i; j < i + FindLength; j++) {
                            if (j >= pString->Length ||
                                pString->pText[j] != pFind->pText[j - i]) {
                                bMatch = 0;
                                break;
                            }
                        }
                        if (bMatch) {
                            if (Diff > 0) {
                                for (j = pString->Length - 1; j >= i + Diff; j--) {
                                    pString->pText[j] = pString->pText[j - Diff];
                                }
                            } else if (Diff < 0) {
                                for (j = i + ReplaceLength; j <= pString->Length + Diff; j++) {
                                    pString->pText[j] = pString->pText[j - Diff];
                                }
                            }
                            for (j = i; j < i + ReplaceLength && j < pString->Length; j++) {
                                pString->pText[j] = pReplace->pText[j - i];
                            }
                            i += ReplaceLength - 1;
                        }
                    }
                }
            }
            break;
        }
        case 125: {
            UISStringT *pString;

            pString = (UISStringT *)*--pState->pTop;
            if (pString != NULL && pInfo->pCallback28 != NULL && pScreen != NULL) {
                pInfo->pCallback28(pScreen->GroupID, pScreen->ScreenID, pString->pText);
            }
            break;
        }
        default:
            return 0;
        }
        pState->pCode = *ppCode;
    }
    return 0;
}
