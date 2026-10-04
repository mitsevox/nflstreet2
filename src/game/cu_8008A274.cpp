#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801FCE10.h"
#include "game/FMCAPPORT.h"

struct Slot_8008A900 {
    unsigned char mUsed;
    unsigned char mValue;
};

struct SlotTable_8008A900 {
    Slot_8008A900 mSlots[18];
};

struct Desc_80233EAC {
    float mUnknown0;
    int mUnknown4;
    int mUnknown8;
    int mUnknown12;
    char mUnknown16[76];
    int mUnknown92;
    char mUnknown96[64];
};

struct Object_80233EAC {
    int mUnknown0[5];
};

struct Object_8008AAF8 {
    int mUnknown0[3];
    void *mpUnknown12;
    int mUnknown16;
    void *mpUnknown20;
};

struct Object_8020E52C {
    int mUnknown0[2];
    unsigned short mUnknown8;
};

extern "C" {
int fn_8003E028(void);
int fn_8003E030(void);
void fn_8004625C(void *p, int id, FMCAPPORTText *pText);
int fn_8015E2FC(int a, int b, int c);
void fn_8015E73C(int id);
void fn_8015E908(int a);
void fn_8015F3FC(int a);
void *fn_80160C08(void);
void fn_80199BD4(Object_8008A9F8 *pObject);
void fn_801A4690(int a);
void fn_801A46BC(void);
int fn_801EFF80(void *pArchive, int id, void *pDest);
int fn_801F0C50(void *pArchive, int id);
void fn_8020E2B0(void *p);
Object_8020E52C *fn_8020E52C(void *p, int index);
void *fn_8020E5F8(void *p, int index);
void fn_80221BE8(void (*pCallback)(int, unsigned int, Object_8008AAF8 *));
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
void fn_802336C4(void *pObject, int a, int b);
void fn_80233728(void *pObject);
void fn_80233760(void *pObject, short *pValues, int count);
void fn_80233EAC(Object_80233EAC *pObject, Desc_80233EAC *pDesc, const char *pName, int a,
                 void *pArchive, int b, void **ppData, int c);
void *fn_8023417C(Object_80233EAC *pObject, int a);
void fn_802347EC(void *pData, Desc_802347EC *pDesc, int a, int b);
void fn_80234844(Desc_802347EC *pDesc);

extern char lbl_802EC038[];
extern char lbl_802EC044[];
extern char lbl_802EC050[];
extern char lbl_802EC080[];
}

static SlotTable_8008A900 *sSlots = 0;
static int (*sCallbacks[2])(void) = { fn_8003E028, fn_8003E030 };
static int sUnknown[2] = { 15, 32 };
static const char *sFileNames[2] = { lbl_802EC038, lbl_802EC044 };
static Desc_80233EAC sDesc0 = { 0.5f, 1000, 100000, 0xFFFF, { 0 }, 0xFFFF };
static Desc_80233EAC sDesc1 = { 0.5f, 1000, 100000, 0xFFFF, { 0 }, 0xFFFF };
static Desc_80233EAC *sDescs[2] = { &sDesc0, &sDesc1 };
static Object_80233EAC sObjects[2];

extern "C" {

int fn_8008A800(void);
int fn_8008A84C(int index);
void fn_8008A988(int id);
void fn_8008A9BC(void);
void fn_8008AAF8(unsigned int id, Object_8008AAF8 *pObject);
void fn_8008AC10(int type, unsigned int id, Object_8008AAF8 *pObject);

void fn_8008A274(void)
{
}

void fn_8008A278(const FMCAPPORTValues *pValues, short *pOut)
{
    int i;

    for (i = 0; i < 53; i++) {
        pOut[i] = pValues->mValues[i] * 4096.0f;
    }
}

void fn_8008A2B8(void)
{
    int i;

    for (i = 0; i < 18; i++) {
        sSlots->mSlots[i].mUsed = 0;
    }
}

void fn_8008A2E0(Object_8008A9F8 *pObject)
{
    unsigned int i;
    void *pArchive = fn_80160C08();
    int loaded = 0;

    if (pArchive == 0) {
        pArchive = fn_801EEB44(lbl_802EC080, 44);
        loaded = 1;
    }

    for (i = 0; i < 4; i++) {
        int id = pObject->mUnknown12[i];

        if (id != -1) {
            void *pData = fn_801D2B7C(fn_801F0C50(pArchive, id), 0, 0);

            pObject->mpUnknown368[i] = pData;
            fn_801EFF80(pArchive, id, pData);
            fn_8020E2B0(pData);
            id = pObject->mUnknown28[i];
            if (id != -1) {
                fn_8004625C(fn_8020E5F8(pData, fn_8020E52C(pData, 0)->mUnknown8), id,
                            &pObject->mText264[i]);
            }
        } else {
            pObject->mpUnknown368[i] = 0;
        }
    }

    Desc_802347EC *pDescs = pObject->mUnknown384;
    const char *names[4] = { "HEAD", "FACIALHAIR", "HAIR" };
    for (i = 0; i < 4; i++) {
        memset(&pDescs[i], 0, sizeof(Desc_802347EC));
        if (i != 3) {
            if (pObject->mpUnknown368[i] == 0) {
                pDescs[i].mpName = (char *)fn_801D2B7C(15, 0, 0);
                strncpy(pDescs[i].mpName, "", 15);
            } else {
                pDescs[i].mpName = (char *)fn_801D2B7C(15, 0, 0);
                strncpy(pDescs[i].mpName, names[i], 15);
            }
        }
    }

    for (i = 0; i < 4; i++) {
        if (pObject->mpUnknown368[i] != 0) {
            fn_802347EC(pObject->mpUnknown368[i], &pObject->mUnknown384[i], 7, 1);
        }
    }

    if (loaded == 1) {
        fn_801EEFAC(pArchive);
    }
}

void fn_8008A504(Object_8008A9F8 *pObject)
{
    unsigned int i;

    for (i = 0; i < 4; i++) {
        if (pObject->mUnknown384[i].mpName != 0) {
            fn_801D2BD0(pObject->mUnknown384[i].mpName);
            pObject->mUnknown384[i].mpName = 0;
            fn_80234844(&pObject->mUnknown384[i]);
        }
    }

    for (i = 0; i < 4; i++) {
        if (pObject->mpUnknown368[i] != 0) {
            fn_801D2BD0(pObject->mpUnknown368[i]);
        }
    }
}

void fn_8008A590(Object_8008A9F8 *pObject)
{
    short values[53];
    unsigned int i;

    fn_801A4690(0);
    for (i = 0; i < 2; i++) {
        int id = pObject->mUnknown44[i];

        if (id != 0xFFFF) {
            void *pArchive;

            if (i == 1 && (unsigned int)id > 50000) {
                pArchive = fn_801EEB44(lbl_802EC050, 44);
                id -= 50000;
            } else {
                pArchive = fn_801EEB44(sFileNames[i], 44);
            }
            pObject->mpUnknown512[i] = fn_801D2B7C(fn_801F0C50(pArchive, id), 0, 0);
            sDescs[i]->mUnknown12 = id;
            int value = fn_8008A84C(i);
            fn_80233EAC(&sObjects[i], sDescs[i], "CAPPORT", 0, pArchive, value,
                        &pObject->mpUnknown512[i], 1);
        } else {
            pObject->mpUnknown512[i] = 0;
        }
    }

    memset(values, 0, sizeof(values));
    if (pObject->mUnknown44[0] == 0xFFFF) {
        fn_8008A278(&pObject->mValues52, values);
        fn_802336C4(pObject->mUnknown520, fn_8015E2FC(6, 0, 0), 50000);
        fn_80233760(pObject->mUnknown520, values, 53);
    } else {
        fn_8015E73C(pObject->mUnknown44[0]);
        values[1] = 0x1000;
        values[pObject->mUnknown364 + 2] = 0x1000;
        fn_802336C4(pObject->mUnknown520, fn_8015E2FC(4, 0, 0), 50000);
        fn_80233760(pObject->mUnknown520, values, 37);
    }
    fn_8015F3FC(0);
    fn_801A46BC();
}

void fn_8008A78C(Object_8008A9F8 *pObject)
{
    unsigned int i;

    for (i = 0; i < 2; i++) {
        if (pObject->mpUnknown512[i] != 0) {
            fn_801D2BD0(pObject->mpUnknown512[i]);
        }
    }
    fn_80233728(pObject->mUnknown520);
    if (pObject->mUnknown44[0] != 0xFFFF) {
        fn_8015E908(0);
    }
}

int fn_8008A800(void)
{
    return 1;
}

void *fn_8008A808(Object_8008A9F8 *pObject, int index)
{
    if (index != 0) {
        return fn_8023417C(&sObjects[index], 0);
    }
    return pObject->mUnknown520;
}

int fn_8008A84C(int index)
{
    return sCallbacks[index]();
}

int fn_8008A87C(int index)
{
    return sUnknown[index];
}

void fn_8008A88C(void)
{
    fn_8008A274();
    sSlots = (SlotTable_8008A900 *)fn_801D2B7C(sizeof(SlotTable_8008A900), 4, 0);
    fn_8008A2B8();
    fn_80221BE8(fn_8008AC10);
}

void fn_8008A8D0(void)
{
    fn_8008A9BC();
    fn_801D2BD0(sSlots);
    sSlots = 0;
}

/* Claims the first free slot of the group and stores the value in it; returns the
   slot id (0x277 + index), or 0xFFFF when the group has no free slot. */
int fn_8008A900(int value, int group)
{
    int id = 0xFFFF;
    int start = 0xFFFF;
    int end = 0xFFFF;
    int i;

    switch (group) {
    case 0:
        start = 0;
        end = 16;
        break;
    case 1:
        start = 16;
        end = 18;
        break;
    }

    for (i = start; i < end; i++) {
        if (sSlots->mSlots[i].mUsed == 0) {
            sSlots->mSlots[i].mUsed = 1;
            id = i + 0x277;
            sSlots->mSlots[i].mValue = value;
            break;
        }
    }
    return id;
}

void fn_8008A988(int id)
{
    int i = id - 0x277;

    if (sSlots->mSlots[i].mUsed == 1) {
        sSlots->mSlots[i].mUsed = 0;
        sSlots->mSlots[i].mValue = 0xFF;
    }
}

void fn_8008A9BC(void)
{
    int i;

    for (i = 0; i < 18; i++) {
        fn_8008A988(i + 0x277);
    }
}

void fn_8008A9F8(Object_8008A9F8 *pObject)
{
    pObject->mpUnknown4 = fn_801D2B7C(0x20000, 0, 0);
    pObject->mpUnknown8 = fn_801D2B7C(0x400, 0, 0);
}

void fn_8008AA48(Object_8008A9F8 *pObject)
{
    fn_8008A2E0(pObject);
    fn_8008A590(pObject);
}

int fn_8008AA7C(Object_8008A9F8 *pObject)
{
    return fn_8008A800();
}

void fn_8008AA9C(Object_8008A9F8 *pObject)
{
    fn_8008A504(pObject);
    fn_8008A78C(pObject);
}

void fn_8008AAD0(Object_8008A9F8 *pObject)
{
    fn_80199BD4(pObject);
}

int fn_8008AAF0(Object_8008A9F8 *pObject)
{
    return 1;
}

void fn_8008AAF8(unsigned int id, Object_8008AAF8 *pObject)
{
    if (pObject != 0 && id >= 0x277) {
        void *pUnknown12 = pObject->mpUnknown12;
        void *pBuffer = fn_801D2B7C(0x400, 4, 0);

        fn_801FCE10(0,
                    "use \x8c select 'XTPP' into \x89 and 'LPPP' into \x89 from 'PPRC' where "
                    "'PXSP' = \x85\n",
                    fn_8022F3D4(fn_8022F358((signed char)sSlots->mSlots[id - 0x277].mValue)), pUnknown12, pBuffer, id);
        memcpy(pObject->mpUnknown20, pBuffer, 0x200);
        fn_801D2BD0(pBuffer);
    }
}

void fn_8008ABA4(Object_8008A9F8 *pObject)
{
    void *pUnknown4 = pObject->mpUnknown4;
    void *pUnknown8 = pObject->mpUnknown8;

    fn_801FCE10(0,
                "use \x8c update 'PPRC' set 'XTPP' = \x89 and 'LPPP' = \x89 where 'PXSP' = "
                "\x85\n",
                fn_8022F3D4(fn_8022F4BC()), pUnknown4, pUnknown8, pObject->mUnknown0);
    fn_801D2BD0(pUnknown4);
    fn_801D2BD0(pUnknown8);
}

void fn_8008AC10(int type, unsigned int id, Object_8008AAF8 *pObject)
{
    if (type == 10) {
        fn_8008AAF8(id, pObject);
    }
}
}
