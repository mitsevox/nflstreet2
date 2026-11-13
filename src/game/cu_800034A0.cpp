#include "engine/cu_80229270.h"
#include "game/fn_801D2B7C.h"
#include "game/cu_800034A0.h"
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

extern "C" {

void fn_800034A0(void)
{
    lbl_803ECCA4 = fn_801D2B7C(16384, 0, 0);
}

void fn_800034D0(void)
{
    fn_801D2BD0(lbl_803ECCA4);
    lbl_803ECCA4 = 0;
}

void fn_800034FC(void)
{
    SaveRequest_t req;
    char slot[4];
    int type;

    fn_800034A0();

    *(void **)&req.mUnknown0[0] = &lbl_803EB8C8;
    *(void **)&req.mUnknown0[4] = lbl_803ECCA4;
    *(int *)&req.mUnknown0[8] = 16384;
    req.mTarget = (int)&lbl_80367580;
    req.mUnknown10 = 1;

    lbl_80367580.mFillToEnd = 1;
    lbl_80367580.mPosition = 0;

    if (UISGameGetMainViewport()) {
        VptSetCallback(UISGameGetMainViewport(), 2, (void *)MemCardFilesIdle, 31);
    }

    lbl_803EB8D4 = 1;
    MemCardFilesGetSaveTarget(&type, slot);
    lbl_803EB8C8 = 0;
    lbl_80367580.mSize = MemCardFilesGetDataSize(type);

    switch (type) {
    case 1:
        fn_8022EB94(&lbl_80367580, &gCardStreamOps);
        break;
    case 2:
        fn_8022F358(slot[3]);
        fn_8022F478();
        fn_8022F698(&req, &gCardStreamOps);
        break;
    case 3:
        fn_8022F358(slot[3]);
        fn_8022F478();
        PlayerSaveOnSave(&req, &gCardStreamOps);
        break;
    }
}

void fn_80003620(void)
{
    SaveRequest_t req;
    char slot[4];
    int type;
    int handle = 0;

    fn_800034A0();

    *(void **)&req.mUnknown0[0] = &lbl_803EB8C8;
    *(void **)&req.mUnknown0[4] = lbl_803ECCA4;
    *(int *)&req.mUnknown0[8] = 16384;
    req.mTarget = (int)&lbl_80367580;
    req.mUnknown10 = 1;

    lbl_803EB8C8 = 0;
    lbl_80367580.mFillToEnd = 1;
    lbl_80367580.mPosition = 0;

    if (UISGameGetMainViewport()) {
        VptSetCallback(UISGameGetMainViewport(), 2, (void *)MemCardFilesIdle, 31);
    }

    lbl_803EB8D4 = 1;
    MemCardFilesGetLoadTarget(&type, slot);
    lbl_80367580.mSize = MemCardFilesGetDataSize(type);

    switch (type) {
    case 1:
        handle = fn_8022EB5C(&lbl_80367580, &gCardStreamOps);
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
        break;
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
        break;
    }

    if (handle) {
        lbl_803EB8C8 = handle;
    }
}

void fn_800037C0(int a, int *b)
{
    char buf[24];
    int slot;
    int type;

    buf[0] = 1;

    MemCardFilesGetLoadTarget(&type, &slot);

    switch (type) {
    case 1:
        if (a) {
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
            fn_8022EBC8();
            fn_8022EB10();
            GameOptionsInit(1);
            GameOptionsShutdown();
        } else {
            SndgApplyVolumeOptions();
            fn_801D6B24(buf + 8, 17);
            MemCardFilesAddSlot(type, slot, MemCardFilesComputeChecksum(type, slot), buf + 8);
        }
        break;
    case 2: {
        int res = fn_8022F53C(a);
        if (res == 1) {
            fn_8022F4BC();
            fn_8022F1BC();
            if (*b >= 0) {
                *b = -50;
            }
        } else if (res == 0) {
            int res_f4bc = fn_8022F4BC();
            slot = fn_8022F384(res_f4bc);
            MemCardFilesSetLoadTarget(type, slot);
            fn_801D6B24(buf + 8, 17);
            MemCardFilesAddSlot(type, slot, lbl_80367580.mChecksum, buf + 8);
            DbCheckVersion(fn_8022F3D4(res_f4bc));
            MemCardFilesStoreChecksum(type, slot);
        } else {
            fn_8022F4BC();
            fn_8022F1BC();
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
        }
        break;
    }
    case 3: {
        int res = fn_8022F53C(a);
        if (res == 1) {
            fn_8022F4BC();
            fn_8022F1BC();
            if (*b >= 0) {
                *b = -50;
            }
        } else if (res == 0) {
            int res_f4bc = fn_8022F4BC();
            slot = fn_8022F384(res_f4bc);
            MemCardFilesSetLoadTarget(type, slot);
            fn_801D6B24(buf + 8, 17);
            MemCardFilesAddSlot(type, slot, lbl_80367580.mChecksum, buf + 8);
            MemCardFilesStoreChecksum(type, slot);
        } else {
            fn_8022F4BC();
            fn_8022F1BC();
            fn_801D6DE0(fn_801D6844(), type);
            if (*b >= 0) {
                *b = -100;
            }
        }
        break;
    }
    }
}

int fn_800039E4(int a, int *b, int *c)
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
            fn_800034FC();
            state = 5;
        }
        break;
    case 5:
        *b = 0;
        if ((unsigned int)(lbl_803EB8C8 - 45) > 1) {
            if (fn_801D6EA0((int)&val)) {
                fn_800034D0();
                state = 6;
                fn_801D6EFC();
            }
            if (val) {
                fn_800034D0();
                state = 6;
            }
        }
        break;
    case 6: {
        int type;
        int slot;
        *b = fn_801D6620(c);
        if (*b == 0) {
            return state;
        }
        if (lbl_803EB8C8 == 0 && c != 0 && *c < 0) {
            lbl_803EB8C8 = 36;
        }
        MemCardFilesGetSaveTarget(&type, &slot);
        if (lbl_803EB8C8 == 0) {
            MemCardFilesUpdateSlot(type, slot, lbl_80367580.mChecksum);
        } else {
            MemCardFilesClearSlotInfo(type, slot);
        }
        state = 0;
        break;
    }
    case 7:
        state = 9;
        *b = fn_801D6620(c);
        break;
    case 9:
        *b = fn_801D6620(c);
        if (fn_801D6EA0(0)) {
            fn_80003620();
            state = 10;
        }
        break;
    case 10:
        *b = 0;
        if ((unsigned int)(lbl_803EB8C8 - 45) > 1) {
            if (fn_801D6EA0((int)&val)) {
                fn_800034D0();
                state = 11;
                fn_801D6EFC();
            }
            if (val) {
                fn_800034D0();
                state = 11;
            }
        }
        break;
    case 11:
        *b = fn_801D6620(c);
        if (*b == 0) {
            return state;
        }
        if (lbl_803EB8C8 == 0 && c != 0 && *c < 0) {
            lbl_803EB8C8 = 36;
        }
        state = 0;
        fn_800037C0(lbl_803EB8C8, c);
        break;
    }

    if (*b != 0 && lbl_803EB8D4 != 0) {
        if (UISGameGetMainViewport()) {
            VptRemoveCallback(UISGameGetMainViewport(), (void *)MemCardFilesIdle);
        }
        lbl_803EB8D4 = 0;
    }

    return state;
}

}
