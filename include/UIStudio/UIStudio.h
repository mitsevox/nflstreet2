#ifndef UISTUDIO_UISTUDIO_H
#define UISTUDIO_UISTUDIO_H

#include "types.h"

/* Type and field names follow the related Madden NFL 2003 UI Studio build.
   Regions this game's code has not yet been shown to use are left as padding. */

typedef struct UISControlInfo_t UISControlInfoT;

typedef struct UISScreen_t {
    Uint8 unk_00[0x0C];
    Int32 bWaitingToBeUnloaded; /* 0x0C */
} UISScreenT;

typedef struct UISAnimateData_t {
    Uint32 iType;                     /* 0x00: UIS_ACTION_* value */
    Float32 fEndValue;                /* 0x04 */
    Float32 fStepValue;               /* 0x08: change per tick */
    Uint8 *pEndFnc;                   /* 0x0C */
    UISControlInfoT *pSubControlInfo; /* 0x10 */
} UISAnimateDataT;

/* A script routine run at a fixed rate on behalf of a control. */
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
    Uint8 unk_00[0x08];
    Uint32 MSPerTick;               /* 0x08 */
    Uint8 unk_0C[0x54];
    Uint32 NumRateFncs;             /* 0x60 */
    UISRateFncT *RateFncs;          /* 0x64 */
    /* Remaining fields not yet established. */
} UISInfoT;

enum {
    UISRATE_LOAD = 0,
    UISRATE_UNLOAD = 1,
    UISRATE_ACTIVE = 2
};

/* Called with a level, source file, line number and message. */
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

#endif
