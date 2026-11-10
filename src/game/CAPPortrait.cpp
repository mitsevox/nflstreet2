/* Create-a-player portraits: loads the head, facial hair and hair parts and the head
   model of a created player for the portrait shot, manages the portrait slots, and reads
   and saves the portrait image and palette in the profile database. */

#include <string.h>
#include "game/fn_801D2B7C.h"
#include "game/fn_801EEB44.h"
#include "game/fn_801FCE10.h"
#include "game/FMCAPPORT.h"
#include "game/CAPPortrait.h"
#include "game/Object_80233EAC.h"
#include "game/cu_8015D3EC.h"
#include "engine/texfile.h"

struct PortraitSlot_t {
    unsigned char mUsed;
    unsigned char mValue;
};

struct PortraitSlotTable_t {
    PortraitSlot_t mSlots[18];
};

struct PortraitImageRequest_t {
    int mUnknown0[3];
    void *mpUnknown12;
    int mUnknown16;
    void *mpUnknown20;
};

extern "C" {
Skeleton_80041930 *fn_8003E028(void);
Skeleton_80041930 *fn_8003E030(void);
void PlaDynClutApplyColors(void *p, int id, FMCAPPORTText *pText);
void *fn_80160C08(void);
void PortraitRenderQuantize(PortraitJob_t *pObject);
void fn_801A4690(int a);
void fn_801A46BC(void);
int fn_801EFF80(void *pArchive, int id, void *pDest);
int fn_801F0C50(void *pArchive, int id);
void fn_80221BE8(void (*pCallback)(int, unsigned int, PortraitImageRequest_t *));
int fn_8022F358(int index);
int fn_8022F3D4(int a);
int fn_8022F4BC(void);
void fn_802336C4(void *pObject, Object_8023417C *pModel, int b);
void fn_80233728(void *pObject);
void fn_80233760(void *pObject, short *pValues, int count);
void fn_802347EC(void *pData, ModelTexSlot_t *pDesc, int a, int b);
void fn_80234844(ModelTexSlot_t *pDesc);

extern char lbl_802EC038[];
extern char lbl_802EC044[];
extern char lbl_802EC050[];
extern char lbl_802EC080[];
}

static PortraitSlotTable_t *_Portrait_pSlots = 0;
static Skeleton_80041930 *(*_Portrait_apGetSkeleton[2])(void) = { fn_8003E028, fn_8003E030 };
static int _Portrait_aiSkeletonParam[2] = { 15, 32 };
static const char *_Portrait_apszArchives[2] = { lbl_802EC038, lbl_802EC044 };
static ModelLod_802DF190 _Portrait_aLod0[2] = { { 0.5f, 1000, 100000, 0xFFFF }, { 0.0f, 0, 0, 0xFFFF } };
static ModelLod_802DF190 _Portrait_aLod1[2] = { { 0.5f, 1000, 100000, 0xFFFF }, { 0.0f, 0, 0, 0xFFFF } };
static ModelLod_802DF190 *_Portrait_apLods[2] = { _Portrait_aLod0, _Portrait_aLod1 };
static Object_80233EAC _Portrait_aModels[2];

extern "C" {

int PortraitIsReady(void);
void PortraitFreeSlot(int id);
void PortraitFreeAllSlots(void);
void PortraitReadImage(unsigned int id, PortraitImageRequest_t *pObject);
void _PortraitDbCallback(int type, unsigned int id, PortraitImageRequest_t *pObject);

void PortraitInitHook(void)
{
}

void PortraitConvertMorphs(const FMCAPPORTValues *pValues, short *pOut)
{
    int i;

    for (i = 0; i < 53; i++) {
        pOut[i] = pValues->mValues[i] * 4096.0f;
    }
}

void PortraitClearSlots(void)
{
    int i;

    for (i = 0; i < 18; i++) {
        _Portrait_pSlots->mSlots[i].mUsed = 0;
    }
}

void PortraitLoadParts(PortraitJob_t *pObject)
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
            TexMipmapRelocate(pData);
            id = pObject->mUnknown28[i];
            if (id != -1) {
                PlaDynClutApplyColors(TexGetPaletteByIndex(pData, TexGetMaterialByIndex(pData, 0)->mUnknown8), id,
                            &pObject->mText264[i]);
            }
        } else {
            pObject->mpUnknown368[i] = 0;
        }
    }

    ModelTexSlot_t *pDescs = pObject->mUnknown384;
    const char *names[4] = { "HEAD", "FACIALHAIR", "HAIR" };
    for (i = 0; i < 4; i++) {
        memset(&pDescs[i], 0, sizeof(ModelTexSlot_t));
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

void PortraitFreeParts(PortraitJob_t *pObject)
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

void PortraitLoadModels(PortraitJob_t *pObject)
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
                pArchive = fn_801EEB44(_Portrait_apszArchives[i], 44);
            }
            pObject->mpUnknown512[i] = fn_801D2B7C(fn_801F0C50(pArchive, id), 0, 0);
            _Portrait_apLods[i]->mId = id;
            Skeleton_80041930 *pSkeleton = PortraitGetSkeleton(i);
            fn_80233EAC(&_Portrait_aModels[i], _Portrait_apLods[i], "CAPPORT", 0, pArchive, pSkeleton,
                        &pObject->mpUnknown512[i], 1);
        } else {
            pObject->mpUnknown512[i] = 0;
        }
    }

    memset(values, 0, sizeof(values));
    if (pObject->mUnknown44[0] == 0xFFFF) {
        PortraitConvertMorphs(&pObject->mValues52, values);
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

void PortraitFreeModels(PortraitJob_t *pObject)
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

int PortraitIsReady(void)
{
    return 1;
}

void *PortraitGetModel(PortraitJob_t *pObject, int index)
{
    if (index != 0) {
        return fn_8023417C(&_Portrait_aModels[index], 0);
    }
    return pObject->mUnknown520;
}

Skeleton_80041930 *PortraitGetSkeleton(int index)
{
    return _Portrait_apGetSkeleton[index]();
}

int PortraitGetSkeletonParam(int index)
{
    return _Portrait_aiSkeletonParam[index];
}

void PortraitSystemInit(void)
{
    PortraitInitHook();
    _Portrait_pSlots = (PortraitSlotTable_t *)fn_801D2B7C(sizeof(PortraitSlotTable_t), 4, 0);
    PortraitClearSlots();
    fn_80221BE8(_PortraitDbCallback);
}

void PortraitSystemShutdown(void)
{
    PortraitFreeAllSlots();
    fn_801D2BD0(_Portrait_pSlots);
    _Portrait_pSlots = 0;
}

/* Claims the first free slot of the group and stores the value in it; returns the
   slot id (0x277 + index), or 0xFFFF when the group has no free slot. */
int PortraitAllocSlot(int value, int group)
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
        if (_Portrait_pSlots->mSlots[i].mUsed == 0) {
            _Portrait_pSlots->mSlots[i].mUsed = 1;
            id = i + 0x277;
            _Portrait_pSlots->mSlots[i].mValue = value;
            break;
        }
    }
    return id;
}

void PortraitFreeSlot(int id)
{
    int i = id - 0x277;

    if (_Portrait_pSlots->mSlots[i].mUsed == 1) {
        _Portrait_pSlots->mSlots[i].mUsed = 0;
        _Portrait_pSlots->mSlots[i].mValue = 0xFF;
    }
}

void PortraitFreeAllSlots(void)
{
    int i;

    for (i = 0; i < 18; i++) {
        PortraitFreeSlot(i + 0x277);
    }
}

void PortraitJobAllocImage(PortraitJob_t *pObject)
{
    pObject->mpUnknown4 = fn_801D2B7C(0x20000, 0, 0);
    pObject->mpUnknown8 = fn_801D2B7C(0x400, 0, 0);
}

void PortraitJobLoad(PortraitJob_t *pObject)
{
    PortraitLoadParts(pObject);
    PortraitLoadModels(pObject);
}

int PortraitJobIsLoaded(PortraitJob_t *pObject)
{
    return PortraitIsReady();
}

void PortraitJobUnload(PortraitJob_t *pObject)
{
    PortraitFreeParts(pObject);
    PortraitFreeModels(pObject);
}

void PortraitJobQuantize(PortraitJob_t *pObject)
{
    PortraitRenderQuantize(pObject);
}

int PortraitJobIsDone(PortraitJob_t *pObject)
{
    return 1;
}

void PortraitReadImage(unsigned int id, PortraitImageRequest_t *pObject)
{
    if (pObject != 0 && id >= 0x277) {
        void *pUnknown12 = pObject->mpUnknown12;
        void *pBuffer = fn_801D2B7C(0x400, 4, 0);

        fn_801FCE10(0,
                    "use \x8c select 'XTPP' into \x89 and 'LPPP' into \x89 from 'PPRC' where "
                    "'PXSP' = \x85\n",
                    fn_8022F3D4(fn_8022F358((signed char)_Portrait_pSlots->mSlots[id - 0x277].mValue)), pUnknown12, pBuffer, id);
        memcpy(pObject->mpUnknown20, pBuffer, 0x200);
        fn_801D2BD0(pBuffer);
    }
}

void PortraitJobSave(PortraitJob_t *pObject)
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

void _PortraitDbCallback(int type, unsigned int id, PortraitImageRequest_t *pObject)
{
    if (type == 10) {
        PortraitReadImage(id, pObject);
    }
}
}
