#ifndef UISTUDIO_UISTUDIO_H
#define UISTUDIO_UISTUDIO_H

#include "types.h"

/* Type and field names follow the related Madden NFL 2003 UI Studio build.
   Regions this game's code has not yet been shown to use are left as padding. */

typedef struct UISControlInfo_t UISControlInfoT;
typedef struct UISControlList_t UISControlListT;

/* One word of a script or thread-action stack. */
typedef union UISParam_t {
    Int32 iValue;
    /* Other members not yet established. */
} UISParamT;

typedef struct UISStackInfo_t {
    Uint8 unk_00[0x14];
} UISStackInfoT;

typedef struct UISScreen_t {
    Uint8 unk_00[0x0C];
    Int32 bWaitingToBeUnloaded; /* 0x0C */
    Uint8 unk_10[0x04];
} UISScreenT;

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

/* The pending thread actions: a stack of UISParamT words growing downward from
   pBeginParams to pCurrentParams. */
typedef struct UISLocalThreadInfo_t {
    UISParamT *pBeginParams;        /* 0x00 */
    UISParamT *pCurrentParams;      /* 0x04 */
    /* Remaining fields not yet established. */
} UISLocalThreadInfoT;

typedef struct UISInfo_t {
    Uint8 unk_00[0x04];
    Uint32 CriticalRegions;         /* 0x04: UISCRITICAL_* */
    Uint32 MSPerTick;               /* 0x08 */
    Uint8 unk_0C[0x38];
    Uint32 NumScreens;              /* 0x44 */
    UISScreenT *Screens;            /* 0x48 */
    Uint8 unk_4C[0x14];
    Int32 NumRateFncs;              /* 0x60 */
    UISRateFncT *RateFncs;          /* 0x64 */
    Uint8 unk_68[0x0C];
    UISStackInfoT EventStack;       /* 0x74 */
    Uint8 unk_88[0x34];
    UISLocalThreadInfoT ThreadInfo; /* 0xBC */
} UISInfoT;

enum {
    UISRATE_LOAD = 0,
    UISRATE_UNLOAD = 1,
    UISRATE_ACTIVE = 2
};

enum {
    UISCRITICAL_THREADACTIONS = 1,  /* the thread-action stack is being processed */
    UISCRITICAL_INTERNALEVENTS = 2  /* a queued action is dispatching an internal event */
};

typedef enum {
    UISThreadAction_Load = 0,
    UISThreadAction_Unload = 1,
    UISThreadAction_Update = 2,
    UISThreadAction_ScreenActivate = 3,
    UISThreadAction_ScreenDeactivate = 4,
    UISThreadAction_ControlActivate = 5,
    UISThreadAction_ControlDeactivate = 6,
    UISThreadAction_ProcessEvent = 7,
    UISThreadAction_MoveScreen = 8,
    UISThreadAction_HINT = 9
} UISThreadActionT;

typedef struct UISThreadGroupInfoMessage_t {
    Uint32 Message;                 /* 0x00 */
    Uint32 Controller;              /* 0x04 */
    Uint32 pad1;                    /* 0x08 */
    Uint32 pad2;                    /* 0x0C */
} UISThreadGroupInfoMessageT;

typedef struct UISThreadGroupInfoActivate_t {
    Int16 iDir;                     /* 0x00 */
    Int16 iProcessed;               /* 0x02 */
    UISControlListT *pTableEntry;   /* 0x04 */
    UISControlInfoT *pControlInfo;  /* 0x08 */
    Uint16 GroupID;                 /* 0x0C */
    Uint16 ScreenID;                /* 0x0E */
} UISThreadGroupInfoActivateT;

typedef struct UISThreadGroupInfoScreen_t {
    Uint16 GroupID;                 /* 0x00 */
    Uint16 ScreenID;                /* 0x02 */
    Uint16 ParentGroupID;           /* 0x04 */
    Uint16 ParentScreenID;          /* 0x06 */
    Uint32 iRetVal;                 /* 0x08 */
    Int32 iDir;                     /* 0x0C */
} UISThreadGroupInfoScreenT;

typedef struct UISThreadGroupInfoGeneric_t {
    Uint32 Data[4];                 /* 0x00 */
} UISThreadGroupInfoGenericT;

/* The fixed-size part of a queued thread action. */
typedef union {
    UISThreadGroupInfoMessageT MessageInfo;
    UISThreadGroupInfoActivateT ActivateInfo;
    UISThreadGroupInfoScreenT ScreenInfo;
    UISThreadGroupInfoGenericT GenericInfo;
} UISThreadGroupInfoT;

/* Called with an integer (0 at all known call sites), source file, line number and message. */
typedef void UISRuntimeErrorFncT(Int32, const char *, Int32, const char *);

extern UISRuntimeErrorFncT *RuntimeErrorFnc;

/* UIStudio.c */
Bool UISInternalLoadScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Uint16 ParentGroupID,
                           Uint16 ParentScreenID, Uint8 nParams, UISParamT *pParams);
Bool UISInternalUnloadScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 iRetVal);
void UISProcessInternalEvents(UISInfoT *pInfo, UISStackInfoT *pStackInfo, Int32 Channel,
                              Uint32 Message, Uint32 nParam, UISParamT *pParam, Bool AllScreens);
void UISInternalActivateControl(UISInfoT *pInfo, Bool bActivate, Uint32 iDir,
                                UISControlInfoT *pControlInfo, UISControlListT *pTableEntry,
                                Uint16 GroupID, Uint16 ScreenID);
void UISInternalActivateScreen(UISInfoT *pInfo, Bool bActivate, Uint16 GroupID, Uint16 ScreenID);

/* UISUtils.c */
Uint32 UISFindScreen(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID);
Float32 *UISGetActionPtrValue(Uint32 Action, UISControlInfoT *pControlInfo);
void UISMoveScreenDrawPosition(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID, Int32 iDir);
void UISDoHint(UISInfoT *pInfo, Uint32 Hint, Int32 nParms, UISParamT *pParam);

/* UISError.c */
void UISRegisterRuntimeErrorFnc(UISRuntimeErrorFncT *pRuntimeErrorFnc);

/* UISEvent.c */
Uint32 UISFindRateFnc(UISInfoT *pInfo, UISControlInfoT *pControlInfo, Uint32 RateFncID);
void UISLoadAdvRateFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlInfoT *pControlInfo,
                       UISControlInfoT *pSubControlInfo, Uint32 RateFncID, Uint8 *pEndFnc,
                       Uint8 *pAcelFnc, Uint32 MSDur, Float32 targValue, Uint32 animType);
void UISLoadRateFnc(UISInfoT *pInfo, UISScreenT *pScreen, UISControlInfoT *pControlInfo,
                    Uint32 RateFncID, Uint8 *pFnc, Uint32 MSRate);
void UISUnloadRateFnc(UISInfoT *pInfo, UISControlInfoT *pControlInfo, Uint32 RateFncID);
void UISRemoveUnNessaryRateFncs(UISInfoT *pInfo);

/* UISActionProcess.c */
void UISAddThreadAction(Int16 GroupID, Int16 ScreenID, UISInfoT *pInfo, UISThreadActionT Action,
                        UISThreadGroupInfoT *pInputThreadInfo, Int32 nParms, UISParamT *pParms);
Bool UISThreadProcessHints(UISInfoT *pInfo, Uint16 GroupID, Uint16 ScreenID);
void UISProcessThreadAction(UISInfoT *pInfo, Bool bControlEventsOnly);

#endif
