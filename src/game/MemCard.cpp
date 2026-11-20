/* Memory card save and load driver: allocates the 16 KB I/O buffer, starts the
   asynchronous save or load of the current save target (options through the card
   stream, a roster or a player profile through the database), finishes a load and
   steps the save/load state machine that MemCardFiles drives. */
#include "engine/cu_80229270.h"
#include "game/fn_801D2B7C.h"
#include "game/MemCard.h"
#include "game/PlayerSave.h"

extern "C" {
void *fn_801D2B7C(int size, int a, int b);
int UISGameGetMainViewport(void);
void VptSetCallback(int a, int b, void *c, int d);
void MemCardFilesGetSaveTarget(int *pType, void *pSlot);
int MemCardFilesGetDataSize(int type);
void fn_8022F478(void);
int fn_8022F698(SaveRequest_t *pRequest, SaveStreamOps_t *pOps);
void MemCardFilesGetLoadTarget(int *pType, void *pSlot);
int MemCardFilesIsUsed(int a, int b);
void fn_8022F1BC(void);
void MemCardFilesRemoveSlot(int a, int b);
int fn_8022F0D4(void);
int PlayerSaveOnLoad(SaveRequest_t *pRequest, SaveStreamOps_t *pOps);
int fn_8022F5E4(SaveRequest_t *pRequest, SaveStreamOps_t *pOps);
int fn_8022EB5C(CardStreamTarget *pTarget, SaveStreamOps_t *pOps);

int fn_8022F53C(int a);
int fn_8022F4BC(void);
int fn_8022F384(int a);
void MemCardFilesSetLoadTarget(int a, int b);
void fn_801D6B24(char *p, int size);
void MemCardFilesAddSlot(int a, int b, unsigned int c, char *d);
int fn_8022F3D4(int a);
void DbCheckVersion(int handle);
void MemCardFilesStoreChecksum(int a, int b);
int fn_801D6844(void);
void fn_801D6DE0(int a, int b);
void SndgApplyVolumeOptions(void);
void GameOptionsInit(int a);
void GameOptionsShutdown(void);
int MemCardFilesComputeChecksum(int a, int b);

int fn_801D6620(void *p);
int fn_801D6EA0(int a);
void fn_801D6EFC(void);
void MemCardFilesUpdateSlot(int type, int index, int value);
void MemCardFilesClearSlotInfo(int a, int b);
void VptRemoveCallback(int a, void *b);
void MemCardFilesIdle(void);

extern SaveStreamOps_t gCardStreamOps;
}

static int _MemCard_iResult = 0;
int _MemCard_aiReserved[2] = {0, 0};
static unsigned char _MemCard_bIdleCallback = 0;
static void *_MemCard_pIOBuffer;
static CardStreamTarget _MemCard_StreamTarget;

extern "C" {

void MemCardAllocateIOBuffer(void)
{
    _MemCard_pIOBuffer = fn_801D2B7C(16384, 0, 0);
}

void MemCardFreeIOBuffer(void)
{
    fn_801D2BD0(_MemCard_pIOBuffer);
    _MemCard_pIOBuffer = 0;
}

void MemCardBeginSave(void)
{
    SaveRequest_t req;
    char slot[4];
    int type;

    MemCardAllocateIOBuffer();

    *(void **)&req.mUnknown0[0] = &_MemCard_iResult;
    *(void **)&req.mUnknown0[4] = _MemCard_pIOBuffer;
    *(int *)&req.mUnknown0[8] = 16384;
    req.mUnknown10 = 1;
    req.mTarget = (int)&_MemCard_StreamTarget;

    _MemCard_StreamTarget.mFillToEnd = 1;
    _MemCard_StreamTarget.mPosition = 0;

    if (UISGameGetMainViewport()) {
        VptSetCallback(UISGameGetMainViewport(), 2, (void *)MemCardFilesIdle, 31);
    }

    _MemCard_bIdleCallback = 1;
    MemCardFilesGetSaveTarget(&type, slot);
    _MemCard_iResult = 0;
    _MemCard_StreamTarget.mSize = MemCardFilesGetDataSize(type);

    switch (type) {
    case 3:
        fn_8022F358(slot[3]);
        fn_8022F478();
        PlayerSaveOnSave(&req, &gCardStreamOps);
        break;
    case 2:
        fn_8022F358(slot[3]);
        fn_8022F478();
        fn_8022F698(&req, &gCardStreamOps);
        break;
    case 1:
        fn_8022EB94(&_MemCard_StreamTarget, &gCardStreamOps);
        break;
    }
}

void MemCardBeginLoad(void)
{
    SaveRequest_t req;
    char slot[4];
    int type;
    int handle = 0;

    MemCardAllocateIOBuffer();

    *(void **)&req.mUnknown0[0] = &_MemCard_iResult;
    *(void **)&req.mUnknown0[4] = _MemCard_pIOBuffer;
    *(int *)&req.mUnknown0[8] = 16384;
    req.mUnknown10 = 1;
    req.mTarget = (int)&_MemCard_StreamTarget;

    _MemCard_iResult = 0;
    _MemCard_StreamTarget.mFillToEnd = 1;
    _MemCard_StreamTarget.mPosition = 0;

    if (UISGameGetMainViewport()) {
        VptSetCallback(UISGameGetMainViewport(), 2, (void *)MemCardFilesIdle, 31);
    }

    _MemCard_bIdleCallback = 1;
    MemCardFilesGetLoadTarget(&type, slot);
    _MemCard_StreamTarget.mSize = MemCardFilesGetDataSize(type);

    // FAKEMATCH: each case stores its own handle (the target tests it at the end of every case)
    switch (type) {
    case 3:
        if (MemCardFilesIsUsed(3, *(int *)slot)) {
            fn_8022F358(slot[3]);
            fn_8022F1BC();
            MemCardFilesRemoveSlot(type, *(int *)slot);
        }
        if (fn_8022F0D4() != -1) {
            fn_8022F478();
            handle = PlayerSaveOnLoad(&req, &gCardStreamOps);
        }
        if (handle) {
            _MemCard_iResult = handle;
        }
        break;
    case 2:
        if (MemCardFilesIsUsed(2, *(int *)slot)) {
            fn_8022F358(slot[3]);
            fn_8022F1BC();
            MemCardFilesRemoveSlot(type, *(int *)slot);
        }
        if (fn_8022F0D4() != -1) {
            fn_8022F478();
            handle = fn_8022F5E4(&req, &gCardStreamOps);
        }
        if (handle) {
            _MemCard_iResult = handle;
        }
        break;
    case 1:
        handle = fn_8022EB5C(&_MemCard_StreamTarget, &gCardStreamOps);
        if (handle) {
            _MemCard_iResult = handle;
        }
        break;
    }
}

void MemCardFinishLoad(int a, int *b)
{
    SaveRequest_t req;
    char date[0x11];
    int type;
    int slot;

    req.mUnknown10 = 1;

    MemCardFilesGetLoadTarget(&type, &slot);

    switch (type) {
    case 3:
        a = fn_8022F53C(a);
        switch (a) {
        case 0:
            slot = fn_8022F384(fn_8022F4BC());
            MemCardFilesSetLoadTarget(type, slot);
            fn_801D6B24(date, 17);
            MemCardFilesAddSlot(type, slot, _MemCard_StreamTarget.mChecksum, date);
            MemCardFilesStoreChecksum(type, slot);
            break;
        case 1:
            fn_8022F4BC();
            fn_8022F1BC();
            if (*b >= 0) {
                *b = -50;
            }
            break;
        case 2: // FAKEMATCH: explicit case 2 shapes the dispatch tree; its body is the default one
        default:
            fn_8022F4BC();
            fn_8022F1BC();
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
            break;
        }
        break;
    case 2:
        a = fn_8022F53C(a);
        switch (a) {
        case 0: {
            int handle = fn_8022F4BC();
            slot = fn_8022F384(handle);
            MemCardFilesSetLoadTarget(type, slot);
            fn_801D6B24(date, 17);
            MemCardFilesAddSlot(type, slot, _MemCard_StreamTarget.mChecksum, date);
            DbCheckVersion(fn_8022F3D4(handle));
            MemCardFilesStoreChecksum(type, slot);
            break;
        }
        case 1:
            fn_8022F4BC();
            fn_8022F1BC();
            if (*b >= 0) {
                *b = -50;
            }
            break;
        case 2: // FAKEMATCH: explicit case 2 shapes the dispatch tree; its body is the default one
        default:
            fn_8022F4BC();
            fn_8022F1BC();
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
            break;
        }
        break;
    case 1:
        if (a == 0) {
            SndgApplyVolumeOptions();
        } else {
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
            fn_8022EBC8();
            fn_8022EB10();
            GameOptionsInit(1);
            GameOptionsShutdown();
        }
        if (a == 0) {
            fn_801D6B24(date, 17);
            MemCardFilesAddSlot(type, slot, MemCardFilesComputeChecksum(type, slot), date);
        }
        break;
    }
}

int MemCardUpdateSaveLoad(int a, int *b, int *c)
{
    char val = 0;
    int state = a;

    switch (state) {
    case 0:
        *b = fn_801D6620(c);
        break;
    case 1:
        state = 4;
        *b = fn_801D6620(c);
        break;
    case 4:
        *b = fn_801D6620(c);
        if (fn_801D6EA0(0)) {
            MemCardBeginSave();
            state = 5;
        }
        break;
    case 5:
        *b = 0;
        if ((unsigned int)(_MemCard_iResult - 45) > 1) {
            if (fn_801D6EA0((int)&val)) {
                MemCardFreeIOBuffer();
                state = 6;
                fn_801D6EFC();
            }
            if (val) {
                MemCardFreeIOBuffer();
                state = 6;
            }
        }
        break;
    case 6: {
        int type;
        int slot;
        *b = fn_801D6620(c);
        if (*b != 0) {
            if (_MemCard_iResult == 0 && c != 0 && *c < 0) {
                _MemCard_iResult = 36;
            }
            MemCardFilesGetSaveTarget(&type, &slot);
            if (_MemCard_iResult == 0) {
                MemCardFilesUpdateSlot(type, slot, _MemCard_StreamTarget.mChecksum);
            } else {
                MemCardFilesClearSlotInfo(type, slot);
            }
            state = 0;
        }
        break;
    }
    case 7:
        state = 9;
        *b = fn_801D6620(c);
        break;
    case 9:
        *b = fn_801D6620(c);
        if (fn_801D6EA0(0)) {
            MemCardBeginLoad();
            state = 10;
        }
        break;
    case 10:
        *b = 0;
        if ((unsigned int)(_MemCard_iResult - 45) > 1) {
            if (fn_801D6EA0((int)&val)) {
                MemCardFreeIOBuffer();
                state = 11;
                fn_801D6EFC();
            }
            if (val) {
                MemCardFreeIOBuffer();
                state = 11;
            }
        }
        break;
    case 11:
        *b = fn_801D6620(c);
        if (*b != 0) {
            if (_MemCard_iResult == 0 && c != 0 && *c < 0) {
                _MemCard_iResult = 36;
            }
            state = 0;
            MemCardFinishLoad(_MemCard_iResult, c);
        }
        break;
    }

    if (*b != 0 && _MemCard_bIdleCallback != 0) {
        if (UISGameGetMainViewport()) {
            VptRemoveCallback(UISGameGetMainViewport(), (void *)MemCardFilesIdle);
        }
        _MemCard_bIdleCallback = 0;
    }

    return state;
}

}
