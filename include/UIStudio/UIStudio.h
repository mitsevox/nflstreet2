#ifndef UISTUDIO_UISTUDIO_H
#define UISTUDIO_UISTUDIO_H

#include "types.h"

/* Type and field names follow the related Madden NFL 2003 UI Studio build.
   Regions this game's code has not yet been shown to use are left as padding. */

/* Control information block; only the fields selected by
   UISGetActionPtrValue are established. */
typedef struct UISControlInfo_t {
    Uint8 unk_00[0x08];
    Float32 f08; /* 0x08 */
    Float32 f0C; /* 0x0C */
    Float32 f10; /* 0x10 */
    Float32 f14; /* 0x14 */
    Float32 f18; /* 0x18 */
    Float32 f1C; /* 0x1C */
    Float32 f20; /* 0x20 */
    Float32 f24; /* 0x24 */
    Float32 f28; /* 0x28 */
    Float32 f2C; /* 0x2C */
    Float32 f30; /* 0x30 */
    Float32 f34; /* 0x34 */
    Uint8 unk_38[0x04];
    Float32 f3C; /* 0x3C */
    Float32 f40; /* 0x40 */
    Float32 f44; /* 0x44 */
    Float32 f48; /* 0x48 */
    Float32 f4C; /* 0x4C */
    Float32 f50; /* 0x50 */
    Float32 f54; /* 0x54 */
    Float32 f58; /* 0x58 */
} UISControlInfoT;

/* Draw colour factors (r, g, b, a). */
typedef struct UISColorVector_t {
    Float32 r; /* 0x00 */
    Float32 g; /* 0x04 */
    Float32 b; /* 0x08 */
    Float32 a; /* 0x0C */
} UISColorVectorT;

/* Per-control state block. */
typedef struct UISControlState_t {
    void *unk_00;   /* 0x00: nonzero while the control is shown */
    Int32 bEnabled; /* 0x04 */
    Uint8 unk_08[0x34];              /* 0x08: transform block passed to UISInfoT.pControlFnc */
    UISColorVectorT MultiplerFactor; /* 0x3C */
    UISColorVectorT AdditiveFactor;  /* 0x4C */
    Uint8 unk_5C[0x04];
    Int32 bCanHandleMessages;        /* 0x60 */
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

/* 8-byte item of a control's item list: ID 0xFFFF marks a link to the
   control whose index is Value; bits 0xC000 of Flags select the item kind. */
typedef struct UISControlItem_t {
    Uint16 Flags; /* 0x00 */
    Uint16 ID;    /* 0x02 */
    Int32 Value;  /* 0x04 */
} UISControlItemT;

/* 20-byte control record of a screen. */
typedef struct UISControl_t {
    UISControlStateT *pState; /* 0x00 */
    Uint32 NumNodes;          /* 0x04 */
    UISNodeT **ppNodes;       /* 0x08 */
    Uint32 NumItems;          /* 0x0C */
    UISControlItemT *pItems;  /* 0x10 */
} UISControlT;

/* 8-byte entry of a screen's object table; pOffset (when set) holds the
   object's byte offset from the start of the screen data. */
typedef struct UISObjectRef_t {
    Uint16 ID;      /* 0x00 */
    Int16 State;    /* 0x02 */
    Int32 *pOffset; /* 0x04 */
} UISObjectRefT;

/* 12-byte string record of a screen file's string table. */
typedef struct UISString_t {
    Uint32 unk_00; /* 0x00 */
    Uint32 Length; /* 0x04 */
    char *pText;   /* 0x08 */
} UISStringT;

/* A loaded screen file; its pointer fields hold file offsets until
   0x8021861C turns them into pointers. */
typedef struct UISScreenData_t {
    Uint32 NumControls;      /* 0x00 */
    UISControlT *pControls;  /* 0x04 */
    Uint32 NumStrings;       /* 0x08 */
    UISStringT *pStrings;    /* 0x0C */
    Uint32 NumPatchStrings;  /* 0x10 */
    Uint32 *pStringPatchTable; /* 0x14: file offsets of words that name a pStrings entry */
    Uint32 NumObjects;       /* 0x18 */
    UISObjectRefT *pObjects; /* 0x1C */
} UISScreenDataT;

/* 20-byte loaded-screen record. */
typedef struct UISScreen_t {
    Int32 unk_00;               /* 0x00 */
    Uint16 GroupID;             /* 0x04 */
    Uint16 ScreenID;            /* 0x06 */
    Uint16 ParentGroupID;       /* 0x08 */
    Uint16 ParentScreenID;      /* 0x0A */
    Int32 bWaitingToBeUnloaded; /* 0x0C */
    UISScreenDataT *pData;      /* 0x10 */
} UISScreenT;

/* 16-byte record passed by address to 0x8021D904 and copied into the
   thread-action stack; how it is read depends on the action type. */
typedef union UISThreadAction_t {
    struct {
        Int16 GroupID;  /* 0x00 */
        Int16 ScreenID; /* 0x02 */
        Int16 unk_04;   /* 0x04 */
        Int16 unk_06;   /* 0x06 */
        Int32 unk_08;   /* 0x08 */
        Uint16 unk_0C;  /* 0x0C */
        Uint16 unk_0E;  /* 0x0E */
    } s;
    struct {
        Int16 unk_00;   /* 0x00 */
        Int16 bDone;    /* 0x02: set to 1 once the action has run */
    } c;
    Int32 Words[4];
} UISThreadActionT;

/* The global script's screen record (laid out as UISScreenT; 0x802188D4 fills it). */
typedef struct UISCursor_t {
    Int32 unk_00;               /* 0x00 */
    Uint16 GroupID;             /* 0x04 */
    Uint16 ScreenID;            /* 0x06 */
    Uint16 ParentGroupID;       /* 0x08 */
    Uint16 ParentScreenID;      /* 0x0A */
    Int32 bWaitingToBeUnloaded; /* 0x0C */
    void *pTarget;              /* 0x10: the global script's screen data */
} UISCursorT;

/* Screen resource callbacks the game registers (group ID, screen ID). */
typedef void *UISResLoadFncT(Uint16 GroupID, Uint16 ScreenID);
typedef void UISResUnloadFncT(Uint16 GroupID, Uint16 ScreenID, void *pData);
typedef void UISScreenActivatedFncT(Uint16 GroupID, Uint16 ScreenID);

/* A word of a script call's arguments. */
typedef union UISParam_t {
    Float32 fValue;
    Int32 iValue;
    void *pValue;
} UISParamT;

typedef Int32 UISActionFncT(void *pObject, Int32, Int32, void *, Int32);

/* One entry of the action function table (UISInfoT.ActionFncs). */
typedef struct UISPlugin_t {
    UISActionFncT *pFnc; /* 0x00 */
} UISPluginT;
/* Transform callback: Action 0 init, 1 push, 2 pop, 3 shutdown, with the
   control state's transform block (+0x08). */
typedef void UISControlFncT(Int32 Action, void *pTransform);

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

/* Word stack used when calling into screen code (20 bytes); pTop is stored to
   and then advanced, pCode is the script byte code being run. */
typedef struct UISRunState_t {
    Int32 *pStackStart;   /* 0x00 */
    Int32 *pStackCurrent; /* 0x04 */
    Int32 *pStackEnd;     /* 0x08 */
    Int32 *pTop;          /* 0x0C */
    Uint8 *pCode;         /* 0x10 */
} UISRunStateT;

/* 40-byte modal record: the screen a modal screen was loaded over and the
   script state paused there. */
typedef struct UISScreenRef_t {
    UISRunStateT StackState;         /* 0x00: copy of *pRestoreState taken when the script paused */
    UISControlStateT *pControlState; /* 0x14: the screen's first control's */
    UISScreenT *pScreen;             /* 0x18 */
    Int32 *pRestoreStack;            /* 0x1C */
    UISRunStateT *pRestoreState;     /* 0x20: the live state */
    Uint16 ScreenID;                 /* 0x24 */
    Uint16 GroupID;                  /* 0x26 */
} UISScreenRefT;

/* Thread actions are pushed downwards from pTop; pStart is the first
   (highest) record. */
typedef struct UISActionStack_t {
    Int32 *pStart; /* 0x00 */
    Int32 *pTop;   /* 0x04 */
} UISActionStackT;

#define UIS_MAGIC 0x5549535F /* "UIS_", stored by 0x802188D4 */

typedef struct UISInfo_t {
    Int32 unk_00;                   /* 0x00: UIS_MAGIC once set up */
    Uint32 Flags;                   /* 0x04 */
    Uint32 MSPerTick;               /* 0x08 */
    void *pMessageFnc;              /* 0x0C */
    UISResUnloadFncT *pShutdownScreenFnc; /* 0x10 */
    UISResLoadFncT *pLoadFnc;       /* 0x14: returns a screen's data */
    UISResUnloadFncT *pUnloadFnc;   /* 0x18 */
    UISControlFncT *pControlFnc;    /* 0x1C */
    void *pCallback20;              /* 0x20 */
    UISScreenActivatedFncT *pScreenActivatedFnc; /* 0x24 */
    void (*pCallback28)(Uint16, Uint16, char *); /* 0x28: (group, screen, text) */
    void (*pCallback2C)(void);              /* 0x2C: called before the screens are drawn */
    void (*pCallback30)(void);              /* 0x30: called after the screens are drawn */
    void (*pCallback34)(Uint16, Uint16);    /* 0x34: called before each screen (group, screen) */
    void (*pCallback38)(Uint16, Uint16);    /* 0x38: called after each screen (group, screen) */
    Uint32 ActiveScreen;            /* 0x3C: index into Screens, -1 when none */
    Uint32 MaxScreens;              /* 0x40 */
    Int32 NumScreens;               /* 0x44 */
    UISScreenT *Screens;            /* 0x48 */
    UISCursorT *pCursor;            /* 0x4C */
    Uint32 MaxActionFncs;           /* 0x50 */
    Uint32 NumActionFncs;           /* 0x54 */
    UISPluginT *ActionFncs;         /* 0x58 */
    Uint32 MaxRateFncs;             /* 0x5C */
    Int32 NumRateFncs;              /* 0x60 */
    UISRateFncT *RateFncs;          /* 0x64 */
    Uint32 MaxScreenRefs;           /* 0x68 */
    Uint32 NumScreenRefs;           /* 0x6C */
    UISScreenRefT *ScreenRefs;      /* 0x70 */
    UISRunStateT RunState;          /* 0x74: passed by address to 0x802180A0 */
    UISRunStateT RateStack;         /* 0x88 */
    Uint8 unk_9C[0x20];             /* 0x9C */
    UISActionStackT ActionStack;    /* 0xBC */
    Int32 **ppStackCurrent;         /* 0xC4: &RunState.pStackCurrent */
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

/* UIStudio.c functions called from other files; names not yet established. */
Int32 UISInternalLoadScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Uint16 ParentGroupID,
                  Uint16 ParentScreenID, Uint8 Count, Int32 *pArgs);
Int32 UISInternalUnloadScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Arg3);
void UISInternalProcessEvent(UISInfoT *pInfo, UISRunStateT *pState, Int32 Arg2, Int32 Arg3, Int32 Count,
                 Int32 *pArgs, Int32 bAll);
void UISInternalActivateControl(UISInfoT *pInfo, Int32 bArg1, Int16 Arg2, Int32 Arg3, Int32 Arg4, Uint16 Arg5,
                 Uint16 Arg6);
void UISInternalActivateScreen(UISInfoT *pInfo, Int32 bArg1, Uint16 GroupID, Uint16 ScreenID);
void fn_80219650(UISInfoT *pInfo, Uint16 *pGroupID, Uint16 *pScreenID);
void UISUpdateVisibility(UISInfoT *pInfo, UISScreenT *pScreen, Int32 Type, void *pNode, Int32 bValue);

/* UI Studio functions of UISStack.c, UISUtils.c and UISActionProcess.c called from other files. */
Int32 UISStackProcess(UISInfoT *pInfo, Int32 *pFrame, UISRunStateT *pState, UISScreenT *pScreen,
                  UISControlStateT *pControlState);
Uint32 UISFindScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID);
Int32 UISExecuteFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlStateT *pControlState,
                  UISRunStateT *pState, Int32 Value, Uint32 NumArgs, Int32 *pArgs,
                  Uint32 NumExtra, Int32 *pExtra, Uint8 bPushArg, Int32 Arg, Int32 *pResult);
void UISMoveScreenDrawPosition(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 Delta);
void UISDoHint(UISInfoT *pInfo, Int32 Value, Int32 Count, Int32 *pArgs);
void UISAddThreadAction(Int16 GroupID, Int16 ScreenID, UISInfoT *pInfo, Int32 Type,
                 UISThreadActionT *pAction, Int32 Arg5, Int32 *pArg6);
void UISProcessThreadAction(UISInfoT *pInfo, Int32 Arg1);

#endif
