#ifndef UISTUDIO_UISTUDIO_H
#define UISTUDIO_UISTUDIO_H

#include "types.h"

/* Type and field names follow the related Madden NFL 2003 UI Studio build.
   Regions this game's code has not yet been shown to use are left as padding. */

typedef struct UISControlInfo_t UISControlInfoT;

/* Per-control state block; only the enable word is established. */
typedef struct UISControlState_t {
    Uint8 unk_00[0x04];
    Int32 bEnabled; /* 0x04 */
} UISControlStateT;

/* 8-byte entry of a control node: ID 0xFFFF marks a link to the control
   whose index is Value; other IDs select an action function. */
typedef struct UISNodeEntry_t {
    Uint16 ID;    /* 0x00 */
    Int16 State;  /* 0x02 */
    Int32 Value;  /* 0x04 */
} UISNodeEntryT;

typedef struct UISNode_t {
    Int32 *pFlag;             /* 0x00: first word nonzero when the node is live */
    Uint32 NumEntries;        /* 0x04 */
    UISNodeEntryT *pEntries;  /* 0x08 */
} UISNodeT;

/* 20-byte control record of a screen. */
typedef struct UISControl_t {
    UISControlStateT *pState; /* 0x00 */
    Uint32 NumNodes;          /* 0x04 */
    UISNodeT **ppNodes;       /* 0x08 */
    Uint8 unk_0C[0x08];
} UISControlT;

/* 8-byte entry of a screen's object table; pOffset (when set) holds the
   object's byte offset from the start of the screen data. */
typedef struct UISObjectRef_t {
    Uint16 ID;      /* 0x00 */
    Int16 State;    /* 0x02 */
    Int32 *pOffset; /* 0x04 */
} UISObjectRefT;

typedef struct UISScreenData_t {
    Uint8 unk_00[0x04];
    UISControlT *pControls;  /* 0x04 */
    Uint8 unk_08[0x10];
    Uint32 NumObjects;       /* 0x18 */
    UISObjectRefT *pObjects; /* 0x1C */
} UISScreenDataT;

/* 20-byte loaded-screen record. */
typedef struct UISScreen_t {
    Uint8 unk_00[0x04];
    Uint16 GroupID;             /* 0x04 */
    Uint16 ScreenID;            /* 0x06 */
    Uint8 unk_08[0x04];
    Int32 bWaitingToBeUnloaded; /* 0x0C */
    UISScreenDataT *pData;      /* 0x10 */
} UISScreenT;

/* 16-byte record passed by address to 0x8021D904. */
typedef struct UISThreadAction_t {
    Int16 GroupID;  /* 0x00 */
    Int16 ScreenID; /* 0x02 */
    Int16 unk_04;   /* 0x04 */
    Int16 unk_06;   /* 0x06 */
    Uint8 unk_08[0x08];
} UISThreadActionT;

typedef struct UISCursor_t {
    Uint8 unk_00[0x10];
    void *pTarget; /* 0x10 */
} UISCursorT;

typedef Int32 UISActionFncT(void *pObject, Int32, Int32, void *, Int32);
typedef void UISControlFncT(void *, void *);

typedef struct UISAnimateData_t {
    Uint32 iType;                     /* 0x00: selector passed to UISGetActionPtrValue */
    Float32 fEndValue;                /* 0x04 */
    Float32 fStepValue;               /* 0x08: change per firing */
    Uint8 *pEndFnc;                   /* 0x0C */
    UISControlInfoT *pSubControlInfo; /* 0x10 */
} UISAnimateDataT;

typedef struct UISRateFnc_t {
    Uint32 RateFncID;               /* 0x00 */
    Uint8 *pFnc;                    /* 0x04 */
    Uint32 MSCount;                 /* 0x08 */
    Uint32 MSLastCount;             /* 0x0C */
    Uint32 MSRate;                  /* 0x10 */
    Uint32 State;                   /* 0x14: UISRATE_* */
    UISControlInfoT *pControlInfo;  /* 0x18 */
    UISScreenT *pScreen;            /* 0x1C */
    UISAnimateDataT AnimationData;  /* 0x20 */
} UISRateFncT;

typedef struct UISInfo_t {
    Int32 unk_00;                   /* 0x00 */
    Uint32 Flags;                   /* 0x04 */
    Uint32 MSPerTick;               /* 0x08 */
    void *pCallback0C;              /* 0x0C */
    void *pCallback10;              /* 0x10 */
    void *pCallback14;              /* 0x14 */
    void *pCallback18;              /* 0x18 */
    UISControlFncT *pControlFnc;    /* 0x1C */
    Uint8 unk_20[0x04];
    void *pCallback24;              /* 0x24 */
    Uint8 unk_28[0x14];
    Uint32 ActiveScreen;            /* 0x3C: index into Screens, -1 when none */
    Uint8 unk_40[0x04];
    Int32 NumScreens;               /* 0x44 */
    UISScreenT *Screens;            /* 0x48 */
    UISCursorT *pCursor;            /* 0x4C */
    Uint8 unk_50[0x04];
    Uint32 NumActionFncs;           /* 0x54 */
    UISActionFncT **ActionFncs;     /* 0x58 */
    Uint8 unk_5C[0x04];
    Int32 NumRateFncs;              /* 0x60 */
    UISRateFncT *RateFncs;          /* 0x64 */
    Uint8 unk_68[0x0C];
    Uint8 unk_74[0x54];             /* 0x74: passed by address to 0x802180A0 */
    Int32 bShuttingDown;            /* 0xC8 */
} UISInfoT;

enum {
    UISRATE_LOAD = 0,
    UISRATE_UNLOAD = 1,
    UISRATE_ACTIVE = 2
};

/* Called with an integer (0 at all known call sites), source file, line number and message. */
typedef void UISRuntimeErrorFncT(Int32, const char *, Int32, const char *);

extern UISRuntimeErrorFncT *RuntimeErrorFnc;

Float32 *UISGetActionPtrValue(Uint32 Action, UISControlInfoT *pControlInfo);

Uint32 UISFindRateFnc(UISInfoT *pInfo, UISControlInfoT *pControlInfo, Uint32 RateFncID);
void UISLoadAdvRateFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlInfoT *pControlInfo,
                       UISControlInfoT *pSubControlInfo, Uint32 RateFncID, Uint8 *pEndFnc,
                       Uint8 *pAcelFnc, Uint32 MSDur, Float32 targValue, Uint32 animType);
void UISLoadRateFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlInfoT *pControlInfo,
                    Uint32 RateFncID, Uint8 *pFnc, Uint32 MSRate);
void UISUnloadRateFnc(UISInfoT *pInfo, UISControlInfoT *pControlInfo, Uint32 RateFncID);
void UISRemoveUnNessaryRateFncs(UISInfoT *pInfo);

/* UI Studio functions outside UIStudio.c whose names are not yet established. */
Int32 fn_8021C5EC(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID);
void fn_8021D904(Int16 GroupID, Int16 ScreenID, UISInfoT *pInfo, Int32 Type,
                 UISThreadActionT *pAction, Int32 Arg5, Int32 *pArg6);
void fn_8021DDF4(UISInfoT *pInfo, Int32 Arg1);

#endif
